#include <fcntl.h>
#include <mosquitto/libmosquitto.h>
#include <mosquitto/libmosquitto_callbacks.h>
#include <mosquitto/libmosquitto_connect.h>
#include <mosquitto/libmosquitto_create_delete.h>
#include <mosquitto/libmosquitto_loop.h>
#include <mosquitto/libmosquitto_subscribe.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include "../include/telemetry.h"

int telemetry_handler(telemetry_t *in);

int telemetry_handler(telemetry_t *in) {
    printf("Printing deviceid from handler: %s\n", in->device_id);
    
    return 0;
}