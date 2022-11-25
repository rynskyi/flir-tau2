#pragma once
#include "TauCamBase.h"

#define TAU_ZOOM_1X         0b00000
#define TAU_ZOOM_2X         0b00100
#define TAU_ZOOM_4X         0b01000
#define TAU_ZOOM_8X         0b10000

#define TAU_SPOTMETER_OFF       0
#define TAU_SPOTMETER_ON_F      1
#define TAU_SPOTMETER_ON_C      2

#define TAU_VIDEO_NTSC_30       0x00
#define TAU_VIDEO_PAL_25        0x01
#define TAU_VIDEO_NTSC_60       0x04
#define TAU_VIDEO_PAL_50        0x05

#define TAU_ORIENT_NORMAL           0
#define TAU_ORIENT_INVERT           1
#define TAU_ORIENT_REVERT           2
#define TAU_ORIENT_INVERT_REVERT    3

#define TAU_COLOR_YELLOW        251 // 243
#define TAU_COLOR_WHITE         255
#define TAU_COLOR_PINK          253
#define TAU_COLOR_BLUE          252 // 244, 246
#define TAU_COLOR_GREEN         250 // 242
#define TAU_COLOR_RED           249 // 241
#define TAU_COLOR_DARK_RED      241
#define TAU_COLOR_GREY          248 // 247
#define TAU_COLOR_PURPLE        245
#define TAU_COLOR_BLACK         240
#define TAU_COLOR_ORANGE        239
#define TAU_COLOR_BROWN         238
#define TAU_COLOR_TRANSPRNT     0

#define TAU_FONT_SMALL      0
#define TAU_FONT_MIDDLE     1
#define TAU_FONT_LARGE      2

#define TAU_FONT_ALIGN_CENTER  0x0000
#define TAU_FONT_ALIGN_LEFT    0x0100
#define TAU_FONT_ALIGN_RIGHT   0x8000


class TauCam : TauCamBase {

using TauCamBase::TauCamBase;

public:
    void setPalette(uint8_t paletteNum);
    void setZoom(uint8_t zoomMode);
    void setSpotMeter(uint8_t mode);
    void setOrientation(uint8_t orientMode);
    void setVideoStandart(uint8_t standart);
    void drawSymbol();
    
    void printText(
        const char *text, 
        uint16_t posX,
        uint16_t posY,
        uint8_t colorBgrnd = 0x00,
        uint8_t colorFrgrnd = 0x01, 
        uint16_t aligment = 1,
        uint16_t font = 1
    );
    
    void drawRectangle(
        uint16_t posX,
        uint16_t posY,
        uint16_t width,
        uint16_t height,
        uint8_t color = 0x01
    );
};
