//	��f�V�F�[�_

#version 330 core
 
// ���_�V�F�[�_����̒l���������݂܂�
in vec2 UV;
 
// �A�E�g�v�b�g�f�[�^
out vec3 color;
 
// ���ׂẴ��b�V���ň��̒l
uniform sampler2D myTextureSampler;
 
void main(){
 
    // �A�E�g�v�b�g�J���[ = �w�肵��UV���W�̃e�N�X�`���̐F
    color = texture( myTextureSampler, UV ).rgb;
}