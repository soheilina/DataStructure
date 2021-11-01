#include "hashset.h"

HashSet::HashSet()
    : capacity(10)
    , mySize(0)
{
    elements = new HashNode* [10]();
}

HashSet::~HashSet(){
    delete [] elements;
}

void HashSet :: add( int value){
    if( !contains(value) ){
        HashNode* ptrNode = new HashNode(value);
        // gets the index in the array
        int bucket = hashCode(value);
        // inserts at the front
        ptrNode->next = elements[bucket];
        elements[bucket] = ptrNode;
        //updates size
        mySize++;
    }
}

void HashSet :: clear(){
    delete [] elements;
}

void HashSet :: remove(int value){
    int bucket = hashCode(value);
    if(elements[bucket]->data == value){
        // remove first node
        elements[bucket] = elements[bucket]->next;
        mySize--;
        return;
    }
    else{
        // remove non-first node
        HashNode* currentNode = elements[bucket];
        while(currentNode->next != nullptr){
            if( currentNode->next->data == value){
                // remove the next node
                HashNode* trash = currentNode->next; // found it! make a copy of it in order to free the memory later
                currentNode->next = currentNode->next->next;
                mySize--;
                delete trash; // frees memory
                return;
            }
            currentNode = currentNode->next;
        }
    }
    return;
}

bool HashSet :: contains(int value) const {
    int bucket = hashCode(value);
    HashNode* currentNode = elements[bucket];
    while(currentNode != nullptr){
        if(currentNode->data == value){
            // Node found
            return true;
        }
        else{
            // moves to the next node
            currentNode = currentNode->next;
        }
    }
    return false;
}

void HashSet :: printStructure() const {
    for(int i = 0; i < capacity; i++){
        cout << "[" << setw(2) << i << "]:";
        HashNode* current = elements[i];
        while( current != nullptr ){
            cout << " -> " << setw(2) << current->data;
            current = current->next;
        }
        cout << " /" << endl;
    }
    cout << "size = " << mySize << endl;
}

int HashSet :: hashCode(int value) const{
    return value % capacity; // TODO: abs() causes an error
}
