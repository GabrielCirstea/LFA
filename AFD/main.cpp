#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using namespace std;
#define EMP_BUF(fisier) {\
        char c = fisier.peek();\
        while(c == '\n' || c == '\r')\
        {\
            fisier.get();\
            c = fisier.peek();\
        }\
    }       //.get(), pt golirea buff-erului, in linux nu mai e \r dar prezenta lui din windows persista
//...............................
//Formatul fisierului de intrare:
//
// nr de stari
//lista de stari finale 1 - finala, 0 - nu
//nr de adiacente
//lista de adiacente: a 0 1 de la 0 la 1 cu 'a'
//nr de cuvinte
//cuvinte
///chestiile citite pt automat
//..............................
int nrStari, stariFinale[20];
//matrice de adiacenta
int matrice[40][40] = {{-1}};
int dimMatrice;
string alfabet;
int nrCuv;

void afisare_info()
{
	cout<<"nrStari = "<<nrStari<<endl;
    cout<<"alfabet:"<<alfabet<<endl;
    cout<<"Stari finale:\n";
	for(int i=0;i<=nrStari;i++)
    {
        cout<<stariFinale[i]<<" ";
    }
    cout<<endl;
}

void afisare_matrice(int matrice[40][40], int dimMatrice)
{///afisare matrice de tranzitii
  //se afiseaza literele
    cout<<"   ";
    int size = alfabet.length();
    for(int i = 0;i<size;i++)
    {
        cout<<alfabet[i]<<"  ";
    }
    cout<<endl;
    for(int i = 0;i<dimMatrice;i++)
    {
        cout<<i<<": ";
        for(int j = 0; j<size;j++)
        {
            if(matrice[i][j])
            {
                cout<<"'"<<matrice[i][j]<<"' ";
            }
            else
                cout<<"' ' ";
        }
        cout<<endl;
    }
}

void citire_imput(ifstream& fisier)
{///citirea din fisier
    fisier>>nrStari;
    fisier.get();
    for(int i=0; i<=nrStari;i++)
        fisier>>stariFinale[i];
    EMP_BUF(fisier);
    getline(fisier,alfabet);
    fisier>>dimMatrice;
    for(int i = 0;i<dimMatrice;i++){
        char litera;
        int sursa,dest;
        fisier>>litera;
        fisier>>sursa;
        fisier>>dest;
        matrice[sursa][alfabet.find(litera,0)] = dest;
    }
    //pt afisare
    dimMatrice = nrStari+1;
}

int delta(int stare, char c)
{///functia delta
    if(matrice[stare][alfabet.find(c,0)])
        return matrice[stare][alfabet.find(c,0)];
    return -1; ///eroare
}

int AFD(string cuvant)
{
    unsigned int i = 0;
    int stareCurenta = 0;
    while(i<cuvant.length())
    {
        stareCurenta = delta(stareCurenta, cuvant[i]);
        if(stareCurenta < 0)
            break;
        i++;
    }
    if(stariFinale[stareCurenta])
        return 1;
    return 0;
}

int main()
{
    cout << "Hello world!" << endl;
    ifstream f("date.in");
    ofstream iesire("afd.out");
    citire_imput(f);
    //pentru afisarea informatiilor citite.
    afisare_info();
    afisare_matrice(matrice,dimMatrice);
    int nr_cuvinte;
    f>>nr_cuvinte;
    cout<<"nr cuvinte:"<<nr_cuvinte<<endl;
    EMP_BUF(f);
    string cuvant;
    for(int i=0;i<nr_cuvinte;i++)
    {
        getline(f,cuvant);
        EMP_BUF(f);
        int rezultat = AFD(cuvant);
        cout<<cuvant<<" "<<rezultat<<endl;
        iesire<<rezultat<<endl;
	}
	f.close();
	iesire.close();
  return 0;
}
