#pragma once
#include <stdint.h>

#define LSB(X) X & 0xFF
#define MSB(X) X >> 8

#define TAU_RES_BUF_LEN 128

// TAU Success/Error codes
#define TAU_OK                          0x00
#define TAU_RANGE_ERROR                 0x03
#define TAU_CHECKSUM_ERROR              0x04
#define TAU_UNDEFINED_PROCESS_ERROR     0x05
#define TAU_UNDEFINED_FUNCTION_ERROR    0x06
#define TAU_TIMEOUT_ERROR               0x07
#define TAU_BYTE_COUNT_ERROR            0x09
#define TAU_FEATURE_NOT_ENABLED         0x0A

// Lib custom Error codes
#define TAU_RES_ERR_LEN                 0xF1
#define TAU_RES_ERR_INVALID             0xF1
#define TAU_RES_ERR_CRC                 0xF3
#define TAU_RES_ERR_UDEFINED            0xFF


class TauCamBase {
private:
    // properies
    void (*serialWriteByte)(uint8_t);
    void (*serialDelay)(uint32_t);
    uint8_t (*serialReadByte)();
    uint32_t (*serialAvailableBytes)();
    uint8_t buffer[TAU_RES_BUF_LEN];

    // methods
    uint16_t crc16(uint8_t *pBlock, uint16_t len);
    uint32_t available();
    uint32_t read();
    void write(const void *pBuf, uint32_t len);
protected:
    uint8_t sendCommand(uint8_t cmd, const void *pArgs = NULL, uint16_t argsLen = 0);
    uint8_t readResponse();
public:
    TauCamBase(
        void (*writeByte)(uint8_t),
        uint8_t (*readByte)() = NULL,
        uint32_t (*availableBytes)() = NULL,
        void (*delayMs)(uint32_t) = NULL
    );
};