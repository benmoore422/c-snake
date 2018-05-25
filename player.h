#ifndef player_h
#define player_h

#include "drawing.h"

#define EAT 1
#define DIE 2

typedef struct Snake_node {
		int x;
		int y;
		char direction;
		struct Snake_node *next;
} Snake;

typedef struct Food_struct {
		int x;
		int y;
} Food;

Snake* create_snake();
Food* create_food();
void getstartingpos(int* x, int* y, struct game_area *a);
int rand_lim(int max, int min);
void draw_snake(Snake* snek);
void draw_food(Food* fud);
void get_snake_direction(Snake* snek);
int check_collisions(Snake *snek, Food* fud);
void move_snake(Snake* snek);
void eat(Snake* snek);

#endif
