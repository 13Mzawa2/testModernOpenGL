#pragma once

#include "OpenGLHeader.h"

class Shader
{
private:
	GLuint vertexShader, fragmentShader;
public:
	GLuint program;			//	�V�F�[�_�v���O����
	Shader();
	~Shader();
	void readShaderCompile(GLuint shader, const char *file);	//	.shader�̃R���p�C��
	void link(GLuint prog);		//	�R���p�C������shader�������N����
	//	������
	//	�t���O�����g�V�F�[�_�[�̗L���ŕ�����
	void initGLSL(const char *vertexFile);
	void initGLSL(const char *vertexFile, const char *fragmentFile);


};

