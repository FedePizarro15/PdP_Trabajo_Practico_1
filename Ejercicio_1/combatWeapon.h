#pragma once

#include "weapon.h"

class CombatWeapon : public Weapon {
    protected:
        weak_ptr<Character> character;

        string name;

        float damage;
        
        float durability = 15;
        const float durabilityCost;
        
        const float criticalProbability;
        
        const int attacksToSpecial;
        int attacksCount = 1;

        bool ranged;

        string changeName() const;

        bool checkDurability() const;
        bool criticalHit() const;

        void setName(const string& newName) override;

        void damageCharacter(Character& damageReceiver, float amount) const override;

        void showReparation(const float oldDurability) const;
        
        void consumeDurability(const int multiplier = 1) override;

        virtual float specialCombatDamage() = 0;

    public:
        CombatWeapon(
            weak_ptr<Character> _character,
            const string& _name,
            const float _damage,
            const float _durabilityCost,
            const float _criticalProbability,
            const int _attacksToSpecial,
            const bool _ranged) :
            character(_character),
            name(_name),
            damage(_damage),
            durabilityCost(_durabilityCost),
            criticalProbability(_criticalProbability),
            attacksToSpecial(_attacksToSpecial),
            ranged(_ranged) {};

        virtual ~CombatWeapon() = default;

        bool isNextSpecial() const override;
        bool isSpecial() const override;
        bool isRanged() const override;
        bool isDurabilityFull() const override;

        float getCriticalProbability() const;

        weak_ptr<Character> getCharacter() const override;

        string getName() const override;
        string getType() const override;

        float getDamage() const override;
        float getDurability() const override;
        float getDurabilityCost() const override;

        void showWeapon() const override;
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
    public:
        SingleAxe(weak_ptr<Character> _character) : CombatWeapon(_character, "Hacha Simple", 17.5, 1, 0.25, 3, false) {};
        
        ~SingleAxe() = default;

        float specialCombatDamage() override;

        bool attack(Character& damageReceiver, const float multiplier = 1.0) override;
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
    public:
        BattleAxe(weak_ptr<Character> _character) : CombatWeapon(_character, "Hacha Doble", 25, 1.5, 0.1, 4, false) {};
        
        ~BattleAxe() = default;

        float specialCombatDamage() override;

        bool attack(Character& damageReceiver, const float multiplier = 1.0) override;
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
    public:
        Sword(weak_ptr<Character> _character) : CombatWeapon(_character, "Espada", 20, 2, 0.15, 3, false) {};
        
        ~Sword() = default;

        float specialCombatDamage() override;

        bool attack(Character& damageReceiver, const float multiplier = 1.0) override;
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
    public:
        Spear(weak_ptr<Character> _character) : CombatWeapon(_character, "Lanza", 17.5, 1, 0.1, 4, false) {};
        
        ~Spear() = default;
        
        float specialCombatDamage() override;

        bool attack(Character& damageReceiver, const float multiplier = 1.0) override;
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
    public:
        Mace(weak_ptr<Character> _character) : CombatWeapon(_character, "Garrote", 12.5, 0.75, 0.1, 4, false) {};
        
        ~Mace() = default;

        float specialCombatDamage() override;

        bool attack(Character& damageReceiver, const float multiplier = 1.0) override;
        void repair() override;
};