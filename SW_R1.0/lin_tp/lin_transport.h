#ifndef LIN_TRANSPORT_H
#define LIN_TRANSPORT_H

#include <stdint.h>
#include "config.h"

Std_ReturnType Lin_SendData(const uint8_t* data, uint8_t length);
Std_ReturnType LIN_send_negative_reponse (const uint8_t respCode);

#endif