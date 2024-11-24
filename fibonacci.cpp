#include <iostream>
using namespace std;
int a =  0 ; 
int b = 1 ; 
int somma = 0 ; 



int main () {


    for (int i = 0 ; i<10 ; i ++) {
        
        somma = a + b ; 

        a = b ; 
        b = somma ; 
        
    }
    cout << somma ; 
}   