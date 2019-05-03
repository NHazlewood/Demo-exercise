//Ned Hazlewood
#include "header.h"

// node_tuble has a slightly special set() because for integers negative and 0
// are valid so symbol gets set to '\0' when value is valid
void node_tuple::set(char newSymbol){
    this->symbol = newSymbol;
    this->value = 0;
}
void node_tuple::set(int newValue){
    this->value = newValue;
    this->symbol = '\0';
}

