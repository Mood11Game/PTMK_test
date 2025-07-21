#include "DBManager.hpp"
#include "Employee.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <functional>

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
            auto random_in_range = [](int min, int max) -> int{
                return min + rand() % (max - min + 1);
            };

            std::vector<Employee> employees;
            std::vector<std::string> firstNamePerson ={
                "James", "Mary", "John", "Patricia", "Robert", "Jennifer", "Michael", "Linda", "William", "Elizabeth", "David", "Barbara", "Richard", "Susan", "Joseph", "Jessica", "Thomas", "Sarah", "Charles", "Karen", "Christopher", "Nancy", "Daniel", "Lisa", "Matthew", "Betty", "Anthony", "Margaret", "Donald", "Sandra",
                "Mark", "Ashley", "Paul", "Kimberly", "Steven", "Emily", "Andrew", "Donna", "Kenneth", "Michelle", "George", "Dorothy", "Joshua", "Carol", "Kevin", "Amanda", "Brian", "Melissa", "Edward", "Deborah", "Ronald", "Stephanie", "Timothy", "Rebecca", "Jason", "Laura", "Jeffrey", "Sharon", "Ryan", "Cynthia",
                "Jacob", "Kathleen", "Gary", "Amy", "Nicholas", "Shirley", "Eric", "Angela", "Stephen", "Helen", "Jonathan", "Anna", "Larry", "Brenda", "Justin", "Pamela", "Scott", "Nicole", "Brandon", "Emma", "Benjamin", "Samantha", "Samuel", "Katherine", "Frank", "Christine", "Gregory", "Debra", "Raymond", "Rachel"

            };
            std::vector<std::string> lastNamePerson ={
                "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin", "Lee", "Perez", "Thompson", "White", "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson",
                "Walker", "Young", "Allen", "King", "Wright", "Scott", "Torres", "Nguyen", "Hill", "Flores", "Green", "Adams", "Nelson", "Baker", "Hall", "Rivera", "Campbell", "Mitchell", "Carter", "Roberts", "Gomez", "Phillips", "Evans", "Turner", "Diaz", "Parker", "Cruz", "Edwards", "Collins", "Reyes",
                "Stewart", "Morris", "Morales", "Murphy", "Cook", "Rogers", "Gutierrez", "Ortiz", "Morgan", "Cooper", "Peterson", "Bailey", "Reed", "Kelly", "Howard", "Ramos", "Kim", "Cox", "Ward", "Richardson", "Watson", "Brooks", "Chavez", "Wood", "James", "Bennett", "Gray", "Mendoza", "Ruiz", "Hughes",
                "Price", "Alvarez", "Castillo", "Sanders", "Patel", "Myers", "Long", "Ross", "Foster", "Jimenez"

            };

            std::vector<std::string> midNamePerson ={
                "Michael", "James", "Robert", "John", "David", "William", "Richard", "Thomas", "Charles", "Joseph", "Christopher", "Daniel", "Matthew", "Anthony", "Mark", "Donald", "Steven", "Paul", "Andrew", "Joshua", "Kenneth", "Kevin", "Brian", "George", "Edward", "Ronald", "Timothy", "Jason", "Jeffrey", "Ryan",
                "Jacob", "Gary", "Nicholas", "Eric", "Stephen", "Jonathan", "Larry", "Justin", "Scott", "Brandon", "Benjamin", "Samuel", "Frank", "Gregory", "Raymond", "Patrick", "Alexander", "Jack", "Dennis", "Jerry", "Tyler", "Aaron", "Jose", "Henry", "Douglas", "Peter", "Adam", "Nathan", "Zachary", "Walter",
                "Kyle", "Harold", "Carl", "Jeremy", "Keith", "Roger", "Gerald", "Ethan", "Arthur", "Terry", "Christian", "Sean", "Lawrence", "Austin", "Joe", "Noah", "Jesse", "Albert", "Bryan", "Billy", "Bruce", "Willie", "Jordan", "Dylan", "Alan", "Ralph", "Gabriel", "Roy", "Juan"

            };

            employees.reserve(1'000'100);

            for (int i = 0; i < 1'000'000; ++i) 
            {
                std::string last_name =  lastNamePerson[random_in_range(0,99)];
                std::string first_name = firstNamePerson[random_in_range(0,99)];
                std::string middle_name = midNamePerson[random_in_range(0,99)];
                std::string birth_date = std::to_string(random_in_range(1970,2020)) + "-" + std::to_string(random_in_range(1,12)) + "-" + std::to_string(random_in_range(1,12));
                std::string gender = ((i % 2 == 0) ? "Male" : "Female");
                employees.emplace_back(last_name, first_name, middle_name, birth_date, gender);
            }

            for (int i = 0; i < 100; ++i) 
            {
                std::string last_name =  lastNamePerson[random_in_range(0,99)];
                std::string first_name = firstNamePerson[random_in_range(0,99)];
                std::string middle_name = midNamePerson[random_in_range(0,99)];
                std::string birth_date = std::to_string(random_in_range(1970,2020)) + "-" + std::to_string(random_in_range(1,12)) + "-" + std::to_string(random_in_range(1,12));
                std::string gender = "Male";
                employees.emplace_back(last_name, first_name, middle_name, birth_date, gender);
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
