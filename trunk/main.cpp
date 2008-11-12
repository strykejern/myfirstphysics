#include <allegro.h>
#include <math.h>
#include <vector>
#include "vector.cpp"
#include "box.cpp"
#include "collision.cpp"

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
	
	std::vector<box> boks;
	
	int length = 2;
	
	for (int x = 0; x < length; ++x) {
		int seedx = (rand()%400);
		int seedy = (rand()%400);
		int seed = rand()%50;
		point points[] = {
			point(Vector(seedx, seedy), width, height),
			point(Vector(seedx, seedy+30+seed), width, height),
			point(Vector(seedx+30+seed, seedy+30+seed), width, height),
			point(Vector(seedx+30+seed, seedy), width, height)
		};
		boks.push_back(*new box (points));
	}
	boks[1].points[0].speed.y = -10;
	boks[1].points[2].speed.y = 10;
	
	int mytimer = 0;
	
	while (!key[KEY_ESC]) {
        while (speed_counter > 0) {
        	for (int x = 0; x < length; ++x) {
				//boks[x].points[0].speed = boks[x].points[0].speed * 1.1f;
				if (boks[x].points[0].speed.length() < 10) boks[x].points[0].speed.set_length(10);
        		boks[x].update_phys(false);
			}
			
			for (int x = 0; x < length; ++x) {
				for (int y = 0; y < length; ++y) {
					if (x != y)
						for (int i = 0; i < 3; ++i) {
							collision_box(&boks[x], &boks[y]);
							boks[x].shape();
							boks[y].shape();
						}
				}
			}
			
			if (mytimer >= 60 && length < 5) {
				mytimer = 0;
				length++;
				int seedx = 0;
				int seedy = 0;
				int seed = rand()%50;
				point points[] = {
					point(Vector(seedx, seedy), width, height),
					point(Vector(seedx, seedy+30+seed), width, height),
					point(Vector(seedx+30+seed, seedy+30+seed), width, height),
					point(Vector(seedx+30+seed, seedy), width, height)
				};
				boks.push_back(*new box (points));
				boks[length-1].points[0].speed.x = seed;
			}
			else if(mytimer >= 60 && length == 4) {
				mytimer = 0;
			}
			
			//for (int x = 0; x < length; ++x)
			//	textprintf(buffer, font, 10, 10 + (x*20), makecol(255,255,255), "%f", boks[x].points[0].pos.x);
			
			speed_counter--;
			mytimer++;
		}
		
		for (int x = 0; x < length; ++x) {
			boks[x].draw(buffer);
		}
		//textprintf_ex(buffer, font, 10, 10, makecol(255,255,255), -1, "%f", boksen.points[0].pos.x);
		
		blit(buffer, screen, 0, 0, 0, 0, width, height);
		clear_bitmap(buffer);
	}
	destroy_bitmap(buffer);
	return 0;
}
END_OF_MAIN();
