#pragma once

#include <string>
#include <ctime>
#include <sstream>

class Employee
{
public:
    std::string last_name;
    std::string first_name;
    std::string middle_name;
    std::string birth_date;
    std::string gender;

    Employee(const std::string ln, const std::string fn, const std::string mn, 
        const std::string bd, const std::string g);


    int calculate_age() const;
    std::string to_insert_query() const;

    std::string get_last_name() const;
    std::string get_first_name() const;
    std::string get_middle_name() const;
    std::string get_birth_date() const;
    std::string get_gender() const;

};