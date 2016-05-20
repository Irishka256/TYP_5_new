#include "stdafx.h"
#include <string.h>
#include "Defs.h"
#include "Scaner.h"

int i_mas=0;
int mass_str[100];
int fl=0;

TScaner:: TScaner(char * FileName) {
	GetData(FileName);
	PutUK(0);
	stroka=1;
}

TypeLex Keyword[MAX_KEYW]={"main","int", "double", "if","else", "typedef", "void"};
int IndexKeyword[MAX_KEYW]={TMain, TInt, TDouble, TIf, TElse, TTypedef, TVoid};

void TScaner::PutUK(int i){uk=i;} //������������ ���������
int TScaner::GetUK(void){return uk;} // ��������� ���������

void TScaner::PutStroka (int i){ //������������ ���������
	stroka =i;
} 

int TScaner::GetStroka (void){ // ��������� ���������
	return stroka ;
} 

void TScaner::PrintError(char * err, char * a) {
	int str=i_mas;
	if(i_mas!=0)
		for(int j=0;j<i_mas;j++)
			if(mass_str[j]>uk){
						str=j+1;
							break;
					}
			

	// ������ ��������� �� ������
	if (a[0]=='\0') printf("������ : %s %s  C����� %d\n",err,a,str+1);
	else printf("������ : %s. �������� ������ %s  C����� %d\n",err,a,str+1);
	//system("pause");
	//exit(0);
}

int TScaner::Scaner(TypeLex l) {
	int fl=0;
	int fl_len_const=0;
	int i; // ������� ����� �������
	for (i=0;i<MAX_LEX;i++) l[i]=0; //�������� ���� �������
	i=0; // ������� ����������� � ������� i

	start: // ��� ������������ ��������:
	while((t[uk]==' ') || (t[uk]=='\n') || (t[uk]=='\t')) {
		///////////////////////
		if (t[uk]=='\n'){
			if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}
			stroka++;
		}
		//////////////////////
		uk++;
	}
	// ������� ���������� ���������
	if ( (t[uk]=='/') && (t[uk+1]=='/') )
	{ // ������� �����������, ���� ���������� ����� �� "\n"
	uk=uk+2;
	while ( (t[uk]!='\n')/*&&(t[uk]!='\0')&&(t[uk]!='#')*/) uk++;
	///////////////////
		if (t[uk]=='\n'){

			if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}

		//stroka++;
		}
		//////////////////
	goto start;
	}
	
	// ������� ���������� ���������
	if ( (t[uk]=='/') && (t[uk+1]=='*') )
	{ 
		uk=uk+2;////////////////////////////////////////////////////////////////
		// ������� �����������, ���� ���������� ����� �� */
		while ( (t[uk]!='*')||(t[uk+1]!='/')) { 
			if(t[uk]=='#'||t[uk]=='\0') {fl=1; break;} 
			uk++; 
		} 
		if(fl){ 
			PrintError("������������ �����������",l); 
			return TError; 
		} 
		else{ uk=uk+2;} 
		goto start;
	}

	/*uk=uk+2;
	while ((t[uk]!='*')&&(t[uk+1]!='/')) 
		uk++;
	uk=uk+2;
	goto start;
	}*/


	if (t[uk]=='\0') {l[0]='#'; return TEnd;}
	
	if (Number)
	{
		l[i++]=t[uk++];
		while (Number)
			if (i<=MAX_CONST) l[i++]=t[uk++]; 
			else {uk++; fl_len_const=1;}
		if(!fl_len_const)
			return TConstInt10;
		else
		{PrintError("������� �������� ���������",l);  
				return TError; }
	}
	else if(LetterBig||LetterSmall){
		//���������� �������������
		l[i++]=t[uk++];
		while(Number||LetterBig||LetterSmall)
			if (i<MAX_LEX-1) l[i++]=t[uk++]; else uk++;
		
		//������� ������������� ��������
		int j; // �������� �� �������� �����
		for (j=0; j<MAX_KEYW; j++)
			if (strcmp(l,Keyword[j])==0) return IndexKeyword[j];
		return TIdent;
	}

	else if (t[uk]=='\'') { 
		uk++; // �� ����� �������� ������� ��������� 
		if (t[uk+1]!='\'') { 
			while( (t[uk]!='\'')&& (t[uk]!='\n')&& (t[uk]!='\0') && (t[uk]!='#') ){ 
				if (i<MAX_LEX-1) l[i++]=t[uk++]; 
				else uk++; // ������� ������������� �������� 
			} 
			/////////////////////
			if (t[uk]=='\n'){
				if(i_mas==0){
				mass_str[i_mas++]=uk;
			}
			else{
				for(int j=0;j<i_mas;j++)
					if(mass_str[j]==uk){
						fl=1;
							break;
					}
				if(!fl){
					mass_str[i_mas++]=uk;
				}
				fl=0;

			}
				//stroka++;
				//simvol=1;
			}
			///////////////////////
			if(t[uk]=='\'') 
				uk++; 
			PrintError("�������� ���������� ���������",l);  
			return TError; 
		} 
		else { 
			if (t[uk]!='\n'&&t[uk]!='\0')
			{l[i++]=t[uk++]; 
			uk++; // ����������� ������� 
			return TConstSymvol; 
			}else { 
				//simvol=simvol-i+1;
				if(t[uk]=='\n'){

					if(i_mas==0){
						mass_str[i_mas++]=uk;
					}
					else{
						for(int j=0;j<i_mas;j++)
							if(mass_str[j]==uk){
								fl=1;
								break;
							}
							if(!fl){
								mass_str[i_mas++]=uk;
							}

					}

					//simvol=1;
					//stroka++;
				}
				//else {
					PrintError("�������� ���������� ���������",l); 
					return TError; 
				}
		} 
	}

	/////////////////////////////////
	else if (t[uk]==',') { l[i++]=t[uk++]; return TZap; }
	else if (t[uk]==';') { l[i++]=t[uk++]; return TTochkaZap; }
	else if (t[uk]=='(') { l[i++]=t[uk++]; return TLSkob; }
	else if (t[uk]==')') { l[i++]=t[uk++]; return TRSkob; }
	else if (t[uk]=='{') { l[i++]=t[uk++]; return TLFigScob; }
	else if (t[uk]=='}') { l[i++]=t[uk++]; return TRFigScob; }
	else if (t[uk]=='[') { l[i++]=t[uk++]; return TLKvScob; }
	else if (t[uk]==']') { l[i++]=t[uk++]; return TRKvScob; }
	else if (t[uk]=='+') { l[i++]=t[uk++]; if (t[uk]=='+') { l[i++]=t[uk++]; return TPlusPlus; } return TPlus; }
	else if (t[uk]=='-') { l[i++]=t[uk++]; if (t[uk]=='-') { l[i++]=t[uk++]; return TMinusMinus; }return TMinus; }
	else if (t[uk]=='*') { l[i++]=t[uk++]; return TMul; }
	else if (t[uk]=='/') { l[i++]=t[uk++]; return TDiv; }
	else if (t[uk]=='%') { l[i++]=t[uk++]; return TMod; }
	else if (t[uk]=='<') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TMensheRavno; }return TMenshe; }
	else if (t[uk]=='>') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TBolsheRavno; }return TBolshe; }
	else if (t[uk]=='!') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TNeRavno ; }
	else { PrintError("�������� ������",l); // ������ 
	return TError;} }
	else if (t[uk]=='=') { l[i++]=t[uk++]; if (t[uk]=='=') { l[i++]=t[uk++]; return TRavno; } else return TPris; }
	else { PrintError("�������� ������",l); // ������
	//uk++;
	l[i++]=t[uk++]; //� �� ����� ������ �������, �� ������� ������
	return TError;
	}
}


void TScaner::GetData(char * FileName) {
	// ���� ����� FileName, ������� �������� ����� ��������� ������
	char aa;
	FILE * in = fopen(FileName,"r");
	if (in==NULL) { PrintError("����������� ������� ����",""); exit(1); }
	int i=0;
	while(!feof(in))
	{
	fscanf(in,"%c",&aa);
	if (!feof(in)) t[i++]=aa;
		if (i>=MAX_TEXT-1)
		{
			PrintError("������� ������� ������ ��������� ������","");
			break;
		}
	}
	t[i]='\0'; // ����������� ���� �\0� � ����� ������
	fclose(in);
} // ����� GetData()
