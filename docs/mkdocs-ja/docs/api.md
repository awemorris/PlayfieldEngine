Playfield VM の API
===================

すべての API 関数は 1 つのパラメータを取ります。
そのパラメータは辞書でなければならず、引数はキーと値のペアとして格納されます。

## 骨組み

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

## 時間

### 絶対的な時間

|変数                        |説明                                       |
|----------------------------|-------------------------------------------|
|Engine.millisec             |起動からの時間（ミリ秒）                   |

```
func frame() {
    var dt = (Engine.millisec - lastTime) * 0.001;

    update(dt);
    render();
}
```

### Engine.getDate()

日付を表す辞書を返します。

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

## 入力

### マウス状態

これらは変数であり、関数ではありません。

|変数                        |説明                                       |
|----------------------------|-------------------------------------------|
|Engine.mousePosX            |マウスX座標                                |
|Engine.mousePosY            |マウスY座標                                |
|Engine.isMouseLeftPressed   |左マウスボタン                             |
|Engine.isMouseRightPressed  |右マウスボタン                             |

```
func update() {
    if (Engine.isMouseLeftPressed) {
        player.x = player.x + 100;
    }
}
```

## レンダリング

### Engine.createColorTexture()

この API は指定された色のテクスチャを作成して返します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|width               |テクスチャの幅                                                |
|height              |テクスチャの高さ                                              |
|r                   |色の R 値 (0-255)                                             |
|g                   |色の G 値 (0-255)                                             |
|b                   |色の B 値 (0-255)                                             |
|a                   |アルファ値 (0-255)                                            |

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

この API はアセットからテクスチャをロードし、テクスチャを返します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|file                |ロードするファイルの名前                                      |

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

この API はテクスチャを破棄します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|texture             |テクスチャ                                                    |

```
func destroyPlayerTexture() {
    Engine.loadTexture({
        texture: playerTex
    });
}
```

### Engine.renderTexture()

この API はテクスチャをスクリーンに描画します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|dstLeft             |スクリーン X 座標                                             |
|dstTop              |スクリーン Y 座標                                             |
|dstWidth            |スクリーンでの幅                                              |
|dstHeight           |スクリーンでの高さ                                            |
|texture             |テクスチャ                                                    |
|srcLeft             |テクスチャの左上 X 座標                                       |
|srcTop              |テクスチャの左上 Y 座標                                       |
|srcWidth            |テクスチャ矩形の幅                                            |
|srcHeight           |テキスチャ矩形の高さ                                          |
|alpha               |アルファ値 (0-255)                                            |

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

この API はテキスチャをスクリーンに描画します。
`Engine.renderTexture()` のシンプル版です。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|texture             |テクスチャ                                                    |
|x                   |スクリーン X 座標                                             |
|y                   |スクリーン Y 座標                                             |

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

この API はテクスチャを 3D 変形してスクリーンに描画します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|x1                  |スクリーン座標 X1                                             |
|y1                  |スクリーン座標 Y1                                             |
|x2                  |スクリーン座標 X2                                             |
|y2                  |スクリーン座標 Y2                                             |
|x3                  |スクリーン座標 X3                                             |
|y3                  |スクリーン座標 Y3                                             |
|x4                  |スクリーン座標 X4                                             |
|y4                  |スクリーン座標 Y4                                             |
|texture             |テクスチャ                                                    |
|srcLeft             |テクスチャ左上 X 座標                                         |
|srcTop              |テクスチャ左上 Y 座標                                         |
|srcWidth            |テクスチャ矩形の幅                                            |
|srcHeight           |テクスチャ矩形の高さ                                          |
|alpha               |アルファ値 (0-255)                                            |

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

この API はフォントファイルをフォントスロットにロードします。

|Argument Name       |Description                                                   |
|--------------------|--------------------------------------------------------------|
|slot                |フォントスロット番号 (0-3)                                    |
|file                |ロードするファイルの名前                                      |

```
func loadNotoSansFont() {
    Engine.loadFont({ slot: 0, file: "NotoSans.ttf" });
}
```

### Engine.createTextTexture()

この API はテキストを描画したテクスチャを描画します。
     	 	 
|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|slot                |フォントスロット番号 (0-3)                                    |
|text                |描画するテキスト                                              |
|size                |フォントサイズ                                                |
|r                   |色の R 値 (0-255)                                             |
|g                   |色の G 値 (0-255)                                             |
|b                   |色の B 値 (0-255)                                             |
|a                   |アルファ値 (0-255)                                            |

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

## サウンド

### Engine.playSound()

この API はサウンドをサウンドトラック上で再生します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|stream              |トラック番号 (0-3)                                            |
|file                |再生するファイルの名前                                        |

```
func playJumpSound() {
    Engine.playSound({ stream: 0, file: "jump.ogg" });
}
```

### Engine.stopSound()

この API はサウンドトラック上のサウンド再生を停止します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|stream              |Track index. (0-3)                                            |

```
func playJumpSound() {
    Engine.stopSound({ stream: 0 });
}
```

### Engine.setSoundVolume()

この API はサウンドトラックのボリュームを設定します。

|引数名              |説明                                                          |
|--------------------|--------------------------------------------------------------|
|stream              |トラック番号 (0-3, -1 ならマスター)                           |
|volume              |ボリューム値 (0-1.0)                                          |

```
func playJumpSound() {
    Engine.setSoundVolume({
        stream: 0,
        volume: 1.0
    });
}
```
