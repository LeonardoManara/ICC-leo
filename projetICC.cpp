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
void verification_2_liste_queues(vector<queue<int> >&liste_queues, int nbF, vector<int> &taille_queue) ;
void construction_liste_bool(vector<queue<int> >liste_queues, int nbF , vector<bool> &liste_bool) ; 
void affiche_etat_initial (vector<queue<int> > liste_queues, int nbF) ; 
int nombre_de_cycles(vector<queue<int> >liste_queues, vector<bool> &liste_bool, int &nbCycle, int nbF, int &d1, vector<double> &attente_moyenne_NEQLI) ;  
int i_non_vide(vector<bool> &liste_bool, int nbF) ; 
void affiche_attente_moyenne(int nbF, vector<double> attente_moyenne_NEQLI, vector<int> taille_queue) ;


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

void verification_2_liste_queues(vector<queue<int> >& liste_queues, int nbF, vector<int> &taille_queue) {

    int file_attente_arrive, couloir_sortie = 0 ; 

    

    cin >> file_attente_arrive >> couloir_sortie  ; 
      
    while ((file_attente_arrive >= 0) and (couloir_sortie >= 0)) {


    
        if ((file_attente_arrive >= nbF) or (couloir_sortie >= nbF)) {

            print_error(BAD_QUEUE_INDEX) ; 
        }

        liste_queues[file_attente_arrive].push(couloir_sortie) ;
        taille_queue[file_attente_arrive] = taille_queue[file_attente_arrive] + 1 ;

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


    for ( int j = 0 ; j < nbF ; j ++ ) {

       if  (liste_bool[j] == false) {

            return j ;

       }

    }   

 return nbF ; 

}


int nombre_de_cycles(vector<queue<int> >liste_queues, vector<bool> &liste_bool, int &nbCycle, int nbF, int &d1, vector<double> &attente_moyenne_NEQLI) {

    int i = 0 ;
    int c = 0 ;
    bool iscan = false  ; 
    cout << "NEQLI" << endl ; 

    if (liste_bool[0]) {
        cout << i << "       " ;
        i =  i_non_vide(liste_bool, nbF) ;
        cout << i << "      " << "0 0" << endl ;         
    } 

    while (i < nbF ) {
           
            
        if (i >= nbF ) {
            
            return nbCycle ; 
        }

        c = liste_queues[i].front() ;
        liste_queues[i].pop() ;
        cout << i <<"       "<< c << "        " ;  
        attente_moyenne_NEQLI[i] = attente_moyenne_NEQLI[i] + nbCycle ;
        nbCycle = nbCycle + 1 ;

        if (iscan == false) {
            cout << "0 1" << endl ;

        }  else { 

            cout << "1 1" << endl ;

        } 
        d1 = d1 + abs(c-i) ;
        iscan = true ;

        if (liste_queues[i].empty()) {

            liste_bool[i] = true ; 

        }

        i = c ; 
        

        if (liste_bool[i]) {
            cout << i << "       " ; 
            i =  i_non_vide(liste_bool, nbF) ; 
            
            if (i == nbF) {
                cout << c << "        "<<"1 0" << endl;
                break ; 

            }
            nbCycle = nbCycle + 1 ; 
            d1 = d1 + abs(c-i) ;
            cout << i << "        " << "1 0" << endl ;
            iscan = false   ;      
        }
    }
    cout << "Nombre de cylces" << endl ;
    return nbCycle  ;  
}


void affiche_attente_moyenne(int nbF, vector<double> attente_moyenne_NEQLI, vector<int> taille_queue) {

    cout << "Attente moyenne" << endl ; 
    cout << setprecision(2) << fixed;
    for (int i = 0 ; i < nbF ;  i ++ ) {

        cout << i << "       " << attente_moyenne_NEQLI[i]/taille_queue[i] << endl ;  

    }

}


int main () {

    int nbF, d1 = 0 ;
    int nbCycle = 1 ;
    string display_type ; 

    verification_1(display_type, nbF) ;

    vector<queue<int> > liste_queues(nbF);
    vector<bool> liste_bool(nbF);
    vector<double> attente_moyenne_NEQLI ( nbF, 0) ;
    vector<int> taille_queue( nbF, 0) ; 

    verification_2_liste_queues(liste_queues, nbF, taille_queue) ;
    construction_liste_bool(liste_queues, nbF , liste_bool);

    affiche_etat_initial(liste_queues, nbF) ;
 
    cout << nombre_de_cycles(liste_queues, liste_bool, nbCycle, nbF, d1, attente_moyenne_NEQLI) << endl ; 

    cout << "Déplacement total" << endl ;
    cout << d1 << endl ; 
    affiche_attente_moyenne(nbF, attente_moyenne_NEQLI, taille_queue) ; 

}

