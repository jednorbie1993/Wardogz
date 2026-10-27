#include "rpg.h"
#include "save.h"
#include "skill.h"
#include "console.h"
#include "menu_shortcuts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const Gear rpgGear[RPG_GEAR_COUNT] = {
    {"Leather Cap", 0, 1, 0, 60, 0, 5, 0, 0, 0, 0},
    {"Padded Vest", 1, 1, 0, 70, 0, 5, 0, 0, 0, 0},
    {"Training Collar", 2, 1, 0, 80, 0, 0, 0, 0, 0, 1},
    {"Trail Boots", 3, 1, 0, 90, 0, 0, 5, 0, 0, 0},
    {"Steel Fangs", 4, 1, 0, 100, 5, 0, 0, 0, 0, 0},
    {"Focus Earrings", 5, 1, 0, 110, 0, 0, 0, 0, 0, 0},
    {"Shock Helm", 0, 3, 2, 300, 0, 15, 0, 3, 1, 0},
    {"Guard Plate", 1, 3, 2, 340, 0, 15, 0, 0, 0, 0},
    {"Venom Pendant", 2, 4, 3, 380, 0, 0, 0, 1, 2, 0},
    {"Thunder Paws", 3, 4, 3, 420, 0, 0, 12, 4, 3, 0},
    {"Serrated Fangs", 4, 5, 4, 460, 12, 0, 0, 2, 0, 0},
    {"Scholar Earrings", 5, 5, 4, 500, 0, 0, 0, 0, 0, 2},
    {"Alley Alpha Helm", 0, 1, 0, 400, 0, 8, 0, 1, 1, 0},
    {"Iron Jaw Armor", 1, 1, 0, 440, 0, 9, 0, 2, 0, 0},
    {"Street King Collar", 2, 1, 0, 480, 0, 10, 0, 3, 3, 0},
    {"Ravine Paws", 3, 1, 0, 520, 0, 0, 11, 4, 1, 0},
    {"Trial Fangs", 4, 2, 0, 560, 12, 0, 0, 1, 0, 0},
    {"Forest Earrings", 5, 2, 0, 600, 0, 0, 13, 2, 0, 1},
    {"Wildlands Helm", 0, 2, 0, 640, 0, 14, 0, 3, 1, 0},
    {"Predator Armor", 1, 2, 0, 680, 0, 15, 0, 4, 0, 0},
    {"Outpost Collar", 2, 3, 0, 720, 0, 16, 0, 1, 3, 0},
    {"Tactical Paws", 3, 3, 0, 760, 0, 0, 17, 2, 1, 0},
    {"Sniper Fangs", 4, 3, 0, 800, 18, 0, 0, 3, 0, 0},
    {"Commander Earrings", 5, 3, 0, 840, 0, 0, 19, 4, 0, 1},
    {"Facility Helm", 0, 4, 0, 880, 0, 20, 0, 1, 1, 0},
    {"Research Armor", 1, 4, 0, 920, 0, 21, 0, 2, 0, 0},
    {"Containment Collar", 2, 4, 0, 960, 0, 22, 0, 3, 3, 0},
    {"Prototype Zero Paws", 3, 4, 0, 1000, 0, 0, 23, 4, 1, 0},
    {"Alpha-X Fangs", 4, 5, 0, 1040, 24, 0, 0, 1, 0, 0},
    {"Lycan Rex Earrings", 5, 5, 0, 1080, 0, 0, 25, 2, 0, 1},
    {"Commander Cerberus Helm", 0, 5, 0, 1120, 0, 26, 0, 3, 1, 0},
    {"Apex Chimera Armor", 1, 5, 0, 1160, 0, 27, 0, 4, 0, 0},
    {"Project Cerberus Collar", 2, 6, 0, 1200, 0, 28, 0, 1, 3, 0},
    {"Grimfang Paws", 3, 6, 0, 1240, 0, 0, 29, 2, 1, 0},
    {"Diremaw Fangs", 4, 6, 0, 1280, 30, 0, 0, 3, 0, 0},
    {"Blackclaw Earrings", 5, 6, 0, 1320, 0, 0, 31, 4, 0, 1},
    {"Omega Prime Helm", 0, 7, 0, 1360, 0, 32, 0, 1, 1, 0},
    {"Grimfang-X Armor", 1, 7, 0, 1400, 0, 33, 0, 2, 0, 0},
};
RpgState rpg;
static Dog *owner;
static Dog *fighter;
static int attackBonus, originalDef, originalSpd;
static int poison, paralysis, gearBleed, gearStun, serumUsed[3];
static const int zoneMax[21]={3,3,3,3,3,2,4,4,2,4,4,3,2,4,4,3,4,4,4,4,1};
static const char *slots[6]={"Head","Body","Neck","Paws","Fangs","Earrings"};
static const char *effects[5]={"None","Poison","Bleed","Stun","Paralysis"};
static const char *itemNames[6]={"Meat (+80 HP)","Energy Meal (+60 Energy)","Full Meal (+120 HP/+80 Energy)","Power Serum (+25 ATK/battle)","Guard Serum (+25 DEF/battle)","Speed Serum (+25 SPD/battle)"};
static const int prices[6]={20,20,45,50,50,50};
static uint32_t cappedAdd(uint32_t a, uint32_t b) { return b>RPG_LIMIT-a ? RPG_LIMIT : a+b; }
void rpgBind(Dog *p) { owner=p; }
void rpgInit(void) {
    memset(&rpg,0,sizeof rpg);
    for(int i=0;i<6;i++) rpg.worn[i]=-1;
    rpg.active[0]=rpg.active[1]=-1;
    fighter=NULL;
}
int rpgRank(char c) { const char *p=c?strchr("FEDCBASXZ",c):NULL; return p ? (int)(p-"FEDCBASXZ") : 0; }
int rpgLevel(void) {
    int level=1; uint32_t xp=rpg.xp;
    while(level<99 && xp>=(uint32_t)(100*level)) { xp-=100*level; level++; }
    return level;
}
static int wornIn(const RpgState *s,int id) {
    return id>=0 && id<RPG_GEAR_COUNT && s->worn[rpgGear[id].slot]==id;
}
int rpgValidate(const RpgState *s) {
    if(s->xp>RPG_LIMIT || s->coins>RPG_LIMIT || (s->claimed>>RPG_BOSS_COUNT) ||
       (s->pending>>RPG_BOSS_COUNT) || (s->claimed&s->pending)) return 0;
    for(int i=0;i<RPG_GEAR_COUNT;i++) if(s->owned[i]>1) return 0;
    for(int i=0;i<6;i++) {
        int id=s->worn[i];
        if(id < -1 || id>=RPG_GEAR_COUNT || (id>=0 && (rpgGear[id].slot!=i || !s->owned[id]))) return 0;
        if(s->items[i]>999) return 0;
    }
    for(int i=0;i<2;i++) if(s->active[i]!=-1 && (!wornIn(s,s->active[i]) || !rpgGear[s->active[i]].skill)) return 0;
    return s->active[0]==-1 || s->active[0]!=s->active[1];
}
/* Only positive evidence: cleared zone counters, secret-boss flags, final completion. */
void rpgMigrate(const Dog *p,const int progress[21]) {
    rpgInit();
    for(int i=0;i<21;i++) if(progress[i]>=zoneMax[i]) rpg.pending |= 1u<<i;
    const int flags[5]={p->defeatedGrimfang,p->defeatedDiremaw,p->defeatedBlackclaw,p->defeatedOmega,p->defeatedGrimfangX};
    for(int i=0;i<5;i++) if(flags[i]) rpg.pending |= 1u<<(21+i);
    if(p->campaignCompleted) rpg.pending |= 1u<<20;
}
void rpgGrant(int id) {
    if(id<0 || id>=RPG_GEAR_COUNT) return;
    if(rpg.owned[id]) {
        int value=rpgGear[id].price/2;
        rpg.coins=cappedAdd(rpg.coins,value);
        printCenteredFormat("Duplicate %s: +%d Battle Coins",rpgGear[id].name,value);
    } else {
        rpg.owned[id]=1;
        printCenteredFormat("Equipment received: %s",rpgGear[id].name);
    }
}
int rpgClaim(void) {
    int count=0;
    for(int i=0;i<RPG_BOSS_COUNT;i++) if((rpg.pending & (1u<<i)) && !(rpg.claimed & (1u<<i))) {
        rpgGrant(12+i); rpg.claimed|=1u<<i; count++;
    }
    rpg.pending=0;
    return count;
}
void rpgReward(Dog *p,int zone,int enemyIndex,char rank) {
    if(p!=owner) return;
    int boss=-1, tier;
    if(zone>=0 && zone<21) {
        tier=zone/4+1;
        if(enemyIndex==zoneMax[zone]-1) boss=zone;
        if(enemyIndex>=95 && enemyIndex<=99) boss=21+(99-enemyIndex);
    } else tier=rpgRank(rank)+1;
    int xp=20*tier, coins=12*tier;
    if(boss>=0) { xp*=2; coins*=2;
        rpgGrant(12+boss); rpg.claimed|=1u<<boss; rpg.pending &= ~(1u<<boss);
    }
    int before=rpgLevel();
    rpg.xp=cappedAdd(rpg.xp,xp); rpg.coins=cappedAdd(rpg.coins,coins);
    printCenteredFormat("+%d EXP | +%d Battle Coins | Level %d",xp,coins,rpgLevel());
    if(rpgLevel()!=before) printCentered("Level up! New equipment requirements may now be met. Base stats unchanged.");
}
static void syncSkills(void) {
    int available[6], n=0;
    for(int i=0;i<6;i++) if(rpg.worn[i]>=0 && rpgGear[rpg.worn[i]].skill) available[n++]=rpg.worn[i];
    for(int i=0;i<2;i++) if(!wornIn(&rpg,rpg.active[i])) rpg.active[i]=-1;
    if(n<=2) { for(int i=0;i<2;i++) rpg.active[i]=i<n?available[i]:-1; }
    else for(int i=0;i<2;i++) if(rpg.active[i]<0) {
        for(int j=0;j<n;j++) if(available[j]!=rpg.active[1-i]) { rpg.active[i]=available[j]; break; }
    }
}
int rpgEquip(int id) {
    if(fighter || id<0 || id>=RPG_GEAR_COUNT || !rpg.owned[id] || rpgLevel()<rpgGear[id].level) return 0;
    rpg.worn[rpgGear[id].slot]=id; syncSkills(); return 1;
}
int rpgSelect(int a,int b) {
    if(a==b || !wornIn(&rpg,a) || !wornIn(&rpg,b) || !rpgGear[a].skill || !rpgGear[b].skill) return 0;
    rpg.active[0]=a; rpg.active[1]=b; return 1;
}
int rpgBuy(Dog *p,int id,int consumable) {
    if(fighter || id<0) return 0;
    int price;
    if(consumable) {
        if(id>=6 || rpg.items[id]>=999 || (id>=3 && (rpgLevel()<3 || rpgRank(p->arenaRank)<1))) return 0;
        price=prices[id];
    } else {
        if(id>=12 || rpg.owned[id] || rpgLevel()<rpgGear[id].level || rpgRank(p->arenaRank)<rpgGear[id].rank) return 0;
        price=rpgGear[id].price;
    }
    if(rpg.coins<(uint32_t)price) return 0;
    rpg.coins-=price;
    if(consumable) rpg.items[id]++; else rpg.owned[id]=1;
    return 1;
}
int rpgSell(int id,int consumable) {
    if(fighter || id<0) return 0;
    int price;
    if(consumable) {
        if(id>=6 || !rpg.items[id]) return 0;
        rpg.items[id]--; price=prices[id];
    } else {
        if(id>=RPG_GEAR_COUNT || !rpg.owned[id] || wornIn(&rpg,id)) return 0;
        rpg.owned[id]=0; price=rpgGear[id].price;
    }
    rpg.coins=cappedAdd(rpg.coins,price/2); return 1;
}
void rpgBegin(Dog *p) {
    if(p!=owner || fighter) return;
    fighter=p; attackBonus=0; originalDef=p->defense; originalSpd=p->speed;
    poison=paralysis=gearBleed=gearStun=0; memset(serumUsed,0,sizeof serumUsed);
    syncSkills();
    for(int i=0;i<6;i++) if(rpg.worn[i]>=0) {
        const Gear *g=&rpgGear[rpg.worn[i]];
        attackBonus+=g->atk; p->attack+=g->atk; p->defense+=g->def; p->speed+=g->spd;
    }
}
void rpgEnd(Dog *p) {
    if(p!=fighter) return;
    p->attack-=attackBonus; if(p->attack<0) p->attack=0; p->defense=originalDef; p->speed=originalSpd;
    fighter=NULL; poison=paralysis=gearBleed=gearStun=0;
}
int rpgInBattle(void) { return fighter!=NULL; }
int rpgGrowth(Dog *p) {
    if(p!=owner) return 0;
    int bonus=0;
    for(int i=0;i<6;i++) if(rpg.worn[i]>=0) bonus+=rpgGear[rpg.worn[i]].growth;
    return bonus;
}
void rpgOnHit(Dog *user,Dog *target) {
    if(user!=fighter || target->hp<=0) return;
    for(int i=0;i<6;i++) if(rpg.worn[i]>=0) {
        int effect=rpgGear[rpg.worn[i]].effect;
        if(effect && rand()%100<15) {
            if(effect==RPG_POISON) poison=3;
            if(effect==RPG_BLEED) gearBleed=3;
            if(effect==RPG_STUN) gearStun=1;
            if(effect==RPG_PARALYSIS) paralysis=3;
            printCenteredFormat("Equipment inflicted %s!",effects[effect]);
        }
    }
}
/* Called once per accepted action, before the enemy turn; independent of old skill statuses. */
int rpgEnemyTurn(Dog *e) {
    if(!fighter) return 0;
    if(poison>0) { poison--; int damage=e->maxHP/50+1; e->hp-=damage; printCenteredFormat("Poison: -%d HP",damage); }
    if(gearBleed>0) { gearBleed--; e->hp-=8; printCentered("Equipment bleed: -8 HP"); }
    if(e->hp<=0) { e->hp=0; return 1; }
    if(gearStun>0) { gearStun--; printCentered("Equipment stun: enemy turn skipped."); return 1; }
    if(paralysis>0) { paralysis--; if(rand()%100<40) { printCentered("Paralysis: enemy turn skipped."); return 1; } }
    return 0;
}
static Skill gearSkill(int id) {
    Skill s={"",30,18,SKILL_DAMAGE,90,SKILL_NONE,0,0,0};
    int type=rpgGear[id].skill;
    snprintf(s.name,sizeof s.name,"%s",type==1?"Gear Shock":type==2?"Gear Venom":"Gear Rush");
    if(type==3) s.power=40;
    return s;
}
void rpgPrintSkills(void) {
    for(int i=0;i<2;i++) if(rpg.active[i]>=0) {
        Skill s=gearSkill(rpg.active[i]); printCenteredFormat("%d. %s (gear; Energy %d)",9+i,s.name,s.cost);
    }
}
int rpgUseSkill(Dog *p,Dog *e,int choice) {
    int slot=choice-9;
    if(p!=fighter || slot<0 || slot>1 || rpg.active[slot]<0) return 0;
    Skill s=gearSkill(rpg.active[slot]);
    if(p->fatigue<s.cost) { printCentered("Not enough Energy for equipment skill."); return 0; }
    p->fatigue-=s.cost;
    int hit=useSkill(p,e,s);
    if(hit && e->hp>0) {
        int type=rpgGear[rpg.active[slot]].skill;
        if(type==1 && rand()%100<35) gearStun=1;
        if(type==2) poison=3;
    }
    return 1;
}
int rpgUseItem(Dog *p,int id) {
    if(id<0 || id>=6 || !rpg.items[id]) return 0;
    if(id<3) {
        int hp=id==0?80:id==2?120:0, energy=id==1?60:id==2?80:0;
        if((!hp || p->hp>=p->maxHP) && (!energy || p->fatigue>=p->maxFatigue)) return 0;
        p->hp+=hp; if(p->hp>p->maxHP) p->hp=p->maxHP;
        p->fatigue+=energy; if(p->fatigue>p->maxFatigue) p->fatigue=p->maxFatigue;
    } else {
        if(fighter!=p || serumUsed[id-3]) return 0;
        serumUsed[id-3]=1;
        if(id==3) { p->attack+=25; attackBonus+=25; }
        if(id==4) p->defense+=25;
        if(id==5) p->speed+=25;
    }
    rpg.items[id]--; return 1;
}
static int readNumber(void) {
    char line[80],extra; int n;
    if(!fgets(line,sizeof line,stdin)) return -1;
    if(!fighter && handleMenuShortcut(line)) return -1;
    return sscanf(line,"%d %c",&n,&extra)==1?n:-2;
}
/* The in-battle item menu intentionally keeps the battle screen visible. */
static void listItems(void) {
    for(int i=0;i<RPG_ITEM_COUNT;i++)
        printf("%d. %-40s x%u | Buy %d / Sell %d\n",i+1,itemNames[i],rpg.items[i],prices[i],prices[i]/2);
}
int rpgItemMenu(Dog *p) {
    listItems(); puts("0. Back (serums last this battle, one of each per battle)");
    int n=readNumber();
    if(n<=0) return 0;
    int ok=rpgUseItem(p,n-1); puts(ok?"Item used.":"Cannot use this item now."); return ok;
}

/* Home-menu screens use the same clear/center helpers as the original Wardogz menus. */
static void rpgScreen(const char *title) {
    system("cls");
    printBorder();
    printBlankLine();
    printCentered(title);
    printBlankLine();
}
static void rpgFooter(void) {
    printBlankLine();
    printMenuShortcutLegend();
    printBlankLine();
    printf("%*sChoice: ", MENU_MARGIN, "");
}
static void rpgNotice(const char *message) {
    printBlankLine();
    printCentered(message);
    waitForEnter();
}
static const char *rankName(int rank) {
    static const char *names[]={"F","E","D","C","B","A","S","SS","SSS"};
    return rank>=0 && rank<9 ? names[rank] : "F";
}
static void gearDetails(int id) {
    const Gear *g=&rpgGear[id];
    printCenteredFormat("%s | %s",g->name,slots[g->slot]);
    printCenteredFormat("ATK +%d  |  DEF +%d  |  SPD +%d",g->atk,g->def,g->spd);
    printCenteredFormat("Passive: %s%s",effects[g->effect],g->effect?" (15% on hit)":"");
    printCenteredFormat("Growth bonus: +%d to victory stat gains",g->growth);
    if(g->skill) printCenteredFormat("Special skill: %s",gearSkill(id).name);
    printCenteredFormat("Level needed: %d  |  Store rank: Class %s",g->level,rankName(g->rank));
    printCenteredFormat("Buy: %d BC  |  Sell: %d BC",g->price,g->price/2);
    printCenteredFormat("Owned: %s  |  Equipped: %s",rpg.owned[id]?"Yes":"No",wornIn(&rpg,id)?"Yes":"No");
}
static int ownedGearList(int out[RPG_GEAR_COUNT]) {
    int count=0;
    for(int id=0;id<RPG_GEAR_COUNT;id++) if(rpg.owned[id]) out[count++]=id;
    return count;
}
/* Up to eight items per screen, so long inventories stay within the console height. */
static int pickGear(const char *title, int storeBuy) {
    int ids[RPG_GEAR_COUNT],count=0,page=0;
    if(storeBuy) {
        for(int i=0;i<12;i++) ids[count++]=i; /* Store stock is defined by rpgBuy. */
    } else count=ownedGearList(ids);
    for(;;) {
        if(menuNavigationRequested()) return -1;
        rpgScreen(title);
        if(count==0) printCentered("No equipment owned yet.");
        else {
            for(int j=page*8;j<count && j<page*8+8;j++) {
                int id=ids[j]; const Gear *g=&rpgGear[id];
                printMenuItemFormat(j-page*8+1,"%s [%s]%s",g->name,slots[g->slot],
                                    wornIn(&rpg,id)?" (EQUIPPED)":"");
            }
            printBlankLine();
            printCenteredFormat("Page %d/%d",page+1,(count+7)/8);
        }
        if(page>0) printMenuItem(98, "Previous Page");
        if((page+1)*8<count) printMenuItem(99, "Next Page");
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n==0 || n==-1) return -1;
        if(n==98 && page>0) { page--; continue; }
        if(n==99 && (page+1)*8<count) { page++; continue; }
        if(n>=1 && n<=8 && page*8+n<=count) return ids[page*8+n-1];
        rpgNotice("Invalid item number.");
    }
}
static void viewGear(void) {
    for(;;) {
        int id=pickGear("VIEW EQUIPMENT",0);
        if(id<0 || menuNavigationRequested()) return;
        rpgScreen("ITEM INFO");
        gearDetails(id);
        printBlankLine();
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n==-1 || menuNavigationRequested()) return;
        /* Any input redisplays the owned gear list. */
    }
}
static void viewConsumables(void) {
    while(!menuNavigationRequested()) {
        rpgScreen("FOOD & SERUM INVENTORY");
        for(int i=0;i<RPG_ITEM_COUNT;i++)
            printMenuItemFormat(i+1,"%s  x%u",itemNames[i],rpg.items[i]);
        printBlankLine();
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n>RPG_ITEM_COUNT) {rpgNotice("Invalid item number.");continue;}
        int id=n-1;
        rpgScreen("ITEM INFO");
        printCentered(itemNames[id]);
        printCenteredFormat("Category: %s",id<3?"Food":"Serum");
        printCenteredFormat("Owned: %u  |  Buy: %d BC  |  Sell: %d BC",rpg.items[id],prices[id],prices[id]/2);
        if(id>=3) printCentered("Serums can only be used during battle.");
        printBlankLine(); printMenuItem(0, "Back"); rpgFooter();
        n=readNumber();
        if(n==-1 || menuNavigationRequested()) return;
    }
}
static void viewItems(void) {
    while(!menuNavigationRequested()) {
        rpgScreen("VIEW ITEMS");
        printMenuItem(1, "Equipment Inventory");
        printMenuItem(2, "Foods & Serums");
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n==1) viewGear();
        else if(n==2) viewConsumables();
        else rpgNotice("Invalid choice.");
    }
}
static void equipGear(void) {
    while(!menuNavigationRequested()) {
        int id=pickGear("EQUIP GEAR",0);
        if(id<0 || menuNavigationRequested()) return;
        rpgScreen("EQUIP ITEM");
        gearDetails(id);
        printBlankLine();
        printMenuItem(1, "Equip");
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n==-1) return;
        if(n==1) rpgNotice(rpgEquip(id)?"Equipment equipped!":"Cannot equip: check Level or battle status.");
        else if(n!=0) rpgNotice("Invalid choice.");
    }
}
static void unequipGear(void) {
    while(!menuNavigationRequested()) {
        rpgScreen("UNEQUIP GEAR");
        for(int i=0;i<6;i++)
            printMenuItemFormat(i+1,"%s: %s",slots[i],
                                rpg.worn[i]<0?"None":rpgGear[rpg.worn[i]].name);
        printBlankLine(); printMenuItem(0, "Back"); rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n>6) {rpgNotice("Invalid slot.");continue;}
        if(rpg.worn[n-1]<0) {rpgNotice("That slot is already empty.");continue;}
        rpgScreen("EQUIPMENT INFO");
        gearDetails(rpg.worn[n-1]);
        printBlankLine(); printMenuItem(1, "Unequip"); printMenuItem(0, "Back"); rpgFooter();
        int confirm=readNumber();
        if(confirm==-1) return;
        if(confirm==1) {
            rpg.worn[n-1]=-1;
            syncSkills();
            rpgNotice("Equipment removed. Passive bonuses updated.");
        }
    }
}
static void selectGearSkills(void) {
    int ids[6],count=0;
    for(int i=0;i<6;i++) {
        int id=rpg.worn[i];
        if(id>=0 && rpgGear[id].skill) ids[count++]=id;
    }
    if(count<2) {rpgNotice("Equip at least two skill-granting items first.");return;}
    rpgScreen("SELECT EQUIPMENT SKILLS");
    printCentered("Choose two skills (normal skill slots are unchanged).");
    printBlankLine();
    for(int i=0;i<count;i++)
        printMenuItemFormat(i+1,"%s - %s%s",rpgGear[ids[i]].name,gearSkill(ids[i]).name,
                            rpg.active[0]==ids[i] || rpg.active[1]==ids[i]?" [ACTIVE]":"");
    printBlankLine(); printMenuItem(0, "Back");
    printBlankLine(); printf("%*sFirst skill: ", MENU_MARGIN, "");
    int a=readNumber();
    if(a<=0 || a>count) return;
    printf("%*sSecond skill: ", MENU_MARGIN, "");
    int b=readNumber();
    if(b<=0 || b>count) return;
    rpgNotice(rpgSelect(ids[a-1],ids[b-1])?"Two equipment skills selected!":"Choose two different skills.");
}
static void equipmentSlots(void) {
    while(!menuNavigationRequested()) {
        rpgScreen("EQUIP ITEMS");
        for(int i=0;i<6;i++)
            printf("%*s%-9s: %s\n", MENU_MARGIN, "", slots[i],
                   rpg.worn[i]<0?"None":rpgGear[rpg.worn[i]].name);
        printBlankLine();
        printMenuItem(1, "Equip Gear");
        printMenuItem(2, "Unequip Gear");
        printMenuItem(3, "Select Equipment Skills");
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n==1) equipGear();
        else if(n==2) unequipGear();
        else if(n==3) selectGearSkills();
        else rpgNotice("Invalid choice.");
    }
}
static void shopGear(Dog *p,int sell) {
    while(!menuNavigationRequested()) {
        int id=pickGear(sell?"SELL EQUIPMENT":"BUY EQUIPMENT",!sell);
        if(id<0 || menuNavigationRequested()) return;
        rpgScreen("STORE ITEM INFO");
        gearDetails(id);
        printCenteredFormat("Your Level: %d | Arena Rank: Class %c | Coins: %u",rpgLevel(),p->arenaRank,rpg.coins);
        printBlankLine();
        printMenuItem(1, sell?"Sell":"Buy");
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n==-1) return;
        if(n==1) {
            int ok=sell?rpgSell(id,0):rpgBuy(p,id,0);
            rpgNotice(ok?(sell?"Equipment sold!":"Equipment purchased!"):
                         "Unavailable: check ownership, Level, Rank, Coins or equipped status.");
        } else if(n!=0) rpgNotice("Invalid choice.");
    }
}
static void shopConsumables(Dog *p,int sell) {
    while(!menuNavigationRequested()) {
        rpgScreen(sell?"SELL FOODS & SERUMS":"BUY FOODS & SERUMS");
        printCenteredFormat("Battle Coins: %u",rpg.coins);
        printBlankLine();
        for(int i=0;i<RPG_ITEM_COUNT;i++)
            printMenuItemFormat(i+1,"%s | %d BC | Owned: %u",itemNames[i],
                                sell?prices[i]/2:prices[i],rpg.items[i]);
        printBlankLine();printMenuItem(0, "Back");rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n>RPG_ITEM_COUNT) {rpgNotice("Invalid item number.");continue;}
        int id=n-1;
        rpgScreen("STORE ITEM INFO");
        printCentered(itemNames[id]);
        printCenteredFormat("You own: %u  |  %s price: %d BC",rpg.items[id],sell?"Sell":"Buy",
                            sell?prices[id]/2:prices[id]);
        if(id>=3) printCentered("Serums require Level 3 and Arena Class E to buy.");
        printBlankLine();printMenuItem(1, sell?"Sell":"Buy");printMenuItem(0, "Back");rpgFooter();
        int confirm=readNumber();
        if(confirm==-1) return;
        if(confirm==1) {
            int ok=sell?rpgSell(id,1):rpgBuy(p,id,1);
            rpgNotice(ok?(sell?"Item sold!":"Item purchased!"):
                         "Unavailable: check Coins, stock, Rank, Level or quantity.");
        }
    }
}
static void storeMenu(Dog *p) {
    while(!menuNavigationRequested()) {
        rpgScreen("STORE");
        printCenteredFormat("Battle Coins: %u",rpg.coins);
        printBlankLine();
        printMenuItem(1, "Buy Equipment");
        printMenuItem(2, "Sell Equipment");
        printMenuItem(3, "Buy Foods & Serums");
        printMenuItem(4, "Sell Foods & Serums");
        printMenuItem(0, "Back");
        rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n==1) shopGear(p,0);
        else if(n==2) shopGear(p,1);
        else if(n==3) shopConsumables(p,0);
        else if(n==4) shopConsumables(p,1);
        else rpgNotice("Invalid choice.");
    }
}
static void homeUseItems(Dog *p) {
    while(!menuNavigationRequested()) {
        rpgScreen("USE ITEMS");
        for(int i=0;i<RPG_ITEM_COUNT;i++)
            printMenuItemFormat(i+1,"%s  x%u%s",itemNames[i],rpg.items[i],
                                i>=3?" (battle only)":"");
        printBlankLine();printMenuItem(0, "Back");rpgFooter();
        int n=readNumber();
        if(n<=0) return;
        if(n>RPG_ITEM_COUNT) {rpgNotice("Invalid item number.");continue;}
        rpgNotice(rpgUseItem(p,n-1)?"Item used!":"Cannot use this item now.");
    }
}
void rpgMenu(Dog *p) {
    while(!menuNavigationRequested()) {
        rpgScreen("EQUIPMENT");
        printCenteredFormat("Level %d  |  EXP %u  |  Battle Coins %u",rpgLevel(),rpg.xp,rpg.coins);
        printBlankLine();
        printMenuItem(1, "View Items");
        printMenuItem(2, "Equip Items");
        printMenuItem(3, "Store");
        printMenuItem(4, "Use Items");
        printMenuItem(9, "Claim Boss Rewards");
        printMenuItem(0, "Back");
        rpgFooter();
        int op=readNumber();
        if(op<=0) return;
        if(op==1) viewItems();
        else if(op==2) equipmentSlots();
        else if(op==3) storeMenu(p);
        else if(op==4) homeUseItems(p);
        else if(op==9) {
            int n=rpgClaim();
            if(n) {
                system("cls");
                rpgScreen("BOSS REWARDS CLAIMED");
                printCenteredFormat("Claimed %d pending rewards. Campaign progress unchanged.",n);
                waitForEnter();
            } else rpgNotice("No unclaimed boss rewards available.");
        } else rpgNotice("Invalid choice.");
    }
}
