#pragma once

#include <string>
#include <vector>

using namespace std;

class OrganizationalEntity {
    private:
        const string name;
        vector<OrganizationalEntity*> subEntities;
    
    public:
        const string getName() const;
        void addSubEntities(const OrganizationalEntity*);
        int countSubEntities() const;
};