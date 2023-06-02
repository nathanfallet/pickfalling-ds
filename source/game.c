#include "game.h"

void renderMainScreen(Game *game) {
    glBoxFilled(0, 0, 256, 192, RGB15(16, 15, 5));
    glSprite(game->objectX, game->objectY, GL_FLIP_NONE, game->objectSprite);
}

void renderSubScreen(Game *game) {
    glBoxFilled(0, 0, 256, 192, RGB15(16, 15, 5));
    glSprite(game->playerX, game->playerY-192, GL_FLIP_NONE, game->playerSprite);
    glSprite(game->objectX, game->objectY-192, GL_FLIP_NONE, game->objectSprite);
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
        game->objectX = rand() % 256 - 32;
    }
    if (game->objectY > 2*192) {
        game->lost = 1;
    }
}
