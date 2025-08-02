# Development Journal — CLI Tetris

## Project Start
**Date:** July 2025  
**Objective:** Build a lightweight, terminal-based Tetris clone in C, just for fun and for Hack Club's Summer of Making.

## Environment
- OS: Windows 11
- Language: C
- IDE: CLion
- Compiler: GCC
- Input Handling: `kbhit()` + `getch()` (WinAPI)
- Display: 2D character buffer printed to terminal
- Threading: WinAPI threads for gravity loop

## Progress Log
- ✅ Created board buffer and basic render loop
- ✅ Implemented piece spawning and falling
- ✅ A/D movement with wall collision
- ✅ Rotation via E/Q keys
- ✅ Line clearing
- ✅ WinAPI thread-based drop loop
- 🟨 Random crash when rotating fast or during piece swap (unresolved)

## Current Status
> It started working on my machine out of nowhere.  
The crashing bug is still present under specific conditions, but behavior stabilized enough to stop blocking development. Project is temporarily frozen while I finish CS50x and Summer of Making.

## Next Steps
- [ ] Revisit threading model
- [ ] Investigate memory corruption / segfault on rotate
- [ ] Add proper game over screen
- [ ] Implement replay/high score system
- [ ] Port to Linux terminal