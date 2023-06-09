#include "game.h"

void gameFromMode(Game *game, Mode mode) {
    game->playerX = 128 - 16;
    game->playerY = 2 * 192 - 32;
    game->objectX = 128 - 16;
    game->objectY = 0;
    game->score = 0;
    game->started = 0;
    game->lost = 0;
}

void handleGameTouch(Game *game, touchPosition touch) {
    game->started = 1;
    game->playerX = touch.px - 16;
}

void handleGameKey(Game *game, int key) {
    
}

void renderGameMainScreen(Game *game, Font *font) {
    glBoxFilled(0, 0, 256, 192, RGB15(16, 15, 5));
    if (game->started) {
        glSprite(game->objectX, game->objectY, GL_FLIP_NONE, &game->objectSprite);
    }
    printFontCenteredN(font, 0, 16, game->score);
}

void renderGameSubScreen(Game *game, Font *font) {
    glBoxFilled(0, 0, 256, 192, RGB15(16, 15, 5));
    if (game->lost) {
        printFontCentered(font, 0, 80, "GAME OVER");
    } else {
        glSprite(game->playerX, game->playerY-192, GL_FLIP_NONE, &game->playerSprite);
        glSprite(game->objectX, game->objectY-192, GL_FLIP_NONE, &game->objectSprite);
    }
}

int speed(Game *game) {
    return 2;
}

void nextFrame(Game *game) {
    int offset = speed(game);
    game->objectY += offset;

    if (
        abs(game->playerX - game->objectX) < 32 &&
        abs(game->playerY - game->objectY) < 32
    ) {
        game->score += 1;
        game->objectY = 0;
        game->objectX = rand() % (256 - 32);
    }
    if (game->objectY > 2*192) {
        game->lost = 1;
    }
}
