#ifndef FUNCTII_DE_DERIVARE_H_INCLUDED
#define FUNCTII_DE_DERIVARE_H_INCLUDED

void Derivare(nod*&radacina, string variabila);
int Parcurgere_Gasire_Variabila(nod*radacina, string variabila);
void Derivare_Variabila(nod*&radacina);
void Derivare_Constanta(nod*&radacina);
void Derivare_Suma(nod*&radacina, string variabila);
void Derivare_Diferenta(nod*&radacina, string variabila);
nod* DuplicareDinNod(nod* radacina);
void Derivare_Produs(nod*&radacina,string variabila);
void Derivare_Raport(nod *&radacina,string variabila);
void Derivare_Exponent(nod *&radacina, string variabila);


void Derivare_Sinus(nod *&radacina,string variabila);
void Derivare_Cosinus(nod*&radacina,string variabila);
void Derivare_Tangenta(nod*&radacina, string variabila);
void Derivare_Cotangenta(nod*&radacina,string variabila);
void Derivare_Arcsinus(nod*&radacina, string variabila);
void Derivare_Arccosinus(nod*&radacina, string variabila);
void Derivare_Arctangent(nod*&radacina,string variabila);
void Derivare_Arccotangent(nod*&radacina,string variabila);
void Derivare_SQRT(nod*&radacina,string variabila);
void Derivare_Logaritm(nod*&radacina,string variabila);
void Derivare_Logaritm_Natural(nod*&radacina,string variabila);
void Derivare_Logaritm_Zecimal(nod*&radacina,string variabila);
void Derivare_Negatie(nod*&radacina, string variabila);

#endif // FUNCTII_DE_DERIVARE_H_INCLUDED
