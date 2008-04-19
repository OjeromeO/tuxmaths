//
// C Interface: SDL_extras
//
// Description: A few handy functions for using SDL graphics.
//
//
// Author: David Bruce,,, <dbruce@tampabay.rr.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
// (briefly, GPL v3 or later).
//

#ifndef SDL_EXTRAS_H
#define SDL_EXTRAS_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xff000000
#define gmask 0x00ff0000
#define bmask 0x0000ff00
#define amask 0x000000ff
#else
#define rmask 0x000000ff
#define gmask 0x0000ff00
#define bmask 0x00ff0000
#define amask 0xff000000
#endif

void DrawButton(SDL_Rect* target_rect, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void RoundCorners(SDL_Surface* s, Uint16 radius);
SDL_Surface* Flip(SDL_Surface *in, int x, int y);
SDL_Surface* BlackOutline(unsigned char *t, TTF_Font* font, SDL_Color* c);
int  inRect(SDL_Rect r, int x, int y);
void DarkenScreen(Uint8 bits);
void SwitchScreenMode(void);
SDL_Surface* Blend(SDL_Surface *S1, SDL_Surface *S2,float gamma);

#endif
