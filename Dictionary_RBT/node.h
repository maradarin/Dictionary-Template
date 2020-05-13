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
};


template <class K, class V>
Node<K, V>::Node(K newKey=0, V newVal=0) {
    this->key = newKey;
    this->value = newVal;
    color = RED;
    left = right = parent = NULL;
}

#endif // _NODE_H_

