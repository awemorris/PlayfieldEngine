NoctVM Engine API
=================

Every API function takes one parameter. The parameter must be a dictionary and
arguments must be stored as key-and-value pairs.

## Input

### Mouse Positions

|Variable                 |Description                                |
|-------------------------|-------------------------------------------|
|API.mousePosX            |Mouse position X.                          |
|API.mousePosY            |Mouse position Y.                          |
|API.isMouseLeftPressed   |Left mouse button state.                   |
|API.isMouseRightPressed  |Right mouse button state.                  |

## Rendering

### API.loadTexture()

This API loads a texture from assets, and returns a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|file                |File name to load.                                            |

### API.removeTexture()

This API removes a texture.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|tex                 |Texture.                                                      |

### API.renderTexture()

This API renders a texture to the screen.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|dstLeft             |Screen coordinate X.                                          |
|dstTop              |Screen coordinate Y.                                          |
|dstWidth            |Width in screen.                                              |
|dstHeight           |Height in screen.                                             |
|texId               |Texture ID.                                                   |
|srcLeft             |Texture top left X.                                           |
|srcTop              |Texture top left Y.                                           |
|srcWidth            |Texture rectangle width.                                      |
|srcHeight           |Texture rectangle height.                                     |
|alpha               |Alpha value (0-255)                                           |

### API.loadFontSlot()

This API loads an asset font file to a specified font slot.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |Font slot index. (0-3)                                        |
|file                |File name to load.                                            |

### API.createTextTexture()

This API creates a texture and draws a text on it.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |Font slot index. (0-3)                                        |
|text                |Glyph code point.                                             |
|size                |Font size.                                                    |
|color               |Color, e.g. "#ff0000" for red.                                |

## Sound

### API.playSound()

This API starts playing a sound asset file on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |
|file                |File to play.                                                 |

### API.stopSound()

This API stops a sound playback on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |

### API.setVolume()

This API sets a sound volume on a specified sound track.

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |
|volume              |Volume value. (0-1.0)                                         |
