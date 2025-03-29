#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>

#include "CreareArboreSintaxa.h"
#include "Structuri.h"

nod* CreareArboreSintaxa(string s)
{
    nod *adresaRad;
    stack<nod*> Stiva;
    for(int i=0; s[i]!='\0'; i++)
    {
        if(s[i]>='0' && s[i]<='9')
        {
            string Numar;
            int j;
            for(j=i; s[j]!='\0' && (s[j]>='0' && s[j]<='9' || s[j]=='.');j++)
            {
                string nr(1,s[j]);
                Numar+=nr;
            }
            i=j-1;
            nod *x= new nod;
            x->val=Numar;
            x->st = NULL;
            x->dr = NULL;
            x->parinte=NULL;
            Stiva.push(x);
        }
        else if(isalpha(s[i]) && !isalnum(s[i+1]))   //daca este doar o variabila neindexata
        {
            //nod *x;
            nod *x= new nod;
            string op(1,s[i]);
            x->val=op;
            x->st = NULL;
            x->dr = NULL;
            x->parinte=NULL;
            Stiva.push(x);
        }
        else if(isalpha(s[i]) && s[i+1]>='0' && s[i+1]<='9')  //daca este doar o variabila indexata
        {
            string ElementCurent(1,s[i]);
            int j;
            for( j=i+1; s[j]!='\0' && s[j]!=';';j++)
            {
                string fct(1,s[j]);
                ElementCurent+=fct;
            }
            i=j-1;
            nod *x= new nod;
            x->val=ElementCurent;
            x->st = NULL;
            x->dr = NULL;
            x->parinte=NULL;
            Stiva.push(x);
        }
        else if(s[i]!=';')        //va fi operator
        {
            string ElementCurent;
            int j;
            for( j=i; s[j]!='\0' && s[j]!=';';j++)
            {
                string fct(1,s[j]);
                ElementCurent+=fct;
            }
            i=j-1;
            //dreapta= new nod;

            if(NrFiiOperatie(ElementCurent)==2)
            {
                nod *dreapta=new nod;
                dreapta = Stiva.top();
                Stiva.pop();

                //stanga = new nod;

                nod * stanga=new nod;
                stanga= Stiva.top();
                Stiva.pop();

                //x = new nod;
                nod *x=new nod;

                x->val = ElementCurent;
                x->st = stanga;
                x->dr = dreapta;
                x->parinte=NULL;
                stanga->parinte=x;
                dreapta->parinte=x;
                Stiva.push(x);
                adresaRad=x;
            }
            else if(NrFiiOperatie(ElementCurent)==1)
            {
                nod * stanga=new nod;
                stanga = Stiva.top();
                Stiva.pop();

                nod *x=new nod;
                x->val = ElementCurent;
                x->st = stanga;
                x->dr = NULL;
                x->parinte=NULL;
                x->st->parinte=x;

                Stiva.push(x);
                adresaRad=x;
            }

        }
    }
    if(!Stiva.empty())   //daca este doar un numar in stiva, adica daca input ul e doar o expresie de genul: 5 sau x (fara operatori), va ramane in stiva si va da eroare. Astfel, ii dam top pt ca adresarad sa aiba o valoare
        adresaRad=Stiva.top();
    return adresaRad;
}
