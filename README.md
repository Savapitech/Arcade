# Arcade – Epitech Project

**Group Leader:** savinien.petitjean@epitech.eu  

## Introduction

Welcome to our Arcade project, developed during our second year at Epitech Rennes.  
This project was carried out in a group of three students, and part of the work involved sharing our architecture with another group.

The objective of this project is to recreate an arcade environment. It is primarily a graphical project, with a strong focus on software architecture and modular design.

---

## Project Overview

The project is divided into three main parts:

- The Core  
- The Graphical Libraries  
- The Game Libraries  

The Core acts as the central element of the project and is responsible for managing the interaction between the different libraries.

---

## Architecture

One of the key aspects of this project is the ability to switch graphical and game libraries at runtime.

Both the graphical libraries and the game libraries are implemented as dynamic shared objects (`.so`). The Core has been designed in such a way that changing a library does not cause issues, ensuring flexibility and stability during execution.

This architecture allows the program to dynamically load and unload libraries without restarting the application.

---

## Extensibility

It is possible to develop new graphical or game libraries.

To do so, you simply need to create a new class that implements the corresponding interface (game or graphical). Once implemented and compiled as a shared library, it can be loaded by the Core at runtime.

---

## Conclusion

This project highlights the importance of modular architecture and dynamic loading in software development. It provides a flexible foundation where new features can be added without modifying the Core system.
