#include <iostream>
#include <cstring>
using namespace std;
char *stringtochar(string s)
{
    char* ch = new char[s.length() + 1];
    int i;
    for(i=0;s[i]!='\0';i++)
    {
        ch[i]=s[i];
    }
    ch[i]='\0';
    return ch;
};
string chartostring(char s[])
{
    string str;
    str= s;
    return str;
};

