# XUL'S EMULATION PROJECT (MIEMU)
Personal 8 bit emulation proyect roadmap

### CC8 V1.0 (ALMOST DONE)
Chip 8 emulator

* Chip 8 emulator
    - Precise emulation (correct cpu timings)
    - Audio
    - Emulator shell
        - Emulation control (start, stop, reset)
        - File explorer 
    - Extended instruction set (super chip 48)

### XUL EMU V1.0 (TODO)
* Configuration manager
    - JSON (klib)

* Emulator manager shell (emulator selector)
    * Hotswappable emulators

* Shared library api (emulator shell and independent emulators)
    - MIEMU CORE [LIB]
        - Platforms
        - Emulation api
    - MIEMU CHIP 8  [LIB]
    - MIEMU GameBoy [LIB]
    - MIEMU UI [EXECUTABLE]
        - App entry point
* Emulators
    - Chip8   (CC8)
    - GameBoy (CGB)

### XUL EMU V1.2 (TODO)
* Platform support
    - LINUX
    - PSP
    - WINDOWS
    - STM32 with [uDisplay] (https://github.com/54UL/uDisplay)
        - NO AUDIO EMULATION ON THIS PLATFORM

### XUL EMU V1.4 (TODO)
* Shell enhanced UI system
    * UI Input
        - Key filtering
        - Mouse events
    * UI Layouts
        - rows
        - colums
        - grids
    * UI Widgets
        - text
        - line
        - rect
        - button
        - graph


### XUL EMU BACKLOG
* Emulators
    - NES (Nintendo Entertainment System)
    - SNES(Super Nintendo Entertainment System)
    - GBA
    - N64
    - Play station 1

### Resources:
- klib
http://attractivechaos.github.io/klib/#Generic%20Programming%20in%20C

- sdl 2 ttf
https://wiki.libsdl.org/SDL2_ttf

- glib (similar to klib)
https://en.wikipedia.org/wiki/GLib

- Game Boy: Complete Technical Reference
https://gekkio.fi/files/gb-docs/gbctr.pdf