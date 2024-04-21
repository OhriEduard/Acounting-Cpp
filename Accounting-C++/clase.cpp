#ifndef ITEM_CPP
#define ITEM_CPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Item
{
    string data, categorie;
    int suma;
    public :
    Item();
    Item (string, string, int);
    string getItemData ();
    string getItemCategorie ();
    int getItemSuma ();

    void setItemData(string);
    void setItemCategorie(string);
    void setItemSuma (int);

    ostream& afisare(ostream&);
};

class Intrari
{
    int nr_iteme;
    vector<Item*> intrari;
    public :
    Intrari(int nr_iteme = 0): nr_iteme(nr_iteme){};
    Intrari (int, vector<Item*>);

    int getNr ();
    vector <Item*> getItems ();
    void addItem (Item*);
    void deleteItem (Item*);

    friend ostream& operator << (ostream& , const Intrari&);
};

class Iesiri
{
    int nr_iteme;
    vector<Item*> iesiri;
    public :
    Iesiri (int nr_iteme = 0) : nr_iteme(nr_iteme){};
    Iesiri (int, vector<Item*>);

    int getNr ();
    vector <Item*> getItems ();
    void addItem (Item*);
    void deleteItem (Item*);

    friend ostream& operator << (ostream& , const Iesiri&);
};

#endif // ITEM_CPP
