#pragma once

#include "OpenGLHeader.h"

class Shader
{
protected:
	GLuint vertexShader, fragmentShader;
	void readShaderCompile(GLuint shader, const char *file);	//	.shader�̃R���p�C��
	void link(GLuint prog);		//	�R���p�C������shader�������N����
public:
	GLuint program;			//	�V�F�[�_�v���O����
	Shader();
	~Shader();
	//	������
	//	�t���O�����g�V�F�[�_�[�̗L���ŕ�����
	void loadGLSL(const char *vertexFile);
	void loadGLSL(const char *vertexFile, const char *fragmentFile);
};

