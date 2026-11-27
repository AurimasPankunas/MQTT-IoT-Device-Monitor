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
#include "../include/mqtt_client.h"

int main( int argc, char * argv[] ) {
    //Start the mqtt client
    mqtt_client();
    
    return 0;
}