#include "scene.h"

ALLEGRO_FONT *titletext = NULL;
ALLEGRO_FONT *start = NULL;
ALLEGRO_FONT *exittext = NULL;
ALLEGRO_FONT *playerone = NULL;
ALLEGRO_FONT *playertwo = NULL;
ALLEGRO_FONT *gameovertext = NULL;
ALLEGRO_FONT *p1text = NULL;
ALLEGRO_FONT *p2text = NULL;
ALLEGRO_BITMAP *menupic = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *gameOverImage = NULL;

void menu_init(){
    titletext = al_load_ttf_font("./font/Caslon.ttf",80,0);
    start = al_load_ttf_font("./font/AIR.ttf",50,0);
    exittext = al_load_ttf_font("./font/AIR.ttf",50,0);
    gameovertext = al_load_ttf_font("./font/AIR.ttf",180,0);
    p1text = al_load_ttf_font("./font/Caslon.ttf",80,0);
    p2text = al_load_ttf_font("./font/Caslon.ttf",80,0);
}

void menu_process(ALLEGRO_EVENT event){
  if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
        judge_next_window = true;
}

void menu_draw(){
    menupic = al_load_bitmap("./image/menupic.jpg");
    al_draw_bitmap(menupic, 0, 0, 0);
    al_draw_text(titletext, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/5 , ALLEGRO_ALIGN_CENTRE, "Swords of Honor:Ninja vs. Romans");
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

// function of game_scene
void game_scene_init(){
    character_init();
    background = al_load_bitmap("./image/background.jpg");
    playerone = al_load_ttf_font("./font/Caslon.ttf",40,0);
    playertwo = al_load_ttf_font("./font/Caslon.ttf",40,0);
}

void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_rectangle(WIDTH/38, 40, WIDTH/3.9, 80, al_map_rgb(255, 255, 255), 5);
    al_draw_rectangle(WIDTH/1.35, 40, WIDTH/1.035, 80, al_map_rgb(255, 255, 255), 5);
    al_draw_text(playerone, al_map_rgb(255,255,255), WIDTH/13.5, 82 , ALLEGRO_ALIGN_CENTRE, "Player1");
    al_draw_text(playertwo, al_map_rgb(255,255,255), WIDTH/1.089, 82 , ALLEGRO_ALIGN_CENTRE, "Player2");
    character_draw();
    if( dead1 == 1 || dead2 == 1 ) {//GAMEOVER
        al_rest(1.5);
        al_clear_to_color(al_map_rgb(0, 0, 0)); // Clear the screen to black
        gameOverImage = al_load_bitmap("./image/gameover.jpg");
        al_draw_bitmap(gameOverImage, 0, 0, 0); // Draw the game over figure
        al_draw_text(gameovertext, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-100 , ALLEGRO_ALIGN_CENTRE, " GAME OVER ");
        if( dead2 == 1 ){
            al_draw_text(p1text, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+120 , ALLEGRO_ALIGN_CENTRE, " Player1 WIN ");
            al_draw_rectangle(WIDTH/3.5+45, HEIGHT/2+120, WIDTH-445, HEIGHT/2+225, al_map_rgb(255, 255, 255), 5);
        }
        else{
            al_draw_text(p2text, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+120 , ALLEGRO_ALIGN_CENTRE, " Player2 WIN ");
            al_draw_rectangle(WIDTH/3.5+45, HEIGHT/2+120, WIDTH-445, HEIGHT/2+225, al_map_rgb(255, 255, 255), 5);
        }
    }
}

void game_scene_destroy(){
    character_destory();
    al_destroy_bitmap(background);
    al_destroy_font(gameovertext);
    al_destroy_font(p1text);
    al_destroy_font(p2text);
    al_destroy_bitmap(gameOverImage);
}

