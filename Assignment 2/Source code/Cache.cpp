#include "Cache.h"

Data* Cache::read(int addr) {
    Elem *temp = AVLTree.contain(addr);
    if(temp) return temp->data;
    return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
    Elem *temp = new Elem(addr, cont, true);
    Elem *remove = NULL;
    if(int(recentUse.size()) == MAXSIZE)
    {
        remove = recentUse.front();
        AVLTree.removeNode(remove->addr);
        recentUse.pop();
    }
    recentUse.push(temp);
    AVLTree.addNode(temp);
    return remove;
}
Elem* Cache::write(int addr, Data* cont) {
    Elem *remove = NULL;
    Elem *temp = AVLTree.contain(addr);
    if(temp != NULL) 
    {
        delete temp->data;
        temp->data = cont;
        temp->sync = false;
    }
    else
    {
        if(int(recentUse.size()) == MAXSIZE)
        {
            remove = recentUse.front();
            AVLTree.removeNode(remove->addr);
            recentUse.pop();
        }
        Elem *temp1 = new Elem(addr, cont, false);
        recentUse.push(temp1);
        AVLTree.addNode(temp1);
    }
    return remove;
}
void Cache::print() {
    queue<Elem *> temp;
    while(!recentUse.empty())
    {
        recentUse.front()->print();
        temp.push(recentUse.front());
        recentUse.pop();
    }
    while(!temp.empty())
    {
        recentUse.push(temp.front());
        temp.pop();
    }
}
void Cache::preOrder() {
    AVLTree.preorder();
}
void Cache::inOrder() {
    AVLTree.inorder();
}
