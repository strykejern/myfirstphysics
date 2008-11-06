#include <allegro.h>
#include "box.cpp"
#include <iostream>

volatile long speed_counter = 0;

void increment_speed_counter() {
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);

int main() {
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();
	
	LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(30));
	
	int width , height;
	width = 640;
	height = 480;
	
	set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
    set_alpha_blender();
    
    BITMAP* buffer = create_bitmap(width, height);
	
	srand(time(NULL));
	
	point points [] = { 
		* new point (40, 40, width, height), 
		* new point (180, 40, width, height), 
		* new point (180, 180, width, height) 
	};
	
	triangleclass boks (points);
	
	point points2 [] = { 
		* new point (40, 40, width, height), 
		* new point (180, 40, width, height), 
		* new point (40, 180, width, height) 
	};
	
	triangleclass boks2 (points2);
	
	boks.points[0].speed_y = -50;
	*/
	
	point points[] = {
		* new point(  0,   0, width, height),
		* new point(  0, 140, width, height),
		* new point(140, 140, width, height),
		* new point(140,   0, width, height)
	};
	
	box boksen (points);
	
	while (!key[KEY_ESC]) {
        while (speed_counter > 0) {
        	
        	boks.update_phys();
        	
        	boks.points[1].pos_x = mouse_x;
        	boks.points[1].pos_y = mouse_y;
        	
			boks2.points[0] = boks.points[0];
			boks2.points[1] = boks.points[2];
			
        	boks2.update_phys();
        	
        	boks.points[1].pos_x = mouse_x;
        	boks.points[1].pos_y = mouse_y;
        	
			boks.points[0] = boks2.points[0];
			boks.points[2] = boks2.points[1];
        	*/
			
			boksen.update_phys();
			
			speed_counter--;
		}
		
		boksen.draw(buffer);
		
		//textprintf_ex(buffer, font, 10, 10, makecol(255,255,255), -1, "%f", boksen.triangles[0].points[0].pos_x);
		
		blit(buffer, screen, 0, 0, 0, 0, width, height);
		clear_bitmap(buffer);
	}
	destroy_bitmap(buffer);
	return 0;
}
END_OF_MAIN();
