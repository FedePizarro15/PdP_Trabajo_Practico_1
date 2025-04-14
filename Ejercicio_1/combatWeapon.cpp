#include "combatWeapon.h"

#include <iostream>
#include <random>

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

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(0.0, 1.0);

string CombatWeapon::changeName() const {
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

bool CombatWeapon::checkDurability() const {
    if (durability < 1) {
        cout << RED_FORMAT << "No hay durabilidad restante para atacar." << RESET_FORMAT << endl;
        return false;
    } else {return true;}
}

bool CombatWeapon::criticalHit() const {return dist(gen) <= criticalProbability;}

void CombatWeapon::setName(const string& newName) {name = newName;}

void CombatWeapon::damageCharacter(Character& damageReceiver, float amount) const {
    cout << character.lock()->getName() << " ataca a " << damageReceiver.getName() 
         << " con " << getName() 
         << (isNextSpecial() ? " (¡ATAQUE ESPECIAL!)" : "")
         << (ranged ? " a distancia" : " cuerpo a cuerpo")
         << " causando " << RED_FORMAT << amount << RESET_FORMAT << " puntos de daño." << endl;
         
    damageReceiver.receiveDamage(amount, *character.lock(), "CombatWeapon", ranged, isNextSpecial());
}

void CombatWeapon::consumeDurability(const int multiplier) {
    const float oldDurability = durability;

    durability -= durabilityCost * multiplier;

    cout << getName() << " pierde " << YELLOW_FORMAT << durabilityCost * multiplier << RESET_FORMAT << " puntos de durabilidad ("
         << YELLOW_FORMAT << oldDurability << RESET_FORMAT << " → " << YELLOW_FORMAT << durability << RESET_FORMAT << ")." << endl;
}

bool CombatWeapon::isNextSpecial() const {return attacksToSpecial == attacksCount;}

bool CombatWeapon::isSpecial() const {return attacksToSpecial == 0;}

bool CombatWeapon::isRanged() const {return ranged;}

bool CombatWeapon::isDurabilityFull() const {return durability == 15;}

float CombatWeapon::getCriticalProbability() const {return criticalProbability;}

weak_ptr<Character> CombatWeapon::getCharacter() const {return character.lock();}

string CombatWeapon::getName() const {return name;}

string CombatWeapon::getType() const {return "CombatWeapon";}

float CombatWeapon::getDamage() const {return damage;}

float CombatWeapon::getDurability() const {return durability;}

float CombatWeapon::getDurabilityCost() const {return durabilityCost;}

void CombatWeapon::showWeapon() const {
    cout << "Portador: " << getCharacter().lock()->getName() << endl;
    cout << "Nombre: " << getName() << endl;
    cout << "Daño: " << RED_FORMAT << getDamage() << RESET_FORMAT << endl;
    cout << "Durabilidad: " << YELLOW_FORMAT << getDurability() << RESET_FORMAT << "/" << YELLOW_FORMAT << "15" << RESET_FORMAT << endl;
    cout << "Probabilidad de Crítico: " << MAGENTA_FORMAT << (getCriticalProbability() * 100) << "%" << RESET_FORMAT << endl;
    cout << (isNextSpecial() ? "El próximo ataque es Especial" : "Faltan " + to_string(attacksToSpecial - attacksCount) + " ataques para un ataque Especial" ) << endl;
    cout << "Rango: " << (isRanged() ? "Sí" : "No") << endl;
}

void CombatWeapon::showReparation(const float oldDurability) const {
    cout << getName() << " ha sido reparado:" << endl;
    cout << "Durabilidad: " << YELLOW_FORMAT << oldDurability << RESET_FORMAT << " → " << YELLOW_FORMAT << durability << RESET_FORMAT << endl;
}

float SingleAxe::specialCombatDamage() {
    damage += 2.5;
        
    cout << "¡El hacha " << getName() << " aumenta su daño base permanentemente!" << endl;
    cout << "Daño base: " << RED_FORMAT << damage - 2.5 << RESET_FORMAT << " → " << RED_FORMAT << damage << RESET_FORMAT << endl;

    return damage * 0.1;
}

bool SingleAxe::attack(Character& damageReceiver, const float multiplier) {
    if (!checkDurability()) return false;

    float toDamage = damage;

    if (attacksCount == attacksToSpecial) {
        float specialDamage = specialCombatDamage() + 2.5;
        toDamage += specialDamage;
        attacksCount = 0;
        cout << "¡" << character.lock()->getName() << " afila el hacha " << getName() << " generando " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
    }

    if (criticalHit()) {
        cout << RED_FORMAT << "¡GOLPE CRÍTICO!" << RESET_FORMAT << " El daño aumenta en un " 
             << ((attacksCount == attacksToSpecial) ? "100%" : "50%") << endl;
        toDamage *= attacksCount == attacksToSpecial ? 2 : 1.5;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void SingleAxe::repair() {
    const float oldDurability = durability;

    durability += (15 - durability) / 2;

    showReparation(oldDurability);
}

float BattleAxe::specialCombatDamage() {return damage / 2;}

bool BattleAxe::attack(Character& damageReceiver, const float multiplier) {
    if (!checkDurability()) return false;

    int durabilityConsumeMultiplier = 1;

    float toDamage = damage;

    if (attacksCount == attacksToSpecial) {
        float specialDamage = specialCombatDamage();
        toDamage += specialDamage;
        attacksCount = 0;
        durabilityConsumeMultiplier = 2;

        cout << "¡" << character.lock()->getName() << " gira con el hacha doble " << getName() << " provocando " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
        cout << "¡Consume durabilidad extra!" << endl;
    }

    if (criticalHit()) {
        cout << RED_FORMAT << "¡GOLPE CRÍTICO!" << RESET_FORMAT << " El daño aumenta en un 50%" << endl;
        toDamage *= 1.5;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability(durabilityConsumeMultiplier);
    
    attacksCount++;

    return true;
}

void BattleAxe::repair() {
    const float oldDurability = durability;

    durability += (15 - durability) / 3;

    showReparation(oldDurability);
}

float Sword::specialCombatDamage() {
    repair();
    return durability * 1.5;
}

bool Sword::attack(Character& damageReceiver, const float multiplier) {
    if (!checkDurability()) return false;

    float toDamage = damage;

    if (attacksCount == attacksToSpecial) {
        float specialDamage = specialCombatDamage();
        toDamage += specialDamage;
        attacksCount = 0;

        cout << "¡" << character.lock()->getName() << " canaliza la energía de " << getName() << " causando " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
        cout << "¡" << getName() << " se repara a sí misma durante el ataque!" << endl;
    }

    if (criticalHit()) {
        cout << RED_FORMAT << "¡GOLPE CRÍTICO!" << RESET_FORMAT << " El daño aumenta en un 50%" << endl;
        toDamage *= 1.5;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void Sword::repair() {
    const float oldDurability = durability;
    
    durability += (15 - durability) / 2;

    showReparation(oldDurability);
}

float Spear::specialCombatDamage() {return damage * 2;}

bool Spear::attack(Character& damageReceiver, const float multiplier) {
    if (!checkDurability()) return false;

    float toDamage = damage;

    if (attacksCount == attacksToSpecial) {
        float specialDamage = specialCombatDamage();
        ranged = true;
        toDamage += specialDamage;
        attacksCount = 0;
        
        cout << "¡" << character.lock()->getName() << " arroja " << getName() << " sobrecargada, causando " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
    } else if (!attacksCount) {
        cout << getName() << " está siendo recuperada. No causa daño este turno." << endl;
        ranged = false;
        toDamage = 0;
    }

    if (criticalHit()) {
        cout << " RED_FORMAT <<\n¡GOLPE CRÍTICO" << RESET_FORMAT << " ! El daño aumenta en un 100%\n" << endl;
        toDamage *= 2;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void Spear::repair() {
    const float oldDurability = durability;
    
    durability += (15 - durability) / 2;

    showReparation(oldDurability);
}

float Mace::specialCombatDamage() {return damage * 2;}

bool Mace::attack(Character& damageReceiver, const float multiplier) {
    if (!checkDurability()) return false;

    int durabilityConsumeMultiplier = 1;

    float toDamage = 0;

    if (attacksCount == attacksToSpecial) {
        float specialDamage = specialCombatDamage();
        toDamage += specialDamage;
        attacksCount = 0;
        durabilityConsumeMultiplier = 4;

        cout << "¡" << character.lock()->getName() << " libera toda la energía de " << getName() << " en un golpe demoledor que provoca " << RED_FORMAT << specialDamage << RESET_FORMAT << " de daño adicional!" << endl;
        cout << "Este ataque consume mucha durabilidad." << endl;
    } else if (!attacksCount) {
        damage = 12.5;
    }

    toDamage += damage;

    if (criticalHit()) {
        cout << RED_FORMAT << "¡GOLPE CRÍTICO!" << RESET_FORMAT << " El daño aumenta en un 50%" << endl;
        toDamage *= 1.5;
    }

    damageCharacter(damageReceiver, toDamage * multiplier);
    consumeDurability(durabilityConsumeMultiplier);

    damage += 1.5;    
    cout << getName() << " aumenta su daño base: " << damage - 1.5 << " → " << damage << endl;
    attacksCount++;

    return true;
}

void Mace::repair() {
    const float oldDurability = durability;
    
    durability += 3 * (15 - durability) / 5;

    showReparation(oldDurability);
}