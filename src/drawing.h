#ifndef drawing_h
#define drawing_h

struct game_area{
		int max_x;
		int min_x;
		int max_y;
		int min_y;
};

void setupcurses();
void startscreen();
void deathscreen(); 
void drawborder();
void setplayarea(struct game_area* p);
#endif
