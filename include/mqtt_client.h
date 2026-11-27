#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H


void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
int mqtt_client();
#endif