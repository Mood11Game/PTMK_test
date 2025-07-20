#include "Employee.hpp"
#include <iostream>


Employee::Employee(const std::string ln, const std::string fn, const std::string mn, const std::string bd, const std::string g)
        : last_name(ln), first_name(fn), middle_name(mn), birth_date(bd), gender(g) 
        {}

std::string Employee::get_last_name() const
{
    return last_name;
}

std::string Employee::get_first_name() const
{
    return first_name;
}

std::string Employee::get_middle_name() const
{
    return middle_name;
}

std::string Employee::get_birth_date() const
{
    return birth_date;
}

std::string Employee::get_gender() const
{
    return gender;
}


std::string Employee::to_insert_query() const {
    return "INSERT INTO employees (last_name, first_name, middle_name, birth_date, gender) VALUES ('" +
        last_name + "', '" + first_name + "', '" + middle_name + "', '" + 
        birth_date + "', '" + gender + "');";
}

int Employee::calculate_age() const 
{
    struct tm tm = {};
    if (!strptime(birth_date.c_str(), "%Y-%m-%d", &tm)) 
        return -1;

    time_t birth_time = mktime(&tm);
    time_t now = time(nullptr);

    double years = difftime(now, birth_time) / (60 * 60 * 24 * 365.25);
    return static_cast<int>(years);
}
