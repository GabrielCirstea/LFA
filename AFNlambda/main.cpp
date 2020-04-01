#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
using namespace std;

#define VEC_SIZE 20     ///pt alocarea statica
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
    for(int i=0;i<=nrStari;i++)
    {
        f>>stariFinale[i];
    }
    EMP_BUF(f);
    getline(f,alfabet);
    alfabet+='\\';      ///lambda este '\'
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

list<int>& lambda_inchidere(int nod, char *vizitat)
{
    vizitat[nod] = 1;               ///visitam nodul curent
    list<int> &inchiderea = *new list<int>;
    inchiderea.push_back(nod);      ///adaugam in lista nodul curent
    forit(matrice[nod][alfabet.find('\\',0)], t)
    {
        if(!vizitat[*t])
        {
            list<int> lista = lambda_inchidere(*t,vizitat);     ///calculam lista pt nodul viitor
            inchiderea.insert(inchiderea.end(),lista.begin(),lista.end());  ///o adaugam la lista curenta
        }
    }
    return inchiderea;
}
void delta(int stare, char c, queue<int>& coada)       ///adauga starile in coada
{
    forit(matrice[stare][alfabet.find(c,0)],t)
    {
        coada.push(*t);
    }
}
int AFNl(string cuvant)
{
    list<int> v[VEC_SIZE];
    for(int i=0;i<nrStari+1;i++)
   {
       char vizitat[VEC_SIZE] = {0};
       v[i] = lambda_inchidere(i,vizitat);
   }
   ///bun, avem inchiderile
   queue<int> coada, nou;
    coada.push(0);      ///suntem la inceputul procesarii cuvantului
    int stareCurenta;
    for(int i=0;i<cuvant.length();i++)
    {
        while(coada.size())
        {
            stareCurenta = coada.front();
            coada.pop();
            forit(v[stareCurenta],t)///pt fiecare stare plecam cu caracter din inchiderea ei
                delta(*t,cuvant[i],nou);
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

    return 0;   //ca nu merge
}

int main()
{
    cout << "Hello world!" << endl;
    ifstream f("date1.in");
    ofstream F("date.out");
    citire_fisier(f);
    ///pt afisare
    afisare();  ///afisarea datelor citite din fisier
    afisare_matrice(matrice, nrStari+1);
    int nrCuvinte;
    string cuvant;
    f>>nrCuvinte;
    f.get();
    EMP_BUF(f);
    for(int i=0;i<nrCuvinte;i++)
    {
        getline(f,cuvant);
		int rezultat = AFNl(cuvant);
        //afisare in fisier indicele cuvantului - rezultatul automatului
        F<<rezultat<<endl;
        //pentru afisare pe ecran
        cout<<cuvant<<": "<<rezultat<<endl;
    }
    f.close();
	F.close();
    return 0;
}
