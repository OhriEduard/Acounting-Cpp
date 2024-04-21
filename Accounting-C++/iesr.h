#ifndef IESR_H
#define IESR_H
#include "clase.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

Iesiri :: Iesiri (int nr_iteme, vector<Item*> items)
{
    this->nr_iteme = nr_iteme;
    this->iesiri = items;
}

int Iesiri :: getNr ()
{
    return this->nr_iteme;
}

vector<Item*> Iesiri :: getItems ()
{
    return iesiri;
}

void Iesiri :: addItem (Item* item)
{
    iesiri.push_back(item);
    nr_iteme++;
}

void Iesiri :: deleteItem (Item* item)
{
    for (vector<Item*> :: iterator it = iesiri.begin(); it< iesiri.end(); it++)
    {
        if ((*it) == item)
        {
            iesiri.erase(it);
            nr_iteme--;
        }
    }
}

ostream& operator << (ostream& out, const Iesiri& iesire)
{
    for (int i = 0; i<iesire.nr_iteme; i++)
    {
        iesire.iesiri[i]->afisare(out);
    }
    return out;
}

#endif // IESR_H
