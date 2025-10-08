クイックスタート
================

下記のステップに従って、最初のゲームを実行してください。

## Playfield の取得

**ダウンロード**

* 最新の **All-in-One** の ZIP を Playfield の [ウェブサイト](https://noctvm.io/playfield/) からダウンロードしてください
* ZIP ファイルをお好きなフォルダに展開します

**Windows の場合:**

* `playfield.exe` をダウンロードしてください
* サンプルゲームが自動的に開始します

**macOS の場合:**

* `misc/macos/Playfield.dmg` を開きます
* 中に入っている `Playfield` アプリを、`playfield.exe` と同じフォルダにコピーします
* `Playfield` アプリをダブルクリックして、ゲームを実行します

**Linux の場合:**

* `misc/linux/Playfield-x86_64.AppImage` を `playfield.exe` と同じフォルダにコピーします
* 必要であれば、AppImage ファイルを実行可能にします (`chmod +x Playfield-x86_64.AppImage`)
* AppImage をダブルクリックして、ゲームを実行します

## 最初のゲームの作成

最小のゲームを作るには:

1. お好きなフォルダを作成します
2. お好きなテキストエディタをそのフォルダで開きます
3. `main.pf` というファイルを作成します
4. 下記の内容をそのファイルにペーストして保存します

```
// ウィンドウ作成時に呼ばれます
func setup() {
    // ウィンドウの設定を返します
    return {
        width: 1280,
        height: 720,
        title: My First Game
    };
}

// ゲーム開始時に一度だけ呼ばれます
func start() {
    // 100x100 の白いテクスチャを作成します
    tex = Engine.createColorTexture({
        width: 100,
        height: 100,
        r: 255, g: 255, b: 255, a: 255
    });
}

// 毎フレーム、レンダリングの前に呼ばれます
func update() {
    posX = Engine.mousePosX;
    posY = Engine.mousePosY;
}

// 毎フレーム、レンダリングのために呼ばれます
func render() {
    Engine.draw({ texture: tex, x: posX, y: posY });
}
```

## ゲームの実行

Playfield は下記の２通りの方法でゲームをロードできます:

* `main.pf` ファイルを含むフォルダ
* `assets.arc` ファイル (すべてのゲームアセットが入っている)

`assets.arc` ファイルを作成するには、[ゲームの配布](distribute.md) を見てください。
