#ifndef DETECTAREFUNCTII+PRIORITATIFUNCTII_H_INCLUDED
#define DETECTAREFUNCTII+PRIORITATIFUNCTII_H_INCLUDED

using namespace std;

int isFunction(string c);
int NrFiiOperatie(string c);
int prioritati(string c);

int verifcareExpresieSinus(char c1, char c2, char c3);
int verifcareExpresieCosinus(char c1, char c2, char c3);
int verifcareExpresieTangenta(char c1, char c2);
int verificareExpresieCotangenta(char c1,char c2,char c3);
int verifcareExpresieArcsinus(char c1,char c2,char c3,char c4,char c5,char c6);
int verifcareExpresieArccosinus(char c1,char c2,char c3,char c4,char c5,char c6);
int verifcareExpresieArctangenta(char c1,char c2,char c3,char c4,char c5);
int verifcareExpresieArccotangenta(char c1,char c2,char c3,char c4,char c5,char c6);
int verifcareExpresieNegatie(char c1,char c2,char c3);

int verifcareExpresieSqrt(char c1,char c2,char c3,char c4);

int verifcareExpresieLog(char c1, char c2, char c3 );
int verifcareExpresieLn(char c1, char c2);
int verifcareExpresieLg(char c1, char c2);
#endif // DETECTAREFUNCTII+PRIORITATIFUNCTII_H_INCLUDED
