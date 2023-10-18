#include <vector>
#include "common.h"

class programSchedule {
private:
    short day, month;
    struct onOffTime {
        short onHr, offHr, onMin, offMin;
    };
    std::vector<onOffTime> schedule; // Vector to store onOffTime instances

public:
    // Constructor to initialize day and month
    programSchedule(short d, short m) : day(d), month(m) {}

    // Member function to add an onOffTime instance to the schedule
    void addOnOffTime(short onHr, short offHr, short onMin, short offMin) {
        onOffTime newTime{onHr, offHr, onMin, offMin};
        schedule.push_back(newTime);
    }

    // Member function to get the size of the schedule
    size_t getScheduleSize() {
        return schedule.size();
    }

    // Member function to access an onOffTime instance at a specific index
    onOffTime getOnOffTime(size_t index) {
        if (index >= 0 && index < schedule.size()) {
            return schedule[index];
        } else {
            debugln("Invalid index.");
            // You can return a default value or handle the error as needed
        }
    }
};


