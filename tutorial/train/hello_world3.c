#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> // primitives

// helper func to make our initialization phase a bit less unruly with a slick check that each step executes successfully
// skip return and printf at each initialization every time
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* mysha = al_load_bitmap("pic5.png");
    must_init(mysha, "mysha");

    // Lurid colors
    must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");

            al_draw_bitmap(mysha, 100, 100, 0);
            // add more lines and shapes
            al_draw_filled_triangle(35, 350, 85, 375, 35, 400, al_map_rgb_f(0, 1, 0)); // al_map_rgb_f() takes a nums range 0~1
            al_draw_filled_rectangle(240, 260, 340, 340, al_map_rgba_f(0, 0, 0.5, 0.5)); // al_map_rgba_f takes extra argument:alpha(opacity)
            al_draw_circle(450, 370, 30, al_map_rgb_f(1, 0, 1), 2);
            al_draw_line(110, 200, 110, 210, al_map_rgb_f(1, 0, 0), 1); // (x1,y1,x2,y2)
            al_draw_line(500, 220, 200, 220, al_map_rgb_f(1, 1, 0), 1);

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_bitmap(mysha);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
