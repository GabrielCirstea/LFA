#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;
// vrem sa facem un automat extins pt a transforma un automant intr-o expresie.
// trebuie sa renotam tranzitiile
// daca avem mai multe tranzitii intre x si y, fom face o singura tranzitie cu toate caracterele
// retinem renotarea si retinem etichetele ca indici
#define VEC_SIZE 20     ///pt alocarea statica
#define LAMBDA '\\'
#define forit(lista,it) for(list<int>::iterator it = lista.begin();it!=lista.end();it++)
#define EMP_BUF(fisier) {\
        char c = fisier.peek();\
        while(c == '\n' || c == '\r')\
        {\
            fisier.get();\
            c = fisier.peek();\
        }\
    }

int nrStari;
int stariFinale[VEC_SIZE];
string alfabet;
list<int> matrice[VEC_SIZE][VEC_SIZE];

void afisare()
{///afisarea datelor cititea din fisier
    cout<<"NrStari: "<<nrStari<<endl;
    cout<<"Alfabet: "<<alfabet<<endl;
    cout<<"Stari finale: ";
    for(int i=0;i<=nrStari;i++)
        cout<<stariFinale[i]<<" ";
    cout<<endl;
}

void init_matrice(int matrice[VEC_SIZE][VEC_SIZE], int linii, int col ,int val)
{
  for(int i=0;i<linii;i++)
    {
      for(int j=0;j<col;j++)
        {
          matrice[i][j] = val;
        }
    }
}

void afisare_matrice(list<int> matrice[20][20],int dimMatrice)      ///afisarea pt AFN
{
    cout<<"    ";
    for(unsigned int i = 0;i<alfabet.length();i++)
        cout<<alfabet[i]<<"  ";
    cout<<endl;
    for(int i = 0;i<dimMatrice;i++)
    {
        cout<<i<<":";
        for(unsigned int j = 0;j<alfabet.length();j++)
        {
            cout<<"{";
            for(list<int>::iterator t = matrice[i][j].begin();t!=matrice[i][j].end();t++)
            {
                cout<<*t<<", ";
            }
            cout<<"}";
        }
        cout<<endl;
    }
}

void citire_fisier(ifstream &f)
{
    f>>nrStari;
    f.get();
    EMP_BUF(f);
    getline(f,alfabet);		//citeste alfabetul
    alfabet+= LAMBDA;  ///lambda este '\'
    for(int i=0;i<=nrStari;i++)		//citeste starile finale
    {
        f>>stariFinale[i];
    }
    int nrTranzitii;
    f>>nrTranzitii;
    for(int i=0;i<nrTranzitii;i++)
    {
        char litera;
        int sursa,dest;
        f>>litera;
        f>>sursa;
        f>>dest;
        matrice[sursa][alfabet.find(litera,0)].push_back(dest);
    }
}

void appendExp(string& exp, const string& c)
{
	if(exp.find(LAMBDA,0) != string::npos)		// daca aveam lambda in cuvant steergem tot
		exp.erase();							// cel mai probabil era doar lambda acolo
	if(exp.length())
		exp += "|";
	exp += c;
}

void appendExp(string& exp, char c)		// adauga caractere in expresia initiala a AFE
{
	if(exp.find(LAMBDA,0) != string::npos)		// daca aveam lambda in cuvant steergem tot
		exp.erase();							// cel mai probabil era doar lambda acolo
	if(exp.length())
	{
		if(c == LAMBDA)		// nu adaugam lambda dupa alta litera
			return;
		exp += "|";
	}
	exp += c;
}

void concatExp( string& exp,char c)		// concatenarea unui caracter la expresie
{
	if(c == LAMBDA)		// nu adaugam lambda
		return;
	exp += c;
}

void concatExp( string& exp,const string& c)	// cancatenare la expresie
{
	if(exp.find(LAMBDA,0) != string::npos)		// daca aveam lambda in cuvant steergem tot
		exp.erase();							// cel mai probabil era doar lambda acolo
	exp += c;
}

//matricea AFE va tine mintea ranzitia de la stare la stare
//					nu ce tranzitie pleaca din stare
//Prima stare v-a fi noua stare initiala
//aici se adauga si starea finala
string matriceAFE[VEC_SIZE][VEC_SIZE];
int stariAFE;		// se adauga si noua stare initiala si cea finala

void matrice_AFE()		// ma mai gandesc la nume
{	// constuieste matricea pentru AFE
	stariAFE = nrStari+2;
	matriceAFE[0][1] = LAMBDA;		// prima tranzitie e intre starea 0 si 1(vechea stare initiala)
	// transformam matricea anterioara in noua matrice
	for(int i = 0;i< stariAFE;i++)
	{		// facem tranzitiile pentru fiecare litera din starea i
		for(int c = 0; alfabet[c]; c++)
			for(int x : matrice[i][c])
			{
				cout<<"dam apend la "<<alfabet[c]<<" pt "<<i<<"si "<<x<<endl;
				appendExp(matriceAFE[i+1][x+1],alfabet[c]);
				cout<<matriceAFE[i+1][x];
			}
	}
	// facem starea finala
	for(int i = 0;i<=nrStari;i++)
	{
		if(stariFinale[i])
			matriceAFE[i+1][stariAFE] = LAMBDA;
	}
}

void afisare_matriceAFE(string matrice[20][20],int dimMatrice)      ///afisarea pt AFN
{
    cout<<"    ";
    for(unsigned int i = 0;i<dimMatrice;i++)
        cout<<i<<"    ";
    cout<<endl;
    for(int i = 0;i<dimMatrice;i++)
    {
        cout<<i<<":";
        for(unsigned int j = 0;j<dimMatrice;j++)
        {
            cout<<"{";
                cout<<matrice[i][j]<<", ";
            cout<<"} ";
        }
        cout<<endl;
    }
}

string paranteze(const string& exp)
{
	string rez;
	if(exp.find(LAMBDA,0) != string::npos)
		return rez;
	if(exp.length()>1)
		rez = "(" + exp + ")";
	else
		rez = exp;
	return rez;
}

bool eliminare_latura(int start, int stare)		// primeste indicele starii si face legatura
{
	bool modificare = 0; // daca s-au produs schimbari
	for(int i = 0;i<=stariAFE;i++)
	{
		if(i != stare && matriceAFE[stare][i].length())
		{
			modificare = true;
			string expresie;
			expresie = paranteze(matriceAFE[start][stare]);
			matriceAFE[start][stare].clear();
			if(matriceAFE[stare][stare].length())	// daca avem bucla
			{
				concatExp(expresie,paranteze(matriceAFE[stare][stare]));
				expresie += "*";
			}
			if(matriceAFE[stare][i].find(LAMBDA,0) == string::npos)		//  cuvantul vid nu se adauga in expresie
				expresie += matriceAFE[stare][i];
			
			// o adaugam cu \"sau\" intre starea de inceput si cea la care am ajuns
			appendExp(matriceAFE[start][i],expresie);

			//stergem legatura stare - i
			matriceAFE[stare][i].erase();
		}
	}
	// stergem tranzitia dintre cele doua stari pentru a nu o repeta
	//if(modificare)
		//matriceAFE[start][stare].clear();
	
	return modificare;
}

void expresitivizare()			// funcita care elimina tranzitiile
{
	bool run = true;
	while(run)
	{
		run = false;
		for(int i =1; i<stariAFE;i++)
		{
			if(matriceAFE[0][i].length())		// daca avem legatura intre stari
			{
				if(eliminare_latura(0,i))
					run = true;
				afisare_matriceAFE(matriceAFE,stariAFE+1);
			}
		}
	}
}


int main()
{
  cout<<"Salutare!\n";
  ifstream f("date.in");
  citire_fisier(f);
  afisare();
  afisare_matrice(matrice,nrStari+1);
  matrice_AFE();
  afisare_matriceAFE(matriceAFE,stariAFE+1);
  expresitivizare();
  afisare_matriceAFE(matriceAFE,stariAFE+1);

  return 0;
}
