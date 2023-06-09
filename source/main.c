#include <nds.h>
#include <gl2d.h>
#include <time.h>

#include <spinash.h>
#include <player.h>
#include <font_si.h>
#include <font_16x16.h>

#include "menu.h"
#include "game.h"
#include "font.h"
#include "uvcoord_font_si.h"
#include "uvcoord_font_16x16.h"

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
    srand((unsigned) time(NULL));

    touchPosition touch;

    glImage FontImages[FONT_SI_NUM_IMAGES];
    glImage FontBigImages[FONT_16X16_NUM_IMAGES];
    Font font;
    Font fontBig;

    videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);

	initSubSprites();
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	glScreen2D();

	vramSetBankA(VRAM_A_TEXTURE); // 128 kb
	vramSetBankB(VRAM_B_TEXTURE); // 128 kb

    vramSetBankF(VRAM_F_TEX_PALETTE); // ?
    vramSetBankE(VRAM_E_MAIN_BG); // 64 kb

    // Menu
    Menu menu;
    menu.mode = 0;
    menu.play = 0;

    // Game
    int frame = 0;
    Game game;

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
    loadFont(
        &font, FontImages, FONT_SI_NUM_IMAGES, font_si_texcoords, GL_RGB256,
		TEXTURE_SIZE_64, TEXTURE_SIZE_128,
        GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
		256, (u16*)font_siPal, (u8*)font_siBitmap
    );
    loadFont(
        &fontBig, FontBigImages, FONT_16X16_NUM_IMAGES, font_16x16_texcoords, GL_RGB256,
		TEXTURE_SIZE_64, TEXTURE_SIZE_512,
        GL_TEXTURE_WRAP_S|GL_TEXTURE_WRAP_T|TEXGEN_OFF|GL_TEXTURE_COLOR0_TRANSPARENT,
		256, (u16*)font_siPal, (u8*)font_16x16Bitmap
    );

    while(1) {
        // Read touch position
        scanKeys();
		int held = keysHeld();
		if (held & KEY_TOUCH) {
			touchRead(&touch);
            if (menu.play) {
                handleGameTouch(&game, touch);
            } else {
                handleMenuTouch(&menu, &game, touch);
            }
        } else {
            if (menu.play) {
                handleGameKey(&game, held);
                handleGameMenuKey(&game, &menu, held);
            } else {
                handleMenuKey(&menu, &game, held);
            }
        }

        // Draw things
        glBegin2D();
        if ((frame & 1) == 0) {
            lcdMainOnTop();
			vramSetBankD(VRAM_D_LCD);
			vramSetBankC(VRAM_C_SUB_BG);
			REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
            if (menu.play) {
                renderGameMainScreen(&game, &fontBig);
            } else {
                renderMenuMainScreen(&menu, &fontBig);
            }
        } else {
            lcdMainOnBottom();
			vramSetBankC(VRAM_C_LCD);
			vramSetBankD(VRAM_D_SUB_SPRITE);
			REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
            if (menu.play) {
                renderGameSubScreen(&game, &fontBig);
            } else {
                renderMenuSubScreen(&menu, &fontBig);
            }
        }

        glEnd2D();

        // Wait for the screen to refresh
        glFlush(0);
        swiWaitForVBlank();
        frame++;
        if (menu.play && game.started) {
            nextFrame(&game);
        }    
    }

    return 0;
}
