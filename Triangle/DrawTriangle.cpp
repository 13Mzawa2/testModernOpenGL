#include "OpenGLHeader.h"
#include "Shader.h"

//	Variable
// 3頂点を表す3つのベクトルの配列
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};
GLFWwindow* window;			//	Window ID
Shader shader;				//	プログラマブルシェーダ

int main(void)
{
	//	GLFWの初期化
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	//	Window設定
	glfwWindowHint(GLFW_SAMPLES, 4);								//	4x アンチエイリアス
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						//	リサイズ不可
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					//	OpenGLバージョン3.3を利用
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);					//	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//	古いOpenGLを使わない

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);				//	windowをカレントにする

	// Initialize GLEW
	glewExperimental = true;	// Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	
	//	キー入力を受け付けるようにする
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//	プログラマブルシェーダをロード
	shader.initGLSL("vertex.shader", "fragment.shader");

	//	Vertex Array IDを設定
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	//	背景色の設定
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	//	頂点バッファをOpenGLに渡す
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);							//	バッファを1つ作成
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);			//	以降のコマンドをvertexbufferバッファに指定
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);		//	頂点をOpenGLのvertexbuferに渡す

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.program);			//	シェーダを利用
		// 最初の属性バッファ：頂点
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
			3,                  // サイズ
			GL_FLOAT,           // タイプ
			GL_FALSE,           // 正規化？
			0,                  // ストライド
			(void*)0            // 配列バッファオフセット
			);

		// 三角形を描きます！
		glDrawArrays(GL_TRIANGLES, 0, 3); // 頂点0から始まります。合計3つの頂点です。→1つの三角形です。

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

