#include <nds.h>

#include <player.h>
#include <spinash.h>

typedef struct {
    int x;
    int y;

    u16* sprite_gfx_mem;
} Sprite;

typedef struct {
    u16* sprite_gfx_mem;
} BackgroundColor;

void initGameEngine();
void initSprite(OamState *oamState, Sprite *sprite, u8* gfx);
void initBackgroundColor(BackgroundColor *background_color, u8* gfx);
