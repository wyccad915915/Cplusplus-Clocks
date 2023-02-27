// Clocks.cpp : Starts at 12am/00:00 and prompts user to increment time
// Updates clock and displays new time
// Kenneth Pivarnick
// 01-14-23

#include <iostream>
#include <string>
using namespace std;

unsigned int currentSeconds;
unsigned int currentMinutes;
unsigned int currentHours;


string twoDigitString(int num) {
    // Formats a number as 2 digits, with a leading 0 if needed
    // @param num number to format, assumed between 0 and 59, inclusive
    // @return two digit string representation of number
    if (num < 10) {
        return "0" + to_string(num);
    }
    else {
        return to_string(num);
    }
}

string nCharString(size_t n, char c) {
    // Returns a string of length n, each character a c
    // @param n string length, >=0
    // @return string of n c's
    string result = "";
    for (size_t i = 0; i < n; i++) {
        result += c;
    }
    return result;
}

string formatTime24(unsigned int hours, unsigned int minutes, unsigned int seconds) {
    // Formats the time in military format
    // @param hours, hours 0 to 23
    // @param minutes, minutes 0 to 59
    // @param seconds, seconds 0 to 59
    // @return hh:mm:ss
    if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59) {
        return twoDigitString(hours) + ":" + twoDigitString(minutes) + ":" + twoDigitString(seconds);
    }
    else {
        return "Invalid input";
    }
}

string formatTime12(unsigned int hours, unsigned int minutes, unsigned int seconds) {
    // Formats the time in am/pm format
    // @param hours, hours 0 to 23
    // @param minutes, minutes 0 to 59
    // @param seconds, seconds 0 to 59
    // @return hh:mm:ss A M or hh:mm:ss P M where hh is between 01 and 12, inclusive
    if (hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59) {
        int h;
        string am_pm;
        if (hours > 12) {
            h = hours - 12;
            am_pm = " P M";
        }
        else if (hours == 0) {
            h = 12;
            am_pm = " A M";
        }
        else if (hours == 12) {
            h = 12;
            am_pm = " P M";
        }
        else {
            h = hours;
            am_pm = " A M";
        }
        return twoDigitString(h) + ":" + twoDigitString(minutes) + ":" + twoDigitString(seconds) + am_pm;
    }
    else {
        return "Invalid input";
    }
}



void printMenu(string choices[], unsigned int numStrings, unsigned char width) {
    // Prints menu
    // @param strings[], nonempty array of choices
    // @param numStrings, number of strings in the array
    // @param width, width of each line, will be comfortably bigger than the longest string
    cout << nCharString(width, '*') << endl;
    for (unsigned int i = 0; i < numStrings; i++) {
        cout << "* " << i + 1 << " - " << choices[i];
        unsigned int spaces = width - 3 - to_string(i + 1).length() - choices[i].length();
        cout << nCharString(spaces, ' ') << "*" << endl;
    }
    cout << nCharString(width, '*') << endl;
}

unsigned int getMenuChoice(unsigned int maxChoice) {
    // Gets menu choice 1 through maxChoice, inclusive
    // @param maxChoice, maximum choice index, a number between 2 and 9, inclusive
    // @return the first valid choice, could be 1 through maxChoice, inclusive
    unsigned int choice;
    cin >> choice;
    while (choice < 1 || choice > maxChoice) {
        cin >> choice;
    }
    return choice;
}

void displayClocks(unsigned int hours, unsigned int minutes, unsigned int seconds) {
    // Prints a clock display of the current time in both 12-hour and 24-hour formats
    // @param hours, hours 0 to 23
    // @param minutes, minutes 0 to 59
    // @param seconds, seconds 0 to 59
    cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
    cout << "*" << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << "*   ";
    cout << "*" << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << "*" << endl;
    cout << endl;
    cout << "*" << nCharString(6, ' ') << formatTime12(hours, minutes, seconds) << nCharString(7, ' ') << "*   ";
    cout << "*" << nCharString(8, ' ') << formatTime24(hours, minutes, seconds) << nCharString(9, ' ') << "*" << endl;
    cout << nCharString(27, '*') << "   " << nCharString(27, '*') << endl;
}

void setSeconds(unsigned int seconds) {
    // Set current second(s)
    // @param seconds, seconds 0 to 59
        currentSeconds = seconds;
}

void setMinutes(unsigned int minutes) {
    // Set current minute(s)
    // @param minutes, minutes 0 to 59
        currentMinutes = minutes;
}

void setHours(unsigned int hours) {
    // Set current hour(s)
    // @param hours, hours 0 to 23
        currentHours = hours;
}

unsigned int getSeconds() {
    // Get current seconds
    return currentSeconds;
}

unsigned int getMinutes() {
    // Get current minutes
    return currentMinutes;
}

unsigned int getHours() {
    // Get current hours
    return currentHours;
}

void addOneHour() {
    // Function to add one hour using local variable hour
    int hour = getHours();
    if (hour >= 0 && hour <= 22) {
        setHours(hour + 1);
    }
    else if (hour == 23) {
        setHours(0);
    }
}

void addOneMinute() {
    // Function to add one minute using local variable minute
    int minute = getMinutes();
    if (minute >= 0 && minute <= 58) {
        setMinutes(minute + 1);
    }
    else if (minute == 59) {
        setMinutes(0);
        addOneHour();
    }
}

void addOneSecond() {
    // Function to add one second using local variable second
    int second = getSeconds();
    if (second >= 0 && second <= 58) {
        setSeconds(second + 1);
    }
    else if (second == 59) {
        setSeconds(0);
        addOneMinute();
    }
}

void mainMenu(unsigned int hours, unsigned int minutes, unsigned int seconds) {
    // Display the main menu and prompts the user to make a choice
    // When the user chooses to quit, the while loop will exit and the program ends
    // @param hours, hours 0 to 23
    // @param minutes, minutes 0 to 59
    // @param seconds, seconds 0 to 59
    while (true) {
        // Display the main menu options
        string choices[] = { "Add 1 Hour", "Add 1 Minute", "Add 1 Second", "Display Time", "Quit" };
        printMenu(choices, 5, 30);
        // Get the user's choice
        int choice = getMenuChoice(5);
        if (choice == 1) {
            addOneHour();
        }
        else if (choice == 2) {
            addOneMinute();
        }
        else if (choice == 3) {
            addOneSecond();
        }
        else if (choice == 4) {
            displayClocks(currentHours, currentMinutes, currentSeconds);
        }
        else if (choice == 5) {
            cout << "Goodbye!";
            break;
        }
        // display the current time
        if (choice != 4) {
            displayClocks(currentHours, currentMinutes, currentSeconds);
        }
    }
}

int main() {
    // Declare current time variables (12:00 AM or 00:00)
    currentHours = 0;
    currentMinutes = 0;
    currentSeconds = 0;

    // Call the main menu function
    mainMenu(currentHours, currentMinutes, currentSeconds);

    return 0;
}

