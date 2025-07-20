#include "DBManager.hpp"
#include "Employee.hpp"
#include <iostream>
#include <vector>
#include <string>

void print_help(const std::string& app_name) 
{
    std::cout << "====== PTMK Test Application Modes ======\n";
    std::cout << "Usage: " << app_name << " <mode> [params]\n\n";
    std::cout << "Modes:\n";
    std::cout << "1 - Create employee table in DB\n";
    std::cout << "2 - Insert a single employee\n";
    std::cout << "    Usage: " << app_name << " 2 <LastName> <FirstName> <MiddleName> <BirthDate> <Gender>\n";
    std::cout << "3 - Select and display all employees\n";
    std::cout << "4 - Bulk insert 1,000,000 employees + 100 with 'F' last names\n";
    std::cout << "5 - Select male employees with last name starting with 'F' and measure time\n";
    std::cout << "6 - Create index to optimize previous query and measure performance gain\n";
    std::cout << "=========================================\n";
}

int main(int argc, char* argv[]) 
{
    std::vector<std::string> args(argv, argv + argc);
    std::string conn_str = "dbname=ptmk_test_db user=moodgame";
    DBManager db(conn_str);

    if (args.size() < 2) 
    {
        print_help(args[0]);
        return 1;
    }

    int mode = 0;
    try 
    {
        mode = std::stoi(args[1]);
    } 
    catch (...) 
    {
        std::cerr << "Invalid mode number.\n";
        print_help(args[0]);
        return 1;
    }

    switch (mode) 
    {
        case 1:
            db.create_table();
            break;
        case 2:
            if (args.size() != 7) 
            {
                std::cerr << "Usage: " << args[0] << " 2 <LastName> <FirstName> <MiddleName> <BirthDate> <Gender>\n";
                return 1;
            } 
            else 
            {
                Employee emp(args[2], args[3], args[4], args[5], args[6]);
                db.insert_employee(emp);
            }
            break;
        case 3:
            db.select_all();
            break;
        case 4: 
        {
            std::vector<Employee> employees;
            employees.reserve(1000100); 
            for (int i = 0; i < 1000000; ++i) 
            {
                employees.emplace_back(
                    "Smith" + std::to_string(i),
                    "John",
                    "Doe",
                    "1990-01-01",
                    (i % 2 == 0) ? "Male" : "Female"
                );
            }
            for (int i = 0; i < 100; ++i) 
            {
                employees.emplace_back(
                    "Foster" + std::to_string(i),
                    "Mike",
                    "Jr",
                    "1985-05-05",
                    "Male"
                );
            }
            db.insert_bulk(employees);
            break;
        }
        case 5:
            db.select_by_filter();
            break;
        case 6:
            db.create_index_for_optimization();
            break;
        default:
            std::cerr << "Unknown mode.\n";
            print_help(args[0]);
            return 1;
    }

}
