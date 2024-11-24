#include <iostream>
#include <cmath>
using namespace std;

double h0  = 0 ; 
double eps  = 0 ;  
int nbr  = 0 ; 
double v,v1,h,h1 = 0 ; 

int main() {  

    do  {

        cout << "entrez la hauteur initiale" << endl ; 
        cout << "entrez le coefficient de rebond" << endl ; 
        cout << "entrez le nombre de rebond" << endl  ;

        cin >> h0 ; 
        cin >> eps ; 
        cin >> nbr ; 


    } while ( (h0 <= 0 ) or  (eps >= 1) or (eps <= 0) or (nbr <= 0) ) ;




    for (int i= 0  ; i < nbr ; ++i ) {

        v = sqrt(2*h0*9.81) ;
        v1 = eps * v ; 
        h = ( v1 * v1 )/ ( 2 * 9.81) ; 


        h0 = h ; 


    }

    cout << h << endl ; 

}

    
