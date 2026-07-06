#include <stdio.h>
#include "save.h"

int saveGame(GameData *game)
{
    FILE *fp = fopen(SAVE_FILE, "wb");

    if (fp == NULL)
        return 0;

    fwrite(game, sizeof(GameData), 1, fp);
    fclose(fp);

    return 1;
}

int loadGame(GameData *game)
{
    FILE *fp = fopen(SAVE_FILE, "rb");

    if (fp == NULL)
        return 0;

    fread(game, sizeof(GameData), 1, fp);
    fclose(fp);

    return 1;
}