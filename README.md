# Employee Test Logger

## Overview
The Employee Test Logger is a simple C++ program that helps you manage employee records. 
You can easily add, view, and delete information about employees, including their test results and system status. 
The program keeps everything organized in a text file, making it easy to access and manage records.

## Key Features
- Add Employee Records: You can enter new employee details, such as their number, name, missed distance, test result, and system status.
- View All Records: See a clear list of all employee records displayed in a table format.
- Delete Records: Remove employee records using their unique employee number.
- Data Storage: Employee information is saved in a text file, and the program creates any necessary folders automatically.

## How It Works
1. User Menu: When you run the program, you will see a menu with options to add, view, or delete records.
2. Input Data: You can enter employee details, and the program checks if the information is correct.
3. File Management: The program saves employee records in a text file, using C++17 features to manage folders.
4. Display Records: All records are shown in a clear and easy-to-read format.

## Technologies Used
- C++: The main programming language used to build the application.
- C++17 Features: Uses modern features for managing folders.
- File Handling: Reads and writes data to a text file.

## Installation
Follow these stepsTo run this program:
1. Download the source code.
2. Compile using a C++17 compatible compiler.

```bash
g++ -std=c++17 -o employee_logger employee_logger.cpp
./employee_logger
```
