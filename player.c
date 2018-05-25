#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include "player.h"
#include "drawing.h"

struct game_area* a;

void getstartingpos(int* x, int* y, struct game_area *a) {
		*x = rand_lim(a->max_x-1, a->min_x+1);
		*y = rand_lim(a->max_y-1, a->min_y+1);
}

int rand_lim(int max, int min) {
		srand(time(NULL));

		return rand() % (max + 1 - min) + min;
}

Snake* create_snake() {
		int* x = malloc(sizeof(int));
		int* y = malloc(sizeof(int));

		a = malloc(sizeof(struct game_area));
		setplayarea(a);
		
		getstartingpos(x, y, a);

		Snake* snek = malloc(sizeof(Snake));

		snek->x = *x;
		snek->y = *y;
		snek->direction = 'r';
		snek->next = NULL;

		draw_snake(snek);

		return snek;
}

Food* create_food() {
		int* x = malloc(sizeof(int));
		int* y = malloc(sizeof(int));

		getstartingpos(x, y, a);

		Food* fud = malloc(sizeof(Food));

		fud->x = *x;
		fud->y = *y;


		return fud;
}

void draw_food(Food* fud) {
		mvaddch(fud->y, fud->x, '*');
}

void draw_snake(Snake* snek) {
		Snake* snek_ptr = snek;
		do {
				mvaddch(snek_ptr->y, snek_ptr->x, 'o');
				snek_ptr = snek_ptr->next;
		} while (snek_ptr != NULL);
}

void get_snake_direction(Snake* snek) {
		int c = getch();
		switch(c) {
				case KEY_UP:
						if(snek->direction != 'd') {
								snek->direction = 'u';
						}
						break;
				case KEY_DOWN:
						if(snek->direction != 'u') {
								snek->direction = 'd';
						}
						break;
				case KEY_LEFT:
						if(snek->direction != 'r') {
								snek->direction = 'l';
						}
						break;
				case KEY_RIGHT:
						if(snek->direction != 'l') {
								snek->direction = 'r';
						}
						break;
		}
}

int check_collisions(Snake* snek, Food* fud) {
		Snake* snek_ptr = snek;

		if(a == NULL) {
				perror("Game area not defined\n");
				exit(1);
		}

		if (snek->x == fud->x && snek->y == fud->y) {
				return EAT;
		}

		if (snek->x >= a->max_x || snek->x <= a->min_x || 
						snek->y >= a->max_y || snek->y <= a->min_y) {
				return DIE; 
		}

		while (snek_ptr->next != NULL)	{
				snek_ptr = snek_ptr->next;
				if(snek->x == snek_ptr->x && snek->y == snek_ptr->y) {
						return DIE;
				}
		} 


		return 0;
}

void move_snake(Snake* snek) {
		Snake* snake_head = snek;
		Snake* snek_ptr = snek;
		char dir = snek->direction;

		int temp_x, temp_y;
		int swap_x, swap_y;
		temp_x = snek_ptr->x;
		temp_y = snek_ptr->y;

		// move the whole snake
		// the issue is here!
		while(snek_ptr->next != NULL) {
				snek_ptr = snek_ptr->next;
				swap_x = snek_ptr->x;
				swap_y = snek_ptr->y;
				snek_ptr->x = temp_x;
				snek_ptr->y = temp_y;
				temp_x = swap_x;
				temp_y = swap_y;
		}

		// move the snakes head in the right direction
		switch(dir) {
				case 'u': // up
						snake_head->y--;
						break;
				case 'd': // down
						snake_head->y++;
						break;
				case 'l': // left
						snake_head->x--;
						break;
				case 'r': // right
						snake_head->x++;
						break;
		}

		draw_snake(snake_head);
}

void eat(Snake *snek) {
		Snake* snek_ptr = snek;
		Snake* new_seg = malloc(sizeof(Snake));
		char dir = snek->direction;
		new_seg->next = NULL;

		while(snek_ptr->next != NULL) {
				snek_ptr = snek_ptr->next;
		}

		new_seg->x = snek_ptr->x;
		new_seg->y = snek_ptr->y;

		switch(dir) {
				case 'u': // up
						new_seg->y++;
						break;
				case 'd': // down
						new_seg->y--;
						break;
				case 'l': // left
						new_seg->x++;
						break;
				case 'r': // right
						new_seg->x--;
						break;
		}

		snek_ptr->next = new_seg;
}
