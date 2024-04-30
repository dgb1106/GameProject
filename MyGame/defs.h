#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define WINDOW_TITLE "MiniGolf"

const int FPS = 60;
const int frameDelay = 1000 / FPS;

#define BACKGROUND_IMG "assets\\Background.png"
#define BALL_IMG "assets\\Ball.png"
#define HOLE_IMG "assets\\Hole.png"
#define PAINT_IMG "assets\\Paint.png"
#define TILE64_IMG "assets\\Tile64.png"
#define TILE32_IMG "assets\\Tile32.png"
#define TILEHORIZONTAL_IMG "assets\\TileHorizontal.png"
#define TILEVERTICAL_IMG "assets\\TileVertical.png"

#define BG_MUSIC "assets\\sounds\\GameMusic.mp3"
#define HIT_SOUND "assets\\sounds\\BallHit.wav"
#define BOUNCE_SOUND "assets\\sounds\\Bounce.wav"
#define LEVELUP_SOUND "assets\\sounds\\LevelUp.wav"
#define FINALWIN_SOUND "assets\\sounds\\FinalWin.wav"

#define FONT_KAPH "assets\\fonts\\Kaph-Regular.ttf"
const int STROKES_SIZE = 24;

const int BORDER_SIZE_HORIZONTAL = 16;
const int BORDER_SIZE_VERTICAL = 13;

const int BALL_SIZE = 24;
const double FRICTION = 0.95;

#endif // _DEFS__H
