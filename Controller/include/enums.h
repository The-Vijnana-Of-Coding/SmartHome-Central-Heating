// Main menu layout
enum mainMenuLayout {
    home_screen,
    show_next_central_heating_on_off,
    show_next_hot_water_on_off,
    settings
};

// Settings menu Layout
enum settingsMenu {
    set_central_heating_routine,
    set_hot_water_routine,
    override_scheduled_season
};

// Routine menu layout for - set_central_heating_routine and set_hot_water_routine
enum routineMenu {
    set_num_of_on_off_times_for_day,
    set_num_of_days_to_repeat,
    set_schedule_season,
    set_on_time,
    set_off_time,
    confirm,
    add_next_routine
};

// Days of the weeks
enum daysOfWeek {
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

// Months of the year
enum monthOfYear {
    jan,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    otc,
    nov,
    dec
};

// Seasons
enum seasons {
    winter,
    spring,
    summer,
    autumn
};