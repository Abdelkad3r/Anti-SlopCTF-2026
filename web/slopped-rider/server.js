import crypto from "node:crypto";
import http from "node:http";
import https from "node:https";
import net from "node:net";
import path from "node:path";
import { fileURLToPath } from "node:url";
import express from "express";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const FLAG = process.env.FLAG || "FLAG_REDACTED_REMOTE_ONLY";
const SCORE_KEY =
  process.env.SCORE_KEY ||
  crypto.randomBytes(32).toString("hex");
const PORT = Number(process.env.PORT || 3000);
const OPS_PORT = Number(process.env.OPS_PORT || 43219);
const TARGET_SCORE = 676767;

function closes(points) {
  return points.map((p) => p.close);
}

const featured = {
  TSLA: {
    symbol: "TSLA",
    name: "Tesla Inc.",
    exchange: "NASDAQ",
    period: "5y",
    difficulty: "hard",
    performance: 93.9,
    dataPoints: [
      { date: "2021-06-14", close: 205.9 }, { date: "2021-08-12", close: 240.75 },
      { date: "2021-10-13", close: 270.36 }, { date: "2021-11-02", close: 390.67 },
      { date: "2022-01-03", close: 399.93 }, { date: "2022-03-24", close: 337.97 },
      { date: "2022-05-25", close: 219.6 }, { date: "2022-08-16", close: 306.56 },
      { date: "2022-11-23", close: 183.2 }, { date: "2023-01-06", close: 113.06 },
      { date: "2023-03-29", close: 193.88 }, { date: "2023-06-20", close: 274.45 },
      { date: "2023-09-11", close: 273.58 }, { date: "2023-11-29", close: 244.14 },
      { date: "2024-01-31", close: 187.29 }, { date: "2024-04-23", close: 144.68 },
      { date: "2024-07-15", close: 252.64 }, { date: "2024-10-22", close: 217.97 },
      { date: "2024-12-23", close: 430.6 }, { date: "2025-02-26", close: 290.8 },
      { date: "2025-05-16", close: 349.98 }, { date: "2025-08-28", close: 345.98 },
      { date: "2025-10-28", close: 460.55 }, { date: "2026-01-20", close: 419.25 },
      { date: "2026-03-23", close: 380.85 }, { date: "2026-06-11", close: 399.15 }
    ]
  },
  BTC: {
    symbol: "BTC",
    name: "Bitcoin",
    exchange: "CRYPTO",
    period: "5y",
    difficulty: "hard",
    performance: 78.7,
    dataPoints: [
      { date: "2021-06-12", close: 35552.52 }, { date: "2021-08-13", close: 47793.32 },
      { date: "2021-10-13", close: 57401.1 }, { date: "2021-11-23", close: 57569.07 },
      { date: "2022-01-24", close: 36654.33 }, { date: "2022-04-16", close: 40424.48 },
      { date: "2022-06-16", close: 20381.65 }, { date: "2022-08-17", close: 23336 },
      { date: "2022-11-27", close: 16444.63 }, { date: "2023-01-28", close: 23031.09 },
      { date: "2023-03-30", close: 28033.56 }, { date: "2023-06-20", close: 28327.49 },
      { date: "2023-08-21", close: 26124.14 }, { date: "2023-11-11", close: 37138.05 },
      { date: "2024-01-11", close: 46368.59 }, { date: "2024-03-13", close: 73083.5 },
      { date: "2024-06-03", close: 68804.78 }, { date: "2024-08-24", close: 64178.99 },
      { date: "2024-10-24", close: 68161.05 }, { date: "2024-12-04", close: 98768.53 },
      { date: "2025-02-24", close: 91418.17 }, { date: "2025-05-17", close: 103191.09 },
      { date: "2025-07-18", close: 118003.23 }, { date: "2025-10-08", close: 123354.87 },
      { date: "2026-01-18", close: 93634.43 }, { date: "2026-06-12", close: 63521.57 }
    ]
  },
  NVDA: {
    symbol: "NVDA",
    name: "NVIDIA Corp.",
    exchange: "NASDAQ",
    period: "5y",
    difficulty: "hard",
    performance: 1036.9,
    dataPoints: [
      { date: "2021-06-14", close: 18.02 }, { date: "2021-09-01", close: 22.44 },
      { date: "2021-11-22", close: 31.96 }, { date: "2022-01-24", close: 23.37 },
      { date: "2022-04-13", close: 22.2 }, { date: "2022-07-27", close: 17.79 },
      { date: "2022-10-14", close: 11.23 }, { date: "2023-01-27", close: 20.36 },
      { date: "2023-05-30", close: 40.11 }, { date: "2023-07-31", close: 46.73 },
      { date: "2023-11-29", close: 48.14 }, { date: "2024-01-31", close: 61.53 },
      { date: "2024-03-12", close: 91.91 }, { date: "2024-06-03", close: 115 },
      { date: "2024-08-22", close: 123.74 }, { date: "2024-10-22", close: 143.59 },
      { date: "2025-01-15", close: 136.24 }, { date: "2025-04-07", close: 97.64 },
      { date: "2025-06-27", close: 157.75 }, { date: "2025-08-08", close: 182.7 },
      { date: "2025-10-28", close: 201.03 }, { date: "2026-02-09", close: 190.04 },
      { date: "2026-04-13", close: 189.31 }, { date: "2026-06-11", close: 204.87 }
    ]
  },
  ENRN: {
    symbol: "ENRN",
    name: "Enron Corp.",
    exchange: "NYSE",
    period: "crash",
    difficulty: "insane",
    performance: -91.6,
    dataPoints: [
      { date: "1990-01-31", close: 56.88 }, { date: "1991-07-31", close: 62 },
      { date: "1992-08-31", close: 95.25 }, { date: "1993-08-31", close: 137 },
      { date: "1994-11-30", close: 108 }, { date: "1995-12-29", close: 152.5 },
      { date: "1996-10-31", close: 186 }, { date: "1998-06-30", close: 216.25 },
      { date: "1999-07-30", close: 340.75 }, { date: "2000-02-29", close: 550 },
      { date: "2000-08-31", close: 679 }, { date: "2001-01-31", close: 640 },
      { date: "2001-05-31", close: 423.28 }, { date: "2001-08-31", close: 279.92 },
      { date: "2001-10-31", close: 111.2 }, { date: "2001-12-31", close: 4.8 }
    ],
    defunct: true
  },
  SLOP: {
    symbol: "SLOP",
    name: "Slop Futures Charity Index",
    exchange: "LOCAL",
    period: "1y",
    difficulty: "medium",
    performance: 12.4,
    dataPoints: [
      { date: "2025-01-01", close: 32 }, { date: "2025-01-15", close: 34 },
      { date: "2025-02-01", close: 35 }, { date: "2025-02-15", close: 33 },
      { date: "2025-03-01", close: 38 }, { date: "2025-03-15", close: 41 },
      { date: "2025-04-01", close: 37 }, { date: "2025-04-15", close: 45 },
      { date: "2025-05-01", close: 44 }, { date: "2025-05-15", close: 48 },
      { date: "2025-06-01", close: 47 }, { date: "2025-06-15", close: 50 },
      { date: "2025-07-01", close: 49 }, { date: "2025-07-15", close: 55 },
      { date: "2025-08-01", close: 53 }, { date: "2025-08-15", close: 58 },
      { date: "2025-09-01", close: 57 }, { date: "2025-09-15", close: 62 },
      { date: "2025-10-01", close: 59 }, { date: "2025-10-15", close: 66 },
      { date: "2025-11-01", close: 64 }, { date: "2025-11-15", close: 69 }
    ]
  }
};

for (const chart of Object.values(featured)) {
  chart.prices = closes(chart.dataPoints);
}

const leaderboard = [
  { nick: "chartdad", score: 4920, symbol: "BTC", at: "2026-06-12T00:12:44Z" },
  { nick: "bagholder", score: 4688, symbol: "ENRN", at: "2026-06-12T00:17:01Z" },
  { nick: "tax-loss", score: 4391, symbol: "TSLA", at: "2026-06-12T00:23:12Z" }
];

function encodeJson(obj) {
  return Buffer.from(JSON.stringify(obj)).toString("base64url");
}

function decodeJson(raw) {
  return JSON.parse(Buffer.from(raw, "base64url").toString("utf8"));
}

function signPayload(payload) {
  return crypto.createHmac("sha256", SCORE_KEY).update(payload).digest("base64url");
}

function makeTicket(data) {
  const payload = encodeJson(data);
  return `${payload}.${signPayload(payload)}`;
}

function verifyTicket(ticket) {
  if (typeof ticket !== "string" || !ticket.includes(".")) {
    throw new Error("bad ticket");
  }
  const [payload, sig] = ticket.split(".", 2);
  const expected = signPayload(payload);
  const a = Buffer.from(sig);
  const b = Buffer.from(expected);
  if (a.length !== b.length || !crypto.timingSafeEqual(a, b)) {
    throw new Error("bad signature");
  }
  return decodeJson(payload);
}

function difficultyFor(points) {
  const deltas = [];
  for (let i = 1; i < points.length; i += 1) {
    deltas.push(Math.abs(points[i] - points[i - 1]) / Math.max(points[i - 1], 1));
  }
  return Math.min(1, deltas.reduce((a, b) => a + b, 0) / Math.max(deltas.length, 1));
}

function realScoreCap(chart) {
  const diff = difficultyFor(chart.prices);
  const base = 2900 + Math.round(diff * 1600);
  const crashBonus = chart.period === "crash" ? 410 : 0;
  return Math.min(5000, base + crashBonus);
}

function normalizeChart(input) {
  if (!input || typeof input !== "object") return null;
  const prices = Array.isArray(input.prices)
    ? input.prices.map((v) => Number(v)).filter((v) => Number.isFinite(v) && v > 0)
    : [];
  if (prices.length < 8 || prices.length > 256) return null;
  return {
    symbol: String(input.symbol || "CUSTOM").slice(0, 12).toUpperCase(),
    name: String(input.name || "Custom Charity Chart").slice(0, 80),
    exchange: String(input.exchange || "URL").slice(0, 20),
    period: String(input.period || "custom").slice(0, 20),
    difficulty: String(input.difficulty || "custom").slice(0, 20),
    performance: Number(input.performance || 0),
    prices
  };
}

function fetchUrl(rawUrl) {
  return new Promise((resolve, reject) => {
    let parsed;
    try {
      parsed = new URL(rawUrl);
    } catch {
      reject(new Error("invalid url"));
      return;
    }

    if (!["http:", "https:"].includes(parsed.protocol)) {
      reject(new Error("only http(s) chart feeds are supported"));
      return;
    }

    const client = parsed.protocol === "https:" ? https : http;
    const req = client.request(
      parsed,
      {
        method: "GET",
        timeout: 2500,
        headers: { "User-Agent": "SloppedRider chart previewer" }
      },
      (res) => {
        let body = "";
        res.setEncoding("utf8");
        res.on("data", (chunk) => {
          body += chunk;
          if (body.length > 64 * 1024) {
            req.destroy(new Error("too large"));
          }
        });
        res.on("end", () => resolve({ status: res.statusCode || 0, body }));
      }
    );
    req.on("error", reject);
    req.on("timeout", () => req.destroy(new Error("timeout")));
    req.end();
  });
}

function createOpsServer() {
  const server = net.createServer((socket) => {
    socket.once("data", (buf) => {
      const firstLine = String(buf).split("\r\n")[0] || "";
      const pathPart = firstLine.split(" ")[1] || "/";
      let body;
      if (pathPart === "/health") {
        body = JSON.stringify({ ok: true, service: "sloppedrider-ops" });
      } else if (pathPart === "/ops/config") {
        body = JSON.stringify({
          service: "sloppedrider-ops",
          scoreKey: SCORE_KEY,
          targetScore: TARGET_SCORE,
          note: "score tickets are HMAC-SHA256 over the base64url JSON payload"
        });
      } else {
        body = JSON.stringify({ error: "not found" });
      }
      socket.end(
        [
          "HTTP/1.1 200 OK",
          "Content-Type: application/json; charset=utf-8",
          `Content-Length: ${Buffer.byteLength(body)}`,
          "Connection: close",
          "",
          body
        ].join("\r\n")
      );
    });
  });
  server.listen(OPS_PORT, "127.0.0.1");
}

const app = express();
app.disable("x-powered-by");
app.use(express.json({ limit: "128kb" }));
app.use("/assets", express.static(path.join(__dirname, "public")));

app.get("/", (_req, res) => res.redirect("/rider"));

app.get("/rider", (_req, res) => {
  res.sendFile(path.join(__dirname, "public", "index.html"));
});

app.get("/api/tickers", (_req, res) => {
  res.json(Object.values(featured).map(({ prices, ...rest }) => ({ ...rest, points: prices.length })));
});

app.get("/api/chart/:symbol", (req, res) => {
  const symbol = String(req.params.symbol || "").toUpperCase();
  const chart = featured[symbol];
  if (!chart) {
    res.status(404).json({ error: "unknown ticker" });
    return;
  }
  const cap = realScoreCap(chart);
  res.json({
    chart,
    rideTicket: makeTicket({
      v: 1,
      kind: "ride",
      symbol: chart.symbol,
      period: chart.period,
      cap,
      iat: Math.floor(Date.now() / 1000)
    })
  });
});

app.post("/api/chart/preview", async (req, res) => {
  const feedUrl = String(req.body?.url || "");
  if (feedUrl.length > 300) {
    res.status(400).json({ error: "url too long" });
    return;
  }

  try {
    const result = await fetchUrl(feedUrl);
    const json = JSON.parse(result.body);
    const chart = normalizeChart(json);
    if (!chart) {
      res.status(400).json({
        error: "chart feed must include 8-256 positive prices",
        sample: result.body.slice(0, 600)
      });
      return;
    }
    res.json({
      sourceStatus: result.status,
      chart,
      rideTicket: makeTicket({
        v: 1,
        kind: "preview",
        symbol: chart.symbol,
        period: chart.period,
        cap: realScoreCap(chart),
        iat: Math.floor(Date.now() / 1000)
      })
    });
  } catch (err) {
    res.status(502).json({
      error: "chart feed failed",
      detail: err instanceof Error ? err.message : "unknown"
    });
  }
});

app.get("/api/leaderboard", (_req, res) => {
  res.json({ targetScore: TARGET_SCORE, maxPlausibleScore: 5000, entries: leaderboard.slice(0, 10) });
});

app.post("/api/score", (req, res) => {
  let ticket;
  try {
    ticket = verifyTicket(req.body?.rideTicket);
  } catch {
    res.status(400).json({ ok: false, error: "invalid ride ticket" });
    return;
  }

  const score = Number(req.body?.score);
  const nick = String(req.body?.nick || "anonymous").replace(/[^a-zA-Z0-9 _.-]/g, "").slice(0, 24) || "anonymous";
  if (!Number.isInteger(score) || score < 0) {
    res.status(400).json({ ok: false, error: "bad score" });
    return;
  }

  const claimedCap = Number(ticket.cap);
  if (!Number.isFinite(claimedCap) || score > claimedCap) {
    res.status(400).json({ ok: false, error: `score exceeds verified ride cap ${claimedCap}` });
    return;
  }

  const entry = {
    nick,
    score,
    symbol: String(ticket.symbol || "CUSTOM").slice(0, 12),
    at: new Date().toISOString()
  };
  leaderboard.push(entry);
  leaderboard.sort((a, b) => b.score - a.score);
  leaderboard.length = Math.min(leaderboard.length, 25);

  if (score >= TARGET_SCORE) {
    res.json({ ok: true, rank: leaderboard.findIndex((x) => x === entry) + 1, flag: FLAG });
    return;
  }
  res.json({ ok: true, rank: leaderboard.findIndex((x) => x === entry) + 1 });
});

app.use((_req, res) => {
  res.status(404).json({ error: "not found" });
});

createOpsServer();
app.listen(PORT, "0.0.0.0", () => {
  console.log(`SloppedRider listening on http://0.0.0.0:${PORT}/rider`);
});
