#pragma once

#include "department.h"
#include "organizationalEntity.h"

#include <string>
#include <vector>

using namespace std;

class Company : public OrganizationalEntity {
    private:
        vector<Department*> departments;

    public:
        const string name;
        const string adress;

        Department getDepartmentByName(const string departmentName) const;
        vector<Department> getDepartmentNames() const;
};