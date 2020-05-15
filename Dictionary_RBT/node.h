#ifndef _NODE_H_
#define _NODE_H_
#include <iostream>
#include <string>
#include "keycomp.h"
using namespace std;

template <typename K, typename V, typename KeyComp>
class dictionary;
enum Color { RED,
    BLACK,
    DOUBLE_BLACK };
//DOUBLE_BLACK: folosit pt stergere
//cand e sters un nod negru si inlocuit de un copil negru, acesta e considerat DOUBLE_BLACK

template <class K, class V>
class Node {
    K key;
    V value;
    int color;
    Node *left, *right, *parent;

public:
    Node(K, V);
    Node(const Node<K, V>&);
    K getKey();
    Node<K, V>* getLeft();
    Node<K, V>* getRight();
    friend class dictionary<K, V, KeyComp<K> >;
};

template <class K, class V>
Node<K, V>::Node(K newKey, V newVal)
    : key(newKey)
    , value(newVal)
    , color(RED)
    , left(NULL)
    , right(NULL)
    , parent(NULL)
{
}

template <class K, class V>
Node<K, V>::Node(const Node<K, V>& n)
    : key(n.key)
    , value(n.value)
    , color(n.color)
    , left(n.left)
    , right(n.right)
    , parent(n.parent)
{
}

template <class K, class V>
Node<K, V>* Node<K, V>::getLeft()
{
    return left;
}

template <class K, class V>
Node<K, V>* Node<K, V>::getRight()
{
    return right;
}

template <class K, class V>
K Node<K, V>::getKey()
{
    return key;
}

#endif // _NODE_H_
