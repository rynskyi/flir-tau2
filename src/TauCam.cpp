#include "TauCam.h"
#include <stdint.h>

#define TAU_CMD_PALETTE     0x10
#define TAU_CMD_ZOOM        0x0F
#define TAU_CMD_SPOTMETER   0x1F

// IMPORTANT: little endian to big endian converting in argument bytes

void TauCam::setPalette(uint8_t paletteNum) {
    // palette num in 0-29 range
    uint8_t args[2] = {0, paletteNum};
    TauCam::sendCommand(TAU_CMD_PALETTE, &args, sizeof(args));
};

void TauCam::setZoom(uint8_t zoomMode) {
    uint8_t args[2] = {0, zoomMode};
    TauCam::sendCommand(TAU_CMD_ZOOM, &args, sizeof(args));
}

void TauCam::setSpotMeter(uint8_t mode) {
    uint8_t args[2] = {0, mode};
    TauCam::sendCommand(TAU_CMD_SPOTMETER, &args, sizeof(args));
}