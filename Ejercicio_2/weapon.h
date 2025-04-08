#pragma once

#include "character.h"

#include <string>

using namespace std;

class Weapon {
    public:
        virtual bool attack(Character& character) = 0;
        virtual void repair() = 0;
        virtual bool isRanged() const = 0;
        virtual bool isDurabilityFull() const = 0;

        virtual void consumeDurability() = 0;
        virtual void setName(const string&) = 0;

        virtual string getName() const = 0;
        virtual float getDamage() const = 0;
        virtual float getDurability() const = 0;
};