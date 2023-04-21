#include "raylib.h"

class Ball
{
public:
  int cordX = GetScreenWidth() / 2;
  int cordY = GetScreenHeight() / 2;
  float radius = 5.0f;
  float speedX = 200;
  float speedY = 500;
  float ballDia = this->radius * 2.0f;
  Color ballClr = BLACK;
  void drawBall()
  {
    DrawCircle(this->cordX, this->cordY, this->radius, this->ballClr);
  }
  void increaseX(float value) { this->speedX *= value; }
  void increaseY(float value) { this->speedY *= value; }
};
