#include <stdio.h>
#include <stdlib.h>
#include "ObjLoader.h"

#pragma warning(disable:4996)

/* �����o�b�t�@�T�C�Y */
#define DEF_BUF_SIZE 2

/* ���������_���o�b�t�@ */
typedef struct {
	int buf_size;
	int current_index;
	float *buf;
} float_buffer;

/* �����o�b�t�@ */
typedef struct {
	int buf_size;
	int current_index;
	int *buf;
} int_buffer;

/* ���_���W�̓ǂݍ��� */
void read_vertices(const char *line, float_buffer *vs);

/* �@���x�N�g���̓ǂݍ��� */
void read_normals(const char *line, float_buffer *vns);

/* �C���f�b�N�X�̓ǂݍ��� */
void read_indices(const char *line, int_buffer *fs);

/* ���f���̍쐬 */
void create_model(model *m,
	float_buffer *vs, float_buffer *vns, int_buffer *fs);

/* ���������_���o�b�t�@�̑��� */
float_buffer *alloc_float_buffer(void);
void free_float_buffer(float_buffer *fbuf);
void add_float(float_buffer *fbuf, float value);
float get_float(float_buffer *fbuf, int index);

/* �����o�b�t�@�̑��� */
int_buffer *alloc_int_buffer(void);
void free_int_buffer(int_buffer *ibuf);
void add_int(int_buffer *ibuf, int value);
int get_int(int_buffer *ibuf, int index);

/*==============================*
** OBJ�t�@�C���̓ǂݍ���
**==============================*/
void load_obj(model *m, const char *file_name)
{
	FILE *fp;
	char line[1024];
	float_buffer *vs, *vns;
	int_buffer *fs;

	fp = fopen(file_name, "r");
	if (!fp) {
		fprintf(stderr, "Cannot open %s.\n", file_name);
		exit(EXIT_FAILURE);
	}

	vs = alloc_float_buffer();
	vns = alloc_float_buffer();
	fs = alloc_int_buffer();

	while (!feof(fp)) {
		fgets(line, sizeof(line), fp);
		if (line[0] == 'v' && line[1] == ' ') {
			read_vertices(line, vs);
		}
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
			read_normals(line, vns);
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			read_indices(line, fs);
		}
	}

	create_model(m, vs, vns, fs);

	free_float_buffer(vs);
	free_float_buffer(vns);
	free_int_buffer(fs);

	fclose(fp);
}

/*------------------------------*
** ���_���W�̓ǂݍ���
**------------------------------*/
void read_vertices(const char *line, float_buffer *vs)
{
	float x, y, z;
	int count;

	count = sscanf(line, "%*s%f%f%f", &x, &y, &z);

	if (count == 3) {
		add_float(vs, x);
		add_float(vs, y);
		add_float(vs, z);
	}
}

/*------------------------------*
** �@���x�N�g���̓ǂݍ���
**------------------------------*/
void read_normals(const char *line, float_buffer *vns)
{
	float x, y, z;
	int count;

	count = sscanf(line, "%*s%f%f%f", &x, &y, &z);

	if (count == 3) {
		add_float(vns, x);
		add_float(vns, y);
		add_float(vns, z);
	}
}

/*------------------------------*
** �C���f�b�N�X�̓ǂݍ���
**------------------------------*/
void read_indices(const char *line, int_buffer *fs)
{
	int v1, v2, v3;
	int n1, n2, n3;
	int count;

	count = sscanf(line,
		"%*s %d%*[/]%d %d%*[/]%d %d%*[/]%d",
		&v1, &n1, &v2, &n2, &v3, &n3);

	if (count == 6) {
		add_int(fs, v1);
		add_int(fs, n1);
		add_int(fs, v2);
		add_int(fs, n2);
		add_int(fs, v3);
		add_int(fs, n3);
	}
}

/*------------------------------*
** ���f���̍쐬
**------------------------------*/
void create_model(model *m,
	float_buffer *vs, float_buffer *vns, int_buffer *fs)
{
	int i, j;

	m->num_vertices = fs->current_index / 2 * 3;
	m->vertices = (float*)malloc(sizeof(float)* m->num_vertices);

	if (!m->vertices) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	m->num_normals = fs->current_index / 2 * 3;
	m->normals = (float*)malloc(sizeof(float)* m->num_normals);

	if (!m->normals) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < fs->current_index; i++) {
		int idx = fs->buf[i] - 1;
		if (i % 2 == 0) {
			for (j = 0; j < 3; j++) {
				m->vertices[i / 2 * 3 + j] = vs->buf[idx * 3 + j];
			}
		}
		else {
			for (j = 0; j < 3; j++) {
				m->normals[i / 2 * 3 + j] = vns->buf[idx * 3 + j];
			}
		}

	}
}

/*------------------------------*
** ���������_���o�b�t�@�̊��蓖��
**------------------------------*/
float_buffer *alloc_float_buffer(void)
{
	float_buffer *fbuf;

	fbuf = (float_buffer*)malloc(sizeof(float_buffer));
	if (!fbuf) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	fbuf->buf_size = DEF_BUF_SIZE;
	fbuf->current_index = 0;
	fbuf->buf = (float*)malloc(sizeof(float)* fbuf->buf_size);

	return fbuf;
}

/*------------------------------*
** ���������_���o�b�t�@�̉��
**------------------------------*/
void free_float_buffer(float_buffer *fbuf)
{
	free(fbuf->buf);
	free(fbuf);
}

/*------------------------------*
** �o�b�t�@�ɕ��������_����ǉ�
**------------------------------*/
void add_float(float_buffer *fbuf, float value)
{
	fbuf->buf[fbuf->current_index] = value;
	fbuf->current_index++;
	if (fbuf->current_index >= fbuf->buf_size) {
		fbuf->buf_size *= 2;
		fbuf->buf = (float*)realloc(fbuf->buf, sizeof(float)* fbuf->buf_size);
		if (!fbuf->buf) {
			fprintf(stderr, "Memory allocation error.\n");
			exit(EXIT_FAILURE);
		}
	}
}

/*------------------------------*
** �o�b�t�@���畂�������_�������o��
**------------------------------*/
float get_float(float_buffer *fbuf, int index)
{
	return fbuf->buf[index];
}

/*------------------------------*
** �����o�b�t�@�̊��蓖��
**------------------------------*/
int_buffer *alloc_int_buffer(void)
{
	int_buffer *ibuf;

	ibuf = (int_buffer*)malloc(sizeof(int_buffer));
	if (!ibuf) {
		fprintf(stderr, "Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	ibuf->buf_size = DEF_BUF_SIZE;
	ibuf->current_index = 0;
	ibuf->buf = (int*)malloc(sizeof(int)* ibuf->buf_size);

	return ibuf;
}

/*------------------------------*
** �����o�b�t�@�̉��
**------------------------------*/
void free_int_buffer(int_buffer *ibuf)
{
	free(ibuf->buf);
	free(ibuf);
}

/*------------------------------*
** �o�b�t�@�ɐ�����ǉ�
**------------------------------*/
void add_int(int_buffer *ibuf, int value)
{
	ibuf->buf[ibuf->current_index] = value;
	ibuf->current_index++;
	if (ibuf->current_index >= ibuf->buf_size) {
		ibuf->buf_size *= 2;
		ibuf->buf = (int*)realloc(ibuf->buf, sizeof(int)* ibuf->buf_size);
		if (!ibuf->buf) {
			fprintf(stderr, "Memory allocation error.\n");
			exit(EXIT_FAILURE);
		}
	}
}

/*------------------------------*
** �o�b�t�@���琮�������o��
**------------------------------*/
int get_int(int_buffer *ibuf, int index)
{
	return ibuf->buf[index];
}