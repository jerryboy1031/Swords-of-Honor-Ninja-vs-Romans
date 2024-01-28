// sprite animation2 --advanced character(png) moves and change sides

#include <allegro5/allegro.h> // basic
#include<allegro5/allegro_native_dialog.h> // advanced
#include<allegro5/allegro_image.h>
#include<stdio.h>
#define SCREENWIDTH (int)800
#define SCREENHEIGHT (int)600

int main(int argc, char** argv) {
	enum Direction { DOWN, LEFT, RIGHT, UP };
	const float FPS = 60.0;

	// initialization
	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "cannot initialize allegro5!", NULL, NULL);
		return -1;
	}
	ALLEGRO_DISPLAY* disp = al_create_display(SCREENWIDTH, SCREENHEIGHT);

	// open a window
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);//ALLEGRO_RESIZABLE ,ALLEGRO_NOFRAME

	al_set_window_position(disp, 100, 100);
	al_set_window_title(disp, "player moves");
	if (!disp) {
		al_show_native_message_box(disp, "display title", "display setting", "display window isn't created successfully", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();

	// image in allegro5 are called bitmap
	ALLEGRO_BITMAP* player = al_load_bitmap("player.png");
	// KB state
	ALLEGRO_KEYBOARD_STATE keyState; // new!!!!!!!!!

	// timer
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	// any input event
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	// use events with timer
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	// disp
	al_register_event_source(event_queue, al_get_display_event_source(disp));
	// events on keyboard will line up in the event_queue
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// (some initial conditions)
	bool end = false, draw = true, active=false; //active !!
	int x = 10, y = 10;
	int movespeed = 5; //MOVE each type
	int dir = DOWN;
	// new------
	int sourceX=32, sourceY=0;

	// start timer
	al_start_timer(timer);

	// game loop
	while (!end)
	{
		// KB events
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);
		al_get_keyboard_state(&keyState); // get the keyState!!

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			end = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER) {
			// if any direction is pressed, active is set true
			active = true;
			// al_key_down: Return true if the key specified was held state"down"
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
				y += movespeed;
				dir = DOWN;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
				y -= movespeed;
				dir = UP;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
				x += movespeed;
				dir = RIGHT;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
				x -= movespeed;
				dir = LEFT;
			}
			// if no direction is pressed, active is set false
			else {
				active = false;
			}
			// updates source !!!

			// 1. sourceX
			if (active) {
				sourceX += al_get_bitmap_width(player) / 4; // the width of a play is fig_wid/3
			}
			else
			{
				sourceX = 100; //initial val (the wid and height of a character fig)
			}
			// if it touches the end, back to zero
			if (sourceX >= al_get_bitmap_width(player)) {
				sourceX = 0;
			}

			// 2. sourceY
			sourceY = dir * al_get_bitmap_height(player)/3; // the height of a play is fig_hei/4

			// draw commands aren't light weight, will be harder for hardware
			draw = true;
		}
		if (draw) {
			// animation of different sides
			al_draw_bitmap_region(player, sourceX, sourceY, 130,120, x, y, NULL); //source: before side width,height
			//draw = false;
			//al_draw_bitmap(player, 10, 10, ALLEGRO_FLIP_HORIZONTAL);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

	}
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(player); //destory!
	return 0;
}
