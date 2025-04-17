#include "../Ejercicio_2/characterFactory.h"
#include "../Ejercicio_1/sorcerer.h"
#include "../Ejercicio_1/warrior.h"
#include "../Ejercicio_1/magicItem.h"

#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <limits>

using namespace std;

const string RED_FORMAT = "\033[1;31m";
const string GREEN_FORMAT = "\033[1;32m";
const string YELLOW_FORMAT = "\033[33m";
const string BLUE_FORMAT = "\033[1;34m";
const string MAGENTA_FORMAT = "\033[35m";
const string CIAN_FORMAT = "\033[1;36m";
const string GRAY_FORMAT = "\033[90m";
const string RESET_FORMAT = "\033[0m";

int getRandInt(const int floor, const int ceiling) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(floor, ceiling);

    return dist(gen);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pressEnterToContinue() {
    cout << GRAY_FORMAT << "\nPresiona Enter para continuar..." << RESET_FORMAT;
    getchar();
}

const string getRandCharacterType() {
    const string types[] = {"Hechicero", "Conjurador", "Brujo", "Nigromante",
                            "Bárbaro", "Paladín", "Caballero", "Mercenario", "Gladiador"};
    return types[getRandInt(0, 8)];
}

const string getRandWeaponType() {
    const string types[] = {"Bastón Mágico", "Libro de Hechizos", "Poción", "Amuleto", 
                           "Hacha Simple", "Hacha Doble", "Espada", "Lanza", "Garrote"};
    return types[getRandInt(0, 8)];
}

shared_ptr<Character> createRandomEnemy() {
    string characterType = getRandCharacterType();
    
    const int weaponsCount = getRandInt(1, 2);
    
    if (weaponsCount == 1) {
        return CharacterFactory::createArmedCharacter(characterType, getRandWeaponType());
    } else {
        return CharacterFactory::createArmedCharacter(characterType, getRandWeaponType(), getRandWeaponType());
    }
}

void showDetailedCharacterInfo(shared_ptr<Character> character) {
    cout << BLUE_FORMAT << "\n==== INFORMACIÓN DEL PERSONAJE ====" << RESET_FORMAT << endl;
    character->showCharacter();
    cout << BLUE_FORMAT << "================================\n" << RESET_FORMAT << endl;
}

void showDetailedWeaponInfo(shared_ptr<Character> character) {
    cout << BLUE_FORMAT << "\n==== INFORMACIÓN DE ARMAS ====" << RESET_FORMAT << endl;
    
    if (auto leftWeapon = character->getLeftHand()) {
        cout << "\nARMA IZQUIERDA:" << endl;
        leftWeapon->showWeapon();
    } else {
        cout << "\nMano izquierda vacía" << endl;
    }
    
    if (auto rightWeapon = character->getRightHand()) {
        cout << "\nARMA DERECHA:" << endl;
        rightWeapon->showWeapon();
    } else {
        cout << "\nMano derecha vacía" << endl;
    }
    
    cout << BLUE_FORMAT << "============================" << RESET_FORMAT << endl;
}

void showBattleStatus(shared_ptr<Character> player, shared_ptr<Character> enemy) {
    cout << BLUE_FORMAT << "\n==== ESTADO DE BATALLA ====" << RESET_FORMAT << endl;
    cout << "TÚ: " << player->getName() << " - Vida: " << GREEN_FORMAT << player->getHealth() << RESET_FORMAT << "/" << GREEN_FORMAT << player->getTotalHealth() << RESET_FORMAT << endl;
    
    cout << "RIVAL: " << enemy->getName() << " - Vida: " << GREEN_FORMAT << enemy->getHealth() << RESET_FORMAT << "/" << GREEN_FORMAT << enemy->getTotalHealth() << RESET_FORMAT << endl;
    cout << BLUE_FORMAT << "===========================" << RESET_FORMAT << endl;

    pressEnterToContinue();
}

shared_ptr<Character> createPlayerCharacter() {
    int choice;
    string characterType;
    
    cout << BLUE_FORMAT << "\n==== CREACIÓN DE PERSONAJE ====\n" << RESET_FORMAT << endl;
    cout << "Elige el tipo de personaje:\n" << endl;
    cout << "1. Hechicero (Daño mágico aumentado)" << endl;
    cout << "2. Conjurador (Potencia ataques especiales)" << endl;
    cout << "3. Brujo (Resistente a daño mágico)" << endl;
    cout << "4. Nigromante (Potencia ataques a distancia)" << endl;
    cout << "5. Bárbaro (Daño cuerpo a cuerpo aumentado)" << endl;
    cout << "6. Paladín (Aumenta curación)" << endl;
    cout << "7. Caballero (Puede rebotar ataques)" << endl;
    cout << "8. Mercenario (Resistente a daño físico)" << endl;
    cout << "9. Gladiador (Resistente a ataques especiales)" << endl;
    cout << ">> ";
    cin >> choice;
    
    switch (choice) {
        case 1: characterType = "Hechicero"; break;
        case 2: characterType = "Conjurador"; break;
        case 3: characterType = "Brujo"; break;
        case 4: characterType = "Nigromante"; break;
        case 5: characterType = "Bárbaro"; break;
        case 6: characterType = "Paladín"; break;
        case 7: characterType = "Caballero"; break;
        case 8: characterType = "Mercenario"; break;
        case 9: characterType = "Gladiador"; break;
        default: 
            cout << "Opción inválida. Se seleccionará Hechicero por defecto." << endl;
            characterType = "Hechicero"; 
            break;
    }
    
    cout << "\nElige un arma para la mano izquierda:\n" << endl;
    cout << "1. Bastón Mágico (Daño especial basado en maná)" << endl;
    cout << "2. Libro de Hechizos (Alto daño base, especiales potentes)" << endl;
    cout << "3. Poción (Cura al portador, bajo daño)" << endl;
    cout << "4. Amuleto (Alterna entre daño cuerpo a cuerpo y a distancia)" << endl;
    cout << "5. Hacha Simple (Aumenta daño con el tiempo)" << endl;
    cout << "6. Hacha Doble (Alto daño base, consume más durabilidad)" << endl;
    cout << "7. Espada (Se repara durante ataques especiales)" << endl;
    cout << "8. Lanza (Alto daño a distancia, inútil un turno después)" << endl;
    cout << "9. Garrote (Aumenta daño gradualmente)" << endl;
    cout << ">> ";
    cin >> choice;
    
    string leftWeaponType;
    string rightWeaponType;

    switch (choice) {
        case 1: leftWeaponType = "Bastón Mágico"; break;
        case 2: leftWeaponType = "Libro de Hechizos"; break;
        case 3: leftWeaponType = "Poción"; break;
        case 4: leftWeaponType = "Amuleto"; break;
        case 5: leftWeaponType = "Hacha Simple"; break;
        case 6: leftWeaponType = "Hacha Doble"; break;
        case 7: leftWeaponType = "Espada"; break;
        case 8: leftWeaponType = "Lanza"; break;
        case 9: leftWeaponType = "Garrote"; break;
        default: leftWeaponType = "Bastón Mágico"; break;
    }
    
    cout << "\n¿Quieres un arma en la mano derecha? (s/n): " << endl;
    char wantSecondWeapon;
    cin >> wantSecondWeapon;
    
    if (wantSecondWeapon == 's' || wantSecondWeapon == 'S') {
        cout << "\nElige un arma para la mano derecha:\n" << endl;
        cout << "1. Bastón Mágico (Daño especial basado en maná)" << endl;
        cout << "2. Libro de Hechizos (Alto daño base, especiales potentes)" << endl;
        cout << "3. Poción (Cura al portador, bajo daño)" << endl;
        cout << "4. Amuleto (Alterna entre daño cuerpo a cuerpo y a distancia)" << endl;
        cout << "5. Hacha Simple (Aumenta daño con el tiempo)" << endl;
        cout << "6. Hacha Doble (Alto daño base, consume más durabilidad)" << endl;
        cout << "7. Espada (Se repara durante ataques especiales)" << endl;
        cout << "8. Lanza (Alto daño a distancia, inútil un turno después)" << endl;
        cout << "9. Garrote (Aumenta daño gradualmente)" << endl;
        cout << ">> ";
        cin >> choice;
        switch (choice) {
            case 1: rightWeaponType = "Bastón Mágico"; break;
            case 2: rightWeaponType = "Libro de Hechizos"; break;
            case 3: rightWeaponType = "Poción"; break;
            case 4: rightWeaponType = "Amuleto"; break;
            case 5: rightWeaponType = "Hacha Simple"; break;
            case 6: rightWeaponType = "Hacha Doble"; break;
            case 7: rightWeaponType = "Espada"; break;
            case 8: rightWeaponType = "Lanza"; break;
            case 9: rightWeaponType = "Garrote"; break;
            default: rightWeaponType = "Espada"; break;
        }
    }

    auto character = CharacterFactory::createArmedCharacter(characterType, leftWeaponType, rightWeaponType);
    
    string characterName;
    cout << "\nIngresa el nombre de tu personaje:\n>> ";
    clearInputBuffer();
    getline(cin, characterName);
    
    character->setName(characterName);
    
    return character;
}

void playerTurn(weak_ptr<Character> player, weak_ptr<Character> enemy, bool& battleOver) {
    auto playerPtr = player.lock();
    auto enemyPtr = enemy.lock();
    
    if (!playerPtr || !enemyPtr) {
        cout << RED_FORMAT << "Error: personaje no válido" << RESET_FORMAT << endl;
        return;
    }
    
    int choice;
    
    cout << BLUE_FORMAT << "\n==== TU TURNO ====\n" << RESET_FORMAT << endl;
    cout << "¿Qué acción quieres realizar?\n" << endl;
    cout << "1. Atacar" << endl;
    
    if (auto sorcerer = dynamic_pointer_cast<Sorcerer>(playerPtr)) {
        cout << "2. Esconderse y reparar armas (aumenta agilidad y cura)" << endl;
    } else if (auto warrior = dynamic_pointer_cast<Warrior>(playerPtr)) {
        cout << "2. Reforzarse y reparar armas (aumenta armadura y cura)" << endl;
    }
    
    cout << "3. Mostrar información detallada de personaje y armas" << endl;
    cout << "4. Rendirse" << endl;
    
    cout << ">> ";
    cin >> choice;
    
    if (choice == 1) {
        playerPtr->attack(*enemyPtr);
    } else if (choice == 2) {
        if (auto sorcerer = dynamic_pointer_cast<Sorcerer>(playerPtr)) {
            sorcerer->hide();
        } else if (auto warrior = dynamic_pointer_cast<Warrior>(playerPtr)) {
            warrior->reinforce();
        }
    } else if (choice == 3) {
        showDetailedCharacterInfo(playerPtr);

        showDetailedWeaponInfo(playerPtr);

        clearInputBuffer();
        
        pressEnterToContinue();
        
        playerTurn(player, enemy, battleOver);
        return;
    } else if (choice == 4) {
        cout << YELLOW_FORMAT << "\n¿Estás seguro que quieres rendirte? (s/n): " << RESET_FORMAT;
        char confirm;
        cin >> confirm;
        
        if (confirm == 's' || confirm == 'S') {
            cout << RED_FORMAT << "\n¡Te has rendido! " << enemyPtr->getName() << " es el vencedor." << RESET_FORMAT << endl;
            battleOver = true;
        } else {
            cout << "Continúas la batalla." << endl;
            playerTurn(player, enemy, battleOver);
            return;
        }
    }
    
    clearInputBuffer();
}

void enemyTurn(weak_ptr<Character> enemy, weak_ptr<Character> player) {
    auto playerPtr = player.lock();
    auto enemyPtr = enemy.lock();
    
    if (!playerPtr || !enemyPtr) {
        cout << RED_FORMAT << "Error: personaje no válido" << RESET_FORMAT << endl;
        return;
    }

    cout << BLUE_FORMAT << "\n==== TURNO DEL RIVAL ====\n" << RESET_FORMAT << endl;

    shared_ptr<Weapon> rightHand = enemyPtr->getRightHand();
    shared_ptr<Weapon> leftHand = enemyPtr->getLeftHand();
    shared_ptr<Weapon> chosenWeapon = nullptr;
    
    if (leftHand && rightHand) {
        chosenWeapon = getRandInt(0, 1) == 0 ? leftHand : rightHand;
    } else if (leftHand) {
        chosenWeapon = leftHand;
    } else if (rightHand) {
        chosenWeapon = rightHand;
    }

    bool canAttack = false;

    if (chosenWeapon) {
        string weaponType = chosenWeapon->getType();
        if (weaponType == "CombatWeapon") {
            if (chosenWeapon->getDurability() >= chosenWeapon->getDurabilityCost()) {canAttack = true;}
        } else if (weaponType == "MagicItem") {
            auto magicItem = dynamic_pointer_cast<MagicItem>(chosenWeapon);
            if (magicItem && magicItem->getDurability() >= magicItem->getDurabilityCost() && magicItem->getMana() >= magicItem->getManaCost()) {canAttack = true;}
        }
    }
    
    if (getRandInt(1, 10) <= 8 && canAttack) {
        cout << enemyPtr->getName() << " decide atacar!" << endl;

        enemyPtr->attack(*playerPtr, chosenWeapon);
    } else {
        if (auto sorcerer = dynamic_pointer_cast<Sorcerer>(enemyPtr)) {
            cout << enemyPtr->getName() << " se esconde y canaliza poder..." << endl;
            sorcerer->hide();
        } else if (auto warrior = dynamic_pointer_cast<Warrior>(enemyPtr)) {
            cout << enemyPtr->getName() << " refuerza su posición..." << endl;
            warrior->reinforce();
        }
    }
}

void showRules() {
    cout << BLUE_FORMAT << "\n==== REGLAS DEL JUEGO ====\n" << RESET_FORMAT << endl;
    cout << "1. Se generá un enemigo aleatorio que te desafiará." << endl;
    cout << "2. Es una batalla por turnos. (Se elige de forma aleatorio quien comienza)." << endl;
    cout << "3. En tu turno, podes atacar o usar tu habilidad especial (Esconderte o reforzarte)." << endl;
    cout << "4. Cada arma tiene características únicas y ataques especiales." << endl;
    cout << "5. El combate termina cuando la vida de uno de los personajes llega a 0." << endl;
    cout << "6. Los hechiceros pueden esconderse para aumentar su agilidad y curarse." << endl;
    cout << "7. Los guerreros pueden reforzarse para aumentar su armadura y curarse." << endl;

    pressEnterToContinue();
}

int main() {
    int menuChoice;
    bool exitGame = false;
    
    while (!exitGame) {
        cout << BLUE_FORMAT << "\n===== JUEGO DE ROL =====\n" << RESET_FORMAT << endl;
        cout << "1. Iniciar nueva partida" << endl;
        cout << "2. Ver reglas" << endl;
        cout << "3. Salir" << endl << endl;
        cout << "Elige una opción:\n>> ";
        cin >> menuChoice;
        
        switch (menuChoice) {
            case 1: {
                auto enemy = createRandomEnemy();
                cout << "\n¡Has sido desafiado por un rival!" << endl << endl;
                enemy->showCharacter();
                
                auto player = createPlayerCharacter();
                cout << "\nTu personaje ha sido creado:\n" << endl;
                player->showCharacter();

                pressEnterToContinue();
                
                bool battleOver = false;
                bool playerTurnFirst = getRandInt(0, 1) == 0;
                
                cout << "\n¡QUE COMIENCE EL COMBATE!\n" << endl;
                if (playerTurnFirst) {
                    cout << "¡Tienes la iniciativa y atacas primero!" << endl;
                } else {
                    cout << "¡Tu rival tiene la iniciativa y ataca primero!" << endl;
                }
                                
                while (!battleOver) {
                    showBattleStatus(player, enemy);
                    
                    if (playerTurnFirst) {
                        playerTurn(player, enemy, battleOver);
                        
                        if (enemy->getHealth() <= 0) {
                            cout << GREEN_FORMAT << "\n¡VICTORIA! Has derrotado a " << enemy->getName() << "." << RESET_FORMAT << endl;
                            battleOver = true;
                            continue;
                        }

                        pressEnterToContinue();
                                                
                        enemyTurn(enemy, player);
                        
                        if (player->getHealth() <= 0) {
                            cout << RED_FORMAT << "\n¡DERROTA! Has sido derrotado por " << enemy->getName() << "." << RESET_FORMAT << endl;
                            battleOver = true;
                            continue;
                        }
                    } else {
                        enemyTurn(enemy, player);
                        
                        if (player->getHealth() <= 0) {
                            cout << RED_FORMAT << "\n¡DERROTA! Has sido derrotado por " << enemy->getName() << "." << RESET_FORMAT << endl;
                            battleOver = true;
                            continue;
                        }

                        pressEnterToContinue();
                                                
                        playerTurn(player, enemy, battleOver);
                        
                        if (enemy->getHealth() <= 0) {
                            cout << GREEN_FORMAT << "\n¡VICTORIA! Has derrotado a " << enemy->getName() << "." << RESET_FORMAT << endl;
                            battleOver = true;
                            continue;
                        }
                    }
                    
                    pressEnterToContinue();
                }
                
                cout << "\n¿Quieres volver al menú principal? (s/n): ";
                char backToMenu;
                cin >> backToMenu;
                
                if (backToMenu != 's' && backToMenu != 'S') {
                    exitGame = true;
                }
                
                break;
            }
            case 2:
                showRules();
                break;
            case 3:
                exitGame = true;
                break;
            default:
                cout << RED_FORMAT << "Opción no válida. Intenta de nuevo." << RESET_FORMAT << endl;
        }
    }
    
    cout << "\n¡Gracias por jugar! ¡Hasta la próxima!" << endl;
    return 0;
}