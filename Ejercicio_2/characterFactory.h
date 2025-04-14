#pragma once

#include "../Ejercicio_1/character.h"

#include <string>
#include <memory>

class CharacterFactory {
    public:
        static shared_ptr<Character> createCharacter(const string characterType);
        static shared_ptr<Weapon> createWeapon(const string weaponType, const shared_ptr<Character> character = nullptr);
        static shared_ptr<Character> createArmedCharacter(const string characterType, const string leftWeaponType, const string rightWeaponType = "");
};