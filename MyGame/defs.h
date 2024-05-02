#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define WINDOW_TITLE "MiniGolf"

const SDL_Color BLACK_COLOR = {0, 0, 0, 255};
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color GOLD_COLOR = {255, 215, 0, 255};

const double PI = 3.1415;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

#define MENU_IMG "assets\\images\\menu.png"
#define BACKGROUND_IMG "assets\\images\\Background.png"
#define COMPLETE_IMG "assets\\images\\Complete.png"

#define BALL_IMG "assets\\images\\Ball.png"
#define HOLE_IMG "assets\\images\\Hole.png"
#define PAINT_IMG "assets\\images\\Paint.png"
#define ARROW_IMG "assets\\images\\arrow.png"
#define TILE64_IMG "assets\\images\\Tile64.png"
#define TILE32_IMG "assets\\images\\Tile32.png"
#define TILEHORIZONTAL_IMG "assets\\images\\TileHorizontal.png"
#define TILEVERTICAL_IMG "assets\\images\\TileVertical.png"
#define SPIKE_IMG "assets\\images\\spike.png"

#define CURSOR_IMG "assets\\images\\cursorRacket.png"

#define BG_MUSIC "assets\\sounds\\GameMusic.mp3"
#define HIT_SOUND "assets\\sounds\\BallHit.wav"
#define BOUNCE_SOUND "assets\\sounds\\Bounce.wav"
#define LEVELUP_SOUND "assets\\sounds\\LevelUp.wav"
#define FINALWIN_SOUND "assets\\sounds\\FinalWin.wav"

#define FONT_KAPH "assets\\fonts\\Kaph-Regular.ttf"
#define FONT_CROCANTE "assets\\fonts\\iciel-crocante.ttf"
const int STROKES_TEXT_SIZE = 24;
const int PLAY_TEXT_SIZE = 36;

const int BORDER_SIZE_HORIZONTAL = 16;
const int BORDER_SIZE_VERTICAL = 13;

const int BALL_SIZE = 24;
const double FRICTION = 0.95;

#endif // _DEFS__H
