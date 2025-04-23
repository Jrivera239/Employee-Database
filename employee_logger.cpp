#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <filesystem> // C++17 feature for folder management

namespace fs = std::filesystem;

// File and folder location
const std::string FOLDER_NAME = "logs";
const std::string FILE_NAME = FOLDER_NAME + "/employee_database.txt";

// Represents a single employee record
class EmployeeRecord {
public:
    EmployeeRecord(int number, const std::string& name, double missedFt,
                   const std::string& testResult, const std::string& systemFail)
        : empNumber_(number), empName_(name), missedDistanceFt_(missedFt),
          testResult_(testResult), systemFail_(systemFail) {}

    // Converts object to CSV format
    std::string serialize() const {
        return std::to_string(empNumber_) + "," + empName_ + "," +
               std::to_string(missedDistanceFt_) + "," + testResult_ + "," + systemFail_;
    }

    // converts CSV line to an object
    static EmployeeRecord deserialize(const std::string& line) {
        size_t pos = 0, prev = 0;
        std::vector<std::string> tokens;
        while ((pos = line.find(',', prev)) != std::string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));

        return EmployeeRecord(std::stoi(tokens[0]), tokens[1],
                              std::stod(tokens[2]), tokens[3], tokens[4]);
    }

    // prints the employee record to the console
    void display() const {
        std::cout << std::left << std::setw(15) << empNumber_
                  << std::setw(20) << empName_
                  << std::setw(20) << missedDistanceFt_
                  << std::setw(15) << testResult_
                  << std::setw(20) << systemFail_ << std::endl;
    }

    int getId() const { return empNumber_; }

private:
    int empNumber_;
    std::string empName_;
    double missedDistanceFt_;
    std::string testResult_;
    std::string systemFail_;
};

class EmployeeDatabase {
private:
    // Creates folder if it doesn't exist
    void ensureFolderExists() const {
        if (!fs::exists(FOLDER_NAME)) {
            fs::create_directory(FOLDER_NAME);
        }
    }

public:
    // adds a new employee record to the database
    void insert(int id, const std::string& name, double missedFt,
                const std::string& result, const std::string& system) {
        ensureFolderExists();
        std::ofstream file(FILE_NAME, std::ios::app);
        if (file.is_open()) {
            EmployeeRecord r(id, name, missedFt, result, system);
            file << r.serialize() << "\n";
            std::cout << "Inserted employee record." << std::endl;
        } else {
            std::cerr << "Error: Unable to open database file.\n";
        }
    }

    // displays all employee records
    void selectAll() const {
        ensureFolderExists();
        std::ifstream file(FILE_NAME);
        std::string line;
        std::cout << "\nEmployee Records:\n";
        std::cout << std::left << std::setw(15) << "Emp Number"
                  << std::setw(20) << "Name"
                  << std::setw(20) << "Missed Ft"
                  << std::setw(15) << "Test Result"
                  << std::setw(20) << "System Fail" << std::endl;
        std::cout << std::string(90, '-') << std::endl;

        while (std::getline(file, line)) {
            EmployeeRecord::deserialize(line).display();
        }
    }

    // removes a record based on employee number
    void remove(int id) {
        ensureFolderExists();
        std::ifstream file(FILE_NAME);
        std::ofstream temp("temp.txt");

        std::string line;
        bool found = false;

        while (std::getline(file, line)) {
            EmployeeRecord r = EmployeeRecord::deserialize(line);
            if (r.getId() != id) {
                temp << r.serialize() << "\n";
            } else {
                found = true;
            }
        }

        file.close();
        temp.close();

        std::remove(FILE_NAME.c_str());
        std::rename("temp.txt", FILE_NAME.c_str());

        std::cout << (found ? "Deleted employee with ID: " : "No employee found with ID: ") << id << std::endl;
    }
};

void menu() {
    EmployeeDatabase db;
    int choice;

    while (true) {
        std::cout << "\nEmployee Test Logger Menu:\n";
        std::cout << "1. Insert Employee Record\n";
        std::cout << "2. View All Records\n";
        std::cout << "3. Delete Record by Employee Number\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 0) break;

        int id;
        std::string name, result, system;
        double missedFt;

        switch (choice) {
            case 1:
                std::cout << "Enter Employee Number: ";
                std::cin >> id;
                std::cin.ignore();

                std::cout << "Enter Employee Name: ";
                std::getline(std::cin, name);

                // gets and validate a number for missed distance
                while (true) {
                    std::cout << "Enter Missed Distance (ft): ";
                    std::cin >> missedFt;

                    if (std::cin.fail()) {
                        std::cin.clear();  // reset the fail flag
                        std::cin.ignore(10000, '\n');  // discard bad input
                        std::cout << "❌ Please enter a valid number.\n";
                    } else {
                        std::cin.ignore();
                        break;
                    }
                }

                // gets and validate test result (pass/fail only)
                while (true) {
                    std::cout << "Enter Test Result (pass/fail): ";
                    std::getline(std::cin, result);

                    if (result == "pass" || result == "fail") {
                        break;
                    } else {
                        std::cout << "❌ Invalid input. Please type only 'pass' or 'fail'.\n";
                    }
                }

                std::cout << "Enter System Status (none/failure): ";
                std::getline(std::cin, system);

                db.insert(id, name, missedFt, result, system);
                break;

            case 2:
                db.selectAll();
                break;
            case 3:
                std::cout << "Enter Employee Number to delete: ";
                std::cin >> id;
                db.remove(id);
                break;
            default:
                std::cout << "Invalid option selected.\n";
        }
    }
}

int main() {
    menu();  // starts the program menu
    return 0;
}
