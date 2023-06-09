#ifndef GAME_H
#define GAME_H

#include <nds.h>
#include <gl2d.h>

#include "font.h"
#include "mode.h"

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

void gameFromMode(Game *game, Mode mode);

void handleGameTouch(Game *game, touchPosition touch);
void handleGameKey(Game *game, int key);
void renderGameMainScreen(Game *game, Font *font);
void renderGameSubScreen(Game *game, Font *font);

int speed(Game *game);
void nextFrame(Game *game);

#endif
