# Plant Tamagotchi

A physical plant companion that monitors soil moisture, light, and touch - and displays an animated character that reacts to how the plant is doing.

## Hardware

- **MCU:** ESP32-S3-DevKitC-1-N32R16V (32MB flash, 16MB OPI PSRAM)
- **Display:** Waveshare 1.69" Round Touch LCD (240×280, ST7789V2 + CST816T)
- **Soil moisture:** Aideepen capacitive sensor V1.2
- **Light:** LDR module (analog)
- **Power:** LiPo 3.7V 1200mAh + IP5306 charge/boost module

## Pinout

TBD - will be finalized during prototyping.

## Project Structure

```
plant-tamagotchi/
├── platformio.ini //define board (used for platformio)
├── README.md
├── .gitignore
├── src/
│   ├── main.cpp
│   └──image_arrays.cpp //contains pixel arrays for animation frames
├── include/
│   ├── pins.h //set pinout
│   └── image_arrays.h //declarations for the arrays (so main.cpp can reference them)
├── pictures/
├── docs/
└── test-sketches/
    ├──blink-ESP32-test.cpp //first test for ESP32, verified blink on board.
    ├──draw-tamagotchi-test.cpp //test to draw the tamagotchi to display based on info from soil sensor. three states.
    └──soil-moisture-sensor-test.cpp //test for the soil sensor

```

## Setup

### Prerequisites

- [VS Code](https://code.visualstudio.com/)
- [PlatformIO IDE](https://platformio.org/install/ide?install=vscode) extension for VS Code

### Getting started

1. Clone this repo
2. Open the project folder in VS Code(Need the PlatformIO extension) (`File → Open Folder`). NB: platformio.ini needs to be in root folder.
3. PlatformIO auto-downloads the ESP32-S3 platform and libraries on first build
4. Connect the ESP32 via USB
5. Click Upload (→) in the status bar to compile and flash

### Important notes

- **Don't put the project in OneDrive/Dropbox/Google Drive.** PlatformIO generates a large `.pio/` build folder that conflicts with cloud sync. Use a local path like `C:\Projects\`.
- **Reset hack:** Put the board in download mode: hold **BOOT**, press **RST**, release **BOOT**, then retry upload.
- **Erasing flash:** if the board gets stuck in a crash loop, erase with: `python "$HOME\.platformio\packages\tool-esptoolpy\esptool.py" --chip esp32s3 --port COM4 erase_flash`
- This project uses the [pioarduino](https://github.com/pioarduino/platform-espressif32) ESP32 platform (Arduino core 3.x) for proper OPI flash/PSRAM support. (Set in platformio.ini)
- The Serial Monitor: debug output at 115200 baud.

## Phases
- [x] Plan and buy components
- [x] Project setup with PlatformIO and VSCODE, blink test
- [ ] Component validation and configuration
- [ ] Character animations
- [ ] Sensor integration (connect and create firmware for entire system)
- [ ] Optimize and polish
- [ ] Enclosure
- [ ] Stretch goal: Integrate with Home Assistant (upload plant information)