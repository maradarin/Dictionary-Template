#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include <iostream>
#include "node.h"
#include "keycomp.h"
#include <queue>
#include <exception>
using namespace std;


template <class K, class V, class F = KeyComp<K> >
class dictionary
{
    private:
        Node<K,V> *root;
        KeyComp<K> cmp;

        void rotateLeft(Node<K,V> *&);
        void rotateRight(Node<K,V> *&);
        void fixInsertRBTree(Node<K,V> *&);
        void fixDeleteRBTree(Node<K,V> *&);
        void inorderBST(Node<K,V> *&);
        void preorderBST(Node<K,V> *&);
        int getColor(Node<K,V> *&);
        void setColor(Node<K,V> *&, int);
        Node<K,V> *minValueNode(Node<K,V> *&);
        Node<K,V> *maxValueNode(Node<K,V> *&);
        Node<K,V>* insertBST(Node<K,V> *&, Node<K,V> *&);
        Node<K,V>* deleteBST(Node<K,V> *&, K);
        int getBlackHeight(Node<K,V> *);
        void printLevelOrder();
        void levelOrder(Node<K,V>*);
        void copy(Node<K,V>*);

    public:
        dictionary();
        dictionary(const dictionary&);
        void insertValue(K, V);
        void deleteValue(K);
        void deleteAll();
        Node<K,V>* treeSearch(const K);
        dictionary<K, V, F>& operator=(dictionary<K, V, F>&);
        V operator[](const K);
        void inorder();
        void preorder();
        Node<K,V>* getRoot() {return root;}
        template <class Q, class W, class E>
        friend ostream& operator<<(ostream&, dictionary<Q, W, E>&);
        ~dictionary();
};

template <class K, class V, class F>
dictionary<K,V,F>::dictionary() {
    root = NULL;
}

template <class K, class V, class F>
dictionary<K,V,F>::dictionary(const dictionary& d)
{
    root=d.root;
}

template <class K, class V, class F>
dictionary<K,V,F>& dictionary<K,V,F>::operator=(dictionary<K,V,F>& d)
{
    root=d.root;
}

template <class K, class V, class F>
void dictionary<K,V,F>::copy(Node<K,V> * N)
{
     if(N)
     {
         insertValue(N->key,N->value);
         copy(N->left);
         copy(N->right);
     }
}

template <class K, class V, class F>
int dictionary<K,V,F>::getColor(Node<K,V> *&node) {
    if (node == NULL)
        return BLACK;

    return node->color;
}

template <class K, class V, class F>
void dictionary<K,V,F>::setColor(Node<K,V> *&node, int color) {
    if (node == NULL)
        return;

    node->color = color;
}

template <class K, class V, class F>
Node<K,V>* dictionary<K,V,F>::insertBST(Node<K,V> *&root, Node<K,V> *&ptr) {
    if (root == NULL)
        return ptr;

    if (cmp(ptr->key, root->key)) {  //ptr->key < root->key
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (cmp(root->key, ptr->key)) {  //root->key < ptr->key
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
    else root->value=ptr->value;

    return root;
}

template <class K, class V, class F>
void dictionary<K,V,F>::insertValue(K key, V val) {
    Node<K,V> *node = new Node<K,V>(key, val);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

template <class K, class V, class F>
void dictionary<K,V,F>::rotateLeft(Node<K,V> *&ptr) {
    Node<K,V> *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != NULL)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

template <class K, class V, class F>
void dictionary<K,V,F>::rotateRight(Node<K,V> *&ptr) {
    Node<K,V> *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != NULL)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == NULL)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

template <class K, class V, class F>
void dictionary<K,V,F>::fixInsertRBTree(Node<K,V> *&ptr) {
    Node<K,V> *parent = NULL;
    Node<K,V> *grandparent = NULL;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node<K,V> *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node<K,V> *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

template <class K, class V, class F>
void dictionary<K,V,F>::fixDeleteRBTree(Node<K,V> *&node) {
    if (node == NULL)
        return;

    if (node == root) {
        root = NULL;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node<K,V> *child = node->left != NULL ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != NULL)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != NULL)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node<K,V> *sibling = NULL;
        Node<K,V> *parent = NULL;
        Node<K,V> *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
        delete(node);
        setColor(root, BLACK);
    }
}

template <class K, class V, class F>
Node<K,V>* dictionary<K,V,F>::deleteBST(Node<K,V> *&root, K newKey) {
    if (root == NULL)
        return root;

    if (newKey < root->key)
        return deleteBST(root->left, newKey);

    if (newKey > root->key)
        return deleteBST(root->right, newKey);

    if (root->left == NULL || root->right == NULL)
        return root;

    Node<K,V> *temp = minValueNode(root->right);
    root->key = temp->key;
    return deleteBST(root->right, temp->key);
}

template <class K, class V, class F>
void dictionary<K,V,F>::deleteValue(K newKey) {
    Node<K,V> *node = deleteBST(root, newKey);
    fixDeleteRBTree(node);
}

template <class K, class V, class F>
void dictionary<K,V,F>::deleteAll()
{
    while(root!=NULL)
        deleteValue(root->key);
}

template <class K, class V, class F>
Node<K, V>* dictionary<K, V, F>::treeSearch(const K newKey)
{
    Node<K, V>* temp = root;
    if (temp == NULL)
        return NULL;

    while (temp) {
        if (!cmp(temp->key, newKey) && !cmp(newKey, temp->key))
            return temp;
        else if (cmp(newKey, temp->key))
            temp = temp->left;
        else
            temp = temp->right;
    }
    return NULL;
}

template <class K, class V, class F>
V dictionary<K, V, F>::operator[](const K i) ///supraincarcarea operatorului []
{
    if(treeSearch(i)==NULL)
        return NULL;
    return treeSearch(i)->value;
}

template <class K, class V, class F>
void dictionary<K,V,F>::inorderBST(Node<K,V> *&ptr) {
    if (ptr == NULL)
        return;

    inorderBST(ptr->left);
    cout << endl << "Cheie: " << ptr->key << "-> Valoare: " << ptr->value << " <" << ptr->color << ">";
    inorderBST(ptr->right);
}

template <class K, class V, class F>
void dictionary<K,V,F>::inorder() {
    inorderBST(root);
}

template <class K, class V, class F>
void dictionary<K,V,F>::preorderBST(Node<K,V> *&ptr) {
    if (ptr == NULL)
        return;
    preorderBST(ptr->left);
    cout << endl << "Cheie: " << ptr->key << "-> Valoare: " << ptr->value << " <" << ptr->color << ">";

    preorderBST(ptr->right);
}

template <class K, class V, class F>
void dictionary<K,V,F>::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

template <class K, class V, class F>
Node<K,V> *dictionary<K,V,F>::minValueNode(Node<K,V> *&node) {

    Node<K,V> *ptr = node;

    while (ptr->left != NULL)
        ptr = ptr->left;

    return ptr;
}

template <class K, class V, class F>
Node<K,V>* dictionary<K,V,F>::maxValueNode(Node<K,V> *&node) {
    Node<K,V> *ptr = node;

    while (ptr->right != NULL)
        ptr = ptr->right;

    return ptr;
}

template <class K, class V, class F>
int dictionary<K,V,F>::getBlackHeight(Node<K,V> *node) {
    int blackheight = 0;
    while (node != NULL) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

template <class K, class V, class F>
void dictionary<K,V,F>::levelOrder(Node<K,V> *x) {
    if (x == NULL)
      return;

    queue<Node<K,V> *> q;
    Node<K,V> *curr;

    q.push(x);

    while (!q.empty()) {
      curr = q.front();
      q.pop();

    cout << endl << "Cheie: " << curr->key << "-> Valoare: " << curr->value << " <" << curr->color << ">";

      if (curr->left != NULL)
        q.push(curr->left);
      if (curr->right != NULL)
        q.push(curr->right);
    }
  }

template <class K, class V, class F>
  void dictionary<K,V,F>::printLevelOrder() {
    cout << "Level order: " << endl;
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      levelOrder(root);
    cout << endl;
  }

template <class K, class V, class F>
ostream& operator<<(ostream& out, dictionary<K, V, F>& d)
{
    d.printLevelOrder();
    return out;
}

template <class K, class V, class F>
dictionary<K,V,F>::~dictionary()
{
    delete root;
    cout<<"destroyed"<<endl;
}

#endif // _DICTIONARY_H_
