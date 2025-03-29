#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <map>
#include <graphics.h>

#include "Transformare_Din_Inordine_In_Postordine.h"
#include "DetectareFunctii+PrioritatiFunctii.h"
#include "Structuri.h"
#include "conversie.h"

string Operatori[]=
{
    "+",
    "-",
    "*",
    "/",
    "^",
    "(",
    ")",
    " "
};

int isOperator(string c)
{
    for(int i=0; i<(sizeof(Operatori)/sizeof(Operatori[0])); i++)
        if(c==Operatori[i])
            return 1;
    return 0;

}

void DFS(nod *radacina, string &SirInoridine)
{
    if(radacina==NULL)
        return;
    DFS(radacina->st, SirInoridine);
    DFS(radacina->dr, SirInoridine);
    SirInoridine+=radacina->val;
    SirInoridine+=";";
}

string Transformare_PostOrdine(string s, bool &ok)
{
    stack<string> Stiva;
    string ExprPostOrdine;

    for(int i=0; s[i]!='\0'; i++) //stergem toate spatiile
        if(s[i]==' ')
        {
            s.erase(s.begin()+i);
            i--;
        }

    for(int i=0; s[i+1]!='\0'; i++)
    {
        string c1(1,s[i]);
        string c2(1,s[i+1]);

        if(c1!="(" && c1!=")" && c2!="(" && c2!=")")
        {
            if(isOperator(c1) && isOperator(c2))
            {
                outtextxy(0,80,"Eroare: Doi operatori unul langa altul fara parantezare!");
                ok=false;
                break;
            }
        }

        else if(c1=="(" && (c2!="(" && c2!="+" && c2!="-" && isOperator(c2)))  // forma (operator este gresita. Ex: (*,(/, dar (+ si (- sunt corecte
        {
            outtextxy(0,80,"Eroare!");
            ok=false;
        }
        else if(c1!=")" && isOperator(c1) && c2==")")    //forma operator) este gresita. Ex: +),-),*)
        {
            outtextxy(0,80,"Eroare!");
            ok=false;
        }


        if(c1==")" && !isOperator(c2))  //(f(x))g(x) va deveni f(x)*g(x)
        {
            s.insert(s.begin()+i+1,'*');
        }
        else if(isdigit(s[i]) && isalpha(s[i+1]))   //123f(x) va deveni 123*f(x)
        {
            s.insert(s.begin()+i+1,'*');
        }
        else if(isdigit(s[i]) && s[i+1]=='(')  //123(f(x)) va deveni 123*f(x)
        {
            s.insert(s.begin()+i+1,'*');
        }
    }


    string c1(1,s[s.length()-1]);

    if(s.empty())
    {
        outtextxy(0,80,"Eroare: Nu a fost introdusa o functie!");
        ok=false;
    }
    if(isOperator(c1) && c1!=")" && c1!="(")
    {
        outtextxy(0,80,"Eroare: Expresia nu se poate termina cu un operator!");
        ok=false;
    }


    if(s[0]=='-')  //daca expresia incepe cu -f(x) scriem ca (0-f(x))
    {
        int paranteze=0;

        int i;
        for(i=1; s[i]!='\0'; i++)
        {
            string c(1,s[i]);
            if(s[i]=='(')
                paranteze++;
            else if(s[i]==')')
                paranteze--;
            else if(isOperator(c) && paranteze==0)
            {
                s.insert(s.begin()+i,')');
                break;
            }

        }

        if(s[i]=='\0')
            s=s+")";
        s="(0"+s;



    }
    else if(s[0]=='+')  //+f(x)=f(x)
        s.erase(s.begin());



    stack<char> st;  //verificam parantezarea
    if(ok)
        for(int i=0; s[i]!='\0'; i++)
        {
            if (s[i] == '(')
                st.push(s[i]);
            else if(s[i]==')')
            {
                if (!st.empty() && st.top() == '(')
                    st.pop();
                else
                {
                    outtextxy(0,80,"Eroare: Parantezare gresita!");
                    ok=false;
                    break;
                }
            }
        }
    if(!st.empty())
    {
        outtextxy(0,80,"Eroare: Parantezare gresita!");
        ok=false;
    }

    if(ok)
        for(int i=0; s[i+1]!='\0'; i++)
        {
            string t1(1,s[i]);
            string t2(1,s[i+1]);

            if(t1=="(" && (t2!="(" && t2!="+" && t2!="-" && isOperator(t2)))  // forma (operator este gresita. Ex: (*,(/, dar (+ si (- sunt corecte
            {
                outtextxy(0,80,"Eroare!");
                ok=false;
            }
            if(t1!=")" && isOperator(t1) && t2==")")    //forma operator) este gresita. Ex: +),-),*)
            {
                outtextxy(0,80,"Eroare!");
                ok=false;
            }

        }



    for(int i=0; s[i]!='\0'; i++)
    {
        if(s[i]=='-' && s[i-1]=='(')    //(-f(x))=(0-f(x))
            s.insert(s.begin()+i, '0');
        else if(s[i]=='+' && s[i-1]=='(')  //(+f(x))=f(x)
            s.erase(s.begin()+i);
    }


    //f(x)-(g(x)+n-y)=f(x)-g(x)-n+y
    int check;
    if(ok)
    {
        do
        {
            check=0;
            int i=0,j;
            for(i=0; s[i]!='\0'; i++)
            {
                if(s[i]=='-' && s[i+1]=='(')
                {
                    int paranteze=0;
                    for(j=i+1; s[j]!='\0'; j++)
                    {
                        if(s[j]=='(')
                            paranteze++;
                        else if(s[j]==')')
                            paranteze--;
                        else if(s[j]=='+' && paranteze==1)
                        {
                            s[j]='-';
                            check=1;
                        }

                        else if(s[j]=='-' && paranteze==1)
                        {
                            if(s[j-1]=='(')
                                s.erase(s.begin()+j);
                            else
                                s[j]='+';
                            check=1;
                        }

                        if(paranteze==0)
                            break;
                    }
                    s.erase(s.begin()+j);
                    s.erase(s.begin()+i+1);

                }

            }
        }
        while(check);
    }

    if(ok)
        for (int i = 0; i < s.length(); i++)
        {
            if (isalpha(s[i]))
                continue;
            if (isdigit(s[i]))
                continue;
            string optest(1,s[i]);
            if (isOperator(optest))
                continue;

            // daca caracterul este un punct, verificam daca e un numar cu decicmale
            if (s[i] == '.')
            {

                if (i == 0 || i == s.length() - 1 || !isdigit(s[i - 1]) || !isdigit(s[i + 1]))
                {
                    outtextxy(0,80,"Eroare: Simbolul '.' nu este folosit corect!");
                    ok = false;
                    break;
                }

            }
            else if(s[i]==',')       // verificam aparitia virgulei daca este folosita intr-o functie log
            {
                int check=0;

                for(int j=i-1; j>=3 && check==0; j--)
                {
                    if(s[j]==',')
                    {
                        check=1;
                        ok=false;
                        outtextxy(0,80,"Eroare: Simbolul ',' nu este folosit corect!");
                        break;
                    }
                    else if(s[j]=='(' && verifcareExpresieLog(s[j-3],s[j-2],s[j-1]))
                    {
                        check=1;
                        if(s[i+1]==')')
                        {
                            outtextxy(0,80,"Eroare: Logaritmul are nevoie de doi parametri, fiind de forma log(b,a), unde 'b' este baza si 'a' este argumentul!");
                            ok=false;
                        }
                    }
                }
                if(check==0)
                {
                    check=1;
                    ok=false;
                    outtextxy(0,80,"Eroare: Simbolul ',' nu este folosit corect!");
                    break;
                }



            }
            else   //nu este ok
            {
                outtextxy(0,80,"Eroare: Simbolul ',' nu este folosit corect!");
                ok = false;
                break;
            }

        }




    while(ok)
    {

        for(int i=0; s[i]!='\0'; i++)
        {
            char ElementCurent=s[i];
            //map care retine existenta formulelor specifice care trebuie sa contina argumente
            map<string,int> mp;
            {
                mp["sin"] = verifcareExpresieSinus(ElementCurent,s[i+1],s[i+2]);
                mp["cos"] = verifcareExpresieCosinus(ElementCurent,s[i+1],s[i+2]);
                mp["tg"] = verifcareExpresieTangenta(ElementCurent,s[i+1]);
                mp["ctg"] = verificareExpresieCotangenta(ElementCurent,s[i+1],s[i+2]);
                mp["arcsin"] = verifcareExpresieArcsinus(ElementCurent,s[i+1],s[i+2],s[i+3], s[i+4], s[i+5]);
                mp["arccos"] = verifcareExpresieArccosinus(ElementCurent,s[i+1],s[i+2],s[i+3], s[i+4], s[i+5]);
                mp["arctg"] = verifcareExpresieArctangenta(ElementCurent,s[i+1],s[i+2],s[i+3], s[i+4]);
                mp["arcctg"] = verifcareExpresieArccotangenta(ElementCurent,s[i+1],s[i+2],s[i+3], s[i+4], s[i+5]);
                mp["sqrt"] = verifcareExpresieSqrt(ElementCurent,s[i+1],s[i+2],s[i+3]);
                mp["log"] = verifcareExpresieLog(ElementCurent,s[i+1],s[i+2]);
                mp["ln"] = verifcareExpresieLn(ElementCurent,s[i+1]);
                mp["lg"] = verifcareExpresieLg(ElementCurent,s[i+1]);
                mp["neg"] = verifcareExpresieNegatie(ElementCurent,s[i+1],s[i+2]);
            }
            map<string,int> :: iterator itr;  //iterator
            int verificareFunctieCuArgument = 0;
            for(itr=mp.begin(); itr!=mp.end(); itr++) //trecem prin fiecare membru din map sa aflam daca exista o expresie de tip sin/cos/lg etc.
            {
                verificareFunctieCuArgument+=itr->second;
                if(verificareFunctieCuArgument)
                    break;
            }
            if(s[i]==' ')
                continue;
            else if(s[i]==',')   //tratam manipularea string-ului daca gasim o virgula care apartine de un log, marcand terminarea bazei
            {
                string Element=Stiva.top();
                while(!Stiva.empty() && Element!="(")
                {
                    ExprPostOrdine+=Element;
                    ExprPostOrdine+=";";
                    Stiva.pop();
                    Element=Stiva.top();
                }
            }
            else if(s[i]>='0' && s[i]<='9')    //construim numarul
            {
                string Numar(1,s[i]);
                int j;
                for(j=i+1; s[j]!='\0' && ((s[j]>='0' && s[j]<='9') || s[j]=='.'); j++)
                {
                    string nr(1,s[j]);
                    Numar+=nr;
                }
                i=j-1;
                ExprPostOrdine+=Numar;
                ExprPostOrdine+=";";

            }
            else if (isalpha(ElementCurent))
            {
                string cpy(1,s[i+1]);
                if((verificareFunctieCuArgument==0 && (isalpha(s[i+1]) || s[i+1]=='(')))   // la aparitia unui grup de litere care nu formeaza o functie, se va cconsidera ca voia sa fie scrisa inmultirea (ex: xyz va deveni x*y*z)
                {
                    s.insert(s.begin()+i+1,'*');
                    i--;

                }

                else if(verificareFunctieCuArgument==0 && s[i+1]>='0' && s[i+1]<='9')       //daca litera nu formeaza o functie, verificam daca este o variabila indexata
                {
                    string VariabilaIndexata(1,s[i]);
                    string sj(1,s[i]);
                    int j;
                    for(j=i+1; s[j]!='\0' && !isOperator(sj) && s[j]>='0' && s[j]<='9'; j++)
                    {
                        string fct(1,s[j]);
                        VariabilaIndexata+=fct;
                        sj=s[j+1];
                    }
                    i=j-1;
                    ExprPostOrdine+=VariabilaIndexata;
                    ExprPostOrdine+=";";
                }

                else if(verificareFunctieCuArgument==0)  //litera e o variabila
                {
                    ExprPostOrdine+=ElementCurent;
                    ExprPostOrdine+=";";
                }

                else if(verificareFunctieCuArgument && (s[i+itr->first.size()]==' ' || s[i+itr->first.size()]=='\0'))   //daca este un spatiu dupa functia, probabil utilizatorul a incercat sa scrie f(x) ca f (x), ceea ce nu este ok
                {
                    char fct[256];
                    strcpy(fct,stringtochar(itr->first));
                    outtextxy(0,80,"Eroare: Functia ");
                    outtextxy(textwidth("Eroare: Functia "),80,fct);
                    outtextxy(textwidth("Eroare: Functia ")+textwidth(fct),80," cere parantezare legata de ea!");

                    ok=false;
                    break;
                }
                else if(verificareFunctieCuArgument && isalnum(s[i+itr->first.size()]))   //caz daca utilizatorul a incercat sa scrie f(x) ca fx
                {
                    char fct[256];
                    strcpy(fct,stringtochar(itr->first));
                    outtextxy(0,80,"Eroare: Functia ");
                    outtextxy(textwidth("Eroare: Functia "),80,fct);
                    outtextxy(textwidth("Eroare: Functia ")+textwidth(fct),80," cere parantezare legata de ea!");
                    ok=false;
                    break;
                }
                else if(verificareFunctieCuArgument)
                {
                    if(itr->first=="log")   //verificam la log-ul sa aiba doi parametri
                    {
                        int checkLog=0;
                        for(int j=i+2; s[j]!='\0'; j++)
                            if(s[j]==',')
                                checkLog=1;
                        if(checkLog==0)
                        {
                            outtextxy(0,80,"Eroare: Logaritmul are nevoie de doi parametri, fiind de forma log(b,a), unde 'b' este baza si 'a' este argumentul!");
                            ok=false;
                            break;
                        }

                    }
                    else if(s[i+itr->first.size()]=='(' && s[i+itr->first.size()+1]==')')   //verificam ca o functie sa nu fie de forma f(), adica fara parametri
                    {
                        char fct[256];
                        strcpy(fct,stringtochar(itr->first));
                        outtextxy(0,80,"Eroare: Functia ");
                        outtextxy(textwidth("Eroare: Functia "),80,fct);
                        outtextxy(textwidth("Eroare: Functia ")+textwidth(fct),80," are nevoie de doi parametri!");
                        ok=false;
                        break;
                    }
                    if(ok)
                    {
                        Stiva.push(itr->first);
                        i+=itr->first.size()-1;
                    }

                }
            }

            else if(ElementCurent=='(')    //tratam cazul unei paranteze
                Stiva.push("(");
            else if(ElementCurent==')')
            {
                while(Stiva.top()!="(")
                {
                    ExprPostOrdine+=Stiva.top();
                    ExprPostOrdine+=";";
                    Stiva.pop();
                }
                Stiva.pop();
            }
            else           //daca elementul citit este un operator
            {
                string stringElementCurent(1,ElementCurent);
                while(!Stiva.empty() && prioritati(stringElementCurent)<= prioritati(Stiva.top()))
                {
                    ExprPostOrdine+=Stiva.top();
                    ExprPostOrdine+=";";
                    Stiva.pop();
                }
                Stiva.push(stringElementCurent);
            }

        }
        while(!Stiva.empty())
        {
            ExprPostOrdine+=Stiva.top();
            ExprPostOrdine+=";";
            Stiva.pop();
        }
        ExprPostOrdine.pop_back(); //elimina ultimul ";" din string
        return ExprPostOrdine;
    }

}
