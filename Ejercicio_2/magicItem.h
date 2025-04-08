#pragma once

#include "weapon.h"

#include <string>

using namespace std;

class MagicItem : public Weapon {
    protected:
        Character* sorcerer;
        string name;

        const float damage;
        
        float durability = 10;
        
        const float totalMana;
        float mana;
        float manaCost;

        int attacksCount = 0;
        
        bool ranged;

        void setName(const string& newName) override;
        void damageCharacter(Character& character, const float amount) const;
        void healCharacter(Character& character, const float amount) const;

        float MagicItem::getTotalHealthCharacter(Character& character) const;
        float MagicItem::getHealthCharacter(Character& character) const;

        void consumeMana();
        
        virtual float specialMagicDamage() = 0;

    public:
        MagicItem(Character* _sorcerer, const string& _name, const float _damage, const float _totalMana, const float _manaCost, const bool _ranged) : sorcerer(_sorcerer), name(_name), damage(_damage), totalMana(_totalMana), mana(_totalMana), manaCost(_manaCost), ranged(_ranged) {};
        
        bool isManaFull() const;

        bool isRanged() const override;
        bool isDurabilityFull() const override;

        float getTotalMana() const;
        float getMana() const;
        float getManaCost() const;

        string getName() const override;
        float getDamage() const override;
        float getDurability() const override;
};

class Staff final : public MagicItem {
    /*
    Tiene un ataque especial cada 4 ataques, que aumenta según el maná disponible,
    por lo tanto es conveniente reparar el objeto antes de usar el ataque especial.
    
    Daño Base: Normal
    Maná Base: Alto
    Consumo de Maná: Alto
    Durabilidad: Normal
    Reparación: Normal
    Recuperación de Maná: Alta
    Rango: Sí
    */
    private:    
        void consumeDurability() override;

    public:
        Staff(Character* _sorcerer) : MagicItem(_sorcerer, "Bastón Mágico", 15, 150, 15, true) {};

        float specialMagicDamage() override;

        bool attack(Character& character) override;
        void repair() override;
};

class Spellbook final : public MagicItem {
    /*
    Cuenta con un ataque base alto, además ataca de manera especial cada 4 ataques, 
    infligiendo una gran cantidad de daño, pero afecta en mayor medida a la durabilidad, 
    también al primer ataque y los siguientes luego del especial se ve debilitado.
    
    Daño Base: Alto
    Maná Base: Bajo
    Consumo de Maná: Normal
    Durabilidad: Normal
    Reparación: Normal
    Recuperación de Maná: Normal
    Rango: Sí
    */
    private:
        void consumeDurability() override;

    public:
        Spellbook(Character* _sorcerer) : MagicItem(_sorcerer, "Libro de Hechizos", 17.75, 75, 10, true) {};

        float specialMagicDamage() override;

        bool attack(Character& character) override;
        void repair() override;

};

class Potion final : public MagicItem {
    /*
    Cada 3 ataques cura a su portador y aumenta su velocidad de ataque, aplica un poco más de daño y se repara.
    
    Daño Base: Muy Bajo
    Maná Base: Muy Bajo
    Consumo de Maná: Normal
    Durabilidad: Normal
    Reparación: Normal
    Recuperación de Maná: Normal
    Rango: Sí
    */
    private:
        const float healPercentage = 0.25;

        void consumeDurability() override;

    public:
        Potion(Character* _sorcerer) : MagicItem(_sorcerer, "Poción", 7.5, 50, 10, true) {};

        float specialMagicDamage() override;

        bool attack(Character& character) override;
        void repair() override;
        void heal() const;

};

class Amulet final : public MagicItem {
    /*
    Cada ataque cambia entre rango y cuerpo a cuerpo, si está en rango genera más daño.
    Cada 4 ataques aplica un porcentaje mayor de daño, pero también consume más maná.
    
    Daño Base: Bajo
    Maná Base: Normal
    Consumo de Maná: Bajo
    Durabilidad: Baja
    Reparación: Normal
    Recuperación de Maná: Normal
    Rango: No (Inicialmente)
    */
    private:
        void consumeDurability() override;

    public:
        Amulet(Character* _sorcerer) : MagicItem(_sorcerer, "Amuleto", 10, 100, 7.5, false) {};

        float specialMagicDamage() override;

        bool attack(Character& character) override;
        void repair() override;

};