const state = {
  chart: null,
  ticket: null,
  score: 0,
  cap: 0,
  terrain: [],
  game: null,
  animation: 0,
  keys: new Set()
};

const el = (id) => document.getElementById(id);

function fmt(n) {
  return Number(n).toLocaleString("en-US");
}

async function api(path, options) {
  const res = await fetch(path, options);
  const text = await res.text();
  let data;
  try {
    data = JSON.parse(text);
  } catch {
    data = { error: text };
  }
  if (!res.ok) {
    throw new Error(data.error || data.detail || "request failed");
  }
  return data;
}

function decodeTicket(ticket) {
  const payload = ticket.split(".")[0];
  return JSON.parse(atob(payload.replace(/-/g, "+").replace(/_/g, "/")));
}

function buildTerrain(chart) {
  const canvas = el("track");
  const w = canvas.width;
  const h = canvas.height;
  const points = chart.dataPoints || chart.prices.map((close, i) => ({ date: String(i + 1), close }));
  const closes = points.map((p) => p.close);
  const min = Math.min(...closes);
  const max = Math.max(...closes);
  const range = max - min || 1;
  const worldWidth = Math.max(2200, points.length * 95);
  const terrain = points.map((point, i) => {
    const x = 80 + (i / (points.length - 1)) * worldWidth;
    const normalized = (point.close - min) / range;
    const y = h - 44 - normalized * 210;
    return { x, y, date: point.date, close: point.close };
  });
  terrain.unshift({ x: 0, y: terrain[0].y, date: points[0].date, close: points[0].close });
  terrain.push({ x: worldWidth + 120, y: terrain[terrain.length - 1].y, date: points[points.length - 1].date, close: points[points.length - 1].close });
  return terrain;
}

function terrainY(x) {
  const terrain = state.terrain;
  if (!terrain.length) return 280;
  for (let i = 1; i < terrain.length; i += 1) {
    const a = terrain[i - 1];
    const b = terrain[i];
    if (x <= b.x) {
      const t = Math.max(0, Math.min(1, (x - a.x) / (b.x - a.x || 1)));
      return a.y + (b.y - a.y) * t;
    }
  }
  return terrain[terrain.length - 1].y;
}

function drawTrack(chart, game = null) {
  const canvas = el("track");
  const ctx = canvas.getContext("2d");
  const w = canvas.width;
  const h = canvas.height;
  const terrain = state.terrain;
  const cameraX = game ? Math.max(0, game.x - w * 0.34) : 0;

  ctx.clearRect(0, 0, w, h);
  ctx.fillStyle = "#0b0c0f";
  ctx.fillRect(0, 0, w, h);

  ctx.strokeStyle = "#202632";
  ctx.lineWidth = 1;
  for (let y = 40; y < h; y += 52) {
    ctx.beginPath();
    ctx.moveTo(0, y);
    ctx.lineTo(w, y);
    ctx.stroke();
  }

  ctx.beginPath();
  terrain.forEach((p, i) => {
    const x = p.x - cameraX;
    if (i === 0) ctx.moveTo(x, p.y);
    else ctx.lineTo(x, p.y);
  });
  const first = chart.prices[0];
  const last = chart.prices[chart.prices.length - 1];
  ctx.strokeStyle = last >= first ? "#5dcaa5" : "#e85d58";
  ctx.lineWidth = 4;
  ctx.stroke();

  ctx.lineTo(terrain[terrain.length - 1].x - cameraX, h);
  ctx.lineTo(0, h);
  ctx.closePath();
  ctx.fillStyle = "rgba(93, 202, 165, 0.06)";
  ctx.fill();

  if (game) {
    drawBike(ctx, game, cameraX);
    drawHud(ctx, game);
  }

  ctx.fillStyle = "#f5f7fb";
  ctx.font = "700 18px ui-monospace, monospace";
  ctx.fillText(`${chart.symbol} / ${chart.period.toUpperCase()}`, 24, 34);
}

function drawBike(ctx, game, cameraX) {
  const x = game.x - cameraX;
  const y = game.y;
  const angle = game.angle;
  const ca = Math.cos(angle);
  const sa = Math.sin(angle);
  const rear = { x: x - ca * 24, y: y - sa * 24 };
  const front = { x: x + ca * 28, y: y + sa * 28 };
  ctx.save();
  ctx.lineCap = "round";
  ctx.lineJoin = "round";
  ctx.strokeStyle = "#111";
  ctx.lineWidth = 6;
  for (const wheel of [rear, front]) {
    ctx.beginPath();
    ctx.arc(wheel.x, wheel.y, 15, 0, Math.PI * 2);
    ctx.stroke();
  }
  ctx.strokeStyle = game.crashed ? "#e85d58" : "#5dcaa5";
  ctx.lineWidth = 5;
  ctx.beginPath();
  ctx.moveTo(rear.x, rear.y);
  ctx.lineTo(x, y - 24);
  ctx.lineTo(front.x, front.y);
  ctx.lineTo(x + ca * 4, y + sa * 4);
  ctx.lineTo(rear.x, rear.y);
  ctx.stroke();
  ctx.strokeStyle = "#ef9f27";
  ctx.lineWidth = 4;
  ctx.beginPath();
  ctx.moveTo(x, y - 24);
  ctx.lineTo(x - sa * 10, y - 44);
  ctx.lineTo(x + ca * 18 - sa * 8, y - 49 + sa * 18);
  ctx.stroke();
  if (game.throttle > 0 && !game.crashed) {
    ctx.fillStyle = "rgba(239,159,39,0.65)";
    ctx.beginPath();
    ctx.arc(rear.x - ca * 18, rear.y - sa * 18, 6 + Math.random() * 4, 0, Math.PI * 2);
    ctx.fill();
  }
  ctx.restore();
}

function drawHud(ctx, game) {
  ctx.fillStyle = "rgba(16,17,20,0.78)";
  ctx.fillRect(16, 52, 210, 82);
  ctx.fillStyle = "#8b929c";
  ctx.font = "13px ui-monospace, monospace";
  ctx.fillText(`score ${fmt(currentScore(game))}`, 28, 76);
  ctx.fillText(`flips ${game.flips}`, 28, 98);
  ctx.fillText(`spin bonus ${fmt(game.spinBonus)}`, 28, 120);
  if (game.finished) {
    ctx.fillStyle = "#5dcaa5";
    ctx.font = "700 24px ui-monospace, monospace";
    ctx.fillText("FINISHED", 450, 68);
  } else if (game.crashed) {
    ctx.fillStyle = "#e85d58";
    ctx.font = "700 24px ui-monospace, monospace";
    ctx.fillText("CRASH", 472, 68);
  }
}

function localRideScore(chart) {
  let energy = 0;
  let flips = 0;
  let crashes = 0;
  for (let i = 1; i < chart.prices.length; i += 1) {
    const prev = chart.prices[i - 1];
    const cur = chart.prices[i];
    const pct = Math.abs(cur - prev) / Math.max(prev, 1);
    energy += Math.min(0.22, pct) * 800;
    if (pct > 0.14) flips += 1;
    if (pct > 0.32) crashes += 1;
  }
  const raw = Math.round(1800 + energy + flips * 140 - crashes * 220);
  return Math.max(400, Math.min(5000, raw));
}

function currentScore(game) {
  const segmentLength = Math.max(1, game.finishX - game.scoreStartX);
  const progress = Math.max(0, Math.min(1, (game.x - game.scoreStartX) / segmentLength));
  const distance = Math.round(progress * 2800);
  const style = game.spinBonus + Math.floor(game.airTime * 45);
  return Math.max(0, Math.min(5000, distance + style + game.bonus));
}

function resetScoreAfterCrash(game) {
  game.scoreStartX = game.x;
  game.flips = 0;
  game.airTime = 0;
  game.bonus = 0;
  game.spinBonus = 0;
  game.lastFlipBucket = Math.trunc(game.angle / (Math.PI * 2));
  game.jumpQueued = false;
  game.scoreReset = true;
}

function startGame() {
  if (!state.chart) return;
  cancelAnimationFrame(state.animation);
  const startY = terrainY(90) - 28;
  state.game = {
    x: 90,
    y: startY,
    vx: 0,
    vy: 0,
    angle: -0.1,
    spin: 0,
    throttle: 0,
    grounded: true,
    crashed: false,
    finished: false,
    flips: 0,
    crashes: 0,
    airTime: 0,
    bonus: 0,
    spinBonus: 0,
    scoreStartX: 90,
    lastFlipBucket: 0,
    jumpQueued: false,
    scoreReset: false,
    finishX: state.terrain[state.terrain.length - 1].x - 130,
    lastTime: performance.now()
  };
  el("submit-score").disabled = true;
  stepGame(state.game.lastTime);
}

function stepGame(now) {
  const game = state.game;
  if (!game) return;
  const dt = Math.min(0.032, (now - game.lastTime) / 1000 || 0.016);
  game.lastTime = now;
  updateGame(game, dt);
  drawTrack(state.chart, game);
  const resetText = game.scoreReset ? " · crash reset" : "";
  el("ride-stats").innerHTML = `Score <span class="ok">${fmt(currentScore(game))}</span> · speed ${Math.round(game.vx * 10)} · flips ${game.flips} · spin bonus ${fmt(game.spinBonus)}${resetText} · cap ${fmt(state.cap)}`;
  if (!game.finished) {
    state.animation = requestAnimationFrame(stepGame);
  }
}

function updateGame(game, dt) {
  const throttle = state.keys.has("w") || state.keys.has("arrowup");
  const brake = state.keys.has("s") || state.keys.has("arrowdown");
  const leanLeft = state.keys.has("a") || state.keys.has("arrowleft");
  const leanRight = state.keys.has("d") || state.keys.has("arrowright");
  const jump = state.keys.has(" ");
  game.throttle = throttle ? 1 : 0;

  if (!game.crashed) {
    if (throttle) game.vx += 95 * dt;
    if (brake) game.vx -= 135 * dt;
    game.vx = Math.max(-20, Math.min(280, game.vx));
    game.vy += 420 * dt;
    const rotatePower = game.grounded ? 3.2 : 7.6;
    if (leanLeft) game.spin -= rotatePower * dt;
    if (leanRight) game.spin += rotatePower * dt;
    if (jump && game.grounded) {
      game.vy = -230;
      game.grounded = false;
      game.y -= 4;
      game.jumpQueued = true;
      game.bonus += 25;
    }
  } else {
    game.vx *= 0.985;
    game.vy += 520 * dt;
  }

  game.x += game.vx * dt;
  game.y += game.vy * dt;
  game.angle += game.spin * dt;
  const ground = terrainY(game.x);

  if (game.y >= ground - 24) {
      if (!game.grounded && !game.crashed) {
      const upright = Math.abs(Math.sin(game.angle));
      if (upright > 0.82 || Math.abs(game.vy) > 520) {
        game.crashed = true;
        game.crashes += 1;
        resetScoreAfterCrash(game);
        game.vx *= 0.35;
        game.spin *= 0.3;
      } else {
        game.bonus += Math.floor(game.airTime * 90);
      }
      game.airTime = 0;
    }
    game.grounded = true;
    game.y = ground - 24;
    game.vy = Math.min(0, game.vy) * -0.1;
    const slope = Math.atan2(terrainY(game.x + 8) - terrainY(game.x - 8), 16);
    game.angle += (slope - game.angle) * Math.min(1, dt * 8);
    game.spin *= 0.8;
    game.vx += Math.sin(-slope) * 55 * dt;
    if (game.crashed && Math.abs(game.vx) < 6) {
      game.crashed = false;
      game.y = ground - 30;
      game.angle = slope;
      game.spin = 0;
      game.vx = 18;
    }
  } else {
    game.grounded = false;
    game.airTime += dt;
    const flipBucket = Math.trunc(game.angle / (Math.PI * 2));
    if (flipBucket !== game.lastFlipBucket) {
      game.flips += 1;
      const fullSpinBonus = game.jumpQueued ? 520 : 360;
      game.spinBonus += fullSpinBonus;
      game.bonus += 80;
      game.lastFlipBucket = flipBucket;
      game.jumpQueued = false;
    }
  }

  if (game.x >= game.finishX) {
    game.finished = true;
    state.score = currentScore(game);
    el("submit-score").disabled = false;
    drawTrack(state.chart, game);
  }
}

async function loadTickers() {
  const tickers = await api("/api/tickers");
  const select = el("ticker-select");
  select.innerHTML = tickers
    .map((t) => `<option value="${t.symbol}">${t.symbol} - ${t.name}</option>`)
    .join("");
  el("daily-symbol").textContent = `${tickers[1].symbol} · ${tickers[1].difficulty.toUpperCase()}`;
  await loadChart(tickers[1].symbol);
}

async function loadChart(symbol) {
  const data = await api(`/api/chart/${encodeURIComponent(symbol)}`);
  setTrack(data.chart, data.rideTicket);
}

function setTrack(chart, ticket) {
  cancelAnimationFrame(state.animation);
  state.chart = chart;
  state.ticket = ticket;
  state.cap = decodeTicket(ticket).cap;
  state.score = 0;
  state.game = null;
  state.terrain = buildTerrain(chart);
  el("track-title").textContent = `${chart.symbol} - ${chart.name}`;
  el("cap-pill").textContent = `verified cap ${fmt(state.cap)}`;
  el("ride-stats").textContent = "Ready to ride.";
  el("submit-score").disabled = true;
  drawTrack(chart);
}

async function refreshBoard() {
  const data = await api("/api/leaderboard");
  el("board").innerHTML = data.entries
    .map(
      (e, i) => `<div class="row">
        <div>#${i + 1}</div>
        <div>${e.nick}</div>
        <div class="score">${fmt(e.score)}</div>
        <div class="symbol">${e.symbol}</div>
      </div>`
    )
    .join("");
}

el("ticker-form").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  try {
    await loadChart(el("ticker-select").value);
  } catch (err) {
    el("ride-stats").innerHTML = `<span class="bad">${err.message}</span>`;
  }
});

el("ride-daily").addEventListener("click", () => {
  startGame();
  el("track-panel").scrollIntoView({ behavior: "smooth" });
});

el("simulate").addEventListener("click", () => {
  startGame();
});

el("submit-score").addEventListener("click", async () => {
  if (!state.ticket) return;
  try {
    const score = state.score || (state.game ? currentScore(state.game) : localRideScore(state.chart));
    const data = await api("/api/score", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        nick: el("nick").value || "anonymous",
        score,
        rideTicket: state.ticket
      })
    });
    el("ride-stats").innerHTML = data.flag
      ? `<span class="ok">${data.flag}</span>`
      : `<span class="ok">Submitted at rank #${data.rank}</span>`;
    await refreshBoard();
  } catch (err) {
    el("ride-stats").innerHTML = `<span class="bad">${err.message}</span>`;
  }
});

el("preview-form").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  try {
    const data = await api("/api/chart/preview", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ url: el("preview-url").value })
    });
    setTrack(data.chart, data.rideTicket);
    el("ride-stats").innerHTML = `<span class="ok">Preview loaded from donor feed.</span>`;
  } catch (err) {
    el("ride-stats").innerHTML = `<span class="bad">${err.message}</span>`;
  }
});

loadTickers().catch((err) => {
  el("daily-symbol").textContent = "offline";
  el("ride-stats").innerHTML = `<span class="bad">${err.message}</span>`;
});
refreshBoard();

window.addEventListener("keydown", (ev) => {
  state.keys.add(ev.key.toLowerCase());
  if (["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight", " "].includes(ev.key)) {
    ev.preventDefault();
  }
});

window.addEventListener("keyup", (ev) => {
  state.keys.delete(ev.key.toLowerCase());
});
