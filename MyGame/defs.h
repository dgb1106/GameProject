#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define WINDOW_TITLE "MiniGolf"
#define WINDOW_ICON "assets\\images\\WindowIcon.png"

const SDL_Color BLACK_COLOR = {0, 0, 0, 255};
const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color GOLD_COLOR = {255, 215, 0, 255};
const SDL_Color BRIGHT_PINK_COLOR = {241, 65, 116, 255};

const double PI = 3.1415;
const int FPS = 60;
const int frameDelay = 1000 / FPS;

const int GAMEOVER_STATUS = -1;
const int MENU_STATUS = 0;
const int PLAYING_STATUS = 1;
const int COMPLETED_STATUS = 2;
const int GUIDE_STATUS = 3;

#define MENU_IMG "assets\\images\\menu.png"
#define GUIDE_IMG "assets\\images\\guide.png"
#define BACKGROUND_IMG "assets\\images\\Background.png"
#define COMPLETE_IMG "assets\\images\\Complete.png"
#define GAMEOVER_IMG "assets\\images\\GameOver.png"

#define BACKBUTTON_WHITE "assets\\images\\BackButton_White.png"
#define BACKBUTTON_GOLD "assets\\images\\BackButton_Gold.png"

#define BALL_IMG "assets\\images\\Ball.png"
#define HOLE_IMG "assets\\images\\Hole.png"
#define PAINT_IMG "assets\\images\\Paint.png"
#define ARROW_IMG "assets\\images\\arrow.png"
#define TILE64_IMG "assets\\images\\Tile64.png"
#define TILE32_IMG "assets\\images\\Tile32.png"
#define TILEHORIZONTAL_IMG "assets\\images\\TileHorizontal.png"
#define TILEVERTICAL_IMG "assets\\images\\TileVertical.png"
#define CACTUS_IMG "assets\\images\\cactus.png"
#define SLIME_IMG "assets\\images\\slime.png"

#define CURSOR_IMG "assets\\images\\cursorRacket.png"

#define BG_MUSIC "assets\\sounds\\GameMusic.mp3"
#define HIT_SOUND "assets\\sounds\\BallHit.wav"
#define BOUNCE_SOUND "assets\\sounds\\Bounce.wav"
#define LEVELUP_SOUND "assets\\sounds\\LevelUp.wav"
#define FINALWIN_SOUND "assets\\sounds\\FinalWin.wav"
#define GAMEOVER_SOUND "assets\\sounds\\GameOver.wav"

#define FONT_KAPH "assets\\fonts\\Kaph-Regular.ttf"
#define FONT_CROCANTE "assets\\fonts\\iciel-crocante.ttf"
#define FONT_WIGGLYE "assets\\fonts\\Wigglye.ttf"
const int STROKES_TEXT_SIZE = 24;
const int PLAY_TEXT_SIZE = 36;
const int TITLE_TEXT_SIZE = 116;

const int BORDER_SIZE_HORIZONTAL = 16;
const int BORDER_SIZE_VERTICAL = 13;

const int BALL_SIZE = 24;
const double FRICTION = 0.95;

const double AMPLITUDE = 64.0;
const double FREQUENCY = 0.5;

const double STANDARD_DURATION = 30.0;

#endif // _DEFS__H
