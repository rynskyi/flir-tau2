#include "TauCam.h"
#include <stdint.h>

#define TAU_CMD_PALETTE         0x10

void TauCam::setPalette(uint8_t paletteNum) {
    // palette num in 0-29 range
    // 2 bytes big endian to little endian converting 
    uint8_t args[2] = {0, paletteNum};
    TauCam::sendCommand(TAU_CMD_PALETTE, &args, sizeof(args));
};