# Trabajo Práctico 1 - Paradigmas de Programación

**Alumno:** Federico Pizarro  
**Ingeniería en Inteligencia Artificial**
**Materia:** Paradigmas de Programación

---

## ✨ Descripción del Proyecto

Este proyecto implementa un juego de rol en C++ utilizando principios de programación orientada a objetos. Se desarrollaron jerarquías de personajes y armas mediante interfaces, clases abstractas y derivadas, permitiendo modelar combates entre personajes en dos modalidades:

- **Modo por turnos clásico**
- **Modo piedra, papel o tijera (PPT)**

El juego permite al usuario crear su personaje, seleccionar armas, y enfrentarse a enemigos generados aleatoriamente.

---

## ✍️ Consigna y Objetivos

El objetivo fue aplicar conceptos clave de POO como:

- Interfaces y clases abstractas  
- Herencia y polimorfismo  
- Smart pointers (`shared_ptr`, `weak_ptr`)  
- Separación en módulos (`.h` / `.cpp`)  

Y además generar:

- Diagramas UML  
- Informe técnico documentado  
- Makefile funcional para compilar el proyecto

---

## 🔧 Compilación

Para compilar el proyecto se utiliza un archivo `Makefile` que genera dos ejecutables:

- `juego_turnos`: versión clásica por turnos (usa `mainShifts.cpp`)
- `juego_rps`: versión con lógica de Piedra, Papel o Tijera (usa `mainRPS.cpp`)

Ambos se compilan ejecutando el comando:

```bash
make
