//	GLEW, GLFW, GLM�̃C���N���[�h�w�b�_
//	GLEW : OpenGL1.1�ȍ~�̋@�\���g����悤�ɂ���
//	GLFW : GLUT�ɑ���OpenGL�\�����C���[
//	GLM  : ���W�ϊ����̃N���X���

#pragma once


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

#include <stdio.h>
#include <stdlib.h>

#include <GL\glew.h>

#include <GL/glfw3.h>	

#include <glm/glm.hpp>						//	��{�I�ȉ��Z
#include <glm/gtc/matrix_transform.hpp>		//	glm::perspective�Ȃ�
#include <glm/gtx/transform.hpp>			//	glm::translate�Ȃ�

using namespace glm;