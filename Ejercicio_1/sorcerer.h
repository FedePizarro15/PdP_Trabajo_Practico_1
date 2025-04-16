#pragma once

#include "character.h"

class Sorcerer : public Character {
    protected:
        shared_ptr<Weapon> leftHand;
        shared_ptr<Weapon> rightHand;

        string name;

        const float totalHealth;
        float health;

        const float agility;
        float hiddenAgility = 0;

        const float damageBonus;
        
        bool dodgeAttack(const float agility) const;
        
        shared_ptr<Weapon> chooseWeapon(shared_ptr<Weapon> leftHand, shared_ptr<Weapon> rightHand) const;

        void setName(const string& newName) override;
    
    public:
        Sorcerer(
            shared_ptr<Weapon> _leftHand,
            shared_ptr<Weapon> _rightHand,
            const string& _name,
            const float _totalHealth,
            const float _agility,
            const float _damageBonus) :
            leftHand(_leftHand),
            rightHand(_rightHand),
            name(_name),
            totalHealth(_totalHealth),
            health(_totalHealth),
            agility(_agility),
            damageBonus(_damageBonus) {};

        virtual ~Sorcerer() = default;

        virtual void hide() = 0;

        bool assignWeapon(shared_ptr<Weapon> weapon);

        bool isHealthFull() const override;

        shared_ptr<Weapon> getLeftHand() const override;
        shared_ptr<Weapon> getRightHand() const override;

        float getAgility() const;

        string getName() const override;
        string getType() const override;
        
        float getTotalHealth() const override;
        float getHealth() const override;
        float getDamageBonus() const override;

        void showCharacter() const override;
};

class Wizard final : public Sorcerer {
    /*
    Al atacar con un arma de tipo Mágico, aplica un daño mayor.

    Vida Base: Normal
    Agilidad: Normal
    Bono de Daño: Alto
    */
    private:
        void heal(const float _heal) override;

    public:
        Wizard(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Sorcerer(_leftHand, _rightHand, "Hechicero", 175, 0.2, 0.2) {};
        
        ~Wizard() = default;
        
        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void hide() override;
};

class Summoner final : public Sorcerer {
    /*
    Los ataques especiales son más potentes.

    Vida Base: Alto
    Agilidad: Bajo
    Bono de Daño: Normal
    */
    private:
        void heal(const float _heal) override;
    
    public:
        Summoner(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Sorcerer(_leftHand, _rightHand, "Conjurador", 225, 0.1, 0.1) {};
        
        ~Summoner() = default;
        
        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void hide() override;
};

class Warlock final : public Sorcerer {
    /*
    El daño recibido de los ataques de armas de tipo Mágico se reducen. Al esconderse aumenta en gran medida su posibilidad de esquivar un ataque, pero se cura menos.

    Vida Base: Muy Alto
    Agilidad: Muy Bajo
    Bono de Daño: Normal
    */
    private:
        void heal(const float _heal) override;
    
    public:
        Warlock(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Sorcerer(_leftHand, _rightHand, "Brujo", 260, 0.05, 0.1) {};
        
        ~Warlock() = default;

        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void hide() override;
};

class Necromancer final : public Sorcerer {
    /*
    Los ataques de rango se potencian. Esconderse no aumenta en gran medida la agilidad, pero se cura más.

    Vida Base: Bajo
    Agilidad: Alto
    Bono de Daño: Bajo
    */
    private:
        void heal(const float _heal) override;
    
    public:
        Necromancer(shared_ptr<Weapon> _leftHand, shared_ptr<Weapon> _rightHand) : Sorcerer(_leftHand, _rightHand, "Nigromante", 130, 0.35, 0.05) {};
        
        ~Necromancer() = default;

        void receiveDamage(const float damage, Character& attacker, const string type = "", const bool ranged = false, const bool isSpecial = false) override;

        void attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon = nullptr) override;
        void hide() override;
};