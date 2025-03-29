#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>
#include "Transformare_Din_Postordine_In_Inordine.h"

int VerificarePrioritate(string s)
{
    int prioritate=10000;
    int paranteze=0;
    for(int i=0; s[i]!='\0'; i++)
    {
        string test(1,s[i]);
        if(s[i]=='(')
            paranteze++;
        else if(s[i]==')')
            paranteze--;
        else if(isOperator(test) && paranteze==0)
        {
            if(prioritati(test)<prioritate)
                prioritate=prioritati(test);
        }

    }
    return prioritate;
}

string Transformare_InOrdine(string ExpInordine)
{
    stack<string> s;

    for (int i=0; ExpInordine[i]!='\0'; i++)
    {
        if((ExpInordine[i]>='0' && ExpInordine[i]<='9') || (ExpInordine[i]=='-' && (ExpInordine[i+1]>='0' && ExpInordine[i+1]<='9')))  //verificare numar
        {
            string Numar(1,ExpInordine[i]);
            int j;
            for(j=i+1; ExpInordine[j]!='\0' && ( (ExpInordine[j]>='0' && ExpInordine[j]<='9') || ExpInordine[j]=='.'); j++)
            {
                string nr(1,ExpInordine[j]);
                Numar+=nr;
            }
            i=j-1;
            s.push(Numar);

        }
        else if (isalpha(ExpInordine[i]) && ExpInordine[i+1]>='0' && ExpInordine[i+1]<='9')   //verificare variabila indexata
        {
            string ElementCurent(1,ExpInordine[i]);
            int j;
            for( j=i+1; ExpInordine[j]!='\0' && ExpInordine[j]!=';'; j++)
            {
                string fct(1,ExpInordine[j]);
                ElementCurent+=fct;
            }
            i=j-1;
            s.push(ElementCurent);
        }

        else if (isalpha(ExpInordine[i]) && !isalnum(ExpInordine[i+1]))   //verificare variabila neindexata
        {
            string op(1, ExpInordine[i]);
            s.push(op);
        }
        else if(isalpha(ExpInordine[i]) && isalpha(ExpInordine[i+1]))    //va fi functie
        {
            string ElementCurent(1,ExpInordine[i]);
            int j;
            for( j=i+1; ExpInordine[j]!='\0' && ExpInordine[j]!=';'; j++)
            {
                string fct(1,ExpInordine[j]);
                ElementCurent+=fct;
            }
            i=j-1;
            string op1 = s.top();
            s.pop();
            if(ElementCurent=="neg")
            {
                int prioritate=VerificarePrioritate(op1);
                if(prioritate>4)
                    ElementCurent="-"+op1;
                else ElementCurent="-("+op1+")";
                s.push(ElementCurent);
            }
            else if(ElementCurent=="log")
            {
                string op2 = s.top();   //log(op2,op1)
                s.pop();
                ElementCurent=ElementCurent+"("+op2+","+op1+")";
                s.push(ElementCurent);

            }
            else
            {
                s.push(ElementCurent+"("+op1+")");
            }
        }

        //daca nu, la un operator construim in stiva expresia
        else if(!isalnum(ExpInordine[i]) &&ExpInordine[i]!=';')
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            string test(1,ExpInordine[i]);

            int prioritate2=VerificarePrioritate(op2);
            int prioritate1=VerificarePrioritate(op1);

            string Pune_Stiva;

            if(ExpInordine[i]!='/')
            {
                if(prioritate2<prioritati(test))
                    Pune_Stiva="("+op2+")"+ExpInordine[i];
                else Pune_Stiva=op2+ExpInordine[i];


                if(prioritate1<prioritati(test) || op1[0]=='-')
                    Pune_Stiva+="("+op1+")";
                else Pune_Stiva+=op1;

            }
            else
            {
                if(prioritate2<=prioritati(test))
                    Pune_Stiva="("+op2+")"+ExpInordine[i];
                else Pune_Stiva=op2+ExpInordine[i];

                if(prioritate1<=prioritati(test))
                    Pune_Stiva+="("+op1+")";
                else Pune_Stiva+=op1;
            }
            s.push(Pune_Stiva);


        }
    }

    //la final, singurul element din stiva va fi expresia infixata
    return s.top();
}
