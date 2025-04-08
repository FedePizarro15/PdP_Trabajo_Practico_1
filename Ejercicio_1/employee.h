#pragma once

#include <string>

using namespace std;

class Employee {
    private:
        int seniority;
        float wage;

        float getWage() const;
    
    public:
        const string name;
        string position;

        int getSeniority() const;
        bool updateWage(const float newWage);
};