//Ned Hazlewood
#include "header.h"

equation::equation(){}
equation::~equation(){}

//takes an input array of chars and convert it into a a list for evaluation
//calls combine_ints, apply_negatives, and insert_multiplication preproccesors
void equation::set(char * input){
    if(!input) return;
    int length = strlen(input);
    eq_list.start(length);
    for(int i=0;i<length;++i){
        if(is_symbol(input[i])) eq_list.append(input[i]);
        else eq_list.append((input[i]-'0'));
    }
    combine_ints();
    apply_negatives();
    insert_multiplication();
}

//combines subquential numbers into  a single int i.e. {3,0,5} -> {305}
void equation::combine_ints(){
    int n = eq_list.get_size();
    for(int i=0;i<n;++i){
        if(eq_list.get(i).symbol == '\0'){
            int adj_sum = 0;
            while(i+1 <= n && eq_list.get(i+1).symbol == '\0'){
                adj_sum = (eq_list.get(i).value * 10) + eq_list.get(i+1).value;
                eq_list.set(i,adj_sum);
                eq_list.remove(i+1);
                --n;
            }
        }        
    }
}

//rewrites '-' for easier evaluation, avoids the ambiguity of it being a minus or negator operator
// turns minus into {+,-1,*} and negation into {-1,*}
void equation::apply_negatives(){    
    int n = eq_list.get_size();
    for(int i=0;i<n;++i){
        if(eq_list.get(i).symbol == '-'){
            if( i != 0 && eq_list.get(i-1).symbol == '\0'){
                eq_list.insert_prev(i,'+');
                ++i;
            }
            eq_list.set(i,-1);
            eq_list.insert_next(i,'*');
        }
    }
}
//inserts implied multiplication i.e x(y) becomes x*(y), simplifies evaluation
void equation::insert_multiplication(){
    int n = eq_list.get_size();
    for(int i=1;i<n;++i){
        if(eq_list.get(i).symbol == '(' && eq_list.get(i-1).symbol == '\0'){
            eq_list.insert_prev(i,'*');
            ++n;
        }
    }
}
//wrapper for evaluate
int equation::eval(){
    int n = eq_list.get_size();
    int answer = evaluate(0,n);

    return answer;
}

// recursive funtion, on the way down it finds sub-equations and calls evaluate or calculate on them
// on the return it repalces sub-equations with the results.
int equation::evaluate (int start, int end){
    if(start == end){
        return eq_list.get(start).value;
    }
    if((start+2) == end){
        if(eq_list.get(start).symbol == '(' ) return eq_list.get(start+1).value;
        return calculate(start,end);
    }
    int tail = eq_list.get_size();
    int inner_start = -1;
    int paren_counter = 0;

    // handling parenthese, since parenthese need a pair and can be nested
    // they are being handled seperatly from the rest of the operators
    for(int i=start;i<=tail;++i){
        if(eq_list.get(i).symbol == '('){
            ++paren_counter;
            if(inner_start < 0){
                inner_start = i;
                paren_counter = 1;
            }
        }
        else {
            if(eq_list.get(i).symbol == ')'){
                --paren_counter;
                if(paren_counter == 0){
                    int return_catch = evaluate(inner_start+1, i-1);
                    if(eq_list.get_size() == 0) return return_catch;
                    eq_list.set(inner_start,return_catch); // replace (
                    while(eq_list.get(inner_start + 1).symbol != ')'){ //removing everthing between ( and )
                        eq_list.remove(inner_start+1);
                        --tail;
                    }
                    eq_list.remove(inner_start+1); //remove )
                    i = inner_start;
                    inner_start = -1;
                }
            }
        }
        tail = eq_list.get_size();
    }

    //handling all other symbols
    int lenth_symbols = strlen(symbols);
    for(int i=2;i<lenth_symbols;++i){
        for(int j=start;j<=tail;++j){
            if(eq_list.get(j).symbol == symbols[i]){
                int return_catch = calculate(j-1,j+1);
                eq_list.set(j,return_catch);
                eq_list.remove(j-1);
                eq_list.remove(j);
                --j;
                tail = eq_list.get_size();
            }
        }
    }
    return evaluate(0, eq_list.get_size());
}

//reads the operator symobls and applies them to the intergers
int equation::calculate(int start, int end){

    int A = eq_list.get(start).value;
    int B = eq_list.get(end).value;
    char operation = eq_list.get(start+1).symbol;

    if(operation == '*'){
        return A * B;
    } 
    if(operation == '+'){
        return A + B;
    }
    cout << "Unrecognized operation symbol" << endl;
    throw "Unrecognized operation symbol.";
    
    return 0;
}
