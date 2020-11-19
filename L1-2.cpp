/**
 * L1-2. Generati 8 triunghiuri aleatoare pe ecranul grafic, schimband culorile
 * de desenare ale acestora.
 */
#include <graphics.h>  // winbgi...
#include <math.h>	   // floor()
#include <stdio.h>	   // printf(), scanf()
#include <stdlib.h>	   // rand(), srand()
#include <time.h>	   // time()

int x_1;  // minimul abscisei
int x_2;  // maximul abscisei
int y_1;  // minimul ordonatei
int y_2;  // maximul ordonatei

int max_screen_x;  // maximul lungimii ecranului curent
int max_screen_y;  // maximul latimii ecranului curent

// lista culorilor, pentru afisare
char* colors[] = {"BLACK",	  "BLUE",		  "GREEN",		"CYAN",
				  "RED",	  "MAGENTA",	  "BROWN",		"LIGHTGRAY",
				  "DARKGRAY", "LIGHTBLUE",	  "LIGHTGREEN", "LIGHTCYAN",
				  "LIGHTRED", "LIGHTMAGENTA", "YELLOW",		"WHITE"};

// normalizeaza coordonata x
int screen_x(float x) {
	return ((int)floor((x - x_1) / (x_2 - x_1) * max_screen_x));
}

// normalizeaza coordonata y
int screen_y(float y) {
	return ((int)floor((y_2 - y) / (y_2 - y_1) * max_screen_y));
}

// deseneaza axele
void draw_axes() {
	// gri pentru a se putea observa si punctele care cad pe axe
	setcolor(LIGHTGRAY);

	// axele propriu-zise
	line(screen_x(x_1), screen_y(0), screen_x(x_2), screen_y(0));
	line(screen_x(0), screen_y(y_1), screen_x(0), screen_y(y_2));

	// simbolurile asociate axelor
	outtextxy(screen_x(0) - 16, screen_y(0) - 16, "0");
	outtextxy(screen_x(x_2) - 20, screen_y(0) - 20, "x");
	outtextxy(screen_x(x_2) - 6, screen_y(0) - 7, ">");
	outtextxy(screen_x(0) - 15, screen_y(y_2) + 15, "y");
	outtextxy(screen_x(0) - 1, screen_y(y_2) + 1, "^");
}

// deseneaza obiectele grafice
void draw_graphics() {
	// coordonatele individuale ale varfurilor unui triunghi (cate 2 pentru un
	// varf) array-ul are n+1 varfuri pentru a se inchide, deci (n+1)*2 = 8
	// coordonate individuale
	int vertices[8];

	int coord_random;

	for (int i = 0; i < 8; i++) {
		// genereaza coordonate aleatorii pentru varfurile unui triunghi
		for (int j = 0; j < 6; j++) {
			// formula: int random = rand() % (max - min + 1) + min;
			// prima componenta din pereche este x, a doua y
			if (j % 2 == 0) {
				coord_random = screen_x(rand() % (x_2 - x_1 + 1) + x_1);
			} else {
				coord_random = screen_y(rand() % (y_2 - y_1 + 1) + y_1);
			}

			vertices[j] = coord_random;
		}
		// inchiderea poligonului cu coordonatele primului punct
		vertices[6] = vertices[0];
		vertices[7] = vertices[1];

		// alege si seteaza culoarea aleatoriu
		int color = rand() % 14 + 1;
		setcolor(color);

		// deseneaza triunghiul
		drawpoly(4, vertices);

		printf("T%d = {(%d, %d), (%d, %d), (%d, %d)} %s\n", i + 1, vertices[0],
			   vertices[1], vertices[2], vertices[3], vertices[4], vertices[5],
			   colors[color]);
	}
}

// incepe executia
int main() {
	srand(time(0));

	// valorile domeniului de afisare sunt hardcodate pentru usurinta in
	// utilizarea programului
	x_1 = -100;
	x_2 = 100;
	y_1 = -100;
	y_2 = 100;

	// initializeaza fereastra grafica
	initwindow(800, 600, "L1-2", 100, 50);

	setbkcolor(WHITE);
	cleardevice();

	// determina rezolutia ferestrei
	max_screen_x = getmaxx();
	max_screen_y = getmaxy();

	// deseneaza axele
	draw_axes();

	// deseneaza obiectele grafice
	draw_graphics();

	getchar();
	closegraph();
	return 0;
}
