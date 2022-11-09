#pragma once
#include "TauCamBase.h"

#define TAU_ZOOM_1X         0b00000
#define TAU_ZOOM_2X         0b00100
#define TAU_ZOOM_4X         0b01000
#define TAU_ZOOM_8X         0b10000

#define TAU_SPOTMETER_OFF       0
#define TAU_SPOTMETER_ON_F      1
#define TAU_SPOTMETER_ON_C      2

class TauCam : TauCamBase {
public:
    void setPalette(uint8_t paletteNum);
    void setZoom(uint8_t zoomMode);
    void setSpotMeter(uint8_t mode);
};