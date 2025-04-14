#include "warrior.h"

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

using namespace std;

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<float> dist(0.0, 1.0);

shared_ptr<Weapon> Warrior::chooseWeapon(shared_ptr<Weapon> leftHand, shared_ptr<Weapon> rightHand) const {
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

void Warrior::setName(const string& newName) {name = newName;}

bool Warrior::assignWeapon(shared_ptr<Weapon> weapon) {
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

bool Warrior::isHealthFull() const {return health == totalHealth;}

shared_ptr<Weapon> Warrior::getLeftHand() const {return leftHand;};

shared_ptr<Weapon> Warrior::getRightHand() const {return rightHand;};

float Warrior::getArmor() const {return armor;}

string Warrior::getName() const {return name;}

string Warrior::getType() const {return "Warrior";}

float Warrior::getTotalHealth() const {return totalHealth;}

float Warrior::getHealth() const {return health;}

float Warrior::getDamageBonus() const {return damageBonus;}

void Warrior::showCharacter() const {
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
    cout << "Armadura: " << BROWN_FORMAT << getArmor() << RESET_FORMAT << endl;
    cout << "Bonificación de daño: " << RED_FORMAT << getDamageBonus() << RESET_FORMAT << endl;
}

void Barbarian::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;
    cout << getName() << " recupera " << GREEN_FORMAT << _heal << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ")." << endl;
}

void Barbarian::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    float reduction = armor + reinforcedArmor;
    float oldHealth = health;
    float actualDamage = damage * (1 - reduction);
    
    health -= actualDamage;
    
    cout << getName() << " recibe el impacto de " << attacker.getName() << ".\n" << endl;
    cout << "Su resistencia física absorbe " << BROWN_FORMAT << (damage * reduction) << RESET_FORMAT << " puntos de daño.\n" << endl;
    cout << getName() << " pierde " << RED_FORMAT << actualDamage << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;

    if (reinforcedArmor != 0) {
        cout << getName() << " pierde su armadura reforzada tras el impacto.\n" << endl;
        reinforcedArmor = 0;
    }
}

void Barbarian::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        multiplier += weapon->getType() == "CombatWeapon" ? 0.35 : 0;
        if (multiplier > 1) {
            cout << getName() << " empuña " << weapon->getName() << " con maestría salvaje (+" << (multiplier - 1) * 100 << "% de daño).\n" << endl;
        }
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << "¡" << getName() << " no puede atacar sin un arma!\n" << endl;
    }
}

void Barbarian::reinforce() {
    cout << getName() << " entra en frenesí de combate...\n" << endl;
    
    float toHeal = (totalHealth - health) * 0.2;
    heal(toHeal);
    
    reinforcedArmor = armor * 0.85;
    
    cout << getName() << " refuerza su armadura con pieles y trofeos (+" << reinforcedArmor 
         << " de protección).\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Paladin::heal(const float _heal) {
    float oldHealth = health;
    float healAmount = _heal * 1.25;
    health += healAmount;

    cout << getName() << " canaliza luz sagrada y recupera " << GREEN_FORMAT << healAmount << RESET_FORMAT << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << "). Curación aumentada en 25%.\n" << endl;
}

void Paladin::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    float reduction = armor + reinforcedArmor;
    float oldHealth = health;
    float actualDamage = damage * (1 - reduction);
    
    health -= actualDamage;
    
    cout << getName() << " recibe el ataque de " << attacker.getName() << ".\n" << endl;
    cout << "Su armadura sagrada absorbe " << BROWN_FORMAT << (damage * reduction) << RESET_FORMAT << " puntos de daño.\n" << endl;
    cout << getName() << " sufre " << actualDamage << " puntos de daño ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;

    if (reinforcedArmor != 0) {
        cout << getName() << " pierde su bendición de protección temporal.\n" << endl;
        reinforcedArmor = 0;
    }
}

void Paladin::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        multiplier += !weapon->isRanged() ? 0.35 : 0;

        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << getName() << " invoca su fuerza interior pero no tiene arma para canalizarla.\n" << endl;
    }
}

void Paladin::reinforce() {
    cout << getName() << " invoca la bendición divina...\n" << endl;
    
    float toHeal = (totalHealth - health) * 0.2;
    heal(toHeal);
    
    reinforcedArmor = armor * 0.65;
    
    cout << getName() << " recibe una protección sagrada (+" << reinforcedArmor 
         << " de armadura).\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Knight::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;

    cout << getName() << " recupera " << _heal << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Knight::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    cout << getName() << " intenta desviar el ataque de " << attacker.getName() << "...\n" << endl;
    
    if (reboundAttack(reboundProbability)) {
        cout << "¡" << getName() << " contraataca y devuelve el golpe!\n" << endl;
        reboundDamage(attacker, damage);
    } else {
        float reduction = armor + reinforcedArmor;
        float oldHealth = health;
        float actualDamage = damage * (1 - reduction);
        
        health -= actualDamage;
        
        cout << "No logra desviar el ataque. Absorbe " << BROWN_FORMAT << damage * reduction << RESET_FORMAT << " del daño recibido, " << getName() << " pierde " << RED_FORMAT << actualDamage << RESET_FORMAT
             << " puntos de vida (" << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
    }

    if (reinforcedArmor != 0) {
        cout << getName() << " pierde su armadura reforzada tras el combate.\n" << endl;
        reinforcedArmor = 0;
    }
}

bool Knight::reboundAttack(const float reboundProbability) const {
    bool success = dist(gen) <= reboundProbability;
    if (success) {
        cout << "¡" << getName() << " ejecuta una perfecta técnica de contraataque!\n" << endl;
    }
    return success;
}

void Knight::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        cout << getName() << " realiza un ataque disciplinado con " << weapon->getName() << ".\n" << endl;
        
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << "Un caballero sin arma es como un rey sin corona. " << getName() << " no puede atacar.\n" << endl;
    }
}

void Knight::reinforce() {
    cout << getName() << " ajusta meticulosamente su postura defensiva...\n" << endl;
    float toHeal = (totalHealth - health) * 0.3;
    heal(toHeal);
    reinforcedArmor = armor * 0.5;
    cout << getName() << " optimiza su protección (+" << reinforcedArmor 
         << " de armadura).\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Knight::reboundDamage(Character& damageReceiver, const float damage) {
    cout << getName() << " ejecuta una técnica de contraataque precisa.\n" << endl;

    damageReceiver.receiveDamage(damage, *this, "CombatWeapon", false, false);
    return;
}

float Knight::getReboundProbability() const {return reboundProbability;}

void Mercenary::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;

    cout << getName() << " utiliza primeros auxilios y recupera " << _heal << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Mercenary::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    float reduction = armor + reinforcedArmor;
    
    if (type == "CombatWeapon") {
        cout << getName() << " utiliza su conocimiento de armas para reducir el impacto.\n" << endl;
        reduction += 0.35;
    }
    
    float oldHealth = health;
    float actualDamage = damage * (1 - reduction);
    
    health -= actualDamage;
    
    cout << getName() << " absorbe " << BROWN_FORMAT << damage * reduction << RESET_FORMAT << " por lo tanto, sufre " << RED_FORMAT << actualDamage << RESET_FORMAT << " puntos de daño ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;

    if (reinforcedArmor != 0) {
        cout << getName() << " pierde su protección adicional.\n" << endl;
        reinforcedArmor = 0;
    }
}

void Mercenary::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        cout << getName() << " utiliza " << weapon->getName() << " con eficiencia profesional.\n" << endl;
        
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << getName() << " busca un arma pero no encuentra ninguna disponible.\n" << endl;
    }
}

void Mercenary::reinforce() {
    cout << getName() << " aplica rápidamente técnicas aprendidas en el campo de batalla...\n" << endl;

    float toHeal = (totalHealth - health) * 0.2;
    heal(toHeal);

    reinforcedArmor = armor * 2;

    cout << getName() << " improvisa protecciones adicionales (+" << reinforcedArmor 
         << " de armadura).\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}

void Gladiator::heal(const float _heal) {
    float oldHealth = health;
    health += _heal;
    cout << getName() << " recupera fuerzas y restaura " << _heal << " puntos de vida ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;
}

void Gladiator::receiveDamage(const float damage, Character& attacker, const string type, const bool ranged, const bool isSpecial) {
    float reduction = armor + reinforcedArmor;
    
    if (isSpecial) {
        cout << "¡" << getName() << " reconoce el ataque especial y se prepara!\n" << endl;
        reduction += 0.35;
    }
    
    float oldHealth = health;
    float actualDamage = damage * (1 - reduction);
    
    health -= actualDamage;
    
    cout << getName() << " absorbe " << BROWN_FORMAT << damage * reduction << RESET_FORMAT << " por lo tanto, sufre " << RED_FORMAT << actualDamage << RESET_FORMAT << " puntos de daño ("
         << GREEN_FORMAT << oldHealth << RESET_FORMAT << " → " << GREEN_FORMAT << health << RESET_FORMAT << ").\n" << endl;

    if (reinforcedArmor != 0) {
        cout << getName() << " pierde su armadura de combate reforzada.\n" << endl;
        reinforcedArmor = 0;
    }
}

void Gladiator::attack(Character& damageReceiver, shared_ptr<Weapon> chosenWeapon) {
    float multiplier = 1 + damageBonus;

    if (!chosenWeapon) {chosenWeapon = chooseWeapon(leftHand, rightHand);}
    
    if (auto weapon = chosenWeapon) {
        cout << getName() << " hace gala de su maestría con " << weapon->getName() << ".\n" << endl;
        
        weapon->attack(damageReceiver, multiplier);
    } else {
        cout << getName() << " intenta atacar desarmado pero no es efectivo.\n" << endl;
    }
}

void Gladiator::reinforce() {
    cout << getName() << " adopta una postura defensiva de la arena...\n" << endl;

    float toHeal = (totalHealth - health) * 0.125;
    heal(toHeal);

    reinforcedArmor = armor * 1.5;
    
    cout << getName() << " maximiza su defensa para el próximo enfrentamiento (+" << reinforcedArmor 
         << " de armadura).\n" << endl;
    
    if (leftHand) {
        cout << endl << getName() << " repara su arma en la mano izquierda:" << endl;
        leftHand->repair();
    }
    if (rightHand) {
        cout << endl << getName() << " repara su arma en la mano derecha:" << endl;
        rightHand->repair();
    }
}