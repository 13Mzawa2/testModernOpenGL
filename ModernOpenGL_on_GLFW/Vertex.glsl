//	���_�V�F�[�_

#version 330 core
 
// �C���v�b�g���_�f�[�^�B���̃V�F�[�_�̎��s���ƂɈقȂ�܂��B
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
 
// �A�E�g�v�b�g�f�[�^�B�e�t���O�����g�ŏ������܂�܂��B
out vec2 UV;
 
// ���ׂẴ��b�V���ň��̒l
uniform mat4 MVP;
 
void main(){
 
    // �N���b�v��Ԃł̒��_�̏o�͈ʒu�BMVP�~�ʒu
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
 
    // ���_��UV���W�ł��B���ʂȋ�Ԃ͂���܂���B
    UV = vertexUV;
}