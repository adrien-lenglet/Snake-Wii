# Snake-Wii
3D snake for Nintendo Wii™

![Game screenshot](https://i.imgur.com/t9aIhRO.png)

## Build instructions

You need the devkitPPC toolchain in order to compile this game.

* https://devkitpro.org/wiki/Getting_Started (install the `wii-dev` package)
* Just `make` to build.
* The output is `Snake-Wii.elf`.

A compiled binary is available here: https://mega.nz/#!aQxhTYQb!5WgawMqrOa3-Rj-HbCC09aJtyKz22SXXOqJ2G5KY7jE (30/05/2018)

## How to run

### On a Wii

You need the Homebrew Channel to run this software. Just place the .elf binary inside a folder of your choice in the `apps` folder. Rename the .elf binary `boot.elf`. Launch the Homebrew Channel, the application should appear.

### On Dolphin

Just open `Snake-Wii.elf` with the emulator !

## How to play

A GameCube controller is required.

Under Dolphin, this can be configured out of any existing controller.

On a Wii, plug the controller in the first port.

### Controls

* Use DPAD to rotate your snake in 3D space.
* Press START to quit the game.
