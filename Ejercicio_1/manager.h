#pragma once

#include "employee.h"

#include <string>

using namespace std;

class Manager : public Employee {
    private:
        float bonus;
        string level;
    
    public:
        bool updateBonus(const float newBonus);
        bool setLevel(const string newLevel);

        float getBonus() const;
};

class HighManager : public Manager {
    public:
        HighManager() {setLevel("high");}
};

class MiddleManager : public Manager {
    public:
        MiddleManager() {setLevel("mid");}
};

class LowManager : public Manager {
    public:
        LowManager() {setLevel("low");}
};

class TeamLeader : public Manager {};