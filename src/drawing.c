#include <sys/ioctl.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "drawing.h"
#include "snake.h"

void setplayarea(struct game_area* p) {
		int row, col;
		getmaxyx(stdscr, row, col);

		p->min_x = 1;
		p->max_x = col - 1;
		p->max_y = row -1;
		p->min_y = 1;
}

void setupcurses() {
		initscr(); 				// Start curses mode
		cbreak(); 					// Disable line buffering
		noecho();
		curs_set(0);
		keypad(stdscr, TRUE);	// Enable keypad 
}

void startscreen() {
		int row, col;
		getmaxyx(stdscr, row, col);
		char msg[]  = "Welcome to snake!";
		char scndmsg[] = "Press any key to begin!";
		drawborder(score);
		mvprintw((row)/2+1, (col-strlen(msg))/2, "%s", msg);
		mvprintw((row)/2+2, (col-strlen(scndmsg))/2, "%s", scndmsg);
}

void deathscreen() {
		int row, col;
		getmaxyx(stdscr, row, col);
		char msg[]  = "You have died :(";
		char scndmsg[] = "Your final score was %d";
		char thrdmsg[] = "Press any key to exit";
		drawborder(score);
		mvprintw((row)/2+1, (col-strlen(msg))/2, "%s", msg);
		mvprintw((row)/2+2, (col-strlen(scndmsg))/2, scndmsg, score);
		mvprintw((row)/2+3, (col-strlen(thrdmsg))/2, "%s", thrdmsg);
}

void drawborder() {
		int row, col;
		getmaxyx(stdscr, row, col);
		char score_msg[] = "Score: %d";
		mvprintw(0, col-strlen(score_msg), score_msg, score);
		move(1, 0);

		for(int i = 0;i < col;i++) {
				printw("#");
		}

		for(int i = 1;i < row - 2;i++) { 

				printw("#");

				for(int j = 1; j < col - 1;j++) {
						printw(" ");
				}

				printw("#");
		}

		for(int i = 0;i < col;i++) {
				printw("#");
		}
}
