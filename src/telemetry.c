#include <fcntl.h>
#include <mosquitto/libmosquitto.h>
#include <mosquitto/libmosquitto_callbacks.h>
#include <mosquitto/libmosquitto_connect.h>
#include <mosquitto/libmosquitto_create_delete.h>
#include <mosquitto/libmosquitto_loop.h>
#include <mosquitto/libmosquitto_subscribe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mosquitto.h>
#include <cjson/cJSON.h>
#include "../include/telemetry.h"

int telemetry_parse(const struct mosquitto_message *msg, telemetry_t *out);

int telemetry_parse(const struct mosquitto_message *msg, telemetry_t *out) {
    const char *payload = msg->payload;

    cJSON *root = cJSON_ParseWithLength(payload, (size_t)msg->payloadlen);
    if (root == NULL) {
        return -1;
    }

    cJSON *device_id = cJSON_GetObjectItemCaseSensitive(root, "device_id");
    cJSON *temperature = cJSON_GetObjectItemCaseSensitive(root, "temperature");
    cJSON *humidity = cJSON_GetObjectItemCaseSensitive(root, "humidity");
    cJSON *battery = cJSON_GetObjectItemCaseSensitive(root, "battery");
    cJSON *timestamp = cJSON_GetObjectItemCaseSensitive(root, "timestamp");

    if(cJSON_IsString(device_id) && cJSON_IsNumber(temperature) && 
    cJSON_IsNumber(humidity) && cJSON_IsNumber(battery) && cJSON_IsNumber(timestamp)) {
        strncpy(out->device_id, device_id -> valuestring, 32);
        out->temperature = temperature->valuedouble;
        out->humidity = humidity->valuedouble;
        out->battery = battery->valuedouble;
        out->timestamp = timestamp->valuedouble;
        //printf("Message parsed!\n");
    } else {
        perror("cjson");
        fprintf(stderr, "JSON is missing fields or has unexpected types\n");
        exit(-1);
    }

    cJSON_Delete(root);
    return 0;
}

