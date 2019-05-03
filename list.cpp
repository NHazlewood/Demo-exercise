//Ned Hazlewood
#include "header.h"

list::list(){
    head = NULL;
    length = 0;
    tail = 0;
}
list::~list(){
    if (head) delete [] head;
    head = NULL;
}

void list::start(int size){
    if(head) destruct();
    length = size + 10;
    head = new node_tuple [length];
    tail = -1;
}

void list::append(int value){
    if(!head){
        cout << "Run start() before trying to append the list." << endl;
        throw "Run start() before trying to append the list.";
    }
    if(tail == length){
        grow();
    }
    ++tail;
    head[tail].set(value);

}
void list::append(char symbol){
    if(!head){
        cout << "Run start() before trying to append the list." << endl;
        throw "Run start() before trying to append the list.";
    }
    if(tail == length){
        grow();
    }
    ++tail;
    head[tail].set(symbol);
}

void list::set(int key, int value){
    if(!head){
        cout << "Run start() before trying to alter members." << endl;
        throw "Run start() before trying to alter members.";
    }
    if(key > tail){
        cout << "Key for set() is out of bounds." << endl;
        throw "Key for set() is out of bounds.";
    }
    head[key].set(value);
}
void list::set(int key, char symbol){
    if(!head){
        cout << "Run start() before trying to alter members." << endl;
        throw "Run start() before trying to alter members.";
    }
    if(key > tail){
        cout << "Key for set() is out of bounds." << endl;
        throw "Key for set() is out of bounds.";
    }
    head[key].set(symbol);
}

node_tuple list::get(int key){
    if(!head){
        cout << "Run start() before trying to get members data." << endl;
        throw "Run start() before trying to get members data.";
    }
    if(key > tail){
        cout << "Key for get() is out of bounds." << endl;
        throw "Key for get() is out of bounds.";
    }
    return head[key];
}

void list::remove(int key){
    if(!head){
        cout << "Run start() before trying to remove members." << endl;
        throw "Run start() before trying to remove members.";
    }
    if(key > tail){
        cout << "Key for remove() is out of bounds." << endl;
        throw "Key for remove() is out of bounds.";
    }

    for(int i=key; i < tail; ++i){
        node_tuple next = head[i+1];
        if(next.symbol == '\0'){
            head[i].set(next.value);
        }
        else {
            head[i].set(next.symbol);
        }
    }
    --tail;
}
void list::destruct(){
    if (head) delete [] head;
    head = NULL;
}
void list::grow(){
    node_tuple * temp = head;
    length += 10;
    head = new node_tuple[length];
    for(int i=0;i <= tail;++i){
        if(temp[i].symbol == '\0'){
            head[i].set(temp[i].value);
        }
        else {
            head[i].set(temp[i].symbol);
        }
    }
    delete [] temp;
}

void list::insert_next(int key, int value){
    if(!head){
        cout << "Run start() before trying to insert new members." << endl;
        throw "Run start() before trying to insert new members.";
    }
    if(key > tail || key < 0){
        cout << "Key for insert_next() is out of bounds." << endl;
        throw "Key for insert_next() is out of bounds.";
    }
    if(tail == length){
       grow(); 
    }
    ++tail;
    for(int i = tail; i > key;--i){
      node_tuple previous = head[i-1];
        if(previous.symbol == '\0'){
            head[i].set(previous.value);
        }
        else {
            head[i].set(previous.symbol);
        }  
    }
    head[key+1].set(value);
}
void list::insert_next(int key, char symbol){
    if(!head){
        cout << "Run start() before trying to insert new members." << endl;
        throw "Run start() before trying to insert new members.";
    }
    if(key > tail || key < 0){
        cout << "Key for insert_next() is out of bounds." << endl;
        throw "Key for insert_next() is out of bounds.";
    }
    if(tail == length){
       grow(); 
    }
    ++tail;
    for(int i = tail; i > key;--i){
      node_tuple previous = head[i-1];
        if(previous.symbol == '\0'){
            head[i].set(previous.value);
        }
        else {
            head[i].set(previous.symbol);
        }  
    }
    head[key+1].set(symbol);
}

void list::insert_prev(int key, int value){
    if(!head){
        cout << "Run start() before trying to insert new members." << endl;
        throw "Run start() before trying to insert new members.";
    }
    if(key > tail || key < 0){
        cout << "Key for insert_prev() is out of bounds." << endl;
        throw "Key for insert_prev() is out of bounds.";
    }
    if(tail == length){
       grow(); 
    }
    ++tail;
    for(int i = tail; i > key;--i){
      node_tuple previous = head[i-1];
        if(previous.symbol == '\0'){
            head[i].set(previous.value);
        }
        else {
            head[i].set(previous.symbol);
        }  
    }
    head[key].set(value);
}
void list::insert_prev(int key, char symbol){
    if(!head){
        cout << "Run start() before trying to insert new members." << endl;
        throw "Run start() before trying to insert new members.";
    }
    if(key > tail || key < 0){
        cout << "Key for insert_prev() is out of bounds." << endl;
        throw "Key for insert_prev() is out of bounds.";
    }
    if(tail == length){
       grow(); 
    }
    ++tail;
    for(int i = tail; i > key;--i){
      node_tuple previous = head[i-1];
        if(previous.symbol == '\0'){
            head[i].set(previous.value);
        }
        else {
            head[i].set(previous.symbol);
        }  
    }
    head[key].set(symbol);
}

int list::get_size(){
    return tail;
}

void list::display(){
    for(int i=0; i <= tail;++i){
        if(head[i].symbol == '\0'){
            cout << head[i].value << " ";
        }
        else{
            cout << head[i].symbol << " ";
        }
    }
    cout << endl;
}