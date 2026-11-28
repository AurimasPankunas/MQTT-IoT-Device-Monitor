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
#include "../include/handler.h"

#define MAX_ALERTS 3

void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
int mqtt_client();

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    //printf("ID: %d\n", * (int *) obj);
    if (rc != 0) {
        printf("Error with result code: %d\n", rc);
        exit(-1);
    }
    mosquitto_subscribe(mosq, NULL, "iot/devices/+/telemetry", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
    telemetry_t local;
    //printf("Parsing message\n");
    telemetry_parse(msg, &local);
    alert_code alerts[MAX_ALERTS];
    telemetry_handler(&local, alerts, MAX_ALERTS);
}

int mqtt_client() {
    int rc, id = 12;
    mosquitto_lib_init();
    struct mosquitto *mosq;

    mosq = mosquitto_new("client", true, &id);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, "localhost", 1883, 10);

    if (rc != 0) {
        printf("Client could not connect to broker! Error Code : %d\n", rc);
        mosquitto_destroy(mosq);
        return -1;
    }
    mosquitto_loop_start(mosq);
    printf("We are now connected to the broker!\n");
    printf("Press Enter to quit...\n");
    getchar();
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}

