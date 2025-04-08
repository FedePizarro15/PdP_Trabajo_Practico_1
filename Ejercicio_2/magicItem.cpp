#include "magicItem.h"

#include <iostream>

bool checkDurability(const float durability) {
    if (durability < 1) {
        cout << "No hay durabilidad restante para atacar." << endl;
        return false;
    } else {return true;}
}

bool checkMana(const float mana, const float manaCost) {
    if (mana < manaCost) {
        cout << "No hay maná restante para atacar." << endl;
        return false;
    } else {return true;}
}

void MagicItem::setName(const string& newName) {name = newName;}

void MagicItem::damageCharacter(Character& character, const float amount) const {character.receiveDamage(amount);}

void MagicItem::healCharacter(Character& character, const float amount) const {character.heal(amount);}

float MagicItem::getTotalHealthCharacter(Character& character) const {character.getTotalHealth();}

float MagicItem::getHealthCharacter(Character& character) const {character.getHealth();}

void MagicItem::consumeMana() {mana -= manaCost;}

bool MagicItem::isManaFull() const {return mana == totalMana;}

bool MagicItem::isRanged() const {return ranged;}

bool MagicItem::isDurabilityFull() const {return durability == 10;}

float MagicItem::getTotalMana() const {return totalMana;}

float MagicItem::getMana() const {return mana;}

float MagicItem::getManaCost() const {return manaCost;}

string MagicItem::getName() const {return name;};

float MagicItem::getDamage() const {return damage;};

float MagicItem::getDurability() const {return durability;};

void Staff::consumeDurability() {durability--;}

float Staff::specialMagicDamage() {return mana / 5;}

bool Staff::attack(Character& character) {
    if (!(checkDurability(durability) && checkMana(mana, manaCost))) return false;

    float toDamage = damage;

    if (attacksCount == 3) {
        toDamage += specialMagicDamage();
        attacksCount = -1;
    }

    damageCharacter(character, toDamage);
    consumeDurability();
    consumeMana();
    
    attacksCount++;

    return true;
}

void Staff::repair() {
    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 2;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + " (Bastón Mágico)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void Spellbook::consumeDurability() {durability--;}

float Spellbook::specialMagicDamage() {
    consumeDurability();
    return damage * 1.5;
}

bool Spellbook::attack(Character& character) {
    if (!(checkDurability(durability) && checkMana(mana, manaCost))) return false;

    float toDamage = damage;

    if (attacksCount == 3) {
        toDamage += specialMagicDamage();
        attacksCount = -1;
    } else if (!attacksCount) {
        toDamage /= 2;
    }

    damageCharacter(character, toDamage);
    consumeDurability();
    consumeMana();
    
    attacksCount++;

    return true;
}

void Spellbook::repair() {
    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 3;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + "(Libro de Hechizos)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void Potion::consumeDurability() {durability--;}

float Potion::specialMagicDamage() {
    heal();
    repair();
    return damage / 3;
}

bool Potion::attack(Character& character) {
    if (!(checkDurability(durability) && checkMana(mana, manaCost))) return false;

    float toDamage = damage;

    if (attacksCount == 2) {
        toDamage += specialMagicDamage();
        attacksCount = -1;
    }

    damageCharacter(character, toDamage);
    consumeDurability();
    consumeMana();
    
    attacksCount++;

    return true;
}

void Potion::repair() {
    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 3;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + "(Poción)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void Potion::heal() const {
    const float toHeal = (sorcerer->getTotalHealth() - sorcerer->getHealth()) * healPercentage;
    healCharacter(*sorcerer, toHeal);
}

void Amulet::consumeDurability() {durability -= 1.5;}

float Amulet::specialMagicDamage() {
    consumeMana();
    return damage / 4;
};

bool Amulet::attack(Character& character) {
    if (!(checkDurability(durability) && checkMana(mana, manaCost))) return false;

    float toDamage = damage;

    if (attacksCount == 3) {
        toDamage += specialMagicDamage();
        attacksCount = -1;
    }

    if (ranged) {toDamage *= 2;}

    damageCharacter(character, toDamage);
    consumeDurability();
    consumeMana();
    
    ranged = !ranged;
    attacksCount++;

    return true;
}

void Amulet::repair() {
    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 3;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + "(Amuleto)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}