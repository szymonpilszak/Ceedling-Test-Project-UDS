#ifndef UDS_SERVICES_H
#define UDS_SERVICES_H

#include <stdint.h>
#include "config.h"

Std_ReturnType Uds_Service_ReadDataByIdentifier(const uint8_t* request, uint8_t reqLen, uint8_t* response, uint8_t* respLen);

#endif