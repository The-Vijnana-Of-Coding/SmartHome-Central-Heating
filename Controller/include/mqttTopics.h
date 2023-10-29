#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

const char* sub_temp = "/esp32/temp";
const char* sub_override_set = "/esp32/controller/override/set";

const char* sub_topics[] = {
    sub_temp,
    sub_override_set
};

enum topics
{
    temp,
    override_set
};

const int num_sub_topics = sizeof(sub_topics) / sizeof(sub_topics[0]);

#endif