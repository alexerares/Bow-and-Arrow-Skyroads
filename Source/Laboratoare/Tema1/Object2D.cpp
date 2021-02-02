#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {

	std::vector<VertexFormat> vertices4;
	
	int nrtri = 100;

	//vertices4.push_back(VertexFormat(center, glm::vec3(1, 0, 1)));

	for (int i = 0; i <= nrtri; i++) {

		vertices4.push_back(VertexFormat(center + glm::vec3(radius * sin(i * 3.14 / nrtri), radius * cos(i * 3.14 / nrtri), 0), color));

	}

	Mesh* circle = new Mesh(name);

	std::vector<unsigned short> indices4;

	if (!fill) {
		circle->SetDrawMode(GL_LINE_LOOP);
	}

	for (int i = 0; i <= nrtri; i++) {

		//indices4.push_back(0);
		indices4.push_back(i);
		//i++;
		//indices4.push_back(i);
		//i--;

	}

	//indices4.push_back(nrtri);
	//indices4.push_back(1);

	circle->InitFromData(vertices4, indices4);

	return circle;
}

Mesh* Object2D::CreateLine(std::string name, glm::vec3 leftCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftCorner;

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color)
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1 };

	if (!fill) {
		line->SetDrawMode(GL_LINE_LOOP);
	}

	line->InitFromData(verticesline, indicesline);
	return line;
}

Mesh* Object2D::CreateTri(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, 5, 0), color),
		VertexFormat(corner + glm::vec3(20, 0, 0), color),
		VertexFormat(corner - glm::vec3(0, 5, 0), color)
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 0, 2, 3 };

	if (!fill) {
		line->SetDrawMode(GL_LINE_LOOP);
	}

	line->InitFromData(verticesline, indicesline);
	return line;
}

Mesh* Object2D::CreateBaloon(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill) {

	std::vector<VertexFormat> vertices4;

	int nrtri = 100;

	vertices4.push_back(VertexFormat(center, color));

	for (int i = 0; i <= nrtri; i++) {

		vertices4.push_back(VertexFormat(center + glm::vec3(radius * sin(i * 6.28 / nrtri), 1.5 * radius * cos(i * 6.28 / nrtri), 0), color));

	}

	Mesh* balloon = new Mesh(name);

	std::vector<unsigned short> indices4;

	if (!fill) {
		balloon->SetDrawMode(GL_LINE_LOOP);
	}

	for (int i = 0; i <= nrtri; i++) {

		indices4.push_back(0);
		indices4.push_back(i);
		i++;
		indices4.push_back(i);
		i--;

	}


	balloon->InitFromData(vertices4, indices4);

	return balloon;
}

Mesh* Object2D::CreatePolilinie(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(center + glm::vec3(0, -radius * 1.5, 0), color),
		VertexFormat(center + glm::vec3(-10, -radius * 1.5 - 7, 0), color),
		VertexFormat(center + glm::vec3(0, -radius * 1.5 - 14, 0), color),
		VertexFormat(center + glm::vec3(-10, -radius * 1.5 - 21, 0), color),
		VertexFormat(center + glm::vec3(0, -radius * 1.5 - 28, 0), color)
	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indicesline = {0, 1, 2, 3, 4};

	if (!fill) {
		line->SetDrawMode(GL_LINE_STRIP);
	}

	line->InitFromData(verticesline, indicesline);
	return line;
}

Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(center),
		VertexFormat(center + glm::vec3(0, radius, 0), color),
		VertexFormat(center + glm::vec3(-radius, radius, 0), color),
		VertexFormat(center + glm::vec3(-radius, 0, 0), color),
		VertexFormat(center + glm::vec3(-radius, -radius, 0), color),
		VertexFormat(center + glm::vec3(0, -radius, 0), color),
		VertexFormat(center + glm::vec3(radius, -radius, 0), color),
		VertexFormat(center + glm::vec3(radius, 0, 0), color),
		VertexFormat(center + glm::vec3(radius, radius, 0), color)

	};

	Mesh* line = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 8};

	if (!fill) {
		line->SetDrawMode(GL_LINE_LOOP);
	}

	line->InitFromData(verticesline, indicesline);
	return line;
}

Mesh* Object2D::CreatePowerBar(std::string name, glm::vec3 leftCorner, float length, float dim, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftCorner;

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* powerbar = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1 };

	if (!fill) {
		powerbar->SetDrawMode(GL_LINE_LOOP);
	}

	powerbar->InitFromData(verticesline, indicesline);
	return powerbar;
}

Mesh* Object2D::CreateFreezBar(std::string name, glm::vec3 leftCorner, float length, float dim, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftCorner;

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color)
	};

	Mesh* powerbar = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1 };

	if (!fill) {
		powerbar->SetDrawMode(GL_LINE_LOOP);
	}

	powerbar->InitFromData(verticesline, indicesline);
	return powerbar;
}

Mesh* Object2D::CreateScore(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(10, 0, 0), color),
		VertexFormat(corner + glm::vec3(10, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* score = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		score->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	score->InitFromData(vertices, indices);
	return score;
}

Mesh* Object2D::CreateHeart(std::string name, glm::vec3 center, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(center + glm::vec3(0, -20, 0), color),
		VertexFormat(center + glm::vec3(-20, 0, 0), color),
		VertexFormat(center + glm::vec3(-14, 12, 0), color),
		VertexFormat(center + glm::vec3(-10, 12, 0), color),
		VertexFormat(center + glm::vec3(0, 6, 0), color),
		VertexFormat(center + glm::vec3(10, 12, 0), color),
		VertexFormat(center + glm::vec3(14, 12, 0), color),
		VertexFormat(center + glm::vec3(20, 0, 0), color)
	};

	Mesh* heart = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 4, 5, 6, 7, 0 };

	if (!fill) {
		heart->SetDrawMode(GL_LINE_STRIP);
	}

	heart->InitFromData(verticesline, indicesline);
	return heart;
}

Mesh* Object2D::CreateG(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(200, 600, 0), color),//
		VertexFormat(glm::vec3(100, 600, 0), color),//
		VertexFormat(glm::vec3(100, 400, 0), color),//
		VertexFormat(glm::vec3(200, 400, 0), color),//
		VertexFormat(glm::vec3(200, 500, 0), color),//
		VertexFormat(glm::vec3(150, 500, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 4, 5 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateA(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(250, 400, 0), color),//
		VertexFormat(glm::vec3(250, 600, 0), color),//
		VertexFormat(glm::vec3(350, 600, 0), color),//
		VertexFormat(glm::vec3(350, 400, 0), color),//
		VertexFormat(glm::vec3(250, 500, 0), color),//
		VertexFormat(glm::vec3(350, 500, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 5, 4 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateM(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(400, 400, 0), color),//
		VertexFormat(glm::vec3(400, 600, 0), color),//
		VertexFormat(glm::vec3(450, 500, 0), color),//
		VertexFormat(glm::vec3(500, 600, 0), color),//
		VertexFormat(glm::vec3(500, 400, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 4 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateE(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(650, 400, 0), color),//
		VertexFormat(glm::vec3(550, 400, 0), color),//
		VertexFormat(glm::vec3(550, 500, 0), color),//
		VertexFormat(glm::vec3(650, 500, 0), color),//
		VertexFormat(glm::vec3(550, 600, 0), color),
		VertexFormat(glm::vec3(650, 600, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 2, 4, 5 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateO(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(550, 350, 0), color),//
		VertexFormat(glm::vec3(650, 350, 0), color),//
		VertexFormat(glm::vec3(650, 150, 0), color),//
		VertexFormat(glm::vec3(550, 150, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 0 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateV(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(700, 350, 0), color),//
		VertexFormat(glm::vec3(750, 150, 0), color),//
		VertexFormat(glm::vec3(800, 350, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateE2(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(950, 150, 0), color),//
		VertexFormat(glm::vec3(850, 150, 0), color),//
		VertexFormat(glm::vec3(850, 250, 0), color),//
		VertexFormat(glm::vec3(950, 250, 0), color),//
		VertexFormat(glm::vec3(850, 350, 0), color),
		VertexFormat(glm::vec3(950, 350, 0), color)

	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 2, 4, 5 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}

Mesh* Object2D::CreateR(std::string name, glm::vec3 color, bool fill)
{

	std::vector<VertexFormat> verticesline =
	{
		VertexFormat(glm::vec3(1000, 150, 0), color),//
		VertexFormat(glm::vec3(1000, 350, 0), color),//
		VertexFormat(glm::vec3(1100, 350, 0), color),
		VertexFormat(glm::vec3(1100, 250, 0), color),
		VertexFormat(glm::vec3(1000, 250, 0), color),
		VertexFormat(glm::vec3(1100, 150, 0), color)
	};

	Mesh* gameover = new Mesh(name);
	std::vector<unsigned short> indicesline = { 0, 1, 2, 3, 4, 5 };

	if (!fill) {
		gameover->SetDrawMode(GL_LINE_STRIP);
	}

	gameover->InitFromData(verticesline, indicesline);
	return gameover;
}