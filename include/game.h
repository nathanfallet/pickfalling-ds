#ifndef GAME_H
#define GAME_H

#include <nds.h>
#include <gl2d.h>

#include "font.h"

typedef struct {
    int playerX;
    int playerY;
    int objectX;
    int objectY;
    int score;
    int started;
    int lost;
    glImage playerSprite;
    glImage objectSprite;
} Game;

void renderMainScreen(Game *game, Font *font);
void renderSubScreen(Game *game);

int speed(Game *game);
void nextFrame(Game *game);

#endif
