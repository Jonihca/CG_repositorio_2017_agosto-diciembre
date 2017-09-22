#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GL/freeglut.h>

#include "InputFile.h"

GLuint vao;
GLuint shaderProgram;

void Initialize() {

	std::vector<glm::vec2> positions;

	std::vector<glm::vec3> colors;

	float r = 1.0;
	float X = 1.0;
	float Y = 0.0;
	float contador = 0.0f;

	positions.push_back(glm::vec2(0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

	while (contador <= 360.0f) {

		float angulo = glm::radians(contador);
		float x = r*(glm::cos(angulo));
		float y = r*(glm::sin(angulo));

		positions.push_back(glm::vec2(x, y));
		colors.push_back(glm::vec3(x, y, 0.0f));


		contador = contador + 1.0f;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint positionsVBO;
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * positions.size(), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0),

		glBindVertexArray(0);

	InputFile ifile;
	ifile.Read("DiscardCenter.vert");
	std::string vertexSource = ifile.GetContents();
	GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	const GLchar * vertexSource_c = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShaderHandle, 1, &vertexSource_c, nullptr);
	glCompileShader(vertexShaderHandle);

	ifile.Read("DiscardCenter.frag");
	std::string fragmentSource = ifile.GetContents();
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderHandle);
	glAttachShader(shaderProgram, fragmentShaderHandle);
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	glLinkProgram(shaderProgram);
}

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
	glBindVertexArray(0);

	glUseProgram(0);

	glutSwapBuffers();
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
	
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello World GL");

	glutDisplayFunc(GameLoop);

	glewInit();

	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	std::cout << glGetString(GL_VERSION) << std::endl;

	Initialize();

	glutMainLoop();

	return 0;
}
