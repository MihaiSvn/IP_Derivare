#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <graphics.h>

#include "Structuri.h"
#include "Verificare_Erori.h"





int Error_Check_Variabila(string s)
{
    if(s=="e")
    {
        outtextxy(0,80,"Eroare: Nu se poate deriva in functie de 'e'!");
        return 0;
    }
    else if(isNumber(s))
    {
        outtextxy(0,80,"Eroare: Nu se poate deriva in functie de un numar!");
        return 0;
    }
    else if(s.empty())
    {
        outtextxy(0,80,"Eroare: Nu a fost introdusa o variabila!");
        return 0;
    }

    for(int i=0; s[i+1]!='\0'; i++)
        if(isdigit(s[i]) && isalpha(s[i+1]))
        {
            outtextxy(0,80,"Eroare: Nu a fost introdusa o variabila corecta!");
            return 0;
        }

    for(int i=0; s[i]!='\0'; i++)
        if(isalpha(s[i]) && isalpha(s[i+1]))
        {
            outtextxy(0,80,"Eroare: Nu a fost introdusa o variabila corecta!");
            return 0;
        }

    for(int i=0; s[i]!='\0'; i++)
        if(!isalnum(s[i]))
        {
            outtextxy(0,80,"Eroare: Nu a fost introdusa o variabila corecta!");
            return 0;
        }


    return 1;
}
void Error_Check_Arbore(nod*radacina, bool&ok)
{

    if(radacina==NULL)
        return;
    Error_Check_Arbore(radacina->st, ok);
    Error_Check_Arbore(radacina->dr, ok);

    if(isOperator(radacina->val))
    {
        if(radacina->st==NULL || radacina->dr==NULL)
        {
            if(ok)
            {
                outtextxy(0,80,"Eroare!");
                ok=false;
                return;
            }

        }

        if(radacina->val=="/")   //verificare impartire la 0
        {
            if(radacina->dr->val=="0")
            {
                if(ok)
                {
                    outtextxy(0,80,"Eroare: Nu poti avea o fractie cu numitorul cu valoarea 0!");
                    ok=false;
                    return;
                }
            }
        }
    }
    else if(isFunction(radacina->val))
    {

        //verificare ca fiecare functie sa aiba nr de operatori
        int nr=NrFiiOperatie(radacina->val);
        if(nr==1)
        {
            if(radacina->st==NULL)
            {
                if(ok)
                {
                    outtextxy(0,80,"Eroare!");
                    ok=false;
                    return;
                }
            }
        }
        else if(nr==2)
        {
            if(radacina->st==NULL || radacina->dr==NULL)
            {
                if(ok)
                {
                    outtextxy(0,80,"Eroare!");
                    ok=false;
                    return;
                }
            }
        }

        if(radacina->val=="log")  //log(b,a), atunci conditiile care trebuie indeplinite sunt: b>0, b!=1 si a>0
        {
            string b=radacina->st->val;
            string a=radacina->dr->val;

            if(isNumber(b))
            {
                int nr1=String_To_Double(b);
                if(!(nr1>0 && nr1!=1))
                {
                    if(ok)
                    {
                        outtextxy(0,80,"Eroare: Logaritmul trebuie sa aiba baza un numar mai mare ca 0 si diferit de 1!");
                        ok=false;
                        return;
                    }
                }
            }

            if(isNumber(a))
            {
                int nr2=String_To_Double(a);
                if(!(nr2>0))
                {
                    if(ok)
                    {
                        outtextxy(0,80,"Eroare: Logaritmul trebuie sa aiba argumentul mai mare de 0!");
                        ok=false;
                        return;
                    }
                }
            }
        }


    }
    else
    {
        if(radacina->st!=NULL && radacina->dr!=NULL)
        {
            if(ok)
                {
                    outtextxy(0,80,"Eroare!");
                    ok=false;
                    return;
                }
        }
    }
}
