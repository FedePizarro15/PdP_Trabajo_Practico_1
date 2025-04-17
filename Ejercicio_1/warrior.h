#pragma once

#include "character.h"
#include <iostream>

using namespace std;

class Warrior : public Character {
    protected:
        shared_ptr<Weapon> leftHand;
        shared_ptr<Weapon> rightHand;

        string name;

        const float totalHealth;
        float health;

        const float armor;
        float reinforcedArmor = 0;

        const float damageBonus;

        shared_ptr<Weapon> chooseWeapon(shared_ptr<Weapon> leftHand, shared_ptr<Weapon> rightHand) const override;
        
        void setName(const string& newName) override;
    
    public:
        Warrior(
            shared_ptr<Weapon> _leftHand,
            shared_ptr<Weapon> _rightHand,
            const string& _name,
            const float _totalHealth,
            const float _armor,
            const float _damageBonus) :
            leftHand(_leftHand),
            rightHand(_rightHand),
            name(_name),
            totalHealth(_totalHealth),
            health(_totalHealth),
            armor(_armor),
            damageBonus(_damageBonus) {};

        virtual ~Warrior() = default;

        virtual void reinforce() = 0;

        bool assignWeapon(shared_ptr<Weapon> weapon);

        bool isHealthFull() const override;

        shared_ptr<Weapon> getLeftHand() const override;
        shared_ptr<Weapon> getRightHand() const override;
        
        float getArmor() const;
        
        string getName() const override;
        string getType() const override;

        float getTotalHealth() const override;
        float getHealth() const override;
        float getDamageBonus() const override;

        void showCharacter() const override;
};

class Barbarian final : public Warrior {
    /*
    Al atacar con un arma de tipo Combate, aplica un daño mayor.

    Vida Base: Normal
    Armadura: Normal
    Bono de Daño: Alto
    */
    private:
        void heal(const float _heal) override;
    
    public:
        Barbarian(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Warrior(_leftHand, _rightHand, "Bárbaro", 175, 0.125, 0.2) {};
        
        ~Barbarian() = default;
        
        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void reinforce() override;

};

class Paladin final : public Warrior {
    /*
    Aplica un mayor daño con los ataques cuerpo a cuerpo. Se cura un poco más.

    Vida Base: Bajo
    Armadura: Alto
    Bono de Daño: Bajo
    */
    private:
        void heal(const float _heal) override;
    
    public:
        Paladin(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Warrior(_leftHand, _rightHand, "Paladín", 130, 0.25, 0.05) {};
        
        ~Paladin() = default;
        
        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void reinforce() override;
};

class Knight final : public Warrior {
    /*
    Tiene una probabilidad de rebotar un ataque. Reforzarse aumenta en menor medida la armadura, pero se cura un poco más.

    Vida Base: Normal
    Armadura: Alto
    Bono de Daño: Bajo
    */
    private:
        const float reboundProbability = 0.15;

        void heal(const float _heal) override;

        bool reboundAttack(const float reboundProbability) const;

    public:
        Knight(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Warrior(_leftHand, _rightHand, "Caballero", 175, 0.25, 0.05) {};
        
        ~Knight() = default;

        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void reinforce() override;

        void reboundDamage(Character& damageReceiver, const float damage);

        float getReboundProbability() const;
};

class Mercenary final : public Warrior {
    /*
    El daño recibido de los ataques de tipo Combate se reducen.

    Vida Base: Alto
    Armadura: Bajo
    Bono de Daño: Normal
    */
    private:
        void heal(const float _heal) override;
    
    public:
        Mercenary(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Warrior(_leftHand, _rightHand, "Mercenario", 175, 0.05, 0.1) {};
        
        ~Mercenary() = default;

        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void reinforce() override;
};

class Gladiator final : public Warrior {
    /*
    Los ataques especiales provocan menos daño. Reforzarse aumenta en gran medida la armadura, pero se cura menos.
    
    Vida Base: Normal
    Armadura: Bajo
    Bono de Daño: Normal
    */
    private:
        void heal(const float _heal) override;

    public:
        Gladiator(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Warrior(_leftHand, _rightHand, "Gladiador", 175, 0.125, 0.2) {};
        
        ~Gladiator() = default;

        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void reinforce() override;
};