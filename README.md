# Employee Test Logger

## Description
The Employee Test Logger is a C++ application designed to manage employee records efficiently. It allows users to insert, view, and delete employee information, including their test results and system status. The application organizes data in a structured format and stores it in a text file, ensuring easy access and management of records.

## Features
- Insert Employee Records: Add new employee details, including employee number, name, missed distance, test result, and system status.
- View All Records: Display a comprehensive list of employee records in a formatted table.
- Delete Records: Remove employee records based on their unique employee number.
- Persistent Storage: Utilizes a text file to store employee data, creating necessary folders if they do not exist.

## How It Works
1. User Menu: The application presents a menu with options to insert, view, or delete records.
2. Data Entry: Users can input employee details, which are validated for correctness.
3. File Management: Employee records are appended to a text file, and the application manages folder creation using C++17 filesystem features.
4. Record Display: All employee records are displayed in a clear format for easy readability.

## Technologies Used
- C++: The primary programming language used for application logic.
- C++17 Features: Utilizes filesystem capabilities for folder management.
- File I/O: Implements file handling for data storage and retrieval.

## Installation
To run this project locally, download the source code and compile it with a C++17 compatible compiler. 

```bash
g++ -std=c++17 -o employee_logger employee_logger.cpp
./employee_logger
```
