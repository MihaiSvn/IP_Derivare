#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>
#include "DetectareFunctii+PrioritatiFunctii.h"

string Functii[]={
"sin",          //ar=1
"cos",          //ar=1
"tg",           //ar=1
"ctg",          //ar=1
"arcsin",       //ar=1
"arccos",       //ar=1
"arctg",        //ar=1
"arcctg",       //ar=1
"sqrt",         //ar=1
"log",          //ar=2
"ln",           //ar=1
"lg",            //ar=1
"neg"           //ar=1
};
int isFunction(string c)
{
    for(int i=0;i<sizeof(Functii)/sizeof(Functii[0]);i++)
        if(c==Functii[i])
            return 1;
    return 0;
}
int NrFiiOperatie(string c)
{
    if(isFunction(c) && c!="log")
        return 1;
    if(c=="+" || c=="-" || c=="^" || c=="/" || c=="*" || c=="log")
        return 2;
}

int prioritati(string c)
{
    if(isFunction(c))
        return 4;
    if(c=="^")
        return 3;
    if(c=="/" || c=="*")
        return 2;
    else if(c=="+" || c=="-")
        return 1;
    return -1;
}

int verifcareExpresieSinus(char c1, char c2, char c3)
{
    if((c1=='s' || c1=='S') && (c2=='i'  || c2=='I') && (c3=='n' || c3=='N'))
        return 1;
    return 0;
}

int verifcareExpresieCosinus(char c1, char c2, char c3)
{
    if((c1=='c' || c1=='C') && (c2=='o'  || c2=='O') && (c3=='s' || c3=='S'))
        return 1;
    return 0;
}


int verifcareExpresieTangenta(char c1, char c2)
{
    if((c1=='t' || c1=='T') && (c2=='g'  || c2=='G'))
        return 1;
    return 0;
}

int verificareExpresieCotangenta(char c1,char c2,char c3)
{
    if((c1=='c' || c1=='C') && (c2=='t'  || c2=='T') && (c3=='g' || c3=='G'))
        return 1;
    return 0;
}

int verifcareExpresieArcsinus(char c1,char c2,char c3,char c4,char c5,char c6)
{
    if((c1=='a' || c1=='A') && (c2=='r' || c2=='R') && (c3=='c' || c3=='C') && (c4=='s' || c4=='S') && (c5=='i'  || c5=='I') && (c6=='n' || c6=='N'))
        return 1;
    return 0;
}

int verifcareExpresieArccosinus(char c1,char c2,char c3,char c4,char c5,char c6)
{
    if((c1=='a' || c1=='A') && (c2=='r' || c2=='R') && (c3=='c' || c3=='C') && (c4=='c' || c4=='C') && (c5=='o'  || c5=='O') && (c6=='s' || c6=='S'))
        return 1;
    return 0;
}

int verifcareExpresieArctangenta(char c1,char c2,char c3,char c4,char c5)
{
    if((c1=='a' || c1=='A') && (c2=='r' || c2=='R') && (c3=='c' || c3=='C') && (c4=='t' || c4=='T') && (c5=='g'  || c5=='G'))
        return 1;
    return 0;
}

int verifcareExpresieArccotangenta(char c1,char c2,char c3,char c4,char c5,char c6)
{
    if((c1=='a' || c1=='A') && (c2=='r' || c2=='R') && (c3=='c' || c3=='C') && (c4=='c' || c4=='C') && (c5=='t'  || c5=='T') && (c6=='g' || c6=='G'))
        return 1;
    return 0;
}

int verifcareExpresieSqrt(char c1,char c2,char c3,char c4)
{
    if((c1=='s' || c1=='S') && (c2=='q'  || c2=='Q') && (c3=='r' || c3=='R') && (c4=='t' || c4=='T'))
        return 1;
    return 0;
}
int verifcareExpresieLog(char c1, char c2, char c3)
{
    if((c1=='l' || c1=='L') && (c2=='o'  || c2=='O') && (c3=='g' || c3=='G'))
        return 1;
    return 0;
}

int verifcareExpresieLn(char c1, char c2)
{
    if((c1=='l' || c1=='L') && (c2=='n'  || c2=='N'))
        return 1;
    return 0;
}

int verifcareExpresieLg(char c1, char c2)
{
    if((c1=='l' || c1=='L') && (c2=='g'  || c2=='G'))
        return 1;
    return 0;
}

int verifcareExpresieNegatie(char c1, char c2, char c3)
{
    if((c1=='n' || c1=='N') && (c2=='e' || c2=='E') && (c3=='g' || c3=='G'))
        return 1;
    return 0;
}
