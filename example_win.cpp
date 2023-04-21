#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include "TauCam.h"

/*
    "serialib.h"
    External simple serial lib to access COM port on Window
    Link: https://github.com/imabot2/serialib/tree/master/lib
*/
#include "serialib.h"


serialib serial;

// callback function
void write(uint8_t byte) {
    serial.writeChar((char) byte);
}
uint8_t read() {
    char byte = 0;
    serial.readChar(&byte, 1000);
    return byte;
}
uint32_t available() {
    return serial.available();
}
void delay(uint32_t ms) {
    Sleep(ms);
};

int main()
{
    // Init COM port
    uint8_t res = serial.openDevice("\\\\.\\COM13", 57600);
    if (res != 1) {
        printf("COM Connection error\n");
    } else {
        printf("COM Connection Ok\n");
    }

    // Init TauCam
    TauCam cam = TauCam(write, read, available, delay);

    // raw custom command
    cam.sendCommand(0x74);

    // vide standart test
    cam.setVideoStandart(TAU_VIDEO_NTSC_30);
    cam.setPalette(5);

    // draw test
    cam.drawRectangle(255, 255, 100, 100, TAU_COLOR_RED);
    cam.printText(text, 320, 256, TAU_COLOR_TRANSPRNT, TAU_COLOR_BLACK, TAU_FONT_ALIGN_CENTER, TAU_FONT_LARGE);
}