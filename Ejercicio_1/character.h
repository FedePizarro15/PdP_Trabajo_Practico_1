#pragma once

#include "weapon.h"

#include <string>
#include <memory>
#include <random>
#include <iostream>

using namespace std;

class Weapon;

class Character {
    protected:
        virtual void heal(const float _heal) = 0;

    public:
        virtual ~Character() = default;
        
        virtual bool assignWeapon(shared_ptr<Weapon> weapon) = 0;
        virtual void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) = 0;
        virtual void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) = 0;

        virtual shared_ptr<Weapon> chooseWeapon(shared_ptr<Weapon> leftHand, shared_ptr<Weapon> rightHand) const = 0;

        virtual void setName(const string& newName) = 0;
        
        virtual bool isHealthFull() const = 0;

        virtual shared_ptr<Weapon> getLeftHand() const = 0;
        virtual shared_ptr<Weapon> getRightHand() const = 0;

        virtual string getName() const = 0;
        virtual string getType() const = 0;

        virtual float getTotalHealth() const = 0;
        virtual float getHealth() const = 0;
        virtual float getDamageBonus() const = 0;

        virtual void showCharacter() const = 0;

    friend class MagicItem;
    friend class CombatWeapon;
};