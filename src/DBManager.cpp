#include "DBManager.hpp"
#include <iostream>
#include <chrono>

DBManager::DBManager(const std::string& conn_str)
    : connection_string(conn_str)
    {}

void DBManager::create_table()
{
    try
    {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);

        txn.exec(
            "CREATE TABLE employees ("
            "id SERIAL PRIMARY KEY, "
            "last_name VARCHAR(100), "
            "first_name VARCHAR(100), "
            "middle_name VARCHAR(100), "
            "birth_date DATE, "
            "gender VARCHAR(10));"
        );

        txn.commit();
        std::cout << "Table create\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void DBManager::insert_employee(const Employee& emp)
{
    try
    {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        txn.exec(emp.to_insert_query());
        txn.commit();
        std::cout << "Employee inserted\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void DBManager::insert_bulk(const std::vector<Employee>& employeeV)
{
    try
    {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        for(const auto& emp : employeeV)
            txn.exec(emp.to_insert_query());

        txn.commit();
        std::cout << "Bulk insert completed.\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void DBManager::select_all() 
{
    try 
    {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        pqxx::result r = txn.exec(
            "SELECT last_name, first_name, middle_name, birth_date, gender "
            "FROM employees "
            "GROUP BY last_name, first_name, middle_name, birth_date, gender "
            "ORDER BY last_name, first_name, middle_name"
        );

        std::cout << "LastName FirstName MiddleName BirthDate Gender Age\n";
        std::cout << "-------------------------------------------------------------\n";

        for (auto row : r) 
        {
            std::string last_name = row[0].c_str();
            std::string first_name = row[1].c_str();
            std::string middle_name = row[2].c_str();
            std::string birth_date = row[3].c_str();
            std::string gender = row[4].c_str();

            Employee emp(last_name, first_name, middle_name, birth_date, gender);
            int age = emp.calculate_age();

            std::cout << last_name << " "
                      << first_name << " "
                      << middle_name << " "
                      << birth_date << " "
                      << gender << " "
                      << age << "\n";
        }
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error selecting all employees: " << e.what() << std::endl;
    }
}


void DBManager::select_by_filter() 
{
    try 
    {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        auto start = std::chrono::high_resolution_clock::now();

        auto result = txn.exec("SELECT last_name, first_name, middle_name, birth_date, gender FROM employees WHERE gender = 'Male' AND last_name LIKE 'F%';");

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        for (auto row : result) {
            std::cout << row[0].c_str() << " "
                      << row[1].c_str() << " "
                      << row[2].c_str() << " "
                      << row[3].c_str() << " "
                      << row[4].c_str() << "\n";
        }

        std::cout << "Query executed in " << elapsed.count() << " seconds.\n";
    } 
    catch (std::exception& e) 
    {
        std::cerr << e.what() << "\n";
    }
}

void DBManager::create_index_for_optimization() 
{
    try 
    {
        pqxx::connection conn(connection_string);
        pqxx::work txn(conn);
        txn.exec("CREATE INDEX IF NOT EXISTS idx_employees_lastname_gender ON employees (last_name, gender);");
        txn.commit();
        std::cout << "Index created.\n";
    } 
    catch (std::exception& e) 
    {
        std::cerr << e.what() << "\n";
    }
}




