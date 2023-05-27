#include "sprite.h"

void initGameEngine() {
    videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);
}

void initSprite(OamState *oamState, Sprite *sprite, u8* gfx) {
    sprite->sprite_gfx_mem = oamAllocateGfx(oamState, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(gfx, sprite->sprite_gfx_mem, 32*32);
}

void initBackgroundColor(BackgroundColor *background_color, u8* gfx) {
    background_color->sprite_gfx_mem = oamAllocateGfx(&oamSub, SpriteSize_32x32, SpriteColorFormat_256Color);
    dmaCopy(gfx, background_color->sprite_gfx_mem, 32*32);
}
