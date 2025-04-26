#ifndef UDS_H
#define UDS_H

#include <stdint.h>
#include "config.h"

Std_ReturnType Uds_ProcessRequest(const uint8_t* request, uint8_t reqLen, uint8_t* response, uint8_t* respLen);

#endif