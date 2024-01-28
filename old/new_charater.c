#include "charater.h"

// the state of character
enum { STOP = 0, MOVE, ATK, JUMP, DEAD, HURT }; // add JUMP, DEAD

ALLEGRO_SAMPLE* sample_atk = NULL, * sample_jump = NULL, * sample_die = NULL; // initialize three sounds ptr
// create character object: chara

//  change files------------------------------------
void character_init(Character* chara,int type) {
    // load character images
    for (int i = 1; i <= 2; i++) {
        char temp[70];
        sprintf(temp, "->/image/move%d%d.png",type, i);  // change file
        chara->img_move[i - 1] = al_load_bitmap(temp);
    }
    // attack fig
    for (int i = 1; i <= 3; i++) {
        char temp[50];
        sprintf(temp, "->/image/attack%d%d.png",type, i);
        chara->img_atk[i - 1] = al_load_bitmap(temp);
    }
    // jump fig
    chara->img_jump[0] = al_load_bitmap("->/image/jump%d1.png",type);

    //dead fig
    for (int i = 1; i <= 2; i++) {
        char temp[50];
        sprintf(temp, "->/image/die%d%d.png", type, i);
        chara->img_die[i - 1] = al_load_bitmap(temp);
    }

    // load effective sound
    sample_atk = al_load_sample("->/sound/atk_sound%d.wav", type); // attack sound
    sample_jump = al_load_sample("->/sound/jump_sound%d.wav", type); // attack sound
    sample_die = al_load_sample("->/sound/die_sound%d.wav", type); // attack sound
    // *2 speed (ATK)
    float playbackSpeed = 4.0; // Desired playback speed (4x faster)
    al_set_sample_instance_speed(sample_atk, playbackSpeed);

    chara->atk_Sound = al_create_sample_instance(sample_atk);

    chara->jump_Sound = al_create_sample_instance(sample_jump);
    chara->die_Sound = al_create_sample_instance(sample_die);

    al_set_sample_instance_playmode(chara->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara->jump_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(chara->die_Sound, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(chara->atk_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara->jump_Sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(chara->die_Sound, al_get_default_mixer());



    // initial the geometric information of character
    chara->width = al_get_bitmap_width(chara->img_move[0]);
    chara->height = al_get_bitmap_height(chara->img_move[0]);
    // initial position
    chara->x = 10;//WIDTH/2;
    chara->y = HEIGHT; //HEIGHT/2;
    chara->dir = true;
    chara->jump = false;
    // initial speed
    chara->speed = 3;
    // initial the animation component
    chara->state = STOP;
    chara->anime = 0;
    chara->anime_time = 20; // the shorter time, the faster the image updates
}

//  change moving------------------------------------
void charater_process(ALLEGRO_EVENT event,Character *chara) {
    // process the animation
    if (event.type == ALLEGRO_EVENT_TIMER) {
        if (event.timer->source == fps) {
            chara->anime++;
            chara->anime %= chara->anime_time;

        }


        // process the keyboard event
        // key pressed
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        key_state[event.keyboard->keycode] = true;
        chara->anime = 0;
        // key realeased
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        key_state[event.keyboard->keycode] = false;
    }
}


// change speed, keyboard-------------------------
void charater_update(Character* chara,int type) {
    // use the idea of finite state machine to deal with different state
    if (type == 1) {
        // sprint
        if (key_state[ALLEGRO_KEY_S]) {
            chara->speed *= 3;
        }

        // change to jump!!
        if (key_state[ALLEGRO_KEY_W] && chara->jump) {
            chara->vely = -40; // negative is jump upwaed
            chara->state = JUMP;
            chara->jump = false;

        }

        if (key_state[ALLEGRO_KEY_A]) {
            chara->dir = false;
            chara->x -= chara->speed;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D]) {
            chara->dir = true;
            chara->x += chara->speed;
            chara->state = MOVE;
        }

        else if (key_state[ALLEGRO_KEY_SPACE]) {
            chara->state = ATK;
        }
        else if (chara->anime == chara->anime_time - 1) {
            chara->anime = 0; //歸零
            chara->state = STOP;
        }
        else if (chara->anime == 0) {
            chara->state = STOP;
        }
    }
    else {
        // sprint
        if (key_state[ALLEGRO_KEY_DOWN]) {
            chara->speed *= 3;
        }

        // change to jump!!
        if (key_state[ALLEGRO_KEY_UP] && chara->jump) {
            chara->vely = -40; // negative is jump upwaed
            chara->state = JUMP;
            chara->jump = false;

        }

        if (key_state[ALLEGRO_KEY_LEFT]) {
            chara->dir = false;
            chara->x -= chara->speed;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_RIGHT]) {
            chara->x += chara->speed;
            chara->state = MOVE;
        }

        else if (key_state[ALLEGRO_KEY_ENTER]) {
            chara->state = ATK;
        }
        else if (chara->anime == chara->anime_time - 1) {
            chara->anime = 0; //�k�s
            chara->state = STOP;
        }
        else if (chara->anime == 0) {
            chara->state = STOP;
        }
    }



    // jump statement
    if (!chara->jump) chara->vely += 4; // gravity
    else chara->vely = 0;
    chara->y += chara->vely;
    // the (head posi(y) + chara height(32)) is under ground(screen size), return false when falling to ground
    chara->jump = (chara->y + chara->height >= HEIGHT);

    // remain jump pose in the air (30 up)
    if (chara->y + chara->height < HEIGHT - 30) chara->state = JUMP;

    // change speed back to initial value
    chara->speed = 3;

    // boundary setting5
    // vertical limit
    if (chara->jump) chara->y = HEIGHT - chara->height;
    // horizontal limit
    if (chara->x + chara->width > WIDTH) chara->x = WIDTH - chara->width;
    if (chara->x < 0) chara->x = 0;

}


// 大改---------------------------------
void character_draw(Character* chara) {
    // with the state, draw corresponding image

    // STOP: nothing
    if (chara->state == STOP) {
        // 需翻轉
        if (chara->dir)
            al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
        // 不需翻轉
        else
            al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
    }
    else if (chara->state == MOVE) {
        if (chara->dir) {
            if (chara->anime < chara->anime_time / 2) {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_draw_bitmap(chara->img_move[1], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
        }
        else {
            if (chara->anime < chara->anime_time / 2) {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
            }
            else {
                al_draw_bitmap(chara->img_move[1], chara->x, chara->y, 0);
            }
        }
    }


    //  ensure better synchronization between the attack sound and movement
    if (chara->state == ATK) {
        if (chara->dir) {
            if (chara->anime < chara->anime_time / 4) {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                static int attackFrame = 0;  // Variable to track the current attack frame
                static bool soundPlayed = false;  // Variable to track if the sound has been played
                static int attackDelay = 0;  // Variable to track the delay between each attack frame and sound sample
                al_draw_bitmap(chara->img_atk[attackFrame], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL); //+ 200*chara->dir-100
                if (!soundPlayed) {
                    // Play the sound only once
                    al_play_sample_instance(chara->atk_Sound);
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
                    chara->state = MOVE;  // Transition to MOVE state or desired state after the attack animation
                    soundPlayed = false;  // Reset the sound flag
                }
                else {
                    // Check if the sound is still playing or not
                    unsigned int pos = al_get_sample_instance_position(chara->atk_Sound);
                    unsigned int len = al_get_sample_instance_length(chara->atk_Sound);
                    if (pos >= len) {
                        // The sound has finished playing, stop the instance
                        al_stop_sample_instance(chara->atk_Sound);
                        soundPlayed = false;  // Reset the sound flag
                    }
                }
            }
        }
        else {
            if (chara->anime < chara->anime_time / 4) {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
            }
            else {
                static int attackFrame = 0;  // Variable to track the current attack frame
                static bool soundPlayed = false;  // Variable to track if the sound has been played
                static int attackDelay = 0;  // Variable to track the delay between each attack frame and sound sample
                al_draw_bitmap(chara->img_atk[attackFrame], chara->x, chara->y, 0);
                if (!soundPlayed) {
                    // Play the sound only once
                    al_play_sample_instance(chara->atk_Sound);
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
                    chara->state = MOVE;  // Transition to MOVE state or desired state after the attack animation
                    soundPlayed = false;  // Reset the sound flag
                }
                else {
                    // Check if the sound is still playing or not
                    unsigned int pos = al_get_sample_instance_position(chara->atk_Sound);
                    unsigned int len = al_get_sample_instance_length(chara->atk_Sound);
                    if (pos >= len) {
                        // The sound has finished playing, stop the instance
                        al_stop_sample_instance(chara->atk_Sound);
                        soundPlayed = false;  // Reset the sound flag
                    }
                }
            }
        }

    }



    // JUMP-- 1 fig
    else if (chara->state == JUMP) {
        al_play_sample_instance(chara->jump_Sound);
        if (chara->dir) al_draw_bitmap(chara->img_jump[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
        else al_draw_bitmap(chara->img_jump[0], chara->x, chara->y, 0);
    }

    //DEAD--2 figs
    else if (chara->state == DEAD) {
        al_play_sample_instance(chara->die_Sound);
        if (chara->dir) {
            if (chara->anime < chara->anime_time / 2) {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
            }
            else {
                al_play_sample_instance(chara->atk_Sound);
                for (int i = 0; i <= 1; i++) {
                    al_draw_bitmap(chara->img_die[i], chara->x, chara->y, ALLEGRO_FLIP_HORIZONTAL);
                    //al_rest(0->02);
                }
            }
        }
        else {
            if (chara->anime < chara->anime_time / 2) {
                al_draw_bitmap(chara->img_move[0], chara->x, chara->y, 0);
            }
            else {
                al_play_sample_instance(chara->atk_Sound);
                for (int i = 0; i <= 1; i++) {
                    al_draw_bitmap(chara->img_die[i], chara->x, chara->y, 0);
                }
            }
        }
    }
    // HURT -- sub_bitmap
    else if (chara->state == HURT) {
        ALLEGRO_BITMAP* subBitmap = al_create_sub_bitmap(chara->img_move[0], chara->x, chara->y, chara->width, chara->height);
        al_draw_tinted_bitmap(subBitmap, al_map_rgb(255, 0, 0), chara->x, chara->y, NULL);
    }
}

void character_destory(Character* chara) {


    for (int i = 0; i <= 1; i++) {
        al_destroy_bitmap(chara->img_move[i]);
    }

    for (int i = 0; i <= 2; i++) {
        al_destroy_bitmap(chara->img_atk[i]);
    }

    al_destroy_bitmap(chara->img_jump[0]);

    for (int i = 0; i <= 1; i++) {
        al_destroy_bitmap(chara->img_die[i]);
    }

    al_destroy_sample_instance(chara->atk_Sound);
    al_destroy_sample_instance(chara->jump_Sound);
    al_destroy_sample_instance(chara->die_Sound);

}

