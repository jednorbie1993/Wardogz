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
    SKILL_PACK_ATTACK = 20,    // 🆕 Wild skills
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
    SkillID id;        // 🔥 CHANGED: Use SkillID instead of int
    int cooldown;
    int cdLeft;
    int aiScore;
} Skill;

// ================= DOG STRUCT - FIXED DUPLICATES =================
typedef struct {
    char name[50];

    int hp, maxHP;
    int attack, defense, speed;  // 🔥 FIXED: Proper names
    int accuracy, intelligence;
    int fatigue;
    int maxFatigue;
    int isConfused;
    int confuseTurns;
    int isBleeding;
    int bleedTurns;
    int bleedDamage;         // Damage per bleed tick
    int isStunned;
    int stunTurns;
    int accTemp;
    int accDebuffTurns;
    int accuracyModifier;    // For debuffs
    int numSkills;           // Number of active skills
    int isCountering;
    int counterDamage;

    // 🔥 FIXED: REMOVED DUPLICATES - ONE OF EACH FIELD ONLY
    int sparringProgress[5]; // Sparring progress tracker

    Skill skills[MAX_SKILLS];
    int skillCount;

    int equipped[4];
} Dog;

// ================= ALL YOUR FUNCTIONS (UNCHANGED) =================
void createDog(Dog *d);
void printDog(Dog d);
int battle(Dog *player, int zoneIndex, int progress[]);
void displayBattleStatus(Dog player, Dog enemy);
void waitForEnter();
void pauseAndClear();
void loseSequence(Dog *player, Dog *enemy);

int playerTurn(Dog *player, Dog *enemy, int *defending);
void playerAttack(Dog *player, Dog *enemy);
void skillMenu(Dog *d);
void checkSkillUnlock(Dog *d);
int hasSkill(Dog *d, char name[]);
int clampFatigue(int f, int max);
void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage);

void showHPBarPlayer(int hp, int maxHp);

void applyBattleStatGain(Dog *d);
void trainDog(Dog *d, int type);
void preBattleScene();

void createEnemy(Dog *e);
int enemyAttack(Dog *player, Dog *enemy, int *defending);
void enemyQuickAttack(Dog *player, Dog *enemy);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
void enemyTurn(Dog *player, Dog *enemy, int *defending);

int clamp(int value);
int getFatiguePenalty(int fatigue);
int isCritical(int hp, int maxHP);

int sparringBattle(Dog *player, int type);
void createSparPartner(Dog *e, int type);
void sparringMenu(Dog *player);
int enemyAI(Dog *enemy, Dog *player, int type);
void applySparReward(Dog *player, int type);
void sparringDog(Dog *player, int type);

// ================= WILD SKILLS =================
void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel);
int usePackAttack(Dog *user, Dog *target);
int useAmbush(Dog *user, Dog *target);
int useHowlDebuff(Dog *user, Dog *target);
int useFeralRush(Dog *user, Dog *target);

#endif