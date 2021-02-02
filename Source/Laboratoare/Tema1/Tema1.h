#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <vector>

class Tema1 : public SimpleScene
{
    float tx = 50;
    float ty = 350;
    float sx = 0;
    float sy = 0;
    float sr = 0;
    float ss = 0;
    float ssx = 0;
    float ssy = 0;
    bool limit_up = true;
    bool limit_down = true;
    bool scale_up = true;
    bool scale_down = true;
    int sign = 1;
    int semn = 1;
    int movew = 0;
    int moves = 0;
    int balrad = 25;
    float rotarc = 0;
    float cursorx;
    float cursory;
    float dif = 0;
    bool movearrow =false;
    bool addspeed = false;
    float arrowmovex = 0;
    float arrowmovey = 0;
    float lastx;
    float lasty;
    float lastcurx;
    float lastcury;
    float lastrot;
    float lastdiff;
    float speedarr = 300;
    float speedshur = 200;
    float verspeedshur = 300;
    bool lockspeed = false;
    int scoredim = 0;
    float shurrot = 0;
    float speednew = 300;
    int verspeed = 0;
    int lives = 3;
    int nrshur = 5;
    bool freez = false;
    float freeztime = 0;
    bool freezsag = false;
    float freezsagtime = 0;
    std::vector <int> shurtip;
    std::vector <float> shurposx;
    std::vector <float> shurposy;

    int nrbal = 5;
    std::vector <int> baltip;
    std::vector <float> balposx;
    std::vector <float> balposy;
    std::vector <float> balexp;
    std::vector <bool> beginexp;
    std::vector <bool> pop;
    std::vector <float> speedball;

public:
    Tema1();
    ~Tema1();

    void Init() override;

private:
    void FrameStart() override;
    void Update(float deltaTimeSeconds) override;
    void FrameEnd() override;

    void OnInputUpdate(float deltaTime, int mods) override;
    void OnKeyPress(int key, int mods) override;
    void OnKeyRelease(int key, int mods) override;
    void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
    void OnWindowResize(int width, int height) override;
    bool CheckCollision(float Lx1, float Ly1, float Lx2, float Ly2, float R);
    bool CheckCollisionCircle(float Lx1, float Ly1, float R1, float Lx2, float Ly2, float R2);
    bool CheckOval(float Lx1, float Ly1, float Lx2, float Ly2, float R1, float R2);

protected:
    glm::mat3 modelMatrix;
    float translateX, translateY;
    float scaleX, scaleY;
    float angularStep;
};