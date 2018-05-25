#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "drawing.h"
#include "player.h"
#include "kbhit.h"
#include "snake.h"

Snake* d;

int main() {
		score = 0;
		setupcurses();
		startscreen();
		refresh();
		getch();
		drawborder(score);
		Snake* s = create_snake();
		Food* f = create_food();
		kbinit();
		while(1) {
				if(kbhit()) {
						get_snake_direction(s);
				}
				drawborder(score);
				move_snake(s);
				draw_food(f);
				if(check_collisions(s, f) == EAT) { // eat
						score++;
						f = create_food();
						eat(s);
				} else if (check_collisions(s, f)== DIE) { // die
						deathscreen();
						getch();
						d = s;
						break;
				}
				refresh();
				usleep(100000);
		}
		kbfini();
		endwin();
		return 0;
}
