#ifndef _NODE_H_
#define _NODE_H_
#include <iostream>
#include <string>
#include "keycomp.h"
using namespace std;

template <typename K, typename V, typename KeyComp> class dictionary;
enum Color {RED, BLACK, DOUBLE_BLACK};

template <class K, class V>
class Node
{
    K key;
    V value;
    int color;
    Node *left, *right, *parent;

public:
    Node(K, V);
    friend class dictionary<K, V, KeyComp<K> >;
    K getKey();
    //~Node();
};


template <class K, class V>
Node<K, V>::Node(K newKey, V newVal) {
    this->key = newKey;
    this->value = newVal;
    color = RED;
    left = right = parent = NULL;
}

template <class K, class V>
K Node<K,V>::getKey()
{
    return key;
}

/*template <class K, class V>
Node<K,V>::~Node()
{
    delete left;
    delete right;
    delete parent;
}*/
#endif // _NODE_H_

