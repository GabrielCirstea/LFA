#include <iostream>
#include <fstream>
#include <queue>
#include <list>

using namespace std;

/**date fisier
    nr stari
    alfabet
    nr finale
    stare finala
    nr de adiacente
    caracter stare stare
    nr cuvinte
    cuvinte
*/

int nrStari, stariFinale[20];
string alfabet;
/// adiacente alfabet stari
list<int> matrice[20][20];
int dimMatrice;
int nrCuv;

void afisare_info()
{
	cout<<"Stari Finale ";
    cout<<"nrStari = "<<nrStari<<endl;
    for(int i=0;i<nrStari+1;i++)
    {
        cout<<stariFinale[i]<<" ";
    }
    cout<<endl;
    cout<<"alfabet:"<<alfabet<<endl;
}

void afisare_matrice(list<int> matrice[20][20],int dimMatrice)      ///afisarea pt AFN
{
    cout<<"    ";
    for(int i = 0;i<alfabet.length()-1;i++)
        cout<<alfabet[i]<<"  ";
    cout<<endl;
    for(int i = 0;i<dimMatrice;i++)
    {
        cout<<i<<":";
        for(int j = 0;j<alfabet.length()-1;j++)
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

void citire_imput(ifstream& fisier)         ///citirea pt AFN
{
    fisier>>nrStari;
    fisier.get();
    //fisier>>nrStariFinale;
    for(int i=0;i<=nrStari;i++)
        fisier>>stariFinale[i];
    fisier.get();
    getline(fisier,alfabet);
    fisier>>dimMatrice;
    for(int i = 0;i<dimMatrice;i++){
        char litera;
        int sursa,dest;
        fisier>>litera;
        fisier>>sursa;
        fisier>>dest;
        matrice[sursa][alfabet.find(litera,0)].push_back(dest);
    }
    dimMatrice = nrStari+1;
}

void delta(int stare, char c, queue<int>& coada)       ///adauga starile in coada
{
    for(list<int>::iterator t = matrice[stare][alfabet.find(c,0)].begin();
            t!=matrice[stare][alfabet.find(c,0)].end();t++)
    {
        coada.push(*t);
    }
}

int AFN(string cuvant)
{
    queue<int> coada, nou;
    coada.push(0);      ///suntem la inceputul procesarii cuvantului
    int stareCurenta;
    for(int i=0;i<cuvant.length();i++)
    {
        while(coada.size())
        {
            stareCurenta = coada.front();
            coada.pop();
            delta(stareCurenta,cuvant[i],nou);
        }   //while
        ///punem ce avem in noua coada in cea originala
        while(nou.size())
        {
            coada.push(nou.front());
            nou.pop();
        }
    }   //for
    while(coada.size())
    {
        int stare = coada.front();
        coada.pop();
        if(stariFinale[stare])
            return 1;
    }
    return 0;
}

int main()
{
    cout << "Hello world!" << endl;
    ifstream f("AFN.in");
    ofstream iesire("AFN.out");
	citire_imput(f);
    afisare_info();
	afisare_matrice(matrice,nrStari);
	string cuvant;
    int n;
    f>>n;
    f.get();
    while(f>>cuvant)    // getline(f,cuvant)
    {
		int rezultat = AFN(cuvant);
        cout<<cuvant<<": "<<rezultat<<endl;
		//pe linia i re pune rezultatul cuvantului i in fisier
		iesire<<rezultat<<endl;
    }
	f.close();
	iesire.close();
    return 0;
}
