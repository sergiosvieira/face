#include "raylib.h"
#include <map>
#include <random>
#include <vector>

enum class IrisPosition {
    Center,
    Left,
    Right,
    Up,
    Down,
    Closed
};

enum class Mouth {
    Closed,
    Opened
};

using Vector = std::vector<IrisPosition>;
using Map = std::map<IrisPosition, Vector2>;

IrisPosition randomIris() {
    Vector v = {
        IrisPosition::Center,
        IrisPosition::Left,
        IrisPosition::Right,
        IrisPosition::Up,
        IrisPosition::Down,
        IrisPosition::Closed,
    };
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, v.size());
    return v[static_cast<int>(dist(mt))];
}

class Face {
    int sw = 0;
    int sh = 0;
    float eyeRadius = 190.f;
    Vector2 center;
    Vector2 leftEye, rightEye;
    IrisPosition iris = IrisPosition::Closed;
    Mouth mouth = Mouth::Closed;
    Map irisMap = {
        {IrisPosition::Center, {0.f, 0.f}},
        {IrisPosition::Left, {- eyeRadius * 0.5, 1.0f}},
        {IrisPosition::Right, {eyeRadius * 0.5, 1.f}},
        {IrisPosition::Up, {1.f, - eyeRadius * 0.5}},
        {IrisPosition::Down, {1.f, eyeRadius * 0.5}}
    };
public:
    Face(int screenWidth,
         int screenHeight):
        sw(screenWidth),
        sh(screenHeight) {
        float rate = 0.3;
        center = {sw / 2.f, sh / 2.f};
        leftEye  = {(center.x - eyeRadius) * (1.f - rate), center.y - eyeRadius};
        rightEye = {(center.x + eyeRadius) * (1.f + rate), center.y - eyeRadius};
    }
    void drawEyes() {
        // left
        DrawCircle(leftEye.x, leftEye.y, eyeRadius, WHITE);
        DrawCircle(leftEye.x, leftEye.y, eyeRadius * 0.91, WHITE);
        //right
        DrawCircle(rightEye.x, rightEye.y, eyeRadius, WHITE);
        DrawCircle(rightEye.x, rightEye.y, eyeRadius * 0.91, WHITE);
    }
    void drawClosedEyes() {
        Vector2 l1 = {leftEye.x - eyeRadius, leftEye.y};
        Vector2 r1 = {leftEye.x + eyeRadius, leftEye.y};
        Vector2 c1 = leftEye;
        DrawLineBezierQuad(l1, r1, c1, 20, WHITE);

        Vector2 l2 = {rightEye.x - eyeRadius, rightEye.y};
        Vector2 r2 = {rightEye.x + eyeRadius, rightEye.y};
        Vector2 c2 = rightEye;
        DrawLineBezierQuad(l2, r2, c2, 20, WHITE);

    }
    void drawIris() {
        Vector2 offset = irisMap[iris];
        // left
        DrawCircle(leftEye.x + offset.x, leftEye.y + offset.y, eyeRadius * 0.5, BLACK);
        //right
        DrawCircle(rightEye.x + offset.x, rightEye.y + offset.y, eyeRadius * 0.5, BLACK);
    }
    void drawSmile() {
        // Desenha a curva do sorriso
        Vector2 left = {leftEye.x, leftEye.y + 250};
        Vector2 right = {rightEye.x, rightEye.y + 250};
        Vector2 c = {center.x, center.y + 200};
        DrawLineBezierQuad(left, right, c, 15, RAYWHITE);
    }
    void drawOpenedMouth() {
        DrawEllipse(center.x, center.y + 150, 300, 125, RAYWHITE);
    }
    void draw() {
        int p1 = 50, p2 = p1 * 2;
        DrawRectangle(0, 0, sw, sh, WHITE);
        DrawRectangle(p1, p1, sw - p2, sh - p2, BLACK);
        if (iris != IrisPosition::Closed) {
            drawEyes();
            drawIris();
        } else {
            drawClosedEyes();
        }
        if (mouth == Mouth::Closed) {
            drawSmile();
        } else {
            drawOpenedMouth();
        }

    }
    void randomLooking() {
        this->iris = randomIris();
    }
};

int main()
{
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Hello, World!");
    SetTargetFPS(1);
    ToggleFullscreen();
    Face face(GetScreenWidth(),GetScreenHeight());
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        face.draw();
        face.randomLooking();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
