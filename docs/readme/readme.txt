==============================================================================
Playfield Engine
==============================================================================
Version      : 0.8.1
Date         : September 17th 2025
Author       : Awe Morris
Contact      : awe@noctvm.io
Requirements : Windows 10 or later
==============================================================================

 * Load this file into ChatGPT.
 * Try entering: "Create a game in Playfield Script."

About
-----

Playfield Engine is a lightweight game scripting runtime.  With scripts
written in Playfield Script, it can render graphics and play sounds across
multiple platforms.

Whether you're a beginner or a seasoned power user, you can create games on
your PC — just like coding in classic BASIC, but with modern features.

Files
-----

  playfield.exe           ... Main executable
  main.pf                 ... Sample main script
  readme.txt              ... This document
  hajimeni.txt            ... README in Japanese
  misc/
    samples/              ... Sample games
    windows/
      playfield-arm64.exe ... Arm64 executable
      playfield-pack.exe  ... Tool to create assets.pak
    macos/
      playfield.dmg       ... macOS app
      playfield-pack.exe  ... Tool to create assets.pak on macOS
    wasm/
      index.html          ... WebAssembly entrypoint
      assets.pak          ... Testing package
      playfield-web.exe   ... Helper app for browser testing
      readme.txt          ... WebAssembly README
    ios/                  ... iOS Xcode project
    android/              ... Android Studio project
    unity/                ... Unity Native Plugin
    documents-english/    ... Documents in English
    documents-japanese/   ... Documents in Japanese

Installation
------------

Just extract the ZIP file to any folder of your choice.

Usage (Windows)
---------------

Double-click "playfield.exe".
If a "main.pf" file exists in the same folder, it will run automatically.

You can also bundle your assets (scripts, images, sounds, fonts, etc.) into a
single package file.  Select the files and drag & drop them onto
"playfield-pack.exe" — this will generate an "aassets.pa" file.

Usage (macOS)
-------------

Open "playfield.dmg" and copy the "Playfield.app" to any folder.  Place the
app in the same folder as "main.pf" or "assets.pak", then double-click the
app to run it.

Usage (Wasm)
------------

Upload the generated "assets.pak" and "index.html" to a web server.
To preview the game locally, use "playfield-web.exe".

Usage (iOS)
-----------

Place "assets.pak" in the "Resources/" folder, then open the project in Xcode.

Usage (Android)
---------------

First, copy all assets into "app/src/main/assets".

  A. Easy Way

    - Copy the "android" folder to a short path, such as "D:\"
    - Double-click "build.bat"
    - When prompted with "(y/N)", type "y" and press Enter
    - "app-debug.apk" will be generated
    - Install the APK on your Android device

  B. Recommended Way

    - Open the "android" folder with Android Studio
    - Build the project
    - Run the app on your device

Usage (Unity)
-------------

Copy all assets into the "StreamingAssets" folder,  
then open the project in the Unity Editor.

License
-------

This software is distributed under the MIT license.

Playfield Engine
© 2025 Awe Morris

Contact
-------

Email: Awe Morris <awe@noctvm.io>
Project Page: https://github.com/awemorris/PlayfieldEngine

I'd love to hear from you!
Feel free to reach out.

==============================================================================

Playfield Script Syntax
=======================

`Playfield Engine` uses `Noct` as a scripting language.

## Assignments

Variables in Noct are dynamically typed and don't require explicit
declaration. The assignment operator (`=`) is used to create and
assign values to variables.

As shown in the example below, Noct supports various data types
including integers, floating-point numbers, and strings. Variables can
be reassigned to different types at any time during execution.

```
func main() {
    var a = 123;
    print(a);

    var b = 1.0;
    print(b);

    var c = "string";
    print(c);
}
```

## Global Variables

Global variables can be defined in functions, and cannot be defined
outside functions.

```
func main() {
    globalVariable = 123;
    print(globalVariable);
}
```

## Local Variables

Using the `var` keyword allows you to declare a variable as
local. Without `var` declaration, assigning to a variable may create a
global variable.

```
func main() {
    var a = 123;
    print(a);
}
```

## Array

Arrays are ordered collections of values, accessed by index. Arrays
support iteration through the `for` loop construct, allowing you to
iterate through each value directly.

```
func main() {
    var array = [0, 1, 2];
    for (value in array) {
        print(value);
    }
}
```

Arrays can hold values of different types simultaneously, reflecting
the dynamic typing system.

```
func main() {
    var array = [123, "string"];
}
```

The language provides a built-in function `push()` to add elements to
the end of an array.  Also, `pop()` removes the final element.

```
func main() {
    var array = []
    array->push(0);
    array->push(1);
    array->push(2);

    var last = array->pop();

    print("Length = " + array.length);
}
```

## Dictionary

Dictionaries store key-value pairs, similar to hash maps or objects in
other languages. They are defined using curly braces with key-value
pairs separated by colons. Dictionaries support iteration where both
the key and value can be accessed simultaneously.

```
func main() {
    var dict = {key1: "value1", key2: "value2"};
    for (key, value in dict) {
        print("key = " + key);
        print("value = " + value);
    }

    print("Length = " + dict.length);
}
```

Dictionaries may be constructed in a single step way. An assignment
can be an array style which uses `[]`, or an object style which uses
`.`.

```
func main() {
    var dict = {};
    dict["key1"] = "value1";
    dict.key2 = "value2";
}
```

The built-in function `remove()` allows for the deletion of entries by
key.

```
func main() {
    var dict = {key1: "value1", key2: "value2"};
    remove(dict, "key1");
}
```

## For-loop

The for-loop construct provides a concise syntax for iterating through
sequences such as ranges, arrays, and dictionaries.

The range syntax (using the `..` operator) creates an iterator that
generates values from the start to one less than the end value.

```
func main() {
    for (i in 0..10) {
        print(i);
    }
}
```

For-loops can also iterate directly over arrays and other collection
types.

Arrays can be iterated by the for-value syntax.

```
func main() {
    array = [0, 1, 2];
    for (value in array) {
        print(value);
    }
}
```

Dictionaries can be iterated by the for-key-value syntax.

```
func main() {
    var dict = {key1: "value1", key2: "value2"};
    for (key, value in dict) {
        print(key + "=" + value);
    }
}
```

## While Loops

The while-loop provides a traditional iteration mechanism that
continues execution as long as a specified condition remains
true. Unlike for-loops which are designed for iterating over
collections, while-loops are more flexible and can be used for
implementing various algorithms where the number of iterations isn't
known in advance. The example shows a basic counter implementation
incrementing from 0 to 9.

```
func main() {
    var i = 0;
    while (i < 10) {
        print(i);
        i = i + 1;
    }
}
```

## If and Else Blocks

Control flows allow for conditional executions based on evaluated
expressions. The if-else construct follows a familiar syntax where
conditions are evaluated in sequence.

```
func main() {
    var a = readint();
    if (a == 0) {
        print("0");
    } else if (a == 1) {
        print("1");
    } else {
        print("other");
    }
}
```

## Lambda Functions

Functions are first-class objects in the language. Anonymous
functions, also known as `lambda` expressions, allow you to create
functions without names.

```
func main() {
    var f = (a, b) => { return a + b; }
    print(f(1, 2));
}
```

Lambda functions are simply translated to named functions in the
compilation process. Therefore, they can't capture variables declared
in outer functions.

## Increment/Decrement (+=, -=, ++, --)

```
func main() {
    var a = 123;
    a += 321;
    a++;

    var b = 123;
    b -= 321;
    b--;
}
```

`++` and `--` are supported only as standalone statements (`a++;`, `b--;`).
Using them inside expressions is disallowed to avoid complex side-effects.

## OOP in Noct

The object-oriented model in Noct is a lightweight variation of prototype-based OOP.

- Classes are simply dictionary templates
- Inheritance and instantiation are realized by dictionary merging
- There is no prototype chain, and modifying a class does not affect existing instances

This design treats dictionaries as first-class objects, and the author refers to it as Dictionary-based OOP (D-OOP).

```
func main() {
    // The base class definition. (A class is just a dictionary.)
    Animal = class {
        name: "Animal",
        cry: (this) => {
        }
    };

    // The subclass definition. (Just a dictionary merging.)
    Cat = extend Animal {
        name: "Cat",
        voice: "meow",
        cry: (this) => {
            print(this.name + " cries like " + this.voice);
        }
    };

    // Instantiation. (Just a dictionary merging.)
    var myCat = new Cat {
        voice: "neee"
    };

    // This-call uses -> () syntax. (Equal to myCat.cry(myCat))
    myCat->cry();
}
```

## Intrinsics

### int()

```
var i = int(1.23);
```

### float()

```
var f = float(123);
```

### newArray()

```
var array = newArray(10);
```

### push()

```
var array = [1, 2, 3];
array->push(4);
```

### pop()

```
var array = [1, 2, 3];
var last = array->pop();
```

### resize()

```
var array = [1, 2, 3];
array->resize(2);
```

### substring()

```
var s1 = "ABCDEFG";
var s2 = s1.substring(1, -1); // from the char 1, to the end "BCDEFG"
}
```

### charAt()

```
var s = "ABC";
for (i in 0 .. s.length) {
   var c = s->charAt(i);
   print(c);
}
```

### sin(), cos(), tan()

```
var s = sin(x);
var c = cos(x);
var t = tan(x);
```

### random()

```
var r = random(); // 0 .. 1.0
```

### fast_gc(), full_gc(), compact_gc()

```
// Do young GC.
fast_gc();

// Do young + old GC.
full_gc();

// Do young + old + compact GC.
compact_gc();
```

### unset()

```
var dic = {key1: "ABC"};
dic->unset("key1");
```

==============================================================================

Playfield Script API
====================

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

|Variable                        |Description                                |
|--------------------------------|-------------------------------------------|
|Engine.mousePosX                |Mouse position X.                          |
|Engine.mousePosY                |Mouse position Y.                          |
|Engine.isMouseLeftPressed       |Left mouse button state.                   |
|Engine.isMouseRightPressed      |Right mouse button state.                  |
|Engine.isKeyUpPressed           |Up key state.                              |
|Engine.isKeyDownPressed         |Down key state.                            |
|Engine.isKeyLeftPressed         |Left key state.                            |
|Engine.isKeyRightPressed        |Right key state.                           |
|Engine.isKeyReturnPressed       |Return key state.                          |
|Engine.isControllerUpPressed    |Game pad up arrow state.                   |
|Engine.isControllerDownPressed  |Game pad down arrow state.                 |
|Engine.isControllerLeftPressed  |Game pad left arrow state.                 |
|Engine.isControllerRightPressed |Game pad right arrow state.                |
|Engine.isController1Pressed     |Game pad button 1 state.                   |
|Engine.isController2Pressed     |Game pad button 2 state.                   |
|Engine.isController3Pressed     |Game pad button 3 state.                   |
|Engine.isController4Pressed     |Game pad button 4 state.                   |
|Engine.isController5Pressed     |Game pad button 5 state.                   |
|Engine.isController6Pressed     |Game pad button 6 state.                   |
|Engine.isController7Pressed     |Game pad button 7 state.                   |
|Engine.isController8Pressed     |Game pad button 8 state.                   |

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
