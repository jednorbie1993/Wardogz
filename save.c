#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include "save.h"
#include "rpg.h"
#ifdef _WIN32
#include <windows.h>
#endif
/* Legacy binary ABI is deliberately frozen. Fail compilation instead of corrupting it. */
_Static_assert(sizeof(int)==4 && sizeof(Skill)==64 && sizeof(Dog)==13152 && sizeof(GameData)==13240,
               "Unsupported legacy save ABI");
_Static_assert(sizeof(RpgState)==224,"RPG v1 layout changed; add an explicit migration");
static uint32_t hashBytes(uint32_t h,const void *data,size_t n) {
    const unsigned char *p=data;
    while(n--) { h^=*p++; h*=16777619u; }
    return h;
}
static uint32_t checksum(const GameData *g,const RpgState *r) {
    return hashBytes(hashBytes(2166136261u,g,sizeof *g),r,sizeof *r);
}
static int validLegacy(const GameData *g) {
    const Dog *p=&g->player;
    if(!memchr(p->name,0,sizeof p->name) || !memchr(p->trainerName,0,sizeof p->trainerName) ||
       p->skillCount<0 || p->skillCount>MAX_SKILLS || p->maxSkillSlots<1 || p->maxSkillSlots>8 ||
       p->maxHP<1 || p->maxHP>MAX_STAT || p->hp<0 || p->hp>p->maxHP ||
       !strchr("FEDCBASXZ",p->arenaRank) || p->arenaRank==0) return 0;
    for(int i=0;i<8;i++) if(p->equipped[i]<-1 || p->equipped[i]>=p->skillCount) return 0;
    for(int i=0;i<p->skillCount;i++) if(!memchr(p->skills[i].name,0,sizeof p->skills[i].name)) return 0;
    const int max[21]={3,3,3,3,3,2,4,4,2,4,4,3,2,4,4,3,4,4,4,4,1};
    for(int i=0;i<21;i++) if(g->progress[i]<0 || g->progress[i]>max[i]) return 0;
    return 1;
}
/* Return 0 only when absent; -1 means invalid/unreadable, never start a new game. */
int loadGame(GameData *game) {
    FILE *fp=fopen(SAVE_FILE,"rb");
    if(!fp) return errno==ENOENT?0:-1;
    GameData candidate; RpgState expansion; unsigned char magic[8];
    uint32_t version,size,hash;
    int ok=fread(&candidate,1,sizeof candidate,fp)==sizeof candidate && validLegacy(&candidate);
    if(!ok) { fclose(fp); return -1; }
    size_t n=fread(magic,1,8,fp);
    if(n==0 && feof(fp)) {
        fclose(fp);
        /* No write here: migration only initializes expansion state. */
        rpgMigrate(&candidate.player,candidate.progress);
        *game=candidate; rpgBind(&game->player); return 1;
    }
    ok=n==8 && !memcmp(magic,"WDZ-RPG1",8) &&
       fread(&version,4,1,fp)==1 && version==RPG_VERSION &&
       fread(&size,4,1,fp)==1 && size==sizeof expansion &&
       fread(&hash,4,1,fp)==1 && fread(&expansion,1,sizeof expansion,fp)==sizeof expansion &&
       fgetc(fp)==EOF && !ferror(fp) && rpgValidate(&expansion) && checksum(&candidate,&expansion)==hash;
    fclose(fp);
    if(!ok) return -1;
    *game=candidate; rpg=expansion; rpgBind(&game->player); return 1;
}
static int backupOriginal(void) {
    FILE *src=fopen(SAVE_FILE,"rb");
    if(!src) return errno==ENOENT;
    FILE *existing=fopen("save.dat.legacy.bak","rb");
    if(existing) { fclose(existing); fclose(src); return 1; }
    FILE *dst=fopen("save.dat.legacy.bak","wb");
    if(!dst) { fclose(src); return 0; }
    unsigned char buf[4096]; size_t n; int ok=1;
    while((n=fread(buf,1,sizeof buf,src))>0) if(fwrite(buf,1,n,dst)!=n) { ok=0; break; }
    if(ferror(src)) ok=0;
    if(fclose(dst)!=0) ok=0;
    fclose(src);
    if(!ok) remove("save.dat.legacy.bak");
    return ok;
}
int saveGame(GameData *game) {
    if(rpgInBattle() || !validLegacy(game) || !rpgValidate(&rpg)) return 0;
    /* Validate any existing save before replacing it, including unknown versions. */
    FILE *old=fopen(SAVE_FILE,"rb");
    if(old) {
        fclose(old); GameData scratch; RpgState current=rpg;
        int status=loadGame(&scratch); rpg=current; rpgBind(&game->player);
        if(status!=1) return 0;
    } else if(errno!=ENOENT) return 0;
    if(!backupOriginal()) return 0;
    FILE *fp=fopen("save.dat.tmp","wb");
    if(!fp) return 0;
    uint32_t version=RPG_VERSION,size=sizeof rpg,hash=checksum(game,&rpg);
    int ok=fwrite(game,1,sizeof *game,fp)==sizeof *game && fwrite("WDZ-RPG1",1,8,fp)==8 &&
       fwrite(&version,4,1,fp)==1 && fwrite(&size,4,1,fp)==1 && fwrite(&hash,4,1,fp)==1 &&
       fwrite(&rpg,1,sizeof rpg,fp)==sizeof rpg;
    if(fflush(fp)!=0) ok=0;
    if(fclose(fp)!=0) ok=0;
    if(ok) {
#ifdef _WIN32
        ok=MoveFileExA("save.dat.tmp",SAVE_FILE,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)!=0;
#else
        ok=rename("save.dat.tmp",SAVE_FILE)==0;
#endif
    }
    if(!ok) remove("save.dat.tmp");
    return ok;
}
