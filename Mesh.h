#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh 
{
public:
	Mesh();
	~Mesh();

	void SetPositionAttribute(std::vector<glm::vec2> positions, GLenum usage, GLuint locationIndex);
	void SetPositionAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(std::vector<glm::vec3> positions, GLenum usage, GLuint locationIndex);
	void SetColorAttribute(std::vector<glm::vec4> positions, GLenum usage, GLuint locationIndex);

	void Draw(GLenum primitive);

	void CreateMesh(GLint vertexCount);

private:
	void SetAttributeData(GLuint& buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components);
	GLuint _vertexArrayObject = 0;
	GLuint _positionsVertexBufferObject = 0;
	GLuint _colorsVertexBufferObject = 0;
	GLint _vertexCount = 0;

};