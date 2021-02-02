#pragma once
#include <Component/SimpleScene.h>

class Laborator4 : public SimpleScene
{
	public:
		Laborator4();
		~Laborator4();

		void Init() override;
		bool moved = false;
		bool movea = false;
		bool moves = false;
		bool movew = false;
		bool mover = false;
		bool movef = false;
		bool scaleup = false;
		bool scaledown = false;
		bool rotX1 = false;
		bool rotX2 = false;
		bool rotY1 = false;
		bool rotY2 = false;
		bool rotZ1 = false;
		bool rotZ2 = false;

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
		glm::mat4 modelMatrix;
		float translateX, translateY, translateZ;
		float scaleX, scaleY, scaleZ;
		float angularStepOX, angularStepOY, angularStepOZ;
		float new_x = 6;
		float new_y;
		int sign = 1;
		float u = 0;
		float v = 3.14;
		int signbon = 1;
		float x_rot = 0;
		bool verbon = true;
		GLenum polygonMode;
};
