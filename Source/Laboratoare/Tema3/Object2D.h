#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
	Mesh* CreateLine(std::string name, glm::vec3 leftCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateTri(std::string name, glm::vec3 leftCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateBaloon(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
	Mesh* CreatePolilinie(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
	Mesh* CreateShuriken(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
	Mesh* CreatePowerBar(std::string name, glm::vec3 leftCorner, float length, float dim, glm::vec3 color, bool fill = false);
	Mesh* CreateFreezBar(std::string name, glm::vec3 leftCorner, float length, float dim, glm::vec3 color, bool fill = false);
	Mesh* CreateScore(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateFuel(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
	Mesh* CreateHeart(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color, bool fill = false);
	Mesh* CreateG(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateA(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateM(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateE(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateO(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateV(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateE2(std::string name, glm::vec3 color, bool fill = false);
	Mesh* CreateR(std::string name, glm::vec3 color, bool fill = false);
}
