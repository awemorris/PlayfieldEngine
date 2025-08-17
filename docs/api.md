Noct2D Engine API
=================

Every API function takes one parameter. The parameter must be a dictionary and
arguments must be stored as key-and-value pairs.

## Skelton

```
func setup() {
    return {
        width:  1920,
        height: 1080,
        title:  "My Game"
    };
}

func start() {
    playerTex = Engine.loadTexture({
                    file: "player.png"
                });
}

func frame() {
    Engine.draw({
        texture: playerTex,
        x:       Engine.mousePosX,
        y:       Engine.mousePosY
    });
}
```

## Time

### Absolute Time

|Variable                    |Description                                |
|----------------------------|-------------------------------------------|
|Engine.millisec             |Time in millisec.                          |

```
func frame() {
    var dt = (Engine.millisec - lastTime) * 0.001;

    update(dt);
    render();
}
```

## Input

### Mouse Positions

These are variables, not functions.

|Variable                    |Description                                |
|----------------------------|-------------------------------------------|
|Engine.mousePosX            |Mouse position X.                          |
|Engine.mousePosY            |Mouse position Y.                          |
|Engine.isMouseLeftPressed   |Left mouse button state.                   |
|Engine.isMouseRightPressed  |Right mouse button state.                  |

```
func update() {
    if (Engine.isMouseLeftPressed) {
        player.x = player.x + 100;
    }
}
```

## Rendering

### Engine.loadTexture()

This API loads a texture from assets, and returns a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|file                |File name to load.                                            |

### Engine.destroyTexture()

This API destroys a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|tex                 |Texture.                                                      |

```
func loadPlayerTexture() {
    var tex = Engine.loadTexture({
                  file: "player.png"
              });
    return tex;
}
```

### Engine.renderTexture()

This API renders a texture to the screen.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|dstLeft             |Screen coordinate X.                                          |
|dstTop              |Screen coordinate Y.                                          |
|dstWidth            |Width in screen.                                              |
|dstHeight           |Height in screen.                                             |
|texture             |Texture ID.                                                   |
|srcLeft             |Texture top left X.                                           |
|srcTop              |Texture top left Y.                                           |
|srcWidth            |Texture rectangle width.                                      |
|srcHeight           |Texture rectangle height.                                     |
|alpha               |Alpha value (0-255)                                           |

```
func renderPlayer() {
    Engine.renderTexture({
        dstLeft:   playerPos.x,
        dstTop:    playerPos.y,
        dstWidth:  playerTex.width,
	dstHeight: playerTex.height,
        texture:   playerTex,
        srcLeft:   0,
        srcTop:    0,
        srcWidth:  playerTex.width,
        srcHeight: playerTex.height,
        alpha:     255
    });
}
```

### Engine.draw()

This API renders a texture to the screen, a simple version of `Engine.renderTexture()`.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|texture             |Texture ID.                                                   |
|x                   |Screen coordinate X.                                          |
|y                   |Screen coordinate Y.                                          |

```
func renderPlayer() {
    Engine.draw({
        texture: playerTex,
        x:       playerPos.x,
        y:       playerPos.y
    });
}
```

### Engine.loadFontSlot()

This API loads an asset font file to a specified font slot.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |Font slot index. (0-3)                                        |
|file                |File name to load.                                            |

### Engine.createTextTexture()

This API creates a texture and draws a text on it.
     	 	 
|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |Font slot index. (0-3)                                        |
|text                |Glyph code point.                                             |
|size                |Font size.                                                    |
|color               |Color, e.g. "#ff0000" for red.                                |

## Sound

### Engine.playSound()

This API starts playing a sound asset file on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |
|file                |File to play.                                                 |

### Engine.stopSound()

This API stops a sound playback on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |

### Engine.setSoundVolume()

This API sets a sound volume on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |
|volume              |Volume value. (0-1.0)                                         |
