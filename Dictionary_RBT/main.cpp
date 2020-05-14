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
cout<<endl<<rbTree1[22]<<" "<<rbTree1[26]<<" "<<rbTree1[13]<<endl;
    cout<<endl<<endl;
    rbTree1.deleteValue(18);
    rbTree1.deleteValue(10);
    rbTree1.deleteValue(11);
    rbTree1.deleteValue(22);
    rbTree1.deleteValue(3);
    //cout<<rbTree1.getRoot()->data;//<<" "<<rbTree1.getRoot()->left->data<<" "<<rbTree1.getRoot()->right->data<<" "<<rbTree1.getRoot()->left->left->data<<" "<<rbTree1.getRoot()->right->left->data<<endl;
rbTree1.preorder();
cout<<endl;
cout<<rbTree1<<endl<<rbTree1.getRoot()->getKey();


//rbTree1.deleteAll();
//cout<<endl<<rbTree1;
    string data1;
    i=1;
    dictionary<string,int,KeyComp<string> > rbTree2;

    cin >> data1;
    while (data1 != "m")
    {
        rbTree2.insertValue(data1,i);
        i++;
        cin >> data1;
    }

    cout<<rbTree2;

    cout<<endl<<endl;
    /*rbTree2.deleteValue(18);
    rbTree2.deleteValue(10);
    rbTree2.deleteValue(11);
    rbTree2.deleteValue(22);
    rbTree2.deleteValue(3);*/
    //cout<<rbTree2.getRoot()->getKey();//<<" "<<rbTree1.getRoot()->left->data<<" "<<rbTree1.getRoot()->right->data<<" "<<rbTree1.getRoot()->left->left->data<<" "<<rbTree1.getRoot()->right->left->data<<endl;
    //rbTree1.preorder();

    dictionary<int,int> rbTree3(rbTree1);
    cout<<rbTree3<<endl<<rbTree3.getRoot()->getKey();

    dictionary<string,int> rbTree4;
    rbTree4=rbTree2;
    cout<<endl<<rbTree4<<endl<<rbTree4.getRoot()->getKey();
    return 0;
}
