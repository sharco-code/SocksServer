#include <fstream>
#include <ctime>
#include <iostream>

std::string getDate() {
    time_t now = time(0);

    tm *ltm = localtime(&now);

    int day = ltm->tm_mday;
    int month = 1 + ltm->tm_mon;
    int year = 1900 + ltm->tm_year;

    std::string date = std::to_string(day);
    
    date.append(":"); date.append(std::to_string(month)); date.append(":"); date.append(std::to_string(year));

    return date;
}

void Log() {
    
    

}

void createLog() {
    std::string _name = "LOG_"; _name.append(getDate()); _name.append(".txt");

    std::fstream fs (_name, std::fstream::in | std::fstream::out | std::fstream::trunc);
}


