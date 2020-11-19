/**
 * L1-3. Sa se genereze aleator 3 triunghiuri, colorate diferit, cu varfurile in
 * interiorul unui cerc cu centrul in originea sistemului de coordonate si
 * raza 5.
 */
#include <graphics.h>  // winbgi...
#include <math.h>	   // floor(), pow(), sin(), cos()
#include <stdio.h>	   // printf(), scanf()
#include <stdlib.h>	   // rand(), srand()
#include <time.h>	   // time()

const float pi = 3.1415;

// valorile domeniului de afisare sunt hardcodate pentru usurinta in
// utilizarea programului
int x_1 = -10;	// minimul abscisei
int x_2 = 10;	// maximul abscisei
int y_1 = -10;	// minimul ordonatei
int y_2 = 10;	// maximul ordonatei

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

// genereaza un numar real intre limitele date
float random(float minimum = 0, float maximum = 1) {
	return minimum + (float)rand() / (float)(RAND_MAX / (maximum - minimum));
}

// normalizeaza lungimea in functie de lungimea ecranului
int screen_length(float length) {
	return ((int)length * max_screen_x / (abs(x_1) + abs(x_2)));
}

// deseneaza obiectele grafice
void draw_graphics() {
	// deseneaza cercul
	// detaliile cercului: origine, raza
	int o_x = 0;
	int o_y = 0;
	int radius = 5;

	setcolor(GREEN);
	circle(screen_x(o_x), screen_y(o_y), screen_length(radius));

	// coordonatele individuale ale varfurilor unui triunghi (cate 2 pentru un
	// varf) array-ul are n+1 varfuri pentru a se inchide, deci (n+1)*2 = 8
	// coordonate individuale
	int vertices[8];

	// genereaza 3 triunghiuri
	for (int i = 0; i < 3; i++) {
		// genereaza coordonate aleatorii pentru varfurile unui triunghi
		for (int j = 0; j < 6; j++) {
			// v. https://programming.guide/random-point-within-circle.html
			float theta = 2 * pi * random();
			float x_logical = o_x + radius * sqrt(random()) * cos(theta);
			float y_logical = o_y + radius * sqrt(random()) * sin(theta);
			vertices[j] = screen_x(x_logical);
			vertices[j + 1] = screen_y(y_logical);
			j++;  // trebuie sa sara din 2 in 2
		}

		// inchide poligonul cu coordonatele primului punct
		vertices[6] = vertices[0];
		vertices[7] = vertices[1];

		// alege si seteaza culoarea aleatoriu
		int color = rand() % 14 + 1;
		setcolor(color);

		// afiseaza detaliile triunghiului
		printf("T%d = {(%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)} %s\n", i + 1,
			   logical_x(vertices[0]), logical_y(vertices[1]),
			   logical_x(vertices[2]), logical_y(vertices[3]),
			   logical_x(vertices[4]), logical_y(vertices[5]), colors[color]);

		// deseneaza triunghiul
		drawpoly(4, vertices);
	}
}

// incepe executia
int main() {
	srand(time(0));

	// initializeaza fereastra grafica
	initwindow(800, 600, "L1-3", 100, 50);

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
