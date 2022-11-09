#include "TauCamBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LSB(X) X & 0xFF
#define MSB(X) X >> 8

TauCamBase::TauCamBase() {
    //
}

void TauCamBase::write(const void *pBuf, uint32_t len) {
    // print to stdout for dev
    for (uint32_t i = 0; i < len; i++) {
        printf("0x%02X ", *((uint8_t*)pBuf+i));
    }
    printf("\n");
}

// calc CRC16 checksum. Polynomial = 0x1021, Initial Value = 0x0
uint16_t TauCamBase::crc16(uint8_t *pcBlock, uint16_t len) {
    uint16_t crc = 0x0;
    uint8_t i;
    while (len--) {
        crc ^= *pcBlock++ << 8;
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
};