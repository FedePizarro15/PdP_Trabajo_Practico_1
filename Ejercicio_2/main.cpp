#include "characterFactory.h"
#include "character.h"
#include "sorcerer.h"
#include "warrior.h"

#include <random>
#include <vector>

using namespace std;

int getRandInt(const int floor, const int ceiling) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(floor, ceiling);

    return dist(gen);
}

const string getRandSorcererType() {
    const string types[] = {"Hechicero", "Conjurador", "Brujo", "Nigromante"};
    return types[getRandInt(0, 3)];
}

const string getRandWarriorType() {
    const string types[] = {"Bárbaro", "Paladín", "Caballero", "Mercenario", "Gladiador"};
    return types[getRandInt(0, 4)];
}

const string getRandMagicWeaponType() {
    const string types[] = {"Bastón Mágico", "Libro de Hechizos", "Poción", "Amuleto"};
    return types[getRandInt(0, 3)];
}

const string getRandCombatWeaponType() {
    const string types[] = {"Hacha Simple", "Hacha Doble", "Espada", "Lanza", "Garrote"};
    return types[getRandInt(0, 4)];
}

const string getRandWeaponType() {
    const string types[] = {"Bastón Mágico", "Libro de Hechizos", "Poción", "Amuleto", 
                           "Hacha Simple", "Hacha Doble", "Espada", "Lanza", "Garrote"};
    return types[getRandInt(0, 8)];
}

int main() {
    vector<weak_ptr<Sorcerer>> sorcerers;
    vector<weak_ptr<Warrior>> warriors;

    const int sorcerersCount = getRandInt(3, 7);
    const int warriorsCount = getRandInt(3, 7);

    string sorcererType;
    string warriorType;

    weak_ptr<Sorcerer> newSorcerer;
    weak_ptr<Warrior> newWarrior;

    string leftWeaponType;
    string rightWeaponType;

    for (int i = 0; i < sorcerersCount; i++) {
        sorcererType = getRandSorcererType();

        const int weaponsCount = getRandInt(0,2);

        if (weaponsCount == 0) {newSorcerer = dynamic_pointer_cast<Sorcerer>(CharacterFactory::createCharacter(sorcererType));}

        else if (weaponsCount == 1) {newSorcerer = dynamic_pointer_cast<Sorcerer>(CharacterFactory::createArmedCharacter(sorcererType, getRandWeaponType()));}

        else {newSorcerer = dynamic_pointer_cast<Sorcerer>(CharacterFactory::createArmedCharacter(sorcererType, getRandWeaponType(), getRandWeaponType()));}
            
        if (newSorcerer.expired()) {
            cerr << "Error: La conversión a Sorcerer falló para el tipo: " << sorcererType << endl;
            exit(EXIT_FAILURE);
        }

        sorcerers.push_back(newSorcerer);
    }
    
    for (int i = 0; i < warriorsCount; i++) {
        warriorType = getRandWarriorType();

        const int weaponsCount = getRandInt(0,2);

        if (weaponsCount == 0) {newWarrior = dynamic_pointer_cast<Warrior>(CharacterFactory::createCharacter(warriorType));}
        
        else if (weaponsCount == 1) {newWarrior = dynamic_pointer_cast<Warrior>(CharacterFactory::createArmedCharacter(warriorType, getRandWeaponType()));}
        
        else {newWarrior = dynamic_pointer_cast<Warrior>(CharacterFactory::createArmedCharacter(warriorType, getRandWeaponType(), getRandWeaponType()));}
        
        if (newWarrior.expired()) {
            cerr << "Error: La conversión a Warrior falló para el tipo: " << warriorType << endl;
            exit(EXIT_FAILURE);
        }

        warriors.push_back(newWarrior);
    }
}