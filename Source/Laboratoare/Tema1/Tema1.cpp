#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos);

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();

	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 50;
	float lenghtline = 55;
	float shur = 25;
	float pb = 25;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;

	for (int z = 0; z < nrshur; z++) {
		shurtip.push_back(rand() % 4 + 0);
		shurposx.push_back(rand() % 1800 + 1400);
		shurposy.push_back(rand() % 500 + 100);
	}

	for (int z = 0; z < nrbal; z++) {
		baltip.push_back(rand() % 3 + 0);
		balposx.push_back(rand() % 1000 + 200);
		balposy.push_back(rand() % 400 + -500);
		balexp.push_back(1.5);
		beginexp.push_back(false);
		pop.push_back(false);
		speedball.push_back(rand() % 250 + 100);
	}

	Mesh* square1 = Object2D::CreateSquare("square1", corner, 10, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 1));
	AddMeshToList(square4);

	Mesh* circle = Object2D::CreateCircle("circle", corner, squareSide, glm::vec3(1, 0, 1));
	AddMeshToList(circle);

	Mesh* line = Object2D::CreateLine("line", corner, lenghtline, glm::vec3(0, 0, 1));
	AddMeshToList(line);

	Mesh* tri = Object2D::CreateTri("tri", corner, lenghtline, glm::vec3(0, 0, 1), true);
	AddMeshToList(tri);

	Mesh* balloon = Object2D::CreateBaloon("balloon", corner, balrad, glm::vec3(1, 0, 0), true);
	AddMeshToList(balloon);

	Mesh* polilin = Object2D::CreatePolilinie("polilin", corner, balrad, glm::vec3(1, 0, 0), false);
	AddMeshToList(polilin);

	Mesh* balloony = Object2D::CreateBaloon("balloony", corner, balrad, glm::vec3(1, 1, 0), true);
	AddMeshToList(balloony);

	Mesh* poliliny = Object2D::CreatePolilinie("poliliny", corner, balrad, glm::vec3(1, 1, 0), false);
	AddMeshToList(poliliny);

	Mesh* shuriken = Object2D::CreateShuriken("shuriken", corner, shur, glm::vec3(1, 1, 1), true);
	AddMeshToList(shuriken);

	Mesh* shurikenalbastru = Object2D::CreateShuriken("shurikenalbastru", corner, shur, glm::vec3(0, 0, 1), true);
	AddMeshToList(shurikenalbastru);

	Mesh* shurikenverde = Object2D::CreateShuriken("shurikenverde", corner, shur, glm::vec3(0, 1, 0), true);
	AddMeshToList(shurikenverde);

	Mesh* shurikenrosu = Object2D::CreateShuriken("shurikenrosu", corner, shur, glm::vec3(1, 0, 0), true);
	AddMeshToList(shurikenrosu);

	Mesh* powerbar = Object2D::CreatePowerBar("powerbar", corner, pb, speedarr, glm::vec3(1, 1, 1));
	AddMeshToList(powerbar);

	Mesh* freezbar = Object2D::CreateFreezBar("freezbar", corner, pb, freeztime, glm::vec3(0, 0, 1));
	AddMeshToList(freezbar);

	Mesh* score = Object2D::CreatePowerBar("score", corner, 5, speedarr, glm::vec3(1, 0, 0));
	AddMeshToList(score);

	Mesh* heart = Object2D::CreateHeart("heart", corner,  glm::vec3(1, 0, 0));
	AddMeshToList(heart);

	Mesh* g = Object2D::CreateG("g", glm::vec3(1, 0, 0));
	AddMeshToList(g);

	Mesh* a = Object2D::CreateA("a", glm::vec3(1, 0, 0));
	AddMeshToList(a);

	Mesh* m = Object2D::CreateM("m", glm::vec3(1, 0, 0));
	AddMeshToList(m);

	Mesh* e = Object2D::CreateE("e", glm::vec3(1, 0, 0));
	AddMeshToList(e);

	Mesh* o = Object2D::CreateO("o", glm::vec3(1, 0, 0));
	AddMeshToList(o);

	Mesh* v = Object2D::CreateV("v", glm::vec3(1, 0, 0));
	AddMeshToList(v);

	Mesh* e2 = Object2D::CreateE2("e2", glm::vec3(1, 0, 0));
	AddMeshToList(e2);

	Mesh* r = Object2D::CreateR("r", glm::vec3(1, 0, 0));
	AddMeshToList(r);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	if (lives > 0) {
		// TODO: update steps for translation, rotation, scale, in order to create animations
		{
			
			if (freezsagtime > 0) {
				freezsag = true;
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(tx-5, ty-5);
				RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
			}

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(tx, ty);
			modelMatrix *= Transform2D::Rotate(rotarc);
			modelMatrix *= Transform2D::Translate(0, 0);
			// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
			//modelMatrix *= Transform2D::Rotate(rotarc);

			//rotarc = atan((350 - cursory -dif) / (cursorx - tx));
			rotarc = atan((350 - cursory - dif) / (cursorx - tx));

			if (freeztime > 0)
				freez = true;

			if (freeztime <= 0)
				freez = false;

			if (freezsagtime <= 0) 
				freezsag = false;

			freeztime -= 1;
			freezsagtime -= 1;

			if (!freez) {
				if (movew == 1)
					if (ty < 600) {
						ty += deltaTimeSeconds * 200;
						dif += deltaTimeSeconds * 200;
					}
				//modelMatrix *= Transform2D::Translate(tx, ty);

				if (moves == 1)
					if (ty > 50) {
						ty -= deltaTimeSeconds * 200;
						dif -= deltaTimeSeconds * 200;
					}
			}


			RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
		}

		{

			if (freez) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(tx, ty-60);
				modelMatrix *= Transform2D::Scale(freeztime/20, 1);
				RenderMesh2D(meshes["freezbar"], shaders["VertexColor"], modelMatrix);
			}

		}

		{
			modelMatrix = glm::mat3(1);

			/*if (addspeed) {
				speedarr += 0.1;
				if (speedarr > 10)
					speedarr = 10;
			}*/

			if (!movearrow) {
				modelMatrix *= Transform2D::Translate(tx, ty);
				modelMatrix *= Transform2D::Rotate(rotarc);
				modelMatrix *= Transform2D::Translate(0, 0);
				lastx = tx;
				lasty = ty;
				lastcurx = cursorx;
				lastcury = cursory;
				lastrot = rotarc;
				lastdiff = dif;
			}

			if (movearrow) {
				//arrowmovex += (lastcurx - lastx) * deltaTimeSeconds;
				//arrowmovey += (350 - lastcury - lastdiff) * deltaTimeSeconds;
				if (lastrot > 0) {
					//arrowmovex += (10 / sin(lastrot)) * deltaTimeSeconds * speedarr;
					//arrowmovey += (10 / cos(lastrot)) * deltaTimeSeconds * speedarr;
					arrowmovex += cos(lastrot) * deltaTimeSeconds * speedarr;
					arrowmovey += sin(lastrot) * deltaTimeSeconds * speedarr;
				}

				if (lastrot < 0) {
					//arrowmovex -= (10 / sin(lastrot)) * deltaTimeSeconds * speedarr;
					//arrowmovey -= (10 / cos(lastrot)) * deltaTimeSeconds * speedarr;
					arrowmovex += cos(lastrot) * deltaTimeSeconds * speedarr;
					arrowmovey += sin(lastrot) * deltaTimeSeconds * speedarr;
				}
				modelMatrix *= Transform2D::Translate(lastx + arrowmovex, lasty + arrowmovey);
				modelMatrix *= Transform2D::Rotate(lastrot);
				modelMatrix *= Transform2D::Translate(0, 0);

				if ((lastx + arrowmovex) > 1300 || (lasty + arrowmovey) < 0 || (arrowmovey + lasty) > 700) {
					movearrow = false;
					arrowmovex = 0;
					arrowmovey = 0;
					speedarr = 300;
				}
			}

			RenderMesh2D(meshes["line"], shaders["VertexColor"], modelMatrix);
		}

		{
			modelMatrix = glm::mat3(1);

			if (!movearrow) {
				modelMatrix *= Transform2D::Translate(tx, ty);
				modelMatrix *= Transform2D::Rotate(rotarc);
				modelMatrix *= Transform2D::Translate(55, 0);
			}

			if (movearrow) {
				modelMatrix *= Transform2D::Translate(lastx + arrowmovex, lasty + arrowmovey);
				modelMatrix *= Transform2D::Rotate(lastrot);
				modelMatrix *= Transform2D::Translate(55, 0);


			}

			//modelMatrix *= Transform2D::Translate(tx , ty);
			// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
			//modelMatrix *= Transform2D::Rotate(rotarc);
			//modelMatrix *= Transform2D::Translate(55, 0);

			RenderMesh2D(meshes["tri"], shaders["VertexColor"], modelMatrix);
		}

		{
			for (int z = 0; z < nrbal; z++) {

				if (scoredim < 0)
					scoredim = 0;

				if (balexp[z] < 1.5)
					balexp[z] += 1.5 * deltaTimeSeconds;
				else
					beginexp[z] = false;

				if (balexp[z] >= 1.5 && pop[z]) {
					balposy[z] = rand() % 250 + -300;
					balposx[z] = rand() % 1000 + 200;
					pop[z] = false;
					speedball[z] = rand() % 250 + 100;
					baltip[z] = rand() % 3 + 0;
				}


				modelMatrix = glm::mat3(1);

				balposy[z] += deltaTimeSeconds * speedball[z];
				if (balposy[z] > 1000) {
					balposy[z] = rand() % 250 + -300;
					balposx[z] = rand() % 1000 + 200;
					pop[z] = false;
					speedball[z] = rand() % 250 + 100;
					baltip[z] = rand() % 3 + 0;
				}

				if (!CheckOval(lastx + arrowmovex + 75 * cos(lastrot), lasty + arrowmovey + 75 * sin(lastrot), balposx[z], balposy[z], 25, 38)) {
					modelMatrix *= Transform2D::Translate(balposx[z], balposy[z]);
					if (beginexp[z])
						modelMatrix *= Transform2D::Scale(balexp[z], 1);
					if(baltip[z] == 0 || baltip[z] == 1)
						RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);
					if (baltip[z] == 2)
						RenderMesh2D(meshes["balloony"], shaders["VertexColor"], modelMatrix);
				}
				else{
					if ((baltip[z] == 0 || baltip[z] == 1) && !pop[z])
						scoredim += 100 * deltaTimeSeconds;
					if (baltip[z] == 2 && !pop[z]) {
						scoredim -= 50 * deltaTimeSeconds;
						if (scoredim < 0)
							scoredim = 0;
					}
					if (!pop[z])
						cout << "Scrore:" << scoredim << "\n";
					beginexp[z] = true;
					pop[z] = true;
					balexp[z] = 1;
					modelMatrix *= Transform2D::Translate(balposx[z], balposy[z]);
					modelMatrix *= Transform2D::Scale(balexp[z], 1);
					if (baltip[z] == 0 || baltip[z] == 1)
						RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);
					if (baltip[z] == 2)
						RenderMesh2D(meshes["balloony"], shaders["VertexColor"], modelMatrix);
				}

			}
		}

		{

			for (int z = 0; z < nrbal; z++) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(balposx[z], balposy[z]);
				if (baltip[z] == 0 || baltip[z] == 1)
					RenderMesh2D(meshes["polilin"], shaders["VertexColor"], modelMatrix);
				if (baltip[z] == 2)
					RenderMesh2D(meshes["poliliny"], shaders["VertexColor"], modelMatrix);
			}

		}

		{

		shurrot = shurrot + 3 * deltaTimeSeconds;
		if (shurrot > 360)
			shurrot = 0;

		speedshur += 0.025;

		if ((verspeedshur - speedshur) < 0) {
			nrshur++;
			shurtip.push_back(rand() % 4 + 0);
			shurposx.push_back(rand() % 1800 + 1400);
			shurposy.push_back(rand() % 500 + 100);
			verspeedshur += 100;
		}

		for (int z = 0; z < nrshur; z++) {
			if(shurtip[z] == 0)
				shurposx[z] -= deltaTimeSeconds * 1.5 * speedshur;
			else
				shurposx[z] -= deltaTimeSeconds * speedshur;

			if (shurposx[z] < -50) {
				shurposx[z] = rand() % 800 + 1400;
				shurposy[z] = rand() % 550 + 50;
			}
		}

		for (int z = 0; z < nrshur; z++) {

			if (!CheckCollision(lastx + arrowmovex + 75 * cos(lastrot), lasty + arrowmovey + 75 * sin(lastrot), shurposx[z], shurposy[z], 36)) {
				modelMatrix = glm::mat3(1);
				
				modelMatrix *= Transform2D::Translate(shurposx[z], shurposy[z]);

				modelMatrix *= Transform2D::Rotate(shurrot);

				modelMatrix *= Transform2D::Translate(0, 0);

				if(shurtip[z] == 0)
					RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

				if (shurtip[z] == 1)
					RenderMesh2D(meshes["shurikenalbastru"], shaders["VertexColor"], modelMatrix);

				if (shurtip[z] == 2)
					RenderMesh2D(meshes["shurikenverde"], shaders["VertexColor"], modelMatrix);

				if (shurtip[z] == 3)
					RenderMesh2D(meshes["shurikenrosu"], shaders["VertexColor"], modelMatrix);
			}
			else if (movearrow) {
				shurposx[z] = rand() % 800 + 1400;
				shurposy[z] = rand() % 550 + 50;
				shurtip[z] = rand() % 4 + 0;
				scoredim += 100 * deltaTimeSeconds;
				movearrow = false;
				arrowmovex = 0;
				arrowmovey = 0;
				speedarr = 300;
				cout << "Scrore:" << scoredim << "\n";
			}

			if (CheckCollisionCircle(tx, ty, 50, shurposx[z], shurposy[z], 35.355)) {
				if (shurtip[z] == 1)
					freeztime = 100;
				if (shurtip[z] == 2)
					lives--;
				if (shurtip[z] == 3) {
					freezsagtime = 100;
					speednew = 300;
				}


				shurposx[z] = rand() % 800 + 1400;
				shurposy[z] = rand() % 550 + 50;
				shurtip[z] = rand() % 4 + 0;
				lives--;
			}
		}

		}

		{
			modelMatrix = glm::mat3(1);
			//modelMatrix *= Transform2D::Translate(100, 150);
			// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
			if(!freezsag)
				if (!movearrow) {
					if (addspeed) {
						speednew += 500* deltaTimeSeconds;
						if (speednew > 800)
							speednew = 800;
					}
				}
			if (!addspeed && verspeed == 0) {
				speedarr = speednew;
				speednew = 300;
				verspeed = 1;
			}
			if (freezsag)
				speednew = 300;

			
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(20, 100);
			modelMatrix *= Transform2D::Scale(1, (speednew - 300)/50);
			RenderMesh2D(meshes["powerbar"], shaders["VertexColor"], modelMatrix);
			

			
		}

		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(1250, 300);
			modelMatrix *= Transform2D::Scale(1, scoredim);
			modelMatrix *= Transform2D::Translate(-5, -2.5);
			// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D


			RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
		}

		{
			if (lives > 0) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(25, 700);
				RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
			}

			if (lives > 1) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(75, 700);
				RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
			}

			if (lives > 2) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(125, 700);
				RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
			}

		}
	}else {
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["g"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["a"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["m"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["e"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["o"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["v"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["e2"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["r"], shaders["VertexColor"], modelMatrix);

		//cout << nrshur << " ";

	}

}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_W)
		movew = 1;

	if (key == GLFW_KEY_S)
		moves = 1;
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_W)
		movew = 0;

	if (key == GLFW_KEY_S)
		moves = 0;
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	cursory = mouseY - 15;
	cursorx = mouseX - 5;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (!freezsag)
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !movearrow) {
		addspeed = true;
		lockspeed = false;
		verspeed = 0;
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	if(!freezsag)
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
		movearrow = true;
		addspeed = false;
		lockspeed = true;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

bool Tema1::CheckCollision(float Lx1, float Ly1, float Lx2, float Ly2, float R)
{
	if (((Lx1 - Lx2) * (Lx1 - Lx2) + (Ly1 - Ly2) * (Ly1 - Ly2)) < (R * R))
		return true;

	return false;
}

bool Tema1::CheckOval(float Lx1, float Ly1, float Lx2, float Ly2, float R1, float R2)
{
	if ((((Lx1 - Lx2) * (Lx1 - Lx2))/(R1 * R1) + ((Ly1 - Ly2) * (Ly1 - Ly2)) / (R2 * R2)) <= 1)
		return true;

	return false;
}

bool Tema1::CheckCollisionCircle(float Lx1, float Ly1, float R1, float Lx2, float Ly2, float R2)
{
	if (((Lx1 - Lx2) * (Lx1 - Lx2) + (Ly1 - Ly2) * (Ly1 - Ly2)) <= ((R1 + R2) * (R1 + R2)))
		return true;

	return false;
}

static void cursorPositionCallBack( GLFWwindow *window, double xpos, double ypos){

	cout << xpos << " : " << ypos << endl;

}

