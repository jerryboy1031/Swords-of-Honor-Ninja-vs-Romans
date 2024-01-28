#include "charater.h"

// the state of character
enum { STOP = 0, MOVE, ATK, JUMP, DEAD ,HURT};

typedef struct _bloodbar{
    float lx,ly;// left-up point of bloodbar
    float rx,ry; // right-down point of bloodbar
    float maxValue;  // Maximum value of the blood bar
    float value;  // Current value of the blood bar
} BloodBar;

typedef struct _character{
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

    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE_INSTANCE* jump_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;

//cretae bloodbar
BloodBar blood[2];
//create character object: chara
Character chara[2];
ALLEGRO_SAMPLE* sample_atk = NULL, * sample_jump = NULL, * sample_die = NULL; // initialize three sounds ptr
ALLEGRO_SAMPLE* sample_atk2 = NULL, * sample_jump2 = NULL, * sample_die2 = NULL;

void character_init(){
    // load P1 images
    for(int i = 1 ; i <= 2 ; i++){
        char temp1[70];
        sprintf( temp1, "./image/move%d.png", i );
        chara[0].img_move[i-1] = al_load_bitmap(temp1);
    }
    // attack fig
    for(int i = 1 ; i <= 3 ; i++){
        char temp1[50];
        sprintf( temp1, "./image/attack%d.png", i );
        chara[0].img_atk[i-1] = al_load_bitmap(temp1);
    }
    // jump fig
    chara[0].img_jump[0] = al_load_bitmap("./image/jump1.png");

    // load effective sound
    sample_atk = al_load_sample("./sound/atk_sound.wav");
    sample_jump = al_load_sample("./sound/jump_Sound.wav");
    sample_die = al_load_sample("./sound/die_sound.wav");
    // *4 speed (ATK sound)
    float playbackSpeed = 4.0;
    al_set_sample_instance_speed(sample_atk, playbackSpeed);
    chara[0].atk_Sound = al_create_sample_instance(sample_atk);
    chara[0].jump_Sound = al_create_sample_instance(sample_jump);

    al_set_sample_instance_playmode(chara[0].atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara[0].jump_Sound, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(chara[0].atk_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara[0].jump_Sound, al_get_default_mixer());

    // initial the geometric information of P1
    chara[0].width = al_get_bitmap_width(chara[0].img_move[0]);
    chara[0].height = al_get_bitmap_height(chara[0].img_move[0]);
    // initial position
    chara[0].x = 10;
    chara[0].y = HEIGHT;
    chara[0].dir = true;
    chara[0].jump = false;
    // initial speed
    chara[0].speed = 3;
    // initial the animation component
    chara[0].state = STOP;
    chara[0].anime = 0;
    chara[0].anime_time = 20;
    // initial P1 bloodbar
    blood[0].lx = WIDTH/36;
    blood[0].ly = 40.5;
    blood[0].rx = WIDTH/3.93;
    blood[0].ry = 77;
    blood[0].maxValue = 350;
    blood[0].value = 350;

    // load P2 images
    for(int i = 1 ; i <= 2 ; i++){
        char temp2[70];
        sprintf( temp2, "./image/move2%d.png", i );
        chara[1].img_move[i-1] = al_load_bitmap(temp2);
    }
    // attack fig
    for(int i = 1 ; i <= 2 ; i++){
        char temp2[50];
        sprintf( temp2, "./image/attack2%d.png", i );
        chara[1].img_atk[i-1] = al_load_bitmap(temp2);
    }
    // jump fig
    chara[1].img_jump[0] = al_load_bitmap("./image/jump21.png");

    // load effective sound
    sample_atk2 = al_load_sample("./sound/atk_sound.wav");
    sample_jump2 = al_load_sample("./sound/jump_Sound2.wav");
    sample_die2 = al_load_sample("./sound/die_sound.wav");
    // *4 speed (ATK sound)
    float playbackSpeed2 = 4.0;
    al_set_sample_instance_speed(sample_atk2, playbackSpeed2);
    chara[1].atk_Sound = al_create_sample_instance(sample_atk2);
    chara[1].jump_Sound = al_create_sample_instance(sample_jump2);

    al_set_sample_instance_playmode(chara[1].atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara[1].jump_Sound, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(chara[1].atk_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara[1].jump_Sound, al_get_default_mixer());

    // initial the geometric information of character2
    chara[1].width = al_get_bitmap_width(chara[1].img_move[0]);
    chara[1].height = al_get_bitmap_height(chara[1].img_move[0]);
    // initial position
    chara[1].x = WIDTH - 20;
    chara[1].y = HEIGHT;
    chara[1].dir = false;
    chara[1].jump = false;
    // initial speed
    chara[1].speed = 3;
    // initial the animation component
    chara[1].state = STOP;
    chara[1].anime = 0;
    chara[1].anime_time = 20;
    // initial P2 bloodbar
    blood[1].lx = WIDTH/1.345;
    blood[1].ly = 40.5;
    blood[1].rx = WIDTH/1.037;
    blood[1].ry = 77;
    blood[1].maxValue = 350;
    blood[1].value = 350;
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

void charater_update(){
    // P1
    if (key_state[ALLEGRO_KEY_S]) {
        chara[0].speed *= 3;
    }
    if( key_state[ALLEGRO_KEY_W] && chara[0].jump){
        chara[0].vely = -40; // negative is jump upward
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
        chara[0].anime = 0;
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

    // boundary setting
    // vertical limit
    if (chara[0].jump) chara[0].y = HEIGHT - chara[0].height;
    // horizontal limit
    if (chara[0].x + chara[0].width > WIDTH) chara[0].x = WIDTH - chara[0].width;
    if (chara[0].x < 0) chara[0].x = 0;

    //dead state
    if (blood[0].value <= 0){
        dead1 = 1;
        chara[0].state = DEAD;
    }

    // P2
    if (key_state2[ALLEGRO_KEY_DOWN]) {
        chara[1].speed *= 3;
    }
    if (key_state2[ALLEGRO_KEY_UP] && chara[1].jump) {
        chara[1].vely = -40; // negative is jump upward
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
        chara[1].anime = 0;
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
    if (blood[1].value <= 0){
        dead2 = 1;
        chara[1].state = DEAD;
    }
}

void character_draw() { // with the state, draw corresponding image
    //P1--------------------------------------------------
    // STOP
    if (chara[0].state == STOP) {
        if (chara[0].dir)
            al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara[0].img_move[0], chara[0].x, chara[0].y, 0);
    }
    //MOVE
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
    //ATK (ensure better synchronization between the attack sound and movement)
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
                    chara[0].state = MOVE;  // After ATK transition to MOVE state
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
                    chara[0].state = MOVE;  // After ATK transition to MOVE state
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
        if (character_collision(0)) chara[1].state = HURT;
    }
    //JUMP--1 fig
    else if (chara[0].state == JUMP) {
        al_play_sample_instance(chara[0].jump_Sound);
        if (chara[0].dir) al_draw_bitmap(chara[0].img_jump[0], chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_bitmap(chara[0].img_jump[0], chara[0].x, chara[0].y, 0);
    }
    //HURT
    if (chara[0].state == HURT) {
        if(chara[0].dir)
            al_draw_tinted_bitmap(chara[0].img_move[0], al_map_rgb(255, 0, 0), chara[0].x, chara[0].y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_tinted_bitmap(chara[0].img_move[0], al_map_rgb(255, 0, 0), chara[0].x, chara[0].y, 0);
        blood[0].value-=1;
    }
    //update bloodbar
    float loss1 = blood[0].value/blood[0].maxValue*(blood[0].rx-blood[0].lx);
    al_draw_filled_rectangle(blood[0].lx, blood[0].ly,blood[0].lx + loss1, blood[0].ry, al_map_rgb(255, 0, 0));

    //P2--------------------------------------------------
    //STOP
    if( chara[1].state == STOP ){
        if( chara[1].dir )
            al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, 0);
    }
    //MOVE
    else if( chara[1].state == MOVE ){
        if( chara[1].dir ){
            if( chara[1].anime < chara[1].anime_time/2 ){
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else{
                al_draw_bitmap(chara[1].img_move[1], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else{
            if( chara[1].anime < chara[1].anime_time/2 ){
                al_draw_bitmap(chara[1].img_move[0], chara[1].x, chara[1].y, 0);
            }
            else{
                al_draw_bitmap(chara[1].img_move[1], chara[1].x, chara[1].y, 0);
            }
        }
    }
    //ATK
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
                if (attackDelay >= 10) {  // Change this value to adjust the speed of the attack
                    // Move to the next attack frame and reset the delay counter
                    attackFrame++;
                    attackDelay = 0;
                }

                if (attackFrame >= 2) {
                    // Reset the attack animation
                    attackFrame = 0;
                    chara[1].state = MOVE;  // After ATK transition to MOVE state
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
                    chara[1].state = MOVE;  // After ATK transition to MOVE state
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
        if (character_collision(1)) chara[0].state = HURT;
    }
    // JUMP--1 fig
    else if (chara[1].state == JUMP) {
        al_play_sample_instance(chara[1].jump_Sound);
        if (chara[1].dir) al_draw_bitmap(chara[1].img_jump[0], chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_bitmap(chara[1].img_jump[0], chara[1].x, chara[1].y, 0);
    }
    // HURT
    else if (chara[1].state == HURT) {
        if(chara[1].dir)
            al_draw_tinted_bitmap(chara[1].img_move[0], al_map_rgb(255, 0, 0), chara[1].x, chara[1].y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_tinted_bitmap(chara[1].img_move[0], al_map_rgb(255, 0, 0), chara[1].x, chara[1].y, NULL);
        blood[1].value-=1;
    }
    //update bloodbar
    float loss2 = blood[1].value/blood[1].maxValue*(blood[1].rx-blood[1].lx); //loss percent of blood
    al_draw_filled_rectangle(blood[1].lx, blood[1].ly,blood[1].lx + loss2, blood[1].ry, al_map_rgb(255, 0, 0));
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
    al_destroy_sample_instance(chara[0].atk_Sound);
    al_destroy_sample_instance(chara[0].jump_Sound);

    //P2
    for(int i=0;i<=1;i++){
        al_destroy_bitmap(chara[1].img_move[i]);
    }

    for(int i=0;i<=2;i++){
        al_destroy_bitmap(chara[1].img_atk[i]);
    }

    al_destroy_bitmap(chara[1].img_jump[0]);
    al_destroy_sample_instance(chara[1].atk_Sound);
    al_destroy_sample_instance(chara[1].jump_Sound);
}

// to judge attack is valid or not :
int character_collision(int attacker) {
    int range = 200;
    if (chara[attacker].x >= chara[attacker ^ 1].x && chara[attacker].dir || (chara[attacker].x + chara[attacker].width <= chara[attacker ^ 1].x+ chara[attacker ^ 1].width )&& !chara[attacker].dir) {
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
