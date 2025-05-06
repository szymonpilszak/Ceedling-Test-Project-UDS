
#include "uds_services.h"
#include "config.h"
#include "lin_transport.h"

static const uint8_t mockData[2] = {0xDE, 0xAD};

Std_ReturnType Uds_Service_ReadDataByIdentifier(const uint8_t* request, uint8_t reqLen, uint8_t* response, uint8_t* respLen) 
{
    Std_ReturnType retVal = E_NOT_OK;
    
    if ((request == NULL) || (response == NULL) || (respLen == NULL))
    {
        retVal = E_NOT_OK;
    }

    if (reqLen != 3U) 
    {
        retVal = E_NOT_OK;
    }
    else 
    {
        uint16_t did = ((uint16_t)request[1] << 8U) | (uint16_t)request[2];

        if (did == 0x1234U) 
        {
            response[0] = 0x62U;
            response[1] = request[1];
            response[2] = request[2];
            response[3] = mockData[0];
            response[4] = mockData[1];
            *respLen = 5U;

            /* Send response via LIN */
            if (Lin_SendData(response, *respLen) != E_OK) 
            {
                retVal = E_NOT_OK;
            }
            else 
            {
                retVal = E_OK;
            }
        }
        else 
        {
            retVal = E_NOT_OK;
        }
    }

    return retVal;
}