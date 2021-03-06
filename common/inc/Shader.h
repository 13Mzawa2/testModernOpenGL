#pragma once

#include "OpenGLHeader.h"

class Shader
{
private:
	GLuint vertexShader, fragmentShader;
public:
	GLuint program;			//	シェーダプログラム
	Shader();
	~Shader();
	void readShaderCompile(GLuint shader, const char *file);	//	.shaderのコンパイル
	void link(GLuint prog);		//	コンパイルしたshaderをリンクする
	//	初期化
	//	フラグメントシェーダーの有無で分ける
	void initGLSL(const char *vertexFile);
	void initGLSL(const char *vertexFile, const char *fragmentFile);


};

