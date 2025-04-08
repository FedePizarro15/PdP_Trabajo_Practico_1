#pragma once

#include "employee.h"

#include <string>
#include <vector>

using namespace std;

class Department {
    private:
        vector<Employee> employees;

    public:
        const string name;
        const string location;

        int countEmployees() const;
        vector<Employee> getEmployees() const;

        bool hireEmployees(Employee employee);
        bool fireEmployees(Employee employee);
};