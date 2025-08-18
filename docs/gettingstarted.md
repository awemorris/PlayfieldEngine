Noc2D Getting Started
=====================

Follow the steps below to run your first game.

## Download the Binary

Download the latest Noct2D binary from the [Releases Page](https://github.com/awemorris/Noct2D/releases).

## Run the Game

Double-click the `noct2d.exe` file to start the game.

## Edit the Game

Open the `main.noct` file.

## Export the Game

Select your game files on Explorer and drop them to the `noct2dpack.exe` file,
then the `product.img` file will be created.

Place the `product.img` file alongside the `noct2d.exe` file.

---

## Noct2D Tutorial Game

### Bouncer

This is the simplest sample. See the `samples/bouncer` folder in the SDK.

```
//
// ==== bouncer ====
//

func setup() {
    return {
        width: 800,
        height: 450,
        title: "Bouncer"
    };
}

func start() {
    W = 800;
    H = 450;
    BLOCK_W = 48;      // pixels
    BLOCK_H = 48;      // pixels
    SPEED_X = 180.0;   // pixels/sec
    SPEED_Y = 140.0;   // pixels/sec
    MAX_DT  = 0.1;     // sec

    // Create a texture.
    tex = Engine.createColorTexture({
        width: BLOCK_W,
        height: BLOCK_H,
        r: 0,
        g: 128,
        b: 255,
        a: 255
    });

    // Set the initial block position.
    x = (W - BLOCK_W) * 0.5;
    y = (H - BLOCK_H) * 0.5;

    // Set the initial speed.
    vx = SPEED_X;
    vy = SPEED_Y;

    last_ms = Engine.millisec;
}

func frame() {
    var now_ms = Engine.millisec;
    var dt = (now_ms - last_ms) * 0.001;
    last_ms = now_ms;

    // Process the input.
    if (Engine.isMouseLeftPressed) {
        x = (W - BLOCK_W) * 0.5;
        y = (H - BLOCK_H) * 0.5;
    }

    // Update the position
    x = x + vx * dt;
    y = y + vy * dt;

    // Reflect.
    if (x < 0) {
        // Left to right.
        x = -x;
        vx = -vx;
    } else if (x > W - BLOCK_W) {
        // Right to left.
        x = 2*(W - BLOCK_W) - x;
        vx = -vx;
    }
    if (y < 0) {
        // Up to down.
        y = -y;
        vy = -vy;
    } else if (y > H - BLOCK_H) {
        // Down to up.
        y = 2*(H - BLOCK_H) - y;
        vy = -vy;
    }

    // Draw.
    Engine.draw({
        texture: tex,
        x: x,
        y: y
    });
}
```

### DON'T RUSH IN COMIKET

This is a simple sample game. See the `samples/rush` folder in the SDK.

```
//
// DON'T RUSH IN COMIKET
//

func setup() {
    screenW = 640;
    screenH = 320;
    return {
        width:  screenW,
        height: screenH,
        title:  "DON'T RUSH IN COMIKET"
    };
}

func start() {
    // Constants.
    true = 1;
    false = 0;
    null = 0;

    // baseline for the ground
    groundY = screenH - 20;

    // Globals
    playerTex = null;
    obTex = null;
    fontReady = false;
    scoreTex = null;
    msgTex = null;

    player = {
        x: 60,
        y: 0,
        w: 48,
        h: 48,
        vy: 0,
        onGround: true
    };

    obstacles = [];

    // Tuning
    gravity = 2000.0;
    jumpVel = -700.0;
    scrollSpeed = 380.0;
    spawnInterval = 1.10; // seconds
    spawnTimer = 0.0;

    score = 0;
    lastTime = 0;
    gameOver = false;

    // Load the textures.
    playerTex = Engine.loadTexture({
        file: "player.png"
    });
    obTex = Engine.loadTexture({
        file: "obstacle.png"
    });
    floorTex = Engine.createColorTexture({
        width: 1, height: 1,
        r: 255, g: 255, b: 0, a: 255
    });

    // Load the font.
    Engine.loadFont({
        slot: 0,
        file: "PixelifySans-VariableFont_wght.ttf"
    });
    fontReady = true;

    // Place player on ground
    player.y = groundY - player.h;
    lastTime = Engine.millisec;

    updateScoreTex();
}

func frame() {
    var now = Engine.millisec;
    var dt = (now - lastTime) * 0.001;
    if (dt > 0.05) { dt = 0.05; } // clamp to avoid huge steps
    lastTime = now;

    update(dt);
    render();
}

func resetGame() {
    obstacles = [];
    player.x = 120;
    player.y = groundY - player.h;
    player.vy = 0;
    player.onGround = true;
    score = 0;
    spawnTimer = 0.0;
    gameOver = false;
    updateScoreTex();
    if (msgTex != null) {
        Engine.destroyTexture({ texture: msgTex });
        msgTex = 0;
    }
}

func update(dt) {
    if (gameOver) {
        if (Engine.isMouseLeftPressed) {
            resetGame();
        }
        return 1;
    }

    // Input: jump on mouse/tap
    if (Engine.isMouseLeftPressed && player.onGround) {
        player.vy = jumpVel;
        player.onGround = false;

        Engine.playSound({ stream: 0, file: "jump.ogg" });
    }

    // Physics
    player.vy = player.vy + gravity * dt;
    player.y  = player.y + player.vy * dt;

    // Ground clamp
    var floorY = groundY - player.h;
    if (player.y >= floorY) {
        player.y = floorY;
        player.vy = 0;
        player.onGround = true;
    }

    // Spawn obstacles
    spawnTimer = spawnTimer + dt;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = spawnTimer - spawnInterval;
        spawnObstacle();
    }

    // Move & prune obstacles, scoring & collisions
    var newObs = [];
    for (ob in obstacles) {
        ob.x = ob.x - scrollSpeed * dt;

        // score when fully passed player
        if (!ob.counted && (ob.x + ob.w) < player.x) {
            ob.counted = true;
            score = score + 1;
            updateScoreTex();
        }

        // AABB collision
        if (rectOverlap(player.x, player.y, player.w, player.h,
                        ob.x, ob.y, ob.w, ob.h)) {
            onGameOver();
        }

        // keep if on screen
        if ((ob.x + ob.w) >= -64) {
            newObs->push(ob);
        }
    }
    obstacles = newObs;
}

func onGameOver() {
    if (gameOver) {
        return 1;
    }

    gameOver = true;

    if (fontReady) {
        msgTex = Engine.createTextTexture({
            slot: 0,
            text: "GAME OVER - click to retry",
            size: 32,
            r: 255,
            g: 64,
            b: 64,
            a: 255
        });
    }
}

func spawnObstacle() {
    // Simple single-block obstacle near ground
    var w = 49;
    var h = 70;  // jump over this
    var x = screenW + 20;
    var y = groundY - h;
    obstacles->push({
        x: x,
        y: y,
        w: w,
        h: h,
        counted: false
    });
}

func render() {
    // Draw ground as a long rectangle
    drawRect(0, groundY, screenW, 8, floorTex);

    // Draw obstacles
    for (ob in obstacles) {
        Engine.draw({
            texture: obTex,
            x: ob.x,
            y: ob.y
        });
    }

    // Draw player
    Engine.draw({
        texture: playerTex,
        x:       player.x,
        y:       player.y
    });

    if (fontReady) {
        if (scoreTex != null) {
            Engine.draw({ texture: scoreTex, x: 12, y: 10 });
        }
        if (gameOver && msgTex != null) {
            Engine.draw({ texture: msgTex, x: (screenW - msgTex.width) / 2, y: 120 });
        }
    }
}

func drawRect(x, y, w, h, tex) {
    Engine.renderTexture({
        dstLeft:   x,
        dstTop:    y,
        dstWidth:  w,
        dstHeight: h,
        texture:   tex,
        srcLeft:   0,
        srcTop:    0,
        srcWidth:  tex.width,
        srcHeight: tex.height,
        alpha:     255
    });
}

func rectOverlap(ax, ay, aw, ah, bx, by, bw, bh) {
    var aRight = ax + aw;
    var bRight = bx + bw;
    var aBottom = ay + ah;
    var bBottom = by + bh;

    if (aRight <= bx) {
        return false;
    }
    if (bRight <= ax) {
        return false;
    }
    if (aBottom <= by) {
        return false;
    }
    if (bBottom <= ay) {
        return false;
    }

    return true;
}

func updateScoreTex() {
    if (!fontReady) {
        return 0;
    }

    if (scoreTex != null) {
        Engine.destroyTexture({
            texture: scoreTex
        });
    }

    scoreTex = Engine.createTextTexture({
        slot: 0,
        text: "Score: " + score,
        size: 28,
        r: 255,
        g: 255,
        b: 255,
        a: 255
    });
}
```
