#include <fcntl.h>
#include <mosquitto/libmosquitto.h>
#include <mosquitto/libmosquitto_callbacks.h>
#include <mosquitto/libmosquitto_connect.h>
#include <mosquitto/libmosquitto_create_delete.h>
#include <mosquitto/libmosquitto_loop.h>
#include <mosquitto/libmosquitto_subscribe.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include "../include/telemetry.h"
#include "../include/handler.h"

int telemetry_handler(const telemetry_t *in, alert_code alerts[], size_t cap);
int print_telemetry(const telemetry_t *data, alert_code alerts[], size_t count);

int telemetry_handler(const telemetry_t *in, alert_code alerts[], size_t cap) {
    //printf("Printing deviceid from handler: %s\n", in->device_id);
    size_t count = 0;
    if (in->temperature > 30 && count < cap) {
       alerts[count++] = HIGH_TEMPERATURE; 
    }
    if (in->humidity > 80 && count < cap) {
        alerts[count++] = HIGH_HUMIDITY;
    }
    if(in->battery < 20 && count < cap) {
        alerts[count++] = LOW_BATTERY;
    }

    print_telemetry(in, alerts, count);
    count = 0;
    return 0;
}

int print_telemetry(const telemetry_t *data, alert_code alerts[], size_t count) {
    printf("\033[2J\033[H");
    struct tm *tm = localtime(&data->timestamp);
    char buf[32];
    strftime(buf, sizeof buf, "%H:%M:%S", tm);
    printf("\r[%s], Device: %s\n",buf, data->device_id);
    printf("Temperature: %.1f C \n", data->temperature);
    printf("Humidity: %f%% \n", data->humidity);
    printf("Battery: %d%% \n", data->battery);
    for (int i = 0; i < count; i++) {
        printf("WARNING: %u\n", alerts[i]);
    }
    fflush(stdout);
    return 0;
}