//	頂点シェーダ

#version 330 core
 
// インプット頂点データ。このシェーダの実行ごとに異なります。
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
 
// アウトプットデータ。各フラグメントで書き込まれます。
out vec2 UV;
 
// すべてのメッシュで一定の値
uniform mat4 MVP;
 
void main(){
 
    // クリップ空間での頂点の出力位置。MVP×位置
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
 
    // 頂点のUV座標です。特別な空間はありません。
    UV = vertexUV;
}