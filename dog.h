#ifndef DOG_H
#define DOG_H

#define MAX_SKILLS 10
#define MAX_STAT 999
#define MIN_STAT 0

extern int systemLog;
extern int animationOn;

// ================= SKILL TYPES =================
typedef enum {
    SKILL_DAMAGE,
    SKILL_HEAL,
    SKILL_BUFF,
    SKILL_DEBUFF
} SkillType;

// ================= SKILL IDs =================
typedef enum {
    SKILL_NONE = -1,
    SKILL_ATTACK,
    SKILL_BITE,
    SKILL_SCRATCH,
    SKILL_QUICK_DASH,
    SKILL_FLASH_STEP,
    SKILL_HEAVY_BITE,
    SKILL_SAVAGE_FANG,
    SKILL_IRON_GUARD,
    SKILL_SURE_STRIKE,
    SKILL_LAST_STAND,

    // 🔥 WILD SKILLS (IBINALIK)
    SKILL_PACK_ATTACK = 20,
    SKILL_AMBUSH,
    SKILL_HOWL_DEBUFF,
    SKILL_FERAL_RUSH

} SkillID;

// ================= SKILL STRUCT =================
typedef struct {
    char name[30];
    int power;
    int cost;
    SkillType type;
    int accuracy;
    SkillID id;
    int cooldown;
    int cdLeft;
    int aiScore;
} Skill;

// ================= DOG STRUCT =================
typedef struct {
    char name[50];

    int hp, maxHP;
    int attack, defense, speed;
    int accuracy, intelligence;

    int fatigue;
    int maxFatigue;

    int isConfused;
    int confuseTurns;

    int isBleeding;
    int bleedTurns;
    int bleedDamage;

    int isStunned;
    int stunTurns;

    int accTemp;
    int accDebuffTurns;
    int accuracyModifier;

    int numSkills;                // 🔥 IBINALIK
    int isCountering;
    int counterDamage;

    int sparringProgress[5];      // 🔥 IBINALIK

    Skill skills[MAX_SKILLS];
    int skillCount;

    int equipped[4];              // 🔥 IBINALIK

} Dog;

// ================= CORE FUNCTIONS =================
void createDog(Dog *d);
void printDog(Dog d);
int battle(Dog *player, int zoneIndex, int progress[]);
void displayBattleStatus(Dog player, Dog enemy);
void trainDog(Dog *d, int type);

void waitForEnter();              // 🔥 IBINALIK
void pauseAndClear();             // 🔥 IBINALIK

void playerAttack(Dog *player, Dog *enemy);
int playerTurn(Dog *player, Dog *enemy, int *defending);
void skillMenu(Dog *d);

int clamp(int value);
int clampFatigue(int f, int max);
int getFatiguePenalty(int fatigue);
int isCritical(int hp, int maxHP);

// ================= SKILL SYSTEM =================
int hasSkill(Dog *d, char name[]);
void checkSkillUnlock(Dog *d);
void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage);

// ================= ENEMY =================
void createEnemy(Dog *e);
void enemyTurn(Dog *player, Dog *enemy, int *defending);

// ================= WILD SKILLS =================
int usePackAttack(Dog *user, Dog *target);
int useAmbush(Dog *user, Dog *target);
int useHowlDebuff(Dog *user, Dog *target);
int useFeralRush(Dog *user, Dog *target);

#endif