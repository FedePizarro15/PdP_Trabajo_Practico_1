#pragma once

#include "weapon.h"

class Character {
    protected:
        const float totalHealth;
        float health;
        
        void heal(const float heal);
        bool receiveDamage(const float damage);

    public:
        float getTotalHealth() const;
        float getHealth() const;

    friend class MagicItem;
    friend class CombatWeapon;
};