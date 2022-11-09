#pragma once
#include <stdint.h>

class TauCamBase {
private:
    void read();
    void write(const void *pBuf, uint32_t len);
    uint16_t crc16(uint8_t *pcBlock, uint16_t len);
protected:
    void sendCommand(uint8_t cmd, const void *pArgs, uint16_t argsLen);
public:
    TauCamBase();
};