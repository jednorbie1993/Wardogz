#ifndef STAT_H
#define STAT_H

#include "dog.h"

int getGrowthGain(int stat);
int clamp(int value);
int clampFatigue(int f, int max);
int getFatiguePenalty(int fatigue);
int randRange(int min, int max);

void applyStatGain(Dog *d, int atk, int hp, int def, int spd, int acc, int intel);
void applyBattleStatGain(Dog *d);

#endif