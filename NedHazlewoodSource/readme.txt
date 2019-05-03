Ned Hazlewood
hunting.hats@gmail.com

A few quick notes:
- I have the program currently in test mode , un-commenting code in main.cpp will put it into user interaction mode

- The program can throw an exceptions if the input is invalid, they aren't caught because in the current design the user 
wouldn't get a chance to alter their input. There are also internal throws that are not caught because they are more useful
 in finding the errors (for me anyways) as they are acting as segfaults for the list class.

-I tried to design my program to feel very different from the Shunting Yard algorithm and make it very easy to add new binary operators
for example if I wanted to add division it add '/' to symbols in header.h and then add (see below) to equation::calculate, and it would 
be ready to go 
    if(operation == '/'){
            return A / B;
	}
	
- Thank you for your time and consideration. 