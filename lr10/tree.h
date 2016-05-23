#pragma once
#include "Defs.h"
#include <string.h>

struct node{
	char Name[MAX_LEX];
	char id[MAX_LEX]; // идентификатор
	char type[MAX_LEX]; // название типа
	bool is_type; // признак типа

	int N; // размерность массива
	int hg[MAX_N]; // верхние границы измерений

	node(){
		id[0] = '\0';
		type[0] = '\0';
		Name[0] = '\0';
		N = 0;
	}
	node(char *i){
		strcpy(id, i);
		type[0] = '\0';
		Name[0] = '\0';
		is_type = false;
		N = 0;
	}
	node(char *i, char *t){
		strcpy(id, i);
		strcpy(type, t);
		Name[0] = '\0';
		N = 0;
		is_type = false;
	}
	node(char *i, char *t, bool it){
		strcpy(id, i);
		strcpy(type, t);
		Name[0] = '\0';
		N = 0;
		is_type = it;
	}
};

class tree
{
public:
	node *n;
	tree *up, *left, *right;
	tree(void);
	tree(tree *u, tree *l, tree *r, node *data);
	void set_left(node *data);
	void set_right(node *data);
	tree *find_up(char *id);
	//tree *find_right_left(char *id);
	bool sosed(char *id);
	void print(void);

	bool sem_get_type(char *id, int line);
	bool sem_override(char *id, int line); //проверка на переобпределение
	bool sem_var_declared(char *id, int line);
	bool sem_arr_rank(char *id, int r, int line);
	int sem_result(int t1, int t2, int oper);
	tree *sem_add_var(char *id, char *type);
	tree *sem_add_type(char *id, char *type);
	void sem_set_dim(int hg, int line);

	~tree(void);
};

