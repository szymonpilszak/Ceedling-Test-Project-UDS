#include "uds_services.h"
#include "config.h"

static const uint8_t mockData[2] = {0xDE, 0xAD};

Std_ReturnType Uds_Service_ReadDataByIdentifier(const uint8_t* request, uint8_t reqLen, uint8_t* response, uint8_t* respLen) {
    if (reqLen != 3) return E_NOT_OK;
    uint16_t did = (request[1] << 8) | request[2];

    if (did == 0x1234) {
        response[0] = 0x62;
        response[1] = request[1];
        response[2] = request[2];
        response[3] = mockData[0];
        response[4] = mockData[1];
        *respLen = 5;
        return E_OK;
    }

    return E_NOT_OK;
}