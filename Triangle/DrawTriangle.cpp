#include "OpenGLHeader.h"
#include "Shader.h"

//	Variable
// 3���_��\��3�̃x�N�g���̔z��
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};
GLFWwindow* window;			//	Window ID
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

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.program);			//	�V�F�[�_�𗘗p
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

		// �O�p�`��`���܂��I
		glDrawArrays(GL_TRIANGLES, 0, 3); // ���_0����n�܂�܂��B���v3�̒��_�ł��B��1�̎O�p�`�ł��B

		glDisableVertexAttribArray(0);

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

