//Ned Hazlewood
#include <iostream>
#include <cctype>
#include <cstring>
#include <stdlib.h>
#include <math.h>
using namespace std;

//This global acts as validation for known operation symbols and sets the order of opertion used in evaluation
const char symbols[] = {'(',')','*','+','-','\0'};

class list;
class equation;
struct node_tuple;

bool is_symbol(char);
void test(equation);

struct node_tuple {
    void set(int value);
    void set(char symbol);
    int value;
    char symbol;
};

class list {
    public:
        list();
        ~list();
        void start(int size);
        void append(int value);
        void append(char symbol);
        void set(int key, int value);
        void set(int key, char symbol);
        node_tuple get(int key);
        void remove(int key);
        void destruct();
        void grow();
        void insert_next(int key, int value);
        void insert_next(int key, char symbol);
        void insert_prev(int key, int value);
        void insert_prev(int key, char symbol);
        int get_size();
        
        void display();

    private:
        node_tuple * head;
        int length;
        int tail;
};


class equation {
    public:
        equation();
        ~equation();
        void set(char *);
        int eval();
    private:
        void clean_up();
        void combine_ints();
        void apply_negatives();
        void insert_multiplication();
        int evaluate(int start, int end);
        int calculate(int start, int end);

        list eq_list;
};