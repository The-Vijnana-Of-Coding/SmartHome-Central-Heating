#include "common.h"
#include <algorithm> // Include for std::sort
#include <vector>

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
        // Validation Checking
        if(!(onHr >= 0 && onHr <= 23))
        {
            debugln("Error, check On Hour Time is valid");
        } else if (!(onMin >= 0 && onMin <= 59))
        {
            debugln("Error, check On Minute Time is valid");

        } else if (!(offHr >= 0 && offHr <= 23))
        {
            debugln("Error, check Off Hour Time is valid");

        } else if (!(offMin >= 0 && offMin <= 59))
        {
            debugln("Error, check Off Minute Time is valid");
        } else 
        {
            debugln("Time Valid");
            onOffTime newTime{onHr, offHr, onMin, offMin};
            schedule.push_back(newTime);
        }
    }

    // Member function to get the size of the schedule
    size_t getScheduleSize() {
        return schedule.size();
    }

    // Member function to access an onOffTime instance at a specific index
    onOffTime getOnOffTime(size_t index) {
        if (index >= 0 && index < schedule.size()) 
        {
            return schedule[index];
        } else {
            //debugln("Invalid index.");
            // You can return a default value or handle the error as needed
        }
    }

    // Member function to sort the schedule by onHr
    void sortScheduleByOnHr() {
        std::sort(schedule.begin(), schedule.end(), [](const onOffTime& a, const onOffTime& b) {
            return a.onHr < b.onHr;
        });
    }
};
