#ifndef HASHSET_H
#define HASHSET_H

/*
 * brief: This implementation is based on "CS 106B Lecture: Hashing" by Marty Stepp
 */

using namespace std;

//========================== Structs ==========================
struct HashNode{
    int data;
    HashNode* next;

    HashNode(int data=0, HashNode* next=nullptr){
        this->data = data;
        this->next = next;
    }
};
//========================== Class ============================
class HashSet
{
public:
    explicit HashSet();
    ~HashSet();

public:
    /// adds a new value to HashSet
    void add( int value);
    /// deletes all value in the HashSet
    void clear();
    /// returns true if the given value is contained
    bool contains(int value) const;
    /// prints all values of the HashSet
    void printStructure() const;
    /// removes given value from the HashSet
    void remove( int value);

    HashNode* trash;

private:
    HashNode** elements;
    int capacity;
    int mySize;

private:
    /// returns the hash code of given value
    int hashCode(int value) const;
};

#endif // HASHSET_H
