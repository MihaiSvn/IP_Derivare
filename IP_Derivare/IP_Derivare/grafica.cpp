#include <iostream>
#include <fstream>
#include <cstring>
#include <ctype.h>
#include <stack>
#include <cmath>
#include <graphics.h>

#include "Structuri.h"
#include "grafica.h"
#include "conversie.h"
#include "Transformare_Din_Inordine_In_Postordine.h"
#include "CreareArboreSintaxa.h"
#include "Functii_De_Derivare.h"
#include "Simplificari.h"
#include "Verificare_Erori.h"

using namespace std;

void Butoane_meniu(int limba, bool ok, nod *n1, nod *n2)
{
    int x,y;
    int left = getmaxx()-150, top = getmaxy()-125, right = getmaxx(), bottom = getmaxy()-100;
    char v[5][256];
    while (!ismouseclick(WM_LBUTTONDOWN))
    {
        delay(100);
        getmouseclick(WM_LBUTTONDOWN, x, y);

        // Check if click is inside the button
        if (x >= getmaxx()-150 && x <= getmaxx() && y >= getmaxy()-125 && y <= getmaxy()-100)
        {
            ok=FALSE;
            limba=1;
            setviewport(0,0,getmaxx(),600,2);
            cleardevice();
            //rectangle(0,0,getmaxx(),600);
            setcolor(7);
            for(int i=0; i<40; i++)
            {
                line(0,i*30,getmaxx(),i*30);
                line(i*40,0,i*40,600);
            }
            setcolor(15);
            //setfillstyle(7, 7);
            //floodfill(getmaxx(),getmaxy(), 15);
            outtextxy(getmaxx()/2,10,"Graphics project");
            outtextxy(getmaxx()/2,30,"Derivation");
            outtextxy(getmaxx()/2,50,"Savin Mihai-Alexandru");
            outtextxy(getmaxx()/2,70,"Hodea Sasha-Carol");
            outtextxy(getmaxx()/2,90,"Year I, Group B3");
            outtextxy(getmaxx()/2-300,getmaxy()/2-160, "This message will disappear after pressing the read function button.");

            outtextxy(getmaxx()/2-300,getmaxy()/2-120, "Press the reset buttons to review the message and if an input error occurs");
            outtextxy(getmaxx()/2-300,getmaxy()/2,"The program reads the menu function and an argument variable");
            outtextxy(getmaxx()/2-300,getmaxy()/2+20,"Writing recommendations: parentheses for established functions, parentheses for syntactic correctness e.g.((x+3)*3)^4");
            outtextxy(getmaxx()/2-300,getmaxy()/2+40,"Possible functions: sin(*),cos(*),tg(*),ctg(*),arcsin(*),arccos(*),arctg(*),arcctg(*),neg(*),log(*,*)");
            outtextxy(getmaxx()/2-300,getmaxy()/2+60,"lg(*),ln(*),sqrt(*), and the possible operations are addition, subtraction, multiplication, ratio and raising to power");
            strcpy(v[0],"english/reset");
            strcpy(v[1],"second derivative");
            strcpy(v[2],"function reading");
            strcpy(v[3],"first derivative");
            strcpy(v[4],"romanian/reset");
            for(int i=0; i<=4; i++)
            {
                if(i%2==0||ok==TRUE)
                {
                    drawButton(left, top-i*100, right, bottom-i*100,v[i]);
                }
            }
        }
        if (x >= getmaxx()-150 && x <= getmaxx() && y >= getmaxy()-225 && y <= getmaxy()-200 && ok==TRUE)
        {
            if(n2!=NULL)
            {
                setviewport(0,50,getmaxx()-150,550,1);
                clearviewport();
                Desenare(n2);
                FILL(n2);
                setfillstyle(0,BLACK);
                floodfill(getmaxx()-10,600-10,LIGHTGRAY);
            }

        }
        if (x >= getmaxx()-150 && x <= getmaxx() && y >= getmaxy()-325 && y <= getmaxy()-300)
        {
            setviewport(0,50,getmaxx()-150,550,1);
            clearviewport();
            char S[150];
            char vari[150];
            if(limba==0)
            {
                CitesteSir(0,0, "Cititi functia", S);
                outtextxy(0,20,S);
                CitesteSir(0,40,"Cititi variabila",vari);
                outtextxy(0,60,vari);
            }
            else
            {
                CitesteSir(0,0, "Give function", S);
                outtextxy(0,20,S);
                CitesteSir(0,40,"Give variable",vari);
                outtextxy(0,60,vari);
            }
            //CitesteVariabila(0,40,"Cititi variabila",c);
            string t=chartostring(S);
            string var=chartostring(vari);


            bool okexpr;

            if(Error_Check_Variabila(var)==1)
                okexpr=TRUE;
            else okexpr=FALSE;

            string Postordine=Transformare_PostOrdine(t,okexpr);


            if(Error_Check_Variabila(var)==1 && okexpr==TRUE) //daca nu apare nicio eroare la variabila si nici la expresie, putem afisa derivatele
            {
                nod *n; //nod *n1, *n2;
                n=CreareArboreSintaxa(Postordine);
                Start_Simplificare(n,vari);
                bool okarbore=true;
                Error_Check_Arbore(n,okarbore);
                if(okarbore==true)
                {
                    n1=CreareArboreSintaxa(Postordine);
                    n2=CreareArboreSintaxa(Postordine);

                    Start_Simplificare(n1,vari);

                    Derivare(n1,var);

                    Start_Simplificare(n1,vari);

                    char pstfixata[256];
                    strcpy(pstfixata,stringtochar(Postordine));

                    if(limba==0)
                    {
                        outtextxy(0,100,"Forma postfixata a functiei: ");
                        outtextxy(textwidth("Forma postfixata a functiei: "),100,pstfixata);
                    }
                    else
                    {
                        outtextxy(0,100,"Postfix expression of the function: ");
                        outtextxy(textwidth("Postfix expression of the function: "),100,pstfixata);
                    }


                    if(limba==0)
                    {
                        outtextxy(0,140,"Prima derivata: ");
                    }
                    else
                    {
                        outtextxy(0,140,"First derivative: ");
                    }
                    string derivI;
                    DFS(n1,derivI);
                    derivI.pop_back();
                    char PostordineDerivI[256];
                    strcpy(PostordineDerivI,stringtochar(derivI));
                    derivI=Transformare_InOrdine(derivI);
                    char *derI;
                    derI=stringtochar(derivI);
                    if(limba==0)
                    {
                        outtextxy(textwidth("Prima derivata: "),140,derI);
                    }
                    else
                    {
                        outtextxy(textwidth("First derivative: "),140,derI);
                    }

                    /*if(limba==0)
                    {
                        outtextxy(0,160,"Forma postfixata a primei derivate: ");
                        outtextxy(textwidth("Forma postfixata a primei derivate: "),160,PostordineDerivI);
                    }
                    else
                    {
                        outtextxy(0,160,"Postfix expression of the first derivative: ");
                        outtextxy(textwidth("Postfix expression of the first derivative: "),160,PostordineDerivI);
                    }*/



                    Start_Simplificare(n2,vari);
                    Derivare(n2,var);
                    Start_Simplificare(n2,vari);
                    Derivare(n2,var);
                    Start_Simplificare(n2,vari);

                    if(limba==0)
                    {
                        outtextxy(0,200,"A doua derivata: ");
                    }
                    else
                    {
                        outtextxy(0,200,"Second derivative: ");
                    }

                    string derivII;
                    DFS(n2,derivII);
                    derivII.pop_back();
                    char PostordineDerivII[256];
                    strcpy(PostordineDerivII,stringtochar(derivII));
                    derivII=Transformare_InOrdine(derivII);
                    char *derII;
                    derII=stringtochar(derivII);
                    if(limba==0)
                    {
                        outtextxy(textwidth("A doua derivata: "),200,derII);
                    }
                    else
                    {
                        outtextxy(textwidth("Second derivative: "),200,derII);
                    }

                    /*if(limba==0)
                    {
                        outtextxy(0,220,"Forma postfixata a celei de-a doua derivata: ");
                        outtextxy(textwidth("Forma postfixata a celei de-a doua derivata: "),220,PostordineDerivII);
                    }
                    else
                    {
                        outtextxy(0,220,"Postfix expression of the second derivative: ");
                        outtextxy(textwidth("Postfix expression of the second derivative: "),220,PostordineDerivII);
                    }*/






                    ok=TRUE;
                    if(limba==0)
                    {
                        drawButton(getmaxx()-175-textwidth("Arborele functiei citite"),getmaxy()-125,getmaxx()-151,getmaxy()-100,"Arborele functiei citite");
                    }
                    else
                    {
                        drawButton(getmaxx()-175-textwidth("Binary tree of function"),getmaxy()-125,getmaxx()-151,getmaxy()-100,"Binary tree of function");
                    }
                    while (!ismouseclick(WM_LBUTTONDOWN))
                    {
                        delay(100);
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if ((x >= getmaxx()-175-textwidth("Arborele functiei citite") && x <= getmaxx()-51 && y >= 525 && y <= 550 && limba==0)||(x >= getmaxx()-175-textwidth("Binary tree of function") && x <= getmaxx()-51 && y >= 525 && y <= 550 && limba==1))
                        {
                            setviewport(0,50,getmaxx()-150,550,1);
                            clearviewport();
                            setfillstyle(SOLID_FILL, MAGENTA);
                            Desenare(n);
                            FILL(n);
                            setfillstyle(0,BLACK);
                            floodfill(getmaxx()-10,600-10,LIGHTGRAY);
                            //clearviewport()
                            setviewport(0,0,getmaxwidth(),600,1);
                            if(limba==1)
                            {
                                strcpy(v[1],"second derivative");
                                strcpy(v[3],"first derivative");
                            }
                            else
                            {
                                strcpy(v[1],"a doua derivata");
                                strcpy(v[3],"prima derivata");
                            }
                            drawButton(left, top-100, right, bottom-100,v[1]);
                            drawButton(left,top-300,right,bottom-300,v[3]);
                            Butoane_meniu(limba,ok,n1,n2);
                        }

                    }
                }

            }




        }
        if (x >= getmaxx()-150 && x <= getmaxx() && y >= getmaxy()-425 && y <= getmaxy()-400 && ok==TRUE)
        {
            if(n1!=NULL)
            {
                setviewport(0,50,getmaxx()-150,550,1);
                clearviewport();
                Desenare(n1);
                FILL(n1);
                setfillstyle(0,BLACK);
                floodfill(getmaxx()-10,600-10,LIGHTGRAY);
            }

        }
        if (x >= getmaxx()-150 && x <= getmaxx() && y >= getmaxy()-525 && y <= getmaxy()-500)
        {
            ok=FALSE;
            limba=0;
            setviewport(0,0,getmaxx(),600,2);
            cleardevice();
            //rectangle(0,0,getmaxx(),600);
            setcolor(7);
            for(int i=0; i<40; i++)
            {
                line(0,i*30,getmaxx(),i*30);
                line(i*40,0,i*40,600);
            }
            //setfillstyle(7, 7);
            //floodfill(getmaxx(),getmaxy(), 15);
            setcolor(15);
            outtextxy(getmaxx()/2,10,"Proiect Grafica");
            outtextxy(getmaxx()/2,30,"Derivare");
            outtextxy(getmaxx()/2,50,"Savin Mihai-Alexandru");
            outtextxy(getmaxx()/2,70,"Hodea Sasha-Carol");
            outtextxy(getmaxx()/2,90,"Anul I, Grupa B3");
            outtextxy(getmaxx()/2-300,getmaxy()/2-160, "Acest mesaj va disparea dupa apasarea butonului de citire a functiei.");

            outtextxy(getmaxx()/2-300,getmaxy()/2-120, "Apasati butoanele reset pentru a revedea mesajul si daca apare o eroare la input");
            outtextxy(getmaxx()/2-300,getmaxy()/2,"Programul citeste functia din meniu si o variabila argument");
            outtextxy(getmaxx()/2-300,getmaxy()/2+20,"Recomandari scriere:  paranteze pentru functii consacrate, paranteze pentru corectitudine sintactica ex:((x+3)*3)^4");
            outtextxy(getmaxx()/2-300,getmaxy()/2+40,"Functiile posibile: sin(*),cos(*),tg(*),ctg(*),arcsin(*),arccos(*),arctg(*),arcctg(*),neg(*),log(*,*)");
            outtextxy(getmaxx()/2-300,getmaxy()/2+60,"lg(*),ln(*),sqrt(*), iar operatiile posibile sunt adunarea,scaderea,inmultirea,raportul si ridicarea la putere");

            strcpy(v[0],"engleza/reset");
            strcpy(v[1],"a doua derivata");
            strcpy(v[2],"citire functie grafica");
            strcpy(v[3],"prima derivata");
            strcpy(v[4],"romana/reset");
            for(int i=0; i<=4; i++)
            {
                if(ok==TRUE || i%2==0)
                {
                    drawButton(left, top-i*100, right, bottom-i*100,v[i]);
                }

            }
        }
    }
}
char transformare(char v[256])
{
    if(strchr("1234567890",v[0])==NULL)
    {
        return v[256];
    }
    else
    {
        char t[11];//1.2*10^256
        t[0]=v[0];
        strcat(t,".");
        t[2]=v[1];//1.2
        strcat(t,"*10^"); //*10^
        //sir de caractere de forma strlen(v)-1
        int aux=strlen(v)-1;
        char c[4];
        int j=0;
        while(aux)
        {
            c[j]=aux%10+'0';
            j++;
            aux/=10;
        }
        strcat(t,strrev(c));
    }
}
int In=0;
void FILL(nod* n)
{
    int r=13;
    if(n!=NULL)
    {
        setfillstyle(1,MAGENTA);
        if(n->xo && n->yo)floodfill(n->xo,n->yo-r+2,LIGHTGRAY);
    }
    if(n->st!=NULL)FILL(n->st);
    if(n->dr!=NULL)FILL(n->dr);
}
void CitesteSir(int x, int y, char mesaj[], char S[150])
{

    char Enter = 13, BackSpace = 8, Escape = 27;
    char MultimeDeCaractereAcceptabile[255] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz()[]{}*+-^/,.";
    char Sinitial[100], tasta;
    char Ss[150], mesajs[200];

    strcpy(Sinitial,S);
    setcolor(WHITE);
    strcpy(mesajs,mesaj);
    strcat(mesajs,":");
    outtextxy(x,y,mesajs);
    x=x+textwidth(mesajs);
    strcpy(S,"");
    do
    {
        tasta=getch();
        if (tasta==0)
        {
            tasta=getch();
            Beep(200,200);
        }
        else if (strchr(MultimeDeCaractereAcceptabile,tasta)&&strlen(S)<=sizeof(Ss))
        {
            // stergem fostul sir
            strcpy(Ss,S);
            strcat(Ss,"_ ");
            setcolor(BLACK);
            outtextxy(x,y,Ss);
            char tt2[2];
            tt2[0]=tasta;
            tt2[1]=0;
            strcat(S,tt2);
            // afisam pe cel nou }
            strcpy(Ss,S);
            strcat(Ss,"_ ");
            setcolor(WHITE);
            outtextxy(x,y,Ss);
        }
        else if (tasta == BackSpace)
        {
            if (!strcmp(S,""))
                Beep(200,200);
            else
            {
                strcpy(Ss,S);
                strcat(Ss,"_");
                setcolor(BLACK);
                outtextxy(x,y,Ss);
                setcolor(WHITE);
                S[strlen(S)-1]=0;
                strcpy(Ss,S);
                strcat(Ss,"_ ");
                outtextxy(x,y,Ss);
            }
        }
        else if (tasta!=Enter && tasta!=Escape)
            Beep(200,200);
    }
    while (tasta!=Enter && tasta!=Escape);
    if (tasta == Escape)
        strcpy(S,Sinitial);
    setcolor(BLACK);
    strcpy(Ss,S);
    strcat(Ss,"_ ");
    outtextxy(x,y,Ss);
    setcolor(WHITE);
    //outtextxy(x,y,S);

}
void drawButton(int left, int top, int right, int bottom,char v[256])
{
    setcolor(15);
    rectangle(left, top, right, bottom);
    setfillstyle(SOLID_FILL, MAGENTA);
    outtextxy(left + 5, top + 5, v);
    floodfill((left + right) / 2+10, (top + bottom) / 2+10, 15);

}
int nr_noduri(nod* n)
{
    if(n==NULL)
        return 0;
    while (n)
    {
        return 1+nr_noduri(n->st)+nr_noduri(n->dr);
    }


}
int inaltime(nod* n)
{
    if(n==NULL)
        return -1;
    return max(inaltime(n->st)+1,inaltime(n->dr)+1);
}
void Desen_arbore_Inordine(nod* n, int level, int height, int totalNodes)
{
    if (n != NULL) // conditie de oprire
    {
        int dy = 600 / (height+4);  // distanta verticala
        int dx = (getmaxx()-150) / (totalNodes + 1);  // Fiecare nod in inordine are o anumita pozitie pe axa OX

        // Apelare Stanga S (SRD)
        Desen_arbore_Inordine(n->st, level + 1, height, totalNodes);


        // Calcularea pozitiei fiecarui nod (centrul nodului) {cazul Radacina}
        int x = (In + 1) * dx;
        int y= level*dy;
        //Retinem pozitia centrului in doua valori din structura nod (xo si yo)
        n->xo=x;
        n->yo=y;
        In++;
        setcolor(LIGHTGRAY);
        // Desenare nod
        int r = 13;
        char c[(n->val).length()+1];
        strcpy(c,stringtochar(n->val));
        int text_w = textwidth(c);

        if(text_w>r)
        {
            ellipse(x, level * dy, 0, 360, text_w/2 + text_w/4 + 2, r);
        }
        else
        {
            ellipse(x,level*dy,0,360,r,r);
        }
        outtextxy(x - text_w / 2, level * dy-8,c);
        //delete s;

        // Apelare Dreapta D (SRD)

        Desen_arbore_Inordine(n->dr, level + 1, height, totalNodes);
        //Desenarea liniilor dintre noduri cu ajutorul coordonatelor xo si yo
        if (n->st != NULL && n->st->xo!=0 &&  n->st->yo!=0)
        {
            setcolor(LIGHTGRAY);
            line(x, y+r, n->st->xo, n->st->yo-r);
        }
        if (n->dr != NULL && n->dr->xo!=0 && n->dr->yo!=0)
        {
            setcolor(LIGHTGRAY);
            line(x, y+r, n->dr->xo, n->dr->yo-r);
        }
    }
}
void Desenare(nod* n)
{
    int noduri = nr_noduri(n);
    In = 0;
    Desen_arbore_Inordine(n, 1, inaltime(n)+1, noduri);
}
void meniu()
{

    setbkcolor(0);
    cleardevice();
    rectangle(0,0,getmaxx(),600);
    setcolor(7);
    for(int i=0; i<40; i++)
    {
        line(0,i*30,getmaxx(),i*30);
        line(i*40,0,i*40,600);
    }
    setcolor(15);
    outtextxy(getmaxx()/2,10,"Proiect Grafica");
    outtextxy(getmaxx()/2,30,"Derivare");
    outtextxy(getmaxx()/2,50,"Savin Mihai-Alexandru");
    outtextxy(getmaxx()/2,70,"Hodea Sasha-Carol");
    outtextxy(getmaxx()/2,90,"Anul I, Grupa B3");
    outtextxy(getmaxx()/2-300,getmaxy()/2-160, "Acest mesaj va disparea dupa apasarea butonului de citire a functiei.");

    outtextxy(getmaxx()/2-300,getmaxy()/2-120, "Apasati butoanele reset pentru a revedea mesajul si daca apare o eroare la input");
    outtextxy(getmaxx()/2-300,getmaxy()/2,"Programul citeste functia din meniu si o variabila argument");
    outtextxy(getmaxx()/2-300,getmaxy()/2+20,"Recomandari scriere:  paranteze pentru functii consacrate, paranteze pentru corectitudine sintactica ex:((x+3)*3)^4");
    outtextxy(getmaxx()/2-300,getmaxy()/2+40,"Functiile posibile: sin(*),cos(*),tg(*),ctg(*),arcsin(*),arccos(*),arctg(*),arcctg(*),neg(*),log(*,*)");
    outtextxy(getmaxx()/2-300,getmaxy()/2+60,"lg(*),ln(*),sqrt(*), iar operatiile posibile sunt adunarea,scaderea,inmultirea,raportul si ridicarea la putere");




    // Coordonatele butoanelor
    int left = getmaxx()-150, top = getmaxy()-125, right = getmaxx(), bottom = getmaxy()-100;
    nod * n1,*n2;
    string var;
    bool ok=FALSE;
    char v[5][256];
    strcpy(v[0],"engleza/reset");
    strcpy(v[1],"a doua derivata");
    strcpy(v[2],"Citire functie grafica");
    strcpy(v[3],"prima derivata");
    strcpy(v[4],"romana/reset");
    for(int i=0; i<=4; i++)
    {
        if(ok==TRUE || i%2==0)
        {
            drawButton(left, top-i*100, right, bottom-i*100,v[i]);
        }

    }
    Butoane_meniu(0,ok,n1,n2);
// setviewport(); clearviewport();
    getch();
}

