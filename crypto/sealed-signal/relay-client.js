(() => {
  const MAGIC = new TextEncoder().encode('R1');
  const enc = new TextEncoder();
  const dec = new TextDecoder();
  const TAG = {
    NAME: 0x01,
    SID: 0x02,
    MOTD: 0x03,
    ROOM: 0x04,
    DRAFT: 0x05,
    TOKEN: 0x06,
    ROLE: 0x07,
    SCOPE: 0x08,
    MESSAGE: 0x09,
    FLAG: 0x0a,
    EXPORT: 0x0b,
    DIALECT: 0x0c,
    BLOB: 0x0d,
    CAPSULE: 0x0e,
    CACHE: 0x0f,
  };
  const OP = {
    HELLO: 0x10,
    HELLO_ACK: 0x11,
    OPEN: 0x20,
    OPENED: 0x21,
    SEAL: 0x30,
    SEALED: 0x31,
    RESUME: 0x40,
    RESUMED: 0x41,
    FLAGREQ: 0x50,
    FLAG: 0x51,
    CAPSULE: 0x60,
    CAPPED: 0x61,
    ERROR: 0x7f,
  };

  let ws = null;
  let nextXid = 1;
  let lastDraft = null;
  let dialect = null;

  const $ = (id) => document.getElementById(id);
  const logEl = $('log');
  const statusEl = $('status');

  function log(s) {
    logEl.textContent += s + '\n';
    logEl.scrollTop = logEl.scrollHeight;
  }

  function wireOpcode(op) {
    if (dialect === null || op === OP.HELLO || op === OP.HELLO_ACK) return op;
    return op ^ dialect;
  }

  function realOpcode(op) {
    if (dialect === null || op === OP.HELLO || op === OP.HELLO_ACK) return op;
    return op ^ dialect;
  }

  function swapNibbleByte(b) {
    return ((b & 0x0f) << 4) | ((b & 0xf0) >> 4);
  }

  function swapNibbles(buf) {
    const out = new Uint8Array(buf.length);
    for (let i = 0; i < buf.length; i++) out[i] = swapNibbleByte(buf[i]);
    return out;
  }

  function crc16Ccitt(buf) {
    let crc = 0xffff;
    for (const b of buf) {
      crc ^= b << 8;
      for (let i = 0; i < 8; i++) {
        if (crc & 0x8000) crc = ((crc << 1) ^ 0x1021) & 0xffff;
        else crc = (crc << 1) & 0xffff;
      }
    }
    return crc;
  }

  function encodeVarint(n) {
    const out = [];
    do {
      let b = n & 0x7f;
      n >>>= 7;
      if (n) b |= 0x80;
      out.push(b);
    } while (n);
    return Uint8Array.from(out);
  }

  function decodeVarint(buf, off) {
    let val = 0, shift = 0, pos = off;
    while (true) {
      if (pos >= buf.length) throw new Error('truncated varint');
      const b = buf[pos++];
      val |= (b & 0x7f) << shift;
      if (!(b & 0x80)) return [val, pos];
      shift += 7;
    }
  }

  function concat(arrays) {
    const total = arrays.reduce((n, a) => n + a.length, 0);
    const out = new Uint8Array(total);
    let off = 0;
    for (const a of arrays) {
      out.set(a, off);
      off += a.length;
    }
    return out;
  }

  function encodeFields(fields) {
    const parts = [];
    for (const [tag, value] of fields) {
      parts.push(Uint8Array.of(tag));
      parts.push(encodeVarint(value.length));
      parts.push(value);
    }
    return concat(parts);
  }

  function decodeFields(payload) {
    const fields = new Map();
    let off = 0;
    while (off < payload.length) {
      const tag = payload[off++];
      const [len, next] = decodeVarint(payload, off);
      off = next;
      fields.set(tag, payload.slice(off, off + len));
      off += len;
    }
    return fields;
  }

  function encodeFrame(op, xid, fields) {
    const payload = encodeFields(fields);
    const head = concat([
      Uint8Array.of(wireOpcode(op)),
      Uint8Array.of(xid & 0xff, (xid >>> 8) & 0xff),
      encodeVarint(payload.length),
      payload,
    ]);
    const crc = crc16Ccitt(head);
    const raw = concat([head, Uint8Array.of(crc & 0xff, (crc >>> 8) & 0xff)]);
    return concat([MAGIC, swapNibbles(raw)]).buffer;
  }

  function decodeFrame(ab) {
    const wire = new Uint8Array(ab);
    if (wire.length < 4 || wire[0] !== MAGIC[0] || wire[1] !== MAGIC[1]) throw new Error('bad magic');
    const raw = swapNibbles(wire.slice(2));
    const body = raw.slice(0, -2);
    const got = raw[raw.length - 2] | (raw[raw.length - 1] << 8);
    const want = crc16Ccitt(body);
    if (got !== want) throw new Error('bad crc');
    const op = realOpcode(body[0]);
    const xid = body[1] | (body[2] << 8);
    const [len, off] = decodeVarint(body, 3);
    const payload = body.slice(off, off + len);
    return {op, xid, fields: decodeFields(payload)};
  }

  function bytesToB64(buf) {
    let s = '';
    for (const b of buf) s += String.fromCharCode(b);
    return btoa(s).replace(/\+/g, '-').replace(/\//g, '_').replace(/=+$/g, '');
  }

  function b64ToBytes(txt) {
    txt = txt.replace(/-/g, '+').replace(/_/g, '/');
    while (txt.length % 4) txt += '=';
    const s = atob(txt);
    const out = new Uint8Array(s.length);
    for (let i = 0; i < s.length; i++) out[i] = s.charCodeAt(i);
    return out;
  }

  function send(op, fields) {
    if (!ws || ws.readyState !== WebSocket.OPEN) throw new Error('not connected');
    const xid = nextXid++;
    ws.send(encodeFrame(op, xid, fields));
    return xid;
  }

  $('connect').onclick = () => {
    dialect = null;
    nextXid = 1;
    lastDraft = null;
    ws = new WebSocket((location.protocol === 'https:' ? 'wss://' : 'ws://') + location.host + '/ws');
    ws.binaryType = 'arraybuffer';
    ws.onopen = () => {
      statusEl.textContent = 'connected';
      log('[*] websocket open');
      send(OP.HELLO, [[TAG.NAME, enc.encode($('nick').value)]]);
    };
    ws.onclose = () => {
      statusEl.textContent = 'closed';
      log('[*] websocket closed');
    };
    ws.onerror = () => log('[!] websocket error');
    ws.onmessage = (ev) => {
      const frame = decodeFrame(ev.data);
      if (frame.op === OP.HELLO_ACK) {
        const d = frame.fields.get(TAG.DIALECT);
        dialect = d ? d[0] : 0;
        log('[+] HELLO_ACK sid=' + Array.from(frame.fields.get(TAG.SID)).map(x => x.toString(16).padStart(2, '0')).join('') + ' dialect=0x' + dialect.toString(16).padStart(2, '0') + ' motd=' + dec.decode(frame.fields.get(TAG.MOTD)));
      } else if (frame.op === OP.OPENED) {
        const draft = frame.fields.get(TAG.DRAFT);
        lastDraft = draft;
        log('[+] OPENED draft=' + (draft[0] | (draft[1] << 8)) + ' room=' + dec.decode(frame.fields.get(TAG.ROOM)));
      } else if (frame.op === OP.SEALED) {
        const token = frame.fields.get(TAG.TOKEN);
        const capsule = frame.fields.get(TAG.CAPSULE);
        const cache = frame.fields.get(TAG.CACHE);
        const draft = frame.fields.get(TAG.DRAFT);
        const ctr = frame.fields.get(TAG.EXPORT);
        $('token').value = bytesToB64(token);
        $('capsule').value = bytesToB64(capsule);
        if (cache) $('blob').value = dec.decode(cache);
        log('[+] SEALED draft=' + (draft[0] | (draft[1] << 8)) + ' room=' + dec.decode(frame.fields.get(TAG.ROOM)) + ' export=' + (ctr ? (ctr[0] | (ctr[1] << 8) | (ctr[2] << 16) | (ctr[3] << 24)) : 0) + ' token=' + bytesToB64(token) + ' capsule=' + bytesToB64(capsule));
      } else if (frame.op === OP.CAPPED) {
        const capsule = frame.fields.get(TAG.CAPSULE);
        $('capsule').value = bytesToB64(capsule);
        log('[+] CAPPED blob=' + dec.decode(frame.fields.get(TAG.BLOB)) + ' capsule=' + bytesToB64(capsule));
      } else if (frame.op === OP.RESUMED) {
        log('[+] RESUMED role=' + dec.decode(frame.fields.get(TAG.ROLE)) + ' scope=' + dec.decode(frame.fields.get(TAG.SCOPE)) + ' room=' + dec.decode(frame.fields.get(TAG.ROOM)));
      } else if (frame.op === OP.FLAG) {
        log('[FLAG] ' + dec.decode(frame.fields.get(TAG.FLAG)));
      } else if (frame.op === OP.ERROR) {
        log('[ERR] ' + dec.decode(frame.fields.get(TAG.MESSAGE)));
      } else {
        log('[?] op=' + frame.op);
      }
    };
  };

  $('open').onclick = () => {
    const room = $('room').value;
    if (room.length !== 8) return log('[!] room must be 8 chars');
    send(OP.OPEN, [[TAG.ROOM, enc.encode(room)]]);
  };

  $('seal').onclick = () => {
    if (!lastDraft) return log('[!] open a draft first');
    send(OP.SEAL, [[TAG.DRAFT, lastDraft]]);
  };

  $('resume').onclick = () => {
    const tok = $('token').value.trim();
    const cap = $('capsule').value.trim();
    send(OP.RESUME, [[TAG.TOKEN, b64ToBytes(tok)], [TAG.CAPSULE, b64ToBytes(cap)]]);
  };

  $('flag').onclick = () => send(OP.FLAGREQ, []);

  $('capsule-sign').onclick = () => {
    send(OP.CAPSULE, [[TAG.BLOB, enc.encode($('blob').value)]]);
  };
})();
