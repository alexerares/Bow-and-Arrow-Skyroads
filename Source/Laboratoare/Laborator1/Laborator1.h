#pragma once

#include <Component/SimpleScene.h>

class Laborator1 : public SimpleScene
{
	private:
		glm::vec3 color;
		int val=0;
		glm::vec3 position = glm::vec3(2,0,1);
		glm::vec3 rotate = glm::vec3(-3, 0, 0);
		int movew = 0;
		int moves = 0;
		int movea = 0;
		int moved = 0;
		int moveq = 0;
		int movee = 0;
		float t = 0;
		int viteza = 2;
		int rot = 0;

	public:
		Laborator1();
		~Laborator1();

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
};
