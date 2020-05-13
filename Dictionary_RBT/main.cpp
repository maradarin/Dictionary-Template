#include <iostream>
#include "dictionary.h"
using namespace std;

int main() {
    int data,i=1;
    dictionary<int,int> rbTree1;

    cin >> data;
    while (data != 0)
    {
        rbTree1.insertValue(data,i);
        i++;
        cin >> data;
    }

    rbTree1.preorder();

    cout<<endl<<endl;
    rbTree1.deleteValue(18);
    rbTree1.deleteValue(10);
    rbTree1.deleteValue(11);
    rbTree1.deleteValue(22);
    rbTree1.deleteValue(3);
    //cout<<rbTree1.getRoot()->data;//<<" "<<rbTree1.getRoot()->left->data<<" "<<rbTree1.getRoot()->right->data<<" "<<rbTree1.getRoot()->left->left->data<<" "<<rbTree1.getRoot()->right->left->data<<endl;
rbTree1.preorder();
    /*cin >> data;
    while (data != 0)
    {
        rbTree2.insertValue(data);
        cin >> data;
    }

    rbTree2.preorder();

    rbTree1.merge(rbTree2);
    rbTree1.preorder();*/

    return 0;
}
