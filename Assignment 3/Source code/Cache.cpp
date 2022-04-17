#include "Cache.h"
Cache::Cache(SearchEngine* s,ReplacementPolicy* r):rp(r),s_engine(s) {}
Cache::~Cache(){
	delete rp;
	delete s_engine;
}
Data* Cache::read(int addr) {
    Elem *temp = s_engine->search(addr);
    if(temp != NULL){
        rp->access(addr);
        return temp->data;
    }
    return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
    Elem *temp = new Elem(addr, cont, true);
    Elem *remove = NULL;
    if(rp->getSize() == MAXSIZE){
        remove = rp->top();
        rp->remove();
        s_engine->removeNode(remove->addr);
    }
    rp->insert(temp);
    s_engine->addNode(temp);
    return remove;
}
Elem* Cache::write(int addr, Data* cont) {
    Elem *remove = NULL;
    Elem *temp = s_engine->search(addr);
    if(temp != NULL){
        rp->access(temp->addr);
        delete temp->data;
        temp->data = cont;
        temp->sync = false;
    }
    else{
        if(rp->getSize() == MAXSIZE){
            remove = rp->top();
            rp->remove();
            s_engine->removeNode(remove->addr);
        }
        Elem *temp1 = new Elem(addr, cont, false);
        rp->insert(temp1);
        s_engine->addNode(temp1);
    }
    return remove;
}
void Cache::printRP() {
    //cout << "Print replacement\n";
    rp->print();
}
void Cache::printSE() {
    //cout << "Print search buffer\n";
    s_engine->print();
}
