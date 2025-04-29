#include "lin_handler.h"
#include "uds_services.h"
#include "lin_transport.h"  


Std_ReturnType lin_handle_uds(const uint8_t* data, uint8_t len)
{
    Std_ReturnType result = E_NOT_OK;

    if ((data == NULL) || (len == 0U))
    {
        return E_NOT_OK;
    }

    switch (data[0])
    {
        case 0x22U: // ReadDataByIdentifier SID
        {
            uint8_t response[8] = {0};
            uint8_t respLen = 0;

            result = Uds_Service_ReadDataByIdentifier(data, len, response, &respLen);

            break;
        }

        default:
            LIN_send_negative_reponse(SERVICE_NOT_SUPPORTED);
            result = E_NOT_OK;
            break;
    }

    return result;
}