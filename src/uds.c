#include "uds.h"
#include "uds_services.h"

Std_ReturnType Uds_ProcessRequest(const uint8_t* request, uint8_t reqLen, uint8_t* response, uint8_t* respLen) {

    uint8_t servResp;
    
    switch(request[0])
    {
        case 0x22:
            servResp = Uds_Service_ReadDataByIdentifier(request, reqLen, response, respLen);        
            break;
            
        default:
            servResp = E_NOT_OK;
    }

    return servResp;
}