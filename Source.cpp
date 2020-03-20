#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <Windows.h>
#include <time.h>
#include <cmath>
#include <vector>
#include <iostream>

#define M_PI 3.14159265358979323846

void abortGame(const char* message)
{
	MessageBox(0, message, "Error", MB_OK);
	exit(1);
}

void initAllegro(ALLEGRO_TIMER** timer, ALLEGRO_DISPLAY** display, ALLEGRO_EVENT_QUEUE** event_queue, bool * done, int width, int height)
{
	if (!al_init())
		abortGame("Failed to initialize allegro");


	if (!al_init_primitives_addon())
		abortGame("Failed to initialize primitives addon");

	//if (!al_init_native_dialog_addon())
	//	abortGame("Failed to initialize dialog addon"); 

	if (!al_init_font_addon())
		abortGame("Failed to initialize font addon");
/*
	if (!al_init_image_addon())
		abortGame("Failed to initialize image addon");*/

	/*(*player_image) = al_load_bitmap("assets/player_sprite_small.png");
	if (!(*player_image))
		abortGame("Failed to load player image");*/

	if (!al_install_keyboard())
		abortGame("Failed to install keyboard");

	if (!al_install_mouse())
		abortGame("Failed to install keyboard");


	(*timer) = al_create_timer(1.0 / 30);
	if (!(*timer))
		abortGame("Failed to create timer");

	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
	/*al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);*/
	al_set_new_window_title("stuff");
	(*display) = al_create_display(width, height);
	if (!(*display))
		abortGame("Failed to create display");



	(*event_queue) = al_create_event_queue();
	if (!(*event_queue))
		abortGame("Failed to create event queue");

	al_register_event_source((*event_queue), al_get_keyboard_event_source());
	al_register_event_source((*event_queue), al_get_mouse_event_source());
	al_register_event_source((*event_queue), al_get_timer_event_source((*timer)));
	al_register_event_source((*event_queue), al_get_display_event_source((*display)));

	*done = false;
}
void shutdownAllegro(ALLEGRO_DISPLAY**display, ALLEGRO_TIMER**timer, ALLEGRO_EVENT_QUEUE**event_queue)
{
	al_destroy_display(*display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(*timer);
	al_destroy_event_queue(*event_queue);
}



int main()
{
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP *buff1;
	ALLEGRO_BITMAP *buff2;
	ALLEGRO_BITMAP *buff3;
	bool done = true;
	bool redraw = true;
	bool activate_redraw = true;

	float window_width = 1920;
	float window_height = 1060;

	

	float mouse_x = 300;
	float mouse_y = 200;

	bool debug = false;

	initAllegro(&timer, &display, &event_queue, &done, window_width, window_height);

	//al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

	(buff1) = al_create_bitmap(window_width*1.1,window_height*1.1);
	if (!(buff1))
		abortGame("Failed to create buff1");

	(buff2) = al_create_bitmap(window_width*1.1, window_height*1.1);
	if (!(buff2))
		abortGame("Failed to create buff2");

	(buff3) = al_create_bitmap(window_width*1.1, window_height*1.1);
	if (!(buff3))
		abortGame("Failed to create buff3");

	float buffer_width = al_get_bitmap_width(buff1);
	float buffer_height = al_get_bitmap_height(buff1);
	float buff1_offset_x = 0;
	float buff1_offset_y = 0;
	float buff1_vel_x = 0;
	float buff1_vel_y = 0;

	

	srand(time(0));

	ALLEGRO_FONT* font = al_create_builtin_font();

	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0, 150, 255);
	ALLEGRO_COLOR green = al_map_rgb(40, 200, 90);
	ALLEGRO_COLOR white = al_map_rgb(250, 250, 245);
	ALLEGRO_COLOR grey = al_map_rgb(50, 50, 50);
	ALLEGRO_COLOR lighter_grey = al_map_rgb(100, 100, 100);
	ALLEGRO_COLOR lightest_grey = al_map_rgb(150, 150, 150);
	ALLEGRO_COLOR red = al_map_rgb(220, 70, 90);
	ALLEGRO_COLOR transparent = al_premul_rgba(0, 0, 0, 0);
	
	al_set_target_bitmap(buff1);
	al_clear_to_color(black);
	al_set_target_bitmap(buff2);
	al_clear_to_color(black);

	al_set_target_bitmap(al_get_backbuffer(display));

	ALLEGRO_VERTEX v[5] = {};

	v[0].x = 10;
	v[0].y = 10;
	v[0].z = 0;
	v[0].color = transparent;
	v[0].u = 128;
	v[0].v = 0;

	v[1].x = 246;
	v[1].y = 0;
	v[1].z = 0;
	v[1].color = transparent;
	v[1].u = 0;
	v[1].v = 256;

	v[2].x = 246;
	v[2].y = 246;
	v[2].z = 0;
	v[2].color = transparent;
	v[2].u = 0;
	v[2].v = 256;

	v[3].x = 10;
	v[3].y = 246;
	v[3].z = 0;
	v[3].color = transparent;
	v[3].u = 256;
	v[3].v = 256;

	v[4].x = 10;
	v[4].y = 246;
	v[4].z = 0;
	v[4].color = transparent;
	v[4].u = 256;
	v[4].v = 256;


	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		if (event.type == ALLEGRO_EVENT_TIMER)
		{

			//if (activate_redraw)
			//{
				//activate_redraw = false;
			if (!debug)
			{
				if (al_get_timer_count(timer) % 5 == 0)
				{

					float start_x = 0;
					float start_y = 0;
					float end_x = al_get_bitmap_width(buff1);
					float end_y = al_get_bitmap_height(buff1);

					al_set_target_bitmap(buff3);
					al_clear_to_color(black);
					al_draw_bitmap(buff1, buff1_offset_x, buff1_offset_y, 0);
					al_draw_bitmap(buff2, -buff1_offset_x, -buff1_offset_y, 0);

					buff1_offset_x = 0;
					buff1_offset_y = 0;
					buff1_vel_x = 0;
					buff1_vel_y = 0;



					if (rand() % 2)
					{
						start_y = 50 + rand() % (al_get_bitmap_height(buff1) - 50);
					}
					else
					{
						start_x = 50 + rand() % (al_get_bitmap_width(buff1) - 50);
					}

					if (start_x == 0)
					{
						if (rand() % 2)
						{
							end_x = 50 + rand() % (al_get_bitmap_width(buff1) - 50);
							if (rand() % 2)
							{
								end_y = 0;
							}
						}
						else
						{
							end_y = 50 + rand() % (al_get_bitmap_height(buff1) - 50);
						}
					}
					else
					{
						if (rand() % 2)
						{
							end_x = 50 + rand() % (al_get_bitmap_width(buff1) - 50);

						}
						else
						{
							end_y = 50 + rand() % (al_get_bitmap_height(buff1) - 50);
							if (rand() % 2)
							{
								end_x = 0;
							}
						}
					}


					float angle = atan2((end_y - start_y), (end_x - start_x));

					if (start_x == 0)
					{
						float additional_speed_mod = ((3 + rand() % 60) * 0.1);
						buff1_vel_x = additional_speed_mod * cosf(angle - (M_PI / 2.0f));
						buff1_vel_y = additional_speed_mod * sinf(angle - (M_PI / 2.0f));
					}
					else
					{
						float additional_speed_mod = ((3 + rand() % 60) * 0.1);
						buff1_vel_x = additional_speed_mod * cosf(angle + (M_PI / 2.0f));
						buff1_vel_y = additional_speed_mod * sinf(angle + (M_PI / 2.0f));
					}


					al_set_target_bitmap(buff1);
					al_draw_bitmap(buff3, 0, 0, 0);
					al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
					if (start_y == 0 && end_x != 0 && end_x != al_get_bitmap_width(buff1))
					{
						v[0].x = start_x;
						v[0].y = start_y;

						v[1].x = al_get_bitmap_width(buff1);
						v[1].y = start_y;

						v[2].x = al_get_bitmap_width(buff1);
						v[2].y = al_get_bitmap_height(buff1);

						v[3].x = end_x;
						v[3].y = end_y;
						al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_y == 0 && end_x == 0)
					{
						v[0].x = start_x;
						v[0].y = start_y;

						v[1].x = al_get_bitmap_width(buff1);
						v[1].y = start_y;

						v[2].x = al_get_bitmap_width(buff1);
						v[2].y = al_get_bitmap_height(buff1);

						v[3].x = end_x;
						v[3].y = al_get_bitmap_height(buff1);

						v[4].x = end_x;
						v[4].y = end_y;
						al_draw_prim(v, NULL, NULL, 0, 5, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_y == 0 && end_x == al_get_bitmap_width(buff1))
					{
						v[0].x = start_x;
						v[0].y = start_y;

						v[1].x = al_get_bitmap_width(buff1);
						v[1].y = start_y;

						v[2].x = end_x;
						v[2].y = end_y;
						al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_x == 0 && end_y != 0 && end_y != al_get_bitmap_height(buff1))
					{
						v[0].x = start_x;
						v[0].y = start_y;

						v[1].x = end_x;
						v[1].y = end_y;

						v[2].x = al_get_bitmap_width(buff1);
						v[2].y = al_get_bitmap_height(buff1);

						v[3].x = start_x;
						v[3].y = al_get_bitmap_height(buff1);
						al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_x == 0 && end_y == 0)
					{
						v[0].x = end_x;
						v[0].y = end_y;

						v[1].x = al_get_bitmap_width(buff1);
						v[1].y = end_y;

						v[2].x = al_get_bitmap_width(buff1);
						v[2].y = al_get_bitmap_height(buff1);

						v[3].x = start_x;
						v[3].y = al_get_bitmap_height(buff1);

						v[4].x = start_x;
						v[4].y = start_y;
						al_draw_prim(v, NULL, NULL, 0, 5, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_x == 0 && end_y == al_get_bitmap_height(buff1))
					{
						v[0].x = start_x;
						v[0].y = start_y;

						v[1].x = end_x;
						v[1].y = end_y;

						v[2].x = start_x;
						v[2].y = al_get_bitmap_height(buff1);
						al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

					al_draw_line(start_x, start_y, end_x, end_y, white, 2);

					//DRAWING ON BUFF2
					al_set_target_bitmap(buff2);
					al_draw_bitmap(buff3, 0, 0, 0);
					al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
					if (start_y == 0 && end_x != 0 && end_x != al_get_bitmap_width(buff2))
					{
						v[0].x = 0;
						v[0].y = 0;

						v[1].x = start_x;
						v[1].y = start_y;

						v[2].x = end_x;
						v[2].y = end_y;

						v[3].x = 0;
						v[3].y = al_get_bitmap_height(buff2);
						al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_y == 0 && end_x == 0)
					{
						v[0].x = 0;
						v[0].y = 0;

						v[1].x = start_x;
						v[1].y = start_y;

						v[2].x = end_x;
						v[2].y = end_y;
						al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);

					}
					else if (start_y == 0 && end_x == al_get_bitmap_width(buff2))
					{
						v[0].x = 0;
						v[0].y = 0;

						v[1].x = start_x;
						v[1].y = start_y;

						v[2].x = end_x;
						v[2].y = end_y;

						v[3].x = al_get_bitmap_width(buff2);
						v[3].y = al_get_bitmap_height(buff2);

						v[4].x = 0;
						v[4].y = al_get_bitmap_height(buff2);
						al_draw_prim(v, NULL, NULL, 0, 5, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_x == 0 && end_y != 0 && end_y != al_get_bitmap_height(buff2))
					{
						v[0].x = 0;
						v[0].y = 0;

						v[1].x = al_get_bitmap_width(buff2);
						v[1].y = 0;

						v[2].x = end_x;
						v[2].y = end_y;

						v[3].x = start_x;
						v[3].y = start_y;
						al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_x == 0 && end_y == 0)
					{
						v[0].x = 0;
						v[0].y = 0;

						v[1].x = end_x;
						v[1].y = end_y;

						v[2].x = start_x;
						v[2].y = start_y;
						al_draw_prim(v, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					else if (start_x == 0 && end_y == al_get_bitmap_height(buff2))
					{
						v[0].x = 0;
						v[0].y = 0;

						v[1].x = al_get_bitmap_width(buff2);
						v[1].y = 0;

						v[2].x = al_get_bitmap_width(buff2);
						v[2].y = al_get_bitmap_height(buff2);

						v[3].x = end_x;
						v[3].y = end_y;

						v[4].x = start_x;
						v[4].y = start_y;
						al_draw_prim(v, NULL, NULL, 0, 5, ALLEGRO_PRIM_TRIANGLE_FAN);
					}
					al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

					al_draw_line(start_x, start_y, end_x, end_y, white, 2);

					al_set_target_bitmap(al_get_backbuffer(display));
				}
				else
				{
					buff1_offset_x += buff1_vel_x;
					buff1_offset_y += buff1_vel_y;
				}
			}
			redraw = true;
			//}
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN)
		{
			activate_redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				done = true;

			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
			{
				debug = !debug;
				

				
				activate_redraw = true;
			}
		}


		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(black);

			//al_draw_bitmap(buff2, 0, 0, 0);
			//if(debug == true)
			al_draw_bitmap(buff1, ((window_width - buffer_width) / 2) + buff1_offset_x, ((window_height - buffer_height) / 2) +buff1_offset_y, 0);
			al_draw_bitmap(buff2, ((window_width - buffer_width) / 2) + (-buff1_offset_x), ((window_height - buffer_height) / 2) +(-buff1_offset_y), 0);

			
			//al_draw_textf(font, black, 10, 10, 0, "MOUSE_X: %d", tmp);

			al_flip_display();
		}
	}
	al_destroy_bitmap(buff1);
	al_destroy_bitmap(buff2);
	al_destroy_bitmap(buff3);
	shutdownAllegro(&display, &timer, &event_queue);
	return 0;
}