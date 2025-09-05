PicoPicoScript API
===================

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

### Engine.getDate()

Returns a date dictionary.

```
func frame() {
    var date = Engine.getDate({});

    var year  = date.year;
    var month = date.month;
    var day   = date.day;
    var hour  = date.hour;
    var min   = date.minute;
    var sec   = date.second;
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

### Engine.createColorTexture()

This API creates a texture with the specified color, and returns a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|width               |Texture width.                                                |
|height              |Texture height.                                               |
|r                   |Red color.                                                    |
|g                   |Green color.                                                  |
|b                   |Blue color.                                                   |
|a                   |Alpha color.                                                  |

```
func createBlockTexture() {
    blockTex = Engine.createColorTexture({
                   width:  16,
                   height: 16,
                   r:      255,
                   g:      255,
                   b:      255,
                   a:      255
               });
}
```

### Engine.loadTexture()

This API loads a texture from assets, and returns a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|file                |File name to load.                                            |

```
func loadPlayerTexture() {
   playerTex = Engine.loadTexture({
                   file: "player.png"
               });

   var width = playerTex.width;
   var height = playerTex.height;
}
```

### Engine.destroyTexture()

This API destroys a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|texture             |Texture.                                                      |

```
func destroyPlayerTexture() {
    Engine.loadTexture({
        texture: playerTex
    });
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
|texture             |Texture.                                                      |
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
|texture             |Texture.                                                      |
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

### Engine.renderTexture3D()

This API renders a texture to the screen.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|x1                  |Screen coordinate X1.                                         |
|y1                  |Screen coordinate Y1.                                         |
|x2                  |Screen coordinate X2.                                         |
|y2                  |Screen coordinate Y2.                                         |
|x3                  |Screen coordinate X3.                                         |
|y3                  |Screen coordinate Y3.                                         |
|x4                  |Screen coordinate X4.                                         |
|y4                  |Screen coordinate Y4.                                         |
|texture             |Texture.                                                      |
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

### Engine.loadFont()

This API loads an asset font file to a specified font slot.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |Font slot index. (0-3)                                        |
|file                |File name to load.                                            |

```
func loadNotoSansFont() {
    Engine.loadFont({ slot: 0, file: "NotoSans.ttf" });
}
```

### Engine.createTextTexture()

This API creates a texture and draws a text on it.
     	 	 
|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |Font slot index. (0-3)                                        |
|text                |Text to draw.                                                 |
|size                |Font size.                                                    |
|r                   |Red color.                                                    |
|g                   |Green color.                                                  |
|b                   |Blue color.                                                   |
|a                   |Alpha color.                                                  |

```
func createScoreTexture() {
    scoreTex = Engine.createTextTexture({
                   slot: 0,
                   text: "Score: " + score,
                   size: 32,
                   r:    255,
                   g:    255,
                   b:    255,
                   a:    255
               });
}
```

## Sound

### Engine.playSound()

This API starts playing a sound asset file on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |
|file                |File to play.                                                 |

```
func playJumpSound() {
    Engine.playSound({ stream: 0, file: "jump.ogg" });
}
```

### Engine.stopSound()

This API stops a sound playback on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |

```
func playJumpSound() {
    Engine.stopSound({ stream: 0 });
}
```

### Engine.setSoundVolume()

This API sets a sound volume on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3, -1 for master)                             |
|volume              |Volume value. (0-1.0)                                         |

```
func playJumpSound() {
    Engine.setSoundVolume({
        stream: 0,
        volume: 1.0
    });
}
```
