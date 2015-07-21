//	頂点シェーダ

#version 330 core			//	OpenGL 3.3を使用

//	インプットデータ
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
//	アウトプットデータ
out vec3 fragmentColor;
uniform mat4 MVP;

void main(){
 
    // クリップ空間での、頂点のアウトプット位置：MVP * 位置
    vec4 v = vec4(vertexPosition_modelspace,1); // 同次4Dベクトルに変換します。覚えていますか？
    gl_Position = MVP * v;

	//	フラグメントシェーダに転送
	fragmentColor = vertexColor;
}