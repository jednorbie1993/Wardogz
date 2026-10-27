#ifndef RPG_H
#define RPG_H
#include <stdint.h>
#include "dog.h"
#define RPG_GEAR_COUNT 38
#define RPG_ITEM_COUNT 6
#define RPG_BOSS_COUNT 26
#define RPG_VERSION 1
#define RPG_LIMIT 1000000000u
/* Serialized separately: never add fields to the legacy Dog/GameData structs. */
typedef struct {
    uint32_t xp, coins, owned[RPG_GEAR_COUNT];
    int32_t worn[6], active[2];
    uint32_t items[RPG_ITEM_COUNT], claimed, pending;
} RpgState;
typedef struct {
    const char *name;
    int slot, level, rank, price, atk, def, spd, effect, skill, growth;
} Gear;
enum { RPG_POISON=1, RPG_BLEED, RPG_STUN, RPG_PARALYSIS };
extern RpgState rpg;
extern const Gear rpgGear[RPG_GEAR_COUNT];
void rpgInit(void);
void rpgBind(Dog *player);
int rpgValidate(const RpgState *state);
int rpgLevel(void);
int rpgRank(char rank);
void rpgMigrate(const Dog *player, const int progress[21]);
int rpgClaim(void);
void rpgReward(Dog *player, int zone, int enemyIndex, char rank);
int rpgEquip(int id);
int rpgSelect(int first, int second);
int rpgBuy(Dog *player, int id, int consumable);
int rpgSell(int id, int consumable);
void rpgGrant(int id);
void rpgBegin(Dog *player);
void rpgEnd(Dog *player);
int rpgInBattle(void);
int rpgGrowth(Dog *player);
void rpgOnHit(Dog *user, Dog *target);
int rpgEnemyTurn(Dog *enemy);
void rpgPrintSkills(void);
int rpgUseSkill(Dog *player, Dog *enemy, int choice);
int rpgUseItem(Dog *player, int id);
int rpgItemMenu(Dog *player);
void rpgMenu(Dog *player);
#endif
