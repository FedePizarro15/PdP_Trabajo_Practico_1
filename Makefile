CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

TARGET = juego

EJ1_DIR = Ejercicio_1
EJ2_DIR = Ejercicio_2
EJ3_DIR = Ejercicio_3

SOURCES = $(EJ3_DIR)/main.cpp \
          $(EJ2_DIR)/characterFactory.cpp \
          $(EJ1_DIR)/sorcerer.cpp \
          $(EJ1_DIR)/warrior.cpp \
          $(EJ1_DIR)/magicItem.cpp \
          $(EJ1_DIR)/combatWeapon.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean