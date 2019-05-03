//Ned Hazlewood
#include "header.h"

node::node():next(NULL){}
//appends passed node to the end of the list the calling node is in
void node::add_tail(node *& newTail){
    node * current = this;
    node * previous = this;

    while(current){
        previous = current;
        current = current->next;
    }

    previous->next = newTail;
    newTail->prev = previous;
    current= NULL;
    previous = NULL;
}
//finds the tail of the calling node and sets the passed pointer to the tail
void node::find_tail(node *& tail){
    node * current = this;
    tail = this;
    while(current){
        tail = current;
        current= current->next;
    }
}

//node has two data members but we only care about 1 at a time
//set() with clear the value of wrong data type, if symbol is set to
// \0 it means that the value number is valid
void node::set(char newSymbol){
    this->symbol = newSymbol;
    this->value = 0;
}
void node::set(int newValue){
    this->value = newValue;
    this->symbol = '\0';
}

//Creates a new node and adjusts pointers, one version for operators and one for integers
void node::insert(char symbol){
    node * next = this->next;
    node * temp = new node;
    temp->set(symbol);
    this->next = temp;
    temp->next = next;
    temp->prev = this;
    next->prev = temp;
    this->prev = temp;
    temp = NULL;
}
void node::insert(int value){
    node * next = this->next;
    node * temp = new node;
    temp->set(value);
    this->next = temp;
    temp->next = next;
    temp->prev = this;
    next->prev = temp;
    this->prev = temp;
    temp = NULL;
}
