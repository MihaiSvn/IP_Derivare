#ifndef SIMPLIFICARI_H_INCLUDED
#define SIMPLIFICARI_H_INCLUDED



int isNumber(string s);
double String_To_Double(string s);
string Double_To_String(double n);
void DFS_SimplificareProdus(nod*radacina, stack<nod*> &StivaElemente, double &produs, bool&ok, int&Nr_Numere, string variabila, int &putereVariabila);
void Simplificare_Produs(nod*&radacina, bool &ok,string variabila);
void DFS_SimplificareSuma(nod*radacina, stack<nod*> &StivaElemente, stack <string> &StivaSemne, double &suma, bool&ok, int&Nr_Numere);
void Simplificare_Suma(nod*&radacina, bool &ok, string variabila);
void Simplificare(nod *&radacina,int &simplificari, string variabila);
void Parcurgere_Simplificare(nod*&radacina, int &simplificari,string variabila);
void Start_Simplificare(nod*&radacina, string variabila);

#endif // SIMPLIFICARI_H_INCLUDED
