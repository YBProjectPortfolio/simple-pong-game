#include "./components/ball.cpp"
#include "./components/rect.cpp"
#include "./components/score.cpp"
#include "./functions/printvec.cpp"
#include "raylib.h"
#include <algorithm>
#include <iostream>

int main() {
  /* InitWindow(1360, 720, "Pong game"); */
  InitWindow(1560, 1000, "Pong game");
  SetWindowState(FLAG_VSYNC_HINT);

  Ball *ball = new Ball();
  Score *score = new Score();

  float rectangleHeight = 100.0f;
  float rectangleWidth = 5.0f;
  float reactangleSpeed = 1000;

  float rightRectangleX = GetScreenWidth() - 50.0f;
  float rightRectangleY = GetScreenHeight() / 2.0f - 50.0f;

  Rect *rightRectangle =
      new Rect(rightRectangleX, rightRectangleY, rectangleWidth,
               rectangleHeight, reactangleSpeed, BLUE);

  float leftRectangleX = 50.0f;
  float leftRectangleY = GetScreenHeight() / 2.0f - 50.0f;
  Rect *leftRectangle = new Rect(leftRectangleX, leftRectangleY, rectangleWidth,
                                 rectangleHeight, reactangleSpeed, RED);

  while (!WindowShouldClose()) {

    ball->cordX += ball->speedX * GetFrameTime();
    ball->cordY += ball->speedY * GetFrameTime();
    DrawText(TextFormat("blue: %i", score->left), GetScreenWidth() - 130, 50,
             30, BLUE);
    DrawText(TextFormat("red:%i", score->right), 30, 50, 30, RED);

    if (ball->cordX > GetScreenWidth()) {
      ball->cordX = GetScreenWidth();
      ball->increaseX(-1);
      ball->ballClr = BLUE;
      score->increaseLeft();
    } else if (ball->cordX < ball->ballDia) {
      ball->cordX = ball->ballDia;
      ball->increaseX(-1);
      ball->ballClr = RED;
      score->increaseRight();
    } else if (ball->cordY > GetScreenHeight()) {
      ball->cordY = GetScreenHeight();
      ball->increaseY(-1);
    } else if (ball->cordY < ball->ballDia) {
      ball->cordY = ball->ballDia;
      ball->increaseY(-1);
    }

    if (IsKeyDown(KEY_W) && leftRectangle->y > 0) {
      leftRectangle->increaseUp();
    }
    if (IsKeyDown(KEY_S) &&
        leftRectangle->y < GetScreenHeight() - leftRectangle->height) {
      leftRectangle->increaseDown();
    }

    if (IsKeyDown(KEY_I) && rightRectangle->y > 0) {
      rightRectangle->increaseUp();
    }
    if (IsKeyDown(KEY_K) &&
        rightRectangle->y < GetScreenHeight() - leftRectangle->height) {
      rightRectangle->increaseDown();
    }

    if (CheckCollisionCircleRec(
            Vector2{(float)ball->cordX, (float)ball->cordY}, ball->radius,
            Rectangle{leftRectangle->x, leftRectangle->y, rightRectangle->width,
                      rightRectangle->height})) {
      ball->cordX = ball->ballDia + leftRectangleX + rectangleWidth;
      ball->increaseX(-1.1f);
      ball->ballClr = BLUE;
    };

    if (CheckCollisionCircleRec(
            Vector2{(float)ball->cordX, (float)ball->cordY}, ball->radius,
            Rectangle{rightRectangle->x, rightRectangle->y,
                      rightRectangle->width, rightRectangle->height})) {
      ball->cordX = rightRectangleX - ball->ballDia + rectangleWidth;
      ball->increaseX(-1.1f);
      ball->ballClr = RED;
    };

    BeginDrawing();
    ClearBackground(WHITE);

    ball->drawBall();

    leftRectangle->drawRect();
    rightRectangle->drawRect();

    DrawFPS(10, 10);
    DrawText(TextFormat("Project->https://github.com/ybprojectportfolio"),
             GetScreenWidth() - 300, GetScreenHeight() - 20, 11, BLACK);
    EndDrawing();
  }
  delete leftRectangle;
  delete rightRectangle;
  delete ball;
  delete score;
  CloseWindow();
  return 0;
}
