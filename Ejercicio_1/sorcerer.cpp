#include "sorcerer.h"

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

bool Sorcerer::dodgeAttack(const float agility) const {
    bool dodged = dist(gen) <= agility;

    if (dodged) {cout << PINK_FORMAT << "¡Ataque esquivado!\n" << RESET_FORMAT << endl;}
    
    return dodged;
}

shared_ptr<Weapon> Sorcerer::chooseWeapon(shared_ptr<Weapon> leftHand, shared_ptr<Weapon> rightHand) const {
    shared_ptr<Weapon> chosenWeapon;
    int option;

    if (leftHand && rightHand) {
        auto leftWeapon = leftHand;
        auto rightWeapon = rightHand;

        cout << "\n1. Mano Izquierda: " << leftWeapon->getName() << RED_FORMAT
             << (leftWeapon->isNextSpecial() ? " (Ataque Especial)" : "") << RESET_FORMAT << endl;
        cout << "2. Mano Derecha: " << rightWeapon->getName() << RED_FORMAT
             << (rightWeapon->isNextSpecial() ? " (Ataque Especial)" : "") << RESET_FORMAT << endl;
        cout << "\nElija con que arma atacar:\n>> ";
        cin >> option;

        if (option == 1) {
            chosenWeapon = leftHand;
            
            if (auto weaponPtr = chosenWeapon) {
                cout << "\nSe utilizará " << weaponPtr->getName() << " para atacar." << endl << endl;
            }
        } else if (option == 2) {
            chosenWeapon = rightHand;
            
            if (auto weaponPtr = chosenWeapon) {
                cout << "\nSe utilizará " << weaponPtr->getName() << " para atacar." << endl << endl;
            }
        } else {
            cout << "\nOpción inválida..." << endl << endl;
        }
    } else if (leftHand) {
        chosenWeapon = leftHand;
        
        if (auto weaponPtr = chosenWeapon) {
            cout << "\nSe utilizará " << weaponPtr->getName() << " para atacar." << endl << endl;
        }

    } else if (rightHand) {
        chosenWeapon = rightHand;
        
        if (auto weaponPtr = chosenWeapon) {
            cout << "\nSe utilizará " << weaponPtr->getName() << " para atacar." << endl << endl;
        }
    } else {
        cout << "\nNo hay armas con las que atacar..." << endl << endl;
    }

    return chosenWeapon;
}

void Sorcerer::setName(const string& newName) {name = newName;}

bool Sorcerer::assignWeapon(shared_ptr<Weapon> weapon) {
    if (!leftHand) {
        leftHand = weapon;
        return true;
    } else if (!rightHand) {
        rightHand = weapon;
        return true;
    } else {
        return false;
    }
}

bool Sorcerer::isHealthFull() const {return health == totalHealth;}

shared_ptr<Weapon> Sorcerer::getLeftHand() const {return leftHand;};

shared_ptr<Weapon> Sorcerer::getRightHand() const {return rightHand;};

float Sorcerer::getAgility() const {return agility;}

string Sorcerer::getName() const {return name;}

string Sorcerer::getType() const {return "Sorcerer";}

float Sorcerer::getTotalHealth() const {return totalHealth;}

float Sorcerer::getHealth() const {return health;}

float Sorcerer::getDamageBonus() const {return damageBonus;}

void Sorcerer::showCharacter() const {
    cout << "Nombre: " << getName() << endl;

    cout << "Mano Izquierda: ";
    if (getLeftHand()) {
        cout << getLeftHand()->getName() << endl;
    } else {
        cout << "Vacía" << endl;
    }
    
    cout << "Mano Derecha: ";
    if (getRightHand()) {
        cout << getRightHand()->getName() << endl;
    } else {
        cout << "Vacía" << endl;
    }

    cout << "Vida: " << GREEN_FORMAT << getHealth() << RESET_FORMAT << "/" << GREEN_FORMAT << getTotalHealth() << RESET_FORMAT << endl;
    cout << "Agilidad: " << PINK_FORMAT << getAgility() << RESET_FORMAT << endl;
    cout << "Bonificación de daño: " << RED_FORMAT << getDamageBonus() << RESET_FORMAT << endl;
}

void Wizard::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;
    cout << getName() << " recupera " << GREEN_FORMAT << _heal << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Wizard::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    cout << getName() << " intenta esquivar el ataque de " << attacker.getName() << "...\n" << endl;
    
    if (!dodgeAttack(agility + hiddenAgility)) {
        float oldHealth = health;
        health -= damage;
        cout << getName() << " recibe " << RED_FORMAT << damage << RESET_FORMAT << " puntos de daño ("
             << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
    }

    if (hiddenAgility != 0) {
        cout << getName() << " pierde su bonificación de agilidad oculta.\n" << endl;
        hiddenAgility = 0;
    }
}

void Wizard::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        multiplier += weapon->getType() == "MagicItem" ? 0.35 : 0;

        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << "¡" << getName() << " no puede atacar sin un arma!\n" << endl;
    }
}

void Wizard::hide() {
    cout << getName() << " se concentra y canaliza poder arcano...\n" << endl;
    float toHeal = (totalHealth - health) * 0.175;
    heal(toHeal);
    hiddenAgility = agility * 0.5;
    cout << getName() << " aumenta su agilidad en " << PINK_FORMAT << hiddenAgility << RESET_FORMAT 
         << " puntos para el próximo ataque.\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Summoner::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;
    cout << getName() << " recupera " << GREEN_FORMAT << _heal << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Summoner::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    cout << getName() << " intenta esquivar el ataque de " << attacker.getName() << "...\n" << endl;
    
    if (!dodgeAttack(agility + hiddenAgility)) {
        float oldHealth = health;
        health -= damage;
        cout << getName() << " recibe " << RED_FORMAT << damage << RESET_FORMAT << " puntos de daño ("
             << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
    }

    if (hiddenAgility != 0) {
        cout << getName() << " pierde su bonificación de agilidad oculta.\n" << endl;
        hiddenAgility = 0;
    }
}

void Summoner::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        if (weapon->isNextSpecial()) {
            multiplier += 0.35;
            cout << getName() << " intensifica el poder del ataque especial.\n" << endl;
            cout << "¡El multiplicador de daño aumenta a " << multiplier << "x!\n" << endl;
        }
        
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << "¡" << getName() << " no puede atacar sin un arma!\n" << endl;
    }
}

void Summoner::hide() {
    cout << getName() << " invoca espíritus protectores...\n" << endl;
    float toHeal = (totalHealth - health) * 0.35;
    heal(toHeal);
    hiddenAgility = agility * 0.25;
    cout << getName() << " aumenta su agilidad en " << PINK_FORMAT << hiddenAgility << RESET_FORMAT 
         << " puntos para el próximo ataque.\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Warlock::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;
    cout << getName() << " recupera " << GREEN_FORMAT << _heal << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Warlock::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    cout << getName() << " intenta esquivar el ataque de " << attacker.getName() << "...\n" << endl;
    
    if (!dodgeAttack(agility + hiddenAgility)) {
        float oldHealth = health;
        float actualDamage = damage;
        
        if (type == "MagicItem") {
            cout << "¡" << getName() << " absorbe parte del poder mágico del ataque!\n" << endl;
            actualDamage *= 0.75;
        }
        
        health -= actualDamage;
        cout << getName() << " recibe " << RED_FORMAT << actualDamage << RESET_FORMAT << " puntos de daño ("
             << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
    }

    if (hiddenAgility != 0) {
        cout << getName() << " pierde su bonificación de agilidad oculta.\n" << endl;
        hiddenAgility = 0;
    }
}

void Warlock::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;
    
    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << "¡" << getName() << " intenta atacar pero no tiene arma disponible!\n" << endl;
    }
}

void Warlock::hide() {
    cout << getName() << " se fusiona con las sombras...\n" << endl;
    float toHeal = (totalHealth - health) * 0.075;
    heal(toHeal);
    hiddenAgility = agility * 3;
    cout << "¡" << getName() << " duplica su agilidad a " << PINK_FORMAT << hiddenAgility << RESET_FORMAT 
         << " para el próximo ataque!\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Necromancer::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;
    cout << getName() << " recupera " << GREEN_FORMAT << _heal << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Necromancer::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    cout << getName() << " intenta esquivar el ataque de " << attacker.getName() << "...\n" << endl;
    
    if (!dodgeAttack(agility + hiddenAgility)) {
        float oldHealth = health;
        health -= damage;
        cout << "Las sombras no protegen a " << getName() << " que recibe " << RED_FORMAT << damage << RESET_FORMAT 
             << " puntos de daño (" << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
    }

    if (hiddenAgility != 0) {
        cout << getName() << " pierde su bonificación de agilidad oculta.\n" << endl;
        hiddenAgility = 0;
    }
}

void Necromancer::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;
    
    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << "¡" << getName() << " no puede canalizar su ataque sin un arma!\n" << endl;
    }
}

void Necromancer::hide() {
    cout << getName() << " invoca esencias de los muertos...\n" << endl;
    float toHeal = (totalHealth - health) * 0.175;
    heal(toHeal);
    hiddenAgility = agility * 0.35;
    cout << getName() << " aumenta su agilidad en " << PINK_FORMAT << hiddenAgility << RESET_FORMAT 
         << " puntos para el próximo ataque.\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}