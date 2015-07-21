#include <opencv2\opencv.hpp>
#include "OpenGLHeader.h"
#include "Shader.h"
#include "OBJLoader.h"

using namespace cv;

GLFWwindow	*mainWindow, *subWindow;		//	�}���`�E�B���h�E
Shader		shader;						//	�V�F�[�_�[�N���X
model		bottle;						//	OBJ���f��

GLuint position_buffer;
GLuint vertex_array;

const GLuint position_location = 0;
const GLuint position_bindindex = 0;

int initialize(void);

int initialize(void)
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
	// Sub Window�̗p��
	subWindow = glfwCreateWindow(1024, 768, "Sub Window", NULL, NULL);
	if (subWindow == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(mainWindow);				//	main window���J�����g�ɂ���

	// Initialize GLEW
	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_FAILURE;
	}

	//	�L�[���͂��󂯕t����悤�ɂ���
	glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);
	//	�v���O���}�u���V�F�[�_�����[�h
	shader.initGLSL("vertex.shader", "fragment.shader");
	//	obj�t�@�C�������[�h
	load_obj(&bottle, "model/drop_modified_x004.obj");

	//	�o�b�t�@�̐ݒ�
	glCreateBuffers(1, &position_buffer);
	glNamedBufferData(position_buffer,
		sizeof(float)* bottle.num_vertices,
		bottle.vertices,
		GL_STATIC_DRAW);

	glCreateVertexArrays(1, &vertex_array);

	glEnableVertexArrayAttrib(
		vertex_array, position_location);
	glVertexArrayAttribFormat(
		vertex_array, position_location,
		3, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(
		vertex_array, position_location,
		position_bindindex);
	glVertexArrayVertexBuffer(
		vertex_array, position_bindindex,
		position_buffer, 0, sizeof(GLfloat)* 3);


	return EXIT_SUCCESS;
}

int main(void)
{
	if (initialize() == EXIT_FAILURE) return EXIT_FAILURE;

	glClearColor(0.6, 0.8, 0.8, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//	���C�����[�v
	while (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS		//	Esc�L�[
		&& !glfwWindowShouldClose(mainWindow))							//	�E�B���h�E�̕���{�^��
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vertex_array);
		glDrawArrays(GL_TRIANGLES, 0, bottle.num_vertices / 3);

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();


	return EXIT_SUCCESS;
}