#pragma once

#include "organizationalEntity.h"
#include "company.h"
#include "manager.h"

#include <string>
#include <vector>
#include <set>

using namespace std;

class RegionalHeadquarters : public OrganizationalEntity {
    private:
        int employeeCount;

        vector<HighManager> highManagers;
        vector<MiddleManager> middleManagers;

        vector<Company> companies;

    public:
        const string name;
        const set<string> countries;

        int getEmployeeCount() const;
        vector<string> getCompaniesNames() const;
        vector<HighManager> getHighManagers() const;
        vector<MiddleManager> getMiddleManagers() const;
};