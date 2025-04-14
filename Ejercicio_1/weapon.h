#pragma once

#include "character.h"

#include <string>
#include <memory>

using namespace std;

class Character;

class Weapon {
    protected:
        virtual void consumeDurability(const int multiplier = 1) = 0;
        
        virtual void setName(const string&) = 0;
        virtual void damageCharacter(Character& damageReceiver, const float amount) const = 0;

    public:
        virtual ~Weapon() = default;
        
        virtual bool attack(Character& damageReceiver, const float multiplier = 1.0) = 0;
        virtual void repair() = 0;

        virtual bool isNextSpecial() const = 0;
        virtual bool isSpecial() const = 0;
        virtual bool isRanged() const = 0;
        virtual bool isDurabilityFull() const = 0;

        virtual weak_ptr<Character> getCharacter() const = 0;

        virtual string getName() const = 0;
        virtual string getType() const = 0;

        virtual float getDamage() const = 0;
        virtual float getDurability() const = 0;
        virtual float getDurabilityCost() const = 0;

        virtual void showWeapon() const = 0;
};