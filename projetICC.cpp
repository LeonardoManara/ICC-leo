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
void verification_2_liste_queues(vector<queue<int> >& queues_N,
 vector<queue<int> >& queues_F, int nbF, vector<int> &taille_queue);
void construction_liste_bool(vector<queue<int> >liste_queues, int nbF,
 vector<bool> &bool_N, vector<bool> &bool_F) ;
bool all_empty(vector<bool> liste_bool, int nbF);
void affiche_etat_initial (vector<queue<int> > liste_queues, int nbF);
int i_non_vide(vector<bool> &liste_bool, int nbF);
void verification_premiere_liste(vector<bool> liste_bool, int nbF, int &i,
 int &nbC, int &d, string display_type);
void NEQLI(vector<queue<int> >queues_N, vector<bool> bool_N, int &nbC1,
 int nbF, int &d1, vector<double> &at_moy_N, string display_type);
void pop(vector<queue<int> > &liste_queues, vector<bool> &liste_bool,
 vector<double> &at_moy,int &i, int &c ,int  &nbC,int  &d, string display_type);
bool NEQLI_1(vector<bool> liste_bool, int nbF, int &i, int c,
 int &nbC1, int &d1, bool &iscan, string display_type);
void construction_done(vector<bool> liste_bool, vector<bool> &done, int nbF);
void FANEQLI(vector<queue<int> >&queues_F, vector<bool> &bool_F, vector<bool> done,
 int &nbC2, int nbF, int &d2, vector<double> &at_moy_F, string display_type);
bool FANEQLI_2(vector<bool> done, int &nbC2, int nbF,int &j, int &i, int &d2,
 bool &iscan, string display_type);
void FANEQLI_3(vector<bool> done, bool iscan, int j, string display_type) ;
bool FANEQLI_4(vector<bool> done, vector<bool> bool_F, int &j,
 int &nbC2, int &d2, bool &iscan, int nbF, string display_type);
void FANEQLI_5(int j, string display_type);
void affiche_attente_moyenne(int nbF, vector<double> at_moy_N,
 vector<double> at_moy_F, vector<int> taille_queue);

// début programme

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

void verification_2_liste_queues(vector<queue<int> >& queues_N,
 vector<queue<int> >& queues_F, int nbF, vector<int> &taille_queue) {

    int f, c = 0 ; 
    cin >> f >> c  ; 
      
    while ((f >= 0) and (c >= 0)) {

        if ((f >= nbF) or (c >= nbF)) {
            print_error(BAD_QUEUE_INDEX) ; 
        }

        queues_N[f].push(c) ;
        queues_F[f].push(c) ;
        taille_queue[f] = taille_queue[f] + 1 ;

        cin >> f >> c  ;

    } 
 
}

// construction liste de bool , si file d atztente vide alors bool vrai sinon faux 

void construction_liste_bool(vector<queue<int> >liste_queues, int nbF,
 vector<bool> &bool_N, vector<bool> &bool_F) {

    for (int i = 0 ; i < nbF ; i ++ ) {

        if (liste_queues[i].empty()) {

            bool_N[i] = true ; 
            bool_F[i] = true ;

        } else {

            bool_N[i] = false  ; 
            bool_F[i] = false  ;
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


void verification_premiere_liste(vector<bool> liste_bool, int nbF, int &i,
 int &nbC, int &d, string display_type) {

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


void pop(vector<queue<int> > &liste_queues, vector<bool> &liste_bool,
 vector<double> &at_moy,int &i, int &c ,int  &nbC,int  &d, string display_type) {

    c = liste_queues[i].front() ;
    liste_queues[i].pop() ;

    if (display_type == "SHOW_CYCLES"){
        cout << i <<"       "<< c << "      " ;  
    }

    at_moy[i] = at_moy[i] + nbC ;
    nbC = nbC + 1 ;
    d = d + abs(c-i) ;

    if (liste_queues[i].empty()) {
        liste_bool[i] = true ; 
    }


}

bool NEQLI_1(vector<bool> liste_bool, int nbF, int &i, int c,
 int &nbC1, int &d1, bool &iscan, string display_type) {

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

void NEQLI(vector<queue<int> >queues_N, vector<bool> bool_N, int &nbC1,
 int nbF, int &d1, vector<double> &at_moy_N, string display_type) {

    int i = 0, c = 0 ;
    bool iscan = false  ; 
    nbC1 = 1;

    if (display_type == "SHOW_CYCLES"){
        cout << "NEQLI" << endl ;
    }

    verification_premiere_liste(bool_N, nbF, i, nbC1, d1, display_type) ;

    while (i < nbF ) {
           
        pop(queues_N, bool_N, at_moy_N, i, c , nbC1, d1, display_type) ;

        if (display_type == "SHOW_CYCLES"){

            if (!iscan) {
                cout << "0 1" << endl ;
            }  else { 
                cout << "1 1" << endl ;
            } 
        }

        iscan = true ;
        i = c ; 
        
        if (NEQLI_1(bool_N, nbF, i, c, nbC1, d1, iscan, display_type)) {
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


bool FANEQLI_2(vector<bool> done, int &nbC2, int nbF,int &j, int &i, int &d2,
 bool &iscan, string display_type) { 

    if (done[j]) {
                
        i = i_non_vide(done, nbF) ; 
        iscan = true ; 

        if (i == nbF) {
            return false ; 

        } else {
            
            if (display_type == "SHOW_CYCLES") {
                cout << j <<"       " ; 
            } 

            d2 = d2 + abs(i-j) ; 
            nbC2 = nbC2 + 1 ; 
            j = i;

            if (display_type == "SHOW_CYCLES") {
                cout << j <<"      " << "1 0" << endl ;
            }    

            iscan = false ;
            
        
        }
    }

    return true ; 

}

void FANEQLI_3(vector<bool> done, bool iscan, int j, string display_type)  {

    if (display_type == "SHOW_CYCLES") {

        if (!done[j] and iscan) {   
            cout << "1 1" << endl ;
        }  else { 
            cout << "0 1" << endl ; 
        } 
    }
}


bool FANEQLI_4(vector<bool> done, vector<bool> bool_F, int &j,
 int &nbC2, int &d2, bool &iscan, int nbF, string display_type) {

    if (all_empty(done, nbF)) {
        return true ; 
    }
 
    if (done[j]) {

        if (display_type == "SHOW_CYCLES") {
            cout << j << "       " ;
        }

        d2 = d2 + abs(j-i_non_vide(done, nbF)) ; 
        nbC2 = nbC2 + 1 ;

        j = i_non_vide(done, nbF) ; 

        if (display_type == "SHOW_CYCLES") {
            cout << j << "      " << "1 0" << endl ; 
        }

        iscan = false ; 
    }

    if (all_empty(bool_F, nbF)) {
        return true ; 
    }

    return false ; 
}   

void FANEQLI_5(int j, string display_type) {

    if (display_type == "SHOW_CYCLES") {
        cout <<  j << "       " << j << "      " << "1 0" << endl ; 
    } 
}

void FANEQLI(vector<queue<int> >&queues_F, vector<bool> &bool_F, vector<bool> done,
 int &nbC2, int nbF, int &d2, vector<double> &at_moy_F, string display_type) {

    int i = 0, j = 0 , c = 0 ;
    bool iscan = false ; 
    nbC2 = 1 ;

    if (display_type == "SHOW_CYCLES"){
        cout << "FANEQLI" << endl ;
    }

    verification_premiere_liste(bool_F, nbF, j, nbC2, d2, display_type) ;

    while (i < nbF) {

        construction_done(bool_F , done, nbF) ;

        while (j < nbF) {
           
            if (!FANEQLI_2(done, nbC2, nbF, j, i, d2, iscan, display_type)) {
                break ; 
            }

            pop(queues_F, bool_F, at_moy_F, j, c , nbC2, d2, display_type) ;
            FANEQLI_3(done, iscan, j, display_type) ; 
            iscan = true ; 
            done[j] = true ; 
            j = c ; 

            if (FANEQLI_4(done, bool_F, j, nbC2, d2, iscan, nbF, display_type)) {
                break ; 
            }      
        }  

        if (all_empty(bool_F, nbF)) {
            FANEQLI_5(j, display_type);
            break ; 
        }     
    }
}    



void affiche_attente_moyenne(int nbF, vector<double> at_moy_N,
 vector<double> at_moy_F, vector<int> taille_queue) {

    cout << "Attente moyenne" << endl ; 
    cout << setprecision(2) << fixed;

    for (int i = 0 ; i < nbF ;  i ++ ) {

        cout << i << "       " ; 
        
        
        if (taille_queue[i] != 0) {

            cout << at_moy_N[i]/taille_queue[i] << "   ";
            cout << at_moy_F[i]/taille_queue[i] << endl ; 

            } else {
            cout << endl ; 
        } 

    }

}


int main () {

    int nbF = 0, nbC1 = 0, nbC2 = 0, d1 = 0, d2 = 0  ; 
    string display_type ; 

    verification_1(display_type, nbF) ;

    vector<queue<int> > queues_N(nbF), queues_F(nbF) ;
    vector<bool> bool_N(nbF), bool_F(nbF), done(nbF, false);
    vector<double> at_moy_N (nbF, 0), at_moy_F (nbF, 0) ;
    vector<int> taille_queue(nbF, 0) ; 

    verification_2_liste_queues(queues_N, queues_F, nbF, taille_queue) ;
    construction_liste_bool(queues_N, nbF, bool_N, bool_F);

    affiche_etat_initial(queues_N, nbF) ;

    if (all_empty(bool_N, nbF)) {

        if (display_type == "SHOW_CYCLES"){
            cout << "NEQLI" << endl << "FANEQLI" << endl ; 
        }

    } else {
        
        NEQLI(queues_N, bool_N, nbC1, nbF, d1, at_moy_N, display_type) ;
        FANEQLI(queues_F, bool_F, done, nbC2, nbF, d2, at_moy_F, display_type) ;

    }
 
    cout << "Nombre de cycles" << endl ; 
    cout << nbC1 << "      " << nbC2 << endl ; 

    cout << "Déplacement total" << endl ;
    cout << d1 << "      " << d2 << endl ; 

    affiche_attente_moyenne(nbF, at_moy_N, at_moy_F, taille_queue) ; 

}

