#include <iostream>
#include <queue>

using namespace std;

int main()
{
	queue<int> file_attente; // vide
	
	if(file_attente.empty()) cout << "file d'attente vide" << endl;
	
	int val(0);
	do 
	{
		cin >> val ;
		// push(val) ajoute val à la fin de la file d'attente
		file_attente.push(val); 
	}while(val>= 0);
	
	while(!file_attente.empty())
	{
		// front() renvoie la tête de la file d'attente sans l'enlever
		cout << file_attente.front() << endl ; 
				
		// pop() enlève la tête de la file d'attente
		file_attente.pop() ; 
	}
	
	if(file_attente.empty()) cout << "file d'attente vide" << endl;
		
	return 0;
}
