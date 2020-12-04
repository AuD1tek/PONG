#pragma once

namespace Settings 
{
	class game
	{
	public:
		int OrthoWid;
		int OrthoHei;
		int WinWid;
		int WinHei;
		int winXPos;
		int winYPos;
		float FieldSizeX;
		float FieldSizeY;
		int delay;
		float PThickness;
		float BallSize;
		float BorderT;
		float MLineT;
		int ScoreL;
		int ScoreR;
		float TextPosX;
		float TextPosY;
		float BallSpeedX;
		float PSpeedY;


		game() {
			WinWid = 700;
			WinHei = 700;
			OrthoWid = 700;
			OrthoHei = 700;
			winXPos = 100;
			winYPos = 100;
			delay = 1;
			PThickness = 10;
			BallSize = 5;
			BorderT = 10;
			MLineT = 5;
			ScoreL = 0;
			ScoreR = 0;
			TextPosX = 0;
			TextPosY = FieldSizeY + 10;
			BallSpeedX = 0.5;
			PSpeedY = 1;

			this->WinHei = 10;
		}

		void start_settings();
		void win();
		void KeyControl();
		void KeyReset();
		void DrawField();
		void DrawScore();
	}settings;

	void game::start_settings()
	{
		left.size = 200;
		right.size = 200;
		left.x = -510;
		right.x = 510;
		while (ball.vx == 0) ball.vx = (rand() % 3 - 1) * BallSpeedX;
		ball.x = 0;
		ball.y = 0;
		ball.vy = 0;
	}
	void game::win()
	{
		if ((ScoreL == 8) || (ScoreR == 8)) 
		{
			glutTimerFunc(2000, exit, 0);
			delay = 10000;
		}
		if (ball.x < left.x + PThickness - BallSpeedX)
		{
			//start.settings();
			right.hold = true;
			ScoreR++;
		}
		if (ball.x > left.x - PThickness + BallSpeedX)
		{
			//start.settings();
			left.hold = true;
			ScoreL++;
		}
	}
	void game::KeyControl()
	{
		if ((left.Up) && (!left.Down))left.vy = PSpeedY;
		if ((!left.Up) && (left.Down))left.vy = -PSpeedY;
		if ((right.Up) && (!right.Down))left.vy = PSpeedY;
		if ((!right.Up) && (right.Down))left.vy = -PSpeedY;
	}
	void game::KeyReset()
	{
		left.vy = 0;
		right.vy = 0;
	}
	void game::DrawField()
	{
		glColor3f(1, 1, 1);
		//glColor(1, 1, 1);
		glVertex2f(-FieldSizeX - BorderT, -FieldSizeY - BorderT);
		glVertex2f(FieldSizeX + BorderT, -FieldSizeY - BorderT);
		glVertex2f(FieldSizeX + BorderT, -FieldSizeY);
		glVertex2f(-FieldSizeX - BorderT, -FieldSizeY);

		glVertex2f(-FieldSizeX - BorderT, -FieldSizeY + BorderT);
		glVertex2f(FieldSizeX + BorderT, -FieldSizeY + BorderT);
		glVertex2f(FieldSizeX + BorderT, FieldSizeY);
		glVertex2f(-FieldSizeX - BorderT, FieldSizeY);

		glVertex2f(-FieldSizeX - BorderT, -FieldSizeY - BorderT);
		glVertex2f(-FieldSizeX, -FieldSizeY - BorderT);
		glVertex2f(-FieldSizeX, FieldSizeY + BorderT);
		glVertex2f(-FieldSizeX - BorderT, FieldSizeY + BorderT);

		glVertex2f(FieldSizeX, -FieldSizeY - BorderT);
		glVertex2f(FieldSizeX + BorderT, -FieldSizeY - BorderT);
		glVertex2f(FieldSizeX + BorderT, FieldSizeY + BorderT);
		glVertex2f(FieldSizeX, FieldSizeY + BorderT);

		for (float i = -FieldSizeY; i < FieldSizeY; i += 4 * MLineT) {
			glVertex2f(-MLineT, i + MLineT);
			glVertex2f(MLineT, i + MLineT);
			glVertex2f(MLineT, i - MLineT);
			glVertex2f(-MLineT, i - MLineT);
		}
	}
	void game::DrawScore()
	{
		glRasterPos2f(TextPosX - 50, TextPosY + 20);

		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + ScoreL);
		glRasterPos2f(TextPosX + 30, TextPosY + 20);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + ScoreR);
		if (ScoreL == 8) {
			glRasterPos2f(TextPosX - 200, TextPosY + 40);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'W');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
		}
		if (ScoreR == 8) {
			glRasterPos2f(TextPosX + 150, TextPosY + 40);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'W');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
		}
	}



	class ball
	{
	public:
		float x;
		float y;
		float vx;
		float vy;

		void move();
		void reflection();
		void draw();
	}ball;

	void ball::move()
	{
		x += vx;//привавляется к оси Х скорость мяча
		y += vy;
	}
	void ball::reflection()
	{
		if ((y <= -settings.FieldSizeY) || (y >= settings.FieldSizeY))vy = -vy;
		if ((x <= x + settings.PThickness) && (fabs(double(y - left.y)) <= left.size / 2 + fabs(vy))) {
			vx = -vx;
			vy += vy * settings.BallSpeedX / 2;
		}
		if ((x >= x + settings.PThickness) && (fabs(double(y - right.y)) <= right.size / 2 + fabs(vy))) {
			vx = -vx;
			vy += vy * settings.BallSpeedX / 2;
		}
	}
	void ball::draw()
	{
		glVertex2f(x + settings.BallSize, y + settings.BallSize);
		glVertex2f(x + settings.BallSize, y - settings.BallSize);
		glVertex2f(x - settings.BallSize, y - settings.BallSize);
		glVertex2f(x - settings.BallSize, y + settings.BallSize);
	}



	class reflector {
	public:
		float x, y;
		float vy;
		float size;
		bool Up, Down, hold;
		reflector() {
			vy = 0;
			x = 0;
			y = 0;
			Up = false;
			Down = false;
			hold = false;
		}
		void draw();
		void move();
		void care();
	}left, right;

	void reflector::draw()
	{
		glColor3f(1, 1, 1);
		glVertex2f(x + settings.PThickness, y + size / 2);
		glVertex2f(x + settings.PThickness, y - size / 2);
		glVertex2f(x - settings.PThickness, y - size / 2);
		glVertex2f(x - settings.PThickness, y + size / 2);
	}
	void reflector::move()
	{
		y += vy;
		if (y < -settings.FieldSizeY + size / 2)
		{
			y = -settings.FieldSizeY + size / 2;
			vy = 0;
		}
		if (y > settings.FieldSizeY - size / 2)
		{
			y = settings.FieldSizeY - size / 2;
			vy = 0;
		}
	}
	void reflector::care()
	{
		if (hold) {
			ball.vx = 0;
			if (x < 0)ball.x = x + 2 * settings.PThickness;
			if (x > 0)ball.x = x - 2 * settings.PThickness;
			ball.vy = vy;
			ball.y = y;
		}
	}
}