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
void NEQLI(vector<queue<int> >liste_queues, vector<bool> &liste_bool, int &nbC1, int nbF, int &d1, vector<double> &attente_moyenne_NEQLI) ;  
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

void verification_2_liste_queues(vector<queue<int> >& liste_queues, vector<queue<int> >& liste_queues_F, int nbF, vector<int> &taille_queue) {

    int file_attente_arrive, couloir_sortie = 0 ; 

    

    cin >> file_attente_arrive >> couloir_sortie  ; 
      
    while ((file_attente_arrive >= 0) and (couloir_sortie >= 0)) {


    
        if ((file_attente_arrive >= nbF) or (couloir_sortie >= nbF)) {

            print_error(BAD_QUEUE_INDEX) ; 
        }

        liste_queues[file_attente_arrive].push(couloir_sortie) ;
        liste_queues_F[file_attente_arrive].push(couloir_sortie) ;
        taille_queue[file_attente_arrive] = taille_queue[file_attente_arrive] + 1 ;

        cin >> file_attente_arrive >> couloir_sortie  ;

    } 

  
}

// construction liste de bool , si file d atztente vide alors bool vrai sinon faux 

void construction_liste_bool(vector<queue<int> >liste_queues, int nbF , vector<bool> &liste_bool_N, vector<bool> &liste_bool_F) {

    for (int i = 0 ; i < nbF ; i ++ ) {

        if (liste_queues[i].empty()) {

            liste_bool_N[i] = true ; 
            liste_bool_N[i] = true ;

        } else {

                liste_bool_N[i] = false  ; 
                liste_bool_F[i] = false  ;
            }

    }

}

bool all_empty(vector<bool> liste_bool, int nbF) {

    for (int j = 0 ; j < nbF ;  j++) {
        
        if (!liste_bool[j]) {

            return false ;
        }

    }

    return true ;
}

void affiche_etat_initial (vector<queue<int> > liste_queues, int nbF) {
    
    int i = 0 ; 
    cout << "Etat initial" << endl ; 
    
    for ( int i = 0 ;  i < nbF ; i++  ) {

     cout << i << "       " ;

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



void verification_premiere_liste(vector<bool> liste_bool, int nbF, int &i, int &nbC, int &d, string display_type) {

    if (liste_bool[0]) {

        if (display_type == "SHOW_CYCLES"){

            cout << i << "       " ;
        }
        i =  i_non_vide(liste_bool, nbF) ;

        if (display_type == "SHOW_CYCLES"){

            cout << i << "      " << "0 0" << endl ;
        } 
        nbC = nbC + 1 ;
        d = d + i  ;      
    }
}

void extraction_neqli(vector<queue<int> > &liste_queues, vector<double> &attente_moyenne_NEQLI, int &i, int &c ,int  &nbC1,int  &d1, bool iscan, string display_type) {

    c = liste_queues[i].front() ;
    liste_queues[i].pop() ;

    if (display_type == "SHOW_CYCLES"){

        cout << i <<"       "<< c << "      " ;  
    }

    attente_moyenne_NEQLI[i] = attente_moyenne_NEQLI[i] + nbC1 ;
    nbC1 = nbC1 + 1 ;
    d1 = d1 + abs(c-i) ;

    if (display_type == "SHOW_CYCLES"){

        if (!iscan) {

            cout << "0 1" << endl ;

        }  else { 

            cout << "1 1" << endl ;

        } 
    }

}

bool extraction_Neqli_2(vector<bool> liste_bool, int nbF, int &i, int c, int &nbC1, int &d1, bool &iscan, string display_type) {

    if (liste_bool[i]) {

        if (display_type == "SHOW_CYCLES"){
            cout << i << "       " ; 
        }
        i =  i_non_vide(liste_bool, nbF) ; 
            
        if (i == nbF) {

            if (display_type == "SHOW_CYCLES"){
                cout << c << "      "<<"1 0" << endl;
            }

            return true ; 

        }
            
        nbC1 = nbC1 + 1 ; 
        d1 = d1 + abs(c-i) ;

        if (display_type == "SHOW_CYCLES"){
            cout << i << "      " << "1 0" << endl ;
        }
        iscan = false   ;      
    }

    return false ; 
}

void NEQLI(vector<queue<int> >liste_queues, vector<bool> liste_bool, int &nbC1, int nbF, int &d1, vector<double> &attente_moyenne_NEQLI, string display_type) {

    int i = 0 ;
    int c = 0 ;
    bool iscan = false  ; 
    nbC1 = 1 ; 
   
    if (display_type == "SHOW_CYCLES"){

        cout << "NEQLI" << endl ;
    }

    verification_premiere_liste(liste_bool, nbF, i, nbC1, d1, display_type) ;

    while (i < nbF ) {
           
        extraction_neqli(liste_queues, attente_moyenne_NEQLI, i, c , nbC1, d1, iscan, display_type) ; 
        
        iscan = true ;

        if (liste_queues[i].empty()) {

            liste_bool[i] = true ; 

        }

        i = c ; 
        
        if (extraction_Neqli_2(liste_bool, nbF, i, c, nbC1, d1, iscan, display_type)) {
            break; 
        }
    }  
}


 void construction_done(vector<bool> liste_bool, vector<bool> &done, int nbF) {

    for (int j = 0 ; j < nbF ; j++) {

        if (!liste_bool[j]) {

            done[j] = false ;

        }  else {

            done[j] = true ; 
        }
    }
}


void FANEQLI(vector<queue<int> >&liste_queues_F, vector<bool> &liste_bool_F, vector<bool> done, int &nbC2, int nbF, int &d2, vector<double> &attente_moyenne_FANEQLI, string display_type) {

    int i = 0, j = 0 , c = 0 ;
    bool iscan = false ; 
    nbC2 = 1 ;

    if (display_type == "SHOW_CYCLES"){

        cout << "FANEQLI" << endl ;
    }

    verification_premiere_liste(liste_bool_F, nbF, j, nbC2, d2, display_type) ;


    while (i < nbF) {

        construction_done(liste_bool_F , done, nbF) ;

        while (j < nbF) {

            if (done[j]) {
                
                i = i_non_vide(done, nbF) ; 
                iscan = true ; 

                if (i == nbF) {
                    break ; 
                } else {

                    cout << j <<"       " ; 
                    d2 = d2 + abs(i-j) ; 
                    nbC2 = nbC2 + 1 ; 
                    j = i;
                    cout << j <<"      " << "1 0" << endl ;
                    iscan = false ;
                    
                   
                }
            }

            if (j == nbF) {
                break ; 
            }

            c = liste_queues_F[j].front() ;
            liste_queues_F[j].pop() ;

            attente_moyenne_FANEQLI[j] = attente_moyenne_FANEQLI[j] + nbC2 ;
            d2 = d2 + abs(j-c) ; 
            nbC2 = nbC2 + 1 ;
            
            cout << j <<"       "<< c << "      " ; 

            if (!done[j] and iscan) {

                cout << "1 1" << endl ;
                

            }  else { 

                cout << "0 1" << endl ; 

            } 

            iscan = true ; 

            done[j] = true ; 

            if (liste_queues_F[j].empty()) {

                liste_bool_F[j] = true ; 

            }

            j = c ; 

            if (all_empty(done, nbF)) {

                break ; 
            }

            if (done[j]) {
                cout << j << "       " ;

                d2 = d2 + abs(j-i_non_vide(done, nbF)) ; 
                nbC2 = nbC2 + 1 ;

                j = i_non_vide(done, nbF) ; 
                cout << j << "      " << "1 0" << endl ; 
                iscan = false ; 
            }

            if (all_empty(liste_bool_F, nbF)) {

            break ; 

            
        }
        

        }

        if (all_empty(liste_bool_F, nbF)) {

            cout <<  j << "       " << j << "      " << "1 0" << endl ;  
            break ; 
        }
        

    }
}    



void affiche_attente_moyenne(int nbF, vector<double> attente_moyenne_NEQLI, vector<double> attente_moyenne_FANEQLI, vector<int> taille_queue) {

    cout << "Attente moyenne" << endl ; 
    cout << setprecision(2) << fixed;
    for (int i = 0 ; i < nbF ;  i ++ ) {

        cout << i << "       " ; 
        
        
        if (taille_queue[i] != 0) {

            cout << attente_moyenne_NEQLI[i]/taille_queue[i] << "   ";
            cout << attente_moyenne_FANEQLI[i]/taille_queue[i] << endl ; 
            } else {

            cout << endl ; 
        } 

    }

}


int main () {

    int nbF = 0, nbC1 = 0, nbC2 = 0, d1 = 0, d2 = 0  ; 
    string display_type ; 

    verification_1(display_type, nbF) ;

    vector<queue<int> > liste_queues(nbF);
    vector<queue<int> > liste_queues_F(nbF) ; 
    vector<bool> liste_bool_N(nbF);
    vector<bool> liste_bool_F(nbF);
    vector<bool> done(nbF, false) ; 
    vector<double> attente_moyenne_NEQLI ( nbF, 0) ;
    vector<double> attente_moyenne_FANEQLI ( nbF, 0) ;
    vector<int> taille_queue( nbF, 0) ; 

    verification_2_liste_queues(liste_queues, liste_queues_F, nbF, taille_queue) ;
    construction_liste_bool(liste_queues, nbF , liste_bool_N, liste_bool_F);

    affiche_etat_initial(liste_queues, nbF) ;

    if (all_empty(liste_bool_N, nbF)) {

        if (display_type == "SHOW_CYCLES"){

            cout << "NEQLI" << endl << "FANEQLI" << endl ; 
        }

    } else {
        
        NEQLI(liste_queues, liste_bool_N, nbC1, nbF, d1, attente_moyenne_NEQLI, display_type) ;
        FANEQLI(liste_queues_F, liste_bool_F, done, nbC2, nbF, d2, attente_moyenne_FANEQLI, display_type) ;

    }
 
    cout << "Nombre de cycles" << endl ; 
    cout << nbC1 << "      " << nbC2 << endl ; 

    cout << "Déplacement total" << endl ;
    cout << d1 << "      " << d2 << endl ; 

    affiche_attente_moyenne(nbF, attente_moyenne_NEQLI, attente_moyenne_FANEQLI, taille_queue) ; 

}

