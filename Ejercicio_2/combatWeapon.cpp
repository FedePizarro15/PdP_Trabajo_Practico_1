#include "combatWeapon.h"

#include <iostream>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(0.0, 1.0);

bool checkDurability(const float durability) {
    if (durability < 1) {
        cout << "No hay durabilidad restante para atacar." << endl;
        return false;
    } else {return true;}
}

bool criticalHit(const float criticalProbability) {return dist(gen) <= criticalProbability;}

void CombatWeapon::setName(const string& newName) {name = newName;}

void CombatWeapon::damageCharacter(Character& character, float amount) const {character.receiveDamage(amount);}

bool CombatWeapon::isRanged() const {return ranged;}

bool CombatWeapon::isDurabilityFull() const {return durability == 15;}

float CombatWeapon::getCriticalProbability() const {return criticalProbability;}

string CombatWeapon::getName() const {return name;}

float CombatWeapon::getDamage() const {return damage;}

float CombatWeapon::getDurability() const {return durability;}

void SingleAxe::consumeDurability() {durability--;}

float SingleAxe::specialCombatDamage() {
    damage += 1.5;
    return damage * 0.1;
}

bool SingleAxe::attack(Character& character) {
    if (!checkDurability(durability)) return false;

    float toDamage = damage;

    if (attacksCount == 2) {
        toDamage += specialCombatDamage();
        attacksCount = -1;
    }

    if (criticalHit(criticalProbability)) {toDamage *= attacksCount == 3 ? 2 : 1.5;}

    damageCharacter(character, toDamage);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void SingleAxe::repair() {
    durability += (15 - durability) / 2;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + " (Hacha Simple)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void BattleAxe::consumeDurability() {durability -= 1.5;}

float BattleAxe::specialCombatDamage() {
    consumeDurability();
    return damage / 2;
}

bool BattleAxe::attack(Character& character) {
    if (!checkDurability(durability)) return false;

    float toDamage = damage;

    if (attacksCount == 3) {
        toDamage += specialCombatDamage();
        attacksCount = -1;
    }

    if (criticalHit(criticalProbability)) {toDamage *= 1.5;}

    damageCharacter(character, toDamage);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void BattleAxe::repair() {
    durability += (15 - durability) / 3;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + " (Hacha Doble)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void Sword::consumeDurability() {durability -= 2;}

float Sword::specialCombatDamage() {
    repair();
    return durability * 1.5;
}

bool Sword::attack(Character& character) {
    if (!checkDurability(durability)) return false;

    float toDamage = damage;

    if (attacksCount == 2) {
        toDamage += specialCombatDamage();
        attacksCount = -1;
    }

    if (criticalHit(criticalProbability)) {toDamage *= 1.5;}

    damageCharacter(character, toDamage);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void Sword::repair() {
    durability += (15 - durability) / 2;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + " (Espada)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void Spear::consumeDurability() {durability--;}

float Spear::specialCombatDamage() {
    return damage * 2;
}

bool Spear::attack(Character& character) {
    if (!checkDurability(durability)) return false;

    float toDamage = damage;

    if (attacksCount == 3) {
        ranged = true;
        toDamage += specialCombatDamage();
        attacksCount = -1;
    } else if (!attacksCount) {
        toDamage = 0;
        ranged = false;
    }

    if (criticalHit(criticalProbability)) {toDamage *= 2;}

    damageCharacter(character, toDamage);
    consumeDurability();
    
    attacksCount++;

    return true;
}

void Spear::repair() {
    durability += (15 - durability) / 2;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + " (Lanza)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}

void Mace::consumeDurability() {durability -= 0.75;}

float Mace::specialCombatDamage() {
    for (int i = 0; i < 4; i++) consumeDurability();
    return damage * 2;
}

bool Mace::attack(Character& character) {
    if (!checkDurability(durability)) return false;

    float toDamage = 0;

    if (attacksCount == 3) {
        toDamage += specialCombatDamage();
        attacksCount = -1;
    } else if (!attacksCount) {
        damage = 12.5;
    }

    toDamage += damage;

    if (criticalHit(criticalProbability)) {toDamage *= 1.5;}

    damageCharacter(character, toDamage);
    consumeDurability();

    damage += 2.5;    
    attacksCount++;

    return true;
}

void Mace::repair() {
    durability += 3 * (15 - durability) / 5;

    cout << "¿Desea cambiar el nombre del objeto? (s/n): ";
    char respuesta;
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        string nuevoNombre;
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore(); // Para limpiar el buffer de entrada
        getline(cin, nuevoNombre);
        setName(nuevoNombre + " (Garrote)");
        cout << "Nombre cambiado con éxito." << endl;
    }
}