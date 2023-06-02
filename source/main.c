#include <nds.h>
#include <gl2d.h>

#include <spinash.h>
#include <player.h>

#include "game.h"

void initSubSprites(void) {
	oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
 
	int x = 0;
	int y = 0;
 
	int id = 0;
	for(y = 0; y < 3; y++) {
        for(x = 0; x < 4; x++) {
            oamSub.oamMemory[id].attribute[0] = ATTR0_BMP | ATTR0_SQUARE | (64 * y);
            oamSub.oamMemory[id].attribute[1] = ATTR1_SIZE_64 | (64 * x);
            oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);
            id++;
        }
    }
 
	swiWaitForVBlank();
	oamUpdate(&oamSub);
}

int main() {
    touchPosition touch;

    videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);

	initSubSprites();
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	glScreen2D();

	vramSetBankA(VRAM_A_TEXTURE); // 128 kb
	vramSetBankB(VRAM_B_TEXTURE); // 128 kb

    vramSetBankF(VRAM_F_TEX_PALETTE); // ?
    vramSetBankE(VRAM_E_MAIN_BG); // 64 kb

    // Game
    int frame = 0;
    Game game;
    game.playerX = 128 - 16;
    game.playerY = 2 * 192 - 32;
    game.objectX = 128 - 16;
    game.objectY = 0;
    game.score = 0;
    game.started = 0;
    game.lost = 0;

    // Load textures
    const unsigned int texcoords[] = {0, 0, 32, 32};
	glLoadSpriteSet(
        &game.playerSprite, 1, texcoords, GL_RGB256, TEXTURE_SIZE_32, TEXTURE_SIZE_32,
		GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
		256, (u16*)playerPal, (u8*)playerBitmap
	);
    glLoadSpriteSet(
        &game.objectSprite, 1, texcoords, GL_RGB256, TEXTURE_SIZE_32, TEXTURE_SIZE_32,
        GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
        256, (u16*)spinashPal, (u8*)spinashBitmap
    );

    while(1) {
        // Read touch position
        scanKeys();
		int held = keysHeld();
		if (held & KEY_TOUCH) {
			touchRead(&touch);
            game.started = 1;
            game.playerX = touch.px - 16;
        }

        // Draw things
        glBegin2D();
        if ((frame & 1) == 0) {
            lcdMainOnTop();
			vramSetBankD(VRAM_D_LCD);
			vramSetBankC(VRAM_C_SUB_BG);
			REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
            renderMainScreen(&game);
        } else {
            lcdMainOnBottom();
			vramSetBankC(VRAM_C_LCD);
			vramSetBankD(VRAM_D_SUB_SPRITE);
			REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
            renderSubScreen(&game);
        }

        glEnd2D();

        // Wait for the screen to refresh
        glFlush(0);
        swiWaitForVBlank();
        frame++;
        if (game.started) {
            nextFrame(&game);
        }    
    }

    return 0;
}
