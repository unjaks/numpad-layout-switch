# Numpad Emulator for Keyboards Without Numpad  

**Description**  
A C++ Windows utility that simulates numpad input when **Caps Lock is ON**, allowing standard number keys to function as numpad keys.

## Features  
- Converts `0-9`, `.`, `+`, `-`, `*`, `/`, and `Enter` to numpad equivalents  
- Toggle with Caps Lock (only active when Caps Lock is ON)  
- Runs in background  

## How It Works  
- Uses a low-level keyboard hook (`WH_KEYBOARD_LL`)  
- Maps standard keys to numpad virtual key codes  
- Blocks original keypresses when Caps Lock is active  

## Build & Run  
1. Compile with a C++ compiler (e.g., Visual Studio, MinGW)  
2. Run the executable (admin rights may be required)  

## Usage  
1. Turn **Caps Lock ON** → Number keys act as numpad  
2. Turn **Caps Lock OFF** → Normal keyboard behavior  

## Notes  
- Requires Windows  
- Keep the program running for functionality  
