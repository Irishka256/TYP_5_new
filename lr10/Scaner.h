#ifndef __SCANER
#define __SCANER
#include "defs.h"

class TScaner{
private:
	TypeMod t; // �������� �����
	int uk; // ��������� ������� ������� � �������� ������
	int stroka;
public:
	void PutUK (int i);
	int GetUK (void);
	void PrintError(char *, char *);
	int Scaner (TypeLex l);
	void GetData(char *);
	TScaner(char *);
	//TScaner();
	void PutStroka (int i);
	int GetStroka  (void);
	~TScaner() {}
};
#endif
