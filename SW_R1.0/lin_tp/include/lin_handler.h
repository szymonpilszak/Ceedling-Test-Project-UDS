#ifndef LIN_HANDLER_H
#define LIN_HANDLER_H

#include <stdint.h>
#include "Std_Types.h"

Std_ReturnType lin_handle_uds(const uint8_t* data, uint8_t len);

#endif /* LIN_HANDLER_H */