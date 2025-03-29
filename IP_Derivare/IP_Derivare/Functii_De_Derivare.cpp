#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>
#include <queue>

#include "Structuri.h"
#include "Functii_De_Derivare.h"



void setare_parinti(nod*radacina)
{
    if(radacina==NULL)
        return;
    if(radacina->st!=NULL)
    {
        radacina->st->parinte=radacina;
        setare_parinti(radacina->st);
    }
    if(radacina->dr!=NULL)
    {
        radacina->dr->parinte=radacina;
        setare_parinti(radacina->dr);
    }
}
void Derivare(nod*&radacina, string variabila);
int Parcurgere_Gasire_Variabila(nod*radacina, string variabila)
{
    queue<nod*> Coada;
    nod *p;
    Coada.push(radacina);
    while(!Coada.empty())
    {
        p=Coada.front();
        if(p->val==variabila)
            return 1;
        if(p->st)
            Coada.push(p->st);
        if(p->dr)
            Coada.push(p->dr);
        Coada.pop();

    }
    return 0;
}
nod* DuplicareDinNod(nod* radacina)
{
    if(radacina==NULL)
        return NULL;
    nod* NodClona = new nod;
    NodClona->val = radacina->val;
    NodClona->st=DuplicareDinNod(radacina->st);
    NodClona->dr=DuplicareDinNod(radacina->dr);
    return NodClona;



}
void Derivare_Variabila(nod*&radacina)
{
    radacina->val="1";
}
void Derivare_Constanta(nod*&radacina)
{
    radacina->val="0";
}
void Derivare_Suma(nod*&radacina, string variabila)
{
    Derivare(radacina->st,variabila);
    Derivare(radacina->dr,variabila);
}
void Derivare_Diferenta(nod*&radacina, string variabila)
{
    Derivare(radacina->st,variabila);
    Derivare(radacina->dr,variabila);
}

void Derivare_Produs(nod*&radacina,string variabila)   // (f(x)*g(x))' = f'(x)*g(x) + f(x)*g'(x)
{

    nod*n1= new nod;
    nod *n2=new nod;

    n1->val="*";
    n2->val="*";



    nod *n3=new nod;
    nod *n4=new nod;
    nod*n5=new nod;
    nod*n6=new nod;

    n3=DuplicareDinNod(radacina->st);  //de derivat
    n4=DuplicareDinNod(radacina->dr);
    n5=DuplicareDinNod(radacina->st);
    n6=DuplicareDinNod(radacina->dr);  //de derivat

    n2->st=n5;
    n2->dr=n6;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    radacina->st=NULL;
    delete radacina->dr;
    radacina->dr=NULL;

    radacina->val="+";
    radacina->st=n1;
    radacina->dr=n2;

    Derivare(n3,variabila);
    Derivare(n6,variabila);
}

void Derivare_Raport(nod *&radacina,string variabila)
{
    if(Parcurgere_Gasire_Variabila(radacina->st,variabila) && Parcurgere_Gasire_Variabila(radacina->dr,variabila))   // (f(x)/g(x))'= ( (f'(x)*g(x) - f(x)*g'(x))/(g(x)^2) )
    {
        nod*stanga=new nod;
        nod*dreapta=new nod;

        nod*stcpy1= new nod;
        stcpy1=DuplicareDinNod(radacina->st);

        nod*stcpy2= new nod;
        stcpy2=DuplicareDinNod(radacina->st);

        nod*drcpy1=new nod;
        drcpy1=DuplicareDinNod(radacina->dr);

        nod*drcpy2=new nod;
        drcpy2=DuplicareDinNod(radacina->dr);

        nod*drcpy3=new nod;
        drcpy3=DuplicareDinNod(radacina->dr);

        //nodul din stanga
        stanga->val="-";
        nod*n3=new nod;
        nod *n4=new nod;
        n3->val="*";
        n4->val="*";
        stanga->st=n3;
        stanga->dr=n4;

        n3->st=stcpy1;  // de derivat
        n3->dr=drcpy1;

        n4->st=stcpy2;
        n4->dr=drcpy2; //de derivat

        //nodul din dreapta
        dreapta->val="^";
        dreapta->st=drcpy3;
        nod*n6=new nod;
        n6->val="2";
        n6->st=NULL;
        n6->dr=NULL;
        dreapta->dr=n6;

        radacina->st=stanga;
        radacina->dr=dreapta;

        Derivare(stcpy1,variabila);
        Derivare(drcpy2,variabila);
    }
    else if(Parcurgere_Gasire_Variabila(radacina->st,variabila) && !Parcurgere_Gasire_Variabila(radacina->dr,variabila))   // (f(x)/g(n))'(x) = 1/(g(n)) * (f(x))'
    {
        nod *n1=new nod;
        nod *n2=new nod;

        n1->val="/";

        n2=DuplicareDinNod(radacina->st);  //de derivat

        nod *n3=new nod;
        nod*n4=new nod;

        n3->val="1";
        n3->st=NULL;
        n3->dr=NULL;

        n4=DuplicareDinNod(radacina->dr);

        n1->st=n3;
        n1->dr=n4;

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->st=n1;
        radacina->dr=n2;
        radacina->val="*";

        Derivare(n2,variabila);
    }
    else if(!Parcurgere_Gasire_Variabila(radacina->st,variabila) && !Parcurgere_Gasire_Variabila(radacina->dr,variabila))   // (f(n)/g(n))'(x) = 0;
    {
        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;
        radacina->val="0";

    }
    else if(!Parcurgere_Gasire_Variabila(radacina->st,variabila) && Parcurgere_Gasire_Variabila(radacina->dr,variabila))   // (g(n)/f(x))'(x) =  -g(n) * (f'(x)/f(x)^2)
    {
        nod* n1=new nod;
        nod*n2 =new nod;

        n1->val="-";
        n2->val="/";

        nod*n3=new nod;
        nod*n4=new nod;
        nod*n5=new nod;
        nod*n6=new nod;

        n3->val="0";
        n3->st=NULL;
        n3->dr=NULL;

        n4=DuplicareDinNod(radacina->st);

        n5=DuplicareDinNod(radacina->dr); //de derivat

        n6->val="^";

        nod*n7=new nod;
        nod*n8=new nod;

        n7=DuplicareDinNod(radacina->dr);

        n8->val="2";
        n8->st=NULL;
        n8->dr=NULL;

        n6->st=n7;
        n6->dr=n8;

        n1->st=n3;
        n1->dr=n4;

        n2->st=n5;
        n2->dr=n6;

        delete radacina->st;
        radacina->st=n1;
        delete radacina->dr;
        radacina->dr=n2;
        radacina->val="*";

        Derivare(n5,variabila);
    }



}
void Derivare_Exponent(nod *&radacina, string variabila)
{

    if(radacina->st->val=="e" && Parcurgere_Gasire_Variabila(radacina->dr,variabila))
    {
        nod*n1=new nod;
        nod*n2=new nod;

        n1=DuplicareDinNod(radacina);
        n2=DuplicareDinNod(radacina->dr);  //de derivat

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->st=n1;
        radacina->dr=n2;
        radacina->val = "*";

        Derivare(n2,variabila);
    }
    else if(Parcurgere_Gasire_Variabila(radacina->st,variabila) && !Parcurgere_Gasire_Variabila(radacina->dr,variabila))   // (f(x)^g(n))'(x) = g(n)*f(x)^(g(n)-1)*f'(x)
    {


        nod *n1=new nod;
        nod *n2=new nod;

        n1->val="*";


        n2=DuplicareDinNod(radacina->st); //de derivat

        nod *n3= new nod;
        nod *n4=new nod;

        n3=DuplicareDinNod(radacina->dr);

        n4->val="^";


        nod *n5= new nod;
        nod *n6= new nod;

        n5=DuplicareDinNod(radacina->st);

        n6->val="-";


        nod *n7=new nod;
        nod *n8=new nod;

        n7=DuplicareDinNod(radacina->dr);

        n8->val="1";
        n8->st=NULL;
        n8->dr=NULL;

        n6->st=n7;
        n6->dr=n8;

        n4->st=n5;
        n4->dr=n6;

        n1->st=n3;
        n1->dr=n4;

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->val="*";
        radacina->st=n1;
        radacina->dr=n2;

        Derivare(n2,variabila);
    }
    else if(!Parcurgere_Gasire_Variabila(radacina->st,variabila) && Parcurgere_Gasire_Variabila(radacina->dr,variabila))  ////(n^f(x))'(x) = n^f(x) * ln(n) * f'(x)
    {
        nod*n1=new nod;
        nod*n2=new nod;

        n1=DuplicareDinNod(radacina);
        n2->val="*";



        nod *n5=new nod;
        nod *n6=new nod;

        n5->val="ln";


        n6=DuplicareDinNod(radacina->dr);

        nod*n7 = new nod;

        n7=DuplicareDinNod(radacina->st);

        n5->st=n7;
        n5->dr=NULL;

        n2->st=n5;
        n2->dr=n6;

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->val="*";
        radacina->st=n1;
        radacina->dr=n2;

        Derivare(n6,variabila);
    }
    else if(Parcurgere_Gasire_Variabila(radacina->st,variabila) && Parcurgere_Gasire_Variabila(radacina->dr,variabila))  // (f(x)^g(x))'(x) = (f(x)^g(x))*(g(x)*(f'(x)/f(x)) + g'(x)*ln(f(x)))
    {
        nod *n1=new nod;
        nod*n2=new nod;

        n1=DuplicareDinNod(radacina);
        n2->val="+";

        nod*n5=new nod;
        nod*n6=new nod;

        n5->val="*";
        n6->val="*";

        nod*n7=new nod;
        nod*n8=new nod;
        nod*n9=new nod;  //de derivat
        nod*n10=new nod;

        n7=DuplicareDinNod(radacina->dr);

        n8->val="/";

        n9=DuplicareDinNod(radacina->dr);

        n10->val="ln";

        nod*n11=new nod;  //de derivat
        nod*n12=new nod;
        nod*n13=new nod;

        n11=DuplicareDinNod(radacina->st);

        n12=DuplicareDinNod(radacina->st);

        n13=DuplicareDinNod(radacina->st);

        n8->st=n11;
        n8->dr=n12;

        n10->st=n13;
        n10->dr=NULL;

        n5->st=n7;
        n5->dr=n8;

        n6->st=n9;
        n6->dr=n10;

        n2->st=n5;
        n2->dr=n6;

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->st=n1;
        radacina->dr=n2;
        radacina->val="*";

        Derivare(n11,variabila);
        Derivare(n9,variabila);


    }
    else if(!Parcurgere_Gasire_Variabila(radacina->st,variabila) && !Parcurgere_Gasire_Variabila(radacina->dr,variabila))  // (f(n)^g(n))'(x) = 0
    {
        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;
        radacina->val="0";
    }
}
void Derivare_Sinus(nod*&radacina, string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="cos";

    n2=DuplicareDinNod(radacina->st);  //de derivat

    nod*n3=new nod;
    n3=DuplicareDinNod(radacina->st);

    n1->st=n3;
    n1->dr=NULL;

    delete radacina->st;
    delete radacina->dr;

    radacina->val="*";
    radacina->st=n1;
    radacina->dr=n2;

    Derivare(n2,variabila);
}
void Derivare_Cosinus(nod*&radacina,string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="-";

    n2=DuplicareDinNod(radacina->st);  //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="0";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="sin";

    nod*n5=new nod;

    n5=DuplicareDinNod(radacina->st);

    n4->st=n5;
    n4->dr=NULL;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    radacina->st=NULL;
    delete radacina->dr;
    radacina->dr=NULL;

    radacina->st=n1;
    radacina->dr=n2;

    radacina->val="*";

    Derivare(n2,variabila);

}
void Derivare_Tangenta(nod*&radacina, string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";
    n2=DuplicareDinNod(radacina->st); //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="^";

    nod*n5=new nod;
    nod*n6=new nod;

    n5->val="cos";

    n6->val="2";
    n6->st=NULL;
    n6->dr=NULL;

    nod*n7=new nod;
    n7=DuplicareDinNod(radacina->st);

    n5->st=n7;
    n5->dr=NULL;

    n4->st=n5;
    n4->dr=n6;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    delete radacina->dr;

    radacina->st=n1;
    radacina->dr=n2;

    radacina->val="*";

    Derivare(n2,variabila);
}
void Derivare_Cotangenta(nod*&radacina,string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";

    n2=DuplicareDinNod(radacina->st);  //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="-1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="^";

    nod*n5=new nod;
    nod*n6=new nod;

    n5->val="sin";

    n6->val="2";
    n6->st=NULL;
    n6->dr=NULL;

    nod*n7=new nod;

    n7=DuplicareDinNod(radacina->st);

    n5->st=n7;
    n5->dr=NULL;

    n4->st=n5;
    n4->dr=n6;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    radacina->st=NULL;
    delete radacina->dr;
    radacina->dr=NULL;

    radacina->st=n1;
    radacina->dr=n2;

    radacina->val="*";

    Derivare(n2,variabila);

}
void Derivare_Arcsinus(nod*&radacina, string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";

    n2=DuplicareDinNod(radacina->st);  //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="sqrt";

    nod*n5=new nod;

    n5->val="-";

    nod*n6=new nod;
    nod*n7=new nod;

    n6->val="1";
    n6->st=NULL;
    n6->dr=NULL;

    n7->val="^";

    nod*n8=new nod;
    nod*n9=new nod;

    n8=DuplicareDinNod(radacina->st);

    n9->val="2";
    n9->st=NULL;
    n9->dr=NULL;

    n7->st=n8;
    n7->dr=n9;

    n5->st=n6;
    n5->dr=n7;

    n4->st=n5;
    n4->dr=NULL;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    delete radacina->dr;

    radacina->st=n1;
    radacina->dr=n2;
    radacina->val="*";

    Derivare(n2,variabila);


}
void Derivare_Arccosinus(nod*&radacina, string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";

    n2=DuplicareDinNod(radacina->st);  //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="-1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="sqrt";

    nod*n5=new nod;

    n5->val="-";

    nod*n6=new nod;
    nod*n7=new nod;

    n6->val="1";
    n6->st=NULL;
    n6->dr=NULL;

    n7->val="^";

    nod*n8=new nod;
    nod*n9=new nod;

    n8=DuplicareDinNod(radacina->st);

    n9->val="2";
    n9->st=NULL;
    n9->dr=NULL;

    n7->st=n8;
    n7->dr=n9;

    n5->st=n6;
    n5->dr=n7;

    n4->st=n5;
    n4->dr=NULL;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    delete radacina->dr;

    radacina->st=n1;
    radacina->dr=n2;
    radacina->val="*";

    Derivare(n2,variabila);


}
void Derivare_Arctangent(nod*&radacina,string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";
    n2=DuplicareDinNod(radacina->st); //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="+";

    nod*n5=new nod;
    nod*n6=new nod;

    n5->val="1";
    n5->st=NULL;
    n5->dr=NULL;

    n6->val="^";

    nod *n7=new nod;
    nod *n8=new nod;

    n7=DuplicareDinNod(radacina->st);

    n8->val="2";
    n8->st=NULL;
    n8->dr=NULL;

    n6->st=n7;
    n6->dr=n8;

    n4->st=n5;
    n4->dr=n6;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    delete radacina->dr;

    radacina->st=n1;
    radacina->dr=n2;
    radacina->val="*";

    Derivare(n2,variabila);
}
void Derivare_Arccotangent(nod*&radacina,string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";
    n2=DuplicareDinNod(radacina->st); //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="-1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="+";

    nod*n5=new nod;
    nod*n6=new nod;

    n5->val="1";
    n5->st=NULL;
    n5->dr=NULL;

    n6->val="^";

    nod *n7=new nod;
    nod *n8=new nod;

    n7=DuplicareDinNod(radacina->st);

    n8->val="2";
    n8->st=NULL;
    n8->dr=NULL;

    n6->st=n7;
    n6->dr=n8;

    n4->st=n5;
    n4->dr=n6;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    delete radacina->dr;

    radacina->st=n1;
    radacina->dr=n2;
    radacina->val="*";

    Derivare(n2,variabila);
}
void Derivare_SQRT(nod*&radacina,string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";
    n2=DuplicareDinNod(radacina->st);   //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="1";
    n3->st=NULL;
    n3->dr=NULL;

    n4->val="*";

    nod*n5=new nod;
    nod*n6=new nod;

    n5->val="2";
    n5->st=NULL;
    n5->dr=NULL;

    n6->val="sqrt";

    nod*n7=new nod;
    n7=DuplicareDinNod(radacina->st);

    n6->st=n7;
    n6->dr=NULL;

    n4->st=n5;
    n4->dr=n6;

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    delete radacina->dr;
    radacina->val="*";

    radacina->st=n1;
    radacina->dr=n2;

    Derivare(n2,variabila);
}
void Derivare_Logaritm(nod*&radacina,string variabila)
{
    if(!Parcurgere_Gasire_Variabila(radacina->st,variabila) && Parcurgere_Gasire_Variabila(radacina->dr,variabila))   // (log(g(n),f(x)))'(x) = 1/(f(x)*ln(g(n))) * f'(x)
    {
        nod*n1=new nod;
        nod*n2=new nod;

        n1->val="/";

        n2=DuplicareDinNod(radacina->dr);  //de derivat

        nod*n3=new nod;
        nod*n4=new nod;

        n3->val="1";
        n3->st=NULL;
        n3->dr=NULL;

        n4->val="*";

        nod*n5=new nod;
        nod*n6=new nod;

        n5=DuplicareDinNod(radacina->dr);

        n6->val="ln";
        n6->dr=NULL;

        nod*n7=new nod;

        n7=DuplicareDinNod(radacina->st);

        n6->st=n7;

        n4->st=n5;
        n4->dr=n6;

        n1->st=n3;
        n1->dr=n4;

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->val="*";
        radacina->st=n1;
        radacina->dr=n2;

        Derivare(n2,variabila);
    }
    else if(!Parcurgere_Gasire_Variabila(radacina,variabila) && !Parcurgere_Gasire_Variabila(radacina,variabila))   // (log(f(n),g(n)))'(x)=0
    {
        radacina->val="0";
        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;
    }
    else    //daca derivezi un logaritm care la baza are ceva in functie de x, iar la exponent nu SAU daca ai si la baza si la exponent in functie de x, modifici logaritmul a.i. log(a,b)=ln(b)/ln(a) (schimbare de baza), apoi derivezi raportul
    {
        nod*n1=new nod;
        nod*n2=new nod;

        n1->val="ln";
        n2->val="ln";

        nod*n3=new nod;
        nod*n4=new nod;

        n3=DuplicareDinNod(radacina->dr);
        n4=DuplicareDinNod(radacina->st);

        n1->st=n3;
        n1->dr=NULL;

        n2->st=n4;
        n2->dr=NULL;

        delete radacina->st;
        radacina->st=NULL;
        delete radacina->dr;
        radacina->dr=NULL;

        radacina->st=n1;
        radacina->dr=n2;

        radacina->val="/";
        Derivare(radacina,variabila);
    }

}
void Derivare_Logaritm_Natural(nod*&radacina,string variabila)
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="/";

    n2=DuplicareDinNod(radacina->st);  //de derivat

    nod*n3=new nod;
    nod*n4=new nod;

    n3->val="1";
    n3->st=NULL;
    n3->dr=NULL;

    n4=DuplicareDinNod(n2);

    n1->st=n3;
    n1->dr=n4;

    delete radacina->st;
    radacina->st=NULL;
    delete radacina->dr;
    radacina->dr=NULL;

    radacina->st=n1;
    radacina->dr=n2;
    radacina->val="*";

    Derivare(n2,variabila);
}
void Derivare_Logaritm_Zecimal(nod*&radacina,string variabila)  //lg(f(x))'=(ln(f(x)/ln(10)))'
{
    nod*n1=new nod;
    nod*n2=new nod;

    n1->val="ln";
    n2->val="ln";

    nod*n3=new nod;
    nod*n4=new nod;

    n3=DuplicareDinNod(radacina->st);

    n4->val="10";
    n4->st=NULL;
    n4->dr=NULL;

    n1->st=n3;
    n1->dr=NULL;

    n2->st=n4;
    n2->dr=NULL;

    delete radacina->st;
    radacina->st=NULL;
    delete radacina->dr;
    radacina->dr=NULL;

    radacina->st=n1;
    radacina->dr=n2;
    radacina->val="/";

    Derivare(radacina,variabila);

}
void Derivare_Negatie(nod*&radacina, string variabila)
{
    Derivare(radacina->st,variabila);
}
void Derivare(nod*&radacina, string variabila)
{


    if(radacina->val==variabila)
        Derivare_Variabila(radacina);
    else if(isalnum(radacina->val[0]) && !isOperator(radacina->val) && !isFunction(radacina->val) || (radacina->val[0]=='-' && isdigit(radacina->val[1]) ))
        Derivare_Constanta(radacina);
    else if(isOperator(radacina->val))
    {
        if(radacina->val=="+")
            Derivare_Suma(radacina,variabila);
        else if(radacina->val=="-")
            Derivare_Diferenta(radacina,variabila);
        else if(radacina->val=="*")
            Derivare_Produs(radacina,variabila);
        else if(radacina->val=="/")
            Derivare_Raport(radacina,variabila);
        else if(radacina->val=="^")
            Derivare_Exponent(radacina,variabila);
    }
    else if(isFunction(radacina->val))
    {
        if(radacina->val=="sin")
            Derivare_Sinus(radacina,variabila);
        else if(radacina->val=="cos")
            Derivare_Cosinus(radacina,variabila);

        else if(radacina->val=="tg")
            Derivare_Tangenta(radacina,variabila);
        else if(radacina->val=="ctg")
            Derivare_Cotangenta(radacina,variabila);

        else if(radacina->val=="arcsin")
            Derivare_Arcsinus(radacina,variabila);
        else if(radacina->val=="arccos")
            Derivare_Arccosinus(radacina,variabila);
        else if(radacina->val=="arctg")
            Derivare_Arctangent(radacina,variabila);
        else if(radacina->val=="arcctg")
            Derivare_Arccotangent(radacina,variabila);
        else if(radacina->val=="sqrt")
            Derivare_SQRT(radacina,variabila);
        else if(radacina->val=="log")
            Derivare_Logaritm(radacina,variabila);
        else if(radacina->val=="ln")
            Derivare_Logaritm_Natural(radacina,variabila);
        else if(radacina->val=="lg")
            Derivare_Logaritm_Zecimal(radacina,variabila);
        else if(radacina->val=="neg")
            Derivare_Negatie(radacina,variabila);
    }
    setare_parinti(radacina);
}
