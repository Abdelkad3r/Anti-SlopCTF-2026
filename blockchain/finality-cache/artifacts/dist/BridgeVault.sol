// SPDX-License-Identifier: MIT
pragma solidity ^0.8.24;

library TinyECDSA {
    function recover(bytes32 digest, bytes memory signature) internal pure returns (address) {
        require(signature.length == 65, "bad sig len");
        bytes32 r;
        bytes32 s;
        uint8 v;
        assembly {
            r := mload(add(signature, 0x20))
            s := mload(add(signature, 0x40))
            v := byte(0, mload(add(signature, 0x60)))
        }
        if (v < 27) {
            v += 27;
        }
        require(v == 27 || v == 28, "bad v");
        address signer = ecrecover(digest, v, r, s);
        require(signer != address(0), "bad sig");
        return signer;
    }
}

contract BridgeVault {
    using TinyECDSA for bytes32;

    address public immutable relayer;
    address public constant ROUTE_FACTORY = 0x5F8d1f6A0dcf9D0A7f7c2eb5fb1131d2F3A77f12;
    bytes32 public constant ROUTE_INIT_HASH =
        hex"8d04f2c7d4bcb67aa725d38ec7f8dd54b99d1c0b7e4a0a6e6d9fba9bb5d41f46";
    uint64 public constant ROUTE_BONUS_CAP = 40000;

    mapping(uint64 => address) public sessionTarget;
    mapping(uint64 => bytes16) private sessionEpochSeed;
    mapping(uint64 => uint64) public pendingBatchId;
    mapping(uint64 => uint64) public pendingNullifier;
    mapping(uint64 => uint64) public pendingCommittedAmount;
    mapping(uint64 => uint64) public balances;
    mapping(uint64 => bool) public settled;
    mapping(uint64 => mapping(uint64 => bool)) public usedNullifiers;

    bytes32 private immutable DOMAIN_SEPARATOR;
    bytes32 private constant NAME_HASH = keccak256("FinalityCache");
    bytes32 private constant VERSION_HASH = keccak256("10");
    bytes32 private constant CLAIM_TYPEHASH =
        keccak256("TransitClaim(uint64 sessionId,uint64 batchId,uint64 nullifier,uint64 committedAmount,bytes32 claimHash)");

    uint256 private constant FIELD_RECIPIENT = 1;
    uint256 private constant FIELD_AMOUNT = 2;
    uint256 private constant FIELD_MEMO = 3;
    uint256 private constant FIELD_LANE_HINT = 4;
    uint256 private constant FIELD_FRAME = 5;
    uint256 private constant FIELD_ROUTE = 6;
    uint256 private constant FIELD_CHECKPOINT = 7;
    uint256 private constant FIELD_SEAL = 8;

    uint256 private constant ROUTE_FIELD_BOOST = 1;
    uint256 private constant ROUTE_FIELD_SALT = 2;
    uint256 private constant ROUTE_FIELD_TICKET = 3;

    uint256 private constant CHECKPOINT_FIELD_BOOST = 1;
    uint256 private constant CHECKPOINT_FIELD_SEAL = 2;

    struct ClaimState {
        address recipient;
        uint64 amount;
        bytes memo;
        uint64 laneHint;
        uint64 routeBonusAmount;
        bytes routeSalt;
        bytes routeTicket;
        uint64 checkpointBonusAmount;
        bytes checkpointSeal;
        bytes sealMac;
    }

    constructor(address relayer_) {
        relayer = relayer_;
        DOMAIN_SEPARATOR = keccak256(
            abi.encode(
                keccak256("EIP712Domain(string name,string version,uint256 chainId,address verifyingContract)"),
                NAME_HASH,
                VERSION_HASH,
                block.chainid,
                address(this)
            )
        );
    }

    function openSession(uint64 sessionId, address target, bytes16 epochSeed) external {
        require(sessionTarget[sessionId] == address(0), "session exists");
        sessionTarget[sessionId] = target;
        sessionEpochSeed[sessionId] = epochSeed;
    }

    function register(uint64 sessionId, uint64 batchId, uint64 nullifier, uint64 committedAmount) external {
        require(sessionTarget[sessionId] != address(0), "no session");
        require(!settled[sessionId], "settled");
        pendingBatchId[sessionId] = batchId;
        pendingNullifier[sessionId] = nullifier;
        pendingCommittedAmount[sessionId] = committedAmount;
    }

    function redeem(uint64 sessionId, bytes calldata claimBlob, bytes calldata signature) external returns (uint64) {
        require(sessionTarget[sessionId] != address(0), "no session");
        require(!settled[sessionId], "settled");

        ClaimState memory state;
        _mergeClaim(claimBlob, 0, state);
        require(state.recipient == sessionTarget[sessionId], "wrong recipient");

        uint64 batchId = pendingBatchId[sessionId];
        uint64 nullifier = pendingNullifier[sessionId];
        uint64 committedAmount = pendingCommittedAmount[sessionId];
        require(!usedNullifiers[sessionId][nullifier], "used");

        bytes32 claimHash = keccak256(claimBlob);
        bytes32 structHash =
            keccak256(abi.encode(CLAIM_TYPEHASH, sessionId, batchId, nullifier, committedAmount, claimHash));
        bytes32 digest = keccak256(abi.encodePacked("\x19\x01", DOMAIN_SEPARATOR, structHash));
        require(digest.recover(signature) == relayer, "bad signer");

        uint64 credit = state.amount;
        if (credit > committedAmount) {
            credit = committedAmount;
        }

        bool routeOk = false;
        if (state.routeSalt.length == 32 && state.routeTicket.length == 16) {
            bytes32 routeSalt = _loadBytes32(state.routeSalt);
            bytes16 expectedTicket =
                bytes16(keccak256(abi.encodePacked(routeSalt, batchId, state.laneHint, keccak256(state.memo))));
            if (computeRouteTarget(routeSalt) == sessionTarget[sessionId] && _loadBytes16(state.routeTicket) == expectedTicket)
            {
                routeOk = true;
                if (state.routeBonusAmount > credit) {
                    credit = state.routeBonusAmount > ROUTE_BONUS_CAP ? ROUTE_BONUS_CAP : state.routeBonusAmount;
                }
            }
        }

        if (routeOk && state.checkpointSeal.length == 16) {
            bytes16 expectedSeal = computeEpochSeal(_loadBytes32(state.routeSalt), sessionEpochSeed[sessionId], batchId, state.memo);
            if (_loadBytes16(state.checkpointSeal) == expectedSeal && state.checkpointBonusAmount > credit) {
                credit = state.checkpointBonusAmount;
            }
        }

        usedNullifiers[sessionId][nullifier] = true;
        settled[sessionId] = true;
        balances[sessionId] += credit;
        return balances[sessionId];
    }

    function decodeClaim(bytes calldata claimBlob)
        external
        pure
        returns (
            address recipient,
            uint64 amount,
            bytes memory memo,
            uint64 laneHint,
            uint64 routeBonusAmount,
            bytes memory routeSalt,
            bytes memory routeTicket,
            uint64 checkpointBonusAmount,
            bytes memory checkpointSeal,
            bytes memory sealMac
        )
    {
        ClaimState memory state;
        _mergeClaim(claimBlob, 0, state);
        return (
            state.recipient,
            state.amount,
            state.memo,
            state.laneHint,
            state.routeBonusAmount,
            state.routeSalt,
            state.routeTicket,
            state.checkpointBonusAmount,
            state.checkpointSeal,
            state.sealMac
        );
    }

    function computeRouteTarget(bytes32 routeSalt) public pure returns (address) {
        return address(uint160(uint256(keccak256(abi.encodePacked(hex"ff", ROUTE_FACTORY, routeSalt, ROUTE_INIT_HASH)))));
    }

    function computeRouteTicket(bytes32 routeSalt, uint64 batchId, uint64 laneHint, bytes calldata memo)
        external
        pure
        returns (bytes16)
    {
        return bytes16(keccak256(abi.encodePacked(routeSalt, batchId, laneHint, keccak256(memo))));
    }

    function computeEpochSeal(bytes32 routeSalt, bytes16 epochSeed, uint64 batchId, bytes memory memo)
        public
        pure
        returns (bytes16)
    {
        return bytes16(keccak256(abi.encodePacked(routeSalt, epochSeed, batchId, keccak256(memo))));
    }

    function _mergeRoute(bytes calldata routeBlob, ClaimState memory state) internal pure {
        uint256 off = 0;
        while (off < routeBlob.length) {
            (uint256 tag, uint256 next) = readVarint(routeBlob, off);
            uint256 fieldNo = tag >> 3;
            uint256 wireType = tag & 0x07;
            off = next;
            if (wireType == 0) {
                (uint256 value, uint256 afterValue) = readVarint(routeBlob, off);
                off = afterValue;
                if (fieldNo == ROUTE_FIELD_BOOST) {
                    state.routeBonusAmount = uint64(value);
                }
            } else if (wireType == 2) {
                (uint256 size, uint256 afterSize) = readVarint(routeBlob, off);
                off = afterSize;
                uint256 end = off + size;
                require(end <= routeBlob.length, "route len");
                bytes calldata payload = routeBlob[off:end];
                off = end;
                if (fieldNo == ROUTE_FIELD_SALT) {
                    state.routeSalt = bytes(payload);
                } else if (fieldNo == ROUTE_FIELD_TICKET) {
                    state.routeTicket = bytes(payload);
                }
            } else {
                revert("route wire");
            }
        }
    }

    function _mergeCheckpoint(bytes calldata checkpointBlob, ClaimState memory state) internal pure {
        uint256 off = 0;
        while (off < checkpointBlob.length) {
            (uint256 tag, uint256 next) = readVarint(checkpointBlob, off);
            uint256 fieldNo = tag >> 3;
            uint256 wireType = tag & 0x07;
            off = next;
            if (wireType == 0) {
                (uint256 value, uint256 afterValue) = readVarint(checkpointBlob, off);
                off = afterValue;
                if (fieldNo == CHECKPOINT_FIELD_BOOST) {
                    state.checkpointBonusAmount = uint64(value);
                }
            } else if (wireType == 2) {
                (uint256 size, uint256 afterSize) = readVarint(checkpointBlob, off);
                off = afterSize;
                uint256 end = off + size;
                require(end <= checkpointBlob.length, "checkpoint len");
                bytes calldata payload = checkpointBlob[off:end];
                off = end;
                if (fieldNo == CHECKPOINT_FIELD_SEAL) {
                    state.checkpointSeal = bytes(payload);
                }
            } else {
                revert("checkpoint wire");
            }
        }
    }

    function _mergeClaim(bytes calldata claimBlob, uint256 depth, ClaimState memory state) internal pure {
        require(depth < 5, "depth");
        uint256 off = 0;
        while (off < claimBlob.length) {
            (uint256 tag, uint256 next) = readVarint(claimBlob, off);
            uint256 fieldNo = tag >> 3;
            uint256 wireType = tag & 0x07;
            off = next;
            if (wireType == 0) {
                (uint256 value, uint256 afterValue) = readVarint(claimBlob, off);
                off = afterValue;
                if (fieldNo == FIELD_AMOUNT) {
                    state.amount = uint64(value);
                } else if (fieldNo == FIELD_LANE_HINT) {
                    state.laneHint = uint64(value);
                }
            } else if (wireType == 2) {
                (uint256 size, uint256 afterSize) = readVarint(claimBlob, off);
                off = afterSize;
                uint256 end = off + size;
                require(end <= claimBlob.length, "bad len");
                bytes calldata payload = claimBlob[off:end];
                off = end;
                if (fieldNo == FIELD_RECIPIENT) {
                    require(payload.length == 20, "recipient len");
                    state.recipient = address(bytes20(payload));
                } else if (fieldNo == FIELD_MEMO) {
                    state.memo = bytes(payload);
                } else if (fieldNo == FIELD_ROUTE) {
                    _mergeRoute(payload, state);
                } else if (fieldNo == FIELD_CHECKPOINT) {
                    _mergeCheckpoint(payload, state);
                } else if (fieldNo == FIELD_FRAME) {
                    _mergeClaim(payload, depth + 1, state);
                } else if (fieldNo == FIELD_SEAL) {
                    state.sealMac = bytes(payload);
                }
            } else {
                revert("wire");
            }
        }
    }

    function _loadBytes32(bytes memory data) internal pure returns (bytes32 out) {
        require(data.length == 32, "route salt len");
        assembly {
            out := mload(add(data, 0x20))
        }
    }

    function _loadBytes16(bytes memory data) internal pure returns (bytes16 out) {
        require(data.length == 16, "ticket len");
        assembly {
            out := mload(add(data, 0x20))
        }
    }

    function readVarint(bytes calldata blob, uint256 off) internal pure returns (uint256 value, uint256 next) {
        uint256 shift = 0;
        next = off;
        while (next < blob.length && shift < 70) {
            uint8 b = uint8(blob[next]);
            next += 1;
            value |= uint256(b & 0x7F) << shift;
            if ((b & 0x80) == 0) {
                return (value, next);
            }
            shift += 7;
        }
        revert("varint");
    }
}
