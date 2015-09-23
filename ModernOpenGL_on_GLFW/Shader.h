#pragma once

#include "OpenGLHeader.h"

class Shader
{
protected:
	GLuint vertexShader, fragmentShader;
	void readShaderCompile(GLuint shader, const char *file);	//	.shaderのコンパイル
	void link(GLuint prog);		//	コンパイルしたshaderをリンクする
public:
	GLuint program;			//	シェーダプログラム
	Shader();
	~Shader();
	//	初期化
	//	フラグメントシェーダーの有無で分ける
	void loadGLSL(const char *vertexFile);
	void loadGLSL(const char *vertexFile, const char *fragmentFile);
};

