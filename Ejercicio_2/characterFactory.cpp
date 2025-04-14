#include "characterFactory.h"
#include "../Ejercicio_1/sorcerer.h"
#include "../Ejercicio_1/warrior.h"
#include "../Ejercicio_1/magicItem.h"
#include "../Ejercicio_1/combatWeapon.h"

#include <stdexcept>

shared_ptr<Character> CharacterFactory::createCharacter(const string characterType) {
    if (characterType == "Hechicero") {
        return make_shared<Wizard>(nullptr, nullptr);
    } else if (characterType == "Conjurador") {
        return make_shared<Summoner>(nullptr, nullptr);
    } else if (characterType == "Brujo") {
        return make_shared<Warlock>(nullptr, nullptr);
    } else if (characterType == "Nigromante") {
        return make_shared<Necromancer>(nullptr, nullptr);
    } else if (characterType == "Bárbaro") {
        return make_shared<Barbarian>(nullptr, nullptr);
    } else if (characterType == "Paladín") {
        return make_shared<Paladin>(nullptr, nullptr);
    } else if (characterType == "Caballero") {
        return make_shared<Knight>(nullptr, nullptr);
    } else if (characterType == "Mercenario") {
        return make_shared<Mercenary>(nullptr, nullptr);
    } else if (characterType == "Gladiador") {
        return make_shared<Gladiator>(nullptr, nullptr);
    } else {
        throw runtime_error("Tipo de personaje no conocido: " + characterType);
    }
}

shared_ptr<Weapon> CharacterFactory::createWeapon(const string weaponType, const shared_ptr<Character> character) {
    if (weaponType == "Bastón Mágico") {
        return make_shared<Staff>(character);
    } else if (weaponType == "Libro de Hechizos") {
        return make_shared<Spellbook>(character);
    } else if (weaponType == "Poción") {
        return make_shared<Potion>(character);
    } else if (weaponType == "Amuleto") {
        return make_shared<Amulet>(character);
    } else if (weaponType == "Hacha Simple") {
        return make_shared<SingleAxe>(character);
    } else if (weaponType == "Hacha Doble") {
        return make_shared<BattleAxe>(character);
    } else if (weaponType == "Espada") {
        return make_shared<Sword>(character);
    } else if (weaponType == "Lanza") {
        return make_shared<Spear>(character);
    } else if (weaponType == "Garrote") {
        return make_shared<Mace>(character);
    } else {
        throw runtime_error("Tipo de arma no conocido: " + weaponType);
    }
}

shared_ptr<Character> CharacterFactory::createArmedCharacter(const string characterType, const string leftWeaponType, const string rightWeaponType) {
    shared_ptr<Character> character = createCharacter(characterType);

    character->assignWeapon(createWeapon(leftWeaponType, character));

    if (!rightWeaponType.empty()) {
        character->assignWeapon(createWeapon(rightWeaponType, character));
    }

    return character;
}