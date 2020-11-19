/**
 * L1-4. Sa se genereze 4 cercuri incluse in interiorul unui patrat de latura
 * 10, avand centrul patratului in originea axelor de coordonate.
 */
#include <graphics.h>  // winbgi...
#include <math.h>	   // floor(), pow(), sin(), cos(), abs(), fabs(), fmin()
#include <stdio.h>	   // printf(), scanf()
#include <stdlib.h>	   // rand(), srand()
#include <time.h>	   // time()

// valorile domeniului de afisare sunt hardcodate pentru usurinta in
// utilizarea programului
int x_1 = -20;	// minimul abscisei
int x_2 = 20;	// maximul abscisei
int y_1 = -15;	// minimul ordonatei
int y_2 = 15;	// maximul ordonatei

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
	return ((int)length * max_screen_x / (abs(x_1) + abs(x_2)));
}

// genereaza un numar real intre limitele date
float random(float minimum = 0, float maximum = 1) {
	return minimum + (float)rand() / (float)(RAND_MAX / (maximum - minimum));
}

// deseneaza obiectele grafice
void draw_graphics() {
	int right = 5;	  // x
	int top = 5;	  // y
	int left = -5;	  // -x
	int bottom = -5;  // -y

	// deseneaza patratul
	setcolor(RED);
	line(screen_x(right), screen_y(top), screen_x(left), screen_y(top));
	line(screen_x(left), screen_y(top), screen_x(left), screen_y(bottom));
	line(screen_x(left), screen_y(bottom), screen_x(right), screen_y(bottom));
	line(screen_x(right), screen_y(bottom), screen_x(right), screen_y(top));

	// deseneaza 4 cercuri
	for (int i = 0; i < 4; i++) {
		// fixeaza centrul cercului in interiorul patratului
		// pentru a fi vizibil usor, centrul va fi la cel putin 1u departare de
		// latura patratului
		float x_center = random(-4, 4);
		float y_center = random(-4, 4);

		// calculeaza raza
		float radius;
		// FIXME: in lipsa de idei mai bune, testeaza fiecare cadran...
		if (x_center >= 0 && y_center >= 0) {
			radius = fmin(right - x_center, top - y_center);
		} else if (x_center <= 0 && y_center >= 0) {
			radius = fmin(fabs(left - x_center), top - y_center);
		} else if (x_center <= 0 && y_center <= 0) {
			radius = fmin(fabs(left - x_center), fabs(bottom - y_center));
		} else if (x_center >= 0 && y_center <= 0) {
			radius = fmin(right - x_center, fabs(bottom - y_center));
		}

		// alege si seteaza culoarea aleatoriu
		int color = rand() % 14 + 1;
		setcolor(color);

		// afiseaza
		printf("C%d = (%.2f, %.2f); r = %.2f %s\n", i + 1, x_center, y_center,
			   radius, colors[color]);
		circle(screen_x(x_center), screen_y(y_center), screen_length(radius));
	}
}

// incepe executia
int main() {
	srand(time(0));

	// initializeaza fereastra grafica
	initwindow(800, 600, "L1-4", 100, 50);

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
