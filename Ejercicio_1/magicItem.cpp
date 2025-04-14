#include "magicItem.h"

#include <iostream>

const string RED_FORMAT = "\033[1;31m"; // Daño
const string GREEN_FORMAT = "\033[1;32m"; // Verde
const string YELLOW_FORMAT = "\033[33m"; // Amarillo
const string BLUE_FORMAT = "\033[1;34m"; // Azul
const string MAGENTA_FORMAT = "\033[35m"; // Magenta
const string CIAN_FORMAT = "\033[1;36m"; // Cian
const string GRAY_FORMAT = "\033[90m"; // Gris
const string PINK_FORMAT = "\033[95m"; // Rosado
const string BROWN_FORMAT = "\033[38;5;94m"; // Marrón
const string RESET_FORMAT = "\033[0m"; // Reset

string MagicItem::changeName() const {
    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char choice;
    cin >> choice;

    if (choice == 's' || choice == 'S') {
        string newName;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore();
        getline(cin, newName);
        return newName;
    }
    
    return "";
}

bool MagicItem::checkDurability() const {
    if (durability < durabilityCost) {
        cout << "No hay durabilidad restante para atacar." << endl;
        return false;
    } else {
        return true;
    }
}

bool MagicItem::checkMana() const {
    if (mana < manaCost) {
        cout << "No hay maná restante para atacar." << endl;
        return false;
    } else {
        return true;
    }
}

void MagicItem::setName(const string& newName) {
    const string oldName = name;
    name = newName;
    cout << "Nombre cambiado: '" << oldName << "' → '" << name << "'" << endl;
}

void MagicItem::damageCharacter(Character& damageReceiver, const float amount) const {
    cout << character.lock()->getName() << " ataca a " << damageReceiver.getName() 
         << " con " << getName() 
         << RED_FORMAT << (isSpecial() ? " (¡ATAQUE ESPECIAL!)" : "") << RESET_FORMAT
         << (ranged ? " a distancia" : " cuerpo a cuerpo")
         << " causando " << RED_FORMAT << amount << RESET_FORMAT << " puntos de daño." << endl;
         
    damageReceiver.receiveDamage(amount, *character.lock(), "MagicItem", ranged, isSpecial());
}

void MagicItem::healCharacter(Character& healReceiver, const float amount) const {
    cout << getName() << " restaura " << GREEN_FORMAT << amount << RESET_FORMAT << " puntos de vida a " 
         << healReceiver.getName() << "." << endl;
         
    healReceiver.heal(amount);
}

void MagicItem::consumeDurability(const int multiplier) {
    const float oldDurability = durability;

    durability -= durabilityCost * multiplier;

    cout << getName() << " pierde " << YELLOW_FORMAT << durabilityCost * multiplier << RESET_FORMAT << " puntos de durabilidad ("
         << YELLOW_FORMAT << oldDurability << RESET_FORMAT << " → " << YELLOW_FORMAT << durability << RESET_FORMAT << ")." << endl;
}

void MagicItem::consumeMana(const int multiplier) {
    const float oldMana = mana;

    mana -= manaCost * multiplier;

    cout << getName() << " consume " << CIAN_FORMAT << manaCost * multiplier << RESET_FORMAT << " puntos de maná ("
         << CIAN_FORMAT << oldMana << RESET_FORMAT << " → " << CIAN_FORMAT << mana << RESET_FORMAT << ")." << endl;
}

bool MagicItem::isManaFull() const {return mana == totalMana;}

bool MagicItem::isNextSpecial() const {return attacksCount == attacksToSpecial;}

bool MagicItem::isSpecial() const {return attacksCount == 0;}

bool MagicItem::isRanged() const {return ranged;}

bool MagicItem::isDurabilityFull() const {return durability == 10;}

float MagicItem::getTotalMana() const {return totalMana;}

float MagicItem::getMana() const {return mana;}

float MagicItem::getManaCost() const {return manaCost;}

weak_ptr<Character> MagicItem::getCharacter() const {return character.lock();}

string MagicItem::getName() const {return name;}

string MagicItem::getType() const {return "MagicItem";}

float MagicItem::getDamage() const {return damage;}

float MagicItem::getDurability() const {return durability;}

float MagicItem::getDurabilityCost() const {return durabilityCost;}

void MagicItem::showWeapon() const {
    cout << "Portador: " << getCharacter().lock()->getName() << endl;
    cout << "Nombre: " << getName() << endl;
    cout << "Tipo: " << getType() << endl;
    cout << "Daño: " << RED_FORMAT << getDamage() << RESET_FORMAT << endl;
    cout << "Durabilidad: " << YELLOW_FORMAT << getDurability() << RESET_FORMAT << "/" << YELLOW_FORMAT << "10" << RESET_FORMAT << endl;
    cout << "Maná: " << CIAN_FORMAT << getMana() << RESET_FORMAT << "/" << CIAN_FORMAT << getTotalMana() << RESET_FORMAT << endl;
    cout << "Costo de Maná: " << CIAN_FORMAT << getManaCost() << RESET_FORMAT << endl;
    cout << (isNextSpecial() ? "El próximo ataque es Especial" : "Faltan " + to_string(attacksToSpecial - attacksCount) + " ataques para un ataque Especial" ) << endl;
    cout << "Rango: " << (isRanged() ? "Sí" : "No") << endl;
}

void MagicItem::showReparation(const float oldDurability, const float oldMana) const {
    cout << getName() << " ha sido reparado:" << endl;
    cout << "Durabilidad: " << YELLOW_FORMAT << oldDurability << RESET_FORMAT << " → " << YELLOW_FORMAT << durability << RESET_FORMAT << endl;
    cout << "Maná: " << CIAN_FORMAT << oldMana << RESET_FORMAT << " → " << CIAN_FORMAT << mana << RESET_FORMAT << endl;
}

float Staff::specialMagicDamage() {return mana / 5;}

bool Staff::attack(Character& damageReceiver, const float multiplier) {
    if (!(checkDurability() && checkMana())) return false;

    float toDamage = damage;

    if (isNextSpecial()) {
        float specialDamage = specialMagicDamage();
        toDamage += specialDamage;
        attacksCount = 0;

        cout << "¡" << character.lock()->getName() << " realiza un ataque especial cargando todo el maná con " << getName() << " provocando " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability();
    consumeMana();
    
    attacksCount++;

    return true;
}

void Staff::repair() {
    const float oldDurability = durability;
    const float oldMana = mana;
    
    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 2;
    
    showReparation(oldDurability, oldMana);
}

float Spellbook::specialMagicDamage() {return damage * 1.5;}

bool Spellbook::attack(Character& damageReceiver, const float multiplier) {
    if (!(checkDurability() && checkMana())) return false;

    int durabilityConsumeMultiplier = 1;

    float toDamage = damage;

    if (isNextSpecial()) {
        float specialDamage = specialMagicDamage();
        toDamage += specialDamage;
        attacksCount = 0;
        durabilityConsumeMultiplier = 2;
        
        cout << "¡El poder mágico de" << getName() << " añade " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño al ataque de " << character.lock()->getName() << "!" << endl;
    } else if (!attacksCount) {
        toDamage /= 2;
        cout << "¡El daño se redujo a la mitad!" << endl;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability(durabilityConsumeMultiplier);
    consumeMana();
    
    attacksCount++;

    return true;
}

void Spellbook::repair() {
    const float oldDurability = durability;
    const float oldMana = mana;

    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 3;
    
    showReparation(oldDurability, oldMana);
}

float Potion::specialMagicDamage() {
    heal();
    cout << "La poción " << getName() << " se reparará como parte del ataque especial." << endl;
    repair();
    return damage / 3;
}

bool Potion::attack(Character& damageReceiver, const float multiplier) {
    if (!(checkDurability() && checkMana())) return false;

    float toDamage = damage;

    if (isNextSpecial()) {
        cout << "¡" << character.lock()->getName() << " realiza un ataque especial con " << getName() << "!" << endl;

        float specialDamage = specialMagicDamage();
        toDamage += specialDamage;
        attacksCount = 0;

        cout << "¡La fusión de pociones añade " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño!" << endl;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability();
    consumeMana();
    
    attacksCount++;

    return true;
}

void Potion::repair() {
    const float oldDurability = durability;
    const float oldMana = mana;

    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 3;
    
    showReparation(oldDurability, oldMana);
}

void Potion::heal() const {
    if (character.lock()->getHealth() >= character.lock()->getTotalHealth()) {
        cout << character.lock()->getName() << " ya tiene la salud al máximo." << endl;
        return;
    }

    const float toHeal = (character.lock()->getTotalHealth() - character.lock()->getHealth()) * healPercentage;

    cout << "La poción " << getName() << " cura " << GREEN_FORMAT << toHeal << RESET_FORMAT << " puntos de vida a " << character.lock()->getName() << endl
         << "(" << GREEN_FORMAT << character.lock()->getHealth() << RESET_FORMAT << " → " << GREEN_FORMAT << character.lock()->getHealth() + toHeal << RESET_FORMAT << ")." << endl;

    healCharacter(*character.lock(), toHeal);
}

float Amulet::specialMagicDamage() {return damage / 4;}

bool Amulet::attack(Character& damageReceiver, const float multiplier) {
    if (!(checkDurability() && checkMana())) return false;

    float manaConsumeMultiplier = 1;

    float toDamage = damage;

    if (isNextSpecial()) {
        float specialDamage = specialMagicDamage();
        toDamage += specialDamage;
        attacksCount = 0;
        manaConsumeMultiplier = 2;

        cout << "¡" << character.lock()->getName() << " invoca el poderoso rayo de " << getName() << " realizando " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
    }

    if (ranged) {toDamage *= 2;}

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability();
    consumeMana(manaConsumeMultiplier);
    
    ranged = !ranged;
    cout << "El próximo ataque será " << (ranged ? "a distancia" : "cuerpo a cuerpo") << "." << endl;
    attacksCount++;

    return true;
}

void Amulet::repair() {
    const float oldDurability = durability;
    const float oldMana = mana;

    durability += (10 - durability) / 2;
    mana += (totalMana - mana) / 3;
    
    showReparation(oldDurability, oldMana);
}