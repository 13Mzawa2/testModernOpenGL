#include <iostream>
#include <opencv2\opencv.hpp>
#include "OpenGLHeader.h"
#include "Shader.h"

using namespace cv;

//	Variable
//// 3頂点を表す3つのベクトルの配列
//static const GLfloat g_vertex_buffer_data[] = {
//	-1.0f, -1.0f, 0.0f,
//	1.0f, -1.0f, 0.0f,
//	0.0f, 1.0f, 0.0f,
//};
// 頂点。3つの連続する数字は3次元の頂点です。3つの連続する頂点は三角形を意味します。
// 立方体は、それぞれが2枚の三角形からなる6面から成ります。だから6*2=12枚の三角形と12*3個の頂点を作ります。
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, -1.0f, // 三角形1:開始
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // 三角形1:終了
	1.0f, 1.0f, -1.0f, // 三角形2:開始
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // 三角形2:終了
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
// 各頂点に一つの色。これらはランダムに作られました。
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
	////	サブウィンドウ生成
	//sub = glfwCreateWindow(1024, 768, "SubWindow", NULL, NULL);
	//if (sub == NULL){
	//	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
	//	glfwTerminate();
	//	return -1;
	//}
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

	//	カラーバッファをOpenGLに渡す
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);							//	バッファを1つ作成
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);			//	以降のコマンドをvertexbufferバッファに指定
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);		//	頂点をOpenGLのvertexbuferに渡す

	// "MVP" uniformへのハンドルを取得します。
	// 初期化時だけ
	GLuint MatrixID = glGetUniformLocation(shader.program, "MVP");		//	vertex.shader内の uniform mat4 MVP; へのID

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader.program);			//	シェーダを利用
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);			// 前のものよりもカメラに近ければ、フラグメントを受け入れる

		// 射影行列：45°の視界、アスペクト比4:3、表示範囲：0.1単位  100単位
		glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		//glm::mat4x4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
		// カメラ行列
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // ワールド空間でカメラは(4,3,3)にあります。
			glm::vec3(0, 0, 0), // 原点を見ています。
			glm::vec3(0, 1, 0)  // 頭が上方向(0,-1,0にセットすると上下逆転します。)
			);
		// モデル行列：単位行列(モデルは原点にあります。)
		glm::mat4 Model = glm::mat4(1.0f);  // 各モデルを変える！
		static float angle = 0.0f;
		angle += 0.1f;
		if (angle >= 360.0) angle -= 360.0;
		Model = glm::translate(glm::vec3(0.0, 0.0, 1.0)) * glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0)) * Model;
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP = Projection * View * Model; // 行列の掛け算は逆になることを思い出してください。

		// 現在バインドしているシェーダの"MVP" uniformに変換を送る
		// レンダリングする各モデルごと、なぜならMVPが違うからです。(少なくともMの部分が違います。)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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
		// 2番目の属性バッファ : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // 属性。1という数字に意味はありません。ただしシェーダのlayoutとあわせる必要があります。
			3,                                // サイズ
			GL_FLOAT,                         // タイプ
			GL_FALSE,                         // 正規化？
			0,                                // ストライド
			(void*)0                          // 配列バッファオフセット
			);

		// 三角形を描きます！
		glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data)/sizeof(GLfloat)); // 頂点0から始まります。合計3つの頂点です。→1つの三角形です。

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

