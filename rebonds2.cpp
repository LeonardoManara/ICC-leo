#include <iostream>
#include <cmath>
using namespace std;

double h0, eps, h_fin, v, v1, h ; 
int i,m ; 

int main () {

    do {

        cout << "entrez la hauteur initiale" << endl ; 
        cout << "entrez le coefficient de rebond " << endl ; 
        cout << "entrez la hauteur finale " << endl ; 

        cin >> h0 ; 
        cin >> eps ; 
        cin >> h_fin ; 

    }  while ( (h0 <= 0) or (eps < 0) or (eps >= 1) or (h_fin <= 0) or (h_fin > h0)) ; 


    for (int i = 0 ; h0 > h_fin  ; i++ ){


        v = sqrt(2*h0*9.81) ;
        v1 = eps * v ; 
        h = ( v1 * v1 )/ ( 2 * 9.81) ; 

        h0 = h ;
        m = m + 1 ; 
    }


    cout << m << endl ; 
}