# Snake-Wii
3D snake for Nintendo Wii™

![Game screenshot](https://i.imgur.com/t9aIhRO.png)

## Background [added context from Adrien LENGLET, 31st of August, 2023]

This is mostly a playground homebrew I wrote, based off the game engine my colleagues & I wrote in college at the time https://github.com/Sangliers-Feroces/Vega-Engine  
The renderer was rewritten of course, as the Dolphin architecture uses a fixed pipeline so modern OpenGL couldn't be ported as is.  
Other than that, this is a 3D snake with the same texture for everything. It was fun learning about Dolphin programming in couple of days! I would like to get back to homebrew programming and work on state-of-the art renderers someday.

## Build instructions [as was published on 31st of May, 2019]

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
