#include <nds.h>
#include <gl2d.h>

typedef struct {
    glImage *playerSprite;
    glImage *objectSprite;
    int playerX;
    int playerY;
    int objectX;
    int objectY;
    int score;
    int started;
    int lost;
} Game;

void renderMainScreen(Game *game);
void renderSubScreen(Game *game);

int speed(Game *game);
void nextFrame(Game *game);
