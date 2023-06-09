#include "menu.h"

void menuStartGame(Menu *menu, Game *game) {
    gameFromMode(game, menu->mode);
    menu->play = 1;
}

void handleMenuTouch(Menu *menu, Game *game, touchPosition touch) {
    if (touch.px >= 32 && touch.px <= 32 + 16 && touch.py >= 80 && touch.py <= 80 + 16) {
        menu->mode = previousMode(menu->mode);
    } else if (touch.px >= 256 - 32 - 16 && touch.px <= 256 - 32 && touch.py >= 80 && touch.py <= 80 + 16) {
        menu->mode = nextMode(menu->mode);
    } else {
        menuStartGame(menu, game);
    }
}

void handleMenuKey(Menu *menu, Game *game, int key) {
    if (key & KEY_LEFT) {
        menu->mode = previousMode(menu->mode);
    } else if (key & KEY_RIGHT) {
        menu->mode = nextMode(menu->mode);
    } else if (key & KEY_A || key & KEY_START) {
        menuStartGame(menu, game);
    }
}

void handleGameMenuKey(Game *game, Menu *menu, int key) {
    if (key & KEY_B) {
        menu->play = 0;
    }
}

void renderMenuMainScreen(Menu *menu, Font *font) {
    glBoxFilled(0, 0, 256, 192, RGB15(16, 15, 5));
    
}

void renderMenuSubScreen(Menu *menu, Font *font) {
    glBoxFilled(0, 0, 256, 192, RGB15(16, 15, 5));
    printFontCentered(font, 0, 76, modeName(menu->mode));
    printFontCenteredN(font, 0, 100, 123);
    printFont(font, 32, 80, "<");
    printFont(font, 256 - 32 - 16, 80, ">");
}
