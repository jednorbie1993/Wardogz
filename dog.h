#ifndef DOG_H
#define DOG_H

struct Dog {
    char name[50];
    int hp;
    int attack;
    int speed;
};

void createDog(struct Dog *d);
void printDog(struct Dog d);
void battle(struct Dog *player);
void showHPBar(int hp, int maxHp);

#endif