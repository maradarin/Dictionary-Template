#include <iostream>
#include <cassert>
#include "dictionary.h"
using namespace std;

void testare()
{
    dictionary<int, int, KeyComp<int> > D;

    D.insertValue(1, 143);

    int valoare;
    D.treeSearch(1, valoare);
    assert(valoare == 143);         //cautare dupa cheie

    D.insertValue(44, 213);
    D.insertValue(87, 412);
    D.insertValue(6, 5);
    D.insertValue(1,100);           //inlocuirea unei valori

    assert(D[1] != 213);            //verificarea valorii inlocuite
    assert(D[1] == 100);

    D.deleteAll();
    assert(D.getRoot() == NULL);
    D.insertValue(5, 7);
    D.deleteValue(5);               //stergere dupa cheie
    assert(D[5] == NULL);           //verificare stergere

    D.deleteAll();                  //stergerea completa a dictionarului
    assert(D.getRoot()==NULL);      //verificare ca arborele e gol
    D.insertValue(23, 24);
    dictionary<int, int> D2;
    D2 = D;                         //atribuire
    D.deleteValue(23);
    assert(D[23] == NULL);
    assert(D2[23] == 24);           //D e gol, D2 ramane nemodificat

    dictionary<string, int, KeyComp<string> > d4; //cu comparatorul specializat pe string
    d4.insertValue("alfa", 1);
    d4.insertValue("beta", 2);
    d4.insertValue("gama", 3);
    d4.insertValue("delta", 4);
    d4.insertValue("omega", 5);
    d4.insertValue("theta", 6);
    d4.insertValue("tau", 7);
    d4.insertValue("niu", 8);

    cout << d4 << endl; //operatorul << supraincarcat

    //verificari de ordine, ref la inserare
    assert(d4.getRoot()->getKey() == "gama");
    assert(d4.getRoot()->getLeft()->getKey() == "tau");
    assert(d4.getRoot()->getRight()->getKey() == "beta");
    assert(d4.getRoot()->getLeft()->getLeft()->getKey() == "theta");
    assert(d4.getRoot()->getRight()->getLeft()->getKey() == "delta");

    D.insertValue(8, 1);
    D.insertValue(18, 2);
    D.insertValue(5, 3);
    D.insertValue(15, 4);

    D.insertValue(17, 5);
    D.insertValue(25, 6);
    D.insertValue(40, 7);
    D.insertValue(80, 8);

    dictionary<int, int> D1(D);                 //constr de copiere
    assert(D1[23] == D[23]);                    //23 nu exista nici in D, nici in D1
    assert(D2[17] == NULL);                     //17 nu exista in D2, ci in D si D1
    D.deleteValue(17);
    assert(D[17] == NULL);
    assert(D1[17] == 5);                        //17 a fost sters doar din D, nu si din D1
}

int main()
{
    testare();
    cout<< endl << "Merge";
    return 0;
}
