#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;


// Error messages
const string BAD_DISPLAY_TYPE("Error: must be SHOW_CYCLES or SHOW_NO_CYCLE");
const string BAD_QUEUE_NB("Error: the number of queues must be strictly positive");
const string BAD_QUEUE_INDEX("Error: invalid queue index");

// prototype des fonctions 

void print_error(string message) ;
void verification_1(string& display_type, int& nbF) ; 
void verification_2_liste_queues(vector<queue<int> >&liste_queues, int nbF) ;
void construction_liste_bool(vector<queue<int> >liste_queues, int nbF , vector<bool> &liste_bool) ; 
void affiche_etat_initial (vector<queue<int> > liste_queues, int nbF) ; 
int nombre_de_cycles(vector<queue<int> >liste_queues, vector<bool> &liste_bool, int nbF, int &d1) ;  
int i_non_vide(vector<bool> &liste_bool, int nbF) ; 


void print_error(string message)
{
    cout << message ;    
    cout << endl;
    exit(0);
}


// lecture et vérification des données

void verification_1(string& display_type, int& nbF) {

    

    cin >> display_type ; 
    cin >> nbF ;  

    if ((display_type != "SHOW_CYCLES") and (display_type != "SHOW_NO_CYCLE")) {

        print_error(BAD_DISPLAY_TYPE);

    }
        
    if (nbF <= 0 ) {

        print_error(BAD_QUEUE_NB); 

    }

}  

void verification_2_liste_queues(vector<queue<int> >& liste_queues, int nbF) {

    int file_attente_arrive, couloir_sortie = 0 ; 

    

    cin >> file_attente_arrive >> couloir_sortie  ; 
      
    while ((file_attente_arrive >= 0) and (couloir_sortie >= 0)) {


    
        if ((file_attente_arrive >= nbF) or (couloir_sortie >= nbF)) {

            print_error(BAD_QUEUE_INDEX) ; 
        }

        liste_queues[file_attente_arrive].push(couloir_sortie) ; 

        cin >> file_attente_arrive >> couloir_sortie  ;

    } 

  
}

// construction liste de bool , si file d atztente vide alors bool vrai sinon faux 

void construction_liste_bool(vector<queue<int> >liste_queues, int nbF , vector<bool> &liste_bool) {

    for (int i = 0 ; i < nbF ; i ++ ) {

        if (liste_queues[i].empty()) {

            liste_bool[i] = true ; 

        } else {

                liste_bool[i] = false  ; 
            }

    }

}

void affiche_etat_initial (vector<queue<int> > liste_queues, int nbF) {
    
    int i = 0 ; 
    cout << "Etat initial" << endl ; 
    
    for ( int i = 0 ;  i < nbF ; i++  ) {

     cout << i << "     " ;

        while(!liste_queues[i].empty()) {

            cout << liste_queues[i].front() << " ";
            liste_queues[i].pop() ; 
        
        }
  
         cout << endl ; 
    }     

}

int i_non_vide(vector<bool> &liste_bool, int nbF) {

    int j = 0 ; 

    for (int j ; j < nbF ; j ++ ) {

       if  (liste_bool[j] == false) {

            return j ;

       }

    }   

    j = j + 1  ;

    return j ; 
}



int nombre_de_cycles(vector<queue<int> >liste_queues, vector<bool> &liste_bool, int nbF, int &d1) {

    int nbCycle = 1 ;
    int i, c = 0 ;

    while (i < nbF ) {
    
        if (liste_bool[0]) {

            nbCycle = nbCycle + 1 ; 
            i =  i_non_vide(liste_bool, nbF) ;
            d1 = d1 + i ; 
        }        
            
        if (i >= nbF ) {
            
            return nbCycle ; 
        }

        c = liste_queues[i].front() ;
        liste_queues[i].pop() ;

        d1 = d1 + abs(c-i) ; 

        if (liste_queues[i].empty()) {

            liste_bool[i] = true ; 

        }

        i = c ; 
        nbCycle = nbCycle + 1 ; 

        if (liste_bool[i]) {

            nbCycle = nbCycle + 1 ; 
            i =  i_non_vide(liste_bool, nbF) ; 
            d1 = d1 + abs(c-i) ;

        }

    }

    return nbCycle  ;  

}


int main () {

    int nbF, d1 = 0 ; 
    string display_type ; 

    verification_1(display_type, nbF) ;

    vector<queue<int> > liste_queues(nbF);
    vector<bool> liste_bool(nbF);

    verification_2_liste_queues(liste_queues, nbF) ;
    construction_liste_bool(liste_queues, nbF , liste_bool);

    affiche_etat_initial(liste_queues, nbF) ;

    cout << "Nombre de cylces" << endl ; 
    cout << nombre_de_cycles(liste_queues, liste_bool, nbF, d1) << endl ; 

   // cout << "Déplacement total" << endl ;
   // cout << d1 ;

}  






