#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1400;
const int HEIGHT = 900;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_TIMER* fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = { false };
bool key_state2[ALLEGRO_KEY_MAX] = { false };
bool judge_next_window = false;


typedef struct character
{
    int x, y; // the position of image
    float vely; // velocity of image
    int speed; // moving speed
    bool jump; // no:false, jump:true
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP* img_move[2];
    ALLEGRO_BITMAP* img_atk[3];
    ALLEGRO_BITMAP* img_jump[1];
    ALLEGRO_BITMAP* img_die[2];


    ALLEGRO_SAMPLE_INSTANCE* atk_Sound;
    ALLEGRO_SAMPLE_INSTANCE* jump_Sound;
    ALLEGRO_SAMPLE_INSTANCE* die_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;


// add --- detect collision: if chara1 attack on chara2 ?
bool collision(Character chara1, Character chara2) {
    int range = 20;
    // dir is totally wrong
    if (chara2.x <= chara1.x && chara1.dir || chara2.x >= chara1.x && !chara1.dir) return false;

    // chara1 turns right, and chara2 is at his right
    // chara1 turns left, and chara2 is at his left
    if (sqrt(pow(chara1.x - chara2.x, 2) + pow(chara1.y - chara2.y, 2)) <= range) {
        return true;
    }
    return false;
}

