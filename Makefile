CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

EXE_TURNOS = juego_turnos
EXE_RPS = juego_rps

EJ1_DIR = Ejercicio_1
EJ2_DIR = Ejercicio_2
EJ3_DIR = Ejercicio_3

SOURCES = $(EJ2_DIR)/characterFactory.cpp \
          $(EJ1_DIR)/sorcerer.cpp \
          $(EJ1_DIR)/warrior.cpp \
          $(EJ1_DIR)/magicItem.cpp \
          $(EJ1_DIR)/combatWeapon.cpp

MAIN_TURNOS = Ejercicio_3/mainShifts.cpp
MAIN_RPS = Ejercicio_3/mainRPS.cpp

all: $(EXE_TURNOS) $(EXE_RPS)

$(EXE_TURNOS): $(SRC_1) $(SRC_2) $(MAIN_TURNOS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXE_RPS): $(SRC_1) $(SRC_2) $(MAIN_RPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXE_TURNOS) $(EXE_RPS)

.PHONY: all clean