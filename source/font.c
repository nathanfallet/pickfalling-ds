#include "font.h"

int loadFont(
	Font *font,
	glImage *_font_sprite,
	const unsigned int numframes,
	const unsigned int *texcoords,
	GL_TEXTURE_TYPE_ENUM type,
	int sizeX,
	int sizeY,
	int param,
	int pallette_width,
	const u16 *palette,
	const uint8 *texture
) {
	font->font_sprite = _font_sprite;

	int textureID = glLoadSpriteSet(
		font->font_sprite,
		numframes,
		texcoords,
		type,
		sizeX,
		sizeY,
		param,
		pallette_width,
		palette,
		texture
	);

	return textureID;
}

void printFont(Font *font, int x, int y, const char *text) {
	unsigned char font_char;

	while (*text) {
		font_char = (*(unsigned char *)text++) - 32;
		glSprite(x, y, GL_FLIP_NONE, &font->font_sprite[font_char]);
		x += font->font_sprite[font_char].width;
	}
}

void printFontN(Font *font, int x, int y, int value) {
	sprintf(font->str, "%i", value);

	printFont(font, x, y, font->str);
}

void printFontCentered(Font *font, int x, int y, const char *text) {
	unsigned char font_char;
	int total_width = 0;
	char *o_text = (char *)text;

	while (*text) {
		font_char = (*(unsigned char *)text++) - 32;
		total_width += font->font_sprite[font_char].width;
	}

	x = (SCREEN_WIDTH - total_width) / 2;

	text = o_text;
	while (*text) {
		font_char = (*(unsigned char *)text++) - 32;
		glSprite(x, y, GL_FLIP_NONE, &font->font_sprite[font_char]);
		x += font->font_sprite[font_char].width;
	}
}

void printFontCenteredN(Font *font, int x, int y, int value) {
	sprintf(font->str, "%i", value);
	printFontCentered(font, x, y, font->str);
}
