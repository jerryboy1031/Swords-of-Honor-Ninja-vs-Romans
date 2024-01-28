#include "GameWindow.h"

bool draw = false,isdead=false;
int window = 1;
const char *title="Final Project Game";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE *startSound=NULL;
ALLEGRO_SAMPLE_INSTANCE *sound;
ALLEGRO_SAMPLE_INSTANCE *menusound;

int Game_establish() {
    int msg = 0;
    game_init();
    game_begin();
    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }
    game_destroy();
    return 0;
}

void game_init() {
    printf( "Game Initializing...\n\n" );
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps  = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.jpg");
    al_set_display_icon(display, icon);
}

void game_begin() {
    // Load sound for menu
    startSound = al_load_sample("./sound/menumusic.wav");
    menusound = al_create_sample_instance(startSound);
    // Loop the song
    al_set_sample_instance_playmode(menusound, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(menusound, al_get_default_mixer());
    al_set_sample_instance_gain(menusound, 0.4) ;
    al_play_sample_instance(menusound);
    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();

}

void game_update(){
    if (isdead) window = 3; // dead condition
    else if( judge_next_window ){
        if( window == 1 ){
            // not back menu anymore, therefore destroy it
            al_stop_sample_instance(menusound);
            menu_destroy();
            // initialize next scene
            // Load sound for game
            song = al_load_sample("./sound/music.wav");
            sound = al_create_sample_instance(song);
            // Loop the song until the display closes
            al_set_sample_instance_playmode(sound, ALLEGRO_PLAYMODE_LOOP);
            al_restore_default_mixer();
            al_attach_sample_instance_to_mixer(sound, al_get_default_mixer());
            // set the volume of instance
            al_set_sample_instance_gain(sound, 1) ;
            al_play_sample_instance(sound);

            game_scene_init();

            judge_next_window = false;
            window = 2;
        }
    }
    if( window == 2 ){
        charater_update();
    }

}

int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if( window == 1 ){
        menu_process(event);
    }
    else if( window == 2 ){
        charater_process(event);
    }



    // Shutdown our program
    if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)//ESC
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        return GAME_TERMINATE;
    else if(dead == 1)
        return GAME_TERMINATE;
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    if(draw) game_update();
    return 0;
}

void game_draw(){
    if( window == 1 ){
        menu_draw();
    }
    else if( window == 2 ){
        game_scene_draw();
    }

    // add-----------------------
    else if (window == 3) {
        game_scene_gameover();
    }
    // add--------------------end

    al_flip_display();
}

int game_run() {
    int error = 0;
    if( draw ){
        game_draw();
        draw = false;
    }
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    game_scene_destroy();
}
