#ifndef MENU_H
#define MENU_H

#include <nds.h>
#include <gl2d.h>

#include "font.h"
#include "mode.h"
#include "game.h"

typedef struct {
    Mode mode;
    int play;
} Menu;

void menuStartGame(Menu *menu, Game *game);
void handleMenuTouch(Menu *menu, Game *game, touchPosition touch);
void handleMenuKey(Menu *menu, Game *game, int key);
void handleGameMenuKey(Game *game, Menu *menu, int key);
void renderMenuMainScreen(Menu *menu, Font *font);
void renderMenuSubScreen(Menu *menu, Font *font);

#endif
