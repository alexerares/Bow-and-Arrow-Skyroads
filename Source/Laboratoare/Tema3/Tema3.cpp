#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::Camera1();
	camera->Set(glm::vec3(4.5, 4, -0.5), glm::vec3(4.5, 2.5, 5), glm::vec3(0, 1, 0));
	//camera->Set(glm::vec3(xsphere, ysphere, zsphere + 0.5), glm::vec3(xsphere, ysphere, 6), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	int i = 0;

	for (int j = 0; j < nrplat; j++) {
		row1.emplace_back(platforme1(1.5 + 3 * j, 1, 7, 0, rand() % 4 + 0, 10));
		for (int i = 1; i <= nrplat; i++) {
			int ddd1 = rand() % 7 + 4;
			row1.emplace_back(platforme1(1.5 + 3 * j, 1, row1[i - 1].posz + row1[i - 1].dim / 2 + (rand() % 4 + 3) + ddd1 / 2, 0, rand() % 4 + 0, ddd1));
		}
		plan.emplace_back(row1);
		row1.clear();
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

	{
		Shader* shader = new Shader("ShaderLab7");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shadersphere = new Shader("ShaderSphere");
		shadersphere->AddShader("Source/Laboratoare/Tema3/Shaders/SphereShader.glsl", GL_VERTEX_SHADER);
		shadersphere->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shadersphere->CreateAndLink();
		shaders[shadersphere->GetName()] = shadersphere;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	renderCameraTarget = false;
	{
		lightPosition = glm::vec3(0, 1, 1);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}

	glm::vec3 corner = glm::vec3(0, 0, 0);

	Mesh* score = Object2D::CreateScore("score", corner, 5,  glm::vec3(1, 1, 1), true);
	AddMeshToList(score);

	Mesh* fuel = Object2D::CreateFuel("fuel", corner, 5, glm::vec3(1, 0, 0), true);
	AddMeshToList(fuel);

	glm::vec3 corner2 = glm::vec3(0, 0, 0);

	Mesh* heart = Object2D::CreateHeart("heart", corner2, glm::vec3(1, 0, 0));
	AddMeshToList(heart);

}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	if (!red && (combustibil > 0) && (micsor > 0)) {
		if (!firstperson)
			camera->Set(glm::vec3(4.5, 4, -0.5), glm::vec3(4.5, 2.5, 5), glm::vec3(0, 1, 0));
		else
			camera->Set(glm::vec3(xsphere, ysphere, zsphere + 0.5), glm::vec3(xsphere, ysphere, 6), glm::vec3(0, 1, 0));

		cout << combustibil << " ";
		combustibil -= 0.2;
		if (combustibil > 900)
			combustibil = 900;
		if (combustibil < 0)
			combustibil = 0;
		//y = y - 2 * deltaTimeSeconds;

		if (count > 0) {

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
				vitplat += deltaTimeSeconds * 2;

			if (moves == 1)
				vitplat -= deltaTimeSeconds * 2;

			if (vitplat < vitmin)
				vitplat = vitmin;

			vitmin += 0.001;

			if (vitplat > 12)
				vitplat = 12;
		}

		if (moved == 1)
			xsphere -= deltaTimeSeconds * 3;
		//modelMatrix *= Transform2D::Translate(tx, ty);

		if (movea == 1)
			xsphere += deltaTimeSeconds * 3;

		if (!explosive) {
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
		}
		if (ysphere < 1.25)
			explosive = true;

		if (explosive)
			micsor -= 0.025;

		if (explosive)
			vitplat = 0;


		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(xsphere, ysphere, zsphere));
			if (!explosive) {
				if (deform || count > 0)
					RenderSimpleMesh(meshes["sphere"], shaders["ShaderSphere"], modelMatrix, glm::vec3(1, 0, 0));
				else
					RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
			}
			else {
				modelMatrix = glm::scale(modelMatrix, glm::vec3(micsor, micsor, micsor));
				RenderSimpleMesh(meshes["sphere"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
			}

		}

		{
			onplat = false;
			deform = false;
			for (int j = 0; j < nrrows; j++)
				for (int i = 0; i <= nrplat; i++) {
					plan[j][i].posz -= vitplat * deltaTimeSeconds;
					glm::mat4 modelMatrix = glm::mat4(1);
					modelMatrix = glm::translate(modelMatrix, glm::vec3(plan[j][i].posx, plan[j][i].posy, plan[j][i].posz));
					modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1, plan[j][i].dim));
					if (plan[j][i].onme)
						RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 1));
					else {
						if (plan[j][i].plat == 0 || plan[j][i].plat == 2 || plan[j][i].plat == 3)
							RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 0, 1));
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 0))
							RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 0));
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 1))
							RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 0));
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 2))
							RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0.5, 0));
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 3))
							RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(0, 1, 0));
					}
					if (CheckCollision(xsphere, ysphere, zsphere, plan[j][i].posx, plan[j][i].posy, plan[j][i].posz, plan[j][i].dim)) {
						onplat = true;
						plan[j][i].onme = true;
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 3)) {
							combustibil += 1;
							deform = true;
						}
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 1)) {
							combustibil -= 0.6;
							deform = true;
						}
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 2)) {
							count = 100;
							deform = true;
						}
						if ((plan[j][i].plat == 1) && (plan[j][i].tipplat == 0)) {
							red = true;
						}
					}

					if (plan[j][i].posz < -plan[j][i].dim / 2) {
						int ddd1 = rand() % 7 + 4;
						if (i == 0)
							plan[j][i].posz = plan[j][nrplat].posz + plan[j][nrplat].dim / 2 + (rand() % 4 + 3) + ddd1 / 2;
						else
							plan[j][i].posz = plan[j][i - 1].posz + plan[j][i - 1].dim / 2 + (rand() % 4 + 3) + ddd1 / 2;

						plan[j][i].onme = false;
						plan[j][i].plat = rand() % 4 + 0;
						plan[j][i].tipplat = rand() % 4 + 0;
						plan[j][i].dim = ddd1;
					}
				}
		}

		/*{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5, 5, 15));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(combustibil / 200, 0.3, 0.01));
			RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 0, 1));

		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(4.5, 5, 15.0001));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(5, 0.3, 0.01));
			RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], modelMatrix, glm::vec3(1, 1, 1));
		}*/
		{
			glm::mat3 modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(1.5, 2.1);
			modelMatrix *= Transform2D::Scale(combustibil / 300, 1);
			// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D


			RenderMesh2D(meshes["fuel"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(1.5, 2.1);
			modelMatrix *= Transform2D::Scale(3, 1);
			// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D


			RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(100, 100, 100));
			RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
		}

		{
			glm::mat3 modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(2, 2.1);
			modelMatrix *= Transform2D::Scale(0.01, 0.01);
			RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(2, 1.8);
			modelMatrix *= Transform2D::Scale(0.01, 0.01);
			RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(2, 1.5);
			modelMatrix *= Transform2D::Scale(0.01, 0.01);
			RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
		}

	}
}

void Tema3::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema3::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
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
	/*glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
	*/
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();

	}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_N))
		{
			fov += 5 * deltaTime * cameraSpeed;

			if (perspectiveproj)
			{
				projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
			}
		}

		if (window->KeyHold(GLFW_KEY_M))
		{
			fov -= 5 * deltaTime * cameraSpeed;

			if (perspectiveproj)
			{
				projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
			}
		}

		if (window->KeyHold(GLFW_KEY_K))
		{
			bottom -= 5 * deltaTime;
			top += 5 * deltaTime;

			if (!perspectiveproj)
			{
				projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
			}
		}

		if (window->KeyHold(GLFW_KEY_L))
		{
			bottom += 5 * deltaTime;
			top -= 5 * deltaTime;

			if (!perspectiveproj)
			{
				projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
			}
		}
	}
}

void Tema3::OnKeyPress(int key, int mods)
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

		if (key == GLFW_KEY_C) {
			if (firstperson)
				firstperson = false;
			else
				firstperson = true;
		}

	}

	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_O)
	{
		perspectiveproj = false;
		projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
	}

	if (key == GLFW_KEY_P)
	{
		perspectiveproj = true;
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
	}

}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (!(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))) {
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
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}

	}
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}

bool Tema3::CheckCollision(float Centerx, float Centery, float Centerz, float Boxx, float Boxy, float Boxz, int dim)
{

	float x = max((Boxx - 0.5), min(Centerx, Boxx + 0.5));
	float y = max((Boxy - 0.05), min(Centery, (Boxy + 0.05)));
	//float y = 0;
	float z = max((Boxz - dim/2), min(Centerz, (Boxz + dim/2)));

	float dist = (x - Centerx) * (x - Centerx) +
		(y - Centery) * (y - Centery) +
		(z - Centerz) * (z - Centerz);

	if (dist < 0.25)
		return true;

	return false;
}