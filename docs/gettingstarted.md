Getting Started
===============

NoctVM is designed to be simple and easy to use from the command line.
Follow the steps below to create and run your first game.

## 1. Download the Binary

Download the latest NoctVM binary from the [Releases Page](https://github.com/awemorris/noctvm/releases).

## 2. Add NoctVM to Your PATH

To use the `noct` command globally, add its directory to your environment's PATH.

### Example (Linux):

```
export PATH=$PATH:/path/to/noctvm/bin:/path/to/noctvm/bin/linux-x86_64
```

### Example (Windows):

Add the path (`\path\to\noctvm\bin`) to your system environment variables.

## 3. Create a New Game Folder

Run the following command to create a new game project folder:

```
noct create mygame
cd mygame
```

## 4. Copy Sample Files

NoctVM comes with sample files to help you get started.
Copy the contents of the sample folder into your new game directory:

```
cp -R /path/to/noctvm/sample/* .
```

## 5. Run the Game

Start the development runtime and run the game:

```
noct run
```

If a game window appears, everything is working correctly.

Instead of calling the `noct run` command, you can run the `noctvm` command.

```
noctvm
```

## 6. Export the Game

You can export your game using this command:

```
noct export windows dest-win
```

The exported files for Windows will be placed in the `dest-win` folder.
Other platforms are also supported in a similar way.
(Run `noct export` to show target platforms.)

With just a few simple commands, you can go from a blank folder to a running and exported game.
For more details, please see the [documentation.](index.md)

---

## NoctVM Tutorial Game

We are looking for a small, fun example game that demonstrates what
NoctVM can do.  This could be a side-scrolling shooter, a puzzle game,
or anything that shows off NoctScript and the engine API.

If you're interested in contributing, open an issue or drop a message
in the community.
