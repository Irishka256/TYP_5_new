#ifndef __DEFS
#define __DEFS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 10000 //макс длина текста ИМ
#define MAX_LEX 100 //макс длина лексемы
#define MAX_KEYW 7 // число ключевых слов
#define MAX_CONST 9 // 
#define MAX_N 8

#define LetterSmall ( (t[uk]>='a') && (t[uk]<='z') )
#define LetterBig ( (t[uk]>='A') && (t[uk]<='Z') )
#define Number ( (t[uk]>='0') && (t[uk]<='9') )

typedef char TypeMod[MAX_TEXT]; // текст ИМ
typedef char TypeLex[MAX_LEX]; // лексема


// Семантические подпрограммы
#define SemPushLex					400001 
#define SemPopLex					400002 
#define SemGetType					400003 
#define SemAddVar					400004 
#define SemPushTree					400005 
#define SemTreeNewBranch			400006 
#define SemTreeRestoreBranch		400007 //восстановление ветви
#define SemOverride					400008 
#define SemAddType					400009
#define SemLex2Tree					400010 
#define SemSetDim					400011 
#define SemLex2Int					400012 
#define SemIndexVyrBegin			410001
#define SemIndexVyrEnd				410002
#define SemIndexVyrStep				410003
#define SemPushInt					420001 
#define SemPushDouble				420002

#define SemVarDeclared				420013

// Команды добавления триад
#define AddTriadeNop				300000
#define AddTriadePlus				300001
#define AddTriadeMinus				300002
#define AddTriadeMul				300004 
#define AddTriadeDiv				300005
#define AddTriadeMod				300006
#define AddTriadeRavno				300007
#define AddTriadeNeRavno			300008
#define AddTriadeMenshe				300009
#define AddTriadeBolshe				300010
#define AddTriadeMensheRavno		300011
#define AddTriadeBolsheRavno		300012
#define AddTriadePris				300013
#define	AddTriadeIf					300014   ///////////////////для иф
#define AddTriadeGoto				300015   ///////////////////для иф
#define AddTriadeOffset				300016
#define AddTriadePlusPlus			300017
#define AddTriadeMinusMinus			300018
#define AddTriadeRet				310000

#define FormTriadeArg1				310001 
#define FormTriadeArg2				310002

#define PushLastTriade				320000 
#define PushNextTriade				320001 /////////////////////////////для иф


#define MagazCastling				500001 //////////////////////////////////МБ для иф????????????????????????7

// Операции в триадах
#define ONop	30000
#define OPlus	30001
#define OMinus	30002
#define OMul	30004
#define ODiv	30005
#define OMod	30006
#define ORavno	30007
#define ONeRavno 30008
#define OMenshe	30009
#define OBolshe	30010
#define OMensheRavno	30011
#define OBolsheRavno	30012
#define OPris	30013
#define	OIf		30014
#define OGoto	30015
#define OOffset	30016
#define OPlusPlus	30017
#define OMinusMinus	30018
#define ORet	31000



// Нетерминалы
#define NS			1000
#define NProgram	1001
#define NOpisPerem	1002 
#define NSpisPerem	1003 
#define NElemSpis	1004 
#define NSpisPerem2 1005 
#define NIndexInt   1025
#define NIndexVyr	1009 
#define NMassiv	    1006 
#define NMassiv1    1007
#define NMain		1008
#define NOper		1010
#define NOper1   	1011 
#define NPris		1012 
#define NVyr		1013
#define NVyr1      	1014
#define NVyr15		1015
#define NVyr2     	1016
#define NVyr25		1017
#define NVyr3 		1018
#define NVyr35		1019 
#define NVyr4     	1020
#define NVyr45		1021
#define NVyr5 		1022
#define NVyr55		1023 
#define NType 		1024 

#define NIf 		1026 
#define NH6 		1027 
#define NH7         1028 

#define NBlock         1029
#define NH8         1030
#define NH3         1031
#define NH4         1032
#define NH5         1033
#define NA         1034
#define NA1         1035
#define NA2        1036

//идентификаторы, константы и массивы
#define TIdent 1
#define TConstInt10 2
#define TConstSymvol 3

//ключевые слова
#define TInt 5
#define TDouble 6
#define TIf 7
#define TElse 8
#define TTypedef 9
#define TMain 4
#define TVoid 32

//специальные знаки
#define TZap 10
#define TLSkob 11
#define TRSkob 12
#define TLFigScob 13
#define TRFigScob 14
#define TTochkaZap 15
#define TLKvScob 30
#define TRKvScob 31

//знаки операций
#define TPlusPlus 16
#define TMinusMinus 17
#define TBolshe 18
#define TBolsheRavno 19
#define TMenshe 20
#define TMensheRavno 21
#define TRavno 22
#define TNeRavno 23
#define TPlus 24
#define TMinus 25
#define TMul 26
#define TDiv 27
#define TMod 28
#define TPris 29

//конец исходного модуля
#define TEnd 100

//ошибочный символ
#define TError 101

#endif