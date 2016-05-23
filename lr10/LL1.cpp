#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "Defs.h"
#include "Scaner.h"
#include "LL1.h"
#include "sup.h"
#include "tree.h"

//проблема с ++, --

Code TheCode;

int m[MAX_TEXT], z = 0; //мазагин LL1-анализатора и указатель магазина
SupData *m2[MAX_TEXT], bufer;
int z2 = -1, type/*, fl = 1*/;
tree *tr;

tree *pt;

int Counter = 0;

void TreeNamesGenerator(tree *t){
	if (t == nullptr) return;
	if (strlen(t->n->id) > 0){
		sprintf(t->n->Name, "ID%d%s", Counter++, t->n->id);
	}
	TreeNamesGenerator(t->left);
	TreeNamesGenerator(t->right);
}


void LL1::epsilon() //обработка правил с пустой правой частью
{/*z--;*/
}

void LL1::Osh(int m) {
	switch (m){
	case 2:
		std::cout << "Ожидалась константа" << std::endl;
		break;
	case 4:
		std::cout << "Ожидался main" << std::endl;
		break;
	case 11:
		std::cout << "Ожидалась (" << std::endl;
		break;
	case 12:
		std::cout << "Ожидалась )" << std::endl;
		break;
	case 13:
		std::cout << "Ожидалась {" << std::endl;
		break;
	case 14:
		std::cout << "Ожидалась }" << std::endl;
		break;
	case 15:
		std::cout << "Ожидалась ;" << std::endl;
		break;
	case 29:
		std::cout << "Ожидалось =" << std::endl;
		break;
	case 30:
		std::cout << "Ожидалась [" << std::endl;
		break;
	case 31:
		std::cout << "Ожидалась ]" << std::endl;
		break;
	case 100:
		std::cout << "Ожидался конец файла" << std::endl;
		break;
	case 1001:
		std::cout << "Ожидалась программа" << std::endl;
		break;
	case 1002:
		std::cout << "Ожидался тип" << std::endl;
		break;
	case 1003:
		std::cout << "Ожидался идентификатор" << std::endl;
		break;
	case 1005:
		std::cout << "Ожидалось выражение" << std::endl;
		break;
	case 1006:
		std::cout << "Ожидался тип" << std::endl;
		break;
	case 1021:
		std::cout << "Ожидалось выражение" << std::endl;
		break;
	case 1029:
		std::cout << "Ожидалось описание типа, или элемент массива, или присваивание" << std::endl;
		break;
	case 1030:
		std::cout << "Ожидалась константа или символ {" << std::endl;
		break;
	default:
		break;
	}
}

int LL1::LL_1() {
	int fl = 1, i, uk1;
	TypeLex l;
	TScaner * sc;
	sc = new TScaner("input.txt");// файл по умолчанию
	int type;
	m[z] = NS;
	type = sc->Scaner(l);
	pt = tr = new tree();
	while (fl){
		if (m[z] < NS){ //в вершущке магазина терминал? (<=)
			// в вершушке мазазина терминал
			if (m[z] == type)
			{
				// верхушка совпадает с отсканированным терминалом
				if (type == TEnd || type == TError) fl = 0;
				else {
					type = sc->Scaner(l); // сканируем новый символ
					z--; // стираем верхушку магазина
				}
			}
			else
			{ // обнаружена ошибка
				sc->PrintError("Неверный символ", l);
				Osh(m[z]);
				fl = 0;
				TheCode.error = true;
				return -1;
			}
		}
		else{ //в верхушке магазина нетерминал
			switch (m[z]){ //по нетерминалу в верхушке магазина


			case AddTriadeNop:
				TheCode.AddTriade(ONop, nullptr, nullptr);
				break;
			case AddTriadePlus:
				TheCode.AddTriade(OPlus, nullptr, nullptr);
				break;
			case AddTriadeMinus:
				TheCode.AddTriade(OMinus, nullptr, nullptr);
				break;
			case AddTriadeMul:
				TheCode.AddTriade(OMul, nullptr, nullptr);
				break;
			case AddTriadeDiv:
				TheCode.AddTriade(ODiv, nullptr, nullptr);
				break;
			case AddTriadeMod:
				TheCode.AddTriade(OMod, nullptr, nullptr);
				break;
			case AddTriadeRavno:
				TheCode.AddTriade(ORavno, nullptr, nullptr);
				break;
			case AddTriadeNeRavno:
				TheCode.AddTriade(ONeRavno, nullptr, nullptr);
				break;
			case AddTriadeMenshe:
				TheCode.AddTriade(OMenshe, nullptr, nullptr);
				break;
			case AddTriadeBolshe:
				TheCode.AddTriade(OBolshe, nullptr, nullptr);
				break;
			case AddTriadeMensheRavno:
				TheCode.AddTriade(OMensheRavno, nullptr, nullptr);
				break;
			case AddTriadeBolsheRavno:
				TheCode.AddTriade(OBolsheRavno, nullptr, nullptr);
				break;
			case AddTriadePris:
				TheCode.AddTriade(OPris, nullptr, nullptr);
				break;
			case AddTriadeGoto: /////////////////////////////////////////////для иф
				TheCode.AddTriade(OGoto, nullptr, nullptr);
				break;
			case AddTriadeIf:////////////////////////////////////////////////для иф
				TheCode.AddTriade(OIf, nullptr, nullptr);
				break;
			case AddTriadeOffset:
				TheCode.AddTriade(OOffset, nullptr, nullptr);
				break;
			case AddTriadePlusPlus:
				TheCode.AddTriade(OPlusPlus, nullptr, nullptr);
				break;
			case AddTriadeMinusMinus:
				TheCode.AddTriade(OMinusMinus, nullptr, nullptr);
				break;
			case AddTriadeRet:
				TheCode.AddTriade(ORet, nullptr, nullptr);
				break;
			case FormTriadeArg1:
				TheCode.SetLastArg1(m2[z2 - 1]);
				z2--;
				break;
			case FormTriadeArg2:
				TheCode.SetLastArg2(m2[z2 - 1]);
				z2--;
				break;
			case PushLastTriade:
				m2[z2++] = new SupData(TheCode.count - 1, true);
				break;
			case PushNextTriade://////////////////////////////////////////////////для иф
				m2[z2++] = new SupData(TheCode.count, true);
				break;
			case SemPushLex:
				m2[z2++] = new SupData(l);
				break;
			case SemPushInt:
				m2[z2++] = new SupData(atoi(l));
				break;
			case SemPushDouble:
				m2[z2++] = new SupData(atof(l));
				break;
			case SemPopLex:
				delete m2[z2 - 1];
				z2--;
				break;
			case SemGetType:
				if (pt->sem_get_type(m2[z2 - 1]->AsString, sc->GetStroka()) == false){
					TheCode.error = true;
				}
				break;
			case SemVarDeclared://///////////////////////////////////////////////////////////////////////////////////
				if (pt->sem_var_declared(m2[z2 - 1]->AsString, sc->GetStroka()) == false){
					TheCode.error = true;
				}
				break;
			case SemAddVar:
				pt = pt->sem_add_var(m2[z2 - 1]->AsString, m2[z2 - 2]->AsString);
				break;
			case SemAddType:
				pt = pt->sem_add_type(m2[z2 - 1]->AsString, m2[z2 - 2]->AsString);
				break;
			case SemPushTree:
				m2[z2++] = new SupData(pt);
				break;
			case SemTreeNewBranch:
				pt->set_right(new node());
				pt = pt->right;
				break;
			case SemTreeRestoreBranch:
				pt = m2[z2 - 1]->AsTreeNode;
				z2--;
				break;
			case SemOverride:
				if (pt->sem_override(m2[z2 - 1]->AsString, sc->GetStroka())){
					TheCode.error = true;
				}
				break;
			case SemLex2Tree:
				m2[z2 - 1] = new SupData(pt->find_up(m2[z2 - 1]->AsString));
				break;
			case SemLex2Int:
				m2[z2 - 1] = new SupData(atoi(m2[z2 - 1]->AsString));
				break;
			case SemSetDim:
				m2[z2 - 2]->AsTreeNode->sem_set_dim(m2[z2 - 1]->AsInt, sc->GetStroka());
				z2--;
				break;
			case SemIndexVyrBegin:
				m2[z2++] = new SupData((int)0);
				m2[z2++] = new SupData((int)0);
				break;
			case SemIndexVyrEnd:
				if (TheCode.error == false){ ///////////////////////////////чтобы не вылетал с исключением на массивах
					if (pt->sem_arr_rank(m2[z2 - 3]->AsTreeNode->n->id, m2[z2 - 1]->AsInt, sc->GetStroka())){
						TheCode.error = true;
					}
					if (m2[z2 - 1]->AsInt > 0){
						z2--;
						m[z++] = PushLastTriade;
						m[z++] = FormTriadeArg1;
						m[z++] = FormTriadeArg2;
						m[z++] = AddTriadeOffset;
					}
					else{
						z2--;
						z2--;
					}
				}
				break;
			case SemIndexVyrStep:
			{
				if (TheCode.error == false){ ///////////////////////////////чтобы не вылетал с исключением на массивах
					int multer = 1;
					for (int i = (m2[z2 - 2]->AsInt); i<(m2[z2 - 4]->AsTreeNode->n->N - 1); i++){
						multer *= m2[z2 - 4]->AsTreeNode->n->hg[i];
					}
					TheCode.AddTriade(OMul, m2[z2 - 1], new SupData(multer));
				}
			}
				if (m2[z2 - 2]->AsInt > 0){
					TheCode.AddTriade(OPlus, m2[z2 - 3], new SupData(TheCode.count - 1, true));
				}
				m2[z2 - 2]->AsInt++;
				m2[z2 - 3] = new SupData(TheCode.count - 1, true);
				z2--;
				break;
			case MagazCastling:   //////////////////////////////////МБ для иф????????????????????????7
				bufer.Copy(m2[z2 - 1]);
				m2[z2 - 1]->Copy(m2[z2 - 2]);
				m2[z2 - 2]->Copy(&bufer);
				break;




			case NS:
				m[z++] = TEnd;
				m[z++] = NProgram;
				break;
			case NProgram:
				if (type == TIdent){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				else if (type == TTypedef){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NMassiv;
				}
				else if (type == TVoid){
					m[z++] = NProgram;
					m[z++] = NMain;
				}
				else if (type == TInt){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				else if (type == TDouble){
					m[z++] = NProgram;
					m[z++] = TTochkaZap;
					m[z++] = NOpisPerem;
				}
				break;
			case NOpisPerem:
				if (type == TInt || type == TDouble){
					m[z++] = SemPopLex;
					m[z++] = NSpisPerem;
					m[z++] = type;
					m[z++] = SemPushLex;
				}
				else if (type == TIdent){
					m[z++] = SemPopLex;
					m[z++] = NSpisPerem;
					m[z++] = SemGetType;
					m[z++] = type;
					m[z++] = SemPushLex;
				}
				else {
					sc->PrintError("Неверный символ", l);
					Osh(m[z]);
					return -1;
				}
				break;
			case NSpisPerem:
				if (type == TIdent){
					m[z++] = NSpisPerem2;
					m[z++] = SemPopLex;
					m[z++] = NElemSpis;
					m[z++] = TIdent;
					m[z++] = SemLex2Tree;
					m[z++] = SemAddVar;
					m[z++] = SemOverride;
					m[z++] = SemPushLex;
				}
				else {
					sc->PrintError("Неверный символ", l);
					Osh(m[z]);
					return -1;
				}
				break;
			case NElemSpis:
				if (type == TPris){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg1;
					m[z++] = FormTriadeArg2;
					m[z++] = AddTriadePris;
					m[z++] = NVyr;
					m[z++] = TPris;
				}
				else if (type == TTochkaZap){
					epsilon();
				}
				else if (type == TLKvScob){
					m[z++] = NIndexInt;
				}
				break;
			case NSpisPerem2:
				if (type == TTochkaZap){
					epsilon();
				}
				else if (type == TZap){
					m[z++] = NSpisPerem;
					m[z++] = TZap;
				}
				break;
			case NIndexInt:
				if (type == TTochkaZap){
					epsilon();
				}
				else if (type == TLKvScob){
					m[z++] = NIndexInt;
					m[z++] = TRKvScob;
					m[z++] = SemSetDim;
					m[z++] = TConstInt10;
					m[z++] = SemLex2Int;
					m[z++] = SemPushLex;
					m[z++] = TLKvScob;
				}
				break;
			case NIndexVyr:
				if (type == TPlus || type == TPlusPlus || type == TMinus ||
					type == TMinusMinus || type == TMul || type == TDiv || type == TMod || type == TMenshe ||
					type == TMensheRavno || type == TBolshe || type == TBolsheRavno || type == TPris || type == TRavno ||
					type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob){
					epsilon();
				}
				else if (type == TLKvScob){
					m[z++] = NIndexVyr;
					m[z++] = TRKvScob;
					m[z++] = SemIndexVyrStep;
					m[z++] = NVyr;
					m[z++] = TLKvScob;
				}
				else if (type == TRKvScob){
					epsilon();
				}break;
			case NMain:
				if (type == TVoid){
					m[z++] = SemTreeRestoreBranch;
					m[z++] = AddTriadeRet;
					m[z++] = TRFigScob;
					m[z++] = NOper;
					m[z++] = TLFigScob;
					m[z++] = TRSkob;
					m[z++] = TLSkob;
					m[z++] = TMain;
					m[z++] = TVoid;
					m[z++] = SemTreeNewBranch;
					m[z++] = SemPushTree;
				}break;
			case NMassiv:
				if (type == TTypedef){
					m[z++] = NMassiv1;
					m[z++] = TTypedef;
				}break;
			case NMassiv1:
				if (type == TInt || type == TDouble || type == TIdent){
					m[z++] = SemPopLex;
					m[z++] = SemPopLex;
					m[z++] = NIndexInt;
					m[z++] = SemLex2Tree;
					m[z++] = SemAddType;
					m[z++] = SemOverride;
					m[z++] = TIdent;
					m[z++] = SemPushLex;
					m[z++] = type;
					m[z++] = SemPushLex;
				}break;
			case NOper: 
				if (type == TIdent || type == TIf || type == TInt || type == TDouble ||
					type == TTochkaZap || type == TLFigScob){
					m[z++] = NOper;
					m[z++] = NOper1;
				}
				else if (type == TRFigScob){
					epsilon();
				}
				break;
			case NOper1:
				if (type == TIdent){
					m[z++] = NPris;
					
					m[z++] = TIdent;
					m[z++] = SemLex2Tree;
					m[z++] = SemVarDeclared; ///////////////////////////тут вставила, чтобы когда была переменная необъявлена, выводилась ошибка
					m[z++] = SemPushLex;
				}
				else if (type == TIf){
					m[z++] = NIf;
				}
				else if (type == TInt){
					m[z++] = NSpisPerem;
					m[z++] = type;
					m[z++] = SemPushLex;
				}
				else if (type == TDouble){
					m[z++] = NSpisPerem;
					m[z++] = type;
					m[z++] = SemPushLex;
				}
				else if (type == TTochkaZap){
					m[z++] = TTochkaZap;
				}
				else if (type == TLFigScob){
					m[z++] = TRFigScob;
					m[z++] = SemTreeRestoreBranch;
					m[z++] = NOper;
					m[z++] = SemTreeNewBranch;
					m[z++] = SemPushTree;
					m[z++] = TLFigScob;
				}
				break;
			case NPris:
				if (type == TIdent){
					m[z++] = NElemSpis;
					m[z++] = TIdent;
					//m[z++] = SemVarDeclared;
					m[z++] = SemGetType;
				}
				else if (type == TPris){
					m[z++] = FormTriadeArg1;
					m[z++] = FormTriadeArg2;
					m[z++] = AddTriadePris;
					m[z++] = NVyr;
					//m[z++] = SemVarDeclared;
					m[z++] = TPris;
				}
				else if (type == TLKvScob){
					m[z++] = FormTriadeArg1;
					m[z++] = FormTriadeArg2;
					m[z++] = AddTriadePris;
					m[z++] = NVyr;
					m[z++] = TPris;
					m[z++] = SemIndexVyrEnd;
					m[z++] = NIndexVyr;
					m[z++] = SemIndexVyrBegin;
				}
				break;
			case NVyr:
				if (type == TIdent){
					m[z++] = NVyr1;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr1;
				}
				else if (type == TPlus){
					m[z++] = NVyr1;
					m[z++] = TPlus;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr1;
				}
				else if (type == TMinus){
					m[z++] = NVyr1;
					m[z++] = TMinus;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr1;
				}
				else if (type == TLSkob){
					m[z++] = NVyr1;
				}break;
			case NVyr1:
				if (type == TIdent){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				else if (type == TLSkob){
					m[z++] = NVyr15;
					m[z++] = NVyr2;
				}
				break;
			case NVyr15:
				if (type == TPlus){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadePlus;
					m[z++] = NVyr1;
					m[z++] = TPlus;
				}
				else if (type == TMinus){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMinus;
					m[z++] = NVyr1;
					m[z++] = TMinus;
				}
				else if (type == TMul || type == TDiv || type == TMod || type == TMenshe ||
					type == TMensheRavno || type == TBolshe || type == TBolsheRavno || type == TRavno || type == TNeRavno ||

					type == TTochkaZap || type == TZap || type == TRSkob || type == TRKvScob){
					epsilon();
				}break;
			case NVyr2:
				if (type == TIdent){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				else if (type == TLSkob){
					m[z++] = NVyr25;
					m[z++] = NVyr3;
				}
				break;
			case NVyr25:
				if (type == TPlus || type == TMinus){
					epsilon();
				}
				else if (type == TMul){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMul;
					m[z++] = NVyr2;
					m[z++] = TMul;
				}
				else if (type == TDiv){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeDiv;
					m[z++] = NVyr2;
					m[z++] = TDiv;
				}
				else if (type == TMod){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMod;
					m[z++] = NVyr2;
					m[z++] = TMod;
				}
				else if (type == TMenshe || type == TMensheRavno || type == TBolshe || type == TBolsheRavno ||
					type == TRavno || type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob ||
					type == TRKvScob){
					epsilon();
				}
				break;
			case NVyr3:
				if (type == TIdent){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}
				else if (type == TLSkob){
					m[z++] = NVyr35;
					m[z++] = NVyr4;
				}break;
			case NVyr35:
				if (type == TPlus || type == TMinus || type == TMinusMinus || type == TMul || type == TDiv ||
					type == TMod){
					epsilon();
				}
				else if (type == TMenshe){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMenshe;
					m[z++] = NVyr4;
					m[z++] = TMenshe;
				}
				else if (type == TMensheRavno){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMensheRavno;
					m[z++] = NVyr4;
					m[z++] = TMensheRavno;
				}
				else if (type == TBolshe){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeBolshe;
					m[z++] = NVyr4;
					m[z++] = TBolshe;
				}
				else if (type == TBolsheRavno){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeBolsheRavno;
					m[z++] = NVyr4;
					m[z++] = TBolsheRavno;
				}
				else if (type == TRavno || type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob || type == TRKvScob){
					epsilon();
				}break;
			case NVyr4:
				if (type == TIdent){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TConstInt10){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TPlusPlus){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TMinusMinus){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}
				else if (type == TLSkob){
					m[z++] = NVyr45;
					m[z++] = NVyr5;
				}break;
			case NVyr45:
				if (type == TPlus || type == TMinus || type == TMinusMinus || type == TMul || type == TDiv ||
					type == TMod || type == TMenshe || type == TMensheRavno || type == TBolshe || type == TBolsheRavno){
					epsilon();
				}
				else if (type == TRavno){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeRavno;
					m[z++] = NVyr5;
					m[z++] = TRavno;
				}
				else if (type == TNeRavno){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg2;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeNeRavno;
					m[z++] = NVyr5;
					m[z++] = TNeRavno;
				}
				else if (type == TTochkaZap || type == TZap || type == TRSkob || type == TRKvScob){
					epsilon();
				}
				break;
			case NVyr5:
				if (type == TIdent){
					m[z++] = NVyr55;
					m[z++] = SemIndexVyrEnd;
					m[z++] = NIndexVyr;
					m[z++] = SemIndexVyrBegin;
					m[z++] = TIdent;
					m[z++] = SemLex2Tree;
					m[z++] = SemPushLex;
				}
				else if (type == TConstInt10){
					m[z++] = TConstInt10;
					m[z++] = SemPushInt;
				}
				else if (type == TPlusPlus){
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadePlusPlus;
					m[z++] = SemIndexVyrEnd;
					m[z++] = NIndexVyr;
					m[z++] = SemIndexVyrBegin;
					m[z++] = TIdent;
					m[z++] = SemLex2Tree;
					m[z++] = SemPushLex;
					m[z++] = SemLex2Tree;
					m[z++] = SemPushLex;
					m[z++] = TPlusPlus;
				}
				else if (type == TMinusMinus){
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMinusMinus;
					m[z++] = SemIndexVyrEnd;
					m[z++] = NIndexVyr;
					m[z++] = SemIndexVyrBegin;
					m[z++] = TIdent;
					m[z++] = SemLex2Tree;
					m[z++] = SemPushLex;
					m[z++] = SemLex2Tree;
					m[z++] = SemPushLex;
					m[z++] = TMinusMinus;
				}
				else if (type == TLSkob){
					m[z++] = TRSkob;
					m[z++] = NVyr;
					m[z++] = TLSkob;
				}break;
			case NVyr55:
				if (type == TPlus){
					epsilon();
				}
				else if (type == TPlusPlus){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadePlusPlus;
					m[z++] = TPlusPlus;
				}
				else if (type == TMinus){
					epsilon();
				}
				else if (type == TMinusMinus){
					m[z++] = PushLastTriade;
					m[z++] = FormTriadeArg1;
					m[z++] = AddTriadeMinusMinus;
					m[z++] = TMinusMinus;
				}
				else if (type == TMul || type == TDiv || type == TMod || type == TMenshe || type == TMensheRavno ||
					type == TBolshe || type == TBolsheRavno){
					epsilon();
				}
				else if (type == TPris){
					m[z++] = NVyr;
					m[z++] = TPris;
				}
				else if (type == TRavno || type == TNeRavno || type == TTochkaZap || type == TZap || type == TRSkob ||
					type == TRKvScob){
					epsilon();
				}break;
			case NIf:
				m[z++] = NH6;
				m[z++] = NOper1;
				m[z++] = TRSkob;
				m[z++] = NVyr;
				m[z++] = TLSkob;
				m[z++] = TIf;
				break;
			case NH6:
				if (type == TElse){
					m[z++] = NH7;
					m[z++] = TElse;
				}
				break;
			case NH7:
				if (type == TIf){
					m[z++] = NIf;
				}
				else
				{
					m[z++] = NOper1;
				}
				break;
			case NType:
				if (type == TIdent){
					m[z++] = TIdent;
				}
				else if (type == TInt){
					m[z++] = TInt;
				}
				else if (type == TDouble){
					m[z++] = TDouble;
				}break;
			default:
				break;
			}
			z--;
		}
	}
	/*if (type == TEnd) printf("Синтаксических ошибок не обнаружено\n");
	else sc->PrintError("Лишний текст в конце программы", "");*/

	TreeNamesGenerator(tr);


	if (TheCode.error == false){
		TheCode.Print();
	}
}
