#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <glut.h>


//int iterations = 500;
//float scale = -2.0
//int windowPlay;
char title[] = "SNAKE";
int game = 0;
int windowID;
using namespace std;
GLuint displist;
int dir = 0; //  0 - вверх  1 - направо 2 - вниз 3 - налево
int w = 900;
int h = 664;
int len = 3;
int speed = 100;
time_t start, end;
struct
{
	int x;
	int y;
} Snake[100];

struct
{
	int x;
	int y;
} Fruit;

struct
{
	int x;
	int y;
} Bonus1;

void Sdisplay()
{
	glPointSize(20);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	if (game == 2 || game == 3)
	{
		glColor3f(0.5, 0.1, 0);
		for (int i = 20; i < 380; i++) glVertex2f(i, 20);
		for (int i = 20; i < 280; i++) glVertex2f(20, i);
		for (int i = 20; i < 380; i++) glVertex2f(i, 280);
		for (int i = 20; i < 280; i++) glVertex2f(380, i);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glColor3f(0, 1, 0);

	for (int i = 0; i < len; ++i)
	{
		glVertex2f(Snake[i].x - 10, Snake[i].y - 10);
	}

	glColor3f(1, 0.3, 0);
	glVertex2f(Fruit.x - 10, Fruit.y - 10);

	glClear(GL_COLOR_BUFFER_BIT);

	if (game == 3)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(Bonus1.x - 10, Bonus1.y - 10);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	glEnd();
	glFlush();
	glutSwapBuffers();

}
void Bon1(int = 0) {
	while (true) {
		Bonus1.x = rand() % 400;
		Bonus1.y = rand() % 300;
		int i = 0;
		while ((Bonus1.y != Snake[i].y || Bonus1.x != Snake[i].x) && i < len && Bonus1.x % 10 == 0 && Bonus1.y % 10 == 0 && Bonus1.x > 40 && Bonus1.x < 350 && Bonus1.y > 40 && Bonus1.y < 250 && (Bonus1.x != Fruit.x || Bonus1.y != Fruit.y)) {
			i++;
		}
		if (i == len)
		{
			break;
		}
	}

}


void Mech(int = 0)
{
	Sdisplay();

	if (dir == 0 && speed % 10 == 0)
	{
		for (int i = len - 1; i > 0; --i)
		{
			Snake[i].x = Snake[i - 1].x;
			Snake[i].y = Snake[i - 1].y;
		}
		Snake[0].y -= 10;
		speed = 1;
	}

	if (dir == 1 && speed % 10 == 0)
	{
		for (int i = len - 1; i > 0; --i)
		{
			Snake[i].x = Snake[i - 1].x;
			Snake[i].y = Snake[i - 1].y;
		}
		Snake[0].x += 10;
		speed = 1;
	}

	if (dir == 2 && speed % 10 == 0)
	{
		for (int i = len - 1; i > 0; --i)
		{
			Snake[i].x = Snake[i - 1].x;
			Snake[i].y = Snake[i - 1].y;
		}
		Snake[0].y += 10;
		speed = 1;
	}

	if (dir == 3 && speed % 10 == 0)
	{
		for (int i = len - 1; i > 0; --i)
		{
			Snake[i].x = Snake[i - 1].x;
			Snake[i].y = Snake[i - 1].y;
		}
		Snake[0].x -= 10;
		speed = 1;
	}

	if ((Snake[0].x <= 30 || Snake[0].y <= 30 || Snake[0].x >= 390 || Snake[0].y >= 290) && (game != 1))
	{
		end = clock() * 1000 / CLOCKS_PER_SEC;;
		printf("\nReal time for sorting %i(ms)\n", (end - start));
		MessageBox(NULL, "Вы проиграли! Не выходите за границы поля", "End of the game", MB_OK);
		exit(0);
	}
	else
	{
		for (int i = 0; i <= 3; i++) { 
			if (i == 0) {
				if (Snake[0].x <= 200) Snake[0].x += 390;
			}
			else if (i == 1) {
				if (Snake[0].x >= 410) Snake[0].x -= 390;
			}
			else if (i == 2) {
				if (Snake[0].y <= 200) Snake[0].y += 290;
			}
			else if (i == 3) {
				if (Snake[0].y >= 310)Snake[0].y -= 290;
			}
		}

	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (dir != 1)dir = 3;
	}
	else
		if (GetAsyncKeyState(VK_RIGHT))
		{
			if (dir != 3)dir = 1;
		}
		else
			if (GetAsyncKeyState(VK_UP))
			{
				if (dir != 0)dir = 2;
			}
			else
				if (GetAsyncKeyState(VK_DOWN))
				{
					if (dir != 2)dir = 0;
				}
				else
					if (GetAsyncKeyState(VK_ESCAPE)) exit(0);

	if (Snake[0].x == Fruit.x && Snake[0].y == Fruit.y)
	{
		while (true)
		{
			Fruit.x = rand() % 400;
			Fruit.y = rand() % 300;
			int i = 0;
			if (game != 1)
			{
				while ((Fruit.y != Snake[i].y || Fruit.x != Snake[i].x) && i < len && Fruit.x % 10 == 0 && Fruit.y % 10 == 0 && Fruit.x > 40 && Fruit.x < 350 && Fruit.y > 40 && Fruit.y < 250)
				{
					i++;
				}
			}
			else
			{
				while ((Fruit.y != Snake[i].y || Fruit.x != Snake[i].x) && i < len && Fruit.x % 10 == 0 && Fruit.y % 10 == 0 && Fruit.x >= 20 && Fruit.x <= 400 && Fruit.y >= 20 && Fruit.y <= 300)
				{
					i++;
				}
			}
			if (i == len)
			{
				break;
			}

		}
		++len;
		Snake[len].x = Snake[len].x;
		Snake[len].y = Snake[len].y - 10;
	}
	if (Snake[0].x == Bonus1.x && Snake[0].y == Bonus1.y  && game == 3) {
		Bonus1.x = 0;
		Bonus1.y = 0;
		len = len + 3;
		Snake[len].x = Snake[len].x;
		Snake[len].y = Snake[len].y - 30;
		glutTimerFunc(30000, Bon1, 0);
	}
	for (int i = 1; i < len; ++i)
		if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y)
		{
			MessageBox(NULL, "Вы врезались в себя :(", "End of the game", MB_OK);
			exit(0);
		}

	if (len == 100)
	{
		MessageBox(NULL, "Ты выиграл! :)", "Win", MB_OK);
		exit(0);
	}

	if (speed < 200) speed++;

	glutTimerFunc(10, Mech, 0);
}

void init()
{
	int len = 3;
	int speed = 100;
	int dir = 0;

	srand(time(NULL));

	while (true)
	{
		Fruit.x = rand() % 400;
		Fruit.y = rand() % 300;
		if ((game == 2 || game == 3) && Fruit.x % 10 == 0 && Fruit.y % 10 == 0 && Fruit.x > 40 && Fruit.x < 350 && Fruit.y > 40 && Fruit.y < 250) break;
		else
		{
			if (game == 1 && Fruit.x % 10 == 0 && Fruit.y % 10 == 0 && Fruit.x >= 20 && Fruit.x <= 400 && Fruit.y >= 20 && Fruit.y <= 300) break;
		}
	}

	if (game == 3) {
		while (true) {
			Bonus1.x = rand() % 400;
			Bonus1.y = rand() % 300;
			if (Bonus1.x % 10 == 0 && Bonus1.y % 10 == 0 && Bonus1.x > 40 && Bonus1.x < 350 && Bonus1.y > 40 && Bonus1.y < 250 && (Bonus1.x != Fruit.x || Bonus1.y != Fruit.y)) break;
		}
	}

	Snake[0].x = 200;
	Snake[0].y = 150;

	for (int i = 0; i < len; ++i)
	{
		Snake[i + 1].x = Snake[i].x;
		Snake[i + 1].y = Snake[i].y + 10;
	}
	Mech();
}

void drawText(float x, float y, const char text[], int j) {
	int len = strlen(text);
	glColor3f(0.0, 0.0, 0.0);
	if (j == 1) {
		glRasterPos2i(x, y);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
	if (j == 2) {
		glRasterPos2i(x, y);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);  //glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}

	if (j == 3) {
		void *font = GLUT_STROKE_ROMAN; //один из предварительно определены шрифтов в GLUT
		glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(0.4f, 0.3f, 25.0f);
		for (int i = 0; i < len; i++)
			glutStrokeCharacter(font, text[i]);
		glPopMatrix();
	}
}


void Modes() {
	

	if (game == 1) {
		printf("1\n");
		Sleep(800);
		glClearColor(0.0, 0.0, 0, 0.0);
		glViewport(0, 0, w, h);
		gluOrtho2D(0, 400, 0, 300);

		glutDisplayFunc(Sdisplay);

		init();
		//timer(); 
		glutMainLoop();

	}
	if (game == 2) {
		printf("2\n");
		Sleep(800);
		glClearColor(0.0, 0.0, 0, 0.0);
		glViewport(0, 0, w, h);
		gluOrtho2D(0, 400, 0, 300);

		glutDisplayFunc(Sdisplay);

		init();
		//timer();

		glutMainLoop();
	}
	if (game == 3) {
		printf("3\n");
		Sleep(800);
		glClearColor(0.0, 0.0, 0, 0.0);
		glViewport(0, 0, w, h);
		gluOrtho2D(0, 400, 0, 300);

		glutDisplayFunc(Sdisplay);

		init();
		Mech();

		glutMainLoop();
	}
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glutSwapBuffers();

}

void orthogonalStart(void) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 1536, 0, 864);
	glMatrixMode(GL_MODELVIEW);
}

void orthogonalEnd(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 49) {
		game = 1;
		Modes();
		glutMainLoop();
	}
	else if (key == 50) {
		game = 2;
		Modes();
		glutMainLoop();

	}
	else if (key == 51) {
		game = 3;
		Modes();
		glutMainLoop();
	}
	printf("%i %c\n", key, key);
}

void displayMenu(void) {
	glClearColor((float)255 / 255.0, (float)255 / 255.0, (float)255 / 255.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	orthogonalStart();
	displist = glGenLists(1);
	glNewList(displist, GL_COMPILE);
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);

	drawText(678, 730, "SNAKE", 3);
	drawText(679, 730, "SNAKE", 3);
	drawText(678, 731, "SNAKE", 3);
	drawText(679, 731, "SNAKE", 3);
	drawText(680, 730, "SNAKE", 3);
	drawText(680, 731, "SNAKE", 3);

	int shift = 0;
	for (int i = 0; i < 3; i++) {
		glBegin(GL_QUADS);
		glColor3f((float)230 / 255.0, (float)230 / 255.0, (float)230 / 255.0);

		glVertex2f(568, 350 + shift); //нижний левый угол
		glVertex2f(568, 250 + shift); //верхний левый угол
		glVertex2f(968, 250 + shift); //верхний правый угол
		glVertex2f(968, 350 + shift); //нижний правый угол
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		if (i == 2) {
			glRasterPos2i(728, 300); //set position to top corner to print EDIT 
			drawText(720, 300 + shift, "level 1", 2);
		}
		if (i == 1) {
			drawText(720, 300 + shift, "level 2", 2);
		}
		if (i == 0) {
			drawText(720, 300 + shift, "level 3", 2);
		}
		glPopMatrix();
		shift += 130;
		glFlush();
	}
	glEndList();
	glCallList(displist);
	orthogonalEnd();
	glutSwapBuffers();
	glLoadIdentity();
	glFlush();
}

int main(int argc, char **argv) {
	start = clock() * 1000 / CLOCKS_PER_SEC;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(80, 80);
	windowID = glutCreateWindow(title);
	glutDisplayFunc(displayMenu);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}