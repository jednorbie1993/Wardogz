# Wardogz

A console-based RPG game written in C where players train, upgrade, and battle dogs through a turn-based combat system.

---

## Overview

Wardogz is a personal project created to practice C programming, modular design, and game development fundamentals.

Players raise a dog, improve its abilities, challenge enemies, unlock new areas, and participate in sparring battles. The project focuses on learning software organization through multiple source files and game systems rather than advanced graphics.

The game demonstrates:

* Structures and pointers
* Modular programming using multiple `.c` and `.h` files
* Turn-based combat mechanics
* Enemy AI behavior
* Progression and unlock systems
* Menu-driven game design

---

## Current Features

### Battle System

* Turn-based combat
* Multiple enemy types
* Damage calculation and combat outcomes
* Enemy personalities and AI decision making

### Character Progression

* Dog leveling system
* Stat growth and upgrades
* Unlockable content

### Stages

* Multiple battle stages
* Zone progression system
* Locked areas that unlock through completion

### Sparring Mode

* Practice battles against unique opponents
* Character-specific sparring encounters
* Progress tracking and rewards

### Dialogue System

* Story and battle dialogue
* Event and encounter messages

### Project Structure

```text
Wardogz/
│
├── enemies/
├── stages/
├── dialogue/
├── sparring/
│
├── main.c
├── battle.c
├── dog.c
└── other core files
```

---

## Planned Improvements

* Save and load system
* Expanded inventory system
* Additional sparring characters
* Boss encounters
* More stages and story content
* Improved terminal interface
* Additional skills and status effects

---

## Build

```bash
gcc *.c enemies/*.c stages/*.c dialogue/*.c sparring/*.c -o wardogz.exe
```

## Run

```bash
wardogz.exe
```

---

## Purpose

Wardogz was developed as a learning project while studying C programming. The goal is to gain practical experience with software design, code organization, debugging, and game system implementation.
