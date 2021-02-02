#include "Laborator4.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	// initialize tx, ty and tz (the translation steps)
	translateX = 0;
	translateY = 0;
	translateZ = 0;

	// initialize sx, sy and sz (the scale factors)
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
	// initialize angularSteps
	angularStepOX = 0;
	angularStepOY = 0;
	angularStepOZ = 0;
}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	if (moved) {
		translateX = translateX + 5 *deltaTimeSeconds;
		moved = false;
	}

	if (movea) {
		translateX = translateX - 5 * deltaTimeSeconds;
		movea = false;
	}

	if (movew) {
		translateZ = translateZ + 5 * deltaTimeSeconds;
		movew = false;
	}

	if (moves) {
		translateZ = translateZ - 5 * deltaTimeSeconds;
		moves = false;
	}

	if (mover) {
		translateY = translateY + 5 * deltaTimeSeconds;
		mover = false;
	}

	if (movef) {
		translateY = translateY - 5 * deltaTimeSeconds;
		movef = false;
	}


	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 0.5f,-1.5f);
	modelMatrix *= Transform3D::Translate(translateX, translateY, translateZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	if (scaleup) {
		scaleX = scaleX + deltaTimeSeconds;
		scaleY = scaleY + deltaTimeSeconds;
		scaleZ = scaleZ + deltaTimeSeconds;
		scaleup = false;
	}

	if (scaledown) {
		scaleX = scaleX - deltaTimeSeconds;
		scaleY = scaleY - deltaTimeSeconds;
		scaleZ = scaleZ - deltaTimeSeconds;
		scaledown = false;
	}

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(scaleX, scaleY, scaleZ);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	if (rotX1) {
		angularStepOX = angularStepOX + 2 * deltaTimeSeconds;
		rotX1 = false;
	}

	if (rotX2) {
		angularStepOX = angularStepOX - 2 * deltaTimeSeconds;
		rotX2 = false;
	}

	if (rotY1) {
		angularStepOY = angularStepOY + 2 * deltaTimeSeconds;
		rotY1 = false;
	}

	if (rotY2) {
		angularStepOY = angularStepOY - 2 * deltaTimeSeconds;
		rotY2 = false;
	}

	if (rotZ1) {
		angularStepOZ = angularStepOZ + 2 * deltaTimeSeconds;
		rotZ1 = false;
	}

	if (rotZ2) {
		angularStepOZ = angularStepOZ - 2 * deltaTimeSeconds;
		rotZ2 = false;
	}

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(angularStepOX);
	modelMatrix *= Transform3D::RotateOY(angularStepOY);
	modelMatrix *= Transform3D::RotateOZ(angularStepOZ);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);


	if (u > 360)
		u = 0;

	u = u + 2 * deltaTimeSeconds;

	if(verbon)
		if (v > 6.28) {
			//x_rot = x_rot - 4;
			//signbon = -1;
			v = 3.14;
			x_rot = x_rot - signbon * 2;
		}

	if (!verbon)
		if (v < 3.14) {
			//x_rot = x_rot - 4;
			//signbon = -1;
			v = 6.28;
			x_rot = x_rot - signbon * 2;
		}
	//if (v < 3.14) {
		//x_rot = x_rot - 4;
//		signbon = 1;
	//}

	if (x_rot == -8) {
		signbon = -1;
		verbon = false;
		v = 6.28;
		x_rot += 2;
	}

	if (x_rot == 2) {
		signbon = 1;
		verbon = true;
		v = 3.14;
		x_rot -= 2;
	}

	v = v +  2*deltaTimeSeconds * signbon;

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(x_rot, 0.5, 0);
	modelMatrix *= Transform3D::RotateOZ(v);
	modelMatrix *= Transform3D::Translate(-1, 0, 0);

	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(6, 0.5, -1.5);
	modelMatrix *= Transform3D::Translate(new_x, 0, 0);
	//modelMatrix *= Transform3D::Translate(5, 0.5, -1.5);
	modelMatrix *= Transform3D::RotateOY(v);

	new_x = new_x + 1.5 * sign * deltaTimeSeconds;

	if (new_x > 20)
		sign = -1;

	if (new_x < 6)
		sign = +1;

	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(new_x + 6, 0, -1.5);
	modelMatrix *= Transform3D::RotateOY(u);
	modelMatrix *= Transform3D::Translate(4, 0.5, -1.5);
	modelMatrix *= Transform3D::RotateOY(u);
	modelMatrix *= Transform3D::Scale(0.5 * scaleX, 0.5 * scaleY, 0.5 * scaleZ);


	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(new_x + 6, 0, -1.5);
	modelMatrix *= Transform3D::RotateOY(u);
	modelMatrix *= Transform3D::Translate(4, 0, -1.5);
	modelMatrix *= Transform3D::RotateOY(u);
	modelMatrix *= Transform3D::Translate(2, 0.5, -1.5);
	modelMatrix *= Transform3D::RotateOY(u);
	modelMatrix *= Transform3D::Scale(0.25 * scaleX, 0.25 * scaleY, 0.25 * scaleZ);


	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);



}

void Laborator4::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods)
{
	// TODO
	if (window->KeyHold(GLFW_KEY_D)) {
		moved = true;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		movea = true;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		moves = true;
	}

	if (window->KeyHold(GLFW_KEY_W)) {
		movew = true;
	}

	if (window->KeyHold(GLFW_KEY_R)) {
		mover = true;
	}

	if (window->KeyHold(GLFW_KEY_F)) {
		movef = true;
	}

	if (window->KeyHold(GLFW_KEY_1)) {
		scaleup = true;
	}

	if (window->KeyHold(GLFW_KEY_2)) {
		scaledown = true;
	}

	if (window->KeyHold(GLFW_KEY_3)) {
		rotX1 = true;
	}

	if (window->KeyHold(GLFW_KEY_4)) {
		rotX2 = true;
	}

	if (window->KeyHold(GLFW_KEY_5)) {
		rotY1 = true;
	}

	if (window->KeyHold(GLFW_KEY_6)) {
		rotY2 = true;
	}

	if (window->KeyHold(GLFW_KEY_7)) {
		rotZ1 = true;
	}

	if (window->KeyHold(GLFW_KEY_8)) {
		rotZ2 = true;
	}

}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator4::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
