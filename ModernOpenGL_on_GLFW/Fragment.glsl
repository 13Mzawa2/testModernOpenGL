//	画素シェーダ

#version 330 core
 
// 頂点シェーダからの値を書き込みます
in vec2 UV;
 
// アウトプットデータ
out vec3 color;
 
// すべてのメッシュで一定の値
uniform sampler2D myTextureSampler;
 
void main(){
 
    // アウトプットカラー = 指定したUV座標のテクスチャの色
    color = texture( myTextureSampler, UV ).rgb;
}