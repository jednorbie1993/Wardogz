# Wardogz

A console-based RPG game written in C where players train, upgrade, and battle dogs through a turn-based combat system.

---

## Overview

Wardogz is a personal project created to practice C programming, modular design, and game development fundamentals.

Players raise a dog, improve its abilities, challenge enemies, unlock new areas, participate in sparring battles, and compete in the arena. The project focuses on learning software organization through multiple source files and game systems rather than advanced graphics.

The game demonstrates:

* Structures and pointers
* Modular programming using multiple `.c` and `.h` files
* Turn-based combat mechanics
* Enemy AI behavior
* Progression and unlock systems
* Save and load functionality
* Menu-driven game design

---

## Current Features

### Battle System

* Turn-based combat
* Multiple enemy types
* Damage calculation and combat outcomes
* Enemy personalities and AI decision making
* Skills and status effects
* Battle dialogue and encounter events

### Character Progression

* Dog leveling system
* Stat growth and upgrades
* Unlockable skills and content
* Progress tracking

### Stages

* Multiple battle stages
* Zone progression system
* Locked areas that unlock through completion
* Story and enemy progression across stages

### Sparring Mode

* Practice battles against unique opponents
* Character-specific sparring encounters
* Sparring AI and skill systems
* Status effects and unlock rewards
* Progress tracking

### Arena Mode

* Separate arena battle system
* Multiple arena enemy classes
* Progressive arena opponents
* Higher-level combat challenges

### Dialogue System

* Story and battle dialogue
* Event and encounter messages
* Stage-specific dialogue

### Save and Load System

* Save game progress
* Load existing progress
* Persistent player data through `save.dat`

---

## Project Structure

```text
Wardogz/
│
├── arena/
├── dialogue/
├── enemies/
├── guide/
├── sparring/
│   └── characters/
├── stages/
│
├── battle.c
├── battle.h
├── console.c
├── console.h
├── dog.c
├── dog.h
├── main.c
├── save.c
├── save.h
├── skill.c
├── skill.h
├── stat.c
├── stat.h
├── build.bat
├── makefile
└── README.md
```

---

## Planned Improvements

* Expanded inventory system
* Additional sparring characters
* Additional arena opponents
* More stages and story content
* Improved terminal interface
* Additional skills and status effects
* Further balancing and gameplay polish

---

## Build

Using `mingw32-make`:

```bash
mingw32-make
```

Or use:

```bash
build.bat
```

For a clean rebuild:

```bash
mingw32-make clean
mingw32-make
```

---

## Run

```bash
mingw32-make run
```

Or run the executable directly:

```bash
wardogz.exe
```

---

## Purpose

Wardogz was developed as a learning project while studying C programming. The goal is to gain practical experience with software design, code organization, debugging, modular programming, and game system implementation.
