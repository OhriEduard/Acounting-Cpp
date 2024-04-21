#ifndef METODE_H
#define METODE_H
#include "clase.cpp"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

Item :: Item ()
{
    data = "";
    categorie = "";
    suma = 0;
}

Item :: Item (string data, string categorie, int suma)
{
    this->data = data;
    this->categorie = categorie;
    this->suma = suma;
}

string Item ::  getItemData ()
{
    return this->data;
}

string Item ::  getItemCategorie ()
{
    return this->categorie;
}

int Item :: getItemSuma ()
{
    return this->suma;
}

void Item :: setItemData (string newdata)
{
    this->data = newdata;
}

void Item :: setItemCategorie (string newcategorie)
{
    this->categorie = newcategorie;
}

void Item :: setItemSuma (int newsuma)
{
    this->suma = newsuma;
}

ostream& Item :: afisare(ostream& out)
{
    out << this->suma<<','<<this->data <<',' << this->categorie << endl;
    return out;
}


#endif // METODE_H

