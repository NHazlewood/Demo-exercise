//Ned Hazlewood
#include "header.h"


int main () {
    
    //Interacting with the user
    /*
    cout << "Please enter an arithmetic expression (with no whitespace)" << endl;

    char inputBuffer[50];
    cin.get(inputBuffer,50,'\n'); cin.ignore(100,'\n');
    int n = strlen(inputBuffer);
    char * input = new char[n+1];
    strcpy(input, inputBuffer);
    equation equ;
    equ.set(input);
    int answer = equ.eval();
    cout << "   = " << answer <<endl;
    delete [] input;
    input = NULL;
    */

    //Running tests
    ///*
    equation equ2;
    test(equ2);
    //*/

    return 0;
}

bool is_symbol(char symbol){
    int n = strlen(symbols);
    for(int i=0;i<n;++i){
        if(symbol == symbols[i]){
            return true;
        }
    }
    return false;
}

void test(equation equ){
    char test1[] = {'1','+','1','\0'};
    char test2[] = {'(','3','+','4',')','*','6','\0'};
    char test3[] = {'(','1','*','4',')','+','(','5','*','2',')','\0'};
    char test4[] = {'4','6','+','5','4','\0'};
    char test5[] = {'3','*','2','\0'};
    char test6[] = {'3','0','0','*','1','2','0','\0'};
    char test7[] = {'3','*','(','4','+','2',')','\0'};
    char test8[] = {'(','2','+','2',')','*','(','3','+','1',')','\0'};
    char test9[] = {'3','*','(','5','*','(','1','+','2',')','+','4',')','\0'};
    char test10[] = {'5','(', '3', ')','*','5','\0'};
    char test11[] = {'4','-','5','\0'};
    char test12[] = {'5','*','-','(', '3', ')','*','5','\0'};

    int answer = 0;

    cout << "Testing in process" << endl;

    equ.set(test1);
    answer = equ.eval();
    cout << "1 + 1 = " << answer << endl;
    if(answer == 2) cout << "Success" << endl;
    else cout << "Failure" << endl; 

    equ.set(test2);
    answer = equ.eval();
    cout << "(3 + 4) * 6 = " << answer << endl;
    if(answer == 42) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test3);
    answer = equ.eval();
    cout << "(1 * 4) + (5 * 2) = " << answer << endl;
    if(answer == 14) cout << "Success" << endl;
    else cout << "Failure" << endl; 

    equ.set(test4);
    answer = equ.eval();
    cout << "46 + 54 = " << answer << endl;
    if(answer == 100) cout << "Success" << endl;
    else cout << "Failure" << endl; 

    equ.set(test5);
    answer = equ.eval();
    cout << "3 * 2 = " << answer << endl;
    if(answer == 6) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test6);
    answer = equ.eval();
    cout << "300 * 120 = " << answer << endl;
    if(answer == 36000) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test7);
    answer = equ.eval();
    cout << "3 * (4 + 2) = " << answer << endl;
    if(answer == 18) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test8);
    answer = equ.eval();
    cout << "(2 + 2) * (3 + 1) = " << answer << endl;
    if(answer == 16) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test9);
    answer = equ.eval();
    cout << "3 * (5 * (1 + 2) + 4) = " << answer << endl;
    if(answer == 57) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test10);
    answer = equ.eval();
    cout << "5 (3) * 5 = " << answer << endl;
    if(answer == 75) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test11);
    answer = equ.eval();
    cout << "4 - 5 = " << answer << endl;
    if(answer == -1) cout << "Success" << endl;
    else cout << "Failure" << endl;

    equ.set(test12);
    answer = equ.eval();
    cout << "5 * -(3) * 5 = " << answer << endl;
    if(answer == -75) cout << "Success" << endl;
    else cout << "Failure" << endl;

    cout << "End of tests" << endl;
}