#include <opencv2\opencv.hpp>
#include "OpenGLHeader.h"
#include "Shader.h"
#include "OBJLoader.h"

using namespace cv;

GLFWwindow	*mainWindow, *subWindow;		//	マルチウィンドウ
Shader		shader;						//	シェーダークラス
model		bottle;						//	OBJモデル

GLuint position_buffer;
GLuint vertex_array;

const GLuint position_location = 0;
const GLuint position_bindindex = 0;

int initialize(void);

int initialize(void)
{
	//	GLFWの初期化
	if (glfwInit() != GL_TRUE)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return EXIT_FAILURE;
	}
	//	Window設定
	glfwWindowHint(GLFW_SAMPLES, 4);								//	4x アンチエイリアス
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						//	リサイズ不可
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					//	OpenGLバージョン3.3を利用
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					//	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//	古いOpenGLを使わない

	// Main Windowの用意
	mainWindow = glfwCreateWindow(1024, 768, "Main Window", NULL, NULL);
	if (mainWindow == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	// Sub Windowの用意
	subWindow = glfwCreateWindow(1024, 768, "Sub Window", NULL, NULL);
	if (subWindow == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(mainWindow);				//	main windowをカレントにする

	// Initialize GLEW
	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return EXIT_FAILURE;
	}

	//	キー入力を受け付けるようにする
	glfwSetInputMode(mainWindow, GLFW_STICKY_KEYS, GL_TRUE);
	//	プログラマブルシェーダをロード
	shader.initGLSL("vertex.shader", "fragment.shader");
	//	objファイルをロード
	load_obj(&bottle, "model/drop_modified_x004.obj");

	//	バッファの設定
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

	//	メインループ
	while (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS		//	Escキー
		&& !glfwWindowShouldClose(mainWindow))							//	ウィンドウの閉じるボタン
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