#ifndef INTR_H
#define INTR_H
#include "clase.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

Intrari :: Intrari (int nr_iteme, vector<Item*> items){
    this->nr_iteme = nr_iteme;
    this->intrari = items;
}

int Intrari :: getNr ()
{
    return this->nr_iteme;
}

vector<Item*> Intrari :: getItems ()
{
    return intrari;
}

void Intrari :: addItem (Item* item)
{
    intrari.push_back(item);
    nr_iteme++;
}

void Intrari :: deleteItem (Item* item)
{
    for (vector<Item*> :: iterator it = intrari.begin(); it < intrari.end(); it++)
    {
        if ((*it) == item)
        {
            intrari.erase(it);
            nr_iteme--;
        }
    }
}

ostream& operator << (ostream& out, const Intrari& intrare)
{
    for (int i = 0; i< intrare.nr_iteme; i++)
    {
        intrare.intrari[i]->afisare(out);
    }
    return out;
}

#endif // INTR_H
