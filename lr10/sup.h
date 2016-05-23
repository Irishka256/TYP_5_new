#pragma once
#include <iostream>
#include <string.h>
#include "Defs.h"
#include "tree.h"

struct SupData{
	int type;
	union{
		int AsInt;
		double AsDouble;
		char AsString[MAX_LEX];
		tree *AsTreeNode;
	};
	SupData(){
		type = -1;
	};
	SupData(int val){
		type = 1;
		AsInt = val;
	}
	SupData(double val){
		type = 2;
		AsDouble = val;
	}
	SupData(char *val){
		type = 3;
		strcpy(AsString, val);
	}
	SupData(tree *val){
		type = 4;
		AsTreeNode = val;
	}
	SupData(int val, bool Triade){
		if (Triade){
			type = 5;
			AsInt = val;
		}
		else{
			type = 1;
			AsInt = val;
		}
	}
	void Copy(SupData *SD){
		if (SD == nullptr){
			type = -1;
			return;
		}
		type = SD->type;
		switch (type){
		case 1:
			AsInt = SD->AsInt;
			break;
		case 2:
			AsDouble = SD->AsDouble;
			break;
		case 3:
			strcpy(AsString, SD->AsString);
			break;
		case 4:
			AsTreeNode = SD->AsTreeNode;
			break;
		case 5:
			AsInt = SD->AsInt;
			break;
		}
	}

	void Print(){
		switch (type){
		case 1:
			std::cout << AsInt;
			break;
		case 2:
			std::cout << AsDouble;
			break;
		case 3:
			std::cout << AsString;
			break;
		case 4:
			std::cout << (AsTreeNode->n->Name);
			break;
		case 5:
			std::cout << "(" << AsInt << ")";
			break;
		}
	}
};

struct Triade{
	int Operation;
	SupData Arg1;
	SupData Arg2;
	Triade(){
		Operation = ONop;
	}
	Triade(Triade *T){
		Operation = T->Operation;
		Arg1.Copy(&(T->Arg1));
		Arg2.Copy(&(T->Arg2));
	}
	Triade(int O, SupData *A1, SupData *A2){
		Operation = O;
		Arg1.Copy(A1);
		Arg2.Copy(A2);
	}
	void Copy(Triade *T){
		Operation = T->Operation;
		Arg1.Copy(&(T->Arg1));
		Arg2.Copy(&(T->Arg2));
	}
	void SetArg1(SupData *A){
		Arg1.Copy(A);
	}
	void SetArg2(SupData *A){
		Arg2.Copy(A);
	}
	
	void Print(){
		switch (Operation){
		case ONop:
			std::cout << "nop";
			break;
		case OPlus:
			std::cout << "+";
			break;
		case OMinus:
			std::cout << "-";
			break;
		case OMul:
			std::cout << "*";
			break;
		case ODiv:
			std::cout << "/";
			break;
		case OMod:
			std::cout << "%";
			break;
		case ORavno:
			std::cout << "==";
			break;
		case ONeRavno:
			std::cout << "!=";
			break;
		case OMenshe:
			std::cout << "<";
			break;
		case OBolshe:
			std::cout << ">";
			break;
		case OMensheRavno:
			std::cout << "<=";
			break;
		case OBolsheRavno:
			std::cout << ">=";
			break;
		case OPris:
			std::cout << "=";
			break;
		case OIf:
			std::cout << "if";
			break;
		case OGoto:
			std::cout << "goto";
			break;
		case OOffset:
			std::cout << "[]";
			break;
		case OPlusPlus:
			std::cout << "++";
			break;
		case OMinusMinus:
			std::cout << "--";
			break;
		case ORet:
			std::cout << "ret";
			break;
		}
		std::cout << "\t";
		Arg1.Print();
		std::cout << "\t";
		Arg2.Print();
		std::cout << std::endl;
	}

};

class Code{
public:
	Triade Triades[MAX_TEXT];
	int count;
	bool error;
	Code(){
		count = 0;
		error = false;
	}
	void AddTriade(Triade *T){
		Triades[count].Operation = T->Operation;
		Triades[count].Arg1.Copy(&(T->Arg1));
		Triades[count].Arg2.Copy(&(T->Arg2));
		count++;
	}
	void AddTriade(int O, SupData *A1, SupData *A2){
		AddTriade(new Triade(O, A1, A2));
	}

	void SetLastArg1(SupData *A){
		for (int i = count - 1; i >= 0; i--){
			if (Triades[i].Arg1.type == -1){
				Triades[i].Arg1.Copy(A);
				break;
			}
		}
	}
	void SetLastArg2(SupData *A){
		for (int i = count - 1; i >= 0; i--){
			if (Triades[i].Arg2.type == -1){
				Triades[i].Arg2.Copy(A);
				break;
			}
		}
	}
	void Print(){
		for (int i = 0; i<count; i++){
			std::cout << i << "\t";
			Triades[i].Print();
		}
	}
	
};