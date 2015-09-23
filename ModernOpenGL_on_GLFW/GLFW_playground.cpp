#include <iostream>
#include <opencv2\opencv.hpp>
#include "OpenGLHeader.h"
#include "Shader.h"
#include "objloader.hpp"

using namespace cv;

GLFWwindow	*mainWindow, *subWindow;		//	�}���`�E�B���h�E
Shader		shader;						//	�V�F�[�_�[�N���X

int main(void)
{

	//	GLFW�̏�����
	if (glfwInit() != GL_TRUE)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return EXIT_FAILURE;
	}
	//	Window�ݒ�
	glfwWindowHint(GLFW_SAMPLES, 4);								//	4x �A���`�G�C���A�X
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						//	���T�C�Y�s��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					//	OpenGL�o�[�W����3.3�𗘗p
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					//	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//	�Â�OpenGL���g��Ȃ�

	// Main Window�̗p��
	mainWindow = glfwCreateWindow(1024, 768, "Main Window", NULL, NULL);
	if (mainWindow == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	//// Sub Window�̗p��
	//subWindow = glfwCreateWindow(1024, 768, "Sub Window", NULL, NULL);
	//if (subWindow == NULL){
	//	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
	//	glfwTerminate();
	//	return EXIT_FAILURE;
	//}
	glfwMakeContextCurrent(mainWindow);				//	main window���J�����g�ɂ���

	// Initialize GLEW
	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_FAILURE;
	}

	glClearColor(0.8, 0.8, 0.6, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LESS);				//	�J�����ɋ߂��ʂ��������_�����O����

	//	�L�[���͂��󂯕t����悤�ɂ���
	glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);
	//	�v���O���}�u���V�F�[�_�����[�h
	shader.loadGLSL("Vertex.glsl", "Fragment.glsl");
	//	.obj�t�@�C����ǂݍ��݂܂��B
	Object obj;
	//bool res = loadOBJ("model/drop_modified_x004.obj", obj.vertices, obj.uvs, obj.normals);
	bool res = loadOBJ("model/drop/drop_modified_x004.obj", obj);
	//	�e�N�X�`���摜��ǂݍ���
	Mat texImg = imread("model/drop/textures/txt_001_diff.bmp");
	flip(texImg, texImg, 0);
	//	�V���ɍ��ꂽ�e�N�X�`����"�o�C���h"���܂��B�܂肱�������̃e�N�X�`���֐��͂��̃e�N�X�`����ύX���܂��B
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//	OpenGL�ɉ摜��n���܂��B
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texImg.cols, texImg.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, texImg.data);
	//	�e�N�X�`���̌J��Ԃ��ݒ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	�摜���g��(MAGnifying)����Ƃ��͐��`(LINEAR)�t�B���^�����O���g�p
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	�摜���k��(MINifying)����Ƃ��A���`(LINEAR)�t�B���^�����A��̃~�b�v�}�b�v����`(LINEARYLY)�ɍ��������̂��g�p
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	�~�b�v�}�b�v���쐬
	glGenerateMipmap(GL_TEXTURE_2D);

	//	Vertex Array ID��ݒ�
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//	uniform�ւ̃n���h�����擾
	//	������������
	GLuint MatrixID = glGetUniformLocation(shader.program, "MVP");		//	vertex.shader���� uniform mat4 MVP; �ւ�ID
	GLuint textureID = glGetUniformLocation(shader.program, "myTextureSampler");	// �ЂƂ�OpenGL�e�N�X�`�������܂��B

	//	���_�o�b�t�@��OpenGL�ɓn��
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);							//	�o�b�t�@��1�쐬
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);			//	�ȍ~�̃R�}���h��vertexbuffer�o�b�t�@�Ɏw��
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * obj.vertices.size(), &obj.vertices[0], GL_STATIC_DRAW);		//	���_��OpenGL��vertexbufer�ɓn��

	//	UV���W�o�b�t�@
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * obj.uvs.size(), &obj.uvs[0], GL_STATIC_DRAW);



	//	���C�����[�v
	while (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS		//	Esc�L�[
		&& !glfwWindowShouldClose(mainWindow))							//	�E�B���h�E�̕���{�^��
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.program);			//	�V�F�[�_�𗘗p
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);			// �O�̂��̂����J�����ɋ߂���΁A�t���O�����g���󂯓����

		// �ˉe�s��F45���̎��E�A�A�X�y�N�g��4:3�A�\���͈́F0.1�P��  100�P��
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
		//glm::mat4x4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
		// �J�����s��
		glm::mat4 View = glm::lookAt(
			glm::vec3(40, 500, 30), // ���[���h��ԂŃJ������(4,3,3)�ɂ���܂��B
			glm::vec3(0, 0, 0), // ���_�����Ă��܂��B
			glm::vec3(0, 1, 0)  // ���������(0,-1,0�ɃZ�b�g����Ə㉺�t�]���܂��B)
			);
		// ���f���s��F�P�ʍs��(���f���͌��_�ɂ���܂��B)
		glm::mat4 Model = glm::mat4(1.0f);  // �e���f����ς���I
		static float angle = 0.0f;
		angle += 0.1f;
		if (angle >= 360.0) angle -= 360.0;
		Model = glm::translate(glm::vec3(0.0, 0.0, 0.0))
			* glm::rotate(angle, glm::vec3(0.0, 0.0, 1.0))
			//* glm::rotate(90.0f, glm::vec3(0.0, 1.0, 0.0))
			* Model;
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP = Projection * View * Model; // �s��̊|���Z�͋t�ɂȂ邱�Ƃ��v���o���Ă��������B

		// ���݃o�C���h���Ă���V�F�[�_��"MVP" uniform�ɕϊ��𑗂�
		// �����_�����O����e���f�����ƂɎ��s
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(textureID, 0);

		// �ŏ��̑����o�b�t�@�F���_
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // ����0�F0�ɓ��ɗ��R�͂���܂���B�������A�V�F�[�_����layout�Ƃ��킹�Ȃ��Ƃ����܂���B
			3,                  // �T�C�Y
			GL_FLOAT,           // �^�C�v
			GL_FALSE,           // ���K���H
			0,                  // �X�g���C�h
			(void*)0            // �z��o�b�t�@�I�t�Z�b�g
			);
		// 2�Ԗڂ̑����o�b�t�@ : UV
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // �����B1�Ƃ��������ɈӖ��͂���܂���B�������V�F�[�_��layout�Ƃ��킹��K�v������܂��B
			2,                                // �T�C�Y
			GL_FLOAT,                         // �^�C�v
			GL_FALSE,                         // ���K���H
			0,                                // �X�g���C�h
			(void*)0                          // �z��o�b�t�@�I�t�Z�b�g
			);


		// �O�p�`��`���܂��I
		glDrawArrays(GL_TRIANGLES, 0, obj.vertices.size()); // ���_0����n�܂�܂��B���v3�̒��_�ł��B��1�̎O�p�`�ł��B

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();

	}

	glfwTerminate();


	return EXIT_SUCCESS;
}