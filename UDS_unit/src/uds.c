#include "uds.h"
#include "uds_services.h"

Std_ReturnType Uds_ProcessRequest(const uint8_t* request, uint8_t reqLen, uint8_t* response, uint8_t* respLen) {
    if (request[0] == 0x22) {
        return Uds_Service_ReadDataByIdentifier(request, reqLen, response, respLen);
    }

    return E_NOT_OK;
}