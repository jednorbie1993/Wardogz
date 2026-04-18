#ifndef DOG_H
#define DOG_H

typedef struct {
    char name[50];
    int hp;
    int maxHP;
    int attack;
    int speed;
} Dog;

// prototypes (WALANG struct Dog dito!)
void createDog(Dog *d);
void printDog(Dog d);
void battle(Dog *player);
void displayBattleStatus(Dog player, Dog enemy);
void waitForEnter();
void showHPBarPlayer(int hp, int maxHp);
void pauseAndClear();

#endif