#include <nds.h>
#include <stdio.h>

#include <spinash.h>
#include <player.h>

#include "sprite.h"

int main() {
    touchPosition touch;

    initGameEngine();

    Sprite player = { 128 - 16, 192 - 32 };
    initSprite(&oamSub, &player, (u8*)playerTiles);
    Sprite spinashMain = { 128 - 16, 0 };
    initSprite(&oamMain, &spinashMain, (u8*)spinashTiles);
    Sprite spinashSub = { 128 - 16, 0 };
    initSprite(&oamSub, &spinashSub, (u8*)spinashTiles);

    dmaCopy(playerPal, SPRITE_PALETTE_SUB, 512);
    dmaCopy(spinashPal, SPRITE_PALETTE, 512);
    //dmaCopy(spinashPal, SPRITE_PALETTE_SUB + 512, 512);

    while(1) {
        // Read touch position
        scanKeys();
		int held = keysHeld();
		if(held & KEY_TOUCH) {
			touchRead(&touch);
            player.x = touch.px - 16;
        }

        // Move the spinash
        spinashMain.y += 1;
        if(spinashMain.y > 192) {
            spinashMain.y = 0;
        }

        // Frame count (debug)
        //iprintf("\x1b[0;0H%d",frame);

        // Draw the player
        oamSet(
            &oamSub, 0, player.x, player.y, 0, 0,
            SpriteSize_32x32, SpriteColorFormat_256Color, player.sprite_gfx_mem, -1,
            false, false, false, false, false
        );

        // Draw spinash
        oamSet(
            &oamMain, 0, spinashMain.x, spinashMain.y, 0, 0,
            SpriteSize_32x32, SpriteColorFormat_256Color, spinashMain.sprite_gfx_mem, -1,
            false, false, false, false, false
        );
        /*oamSet(
            &oamSub, 0, spinashSub.x, spinashSub.y, 0, 0,
            SpriteSize_32x32, SpriteColorFormat_256Color, spinashSub.sprite_gfx_mem, -1,
            false, false, false, false, false
        );*/

        // Wait for the screen to refresh
        swiWaitForVBlank();

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    return 0;
}
