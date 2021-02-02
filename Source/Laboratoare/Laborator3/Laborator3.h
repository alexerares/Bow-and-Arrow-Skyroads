#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Laborator3 : public SimpleScene
{
	public:
		Laborator3();
		~Laborator3();

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

	protected:
		glm::mat3 modelMatrix;
		float translateX, translateY;
		float scaleX, scaleY;
		float angularStep;
		float x, y;
		float new_y;
		float val = 100;
		float sign = 1;

		float u = 0;
		float val2 = 3;
		float x_rot = 400;
		float y_rot = 250;
		float x_rotm = -50;
		float y_rotm = -50;

		float sclx = 0;
		float val3 = 5;
		float sign2 = 1;

		float z = 90;
		float val4 = 1;
		float sign3 = -1;
		float x_bon = 300;
		float y_bon = 400;
		float x_bonm = -200;
		float y_bonm = -0;
};
