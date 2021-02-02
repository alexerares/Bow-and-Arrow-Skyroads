#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("archer");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Archer", "Archer.fbx");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(color.x, color.y, color.z, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes["teapot"], glm::vec3(-3, 0.5f, -2));

	RenderMesh(meshes["archer"], glm::vec3(position.x, position.y, position.z), glm::vec3(0.01f));

	RenderMesh(meshes["box"], glm::vec3(rotate.x, rotate.y, rotate.z));

	if(val == 0)
		RenderMesh(meshes["archer"], glm::vec3(4, 0.1f, 1), glm::vec3(0.01f));
	if(val == 1)
		RenderMesh(meshes["box"], glm::vec3(4, 0.5f, 1), glm::vec3(0.5f));
	if (val == 2)
		RenderMesh(meshes["teapot"], glm::vec3(4, 0.5f, 1), glm::vec3(0.5f));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{

	//Nu am stiut daca trebuie sa invarta doar cand apas o tasta asa ca l-am facut sa se invarta mereu
	if (t >= 360)
		t = 0;
	if(rot == 1)
		t = t + deltaTime * viteza;
	rotate.x = 2 + 2 * cos(t);
	rotate.y = 2 + 2 * sin(t);
	// treat continuous update based on input
	if (movew == 1) {
		position.z = position.z + deltaTime * viteza;
	}
	if (moves == 1) {
		position.z = position.z - deltaTime * viteza;
	}

	if (movea == 1) {
		position.x = position.x - deltaTime * viteza;
	}
	if (moved == 1) {
		position.x = position.x + deltaTime * viteza;
	}

	if (moveq == 1) {
		position.y = position.y - deltaTime * viteza;
	}
	if (movee == 1) {
		position.y = position.y + deltaTime * viteza;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		color = glm::vec3(1, 0, 0);
	}

	if (key == GLFW_KEY_K) {
		color = glm::vec3(4, 3, 2);
	}

	if (key == GLFW_KEY_H) {
		if (val == 2)
			val = 0;
		else
			val = val + 1;
	}

	if (key == GLFW_KEY_W)
		movew = 1;

	if (key == GLFW_KEY_S)
		moves = 1;

	if (key == GLFW_KEY_A)
		movea = 1;

	if (key == GLFW_KEY_D)
		moved = 1;

	if (key == GLFW_KEY_Q)
		moveq = 1;

	if (key == GLFW_KEY_E)
		movee = 1;

	if (key == GLFW_KEY_X)
		rot = 1;

};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_W)
		movew = 0;

	if (key == GLFW_KEY_S)
		moves = 0;

	if (key == GLFW_KEY_A)
		movea = 0;

	if (key == GLFW_KEY_D)
		moved = 0;

	if (key == GLFW_KEY_Q)
		moveq = 0;

	if (key == GLFW_KEY_E)
		movee = 0;

	if (key == GLFW_KEY_X)
		rot = 0;
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
