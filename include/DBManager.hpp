#pragma once

#include <pqxx/pqxx>
#include <vector>
#include "Employee.hpp"

class DBManager
{
public:
    DBManager(const std::string& conn_str);

    void create_table();
    void select_all();
    void select_by_filter();

    void insert_employee(const Employee& emp);
    void insert_bulk(const std::vector<Employee>& employeeV);

    void create_index_for_optimization();

private:
    std::string connection_string;

};