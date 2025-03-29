#ifndef GRAFICA_H_INCLUDED
#define GRAFICA_H_INCLUDED
char transformare(char v[256]);
void Butoane_meniu(int limba, bool ok, nod *n1, nod*n2);
void CitesteSir(int x, int y, char mesaj[], char S[150]);
void drawButton(int left, int top, int right, int bottom,char v[256]);
int nr_noduri(nod* n);
int inaltime(nod* n);
void FILL(nod* n);
void Desen_arbore_Inordine(nod* n, int level, int height, int totalNodes);
void Desenare(nod* n) ;
void meniu();
#endif
