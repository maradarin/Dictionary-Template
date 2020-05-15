#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include <iostream>
#include "node.h"
#include "keycomp.h"
#include <queue>
#include <exception>
using namespace std;

template <class K, class V, class F = KeyComp<K> >
class dictionary {
private:
    Node<K, V>* root;
    KeyComp<K> cmp;

    int getColor(Node<K, V>*&);
    void setColor(Node<K, V>*&, int);
    void rotateLeft(Node<K, V>*&);
    void rotateRight(Node<K, V>*&);
    void fixInsertRBTree(Node<K, V>*&);
    void fixDeleteRBTree(Node<K, V>*&);
    void printLevelOrder();
    void levelOrder(Node<K, V>*);
    Node<K, V>* minValueNode(Node<K, V>*);
    Node<K, V>* insertBST(Node<K, V>*&, Node<K, V>*&);
    Node<K, V>* deleteBST(Node<K, V>*&, K);

public:
    dictionary();
    dictionary(const dictionary<K, V, F>&);

    void insertValue(K, V);
    void deleteValue(K);
    void deleteAll();

    Node<K, V>* getRoot();
    Node<K, V>* treeSearch(const K, V&) const;

    dictionary<K, V, F>& operator=(dictionary<K, V, F>&);
    V operator[](const K&) const;
    template <class Q, class W, class E>
    friend ostream& operator<<(ostream&, dictionary<Q, W, E>&);

    ~dictionary();
};

template <class K, class V, class F>
int dictionary<K, V, F>::getColor(Node<K, V>*& node)
{
    if (node == NULL)
        return BLACK;

    return node->color;
}

template <class K, class V, class F>
void dictionary<K, V, F>::setColor(Node<K, V>*& node, int color)
{
    if (node == NULL)
        return;

    node->color = color;
}

template <class K, class V, class F>
void dictionary<K, V, F>::rotateLeft(Node<K, V>*& x)    // x e nodul curent
{
    Node<K, V>* y = x->right;                           //y e fiul drept al lui x
    x->right = y->left;                                 //atasam lui x in partea dreapta subarborele stang al lui y

    if (x->right != NULL)                               //daca y avea subarbore stang
        x->right->parent = x;                           //atunci x devine parintele acelui subarbore

    y->parent = x->parent;                              //x si y vor avea acelasi parinte

    if (x->parent == NULL)                              //daca x e radacina
        root = y;                                       //y va deveni radacina
    else if (x == x->parent->left)                      //daca x e fiul stang al parintelui sau
        x->parent->left = y;                            //y o sa-i ia locul lui x
    else
        x->parent->right = y;

    y->left = x;                                        //x devine fiul stang al lui y
    x->parent = y;                                      //deci y o sa-i devina parinte lui x
}

template <class K, class V, class F>
void dictionary<K, V, F>::rotateRight(Node<K, V>*& y)   //y e nodul curent
{
    Node<K, V>* x = y->left;                            //x e fiul stang al lui y
    y->left = x->right;                                 //atasam lui y in partea stanga subarborele drept al lui x

    if (y->left != NULL)                                //daca x avea subarbore drept
        y->left->parent = y;                            //atunci y devine parintele acelui subarbore

    x->parent = y->parent;                              //x si y vor avea acelasi parinte

    if (y->parent == NULL)                              //daca y e radacina
        root = x;                                       //x va deveni radacina
    else if (y == y->parent->left)                      //daca y e fiul stang al parintelui sau
        y->parent->left = x;                            //x o sa-i ia locul lui y
    else
        y->parent->right = x;

    x->right = y;                                       //y devine fiul drept al lui x
    y->parent = x;                                      //deci x o sa-i devina parinte lui y
}

template <class K, class V, class F>
void dictionary<K, V, F>::fixInsertRBTree(Node<K, V>*& ptr)
{
    Node<K, V>* parent = NULL;                          //parinte
    Node<K, V>* grandparent = NULL;                     //"bunic" = parintele parintelui
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {              //daca parintele e fiul stang al "bunicului"
            Node<K, V>* uncle = grandparent->right;     //"unchiul" = "fratele" parintelui, fiul drept al "bunicului"
            if (getColor(uncle) == RED) {               //daca "unchiul" e ROSU
                setColor(uncle, BLACK);
                setColor(parent, BLACK);                //ambii frati sunt colorati cu NEGRU
                setColor(grandparent, RED);             //parintele lor, "bunicul" nodului curent, devine ROSU
                ptr = grandparent;                      //nodul curent devine "bunicul"
            }
            else {                                      //altfel, "unchiul" e NEGRU
                if (ptr == parent->right) {             //daca nodul curent e fiul drept
                    rotateLeft(parent);                 //rotatie la stanga
                    ptr = parent;                       //nodul curent devine parintele
                    parent = ptr->parent;               //parintele devine "bunicul"
                }
                rotateRight(grandparent);               //rotatie la dreapta
                swap(parent->color, grandparent->color);//parintele va fi NEGRU si bunicul ROSU
                ptr = parent;
            }
        }
        else {
            Node<K, V>* uncle = grandparent->left;
            if (getColor(uncle) == RED) {               //altfel, "unchiul" e fiul stang al "bunicului" si e ROSU
                setColor(uncle, BLACK);
                setColor(parent, BLACK);                //ambii frati devin NEGRI
                setColor(grandparent, RED);             //"bunicul" devine ROSU
                ptr = grandparent;                      //nodul curent devine "bunicul"
            }
            else {                                      //altfel, "unchiul" e NEGRU
                if (ptr == parent->left) {              //daca nodul curent e fiul stang
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;               //parintele devine nodul curent
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);//parintele va fi NEGRU si bunicul ROSU
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);                              //radacina e mereu NEAGRA
}

template <class K, class V, class F>
void dictionary<K, V, F>::fixDeleteRBTree(Node<K, V>*& node)
{
    if (node == NULL)
        return;

    if (node == root) {
        root = NULL;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node<K, V>* child = node->left != NULL ? node->left : node->right;
        //daca nodul curent are fiu stang, child va deveni acela, altfel este fiul drept
        if (node == node->parent->left) {               //daca nodul curent este fiul stang al parintelui
            node->parent->left = child;                 //fiul nodului curent inlocuieste fiul stang al parintelui
            if (child != NULL)                          //daca nodul curent are fii
                child->parent = node->parent;           //fiul sau devine fratele lui
            setColor(child, BLACK);                     //il coloram cu negru
            delete (node);
        }
        else {                                          //altfel, nodul curent e fiul drept
            node->parent->right = child;                //fiul nodului curent inlocuieste fiul drept al parintelui
            if (child != NULL)                          //daca nodul curent are fii
                child->parent = node->parent;           //fiul sau devine fratele lui
            setColor(child, BLACK);                     //il coloram cu negru
            delete (node);
        }
    }
    else {
        Node<K, V>* sibling = NULL;
        Node<K, V>* parent = NULL;
        Node<K, V>* ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {                  //daca nodul curent e fiul stang al parintelui
                sibling = parent->right;                //fratele va fi fiul opus (drept)
                if (getColor(sibling) == RED) {         //daca fratele e ROSU
                    setColor(sibling, BLACK);           //fratele devine NEGRU
                    setColor(parent, RED);              //parintele devine ROSU
                    rotateLeft(parent);                 //rotatie la stanga
                }
                else {                                  //altfel, fratele e NEGRU
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                                                        //daca fratele are 2 copii NEGRI
                        setColor(sibling, RED);         //fratele devine ROSU
                        if (getColor(parent) == RED)    //daca parintele e ROSU
                            setColor(parent, BLACK);    //devine NEGRU
                        else                            //altfel, parintele e NEGRU
                            setColor(parent, DOUBLE_BLACK); //parintele devine DOUBLE_BLACK
                        ptr = parent;
                    }
                    else {                              //altfel, daca nu ambii copii sunt NEGRI
                        if (getColor(sibling->right) == BLACK) {
                                                        //daca fratele are fiu drept NEGRU
                            setColor(sibling->left, BLACK); //si fiul stang devine NEGRU
                            setColor(sibling, RED);     //parintele lor (fratele nodului curent) devine ROSU
                            rotateRight(sibling);
                            sibling = parent->right;    //fratele e fiul drept (nodul curent e in stanga)
                        }
                        setColor(sibling, parent->color); //fratele are aceeasi culoare ca si parintele
                        setColor(parent, BLACK);        //parintele e NEGRU
                        setColor(sibling->right, BLACK);//fiul drept al fratelui e NEGRU
                        rotateLeft(parent);
                        break;
                    }
                }
            }
            else {                                      //altfel, nodul curent e fiul drept
                sibling = parent->left;                 //fratele e fiul opus (din stanga)
                if (getColor(sibling) == RED) {         //daca fratele e ROSU
                    setColor(sibling, BLACK);           //devine NEGRU
                    setColor(parent, RED);              //parintele devine ROSU
                    rotateRight(parent);
                }
                else {                                  //altfel, fratele e NEGRU
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                                                        //daca fratele are 2 fii NEGRI
                        setColor(sibling, RED);         //fratele devine ROSU
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);    //daca parintele e ROSU, devine NEGRU
                        else
                            setColor(parent, DOUBLE_BLACK); //altfel, e DOUBLE_BLACK
                        ptr = parent;
                    }
                    else {                              //daca fratele nu are 2 fii NEGRI
                        if (getColor(sibling->left) == BLACK) { //daca fiul stang e NEGRU
                            setColor(sibling->right, BLACK); //atunci cel drept devine NEGRU
                            setColor(sibling, RED);     //parintele lor (fratele) devine ROSU
                            rotateLeft(sibling);
                            sibling = parent->left;     //fratele e fiul stang
                        }
                        setColor(sibling, parent->color); //fratele ia culoarea parintelui
                        setColor(parent, BLACK);          //parintele devine NEGRU
                        setColor(sibling->left, BLACK);   //fiul stang devine NEGRU
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        //verificare daca nodul curent e pe partea stanga/dreapta, se anuleaza ca sa se stearga
        if (node == node->parent->left)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
        delete (node);
        setColor(root, BLACK); //radacina e mereu NEAGRA
    }
}

template <class K, class V, class F>
void dictionary<K, V, F>::printLevelOrder()
{
    cout << "Level order: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        levelOrder(root);
    cout << endl;
}

template <class K, class V, class F>
void dictionary<K, V, F>::levelOrder(Node<K, V>* x)
{
    if (x == NULL)
        return;

    queue<Node<K, V>*> q;
    Node<K, V>* curr;

    q.push(x);

    while (!q.empty()) {
        curr = q.front();
        q.pop();

        cout << endl
             << "Cheie: " << curr->key << "-> Valoare: " << curr->value << " <" << curr->color << ">";

        if (curr->left != NULL)
            q.push(curr->left);
        if (curr->right != NULL)
            q.push(curr->right);
    }
}

template <class K, class V, class F>
Node<K, V>* dictionary<K, V, F>::minValueNode(Node<K, V>* node)
{

    Node<K, V>* ptr = node;

    while (ptr->left != NULL)
        ptr = ptr->left;

    return ptr;
}

template <class K, class V, class F>
Node<K, V>* dictionary<K, V, F>::insertBST(Node<K, V>*& root, Node<K, V>*& ptr)
{
    if (root == NULL)                                       //daca arborele e gol
        return ptr;

    if (cmp(ptr->key, root->key)) {                         //daca ptr->key < root->key
        root->left = insertBST(root->left, ptr);            //inseram pe partea stanga (prop bst)
        root->left->parent = root;                          //actualizarea radacinii pe masura ce avansam
    }
    else if (cmp(root->key, ptr->key)) {                    //daca root->key < ptr->key
        root->right = insertBST(root->right, ptr);          //inseram pe partea dreapta (prop bst)
        root->right->parent = root;                         //actualizarea radacinii pe masura ce avansam
    }
    else
        root->value = ptr->value;                           //daca exista deja cheia de inserat, doar actualizam valoarea

    return root;
}

template <class K, class V, class F>
Node<K, V>* dictionary<K, V, F>::deleteBST(Node<K, V>*& root, K newKey)
{
    if (root == NULL)                                       //daca arborele e gol
        return root;

    if (cmp(newKey, root->key))                             //daca newKey < root->key
        return deleteBST(root->left, newKey);               //avansam pe partea stanga (prop bst)

    if (cmp(root->key, newKey))                             //daca root->key < newKey
        return deleteBST(root->right, newKey);              //avansam pe partea dreapta (prop bst)

    if (root->left == NULL || root->right == NULL)          //un nod cu 1 sau 0 fii
        return root;

    //altfel, nu iese prin return deci are 2 fii
    Node<K, V>* temp = minValueNode(root->right);           //se preia minimul din arbore (aflat pe dreapta)
    root->key = temp->key;
    return deleteBST(root->right, temp->key);
}

// METODELE DE LA PUBLIC

template <class K, class V, class F>
dictionary<K, V, F>::dictionary()                           //constructor fara parametri
    : root(NULL)
{
}

template <class K, class V, class F>
dictionary<K, V, F>::dictionary(const dictionary& d)        //constructor de copiere
{
    root = d.root;
}

template <class K, class V, class F>
void dictionary<K, V, F>::insertValue(K key, V val)
{
    Node<K, V>* node = new Node<K, V>(key, val);            //se creeaza nodul de inserat
    root = insertBST(root, node);                           //se apeleaza functia simpla de inserare intr-un arbore de cautare
                                                            //deoarece, la baza, un rbt este un bst
    fixInsertRBTree(node);                                  //se apeleaza functia care regleaza proprietatile de rbt
}

template <class K, class V, class F>
void dictionary<K, V, F>::deleteValue(K newKey)
{
    Node<K, V>* node = deleteBST(root, newKey);             //se apeleaza functia simpla de stergere din bst
    fixDeleteRBTree(node);                                  //se apeleaza functia care regleaza proprietatile de rbt
}

template <class K, class V, class F>
void dictionary<K, V, F>::deleteAll()
{
    while (root != NULL)                                    //apelare functie de stergere pt a elimina nodurile unul cate unul
        deleteValue(root->key);
}

template <class K, class V, class F>
Node<K, V>* dictionary<K, V, F>::getRoot()                  //getter pt radacina arborelui
{
    return root;
}

template <class K, class V, class F>
Node<K, V>* dictionary<K, V, F>::treeSearch(const K newKey, V& newVal) const
{
    Node<K, V>* temp = root;
    if (temp == NULL)                                       //daca arborele este gol sau s-a parcurs integral
        return NULL;                                        //nodul nu exista/nu a fost gasit
    while (temp) {
        if (!cmp(temp->key, newKey) && !cmp(newKey, temp->key))
        //utilizarea obiectului cmp pt a apela functia de comparare
        //NOT(temp->key>newKey) si NOT(newKey>temp->key) <=> temp->key=newkey
        {                                                   //deci nodul a fost gasit
            newVal = temp->value;                           //retinem valoarea in parametru (folosita pt assert)
            return temp;                                    //returnam nodul cu informatia corect gasita
        }
        else if (cmp(newKey, temp->key)) //daca newKey>temp->key, cautam in subarborele stang (prop bst)
            temp = temp->left;
        else if (cmp(temp->key, newKey)) //daca temp->key>newKey, cautam in subarborele drept (prop bst)
            temp = temp->right;
    }
    return NULL;
}

template <class K, class V, class F>
dictionary<K, V, F>& dictionary<K, V, F>::operator=(dictionary<K, V, F>& d)
{
    if (this != &d)                                         //daca obiectul curent e diferit de cel atribuit
        root = d.root;
    return *this;
}

template <class K, class V, class F>
V dictionary<K, V, F>::operator[](const K& i) const
{
    int val = 0;
    if (treeSearch(i, val) == NULL)                         //daca nu exista nodul cu cheia i
        return NULL;
    return val;                                             //altfel se returneaza valoarea
}

template <class K, class V, class F>
ostream& operator<<(ostream& out, dictionary<K, V, F>& d)
{
    d.printLevelOrder();                                    //afisarea se realizeaza pe nivele
    return out;
}

template <class K, class V, class F>
dictionary<K, V, F>::~dictionary()
{
    delete (root);                                          //distrugerea radacinii implica distrugerea intregului arbore
    cout << "destroyed" << endl;
}

#endif // _DICTIONARY_H_
