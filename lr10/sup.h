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
	bool Equals(SupData *SD){
		if (SD->type != this->type) return false;
		switch (type){
		case 1:
			return (SD->AsInt == this->AsInt);
			break;
		case 2:
			return (SD->AsDouble == this->AsDouble);
			break;
		case 3:
			return (strcmp(SD->AsString, this->AsString) == 0);
			break;
		case 4:
			return (SD->AsTreeNode == this->AsTreeNode);
			break;
		case 5:
			return (SD->AsInt == this->AsInt);
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
	bool Equals(Triade *T){
		if (T->Operation != this->Operation) return false;
		switch (Operation){
		case ONop:
			return true;
			break;
		case OPlus:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			if (this->Arg1.Equals(&(T->Arg2)) && this->Arg2.Equals(&(T->Arg1))) return true;
			return false;
			break;
		case OMinus:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OMul:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			if (this->Arg1.Equals(&(T->Arg2)) && this->Arg2.Equals(&(T->Arg1))) return true;
			return false;
			break;
		case ODiv:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OMod:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OEq:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			if (this->Arg1.Equals(&(T->Arg2)) && this->Arg2.Equals(&(T->Arg1))) return true;
			return false;
			break;
		case ONeq:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			if (this->Arg1.Equals(&(T->Arg2)) && this->Arg2.Equals(&(T->Arg1))) return true;
			return false;
			break;
		case OLt:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OGt:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OLteq:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OGteq:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OSet:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OIf:
			return false;
			break;
		case OGoto:
			return false;
			break;
		case OOffset:
			if (this->Arg1.Equals(&(T->Arg1)) && this->Arg2.Equals(&(T->Arg2))) return true;
			return false;
			break;
		case OPlusPlus:
			return false;
			break;
		case OMinusMinus:
			return false;
			break;
		case ORet:
			return false;
			break;
		}
	}
	int ResultType(){
		switch (Operation){
		case ONop:
			return -1;
			break;
		case OPlus:
			if (Arg1.type == 1 && Arg2.type == 1) return 1;
			if (Arg1.type == 1 && Arg2.type == 2) return 2;
			if (Arg1.type == 2 && Arg2.type == 1) return 2;
			if (Arg1.type == 2 && Arg2.type == 2) return 2;
			return -1;
			break;
		case OMinus:
			if (Arg1.type == 1 && Arg2.type == 1) return 1;
			if (Arg1.type == 1 && Arg2.type == 2) return 2;
			if (Arg1.type == 2 && Arg2.type == 1) return 2;
			if (Arg1.type == 2 && Arg2.type == 2) return 2;
			return -1;
			break;
		case OMul:
			if (Arg1.type == 1 && Arg2.type == 1) return 1;
			if (Arg1.type == 1 && Arg2.type == 2) return 2;
			if (Arg1.type == 2 && Arg2.type == 1) return 2;
			if (Arg1.type == 2 && Arg2.type == 2) return 2;
			return -1;
			break;
		case ODiv:
			if (Arg1.type == 1 && Arg2.type == 1) return 1;
			if (Arg1.type == 1 && Arg2.type == 2) return 2;
			if (Arg1.type == 2 && Arg2.type == 1) return 2;
			if (Arg1.type == 2 && Arg2.type == 2) return 2;
			return -1;
			break;
		case OMod:
			if (Arg1.type == 1 && Arg2.type == 1) return 1;
			if (Arg1.type == 1 && Arg2.type == 2) return 2;
			if (Arg1.type == 2 && Arg2.type == 1) return 2;
			if (Arg1.type == 2 && Arg2.type == 2) return 2;
			return -1;
			break;
		case OEq:
			return 1;
			break;
		case ONeq:
			return 1;
			break;
		case OLt:
			return 1;
			break;
		case OGt:
			return 1;
			break;
		case OLteq:
			return 1;
			break;
		case OGteq:
			return 1;
			break;
		case OSet:
			if (Arg1.type == 1 || Arg2.type == 1) return 1;
			if (Arg1.type == 2 || Arg2.type == 2) return 2;
			break;
		case OIf:
			return -1;
			break;
		case OGoto:
			return -1;
			break;
		case OOffset:
			return -1;
			break;
		case OPlusPlus:
			return -1;
			break;
		case OMinusMinus:
			return -1;
			break;
		case ORet:
			return -1;
			break;
		}
	}
	SupData *PerformOperation(){
		SupData *Result = new SupData();
		Result->type = ResultType();

		switch (Operation){
		case ONop:
			return nullptr;
			break;
		case OPlus:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt + Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsDouble = (Arg1.AsInt + Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsDouble = (Arg1.AsDouble + Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsDouble = (Arg1.AsDouble + Arg2.AsDouble);
			break;
		case OMinus:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt - Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsDouble = (Arg1.AsInt - Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsDouble = (Arg1.AsDouble - Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsDouble = (Arg1.AsDouble - Arg2.AsDouble);
			break;
		case OMul:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt * Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsDouble = (Arg1.AsInt * Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsDouble = (Arg1.AsDouble * Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsDouble = (Arg1.AsDouble * Arg2.AsDouble);
			break;
		case ODiv:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt / Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsDouble = (Arg1.AsInt / Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsDouble = (Arg1.AsDouble / Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsDouble = (Arg1.AsDouble / Arg2.AsDouble);
			break;
		case OMod:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt % Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsDouble = (Arg1.AsInt % (int)Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsDouble = ((int)Arg1.AsDouble % Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsDouble = ((int)Arg1.AsDouble % (int)Arg2.AsDouble);
			break;
		case OEq:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt == Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsInt = (Arg1.AsInt == Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsInt = (Arg1.AsDouble == Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsInt = (Arg1.AsDouble == Arg2.AsDouble);
			break;
		case ONeq:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt != Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsInt = (Arg1.AsInt != Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsInt = (Arg1.AsDouble != Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsInt = (Arg1.AsDouble != Arg2.AsDouble);
			break;
		case OLt:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt < Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsInt = (Arg1.AsInt < Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsInt = (Arg1.AsDouble < Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsInt = (Arg1.AsDouble < Arg2.AsDouble);
			break;
		case OGt:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt > Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsInt = (Arg1.AsInt > Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsInt = (Arg1.AsDouble > Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsInt = (Arg1.AsDouble > Arg2.AsDouble);
			break;
		case OLteq:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt <= Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsInt = (Arg1.AsInt <= Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsInt = (Arg1.AsDouble <= Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsInt = (Arg1.AsDouble <= Arg2.AsDouble);
			break;
		case OGteq:
			if (Arg1.type == 1 && Arg2.type == 1) Result->AsInt = (Arg1.AsInt >= Arg2.AsInt);
			else if (Arg1.type == 1 && Arg2.type == 2) Result->AsInt = (Arg1.AsInt >= Arg2.AsDouble);
			else if (Arg1.type == 2 && Arg2.type == 1) Result->AsInt = (Arg1.AsDouble >= Arg2.AsInt);
			else if (Arg1.type == 2 && Arg2.type == 2) Result->AsInt = (Arg1.AsDouble >= Arg2.AsDouble);
			break;
		case OSet:
			if (Arg1.type == 1) Result->AsInt = Arg1.AsInt;
			else if (Arg1.type == 2) Result->AsDouble = Arg1.AsDouble;
			else if (Arg2.type == 1) Result->AsInt = Arg2.AsInt;
			else if (Arg2.type == 2) Result->AsDouble = Arg2.AsDouble;
			break;
		case OIf:
			return nullptr;
			break;
		case OGoto:
			return nullptr;
			break;
		case OOffset:
			return nullptr;
			break;
		case OPlusPlus:
			return nullptr;
			break;
		case OMinusMinus:
			return nullptr;
			break;
		case ORet:
			return nullptr;
			break;
		}

		return Result;
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
		case OEq:
			std::cout << "==";
			break;
		case ONeq:
			std::cout << "!=";
			break;
		case OLt:
			std::cout << "<";
			break;
		case OGt:
			std::cout << ">";
			break;
		case OLteq:
			std::cout << "<=";
			break;
		case OGteq:
			std::cout << ">=";
			break;
		case OSet:
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

	void ReplaceNumbers(int A, int B){
		if (A == B) return;
		int min = A, max = B;
		if (A > B){
			min = B;
			max = A;
		}

		//if (Arg1.type == 5 && Arg1.AsInt == min) Arg1.AsInt = max;
		if (Arg1.type == 5 && Arg1.AsInt == max) Arg1.AsInt = min;
		else if (Arg1.type == 5 && Arg1.AsInt >= min &&  Arg1.AsInt <= max) Arg1.AsInt++;

		//if (Arg2.type == 5 && Arg2.AsInt == min) Arg2.AsInt = max;
		if (Arg2.type == 5 && Arg2.AsInt == max) Arg2.AsInt = min;
		else if (Arg2.type == 5 && Arg2.AsInt >= min &&  Arg2.AsInt <= max) Arg2.AsInt++;
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
	void SetLast(SupData *A){
		for (int i = count - 1; i >= 0; i--){
			if (Triades[i].Arg2.type == -1){
				Triades[i].Arg2.Copy(A);
				break;
			}
			else if (Triades[i].Arg1.type == -1){
				Triades[i].Arg1.Copy(A);
				break;
			}
		}
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

	void ReplaceNumbers(int A, int B){
		for (int i = 0; i<count; i++){
			Triades[i].ReplaceNumbers(A, B);
		}
	}
};