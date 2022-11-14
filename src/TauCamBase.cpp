#include "TauCamBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TauCamBase::TauCamBase(
    void (*writeByte)(uint8_t),
    uint8_t (*readByte)(),
    uint32_t (*availableBytes)()
) {
    TauCamBase::serialWriteByte = writeByte;
    TauCamBase::serialReadByte = readByte;
    TauCamBase::serialAvailableBytes = availableBytes;
};

void TauCamBase::write(const void *pBuf, uint32_t len) {
    // print to stdout for dev
    printf("Send HEX\n");
    for (uint32_t i = 0; i < len; i++) {
        uint8_t byte = *((uint8_t*)pBuf+i);
        printf("0x%02X ", byte);
        TauCamBase::serialWriteByte(byte);
    }
    printf("\n\n");
}

// calc CRC16 checksum. Polynomial = 0x1021, Initial Value = 0x0
uint16_t TauCamBase::crc16(uint8_t *pBlock, uint16_t len) {
    uint16_t crc = 0x0;
    uint8_t i;
    while (len--) {
        crc ^= *pBlock++ << 8;
        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

// Build package structure and write to camera
void TauCamBase::sendCommand(uint8_t cmd, const void *pArgs = NULL, uint16_t argsLen = 0) {

    // allocate memory size = (header = 8b) + (arguments = Nb) + (CRC2 = 2b)
    uint16_t packLen = 8 + argsLen + (argsLen ? 2 : 0);
    uint8_t *pPack = (uint8_t*) calloc(packLen, 1);
    
    // build package 8b standert structure
    pPack[0] = 0x6E;                    // 0x6E on all valid incoming and reply  messages
    pPack[1] = 0x00;                    // status (not used on send)
    pPack[2] = 0x00;                    // not used
    pPack[3] = cmd;                     // call function code
    pPack[4] = MSB(argsLen);            // MSB arguments length
    pPack[5] = LSB(argsLen);            // LSB arguments length
    uint16_t crc1 = TauCamBase::crc16(pPack, 6);
    pPack[6] = MSB(crc1);               // MSB CRC1
    pPack[7] = LSB(crc1);               // LSB CRC1
    
    // add arguments bytes if exists
    if (argsLen != 0) {
        memcpy(pPack+8, pArgs, argsLen);         // copy arguments to package
        uint16_t crc2 = TauCamBase::crc16(pPack, packLen-2); // CRC cal all except last 2 bytes
        pPack[packLen-2] = MSB(crc2);            // MSB CRC2
        pPack[packLen-1] = LSB(crc2);            // LSB CRC2
    }

    // write package
    this->write(pPack, packLen);
    free(pPack);
};