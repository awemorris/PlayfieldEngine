PicoPico Script Getting Started
===============================

Follow the steps below to run your first game.

## Download the Binary

Download the latest `PicoPico Script` binary from the [Releases Page](https://github.com/awemorris/PicoPicoScript/releases).

## Run the Game

Double-click the `picopico.exe` file to start the game.

## Edit the Game

Open the `main.noct` file.

## Export the Game

Select your game files on Explorer and drop them to the `picopico-pack.exe` file,
then the `assets.pak` file will be created.

Place the `assets.pak` file alongside the `picopico.exe` file.

---

## PicoPico Tutorial Game

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
