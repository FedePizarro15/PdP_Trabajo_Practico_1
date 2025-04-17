CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SOURCES = Ejercicio_1/*.cpp Ejercicio_2/characterFactory.cpp

MAIN_TURNOS = Ejercicio_3/mainShifts.cpp
MAIN_RPS = Ejercicio_3/mainRPS.cpp

EXE_TURNOS = juego_turnos
EXE_RPS = juego_rps

all: $(EXE_TURNOS) $(EXE_RPS)

$(EXE_TURNOS): $(SOURCES) $(MAIN_TURNOS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXE_RPS): $(SOURCES) $(MAIN_RPS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXE_TURNOS) $(EXE_RPS)

.PHONY: all clean