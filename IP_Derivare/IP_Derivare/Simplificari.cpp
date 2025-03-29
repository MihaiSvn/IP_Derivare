#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>
#include <queue>
#include <stdlib.h>
#include <cmath>

#include "Structuri.h"
#include "Simplificari.h"

int isNumber(string s)
{
    if(s.empty())
        return 0;
    for(int i=0; s[i]!='\0'; i++)
        if(!(s[i]>='0' && s[i]<='9') && s[i]!='.' && !(s[i]=='-' && (s[i+1]>='0' && s[i+1]<='9')))
            return 0;
    return 1;
}
double String_To_Double(string s)
{
    /*int semn=0;
    if(s[0]=='-')
        semn=1;
    double prt_int=0;
    double prt_frac=0;
    int put10=1;
    int i;
    for(i=semn; s[i]!='\0' && s[i]!='.'; i++)
    {
        int cif=s[i]-'0';
        prt_int=prt_int*10+cif;
    }
    if(s[i]=='.')
    {
        int nrcif=0;
        put10=1;
        for(int j=i+1; s[j]!='\0'; j++)
        {
            int cif=s[j]-'0';
            prt_frac=prt_frac*10+cif;
            put10*=10;
            nrcif++;
        }
        prt_frac/=put10;


    }
    double numar;
    numar=prt_int+prt_frac;
    if(semn)
        numar=0-numar;
    return numar;*/


    return stod(s);




}
string Double_To_String(double n)
{
    string rezultat;
    int semn=0;
    if(n<0)
    {
        semn=1;
        n=-n;
    }
    long long prt_int=n;
    double prt_frac=n-prt_int;
    if(prt_int==0)
        return "0";
    while(prt_int>0)
    {
        int uc=prt_int%10;
        char cif=uc + '0';
        rezultat=cif+rezultat;
        prt_int/=10;
    }
    if(prt_frac>0)
    {
        rezultat+=".";
        while(prt_frac>0 && prt_frac!=0.0)
        {
            prt_frac*=10;
            int c=prt_frac;
            char cif=c+ '0';
            rezultat+=cif;
            prt_frac-=c;
        }
    }
    if(semn==1)
        rezultat="-"+rezultat;
    return rezultat;
}

int DoiArboriEgali(nod*radacina1,nod*radacina2)
{
    string arb1,arb2;
    DFS(radacina1,arb1);
    DFS(radacina2,arb2);
    if(arb1==arb2)
        return 1;
    return 0;
}

void Simplificare_NrVirgula(nod*&radacina)
{
    if(radacina==NULL)
        return;
    Simplificare_NrVirgula(radacina->st);
    Simplificare_NrVirgula(radacina->dr);
    if(isNumber(radacina->val))
    {
        for(int i=0;radacina->val[i]!='\0';i++)
            if(radacina->val[i]=='.')
            {
                int nr=0;
                for(int j=i+1;radacina->val[j]!='\0';j++)
                {
                    nr++;
                    if(nr>4)
                    {
                        radacina->val[j]='\0';
                        break;
                    }
                }
                break;
            }
    }
}
void DFS_SimplificareProdus(nod*radacina, stack<nod*> &StivaElemente, double &produs, bool&ok, int&Nr_Numere, string variabila, int &putereVariabila)
{
    if(radacina->st->val=="*")
        DFS_SimplificareProdus(radacina->st,StivaElemente,produs,ok,Nr_Numere,variabila,putereVariabila);
    if(radacina->dr->val=="*")
        DFS_SimplificareProdus(radacina->dr,StivaElemente,produs,ok,Nr_Numere,variabila,putereVariabila);


    {
        if(isNumber(radacina->st->val))
        {
            if(radacina->st->val!="0" && radacina->st->val!="1")
                Nr_Numere++;
            if(Nr_Numere>=2)
                ok=true;
            double n=String_To_Double(radacina->st->val);
            produs*=n;

        }
        else if(radacina->st->val==variabila)
        {
            putereVariabila++;
            if(putereVariabila>1)
                ok=true;
        }
        else if(radacina->st->val!="*")
        {
            StivaElemente.push(radacina->st);

        }

        if(isNumber(radacina->dr->val))
        {
            if(radacina->dr->val!="0" && radacina->dr->val!="1")
                Nr_Numere++;
            if(Nr_Numere>=2)
                ok=true;
            double n=String_To_Double(radacina->dr->val);
            produs*=n;
        }
        else if(radacina->dr->val==variabila)
        {
            putereVariabila++;
            if(putereVariabila>1)
                ok=true;
        }
        else if(radacina->dr->val!="*")
        {
            StivaElemente.push(radacina->dr);

        }
    }



}
void Simplificare_Produs(nod*&radacina, bool &ok,string variabila)
{
    stack <nod*> StivaElemente;
    double produs=1;
    ok=false;
    int Nr_Numere=0,putereVariabila=0;
    DFS_SimplificareProdus(radacina,StivaElemente,produs,ok,Nr_Numere,variabila,putereVariabila);

    if(ok)
    {
        nod*rad=new nod;
        rad->val="*";
        rad->parinte=NULL;

        nod*radst=new nod;



        if(putereVariabila!=0)
        {

            nod*R1=new nod;
            nod*R2=new nod;
            nod*R3=new nod;
            nod*R4=new nod;

            radst->val="*";

            radst->st=R1;
            radst->dr=R2;

            R1->val=Double_To_String(produs);
            R1->st=NULL;
            R1->dr=NULL;
            R1->parinte=radst;

            if(putereVariabila!=1)
            {
                R2->val="^";
                R2->parinte=radst;
                R2->st=R3;
                R2->dr=R4;

                R3->parinte=R2;
                R3->val=variabila;
                R3->st=NULL;
                R3->dr=NULL;

                R4->parinte=R2;
                R4->val=Double_To_String(putereVariabila);
                R4->st=NULL;
                R4->dr=NULL;
            }
            else
            {
                R2->val=variabila;
                R2->st=NULL;
                R2->dr=NULL;
                R2->parinte=radst;
            }





        }
        else
        {
            radst->val=Double_To_String(produs);
            radst->st=NULL;
            radst->dr=NULL;
        }




        radst->parinte=rad;

        rad->st=radst;

        nod*rp=rad;

        while(!StivaElemente.empty())
        {
            nod*el=StivaElemente.top();
            StivaElemente.pop();
            nod*r1=new nod;
            r1->val="*";
            r1->st=el;
            el->parinte=r1;
            r1->parinte=rp;
            rp->dr=r1;
            rp=rp->dr;
        }

        nod*r2=new nod;
        rp->dr=r2;
        r2->val="1";
        r2->st=NULL;
        r2->dr=NULL;
        r2->parinte=rp;

        int simplificari=0;
        if(rad==rp)
            Simplificare(rad,simplificari,variabila);
        else Simplificare(rp,simplificari,variabila);


        radacina=rad;
    }

}
void DFS_SimplificareSuma(nod*radacina, stack<nod*> &StivaElemente, stack <string> &StivaSemne, double &suma, bool&ok, int&Nr_Numere, string variabila, int &coeficientVariaibla,int &verfiNrVar)
{
    if(radacina->st->val=="+" || radacina->st->val=="-")
        DFS_SimplificareSuma(radacina->st,StivaElemente,StivaSemne,suma,ok,Nr_Numere,variabila,coeficientVariaibla,verfiNrVar);
    if(radacina->dr->val=="+" || radacina->dr->val=="-")
        DFS_SimplificareSuma(radacina->dr,StivaElemente,StivaSemne,suma,ok,Nr_Numere,variabila,coeficientVariaibla,verfiNrVar);


    {
        if(isNumber(radacina->st->val))
        {
            if(radacina->st->val!="0")
                Nr_Numere++;
            if(Nr_Numere>=2)
                ok=true;
            double n=String_To_Double(radacina->st->val);
            suma+=n;

        }
        else if(radacina->st->val==variabila)
        {
            coeficientVariaibla++;
            verfiNrVar++;
            if(verfiNrVar>1)
                ok=true;
        }
        else if(radacina->st->val!="+" && radacina->st->val!="-")
        {
            StivaElemente.push(radacina->st);
            StivaSemne.push("+");
        }

        if(isNumber(radacina->dr->val))
        {
            if(radacina->dr->val!="0")
                Nr_Numere++;
            if(Nr_Numere>=2)
                ok=true;
            double n=String_To_Double(radacina->dr->val);
            if(radacina->val=="+")
                suma+=n;
            else if(radacina->val=="-")
                suma-=n;
        }
        else if(radacina->dr->val==variabila)
        {
            if(radacina->val=="+")
                coeficientVariaibla++;
            else if(radacina->val=="-")
                coeficientVariaibla--;
            verfiNrVar++;
            if(verfiNrVar>1)
                ok=true;
        }
        else if(radacina->dr->val!="+" && radacina->dr->val!="-")
        {
            StivaElemente.push(radacina->dr);
            StivaSemne.push(radacina->val);
        }
    }



}

void Simplificare_Suma(nod*&radacina, bool &ok, string variabila)
{
    stack <nod*> StivaElemente;
    stack <string> StivaSemne;
    double suma=0;
    ok=false;
    int Nr_Numere=0,coeficientVariabila=0,verifNrVar=0;
    DFS_SimplificareSuma(radacina,StivaElemente,StivaSemne,suma,ok,Nr_Numere,variabila,coeficientVariabila,verifNrVar);

    if(ok)
    {
        nod*rad=new nod;
        rad->val="+";

        rad->parinte=NULL;

        nod*raddr=new nod;

        if(coeficientVariabila!=0)
        {
            if(suma>=0)
                raddr->val="+";
            else raddr->val="-";

            nod*R1=new nod;
            nod*R2=new nod;

            R1->val=Double_To_String(abs(suma));
            R1->st=NULL;
            R1->dr=NULL;
            R1->parinte=raddr;
            raddr->dr=R1;

            if(coeficientVariabila!=1)
            {
                R2->val="*";
                R2->parinte=raddr;
                raddr->st=R2;

                nod*R3=new nod;
                nod*R4=new nod;

                R3->val=Double_To_String(coeficientVariabila);
                R3->st=NULL;
                R3->dr=NULL;
                R3->parinte=R2;
                R2->st=R3;

                R4->val=variabila;
                R4->st=NULL;
                R4->dr=NULL;
                R4->parinte=R2;
                R2->dr=R4;

            }
            else
            {
                R2->val=variabila;
                R2->st=NULL;
                R2->dr=NULL;
                R2->parinte=raddr;
                raddr->st=R2;
            }
        }
        else
        {

            raddr->val=Double_To_String(abs(suma));
            if(suma<0)
                rad->val="-";
            raddr->st=NULL;
            raddr->dr=NULL;
            raddr->parinte=rad;
        }



        rad->dr=raddr;


        nod*rp=rad;

        while(!StivaElemente.empty())
        {
            nod*el=StivaElemente.top();
            string semn=StivaSemne.top();
            StivaElemente.pop();
            StivaSemne.pop();
            nod*r1=new nod;
            r1->val=semn;
            r1->dr=el;
            el->parinte=r1;
            r1->parinte=rp;
            rp->st=r1;
            rp=rp->st;
        }
        nod*r2=new nod;
        rp->st=r2;
        r2->val="0";
        r2->st=NULL;
        r2->dr=NULL;
        r2->parinte=rp;

        int simplificari=0;
        if(rad==rp)
            Simplificare(rad,simplificari,variabila);
        else Simplificare(rp,simplificari,variabila);


        radacina=rad;
    }




    /*if(rp->val=="+")
    {
        nod* adresa=rp;
        rp=DuplicareDinNod(rp->dr);
        rp=adresa;
    }
    else
    {
        rp=DuplicareDinNod(rp->dr);
        rp->val="-"+rp->val;
    }*/








}
void Simplificare(nod *&radacina,int &simplificari, string variabila)
{
    if(radacina->val=="+")
    {
        if(radacina->st->val=="0")   //0+x=x
        {
            simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->st;
            radacina->st=NULL;
            nod*dr=radacina->dr;



            if(pred==NULL)
            {
                radacina=dr;
                radacina->parinte=NULL;
            }


            else
            {
                if(pred->st==radacina)
                    pred->st=dr;
                else if(pred->dr==radacina)
                    pred->dr=dr;
                //delete radacina;
                //radacina=NULL;
                dr->parinte=pred;
            }





        }
        else if(radacina->dr->val=="0")   //x+0=x
        {
            simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->dr;
            radacina->dr=NULL;
            nod*st=radacina->st;



            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }


            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                //delete radacina;
                //radacina=NULL;
                st->parinte=pred;
            }

        }
        else if(radacina->dr->val[0]=='-' && isdigit(radacina->dr->val[1]))   //f(x)+(-n)=f(x)-n
        {
            simplificari++;

            radacina->val="-";

            radacina->dr->val.erase(radacina->dr->val.begin());   //-n=n
        }
        else if(radacina->dr->val=="neg")   //f(x)+(-(g(x)))=f(x)-g(x)
        {
            simplificari++;

            nod*st=new nod;
            st=DuplicareDinNod(radacina->st);

            nod*dr=new nod;
            dr=DuplicareDinNod(radacina->dr->st);

            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;

            radacina->st=st;
            radacina->dr=dr;
            radacina->val="-";

            st->parinte=radacina;
            dr->parinte=radacina;

        }
        else if(DoiArboriEgali(radacina->st,radacina->dr)) //f(x)+f(x)=2*f(x)
        {
            simplificari++;

            delete radacina->st;
            radacina->st=NULL;

            nod*st=new nod;
            st->val="2";
            st->st=NULL;
            st->dr=NULL;
            st->parinte=radacina;

            radacina->st=st;
            radacina->val="*";
        }
        else
        {
            {
                bool ok=false;
                Simplificare_Suma(radacina,ok,variabila);
                if(ok)
                    simplificari++;
                if(radacina->val=="+")
                {
                    if(radacina->st)
                    {
                        if(radacina->dr)
                        {
                            if(radacina->st->val!=variabila && radacina->dr->val==variabila)  //g(n)+x=x+g(n)
                            {
                                simplificari=1;
                                nod*n=new nod;
                                n=DuplicareDinNod(radacina->dr);
                                radacina->dr=radacina->st;
                                n->parinte=radacina;
                                radacina->st=n;

                            }
                        }
                    }
                }
            }

        }
    }
    else if(radacina->val=="-")
    {
        if(radacina->st->val=="0" && radacina->dr->val=="0")   //0-0=0
        {
            simplificari++;
            radacina->val="0";
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
        }
        else if(radacina->st->val=="0")
        {
            if(isNumber(radacina->dr->val))   //0-n=-n
            {
                simplificari++;
                int semn;
                if(radacina->dr->val[0]=='-')
                    semn=1;
                else semn=0;
                if(semn)
                {
                    string nr=radacina->dr->val;
                    nr.erase(nr.begin());
                    radacina->val=nr;
                    delete radacina->st;
                    radacina->st=NULL;
                    delete radacina->dr;
                    radacina->dr=NULL;
                }
                else
                {
                    radacina->val="-"+radacina->dr->val;
                    delete radacina->st;
                    radacina->st=NULL;
                    delete radacina->dr;
                    radacina->dr=NULL;
                }

            }
            else  //0-f(x)=neg(f(x))
            {
                simplificari++;
                nod *n1=new nod;
                n1=DuplicareDinNod(radacina->dr);

                radacina->st=n1;
                n1->parinte=radacina;


                delete radacina->dr;
                radacina->dr=NULL;

                radacina->val="neg";
            }

        }
        else if(radacina->dr->val=="0")   //x-0=x
        {
            simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->dr;
            radacina->dr=NULL;
            nod*st=radacina->st;



            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }

            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                //delete radacina;
                //radacina=NULL;
                st->parinte=pred;
            }
        }
        else if(DoiArboriEgali(radacina->st,radacina->dr)) //f(x)-f(x)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
            radacina->val="0";
        }
        else
        {
            {
                //verificam daca elementele operatiei sunt numere, daca da le scadem

                bool ok=false;
                Simplificare_Suma(radacina,ok,variabila);
                if(ok)
                    simplificari++;
                if(radacina->val=="+")
                {
                    if(radacina->st)
                    {
                        if(radacina->dr)
                        {
                            if(!Parcurgere_Gasire_Variabila(radacina->st,variabila) && Parcurgere_Gasire_Variabila(radacina->dr,variabila))  //g(n)+x=x+g(n)
                            {
                                simplificari=1;
                                nod*n=new nod;
                                n=DuplicareDinNod(radacina->dr);
                                radacina->dr=radacina->st;
                                n->parinte=radacina;
                                radacina->st=n;

                            }
                        }
                    }
                }
            }

        }
    }
    else if(radacina->val=="*")
    {
        if(radacina->st->val=="0" || radacina->dr->val=="0")   //0*x=0 si x*0=0
        {
            simplificari++;
            radacina->val="0";
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
        }
        else if(radacina->st->val=="1")    //1*x=x
        {
            simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->st;
            radacina->st=NULL;
            nod*dr=radacina->dr;



            if(pred==NULL)
            {
                radacina=dr;
                radacina->parinte=NULL;
            }


            else
            {
                if(pred->st==radacina)
                    pred->st=dr;
                else if(pred->dr==radacina)
                    pred->dr=dr;
                //delete radacina;
                //radacina=NULL;
                dr->parinte=pred;
            }

        }
        else if(radacina->dr->val=="1")    //x*1=x
        {
            simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->dr;
            radacina->dr=NULL;
            nod*st=radacina->st;



            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }


            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                //delete radacina;
                //radacina=NULL;
                st->parinte=pred;
            }

        }
        else if(radacina->st->val=="-1") //-1*f(x)=neg(f(x))
        {
            simplificari++;

            delete radacina->st;
            radacina->st=NULL;

            nod*dr=new nod;
            dr=DuplicareDinNod(radacina->dr);

            delete radacina->dr;
            radacina->dr=NULL;

            radacina->st=dr;
            dr->parinte=radacina;

            radacina->val="neg";
        }
        else if(radacina->dr->val=="-1") //f(x)*(-1)=neg(f(x))
        {
            simplificari++;

            delete radacina->dr;
            radacina->dr=NULL;

            nod*st=new nod;
            st=DuplicareDinNod(radacina->st);

            delete radacina->st;
            radacina->st=NULL;

            radacina->st=st;
            st->parinte=radacina;

            radacina->val="neg";
        }
        else if(radacina->st->val=="neg" && radacina->dr->val=="neg")    //-f(x)*(-g(x))=f(x)*g(x)
        {
            simplificari++;

            nod*st=new nod;
            st=DuplicareDinNod(radacina->st->st);

            nod*dr=new nod;
            dr=DuplicareDinNod(radacina->dr->st);

            delete radacina->st;
            radacina->st=NULL;

            delete radacina->dr;
            radacina->dr=NULL;

            radacina->st=st;
            radacina->dr=dr;

            st->parinte=radacina;
            dr->parinte=radacina;
        }
        else if(DoiArboriEgali(radacina->st,radacina->dr)) //f(x)*f(x)=f(x)^2
        {
            simplificari++;

            delete radacina->dr;
            radacina->dr=NULL;

            nod*dr=new nod;
            dr->val="2";
            dr->st=NULL;
            dr->dr=NULL;
            dr->parinte=radacina;

            radacina->dr=dr;
            radacina->val="^";
        }
        else if(radacina->st->val=="/" && (radacina->st->st->val=="1" || radacina->st->st->val=="-1" ) && radacina->dr->val!="/")   // (+-1/f(x))*g(x)=(+-g(x)/f(x))
        {

            simplificari++;

            nod* f = new nod;
            nod* g = new nod;


            f=DuplicareDinNod(radacina->st->dr);
            g=DuplicareDinNod(radacina->dr);

            radacina->val="/";

            int semn;
            if(radacina->st->st->val[0]=='-')
                semn=1;
            else semn=0;

            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;

            if(semn)
            {
                if(isNumber(g->val))
                {
                    if(g->val[0]=='-')
                        g->val.erase(g->val.begin());
                    else g->val.insert(g->val.begin(),'-');

                    g->parinte=radacina;
                    radacina->st=g;
                }
                else
                {
                    nod* N=new nod;
                    N->val="neg";
                    N->st=g;
                    N->dr=NULL;
                    N->parinte=radacina;
                    radacina->st=N;
                }


                f->parinte=radacina;
                radacina->dr=f;
            }
            else
            {
                g->parinte=radacina;
                radacina->st=g;

                f->parinte=radacina;
                radacina->dr=f;
            }



        }

        else if(radacina->dr->val=="/" && (radacina->dr->st->val=="1" || radacina->dr->st->val=="-1" ) && radacina->st->val!="/")   // g(x)*(+-1/f(x))=(+-g(x)/f(x))
        {

            simplificari++;


            nod*n=new nod;                             //facem un swap intre st si dr
            n=DuplicareDinNod(radacina->dr);
            radacina->dr=radacina->st;
            n->parinte=radacina;
            radacina->st=n;

            nod* f = new nod;
            nod* g = new nod;


            f=DuplicareDinNod(radacina->st->dr);
            g=DuplicareDinNod(radacina->dr);

            radacina->val="/";

            int semn;
            if(radacina->st->st->val[0]=='-')
                semn=1;
            else semn=0;

            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;

            if(semn)
            {
                if(isNumber(g->val))
                {
                    if(g->val[0]=='-')
                        g->val.erase(g->val.begin());
                    else g->val.insert(g->val.begin(),'-');

                    g->parinte=radacina;
                    radacina->st=g;
                }
                else
                {
                    nod* N=new nod;
                    N->val="neg";
                    N->st=g;
                    N->dr=NULL;
                    N->parinte=radacina;
                    radacina->st=N;
                }


                f->parinte=radacina;
                radacina->dr=f;
            }
            else
            {
                g->parinte=radacina;
                radacina->st=g;

                f->parinte=radacina;
                radacina->dr=f;
            }



        }

        else
        {
            bool ok=false;
            Simplificare_Produs(radacina,ok,variabila);
            if(ok)
                simplificari++;
            if(radacina->val=="*")
            {
                if(radacina->st)
                {
                    if(radacina->dr)
                    {
                        if(Parcurgere_Gasire_Variabila(radacina->st,variabila) && !Parcurgere_Gasire_Variabila(radacina->dr,variabila))  //x*g(n)=g(n)*x
                        {
                            simplificari=1;
                            nod*n=new nod;
                            n=DuplicareDinNod(radacina->dr);
                            radacina->dr=radacina->st;
                            n->parinte=radacina;
                            radacina->st=n;

                        }
                    }
                }
            }
        }
    }
    else if(radacina->val=="^")
    {
        if(radacina->st->val=="0")   // 0^f(x)=0
        {
            simplificari++;
            radacina->val="0";
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
        }
        else if(radacina->st->val=="1")  //1^f(x)=1
        {
            simplificari++;
            radacina->val="1";
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
        }
        else if(radacina->dr->val=="0")  //f(x)^0=1
        {
            simplificari++;
            radacina->val="1";
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
        }
        else if(radacina->dr->val=="1")  //f(x)^1=f(x)
        {
            //simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->dr;
            radacina->dr=NULL;
            nod*st=radacina->st;



            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }


            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                //delete radacina;
                //radacina=NULL;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="neg" && (int)String_To_Double(radacina->dr->val)%2==0)  //(-f(x))^2k=f(x)^2k
        {
            simplificari++;

            nod*st=radacina->st;
            radacina->st->st->parinte=radacina;
            radacina->st=radacina->st->st;
            delete st;
            st=NULL;

        }
    }
    else if(radacina->val=="/")
    {
        if(radacina->dr->val=="1")  // f(x)/1=f(x)
        {
            simplificari++;

            nod*pred=radacina->parinte;
            delete radacina->dr;
            radacina->dr=NULL;
            nod*st=radacina->st;



            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }


            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                //delete radacina;
                //radacina=NULL;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="0")   // 0/f(x)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
            radacina->val="0";
        }
        else if(DoiArboriEgali(radacina->st,radacina->dr)) //f(x)/f(x)=1
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
            radacina->val="1";
        }
        else if(radacina->st->val=="sin" && radacina->dr->val=="cos")
        {
            if(DoiArboriEgali(radacina->st->st,radacina->dr->st))  //sin(f(x))/cos(f(x))=tg(f(x))
            {
                simplificari++;
                nod*n=DuplicareDinNod(radacina->st->st);

                delete radacina->st;
                radacina->st=NULL;
                delete radacina->dr;
                radacina->dr=NULL;

                radacina->val="tg";
                radacina->st=n;
                n->parinte=radacina;
            }
        }
        else if(radacina->st->val=="cos" && radacina->dr->val=="sin")
        {
            if(DoiArboriEgali(radacina->st->st,radacina->dr->st))  //cos(f(x))/sin(f(x))=ctg(f(x))
            {
                simplificari++;
                nod*n=DuplicareDinNod(radacina->st->st);

                delete radacina->st;
                radacina->st=NULL;
                delete radacina->dr;
                radacina->dr=NULL;

                radacina->val="ctg";
                radacina->st=n;
                n->parinte=radacina;
            }
        }
    }
    else if(radacina->val=="log")
    {
        if(radacina->dr->val=="1")   //log(a,1)=0
        {
            simplificari++;
            radacina->val="0";
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
        }
        else if(DoiArboriEgali(radacina->st,radacina->dr)) //log(a,a)=1
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;
            radacina->val="1";
        }
        else if(radacina->st->val=="10")  //log(10,x)=lg(x)
        {
            nod*dr=new nod;
            dr=DuplicareDinNod(radacina->dr);
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;

            radacina->st=dr;
            dr->parinte=radacina;
            radacina->val="lg";
        }
        else if(radacina->st->val=="e")  //log(e,x)=ln(x)
        {
            nod*dr=new nod;
            dr=DuplicareDinNod(radacina->dr);
            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;

            radacina->st=dr;
            dr->parinte=radacina;
            radacina->val="ln";
        }
        else if(isNumber(radacina->st->val) && isNumber(radacina->dr->val))    //daca log(b,a) se poate calcula si sa fie intreg, se calculeaza
        {
            double st=String_To_Double(radacina->st->val);
            double dr=String_To_Double(radacina->dr->val);

            double nr=log2(dr)/log2(st);

            if(nr==(int)nr)
            {
                simplificari++;

                radacina->val=Double_To_String(nr);
                delete radacina->st;
                radacina->st=NULL;

                delete radacina->dr;
                radacina->dr=NULL;


            }
        }
        else
        {
            if(radacina->dr->val=="^")   //log(a,a^f(x))=f(x)
            {
                if(DoiArboriEgali(radacina->st,radacina->dr->st))
                {
                    simplificari++;
                    nod*pred=radacina->parinte;

                    nod*n=radacina->dr->dr;

                    if(pred==NULL)
                    {
                        radacina=n;
                        radacina->parinte=NULL;
                    }


                    else
                    {
                        if(pred->st==radacina)
                            pred->st=n;
                        else if(pred->dr==radacina)
                            pred->dr=n;
                        //delete radacina;
                        //radacina=NULL;
                        n->parinte=pred;
                    }
                }
            }
        }
    }
    else if(radacina->val=="ln")
    {
        if(radacina->st->val=="e") //ln(e)=1
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="1";
        }
        else if(radacina->st->val=="1") //ln(1)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
        else
        {
            if(radacina->st->val=="^")   // ln(e^f(x))=f(x)
            {
                if(radacina->st->st->val=="e")
                {
                    simplificari++;
                    nod*pred=radacina->parinte;

                    nod*n=radacina->st->dr;

                    if(pred==NULL)
                    {
                        radacina=n;
                        radacina->parinte=NULL;
                    }


                    else
                    {
                        if(pred->st==radacina)
                            pred->st=n;
                        else if(pred->dr==radacina)
                            pred->dr=n;
                        //delete radacina;
                        //radacina=NULL;
                        n->parinte=pred;
                    }
                }
            }
        }
    }
    else if(radacina->val=="lg")
    {
        if(radacina->st->val=="10") //lg(10)=1
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="1";
        }
        else if(radacina->st->val=="1") //lg(1)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
        else
        {
            if(radacina->st->val=="^")   // lg(10^f(x))=f(x)
            {
                if(radacina->st->st->val=="10")
                {
                    simplificari++;
                    nod*pred=radacina->parinte;

                    nod*n=radacina->st->dr;

                    if(pred==NULL)
                    {
                        radacina=n;
                        radacina->parinte=NULL;
                    }


                    else
                    {
                        if(pred->st==radacina)
                            pred->st=n;
                        else if(pred->dr==radacina)
                            pred->dr=n;
                        //delete radacina;
                        //radacina=NULL;
                        n->parinte=pred;
                    }
                }
            }
            else
            {
                if(isNumber(radacina->st->val))  //lg(100000...0) (de k ori)=k
                {
                    string numar=radacina->st->val;
                    if(numar[0]=='1')
                    {
                        int check=1,put=0;
                        for(int j=1; numar[j]!='\0' && check; j++)
                        {
                            if(numar[j]!='0')
                                check=0;
                            put++;
                        }
                        if(check)
                        {
                            simplificari++;
                            delete radacina->st;
                            radacina->st=NULL;
                            radacina->val=Double_To_String(put);
                        }
                    }


                }
            }

        }

    }
    else if(radacina->val=="sqrt")
    {
        if(isNumber(radacina->st->val))   // calcul sqrt(patrat perfect)
        {
            simplificari++;
            string nr=radacina->st->val;
            int ok=1;
            for(int i=0; nr[i]!='\0' && ok; i++)
                if(nr[i]=='.')
                    ok=0;
            if(ok)
            {
                int x=String_To_Double(radacina->st->val);
                if(sqrt(x)*sqrt(x)==x)
                {
                    radacina->val=Double_To_String(sqrt(x));
                    delete radacina->st;
                    radacina->st=NULL;
                }
            }

        }
        else if(radacina->st->val=="^")
        {
            if(isNumber(radacina->st->dr->val))
            {
                string nr=radacina->st->dr->val;
                if(nr=="2")
                {
                    simplificari++;
                    nod*pred=radacina->parinte;
                    nod*st=radacina->st->st;
                    if(pred==NULL)
                    {
                        radacina=st;
                        radacina->parinte=NULL;

                    }
                    else
                    {
                        if(pred->st==radacina)
                            pred->st=st;
                        else if(pred->dr==radacina)
                            pred->dr=st;
                        st->parinte=pred;
                    }
                }
                else
                {
                    int ok=1;
                    for(int i=0; nr[i]!='\0' && ok; i++)
                        if(nr[i]=='.')
                            ok=0;
                    if(ok)
                    {
                        int x=String_To_Double(radacina->st->dr->val);
                        if(sqrt(x)*sqrt(x)==x)
                        {
                            simplificari++;
                            nod*pred=radacina->parinte;
                            nod*st=radacina->st;
                            if(pred==NULL)
                            {
                                radacina=st;
                                radacina->parinte=NULL;
                                radacina->dr->val=Double_To_String(sqrt(x));
                            }
                            else
                            {
                                if(pred->st==radacina)
                                    pred->st=st;
                                else if(pred->dr==radacina)
                                    pred->dr=st;
                                st->parinte=pred;
                            }

                        }
                    }
                }

            }
        }
    }
    else if(radacina->val=="neg")
    {
        if(isNumber(radacina->st->val))  //neg(n)=-n, n numar
        {
            simplificari++;

            string nr=radacina->st->val;
            nr="-"+nr;

            delete radacina->st;
            radacina->st=NULL;
            delete radacina->dr;
            radacina->dr=NULL;

            radacina->val=nr;
        }
        else if(radacina->st->val=="neg")  //-(-f(x))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
    }
    else if(radacina->val=="sin")
    {
        if(radacina->st->val=="arcsin")  //sin(arcsin(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="0")  //sin(0)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
    }
    else if(radacina->val=="cos")
    {
        if(radacina->st->val=="arccos")   //cos(arccos(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
    }
    else if(radacina->val=="tg")
    {
        if(radacina->st->val=="arctg")  //tg(arctg(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="0")  //tg(0)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
    }
    else if(radacina->val=="ctg")
    {
        if(radacina->st->val=="arcctg")   //ctg(arcctg(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
    }
    else if(radacina->val=="arcsin")
    {
        if(radacina->st->val=="sin")  //arcsin(sin(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="0")  //arcsin(0)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
    }
    else if(radacina->val=="arccos")
    {
        if(radacina->st->val=="cos")   //arccos(cos(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="1")  //arccos(1)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
    }
    else if(radacina->val=="arctg")
    {
        if(radacina->st->val=="tg")  //arctg(tg(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
        else if(radacina->st->val=="0")  //arctg(0)=0
        {
            simplificari++;
            delete radacina->st;
            radacina->st=NULL;
            radacina->val="0";
        }
    }
    else if(radacina->val=="arcctg")
    {
        if(radacina->st->val=="ctg")   //arcctg(ctg(f(x)))=f(x)
        {
            simplificari++;
            nod*st=radacina->st->st;
            nod*pred=radacina->parinte;
            if(pred==NULL)
            {
                radacina=st;
                radacina->parinte=NULL;
            }
            else
            {
                if(pred->st==radacina)
                    pred->st=st;
                else if(pred->dr==radacina)
                    pred->dr=st;
                st->parinte=pred;
            }
        }
    }

}

void Parcurgere_Simplificare(nod*&radacina, int &simplificari,string variabila)
{
    if (radacina==NULL)
        return;
    simplificari=0;
    Simplificare(radacina,simplificari,variabila);
    if(simplificari==0)
    {
        int smp1=0,smp2=0;
        if(radacina->st!=NULL)
            Parcurgere_Simplificare(radacina->st,smp1,variabila);
        if(radacina->dr!=NULL)
            Parcurgere_Simplificare(radacina->dr,smp2,variabila);
        simplificari=smp1||smp2;
    }

}
void Start_Simplificare(nod*&radacina, string variabila)
{
    int simplificari=0;
    do
    {
        Parcurgere_Simplificare(radacina,simplificari,variabila);
    }
    while(simplificari!=0);

    Simplificare_NrVirgula(radacina);
}
