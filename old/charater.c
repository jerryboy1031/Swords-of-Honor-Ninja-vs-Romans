#include "charater.h"


// the state of character
enum { STOP = 0, MOVE, ATK, JUMP, DEAD ,HURT}; // add JUMP, DEAD
typedef struct character{
    int x, y; // the position of image
    float vely; // velocity of image
    int speed; // moving speed
    bool jump; // no:false, jump:true
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[3];
    ALLEGRO_BITMAP* img_jump[1];
    ALLEGRO_BITMAP* img_die[2];

    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE_INSTANCE* jump_Sound;
    ALLEGRO_SAMPLE_INSTANCE* die_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;
// create character object: chara
Character chara[2];
ALLEGRO_SAMPLE* sample_atk = NULL, * sample_jump = NULL, * sample_die = NULL; // initialize three sounds ptr
ALLEGRO_SAMPLE* sample_atk2 = NULL, * sample_jump2 = NULL, * sample_die2 = NULL;

//  change files------------------------------------
void character_init(){
    // load P1 images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[70];
        sprintf( temp, "./image/move%d.png", i );  // change file
        chara[0].img_move[i-1] = al_load_bitmap(temp);
    }
    // attack fig
    for(int i = 1 ; i <= 3 ; i++){
        char temp[50];
        sprintf( temp, "./image/attack%d.png", i );
        chara[0].img_atk[i-1] = al_load_bitmap(temp);
    }
    // jump fig
    chara[0].img_jump[0] = al_load_bitmap("./image/jump1.png");
    //dead fig
    for (int i = 1; i <= 2; i++) {
        char temp[50];
        sprintf(temp, "./image/die%d.png", i);
        chara[0].img_die[i - 1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample_atk = al_load_sample("./sound/atk_sound.wav"); // attack sound
    sample_jump = al_load_sample("./sound/jump_sound.wav"); // attack sound
    sample_die = al_load_sample("./sound/die_sound.wav"); // attack sound
    // *4 speed (ATK sound)
    float playbackSpeed = 4.0; // Desired playback speed (4x faster)
    al_set_sample_instance_speed(sample_atk, playbackSpeed);
    chara[0].atk_Sound = al_create_sample_instance(sample_atk);
    chara[0].jump_Sound = al_create_sample_instance(sample_jump);
    chara[0].die_Sound = al_create_sample_instance(sample_die);

    al_set_sample_instance_playmode(chara[0].atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara[0].jump_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara[0].die_Sound, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(chara[0].atk_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara[0].jump_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara[0].die_Sound, al_get_default_mixer());

    // initial the geometric information of P1
    chara[0].width = al_get_bitmap_width(chara[0].img_move[0]);
    chara[0].height = al_get_bitmap_height(chara[0].img_move[0]);
    // initial position
    chara[0].x = 10;//WIDTH/2;
    chara[0].y = HEIGHT; //HEIGHT/2;
    chara[0].dir = true;
    chara[0].jump = false;
    // initial speed
    chara[0].speed = 3;
    // initial the animation component
    chara[0].state = STOP;
    chara[0].anime = 0;
    chara[0].anime_time = 20; // the shorter time, the faster the image updates

    // load P2 images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[70];
        sprintf( temp, "./image/move2%d.png", i );  // change file
        chara[1].img_move[i-1] = al_load_bitmap(temp);
    }
    // attack fig
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/attack2%d.png", i );
        chara[1].img_atk[i-1] = al_load_bitmap(temp);
    }
    // jump fig
    chara[1].img_jump[0] = al_load_bitmap("./image/jump21.png");
    //dead fig
    for (int i = 1; i <= 2; i++) {
        char temp[50];
        sprintf(temp, "./image/die2%d.png", i);
        chara[1].img_die[i - 1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample_atk2 = al_load_sample("./sound/atk_sound.wav"); // attack sound
    sample_jump2 = al_load_sample("./sound/jump_sound.wav"); // attack sound
    sample_die2 = al_load_sample("./sound/die_sound.wav"); // attack sound
    // *4 speed (ATK sound)
    float playbackSpeed2 = 4.0; // Desired playback speed (4x faster)
    al_set_sample_instance_speed(sample_atk2, playbackSpeed2);
    chara[1].atk_Sound = al_create_sample_instance(sample_atk2);
    chara[1].jump_Sound = al_create_sample_instance(sample_jump2);
    chara[1].die_Sound = al_create_sample_instance(sample_die2);

    al_set_sample_instance_playmode(chara[1].atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara[1].jump_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara[1].die_Sound, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(chara[1].atk_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara[1].jump_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara[1].die_Sound, al_get_default_mixer());

    // initial the geometric information of character2
    chara[1].width = al_get_bitmap_width(chara[1].img_move[0]);
    chara[1].height = al_get_bitmap_height(chara[1].img_move[0]);
    // initial position
    chara[1].x = WIDTH - 20;
    chara[1].y = HEIGHT; //HEIGHT/2;
    chara[1].dir = false;
    chara[1].jump = false;
    // initial speed
    chara[1].speed = 3;
    // initial the animation component
    chara[1].state = STOP;
    chara[1].anime = 0;
    chara[1].anime_time = 20; // the shorter time, the faster the image updates
}


void charater_process(ALLEGRO_EVENT event){
    // process the P1 animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara[0].anime++;
            chara[0].anime %= chara[0].anime_time;
        }
    // process the keyboard event
    // key pressed
    }
    else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara[0].anime = 0;
    // key realeased
    }
    else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
    // process the P2 animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara[1].anime++;
            chara[1].anime %= chara[1].anime_time;
        }
    // process the keyboard event
    // key pressed
    }
    else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state2[event.keyboard.keycode] = true;
        chara[1].anime = 0;
    // key realeased
    }
    else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state2[event.keyboard.keycode] = false;
    }
}

// change speed, keyboard-------------------------
void charater_update(){
    // P1
    if (key_state[ALLEGRO_KEY_S]) {
        chara[0].speed *= 3;
    }

    // change to jump!!
    if( key_state[ALLEGRO_KEY_W] && chara[0].jump){
        chara[0].vely = -40; // negative is jump upwaed
        chara[0].state = JUMP;
        chara[0].jump = false;
    }
    if (key_state[ALLEGRO_KEY_A]) {
        chara[0].dir = false;
        chara[0].x -= chara[0].speed;
        chara[0].state = MOVE;
    }
    else if( key_state[ALLEGRO_KEY_D] ){
        chara[0].dir = true;
        chara[0].x += chara[0].speed;
        chara[0].state = MOVE;
    }
    else if( key_state[ALLEGRO_KEY_SPACE] ){
        chara[0].state = ATK;
    }
    else if( chara[0].anime == chara[0].anime_time-1 ){
        chara[0].anime = 0; //�k�s
        chara[0].state = STOP;
    }
    else if ( chara[0].anime == 0 ){
        chara[0].state = STOP;
    }
    // jump statement
    if (!chara[0].jump) chara[0].vely += 4; // gravity
    else chara[0].vely = 0;
    chara[0].y += chara[0].vely;
    // the (head posi(y) + chara[0] height(32)) is under ground(screen size), return false when falling to ground
    chara[0].jump = (chara[0].y + chara[0].height >= HEIGHT);
    // remain jump pose in the air (30 up)
    if (chara[0].y + chara[0].height < HEIGHT -30) chara[0].state = JUMP;
    // change speed back to initial value
    chara[0].speed = 3;
    // boundary setting5
    // vertical limit
    if (chara[0].jump) chara[0].y = HEIGHT - chara[0].height;
    // horizontal limit
    if (chara[0].x + chara[0].width > WIDTH) chara[0].x = WIDTH - chara[0].width;
    if (chara[0].x < 0) chara[0].x = 0;
    //dead state
    if (blood1 <= 0) dead = 1;

    // P2

    if (key_state2[ALLEGRO_KEY_DOWN]) {
        chara[1].speed *= 3;
    }

    // change to jump!!
    if (key_state2[ALLEGRO_KEY_UP] && chara[1].jump) {
        chara[1].vely = -40; // negative is jump upwaed
        chara[1].state = JUMP;
        chara[1].jump = false;
    }

    else if (key_state2[ALLEGRO_KEY_LEFT]) {
        chara[1].dir = false;
        chara[1].x -= chara[1].speed;
        chara[1].state = MOVE;
    }
    else if( key_state2[ALLEGRO_KEY_RIGHT]){
        chara[1].dir = true;
        chara[1].x += chara[1].speed;
        chara[1].state = MOVE;
    }
    else if( key_state2[ALLEGRO_KEY_ALTGR] ){
        chara[1].state = ATK;
    }
    else if( chara[1].anime == chara[1].anime_time-1 ){
        chara[1].anime = 0; //�k�s
        chara[1].state = STOP;
    }
    else if ( chara[1].anime == 0 ){
        chara[1].state = STOP;
    }
    // jump statement
    if (!chara[1].jump) chara[1].vely += 4; // gravity
    else chara[1].vely = 0;
    chara[1].y += chara[1].vely;
    // the (head posi(y) + chara[1] height(32)) is under ground(screen size), return false when falling to ground
    chara[1].jump = (chara[1].y + chara[1].height >= HEIGHT);
    // remain jump pose in the air (30 up)
    if (chara[1].y + chara[1].height < HEIGHT -30) chara[1].state = JUMP;
    // change speed back to initial value
    chara[1].speed = 3;
    // boundary setting
    // vertical limit
    if (chara[1].jump) chara[1].y = HEIGHT - chara[1].height;
    // horizontal limit
    if (chara[1].x + chara[1].width > WIDTH) chara[1].x = WIDTH - chara[1].width;
    if (chara[1].x < 0) chara[1].x = 0;
    //dead state
    if (blood2 <= 0) dead = 1;
}

// �j��---------------------------------
void character_draw() { // with the state, draw corresponding image


    //P1 ---------------------------------------------------------------
    if (chara[0].state == STOP) {// STOP: nothing
        // ��½��
        if (chara[0].dir)
            al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
        // ����½��
        else
            al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, 0);
    }
    else if (chara[0].state == MOVE) {
        if (chara[0].dir) {
            if (chara[0].anime < chara[0].anime_time / 2) {
                al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_draw_bitmap(chara[0].img_move[1], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else {
            if (chara[0].anime < chara[0].anime_time / 2) {
                al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, 0);
            }
            else {
                al_draw_bitmap(chara[0].img_move[1], chara[0].x, chara[0].y, 0);
            }
        }
    }

    //  ensure better synchronization between the attack sound and movement
    if (chara[0].state == ATK) {
        if (chara[0].dir) {
            if (chara[0].anime < chara[0].anime_time / 4) {
                al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                static int attackFrame = 0;  // Variable to track the current attack frame
                static bool soundPlayed = false;  // Variable to track if the sound has been played
                static int attackDelay = 0;  // Variable to track the delay between each attack frame and sound sample
                al_draw_bitmap(chara[0].img_atk[attackFrame], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
                if (!soundPlayed) {
                    // Play the sound only once
                    al_play_sample_instance(chara[0].atk_Sound);
                    soundPlayed = true;
                }
                attackDelay++;  // Increment the delay counter
                if (attackDelay >= 10) {  // Change this value to adjust the speed of the attack
                    // Move to the next attack frame and reset the delay counter
                    attackFrame++;
                    attackDelay = 0;
                }
                if (attackFrame >= 3) {
                    // Reset the attack animation
                    attackFrame = 0;
                    chara[0].state = MOVE;  // Transition to MOVE state or desired state after the attack animation
                    soundPlayed = false;  // Reset the sound flag
                }
                else {
                    // Check if the sound is still playing or not
                    unsigned int pos = al_get_sample_instance_position(chara[0].atk_Sound);
                    unsigned int len = al_get_sample_instance_length(chara[0].atk_Sound);
                    if (pos >= len) {
                        // The sound has finished playing, stop the instance
                        al_stop_sample_instance(chara[0].atk_Sound);
                        soundPlayed = false;  // Reset the sound flag
                    }
                }
            }
        }
        else {
            if (chara[0].anime < chara[0].anime_time / 4) {
                al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y,0);
            }
            else {
                static int attackFrame = 0;  // Variable to track the current attack frame
                static bool soundPlayed = false;  // Variable to track if the sound has been played
                static int attackDelay = 0;  // Variable to track the delay between each attack frame and sound sample
                al_draw_bitmap(chara[0].img_atk[attackFrame], chara[0].x, chara[0].y, 0);
                if (!soundPlayed) {
                    // Play the sound only once
                    al_play_sample_instance(chara[0].atk_Sound);
                    soundPlayed = true;
                }
                attackDelay++;  // Increment the delay counter
                if (attackDelay >= 10) {  // Change this value to adjust the speed of the attack
                    // Move to the next attack frame and reset the delay counter
                    attackFrame++;
                    attackDelay = 0;
                }
                if (attackFrame >= 3) {
                    // Reset the attack animation
                    attackFrame = 0;
                    chara[0].state = MOVE;  // Transition to MOVE state or desired state after the attack animation
                    soundPlayed = false;  // Reset the sound flag
                }
                else {
                    // Check if the sound is still playing or not
                    unsigned int pos = al_get_sample_instance_position(chara[0].atk_Sound);
                    unsigned int len = al_get_sample_instance_length(chara[0].atk_Sound);
                    if (pos >= len) {
                        // The sound has finished playing, stop the instance
                        al_stop_sample_instance(chara[0].atk_Sound);
                        soundPlayed = false;  // Reset the sound flag
                    }
                }
            }
        }
        if (character_collision(0)) {
            chara[1].state = HURT;
        }
    }

    // JUMP-- 1 fig
    else if (chara[0].state == JUMP) {
        al_play_sample_instance(chara[0].jump_Sound);
        if (chara[0].dir) al_draw_bitmap(chara[0].img_jump[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_bitmap(chara[0].img_jump[0], chara[0].x, chara[0].y, 0);
    }

    //DEAD--2 figs
    else if (chara[0].state == DEAD) {
        al_play_sample_instance(chara[0].die_Sound);
        if (chara[0].dir) {
            if (chara[0].anime < chara[0].anime_time / 2) {
                al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_play_sample_instance(chara[0].atk_Sound);
                for (int i = 0; i <=1; i++) {
                    al_draw_bitmap(chara[0].img_die[i], chara[0].x, chara[0].y+200, ALLEGRO_FLIP_HORIZONTAL);
                    //al_rest(0.02);
                }
            }
        }
        else{
            if (chara[0].anime < chara[0].anime_time / 2) {
                al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, 0);
            }
            else {
                al_play_sample_instance(chara[0].atk_Sound);
                for (int i = 0; i <= 1; i++) {
                    al_draw_bitmap(chara[0].img_die[i], chara[0].x, chara[0].y+200, 0);
                }
            }
        }
    }

    // HURT -- sub_bitmap
    else if (chara[0].state == HURT) {
        if (chara[0].dir) {
            al_draw_tinted_bitmap(chara[0].img_move[0], al_map_rgb(255, 0, 0), chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
        }
        else al_draw_tinted_bitmap(chara[0].img_move[0], al_map_rgb(255, 0, 0), chara[0].x, chara[0].y,0);
        blood1 -= 10.0/17;
    }

    //P2 ---------------------------------------------------------------
    if( chara[1].state == STOP ){
        // ��½��
        if( chara[1].dir )
            al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
        // ����½��
        else
            al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, 0);
    }
    else if( chara[1].state == MOVE ){
        if( chara[1].dir ){
            if( chara[1].anime < chara[1].anime_time/2 ){
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(chara[1].img_move[1], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }else{
            if( chara[1].anime < chara[1].anime_time/2 ){
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, 0);
            }else{
                al_draw_bitmap(chara[1].img_move[1], chara[1].x, chara[1].y, 0);
            }
        }
    }


   if (chara[1].state == ATK) {
        if (chara[1].dir) {
            if (chara[1].anime < chara[1].anime_time / 3) {
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                static int attackFrame = 0;  // Variable to track the current attack frame
                static bool soundPlayed = false;  // Variable to track if the sound has been played
                static int attackDelay = 0;  // Variable to track the delay between each attack frame and sound sample

                if (attackFrame == 0) al_draw_bitmap(chara[1].img_atk[attackFrame], chara[1].x, chara[1].y , ALLEGRO_FLIP_HORIZONTAL);
                else if (attackFrame == 1)  al_draw_bitmap(chara[1].img_atk[attackFrame], chara[1].x+30, chara[1].y+ 40, ALLEGRO_FLIP_HORIZONTAL);

                if (!soundPlayed) {
                    // Play the sound only once
                    al_play_sample_instance(chara[1].atk_Sound);
                    soundPlayed = true;
                }
                attackDelay++;  // Increment the delay counter
                if (attackDelay >= 1) {  // Change this value to adjust the speed of the attack
                    // Move to the next attack frame and reset the delay counter
                    attackFrame++;
                    attackDelay = 0;
                }

                if (attackFrame >= 2) {
                    // Reset the attack animation
                    attackFrame = 0;
                    chara[1].state = MOVE;  // Transition to MOVE state or desired state after the attack animation
                    soundPlayed = false;  // Reset the sound flag
                }
                else {
                    // Check if the sound is still playing or not
                    unsigned int pos = al_get_sample_instance_position(chara[1].atk_Sound);
                    unsigned int len = al_get_sample_instance_length(chara[1].atk_Sound);
                    if (pos >= len) {
                        // The sound has finished playing, stop the instance
                        al_stop_sample_instance(chara[1].atk_Sound);
                        soundPlayed = false;  // Reset the sound flag
                    }
                }
            }
        }
        else {
            if (chara[1].anime < chara[1].anime_time / 3) {
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y,0);
            }
            else {
                static int attackFrame = 0;  // Variable to track the current attack frame
                static bool soundPlayed = false;  // Variable to track if the sound has been played
                static int attackDelay = 0;  // Variable to track the delay between each attack frame and sound sample

                if (attackFrame == 0) al_draw_bitmap(chara[1].img_atk[attackFrame], chara[1].x, chara[1].y, 0);
                else if (attackFrame == 1)  al_draw_bitmap(chara[1].img_atk[attackFrame], chara[1].x - 30, chara[1].y+40, 0);
                if (!soundPlayed) {
                    // Play the sound only once
                    al_play_sample_instance(chara[1].atk_Sound);
                    soundPlayed = true;
                }
                attackDelay++;  // Increment the delay counter
                if (attackDelay >= 10) {  // Change this value to adjust the speed of the attack
                    // Move to the next attack frame and reset the delay counter
                    attackFrame++;
                    attackDelay = 0;
                }
                if (attackFrame >= 2) {
                    // Reset the attack animation
                    attackFrame = 0;
                    chara[1].state = MOVE;  // Transition to MOVE state or desired state after the attack animation
                    soundPlayed = false;  // Reset the sound flag
                }
                else {
                    // Check if the sound is still playing or not
                    unsigned int pos = al_get_sample_instance_position(chara[1].atk_Sound);
                    unsigned int len = al_get_sample_instance_length(chara[1].atk_Sound);
                    if (pos >= len) {
                        // The sound has finished playing, stop the instance
                        al_stop_sample_instance(chara[1].atk_Sound);
                        soundPlayed = false;  // Reset the sound flag
                    }
                }
            }
        }
        if (character_collision(1)) {
            chara[0].state = HURT;

        }
    }

    // JUMP-- 1 fig
    else if (chara[1].state == JUMP) {
        if (chara[1].dir) al_draw_bitmap(chara[1].img_jump[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_bitmap(chara[1].img_jump[0], chara[1].x, chara[1].y, 0);
    }

    //DEAD--2 figs
    else if (chara[1].state == DEAD) {
        if (chara[1].dir) {
            if (chara[1].anime < chara[1].anime_time / 2) {
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_play_sample_instance(chara[1].atk_Sound);
                for (int i = 0; i <=1; i++) {
                    al_draw_bitmap(chara[1].img_die[i], chara[1].x, chara[1].y+200, ALLEGRO_FLIP_HORIZONTAL);
                    //al_rest(0.02);
                }
            }
        }
        else{
            if (chara[1].anime < chara[1].anime_time / 2) {
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, 0);
            }
            else {
                al_play_sample_instance(chara[1].atk_Sound);
                for (int i = 0; i <= 1; i++) {
                    al_draw_bitmap(chara[1].img_die[i], chara[1].x, chara[1].y+200, 0);
                }
            }
        }
    }

    // HURT -- sub_bitmap
    else if (chara[1].state == HURT) {
        if (chara[1].dir) {
            al_draw_tinted_bitmap(chara[1].img_move[0], al_map_rgb(255, 0, 0), chara[1].x , chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
        }
        else al_draw_tinted_bitmap(chara[1].img_move[0], al_map_rgb(255, 0, 0), chara[1].x, chara[1].y, NULL);
        blood2 -= 10.0 / 17; //
    }
}

void character_destory(){
    //P1
    for(int i=0;i<=1;i++){
        al_destroy_bitmap(chara[0].img_move[i]);
    }

    for(int i=0;i<=2;i++){
        al_destroy_bitmap(chara[0].img_atk[i]);
    }

    al_destroy_bitmap(chara[0].img_jump[0]);

    for(int i=0;i<=1;i++){
        al_destroy_bitmap(chara[0].img_die[i]);
    }

    al_destroy_sample_instance(chara[0].atk_Sound);
    al_destroy_sample_instance(chara[0].jump_Sound);
    al_destroy_sample_instance(chara[0].die_Sound);

    //P2
    for(int i=0;i<=1;i++){
        al_destroy_bitmap(chara[1].img_move[i]);
    }

    for(int i=0;i<=1;i++){
        al_destroy_bitmap(chara[1].img_atk[i]);
    }

    al_destroy_bitmap(chara[1].img_jump[0]);

    for(int i=0;i<=1;i++){
        al_destroy_bitmap(chara[1].img_die[i]);
    }

    al_destroy_sample_instance(chara[1].atk_Sound);
    al_destroy_sample_instance(chara[1].jump_Sound);
    al_destroy_sample_instance(chara[1].die_Sound);
}

// add --- detect collision: if attacker attacks on other?-------------------------------
int character_collision(int attacker) {
    int range = 200;
    // dir is totally wrong
    if (chara[attacker].x >= chara[attacker^1].x && chara[attacker].dir || (chara[attacker].x + chara[attacker].width <= chara[attacker ^ 1].x+ chara[attacker ^ 1].width )&& !chara[attacker].dir) {
        return 0;
    }
    // chara1 turns right, and chara2 is at his right
    if (chara[attacker].dir) {
        if (sqrt(pow(chara[0].x - chara[1].x, 2) + pow(chara[0].y + chara[0].height / 2 - chara[1].y - chara[1].height / 2, 2)) <= range) {
            return 1;
        }
        return 0;
    }
    // chara1 turns left, and chara2 is at his left
    else {
        if (sqrt(pow(chara[0].x+ chara[0].width - chara[1].x- chara[1].width, 2) + pow(chara[0].y + chara[0].height / 2 - chara[1].y - chara[1].height / 2, 2)) <= range) {
            return 1;
        }
        return 0;
    }
}
