#include <iostream>
#include "dictionary.h"
using namespace std;

int main() {
    int data,i=1;
    dictionary<int,int,KeyComp<int> > rbTree1;

    cin >> data;
    while (data != 0)
    {
        rbTree1.insertValue(data,i);
        i++;
        cin >> data;
    }

    rbTree1.preorder();
cout<<endl;
cout<<rbTree1;
    cout<<endl<<endl;
    rbTree1.deleteValue(18);
    rbTree1.deleteValue(10);
    rbTree1.deleteValue(11);
    rbTree1.deleteValue(22);
    rbTree1.deleteValue(3);
    //cout<<rbTree1.getRoot()->data;//<<" "<<rbTree1.getRoot()->left->data<<" "<<rbTree1.getRoot()->right->data<<" "<<rbTree1.getRoot()->left->left->data<<" "<<rbTree1.getRoot()->right->left->data<<endl;
rbTree1.preorder();
cout<<endl;
cout<<rbTree1;

    /*string data1;
    i=1;
    dictionary<string,int,KeyComp<string> > rbTree2;

    cin >> data1;
    while (data1 != "m")
    {
        rbTree2.insertValue(data1,i);
        i++;
        cin >> data1;
    }

    rbTree2.preorder();

    cout<<endl<<endl;*/
    /*rbTree2.deleteValue(18);
    rbTree2.deleteValue(10);
    rbTree2.deleteValue(11);
    rbTree2.deleteValue(22);
    rbTree2.deleteValue(3);*/
    //cout<<rbTree2.getRoot()->getKey();//<<" "<<rbTree1.getRoot()->left->data<<" "<<rbTree1.getRoot()->right->data<<" "<<rbTree1.getRoot()->left->left->data<<" "<<rbTree1.getRoot()->right->left->data<<endl;
    //rbTree1.preorder();

    return 0;
}
