#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <time.h>
typedef struct {
    char device_id[32];
    double temperature;
    double humidity;
    int battery;
    time_t timestamp;
} telemetry_t;

int telemetry_parse(const struct mosquitto_message *msg, telemetry_t *out);

#endif