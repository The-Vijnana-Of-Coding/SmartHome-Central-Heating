struct tempSensor {
    float temp;
    char name[16];
    char type[16];
};

struct tempSensor sensor = {0.0f, "sensor1", "temperature"};