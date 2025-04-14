#pragma once

#include "weapon.h"

#include <string>

using namespace std;

class MagicItem : public Weapon {
    protected:
        weak_ptr<Character> character;

        string name;

        const float damage;
        
        float durability = 10;
        const float durabilityCost;
        
        const float totalMana;
        float mana;
        const float manaCost;

        const int attacksToSpecial;
        int attacksCount = 1;
        
        bool ranged;

        string changeName() const;
        bool checkDurability() const;        
        bool checkMana() const;

        void setName(const string& newName) override;
        void damageCharacter(Character& damageReceiver, const float amount) const override;
        
        void healCharacter(Character& healReceiver, const float amount) const;

        void showReparation(const float oldDurability, const float oldMana) const;

        void consumeDurability(const int multiplier = 1) override;
        void consumeMana(const int multiplier = 1);
        
        virtual float specialMagicDamage() = 0;

    public:
        MagicItem(
            weak_ptr<Character> _character,
            const string& _name,
            const float _damage,
            const float _durabilityCost,
            const float _totalMana,
            const float _manaCost,
            const int _attacksToSpecial,
            const bool _ranged) :
            character(_character),
            name(_name),
            damage(_damage),
            durabilityCost(_durabilityCost),
            totalMana(_totalMana),
            mana(_totalMana),
            manaCost(_manaCost),
            attacksToSpecial(_attacksToSpecial),
            ranged(_ranged) {};
        
        virtual ~MagicItem() = default;
        
        bool isManaFull() const;

        bool isNextSpecial() const override;
        bool isSpecial() const override;
        bool isRanged() const override;
        bool isDurabilityFull() const override;

        float getTotalMana() const;
        float getMana() const;
        float getManaCost() const;

        weak_ptr<Character> getCharacter() const override;

        string getName() const override;
        string getType() const override;

        float getDamage() const override;
        float getDurability() const override;
        float getDurabilityCost() const override;

        void showWeapon() const override;

        // friend ostream& operator<< (ostream& os, const Weapon& weapon) {
        //     os << "'" << weapon.getName() << "' (Item Mágico)";
        //     return os;
        // };
};

class Staff final : public MagicItem {
    /*
    Tiene un ataque especial cada 4 ataques, que aumenta según el maná disponible,
    por lo tanto es conveniente reparar el objeto antes de usar el ataque especial.
    
    Daño Base: Normal
    Durabilidad: Normal
    Maná Base: Alto
    Consumo de Maná: Alto
    Reparación: Normal
    Recuperación de Maná: Alta
    Rango: Sí
    */
    public:
        Staff(weak_ptr<Character> _character) : MagicItem(_character, "Bastón Mágico", 15, 1, 150, 15, 4, true) {};

        float specialMagicDamage() override;

        bool attack(Character& damageReceiver, const float multiplier) override;
        void repair() override;
};

class Spellbook final : public MagicItem {
    /*
    Cuenta con un ataque base alto, además ataca de manera especial cada 4 ataques, 
    infligiendo una gran cantidad de daño, pero afecta en mayor medida a la durabilidad, 
    también al primer ataque y los siguientes luego del especial se ve debilitado.
    
    Daño Base: Alto
    Durabilidad: Normal
    Maná Base: Bajo
    Consumo de Maná: Normal
    Reparación: Normal
    Recuperación de Maná: Normal
    Rango: Sí
    */
    public:
        Spellbook(weak_ptr<Character> _character) : MagicItem(_character, "Libro de Hechizos", 17.75, 1, 75, 10, 4, true) {};

        float specialMagicDamage() override;

        bool attack(Character& damageReceiver, const float multiplier) override;
        void repair() override;
};

class Potion final : public MagicItem {
    /*
    Cada 3 ataques cura a su portador, aplica un poco más de daño y se repara.
    
    Daño Base: Muy Bajo
    Durabilidad: Normal
    Maná Base: Muy Bajo
    Consumo de Maná: Normal
    Reparación: Normal
    Recuperación de Maná: Normal
    Rango: Sí
    */
    private:
        const float healPercentage = 0.25;

    public:
        Potion(weak_ptr<Character> _character) : MagicItem(_character, "Poción", 7.5, 1, 50, 10, 3, true) {};

        float specialMagicDamage() override;

        bool attack(Character& damageReceiver, const float multiplier) override;
        void repair() override;

        void heal() const;
};

class Amulet final : public MagicItem {
    /*
    Cada ataque cambia entre rango y cuerpo a cuerpo, si está en rango genera más daño.
    Cada 4 ataques aplica un porcentaje mayor de daño, pero también consume más maná.
    
    Daño Base: Bajo
    Durabilidad: Baja
    Maná Base: Normal
    Consumo de Maná: Bajo
    Reparación: Normal
    Recuperación de Maná: Normal
    Rango: No (Inicialmente)
    */
    public:
        Amulet(weak_ptr<Character> _character) : MagicItem(_character, "Amuleto", 10, 1.5, 100, 7.5, 4, false) {};

        float specialMagicDamage() override;

        bool attack(Character& damageReceiver, const float multiplier) override;
        void repair() override;
};