#include "scene.h"

ALLEGRO_FONT *titletext= NULL;
ALLEGRO_FONT *start = NULL;
ALLEGRO_FONT *exittext = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *menupic = NULL;
ALLEGRO_BITMAP* gameOverImage = NULL;

typedef struct _BloodBar {
    int x,y;
    float width,height;
    float val,max;
}BloodBar;

BloodBar Blood1, Blood2;

// function of menu
void menu_init(){
    titletext = al_load_ttf_font("./font/AIR.ttf",80,0);
    start = al_load_ttf_font("./font/AIR.ttf",50,0);
    exittext = al_load_ttf_font("./font/AIR.ttf",50,0);
}

void menu_process(ALLEGRO_EVENT event){
  if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
        judge_next_window = true;
}

void menu_draw(){
    menupic = al_load_bitmap("./image/menupic.jpg");
    al_draw_bitmap(menupic, 0, 0, 0);
    al_draw_text(titletext, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/5 , ALLEGRO_ALIGN_CENTRE, "TITLE");
    al_draw_text(start, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/5+200 , ALLEGRO_ALIGN_CENTRE, "Start game   ENTER");
    al_draw_rectangle(WIDTH/2+70, 370, WIDTH/2+230, 440, al_map_rgb(255, 255, 255), 3);
    al_draw_text(exittext, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/5+320 , ALLEGRO_ALIGN_CENTRE, "Exit game   ESC");
    al_draw_rectangle(WIDTH/2+80, 485, WIDTH/2+185, 560, al_map_rgb(255, 255, 255), 3);
}

void menu_destroy(){
    al_destroy_bitmap(menupic);
    al_destroy_font(titletext);
    al_destroy_font(start);
    al_destroy_font(exittext);
}


void blood_init() {
    Blood1.width =350;
    Blood2.width = 350;
    Blood1.height = 40; Blood2.height = 40;
    Blood1.x = WIDTH / 38; Blood1.y = 40;
    Blood2.x = WIDTH / 1.35; Blood2.y = 40;
    Blood1.max = Blood1.width; Blood2.max = Blood2.width;
    Blood1.val = Blood1.max; Blood2.val = Blood2.max;

}

void game_scene_blood_draw() {
    Blood1.val = blood1; Blood2.val = blood2;
    // left bar
    al_draw_rectangle(Blood1.x, Blood1.y, Blood1.x+ Blood1.width, Blood1.y+ Blood1.height , al_map_rgb(255, 255, 255),5);
    al_draw_filled_rectangle(Blood1.x, Blood1.y+2, Blood1.x + Blood1.width * (blood1 / Blood1.max), Blood1.y+ Blood1.height-2, al_map_rgba(255, 0,0,100));

    // right bar
    al_draw_filled_rectangle(Blood2.x, Blood2.y, Blood2.x + Blood2.width * (blood2 / Blood2.max), Blood2.y+ Blood2.height, al_map_rgba(255, 0, 0,100));
    al_draw_rectangle(Blood2.x, Blood2.y, Blood2.x + Blood2.width, Blood2.y+ Blood2.height, al_map_rgb(255, 255, 255), 5);
}


// function of game_scene
void game_scene_init() {
    blood_init();
    character_init();
    background = al_load_bitmap("./image/background.jpg");
}

void game_scene_draw() {
    al_draw_bitmap(background, 0, 0, 0);
    game_scene_blood_draw();
    // draw character 
    character_draw();
}


void game_scene_gameover() {
    // Draw the game over screen with the desired figure
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear the screen to black
    gameOverImage = al_load_bitmap("./image/gameover.png");
    al_draw_bitmap(gameOverImage, 0, 0, 0); // Draw the game over figure
    
}

void game_scene_destroy(){
    al_destroy_bitmap(background);
    character_destory();
    al_destroy_bitmap(gameOverImage);
}

