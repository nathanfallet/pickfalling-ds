#ifndef FONT_H
#define FONT_H

#include <nds.h>
#include <stdio.h>
#include <gl2d.h>

typedef struct {
	glImage *font_sprite;
	char str[256];
	char str2[256];
} Font;

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
);

void printFont(Font *font, int x, int y, const char *text);
void printFontN(Font *font, int x, int y, int value);
void printFontCentered(Font *font, int x, int y, const char *text);
void printFontCenteredN(Font *font, int x, int y, int value);

#endif
