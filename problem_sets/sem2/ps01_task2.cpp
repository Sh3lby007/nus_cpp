#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

/******************************************
Part A. Date Related Functions
******************************************/
struct Date {
    int year;
    int month;
    int day;
};

void make_date(Date& newDate, int year, int month, int day) {
    newDate.year = year;
    newDate.month = month;
    newDate.day = day;
}

int compare_date(Date& dateA, Date& dateB) {
    if (dateA.year != dateB.year) {
        return (dateA.year < dateB.year) ? -1 : 1;
    }
    if (dateA.month != dateB.month) {
        return (dateA.month < dateB.month) ? -1 : 1;
    }
    if (dateA.day != dateB.day) {
        return (dateA.day < dateB.day) ? -1 : 1;
    }
    return 0;
}

/******************************************
Part B. Time Related Functions
******************************************/
struct Time {
    int hour;
    int minute;
};

void make_time(Time& newTime, int hour, int minute) {
    newTime.hour = hour;
    newTime.minute = minute;
}

int compare_time(Time& timeA, Time& timeB) {
    if (timeA.hour != timeB.hour) {
        return (timeA.hour < timeB.hour) ? -1 : 1;
    }
    if (timeA.minute != timeB.minute) {
        return (timeA.minute < timeB.minute) ? -1 : 1;
    }
    return 0;
}

/******************************************
Part C. Appointment Related Functions
******************************************/
struct Appointment {
    string description;
    Date date;
    Time start;
    Time end;
};

void make_appointment(Appointment& newApt, string description, 
             int year, int month, int day,
             int startHour, int startMinute,
             int endHour, int endMinute ) {
    newApt.description = description;
    make_date(newApt.date, year, month, day);
    make_time(newApt.start, startHour, startMinute);
    make_time(newApt.end, endHour, endMinute);
}

bool has_conflict(Appointment& aptA, Appointment& aptB) {
    if (compare_date(aptA.date, aptB.date) != 0) {
        return false;
    }
    if (compare_time(aptA.end, aptB.start) <= 0) {
        return false;
    }
    if (compare_time(aptB.end, aptA.start) <= 0) {
        return false;
    }
    return true;
}

/***********************************************************
   Main function
***********************************************************/
int main() {
    // Example test cases (uncomment to test)
    
    // Testing Part A
    // Date dateOne, dateTwo;
    // make_date(dateOne, 2018, 1, 23);
    // make_date(dateTwo, 2018, 1, 23);
    // cout << "Date compare result = " << compare_date(dateOne, dateTwo) << endl; // Should be 0

    // Testing Part B
    Time timeOne, timeTwo;
    make_time(timeOne, 11, 30);
    make_time(timeTwo, 13, 45);
    cout << "Time compare result = " << compare_time(timeOne, timeTwo) << endl; // Should be -1

    // Testing Part C
    // Appointment aptOne, aptTwo;
    // make_appointment(aptOne, "Appointment One", 2018, 1, 23, 11, 30, 12, 45);
    // make_appointment(aptTwo, "Appointment Two", 2018, 1, 23, 12, 45, 13, 15);
    // if (has_conflict(aptOne, aptTwo)) {
    //     cout << "Appointments CLASH!\n";
    // } else {
    //     cout << "Appointments are FINE!\n"; // Expected output
    // }

    return 0;
}