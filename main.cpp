#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <windows.h>
#include "TauCam.h"

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


    TauCam cam = TauCam(write, read, available, delay);

    // uint8_t args[2] = {0, 3};
    // cam.sendCommand(0x74, args, sizeof(args));
    cam.sendCommand(0x74);


    // for (uint8_t i = 0x00; i < 0xFF; i++) {
    //     uint8_t args[2] = {i, 0};
    //     uint8_t res = cam.sendCommand(0x75, args, sizeof(args));
    //     printf("res: 0x%02X, req: 0x%02X\n", res, i);
    //     Sleep(2000);
    // }
    

    // for (uint32_t i = 104; i < 125; i++) {
    //     uint8_t res = cam.sendCommand(i, NULL, 0);
    //     printf("req: 0x%02X, res: 0x%02X \n", i, res);
    // }
    

    // vide standart test
    // cam.setVideoStandart(TAU_VIDEO_NTSC_30);
    // cam.setPalette(5);
    // draw test
    // cam.drawRectangle(255, 255, 100, 100, TAU_COLOR_RED);
    // cam.printText(text, 320, 256, TAU_COLOR_TRANSPRNT, TAU_COLOR_BLACK, TAU_FONT_ALIGN_CENTER, TAU_FONT_LARGE);
    
}