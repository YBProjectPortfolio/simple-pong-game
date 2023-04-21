#include "raylib.h"

class Rect
{
public:
    float x;
    float y;
    float width;
    float height;
    float speed;
    Color color;
    Rect(float x, float y, float width, float height, float speed, Color color)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->speed = speed;
        this->color = color;
    };
    void drawRect()
    {
        DrawRectangle(this->x, this->y, this->width, this->height, this->color);
    }
    void increaseUp() { this->y -= this->speed * GetFrameTime(); }
    void increaseDown() { this->y += this->speed * GetFrameTime(); }
};
