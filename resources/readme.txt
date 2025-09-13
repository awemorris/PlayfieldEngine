==============================================================================
Playfield Engine
==============================================================================
Version      : 0.8.0
Date         : September 13th 2025
Author       : Awe Morris
Contact      : awe@noctvm.io
Requirements : Windows 10 or later
==============================================================================

About
-----

Playfield Engine is a lightweight game scripting runtime.  
With scripts written in Noct, it can render graphics and play sounds across
multiple platforms.

Whether you're a beginner or a seasoned power user, you can create games on
your PC — just like coding in classic BASIC, but with modern features.

Files
-----

  playfield.exe          ... Main Executable
  main.pf                ... Sample main script
  readme.txt             ... This document
  hajimeni.txt           ... README in Japanese
  documents-english/     ... Documents in English
  documents-japanese/    ... Documents in Japanese
  samples/               ... Sample games
  misc/
    windows/
      playfield-pack.exe ... Tool to create assets.pak
    macos/
      playfield.dmg      ... macOS app
      playfield-pack.exe ... Tool to create assets.pak on macOS
    wasm/
      index.html         ... WebAssembly entrypoint
      assets.pak         ... Testing package
      playfield-web.exe  ... Helper app for browser testing
      readme.txt         ... WebAssembly README
    ios/                 ... iOS Xcode project
    android/             ... Android Studio project
    unity/               ... Unity Native Plugin

Installation
------------

Just extract the ZIP file to any folder of your choice.
==============================================================================
Playfield Engine
==============================================================================
Version      : 0.8.0
Date         : September 13th 2025
Author       : Awe Morris
Contact      : awe@noctvm.io
Requirements : Windows 10 or later
==============================================================================

About
-----

Playfield Engine is a lightweight game scripting runtime.
With scripts written in Noct, it can render graphics and play sounds across
multiple platforms.

Whether you're a beginner or a seasoned power user, you can create games on
your PC — just like coding in classic BASIC, but with modern features.

Files
-----

  playfield.exe          ... Main Executable
  main.pf                ... Sample main script
  readme.txt             ... This document
  hajimeni.txt           ... README in Japanese
  documents-english/     ... Documents in English
  documents-japanese/    ... Documents in Japanese
  samples/               ... Sample games
  misc/
    windows/
      playfield-pack.exe ... Tool to create assets.pak
    macos/
      playfield.dmg      ... macOS app
      playfield-pack.exe ... Tool to create assets.pak on macOS
    wasm/
      index.html         ... WebAssembly entrypoint
      assets.pak         ... Testing package
      playfield-web.exe  ... Helper app for browser testing
      readme.txt         ... WebAssembly README
    ios/                 ... iOS Xcode project
    android/             ... Android Studio project
    unity/               ... Unity Native Plugin

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
