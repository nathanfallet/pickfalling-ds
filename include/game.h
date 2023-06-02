#include <nds.h>
#include <gl2d.h>

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

void renderMainScreen(Game *game);
void renderSubScreen(Game *game);

int speed(Game *game);
void nextFrame(Game *game);
