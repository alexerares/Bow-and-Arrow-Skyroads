#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{


	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	for (int i = 0; i <= 4; i++) {
		row1.emplace_back(platforme(1.5, 1, (5 * (2 * i + 1) + 3 * i), rand() % 4 + 0, rand() % 4 + 0));
		row2.emplace_back(platforme(4.5, 1, (5 * (2 * i + 1) + 3 * i), rand() % 4 + 0, rand() % 4 + 0));
		row3.emplace_back(platforme(7.5, 1, (5 * (2 * i + 1) + 3 * i), rand() % 4 + 0, rand() % 4 + 0));

	}



	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab7");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 1, 1);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Tema2::Update(float deltaTimeSeconds)
{
	cout << combustibil << " ";
	combustibil -= 0.2;
	if (combustibil > 1000)
		combustibil = 1000;
	if (combustibil < 0)
		combustibil = 0;
		//y = y - 2 * deltaTimeSeconds;

	if(count > 0 ){
	
		if (count == 100) 
			oldvit = vitplat;

		vitplat = vitmax;
		count -= 0.5;
		maxvit = true;

	}
	else {
		
		if (maxvit) {
			vitplat = oldvit;
			maxvit = false;
		}

		if (movew == 1)
			vitplat += deltaTimeSeconds * 1;

		if (moves == 1)
			vitplat -= deltaTimeSeconds * 1;

		if (vitplat < 0)
			vitplat = 0;

		if (vitplat > 10)
			vitplat = 10;
	}

	if (moved == 1)
		xsphere -= deltaTimeSeconds * 2;
	//modelMatrix *= Transform2D::Translate(tx, ty);

	if (movea == 1)
		xsphere += deltaTimeSeconds * 2;

	if (movee == 1)
		ysphere += deltaTimeSeconds * 2;
	//modelMatrix *= Transform2D::Translate(tx, ty);

	if (moveq == 1)
		ysphere -= deltaTimeSeconds * 2;

	if (!rise && !onplat)
		ysphere -= 4 * deltaTimeSeconds;

	if (space && onplat)
		rise = true;

	if (rise)
		ysphere += 4 * deltaTimeSeconds;

	if (ysphere > 4) {
		space = false;
		rise = false;
	}

	if (ysphere < 0) {
		//space = false;
		//onplat = false;
		ysphere = 4;
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(xsphere, ysphere, zsphere));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
	}

	{
		onplat = false;
		for (int i = 0; i <= 4; i++) {
			row1[i].posz -= vitplat * deltaTimeSeconds;
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(row1[i].posx, row1[i].posy, row1[i].posz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 10));
			if(row1[i].onme)
				RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 1));
			else {
				if(row1[i].plat == 0 || row1[i].plat == 2 || row1[i].plat == 3)
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 1));
				if((row1[i].plat == 1) && (row1[i].tipplat == 0))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
				if ((row1[i].plat == 1) && (row1[i].tipplat == 1))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 0));
				if ((row1[i].plat == 1) && (row1[i].tipplat == 2))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0.5, 0));
				if ((row1[i].plat == 1) && (row1[i].tipplat == 3))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 1, 0));
			}
			if (CheckCollision(xsphere, ysphere, zsphere, row1[i].posx, row1[i].posy, row1[i].posz)) {
				onplat = true;
				row1[i].onme = true;
				if ((row1[i].plat == 1) && (row1[i].tipplat == 3))
					combustibil += 0.5;
				if ((row1[i].plat == 1) && (row1[i].tipplat == 1))
					combustibil -= 0.3;
				if ((row1[i].plat == 1) && (row1[i].tipplat == 2))
					count = 100;
			}	

			if (row1[i].posz < -8) {
				row1[i].posz = 57;
				row1[i].onme = false;
				row1[i].plat = rand() % 4 + 0;
				row1[i].tipplat = rand() % 4 + 0;
			}
		}
	}

	{
		for (int i = 0; i <= 4; i++) {
			row2[i].posz -= vitplat * deltaTimeSeconds;

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(row2[i].posx, row2[i].posy, row2[i].posz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 10));
			if (row2[i].onme)
				RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 1));
			else {
				if (row2[i].plat == 0 || row2[i].plat == 2 || row2[i].plat == 3)
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 1));
				if ((row2[i].plat == 1) && (row2[i].tipplat == 0))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
				if ((row2[i].plat == 1) && (row2[i].tipplat == 1))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 0));
				if ((row2[i].plat == 1) && (row2[i].tipplat == 2))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0.5, 0));
				if ((row2[i].plat == 1) && (row2[i].tipplat == 3))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 1, 0));
			}
			if (CheckCollision(xsphere, ysphere, zsphere, row2[i].posx, row2[i].posy, row2[i].posz)) {
				onplat = true;
				row2[i].onme = true;
				if ((row2[i].plat == 1) && (row2[i].tipplat == 3))
					combustibil += 0.5;
				if ((row2[i].plat == 1) && (row2[i].tipplat == 1))
					combustibil -= 0.3;
				if ((row2[i].plat == 1) && (row2[i].tipplat == 2))
					count = 100;
			}

			if (row2[i].posz < -8) {
				row2[i].posz = 57;
				row2[i].onme = false;
				row2[i].plat = rand() % 4 + 0;
				row2[i].tipplat = rand() % 4 + 0;
			}
		}
	}

	{
		for (int i = 0; i <= 4; i++) {
			row3[i].posz -= vitplat * deltaTimeSeconds;

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(row3[i].posx, row3[i].posy, row3[i].posz));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, 10));
			if (row3[i].onme)
				RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 1));
			else {
				if (row3[i].plat == 0 || row3[i].plat == 2 || row3[i].plat == 3)
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 1));
				if ((row3[i].plat == 1) && (row3[i].tipplat == 0))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
				if ((row3[i].plat == 1) && (row3[i].tipplat == 1))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 0));
				if ((row3[i].plat == 1) && (row3[i].tipplat == 2))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0.5, 0));
				if ((row3[i].plat == 1) && (row3[i].tipplat == 3))
					RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 1, 0));
			}
			if (CheckCollision(xsphere, ysphere, zsphere, row3[i].posx, row3[i].posy, row3[i].posz)) {
				onplat = true;
				row3[i].onme = true;
				if ((row3[i].plat == 1) && (row3[i].tipplat == 3))
					combustibil += 0.5;
				if ((row3[i].plat == 1) && (row3[i].tipplat == 1))
					combustibil -= 0.3;
				if ((row3[i].plat == 1) && (row3[i].tipplat == 2))
					count = 100;
			}

			if (row3[i].posz < -8) {
				row3[i].posz = 57;
				row3[i].onme = false;
				row3[i].plat = rand() % 4 + 0;
				row3[i].tipplat = rand() % 4 + 0;
			}
		}
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5, 5, 5));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(combustibil/200, 0.3, 0.01));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 1));

	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5, 5, 5.0001));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 0.3, 0.01));
		RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 1));
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	GLint locLightPos = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(locLightPos, 1, glm::value_ptr(lightPosition));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	GLint locEyePos = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(locEyePos, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	GLint locMaterial = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(locMaterial, materialShininess);

	GLint locMaterialKd = glGetUniformLocation(shader->program, "material_kd");  // diffuse light
	glUniform1f(locMaterialKd, materialKd);

	GLint locMaterialKs = glGetUniformLocation(shader->program, "material_ks");  // specular light
	glUniform1f(locMaterialKs, materialKs);

	GLint locObject = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(locObject, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

		// Control light position using on W, A, S, D, E, Q
		if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
		if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (!(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
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

		if (key == GLFW_KEY_SPACE)
			space = 1;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
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
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

bool Tema2::CheckCollision(float Centerx, float Centery, float Centerz, float Boxx, float Boxy, float Boxz)
{

	float x = max((Boxx - 1/2), min(Centerx, Boxx + 1/2));
	float y = max((Boxy - 1/20), min(Centery, (Boxy + 1/20)));
	//float y = 0;
	float z = max((Boxz - 5), min(Centerz, (Boxz + 5)));

	float dist = (x - Centerx) * (x - Centerx) +
				 (y - Centery) * (y - Centery) +
				 (z - Centerz) * (z - Centerz);

	if (dist < 0.25)
		return true;

	return false;
}
