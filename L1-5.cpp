/**
 * L1-5. Sa se genereze aleator 5 patrate cu latura 1, avand in varfurile lor
 * cate un cerc cu raza de 5 pixeli.
 */
#include <graphics.h>  // winbgi...
#include <math.h>	   // floor(), pow(), sin(), cos(), abs(), fabs(), fmin()
#include <stdio.h>	   // printf(), scanf()
#include <stdlib.h>	   // rand(), srand()
#include <time.h>	   // time()

// valorile domeniului de afisare sunt hardcodate pentru usurinta in
// utilizarea programului
// raportul este 800 / 600 (= 10 / 7.5)
float x_1 = -10;   // minimul abscisei
float x_2 = 10;	   // maximul abscisei
float y_1 = -7.5;  // minimul ordonatei
float y_2 = 7.5;   // maximul ordonatei

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

// converteste coordonata x normalizata in valoarea ei logica
// utilizata la afisare...
// valorile sunt aproximative pentru ca x_screen e generat folosind floor
float logical_x(int x_screen) {
	return ((float)x_screen * (x_2 - x_1) / (float)max_screen_x + x_1);
}

// converteste coordonata y normalizata in valoarea ei logica
// utilizata la afisare...
float logical_y(int y_screen) {
	return (y_2 - (float)y_screen * (y_2 - y_1) / (float)max_screen_y);
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

// normalizeaza lungimea in functie de lungimea ecranului
int screen_length(float length) {
	return (int)(length * max_screen_x / (fabs(x_1) + fabs(x_2)));
}

// genereaza un numar real intre limitele date
float random(float minimum = 0, float maximum = 1) {
	return minimum + (float)rand() / (float)(RAND_MAX / (maximum - minimum));
}

// deseneaza obiectele grafice
void draw_graphics() {
	float right = 0.5;	  // x
	float top = 0.5;	  // y
	float left = -0.5;	  // -x
	float bottom = -0.5;  // -y

	// deseneaza 5 patrate
	for (int i = 0; i < 5; i++) {
		// patratele sunt identice, deci vor trebui afisate decalat
		float offset_x = random(x_1 / 2, x_2 / 2);
		float offset_y = random(y_1 / 2, y_2 / 2);

		float _right = right + offset_x;
		float _top = top + offset_y;
		float _left = left + offset_x;
		float _bottom = bottom + offset_y;

		// deseneaza patratul
		int color = rand() % 14 + 1;
		setcolor(color);
		line(screen_x(_right), screen_y(_top), screen_x(_left), screen_y(_top));
		line(screen_x(_left), screen_y(_top), screen_x(_left),
			 screen_y(_bottom));
		line(screen_x(_left), screen_y(_bottom), screen_x(_right),
			 screen_y(_bottom));
		line(screen_x(_right), screen_y(_bottom), screen_x(_right),
			 screen_y(_top));

		// deseneaza cercurile in varfurile patratului
		circle(screen_x(_right), screen_y(_top), 5);
		circle(screen_x(_left), screen_y(_top), 5);
		circle(screen_x(_left), screen_y(_bottom), 5);
		circle(screen_x(_right), screen_y(_bottom), 5);

		// afiseaza detaliile obiectelor
		printf(
			"P%d = {(%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)} "
			"%s\n",
			i + 1, _right, _top, _left, _top, _left, _bottom, _right, _bottom,
			colors[color]);
	}
}

// incepe executia
int main() {
	srand(time(0));

	// initializeaza fereastra grafica
	initwindow(800, 600, "L1-5", 100, 50);

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
