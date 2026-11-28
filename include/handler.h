#include "telemetry.h"
#ifndef HANDLER_H
typedef enum {
    HIGH_TEMPERATURE,
    HIGH_HUMIDITY,
    LOW_BATTERY
} alert_code;

int telemetry_handler(const telemetry_t *in, alert_code alerts[], size_t cap);

#endif