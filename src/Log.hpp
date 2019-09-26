#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <ctime>
#include <iostream>

namespace log {

    std::string getDate(void) {
        time_t now = time(0);

        tm *ltm = localtime(&now);

        int day = ltm->tm_mday;
        int month = 1 + ltm->tm_mon;
        int year = 1900 + ltm->tm_year;

        std::string date = std::to_string(day);
        
        date.append(":"); date.append(std::to_string(month)); date.append(":"); date.append(std::to_string(year));

        return date;
    }

    std::string getHour(void) {

        time_t now = time(0);

        tm *ltm = localtime(&now);

        int hour = 1 + ltm->tm_hour;
        int min = ltm->tm_min;

        std::string str = "("; str.append(std::to_string(hour)); str.append(":"); str.append(std::to_string(min)); str.append(")");

        return str;
    }

    void log(std::string msg, bool err) {
        ////////////////// temporal
        if(!err) std::cout << "[LOG] " << getHour() << " " << msg << std::endl;
        else std::cout << "[ERROR] " << getHour() << " " << msg << std::endl;
        //////////////////


    }

    void createLog(void) {
        std::string _name = "LOG_"; _name.append(getDate()); _name.append(".txt");

        std::fstream fs (_name, std::fstream::in | std::fstream::out | std::fstream::trunc);
    }
    
}
#endif