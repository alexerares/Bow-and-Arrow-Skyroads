#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"

struct platforme {
	float posx;
	float posy;
	float posz;
	bool onme = false;
	int plat;
	int tipplat;
	platforme(float x, float y, float z, int p, int t) {
		posx = x;
		posy = y;
		posz = z;
		plat = p;
		tipplat = t;
	}
};

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;
		float z = -100;
		float ysphere = 10;
		float xsphere = 7.5;
		float zsphere = 5;
		float vitplat = 0;
		float onplat = false;
		bool maxvit = false;
		int space = 0;
		int movew = 0;
		int moves = 0;
		int movea = 0;
		int moved = 0;
		int moveq = 0;
		int movee = 0;

		float combustibil = 1000;
		bool rise = false;
		float count = 0;
		int vitmax = 20;
		float oldvit = 0;
		bool vervit = true;


	private:
		std::vector <platforme> row1;
		std::vector <platforme> row2;
		std::vector <platforme> row3;
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		bool CheckCollision(float Centerx, float Centery, float Centerz, float Boxx, float Boxy, float Boxz);

		glm::vec3 lightPosition;
		unsigned int materialShininess;
		float materialKd;
		float materialKs;

	protected:
		Laborator::Camera2* camera2;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool perspectiveproj = true;;

		GLfloat Z_FAR = 200.f;
		GLfloat Z_NEAR = 1.f;

		GLfloat right = 15.f;
		GLfloat left = .05f;
		GLfloat bottom = .05f;
		GLfloat top = 15.f;
		GLfloat fov = 60.f;
};
