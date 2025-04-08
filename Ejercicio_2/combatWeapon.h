#pragma once

#include "weapon.h"

class CombatWeapon : public Weapon {
    protected:
        Character* warrior;
        string name;

        float damage;
        
        float durability = 15;
        
        const float criticalProbability;
        
        int attacksCount = 0;

        bool ranged;

        void setName(const string& newName) override;
        
        void damageCharacter(Character& character, float amount) const;
        
        virtual float specialCombatDamage() = 0;

    public:
        CombatWeapon(Character* _warrior, const string& _name, const float _damage, const float _criticalProbability, const bool _ranged) : warrior(_warrior), name(_name), damage(_damage), criticalProbability(_criticalProbability), ranged(_ranged) {};

        bool isRanged() const override;
        bool isDurabilityFull() const override;

        float getCriticalProbability() const;

        string getName() const override;
        float getDamage() const override;
        float getDurability() const override;
};

class SingleAxe final : public CombatWeapon {
    /*
    Cada 3 ataques aumenta su daño base un poco,
    además si aplica un ataque crítico, duplicará su daño.
    
    Daño Base: Normal
    Probabilidad de Crítico: Alto
    Durabilidad: Normal
    Reparación: Normal
    Rango: No
    */
    private:
        void consumeDurability() override;

    public:
        SingleAxe(Character* _warrior) : CombatWeapon(_warrior, "Hacha Simple", 17.5, 25, false) {};

        float specialCombatDamage() override;

        bool attack(Character& character) override;
        void repair() override;
};

class BattleAxe final : public CombatWeapon {
    /*
    Cada 4 ataques aplica un mayor daño, pero se reduce su durabilidad.

    Daño Base: Muy Alto
    Probabilidad de Crítico: Bajo
    Durabilidad: Baja
    Reparación: Baja
    Rango: No
    */
    private:
        void consumeDurability() override;

    public:
        BattleAxe(Character* _warrior) : CombatWeapon(_warrior, "Hacha Doble", 25, 10, false) {};

        float specialCombatDamage() override;

        bool attack(Character& character) override;
        void repair() override;
};

class Sword final : public CombatWeapon {
    /*
    Cada 3 ataques aplica un mayor daño con respecto a su durabilidad y se repara.

    Daño Base: Alto
    Probabilidad de Crítico: Normal
    Durabilidad: Muy Baja
    Reparación: Normal
    Rango: No
    */
    private:
        void consumeDurability() override;

    public:
        Sword(Character* _warrior) : CombatWeapon(_warrior, "Espada", 20, 15, false) {};

        float specialCombatDamage() override;

        bool attack(Character& character) override;
        void repair() override;
};

class Spear final : public CombatWeapon {
    /*
    Cada 4 ataques puede ser lanzada, convirtiendose en un arma de rango,
    produce más daño, sin embargo el próximo ataque queda inutilizada.

    Daño Base: Normal
    Probabilidad de Crítico: Bajo
    Durabilidad: Normal
    Reparación: Normal
    Rango: No (Inicialmente)
    Los ataques críticos hacen el doble de daño.
    */
    private:
        void consumeDurability() override;

    public:
        Spear(Character* _warrior) : CombatWeapon(_warrior, "Lanza", 17.5, 10, false) {};
        
        float specialCombatDamage() override;

        bool attack(Character& character) override;
        void repair() override;
};

class Mace final : public CombatWeapon {
    /*
    Cada ataque aumenta su daño, hasta el cuarto ataque que se potenica, perdiendo durabilidad.
    
    Daño Base: Bajo
    Probabilidad de Crítico: Baja
    Durabilidad: Alta
    Reparación: Alta
    Rango: No
    */
    private:
        void consumeDurability() override;

    public:
        Mace(Character* _warrior) : CombatWeapon(_warrior, "Garrote", 12.5, 10, false) {};

        float specialCombatDamage() override;

        bool attack(Character& character) override;
        void repair() override;
};