#ifndef STRUCTURI_H_INCLUDED
#define STRUCTURI_H_INCLUDED

struct nod
{
    string val;
    nod *st;
    nod *dr;
    nod *parinte=NULL;
    int xo,yo;
};

#endif // STRUCTURI_H_INCLUDED
