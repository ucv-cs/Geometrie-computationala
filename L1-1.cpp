/**
 * L1-1. Desenati o elipsa centrata in mijlocul ferestrei grafice. Plasati 50 de
 * puncte rosii de coordonate arbitrare in interiorul acesteia. (Indicatie: a se
 * folosi functia rand() din C).
 */
#include <graphics.h>  // winbgi...
#include <math.h>	   // floor(), pow()
#include <stdio.h>	   // printf(), scanf()
#include <stdlib.h>	   // rand(), srand()
#include <time.h>	   // time()

int x_1;  // minimul abscisei
int x_2;  // maximul abscisei
int y_1;  // minimul ordonatei
int y_2;  // maximul ordonatei

int max_screen_x;  // maximul lungimii ecranului curent
int max_screen_y;  // maximul latimii ecranului curent

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

// verifica daca un punct se afla sau nu intr-o elipsa
// pentru aceasta e necesar sa fie verificata inegalitatea
// (x - o_x)^2 / x_radius^2 + (y - o_y)^2 / y_radius^2 < 1; unde (o_x, o_y) este
// originea
// daca expresia < 1, punctul e in interiorul elipsei
// daca expresia = 1, punctul e pe elipsa
// daca expresia > 1, punctul e in afara elipsei
bool test_point(int o_x, int o_y, int x, int y, int x_radius, int y_radius) {
	return ((pow((x - o_x), 2) / pow(x_radius, 2)) +
			(pow((y - o_y), 2) / pow(y_radius, 2))) < 1;
}

// deseneaza obiectele grafice
void draw_graphics() {
	// deseneaza elipsa
	int start_angle = 0;
	int end_angle = 360;
	int x_radius = 300;
	int y_radius = 150;
	setcolor(GREEN);
	ellipse(screen_x(0), screen_y(0), start_angle, end_angle, x_radius,
			y_radius);

	// coordonatele aleatorii ale punctelor
	int x_random;
	int y_random;

	// culoarea punctelor
	int color = RED;

	int point_counter = 0;
	while (point_counter < 50) {
		// genereaza coordonate aleatorii
		// formula: int random = rand() % (max - min + 1) + min;
		x_random = rand() % (x_2 - x_1 + 1) + x_1;
		y_random = rand() % (y_2 - y_1 + 1) + y_1;

		// afiseaza punctul doar daca e in interiorul elipsei
		if (test_point(screen_x(0), screen_y(0), screen_x(x_random),
					   screen_y(y_random), x_radius, y_radius)) {
			printf("x%d = (%d, %d)\n", point_counter + 1, x_random, y_random);
			putpixel(screen_x(x_random), screen_y(y_random), color);
			point_counter++;
		}
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
	initwindow(800, 600, "L1-1", 100, 50);

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
