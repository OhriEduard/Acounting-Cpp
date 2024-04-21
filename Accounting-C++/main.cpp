#include <iostream>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "clase.cpp"
#include "intr.h"
#include "iesr.h"
#include "item.h"
using namespace std;


Intrari lista_intrari;
Iesiri lista_iesiri;

void setColor (int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute (hStdOut, wColor);
    }
    return;

}

void citire_liste ()
{
    ifstream fintr,fiesr;
    fintr.open("intrari.txt");
    fiesr.open("iesiri.txt");
    char *dateintrare = new char[50];
    while (fintr.getline(dateintrare,50))
    {
        char *p;
        Item *itm_tmp = new Item;

        p = strtok(dateintrare, ",");
        while (p!=NULL)
        {
            if (itm_tmp->getItemSuma() == 0)
            {
                itm_tmp->setItemSuma(atoi(p));
            }
            else if (itm_tmp->getItemData() == "")
            {
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                itm_tmp->setItemData(p);
            }
            else if (itm_tmp->getItemCategorie() == "")
            {
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                itm_tmp->setItemCategorie(p);
            }
            p = strtok(0,",");

        }
        lista_intrari.addItem(itm_tmp);
    }

    while (fiesr.getline(dateintrare,50))
    {
        char *p;
        Item *itm_tmp = new Item;

        p = strtok(dateintrare, ",");
        while (p!=NULL)
        {
            if (itm_tmp->getItemSuma() == 0)
            {
                itm_tmp->setItemSuma(atoi(p));
            }
            else if (itm_tmp->getItemData() == "")
            {
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                itm_tmp->setItemData(p);
            }
            else if (itm_tmp->getItemCategorie() == "")
            {
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                itm_tmp->setItemCategorie(p);
            }
            p = strtok(0,",");
        }
        lista_iesiri.addItem(itm_tmp);
    }
    fintr.close();
    fiesr.close();
}

int viewItems(auto& date, int argc, char* argv[], bool cmd) // Functie de vizualizare intrari/iesiri
{
    system("cls");
    char **categorii = nullptr;
    int nr_categorii = 0;
    vector <Item*> lista_temp = date.getItems();
    for (int i = 0; i<date.getNr(); i++)
    {
        int found = 0;
        for (int j = 0; j<nr_categorii; j++)
        {
            if (categorii[j] == lista_temp[i]->getItemCategorie())
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            nr_categorii += 1;
            categorii = (char**) realloc (categorii, nr_categorii*sizeof(char*));
            categorii[nr_categorii-1] = (char*) malloc (40);
            strcpy(categorii[nr_categorii-1], lista_temp[i]->getItemCategorie().c_str());
        }
    }
    setColor(6);
    for (int i = 0; i<nr_categorii; i++)
        cout<<i+1<<". "<<categorii[i]<<endl;
    cout<<"\n\n";
    cout<<"<- BACK \"8\" \n";
    setColor(4);
    cout<<"<- EXIT \"9\" \n";
    setColor(7);
    int ok =0;
    char *chosen_cat = (char*) malloc (40);
    if (cmd == true)
    {
        strcpy(chosen_cat, argv[3]);
        chosen_cat[strlen(chosen_cat)] = '\0';
    }
    else
    {
        while (ok == 0)
        {
            cout<<"Introduceti categoria : ";
            fgets (chosen_cat, 40, stdin);
            chosen_cat[strlen(chosen_cat)-1] = '\0';
            for (int i = 0; i<nr_categorii; i++)
            {
                if (strcmp(chosen_cat, categorii[i])== 0)
                    ok = 1;
            }

            if (ok == 0)
            {
                switch (atoi(chosen_cat))
                {
                case 8 :
                    return 8;
                    break;
                case 9 :
                    exit(0);
                default :
                    setColor(4);
                    cout<< "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                    setColor(7);
                }
            }
        }
    }

    system("cls");
    setColor(6);
    int nr_date = 0;
    for (int i = 0; i<date.getNr(); i++)
    {

        if (strcmp(lista_temp[i]->getItemCategorie().c_str(), chosen_cat) == 0)
        {
            cout<<nr_date+1<<". "<<lista_temp[i]->getItemData()<<endl;
            nr_date += 1;
        }
    }
    cout<<"\n\n";
    cout<< "<- BACK \"8\" \n";
    setColor(4);
    cout<< "<- EXIT \"9\" \n";
    setColor(7);
    char *chosen_date = (char*) malloc (40);
    if (cmd == true)
    {
        strcpy(chosen_date,argv[4]);
        chosen_date[strlen(chosen_date)] = '\0';
    }
    else
    {
    ok = 0;
        while (ok == 0)
        {
            cout<<"Introduceti data : ";
            fgets (chosen_date, 40, stdin);
            chosen_date[strlen(chosen_date)-1] = '\0';
            for (int i = 0; i<date.getNr(); i++)
            {
                if (strcmp(chosen_date, lista_temp[i]->getItemData().c_str())== 0)
                    ok = 1;
            }

            if (ok == 0)
            {
                switch (atoi(chosen_date))
                {
                case 8 :
                    return 8;
                    break;
                case 9 :
                    exit(0);
                default :
                    setColor(4);
                    cout<<"  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                    setColor(7);
                }
            }

        }
    }
    system("cls");
    setColor(6);
    int nr_sums = 0;
    for (int i = 0; i<date.getNr(); i++)
    {
        if (strcmp(lista_temp[i]->getItemCategorie().c_str(), chosen_cat) == 0)
            if (strcmp(lista_temp[i]->getItemData().c_str()
            , chosen_date) == 0)
            {
                cout<<nr_sums+1<<". "<<lista_temp[i]->getItemSuma()<<endl;
                nr_sums += 1;
            }
    }
    cout<<"\n\n";
    cout<< "<- BACK \"8\" \n";
    setColor(4);
    cout<< "<- EXIT \"9\" \n";
    setColor(7);
    ok = 1;
    while (ok)
    {
        cout<<"Tasta : ";
        cin>>ok;
        cin.get();
        switch (ok)
        {
        case 8 :
            return 8;
            break;
        case 9 :
            exit(0);
        default :
            setColor(4);
            cout<<"  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
            setColor(7);
        }
    }
}

int addItems (auto& date, int argc, char* argv[], bool cmd) // Functie de adaugare intrari/iesiri
{
    vector<Item*> lista_tmp = date.getItems();
    system("cls");
    setColor(2);
    cout<<"==========Bun venit in meniul de adaugare==========\n\n";
    setColor(7);
    char* chosen_cat = (char*) malloc (40);
    int ok = 0;
    if (cmd == true)
    {
        strcpy(chosen_cat, argv[3]);
        chosen_cat[strlen(chosen_cat)] = '\0';
    }

    char* chosen_date = (char*) malloc (30);
    if (cmd == false)
    {
        cout<<"Introduceti categoria pe care vreti sa o adaugati(max. 40 caractere) : ";
        fgets(chosen_cat, 40, stdin);
        chosen_cat[strlen(chosen_cat)-1] = '\0';
        for (int i =0 ; i<strlen(chosen_cat); i++)
        {
            chosen_cat[i] = tolower(chosen_cat[i]);
        }
        cout<<"\n";

        char *luna, *ziua, *anul;
        cout<< "Introduceti data iesiri :\n";
        cout<<"Anul (min. anul 1950) : ";
        anul = (char*) malloc (10);
        while (ok == 0)
        {
            fgets(anul, 10, stdin);
            anul[strlen(anul)-1] = '\0';
            if (strlen(anul) <= 0 || strlen(anul) > 4)
            {
                setColor(4);
                cout<<"Anul introdus este incorect !! \n\n";
                setColor(7);
            }
            else if (atoi(anul) < 1950 || atoi(anul) > 2023)
            {
                setColor(4);
                cout<<"Anul introdus este incorect !! \n\n";
                setColor(7);
            }
            else
                ok = 1;

            if (ok == 0)
                cout<< "Reintroduceti anul : ";
        }


        cout<< "Luna : ";
        luna = (char*) malloc (40);
        ok = 0;
        while (ok == 0)
        {
            fgets (luna,10,stdin);
            luna[strlen(luna)-1] = '\0';
            if (strlen(luna) <= 0 || strlen(luna)>2)
            {
                setColor(4);
                cout<<"Luna introdusa este incorecta !! \n\n";
                setColor(7);
            }
            else if (atoi(luna) < 1 || atoi(luna) > 12)
            {
                setColor(4);
                cout<<"Luna introdusa este incorecta !! \n\n";
                setColor(7);
            }
            else
                ok = 1;

            if (ok == 0)
                cout<< "Reintroduceti luna : ";
        }

        cout<< "Ziua : ";
        ziua = (char*) malloc (10);
        ok = 0;
        while (ok == 0)
        {
            fgets (ziua, 10, stdin);
            ziua[strlen(ziua)-1] = '\0';
            if (strlen(ziua) <= 0 || strlen(ziua)>2)
            {
                setColor(4);
                cout<<"Ziua introdusa este incorecta !! \n\n";
                setColor(7);
            }
            else
            {
                if (atoi(luna) == 1 || atoi(luna) == 3 || atoi(luna) == 5 ||
                        atoi(luna) == 7 || atoi(luna) == 8 || atoi(luna) == 10 || atoi(luna) == 12)
                {
                    if (atoi(ziua) > 31 || atoi(ziua) < 1)
                    {
                        setColor(4);
                        cout<<"Ziua introdusa este incorecta !! \n\n";
                        setColor(7);
                    }
                    else
                    {
                        ok = 1;
                    }
                }

                if (atoi(luna) == 2 || atoi(luna) == 4 || atoi(luna) == 6 ||
                        atoi(luna) == 9 || atoi(luna) == 11)
                {
                    if (atoi(luna) == 2)
                    {
                        if (atoi(anul)%4 == 0)
                        {
                            if (atoi(ziua) > 29 || atoi(ziua) < 1)
                            {
                                setColor(4);
                                cout<<"Ziua introdusa este incorecta !! \n\n";
                                setColor(7);
                            }
                            else
                            {
                                ok = 1;
                            }
                        }
                        else
                        {
                            if (atoi(ziua) > 28 || atoi(ziua) < 1)
                            {
                                setColor(4);
                                cout<<"Ziua introdusa este incorecta !! \n\n";
                                setColor(7);
                            }
                            else
                            {
                                ok = 1;
                            }
                        }
                    }
                    else if (atoi(ziua) > 30 || atoi(ziua) < 1)
                    {
                        setColor(4);
                        cout<<"Ziua introdusa este incorecta !! \n\n";
                        setColor(7);
                    }
                    else
                    {
                        ok = 1;
                    }
                }
            }
            if (ok == 0)
                cout<< "Reintroduceti ziua : ";
        }
        strcpy(chosen_date,ziua);
        strcat(chosen_date,"/");
        strcat(chosen_date,luna);
        strcat(chosen_date,"/");
        strcat(chosen_date,anul);
    }
    else
    {
        strcpy(chosen_date, argv[4]);
        chosen_date[strlen(chosen_date)] = '\0';
    }

    int chosen_suma;
    if (cmd == true)
    {
        chosen_suma = atoi(argv[5]);
    }
    else
    {
        cout<< "\n";
        cout<< "Introduceti suma :";
        ok = 0;
        while (ok == 0)
        {
            cin>>chosen_suma;
            cin.get();
            if (chosen_suma == 0)
            {
                setColor(4);
                cout<<("Nu poate sa existe suma 0 !! \n\n");
                setColor(7);
            }
            else
                ok = 1;

            if (ok == 0)
            {
                cout<< ("Reintroduceti suma : ");
            }
        }
    }

    date.addItem(new Item(chosen_date, chosen_cat, chosen_suma));

    setColor(2);
    cout<< ("! Cererea a fost inregistrata cu succes !");

    setColor(6);
    cout<<("\n\n");
    cout<< ("<- BACK \"8\" \n");
    setColor(4);
    cout<< ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        cout<<("Tasta : ");
        scanf("%d", &ok);
        cin.get();
        switch (ok)
        {
        case 8 :
            return 8;
            break;
        case 9 :
            exit(0);
        default :
            setColor(4);
            cout<< "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
            setColor(7);
        }
    }
}

int deleteItems(auto& date, int argc, char* argv[], bool cmd) // Functie de stergere intrari/iesiri
{
    system("cls");
    char **categorii = nullptr;
    int nr_categorii = 0;
    vector <Item*> lista_temp = date.getItems();
    for (int i = 0; i<date.getNr(); i++)
    {
        int found = 0;
        for (int j = 0; j<nr_categorii; j++)
        {
            if (categorii[j] == lista_temp[i]->getItemCategorie())
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            nr_categorii += 1;
            categorii = (char**) realloc (categorii, nr_categorii*sizeof(char*));
            categorii[nr_categorii-1] = (char*) malloc (40);
            strcpy(categorii[nr_categorii-1], lista_temp[i]->getItemCategorie().c_str());
        }
    }
    setColor(6);
    for (int i = 0; i<nr_categorii; i++)
        cout<<i+1<<". "<<categorii[i]<<endl;
    cout<<"\n\n";
    cout<<"<- BACK \"8\" \n";
    setColor(4);
    cout<<"<- EXIT \"9\" \n";
    setColor(7);
    int ok =0;
    char *chosen_cat = (char*) malloc (40);
    if (cmd == true)
    {
        strcpy(chosen_cat, argv[3]);
        chosen_cat[strlen(chosen_cat)] = '\0';
    }
    else
    {
        while (ok == 0)
        {
            cout<<"Introduceti categoria : ";
            fgets (chosen_cat, 40, stdin);
            chosen_cat[strlen(chosen_cat)-1] = '\0';
            for (int i = 0; i<nr_categorii; i++)
            {
                if (strcmp(chosen_cat, categorii[i])== 0)
                    ok = 1;
            }

            if (ok == 0)
            {
                switch (atoi(chosen_cat))
                {
                case 8 :
                    return 8;
                    break;
                case 9 :
                    exit(0);
                default :
                    setColor(4);
                    cout<< "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                    setColor(7);
                }
            }
        }
    }

    system("cls");
    setColor(6);
    int nr_date = 0;
    for (int i = 0; i<date.getNr(); i++)
    {

        if (strcmp(lista_temp[i]->getItemCategorie().c_str(), chosen_cat) == 0)
        {
            cout<<nr_date+1<<". "<<lista_temp[i]->getItemData()<<endl;
            nr_date += 1;
        }
    }
    cout<<"\n\n";
    cout<< "<- BACK \"8\" \n";
    setColor(4);
    cout<< "<- EXIT \"9\" \n";
    setColor(7);
    char *chosen_date = (char*) malloc (40);
    if (cmd == true)
    {
        strcpy(chosen_date, argv[4]);
        chosen_date[strlen(chosen_date)] = '\0';
    }
    else
    {
        ok = 0;
        while (ok == 0)
        {
            cout<<"Introduceti data : ";
            fgets (chosen_date, 40, stdin);
            chosen_date[strlen(chosen_date)-1] = '\0';
            for (int i = 0; i<date.getNr(); i++)
            {
                if (strcmp(chosen_date, lista_temp[i]->getItemData().c_str())== 0)
                    ok = 1;
            }

            if (ok == 0)
            {
                switch (atoi(chosen_date))
                {
                case 8 :
                    return 8;
                    break;
                case 9 :
                    exit(0);
                default :
                    setColor(4);
                    cout<<"  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                    setColor(7);
                }
            }

        }
    }
    system("cls");
    setColor(6);
    int nr_sums = 0;
    for (int i = 0; i<date.getNr(); i++)
    {
        if (strcmp(lista_temp[i]->getItemCategorie().c_str(), chosen_cat) == 0)
            if (strcmp(lista_temp[i]->getItemData().c_str(), chosen_date) == 0)
            {
                cout << nr_sums+1 << ". " << lista_temp[i]->getItemSuma() << endl;
                nr_sums += 1;
            }
    }

    int chosen_sum = 0;
    if (cmd == true)
    {
        chosen_sum = atoi(argv[5]);
    }
    else
    {
        ok = 0;
        while (ok == 0)
        {
            cout <<"Introduceti suma : ";
            cin>> chosen_sum;
            cin.get();

            for (int i = 0; i<date.getNr(); i++)
            {
            if (strcmp(lista_temp[i]->getItemCategorie().c_str(), chosen_cat) == 0)
                if (strcmp(lista_temp[i]->getItemData().c_str(), chosen_date) == 0)
                    if (lista_temp[i]->getItemSuma() == chosen_sum)
                    ok = 1;
            }

            if (ok == 0)
            {
                switch (chosen_sum)
                {
                case 8 :
                    return 8;
                    break;
                case 9 :
                    exit(0);
                default :
                    setColor(4);
                    cout << "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                    setColor(7);
                }
            }
        }
    }

    bool sters = false;
    for (int i =0 ; i<date.getNr(); i++)
    {
        if (strcmp(lista_temp[i]->getItemCategorie().c_str(), chosen_cat) == 0)
            if (strcmp(lista_temp[i]->getItemData().c_str(), chosen_date) == 0)
                if (lista_temp[i]->getItemSuma() == chosen_sum)
                    if (!sters)
                    {
                        date.deleteItem(lista_temp[i]);
                        sters = true;
                    }
    }

    setColor(2);
    cout << " ! Stergerea a fost inregistrata cu succes ! ";
    setColor(6);
    cout <<"\n\n";
    cout << "<- BACK \"8\" \n";
    setColor(4);
    cout << "<- EXIT \"9\" \n";
    setColor(7);
    ok = 1;
    while (ok)
    {
        cout <<"Tasta : ";
        cin >> ok;
        cin.get();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                cout << "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                setColor(7);
            }
    }

}

int saveChanges()
{
    ofstream fintr, fiesr;
    fintr.open("intrari.txt");
    fiesr.open("iesiri.txt");
    fintr << lista_intrari;
    fiesr << lista_iesiri;
    fintr.close();
    fiesr.close();
    return 4;
}

int intrOption (int argc, char* argv[], bool cmd)
{
    int choice  = -1;
    while (choice)
    {
        system("cls");
        setColor(2);
        cout << "-------------------------------------OPTIUNI INTRARI---------------------------------------\n\n";
        setColor(7);
        cout << "--> Pentru a vizualiza lista de intrari, introduceti \"1\"\n";
        cout << "--> Pentru a adauga in lista de intrari o pozitie noua, introduceti \"2\"\n";
        cout << "--> Pentru a sterge din lista de intrari o pozitie, introduceti \"3\"\n";
        cout << "--> Pentru a salva schimbarile facute \"4\"\n";
        cout << "\n\n";
        setColor(6);
        cout << "<- BACK \"8\"\n";
        setColor(4);
        cout << "<- EXIT \"9\"\n";

        setColor(7);
        cout << "Tasta : ";
        do
        {
            //cin >> choice;
            //cin.get();
            if (choice == -1 && cmd == true)
                choice = atoi(argv[2]);
            else
            {
                cin >> choice;
                cin.get();
            }
            switch (choice)
            {
            case 1 :
                choice = viewItems(lista_intrari,argc, argv, cmd);
                cmd = false;
                break;
            case 2 :
                choice = addItems(lista_intrari,argc, argv, cmd);
                cmd = false;
                break;
            case 3 :
                choice = deleteItems(lista_intrari,argc, argv, cmd);
                cmd = false;
                break;
            case 4 :
                choice = saveChanges ();
                setColor(2);
                cout << "Schimbarile au fost salvate cu succes !!\n\n";
                setColor(7);
                break;
            case 8 :
                return 8;
            case 9 :
                exit(0);
            default :
                setColor(4);
                cout << "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                setColor(7);
            }
            cout << "Tasta : ";
        }
        while (choice != 8);
    }
}

int iesrOption (int argc, char* argv[], bool cmd)
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        setColor(2);
        cout <<  "-------------------------------------OPTIUNI IESIRI---------------------------------------\n\n";
        setColor(7);
        cout <<  "--> Pentru a vizualiza lista de iesiri, introduceti \"1\"\n";
        cout <<  "--> Pentru a adauga in lista de iesiri o pozitie noua, introduceti \"2\"\n";
        cout <<  "--> Pentru a sterge din lista de iesiri o pozitie, introduceti \"3\"\n";
        cout <<  "--> Pentru a salva schimbarile facute \"4\"\n";
        cout <<  "\n\n";
        setColor(6);
        cout <<  "<- BACK \"8\"\n";
        setColor(4);
        cout <<  "<- EXIT \"9\"\n";

        setColor(7);
        cout <<  "Tasta : ";

        do
        {
            //cin >> choice;
            //cin.get();
            if (choice == -1 && cmd == true)
                choice = atoi(argv[2]);
            else
            {
                cin >> choice;
                cin.get();
            }
            switch (choice)
            {
            case 1 :
                choice = viewItems(lista_iesiri,argc, argv, cmd);
                cmd = false;
                break;
            case 2 :
               choice = addItems(lista_iesiri,argc, argv, cmd);
               cmd = false;
                break;
            case 3 :
                choice = deleteItems(lista_iesiri,argc, argv, cmd);
                cmd = false;
                break;
            case 4 :
                choice = saveChanges ();
                setColor(2);
                cout <<  "Schimbarile au fost salvate cu succes !!\n\n";
                setColor(7);
                break;
            case 8 :
                return 8;
            case 9 :
                exit(0);
            default :
                setColor(4);
                cout <<  "  !! OPTIUNEA ALEASA NU EXISTA !! \n\n";
                setColor(7);
            }
            cout <<  "Tasta : ";
        }
        while (choice != 8);
    }
}

void meniu(int argc, char* argv[], bool cmd)
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        setColor(2);
        cout <<  "-------------------------------------BUN VENIT IN MENIU---------------------------------------\n\n";
        setColor(7);
        cout <<  "--> Pentru optiunile privind intrarile (veniturile) introduceti \"1\" \n";
        cout <<  "--> Pentru optiunile privind iesirile (cheltuieli) introduceti \"2\" \n";
        cout <<  "\n\n";
        setColor(4);
        cout <<  "<- EXIT \"9\"\n";
        setColor(7);
        cout <<  "Tasta : ";
        do
        {
            //cin >> choice;
            //cin.get();
            if (choice == -1 && cmd == true)
                choice = atoi(argv[1]);
            else
            {
                cin >> choice;
                cin.get();
            }
            switch (choice)
            {
            case 1 :
                choice = intrOption(argc, argv, cmd);
                cmd = false;
                break;
            case 2 :
                choice = iesrOption(argc, argv, cmd);
                cmd = false;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                cout <<  "  !! ACEASTA COMANDA NU EXISTA !! \n\n";
                setColor(7);
            }
            cout <<  "Tasta : ";
        }
        while (choice != 8);
    }
}

int main(int argc, char* argv[])
{
    citire_liste();
    if (argc == 1)
    {
        meniu(argc, argv, false);
    }
    if (argc == 6 || (argc == 5 && *(argv[2])=='1'))
        meniu(argc, argv, true);
    else
    {
        cout << "Nu ai introdus destule argumente " << endl;
        cout << "Strcutura e :" << endl;
        cout << "-meniul pentru intrari sau iesiri \"1\" sau \"2\")" << endl;
        cout << "-operatia pe care o doriti : doar \"1\" (vizualizare), \"2\"(adaugare), \"3\"(stergere) sau \"4\"(salvare) :" << endl;
        cout << " -> pentru \"1\" introduceti : categoria, data" << endl;
        cout << " -> pentru \"2\" introduceti : categoria, data, suma" << endl;
        cout << " -> pentru \"3\" introduceti : categoria, data, suma" << endl;
    }

    return 0;
}
