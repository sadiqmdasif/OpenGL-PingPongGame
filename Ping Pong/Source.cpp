#include <GL/glut.h>
#include <stdarg.h>
#include <stdio.h>
#include <cmath>
#define RADIUS 0.025
#define SPEED  0.0002

int WIDTH = 900;
int HEIGHT = 650;
int RATIO = WIDTH / HEIGHT;

float P1_XPOS = 0;
float P1_YPOS = -0.83;

float P2_XPOS = 0;
float P2_YPOS = -.75;
float x_pos = 0, y_pos = -.8;

bool p1hit_center = false, p1hit_corner = false;
bool p2hit_center = false, p2hit_corner = false;

bool game_over = false;
bool RIGHT = 1, LEFT = 0, UP = 1, DOWN = 0;
bool started = false;

bool hit = false;
int lives = 3;

void ball_draw()
{
	glColor3f(0.1, 0.1, 0.3);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x_pos, y_pos);
	for (float angle = 0; angle < (10); angle += 0.01)
	{
		glVertex2f((x_pos + sin(angle) * RADIUS), (y_pos + (cos(angle)) * RADIUS));
	}
	glEnd();
}

bool crashed()
{
	if (y_pos < P1_YPOS - 0.05 )
	{
		//down miss
		
		return true;
	}

	else if (y_pos > P2_YPOS+1.70)
	{
		//up miss

		return true;
	}
	else return false;;
}
void paddle1_hit()
{
	p1hit_corner = false;
	p1hit_center = false;
	if (x_pos <= P1_XPOS + 0.13 && x_pos >= P1_XPOS - 0.13)
	{
		if (y_pos <= P1_YPOS+.02)
		{
			p1hit_center = true;
		}
	}
	else if ((x_pos >= P1_XPOS + 0.13 && x_pos <= P1_XPOS + 0.2) || (x_pos <= P1_XPOS - 0.13 && x_pos >= P1_XPOS - 0.2))
	{
		if (y_pos <= P1_YPOS+.02)
		{
			p1hit_corner = true;
		}
	}
}

void paddle2_hit()
{
	p2hit_corner = false;
	p2hit_center = false;
	if (x_pos <= P2_XPOS + 0.13 && x_pos >= P2_XPOS - 0.13)
	{
		if (y_pos >= P2_YPOS+1.58)
		{
			p2hit_center = true;
		}
	}
	else if ((x_pos >= P2_XPOS + 0.13 && x_pos <= P2_XPOS + 0.2) || (x_pos <= P2_XPOS - 0.13 && x_pos >= P2_XPOS - 0.2))
	{
		if (y_pos >= P2_YPOS+1.58)
		{
			p2hit_corner = true;
		}
	}
}
void ball_move()
{
	if (UP && RIGHT)
	{
		x_pos += (SPEED);
		y_pos += (SPEED);
	}
	if (UP && LEFT)
	{
		x_pos -= (SPEED);
		y_pos += (SPEED);
	}
	if (DOWN && RIGHT)
	{
		x_pos += (SPEED);
		y_pos -= (SPEED);
	}
	if (DOWN && LEFT)
	{
		x_pos -= (SPEED);
		y_pos -= (SPEED);
	}

	if (x_pos >= (RATIO - RADIUS))
	{
		RIGHT = 0;
		LEFT = 1;
	}
	else if (x_pos <= (-RATIO + RADIUS))
	{
		RIGHT = 1;
		LEFT = 0;
	}
	if (y_pos >= (RATIO - RADIUS) || hit)
	{
		UP = 0;
		DOWN = 1;
	}
	else if (y_pos <= (-RATIO + RADIUS) || hit)
	{
		UP = 1;
		DOWN = 0;
	}
	paddle1_hit();
	if (p1hit_center)
	{
		DOWN = 0;
		UP = 1;
	}
	if (p1hit_corner)
	{
		if (LEFT)
		{
			LEFT = 0;
			RIGHT = 1;
		}
		else
		{
			RIGHT = 0;
			LEFT = 1;
		}
		UP = 1;
		DOWN = 0;
	}

	paddle2_hit();
	if (p2hit_center)
	{
		DOWN = 1;
		UP = 0;
	}
	if (p2hit_corner)
	{
		if (LEFT)
		{
			LEFT = 0;
			RIGHT = 1;
		}
		else
		{
			RIGHT = 0;
			LEFT = 1;
		}
		UP = 0;
		DOWN = 1;
	}


}
void paddle1_draw()
{
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(P1_XPOS - 0.2, P1_YPOS);
	glVertex2f(P1_XPOS + 0.2, P1_YPOS);
	glVertex2f(P1_XPOS + 0.2, P1_YPOS - 0.05);
	glVertex2f(P1_XPOS - 0.2, P1_YPOS - 0.05);
	glEnd();
}

void paddle2_draw()
{
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(P2_XPOS - 0.2, 1.65+P2_YPOS);
	glVertex2f(P2_XPOS + 0.2, 1.65+P2_YPOS);
	glVertex2f(P2_XPOS + 0.2, 1.65+P2_YPOS - 0.05);
	glVertex2f(P2_XPOS - 0.2, 1.65+P2_YPOS - 0.05);
	glEnd();
}


void BallLoop()
{
	glClearColor(.47, .89, .9, 0);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ball_draw();	
	paddle1_draw();
	paddle2_draw();
	
	glFlush();
	if (started)
		ball_move();
	if (crashed())
	{
		x_pos = 0;
		y_pos = -.80;
		started = 0;
		UP = 1;
		RIGHT = 1;
		DOWN = 0;
		LEFT = 0;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}
void user_input(unsigned char key, int x, int y)
{
	if (key == 13)
		started = true;
}

void ArrowKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT && P1_XPOS >= -0.75)
		for (float a = 0; a < 0.05; a += 0.001)
		{
		P1_XPOS -= 0.003;
		BallLoop();
		}
	if (key == GLUT_KEY_RIGHT && P1_XPOS <= 0.75)
	{
		for (float a = 0; a < 0.05; a += 0.001)
		{
			P1_XPOS += 0.003;
			BallLoop();
		}
	}

	if (key == GLUT_KEY_UP && P2_XPOS >= -0.75)
		for (float a = 0; a < 0.05; a += 0.001)
		{
		P2_XPOS -= 0.003;
		BallLoop();
		}
	if (key == GLUT_KEY_DOWN && P2_XPOS <= 0.75)
	{
		for (float a = 0; a < 0.05; a += 0.001)
		{
			P2_XPOS += 0.003;
			BallLoop();
		}
	}
	
}


void changeSize(int w, int h)
{

	if (h == 0)
		h = 1;
	RATIO = w / h;
	float ratio = 1.0* w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	BallLoop();
}
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Ping pong");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(BallLoop);
	glutKeyboardFunc(user_input);
	glutSpecialFunc(ArrowKeys);
	glutMainLoop();
	return 0;
}
