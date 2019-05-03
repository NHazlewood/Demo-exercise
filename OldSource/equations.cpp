//Ned Hazlewood
#include "header.h"


equation::equation():head(NULL){}
equation::~equation(){
    node * current = head;
    node * temp = NULL;
    while(current){
        temp = current->next;
        delete current;
        current = temp;
    }
}

//takes an input array of chars and convert it into a a list for evaluation
//calls combine_ints, apply_negatives, and insert_multiplication preproccesors
void equation::set(char * input){
    if(!input) return;
    int i = 0;

    if(head){
        node * current = head;
        node * temp = NULL;
        while(current){
            temp = current->next;
            delete current;
            current = temp;
        }
        head = NULL;
    }
    
    while(input[i] != '\0'){
        node * temp = new node;
        if(is_symbol(input[i])){
            temp->set(input[i]);
        }
        else {
            temp->set((input[i]-'0')); 
        }

        if(!head){
            head = temp;
            head->prev = NULL;
        }
        else{
            head->add_tail(temp);
        }
        temp = NULL;
        ++i;  
    }
    combine_ints();
    apply_negatives();
    insert_multiplication();
}

//combines subquential numbers into  a single int i.e. {3,0,5} -> {305}
void equation::combine_ints(){
    node * current = head;
    node * int_start = NULL;
    node * int_end = NULL;
    node * temp = NULL;
    while(current){
        if(current->symbol == '\0'){ 
            if(!int_start) {int_start = current;}
            int_end = current;
        }
        else{
            if(int_start != int_end){
                temp = int_start->next;
                int_start->next = int_end->next;
                int_end->next = NULL;
                int adjustedSum = int_start->value; 
                while(temp){
                    adjustedSum = (adjustedSum * 10) + temp->value; 
                    int_end = temp;
                    temp = temp->next;
                    int_end->next = NULL;
                    delete int_end;
                }
                int_start->set(adjustedSum);
            }
            int_start = NULL;
            int_end = NULL;
        }
        current = current->next;
    }

    if(int_start && int_end && int_start != int_end){
        temp = int_start->next;
        int_start->next = int_end->next;
        int_end->next = NULL;
        int adjustedSum = int_start->value; 
        while(temp){
            adjustedSum = (adjustedSum * 10) + temp->value; 
            int_end = temp;
            temp = temp->next;
            int_end->next = NULL;
            delete int_end;
        }
        int_start->set(adjustedSum);
        int_start = NULL;
        int_end = NULL;
    }
}

//rewrites '-' for easier evaluation, avoids the ambiguity of it being a minus or negator operator
// turns minus into {+,-1,*} and negation into {-1,*}
void equation::apply_negatives(){
    node * current = head;
    
    while(current){
        if(current->symbol == '-'){
            node * previous = current->prev;
            node * next = current->next;
            if(!previous){
                node * temp = new node;
                temp->set(-1);
                temp->next = current;
                current->prev = temp;
                current->set('*');                
                head = temp;
                temp = NULL;
            }
            else {
                if(!next){
                    cout << "Incorrect equation, trailing minus" << endl;
                    clean_up();
                    throw "Incorrect equation, trailing minus";
                }
                else {
                    node * temp;
                    if(previous->symbol == '\0'){
                        temp = new node;
                        temp->set('+');
                        temp->next = current;
                        temp->prev = current->prev;
                        current->prev = temp;
                        previous-> next = temp;
                    }
                    current->set(-1);
                    current->symbol = '\0';
                    temp = new node;
                    temp->set('*');
                    temp->prev = current;
                    temp->next = next;
                    current->next = temp;
                    next->prev = temp;
                    temp = NULL;
                }
            }
            previous = NULL;
            next = NULL;
        }
        current = current->next;
    }
}
//inserts implied multiplication i.e x(y) because x*(y), simplifies evaluation
void equation::insert_multiplication(){
    node * current = head;

    while(current){
        if(current->symbol == '('){
            node * previous = current->prev;
            if(previous && previous->symbol == '\0'){
                previous->insert('*');
            }
            previous = NULL;
        }
        current = current->next;
    }
    
}
//wrapper for evaluate
int equation::eval(){ 
    node * tail;
    head->find_tail(tail);
    int answer = evaluate(head,tail);
    tail = NULL;
    return answer;
}

//recursive funtion, on the way down it finds sub-equations and calls evaluate or calculate on them
// on the return it repalces sub-equatiosn with the result.
int equation::evaluate (node *& start, node *& end){
    if(!end || !start){
        cout << "Invalid evaluate call, NULL pointer passed." << endl;
        clean_up();
        throw "Invalid evaluate call, NULL pointer passed.";
    }
    if(start == end) return start->value; //list of length 1
    if(start->next == end->prev){ //list of length 3
        if(start->symbol == '(' && end->symbol == ')') return start->next->value;
        return calculate(start, end);
    }
    node * current = start;
    int paren_counter = 0;
    node * inner_start = NULL;
    node * inner_end = NULL;
    //dealing with parenthese, since they are a special case were a pair is required 
    //and they can be nested so it needs unique logic
    while(current){
        if(current->symbol == '('){
            ++paren_counter;
            if(!inner_start){
                inner_start = current;
                paren_counter = 1;
            }
        }
        else {
            if(current->symbol == ')'){
                --paren_counter;
                if(paren_counter == 0){
                    //found a complete set of parenthese, calling evaluate of this subset of the equation
                    // and then removing all of its members from the oriognal equation, replace its value
                    inner_end = current;
                    inner_start->set(evaluate(inner_start->next,inner_end->prev));
                    node * temp = inner_start->next;
                    node * next = inner_end->next;
                    inner_end->next = NULL;
                    inner_start->next = next;
                    if(next) next-> prev = inner_start;
                    current = inner_start;
                    while(temp){
                        next = temp->next;
                        temp->next = NULL;
                        delete temp;
                        temp = next;
                    }
                    next = NULL;
                    temp = NULL;
                    inner_start = NULL;
                    inner_end = NULL;
                }
            }
        }
        if(current) current = current->next;
    }
    //dealing with other arithmetic operators, very similar to parenthese but we don't search for a matching pair
    //and since all the operators are binary operatorers we can dirrectly call calculate rather than re-evaluating
    int n = strlen(symbols); 
    for(int i=2;i<n;++i){
        current = start;
        while(current && current != end){
            if(current->symbol == symbols[i]){
                inner_start = current->prev;
                inner_end = current->next;
                if(!inner_start || !inner_end){
                    cout << "Formual error, operation symbol lacking 1 or more inputs." <<endl;
                    clean_up();
                    throw "Formual error, operation symbol lacking 1 or more inputs.";
                }
                inner_start->set(calculate(inner_start, inner_end));
                node * temp = inner_start->next;
                node * temp2 = inner_end->next;
                inner_start->next = temp2;
                if(temp2)temp2->prev = inner_start;
                temp2= NULL;
                inner_end->next = NULL;
                temp->next = NULL;
                delete temp;
                delete inner_end;
                current = inner_start;
                inner_start = NULL;
                inner_end = NULL;
            }
            if(current) current = current->next;
        }
    }
    if(start) return start->value;
    if(!start) {
        cout << "List lost in evaluation" << endl;
        clean_up();
        throw "List lost in evaluation";
    }
    return 0;
}

//reads the operator symobls and applies them to the intergers
int equation::calculate(node * start, node * end){
    if(!start || !end){
        cout << "Invalid calculate call, NULL pointer passed." << endl;
        clean_up();
        throw "Invalid calculate call, NULL pointer passed.";
    }
    int A = start->value;
    int B = end->value;
    char operation = start->next->symbol;

    if(operation == '*'){
        return A * B;
    } 
    if(operation == '+'){
        return A + B;
    }
    cout << "Unrecognized operation symbol:" << operation  << " in " << A << operation << B << endl;
    clean_up();
    throw "Unrecognized operation symbol.";
}

//called when throwing exceptions to avoid memmory leaks
void equation::clean_up(){
    node * current = head;
    node * temp = NULL;
    while(current){
        temp = current->next;
        delete current;
        current = temp;
    }
}