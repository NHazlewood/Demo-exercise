//Ned Hazlewood
#include <iostream>
#include <cctype>
#include <cstring>
#include <stdlib.h>
#include <math.h>
using namespace std;

//This global acts as validation for known operation symbols and sets the order of opertion used in evaluation
const char symbols[] = {'(',')','*','+','-','\0'};

class node;
class equation;
struct node_tuple;

bool is_symbol(char);
void test(equation);

struct node {
    public:
        node();
        void add_tail(node *&);
        void find_tail(node *&);
        void set(int);
        void set(char);
        void insert(char);
        void insert(int);

        int value;
        char symbol;
        node * next;
        node * prev;
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
        int evaluate(node *&, node *&);
        int calculate(node *, node *);

        node * head;
};