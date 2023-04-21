# Library provide few control operation for **Flir Tau 2** thermal camera via UART port

*Cross platform, tested on: Windows, Arduino*

## Initialization

First you have to declare callback function to read(), write(), available() according to your platformfi and serail library

```cpp
    #include "TauCam.h"

    void write(uint8_t byte) {
        // SomeSerialLib.write(byte);
    }
    uint8_t read() {
        // return SomeSerialLib.read();
    }
    uint32_t available() {
        // return SomeSerialLib.available();
    }

    void delay(uint32_t ms) {
        // sleep(ms); // some sleep() call depends on your platform
    };

    // then init main class and pass wrapper functions
    TauCam cam = TauCam(write, read, available, delay);

```

## Method list

```cpp
    TauCam cam = TauCam(write, read, available, delay); // read the section above

    // cam setup methods
    cam.setPalette(...)
    cam.setZoom(...)
    cam.setSpotMeter(...)
    cam.setOrientation(...)
    cam.setVideoStandart(...)

    // OSD drawing methods
    cam.printText(...)
    cam.drawRectangle(...)
    cam.sendCommand(...)

    // send raw custom command
    cam.sendCommand(...)
```