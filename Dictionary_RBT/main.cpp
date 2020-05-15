#include <iostream>
#include <cassert>
#include "dictionary.h"
using namespace std;

void testare()
{
    dictionary<int, int, KeyComp<int> > D;

    D.insertValue(1, 143);
    cout << D; //operatorul << supraincarcat

    int valoare;
    D.treeSearch(1, valoare);
    assert(valoare == 143); //cautare dupa cheie

    D.insertValue(44, 213);
    D.insertValue(87, 412);
    D.insertValue(6, 5);

    cout << D; //operatorul << supraincarcat

    assert(D[44] == 213);
    D.deleteAll();
    D.insertValue(5, 7);
    cout << D;
    D.deleteValue(5); //stergere dupa cheie
    assert(D[5] == NULL);

    D.deleteAll(); //stergerea completa a dictionarului

    D.insertValue(23, 24);
    dictionary<int, int> D2;
    D2 = D;

    dictionary<string, int, KeyComp<string> > d4;
    d4.insertValue("alfa", 1);
    d4.insertValue("beta", 2);
    d4.insertValue("gama", 3);
    d4.insertValue("delta", 4);
    d4.insertValue("omega", 5);
    d4.insertValue("theta", 6);
    d4.insertValue("tau", 7);
    d4.insertValue("niu", 8);
    assert(d4.getRoot()->getKey() == "gama");
    assert(d4.getRoot()->getLeft()->getKey() == "tau");
    assert(d4.getRoot()->getRight()->getKey() == "beta");
    assert(d4.getRoot()->getLeft()->getLeft()->getKey() == "theta");
    assert(d4.getRoot()->getRight()->getLeft()->getKey() == "delta");

    cout << endl
         << d4;
    D.insertValue(8, 1);
    D.insertValue(18, 2);
    D.insertValue(5, 3);
    D.insertValue(15, 4);

    cout << D2;
    D.insertValue(17, 5);
    D.insertValue(25, 6);
    D.insertValue(40, 7);
    D.insertValue(80, 8);

    cout << endl
         << D;

    dictionary<int, int> D1(D);

    cout << endl
         << D1;

    assert(D2[23] == D1[23]);
    assert(D2[23] == D[23]);
    assert(D1[23] == D[23]);

    assert(D.getRoot()->getKey() == 18);
    assert(D.getRoot()->getLeft()->getKey() == 8);
    assert(D.getRoot()->getRight()->getKey() == 25);
    assert(D.getRoot()->getLeft()->getLeft()->getKey() == 5);
    assert(D.getRoot()->getRight()->getLeft()->getKey() == 23);
}

int main()
{
    testare();
    return 0;
}
