#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1400;
const int HEIGHT = 900;
int dead1 = 0;
int dead2 = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool key_state2[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;

