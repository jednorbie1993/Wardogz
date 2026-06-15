#ifndef DOG_H
#define DOG_H

#define MAX_SKILLS 20
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

    SKILL_ATTACK = 0,
    SKILL_BITE,
    SKILL_SCRATCH,
    SKILL_QUICK_DASH,
    SKILL_FLASH_STEP,
    SKILL_HEAVY_BITE,
    SKILL_SAVAGE_FANG,
    SKILL_IRON_GUARD,
    SKILL_SURE_STRIKE,
    SKILL_LAST_STAND,

    // backalley
    SKILL_STRAY_BITE,
    SKILL_DIRTY_SCRATCH,
    SKILL_LOCK_JAW,
    SKILL_ALPHA_RAGE,

    // grimfang
    SKILL_FANG_RIPPER,
    SKILL_SAVAGE_RUSH,
    SKILL_BLOOD_TRAIL,
    SKILL_SHADOW_MAW,
    SKILL_SHADOW_BITE,

    // wild skills
    SKILL_PACK_ATTACK,
    SKILL_AMBUSH,
    SKILL_HOWL_DEBUFF,
    SKILL_FERAL_RUSH,

    // diremaw
    SKILL_MAULING_BITE,
    SKILL_WILD_POUNCE,
    SKILL_RABID_CLAW,
    SKILL_PREDATOR_FRENZY,
    SKILL_DIRE_BITE,
    SKILL_BONE_BREAKER,
    SKILL_BLOOD_SCENT,

    // military
    SKILL_PRECISION_SHOT,
    SKILL_TACTICAL_GUARD,
    SKILL_REINFORCEMENT,
    SKILL_SELF_DESTRUCT,
    SKILL_BARRAGE_FIRE,
    SKILL_MILITARY_CHARGE,
    SKILL_AMBUSH_STRIKE,

    // bio lab
    SKILL_MUTATION_SURGE,
    SKILL_BIO_SHIELD,
    SKILL_CELL_REGEN,
    SKILL_CONTAINED_EXPLOSION,
    SKILL_ACID_SPIT,
    SKILL_NEURO_TOXIN,
    SKILL_OMEGA_BITE,

    // secret lab
    SKILL_REINFORCED_BITE,
    SKILL_COMBAT_RUSH,
    SKILL_PREDATOR_INSTINCT,
    SKILL_ENHANCED_JAW_CRUSH,
    SKILL_RAZOR_SLASH,
    SKILL_BLOOD_FRENZY,
    SKILL_FANG_STORM,
    SKILL_TACTICAL_BITE,
    SKILL_ARMOR_BREAK,
    SKILL_SUPPRESSION_HOWL,
    SKILL_BLACKSITE_EXECUTION,
    SKILL_PLASMA_BITE,
    SKILL_CRYO_LOCK,
    SKILL_THUNDER_SURGE,
    SKILL_APEX_OVERDRIVE,
    SKILL_MUTATION_OVERDRIVE,
    SKILL_HUMANOID_JAW_CRUSH,
    SKILL_TIMELINE_MAUL,
    SKILL_CURSED_INSTINCT,

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

// ================= ZONE TYPE =================
typedef enum
{
    ZONE_NORMAL,
    ZONE_RAVINE,
    ZONE_TRIAL,
    ZONE_FOREST,
    ZONE_CITY,
    ZONE_MILITARY,
    ZONE_BIOLAB,
    ZONE_MUTANT  
} ZoneType;

// ================= PERSONALITY TYPE =================
typedef enum
{
    PERSONALITY_NORMAL,
    PERSONALITY_ALPHA,
    PERSONALITY_TANK,
    PERSONALITY_DESPERATE,
    PERSONALITY_WEAK
} PersonalityType;

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

    ZoneType zoneType;
    PersonalityType personalityType;
    int guardTurns;

    int sparringProgress[5];      // 🔥 IBINALIK

    Skill skills[MAX_SKILLS];
    int skillCount;

    int equipped[4];              // 🔥 IBINALIK
    int defeatedGrimfang;

    int defeatedDiremaw;
    int defeatedBlackclaw;
    int defeatedOmega;

    int mutationTriggered;
    int regenerationTurn;
    int regenerationUsed;

    int campaignCompleted;
} Dog;

// ================= CORE FUNCTIONS =================
void createDog(Dog *d);
void printDog(Dog d);
int battle(Dog *player, int zoneIndex, int progress[]);
int battleWithEnemyIndex(Dog *player, int zoneIndex, int progress[], int enemyIndex);
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