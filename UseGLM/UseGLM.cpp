#include <iostream>
#include <opencv2\opencv.hpp>
#include "OpenGLHeader.h"
#include "Shader.h"

using namespace cv;

//	Variable
//// 3���_��\��3�̃x�N�g���̔z��
//static const GLfloat g_vertex_buffer_data[] = {
//	-1.0f, -1.0f, 0.0f,
//	1.0f, -1.0f, 0.0f,
//	0.0f, 1.0f, 0.0f,
//};
// ���_�B3�̘A�����鐔����3�����̒��_�ł��B3�̘A�����钸�_�͎O�p�`���Ӗ����܂��B
// �����̂́A���ꂼ�ꂪ2���̎O�p�`����Ȃ�6�ʂ��琬��܂��B������6*2=12���̎O�p�`��12*3�̒��_�����܂��B
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, -1.0f, // �O�p�`1:�J�n
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // �O�p�`1:�I��
	1.0f, 1.0f, -1.0f, // �O�p�`2:�J�n
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // �O�p�`2:�I��
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};
// �e���_�Ɉ�̐F�B�����̓����_���ɍ���܂����B
static const GLfloat g_color_buffer_data[] = {
	0.583f, 0.771f, 0.014f,
	0.609f, 0.115f, 0.436f,
	0.327f, 0.483f, 0.844f,
	0.822f, 0.569f, 0.201f,
	0.435f, 0.602f, 0.223f,
	0.310f, 0.747f, 0.185f,
	0.597f, 0.770f, 0.761f,
	0.559f, 0.436f, 0.730f,
	0.359f, 0.583f, 0.152f,
	0.483f, 0.596f, 0.789f,
	0.559f, 0.861f, 0.639f,
	0.195f, 0.548f, 0.859f,
	0.014f, 0.184f, 0.576f,
	0.771f, 0.328f, 0.970f,
	0.406f, 0.615f, 0.116f,
	0.676f, 0.977f, 0.133f,
	0.971f, 0.572f, 0.833f,
	0.140f, 0.616f, 0.489f,
	0.997f, 0.513f, 0.064f,
	0.945f, 0.719f, 0.592f,
	0.543f, 0.021f, 0.978f,
	0.279f, 0.317f, 0.505f,
	0.167f, 0.620f, 0.077f,
	0.347f, 0.857f, 0.137f,
	0.055f, 0.953f, 0.042f,
	0.714f, 0.505f, 0.345f,
	0.783f, 0.290f, 0.734f,
	0.722f, 0.645f, 0.174f,
	0.302f, 0.455f, 0.848f,
	0.225f, 0.587f, 0.040f,
	0.517f, 0.713f, 0.338f,
	0.053f, 0.959f, 0.120f,
	0.393f, 0.621f, 0.362f,
	0.673f, 0.211f, 0.457f,
	0.820f, 0.883f, 0.371f,
	0.982f, 0.099f, 0.879f
};
GLFWwindow* window;			//	Window ID
GLFWwindow* sub;
Shader shader;				//	�v���O���}�u���V�F�[�_

int main(void)
{
	//	GLFW�̏�����
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	//	Window�ݒ�
	glfwWindowHint(GLFW_SAMPLES, 4);								//	4x �A���`�G�C���A�X
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						//	���T�C�Y�s��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					//	OpenGL�o�[�W����3.3�𗘗p
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					//	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//	�Â�OpenGL���g��Ȃ�

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	////	�T�u�E�B���h�E����
	//sub = glfwCreateWindow(1024, 768, "SubWindow", NULL, NULL);
	//if (sub == NULL){
	//	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
	//	glfwTerminate();
	//	return -1;
	//}
	glfwMakeContextCurrent(window);				//	window���J�����g�ɂ���

	// Initialize GLEW
	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	//	�L�[���͂��󂯕t����悤�ɂ���
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//	�v���O���}�u���V�F�[�_�����[�h
	shader.initGLSL("vertex.shader", "fragment.shader");

	//	Vertex Array ID��ݒ�
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//	�w�i�F�̐ݒ�
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//	���_�o�b�t�@��OpenGL�ɓn��
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);							//	�o�b�t�@��1�쐬
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);			//	�ȍ~�̃R�}���h��vertexbuffer�o�b�t�@�Ɏw��
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);		//	���_��OpenGL��vertexbufer�ɓn��

	//	�J���[�o�b�t�@��OpenGL�ɓn��
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);							//	�o�b�t�@��1�쐬
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);			//	�ȍ~�̃R�}���h��vertexbuffer�o�b�t�@�Ɏw��
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);		//	���_��OpenGL��vertexbufer�ɓn��

	// "MVP" uniform�ւ̃n���h�����擾���܂��B
	// ������������
	GLuint MatrixID = glGetUniformLocation(shader.program, "MVP");		//	vertex.shader���� uniform mat4 MVP; �ւ�ID

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.program);			//	�V�F�[�_�𗘗p
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);			// �O�̂��̂����J�����ɋ߂���΁A�t���O�����g���󂯓����

		// �ˉe�s��F45���̎��E�A�A�X�y�N�g��4:3�A�\���͈́F0.1�P��  100�P��
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		//glm::mat4x4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
		// �J�����s��
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // ���[���h��ԂŃJ������(4,3,3)�ɂ���܂��B
			glm::vec3(0, 0, 0), // ���_�����Ă��܂��B
			glm::vec3(0, 1, 0)  // ���������(0,-1,0�ɃZ�b�g����Ə㉺�t�]���܂��B)
			);
		// ���f���s��F�P�ʍs��(���f���͌��_�ɂ���܂��B)
		glm::mat4 Model = glm::mat4(1.0f);  // �e���f����ς���I
		static float angle = 0.0f;
		angle += 0.1f;
		if (angle >= 360.0) angle -= 360.0;
		Model = glm::translate(glm::vec3(0.0, 0.0, 1.0)) * glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0)) * Model;
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP = Projection * View * Model; // �s��̊|���Z�͋t�ɂȂ邱�Ƃ��v���o���Ă��������B

		// ���݃o�C���h���Ă���V�F�[�_��"MVP" uniform�ɕϊ��𑗂�
		// �����_�����O����e���f�����ƁA�Ȃ��Ȃ�MVP���Ⴄ����ł��B(���Ȃ��Ƃ�M�̕������Ⴂ�܂��B)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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
		// 2�Ԗڂ̑����o�b�t�@ : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // �����B1�Ƃ��������ɈӖ��͂���܂���B�������V�F�[�_��layout�Ƃ��킹��K�v������܂��B
			3,                                // �T�C�Y
			GL_FLOAT,                         // �^�C�v
			GL_FALSE,                         // ���K���H
			0,                                // �X�g���C�h
			(void*)0                          // �z��o�b�t�@�I�t�Z�b�g
			);

		// �O�p�`��`���܂��I
		glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data)/sizeof(GLfloat)); // ���_0����n�܂�܂��B���v3�̒��_�ł��B��1�̎O�p�`�ł��B

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

