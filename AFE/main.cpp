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
    getline(f,alfabet);
    alfabet+='\\';      ///lambda este '\'
    for(int i=0;i<=nrStari;i++)
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
vector<string> etichete;
int matriceAFE[VEC_SIZE][VEC_SIZE];
string construieste_eticheta(int src,int target)
{
  string eticheta;
  for(int c=0;alfabet[c];c++) // cautam in fiecare tranzitie
    {
      // std::find() cauta un element in obiecte gen vector/list, care folosec iterator
      // functia returneaza un iterator la pozitia in care a gasit elementul
      //sau iterator la finalul sirului daca elementul nu a fost gasit
      list<int>::iterator it = find(matrice[src][c].begin(),matrice[src][c].end(),target);  // daca tranzitia ne duce la starea cautata
      if(it != matrice[src][c].end())
        if(alfabet[c]!='\\' || !eticheta.size())
          eticheta += alfabet[c]; // adaugam litera(tranzitia) in eticheta
    }
  sort(eticheta.begin(),eticheta.end());
  return eticheta;
}
int cauta_eticheta(string& eticheta,vector<string> &etichete)
{
  for(int k=0;k<etichete.size();k++)
    { // cautam eticheta in lista
      if(etichete[k] == eticheta)
        { // daca o avem deja nu o mai adaugam
          return k;
        }
    }
    etichete.push_back(eticheta); // daca nu am gasit eticheta o bagam in lista
    return etichete.size()-1;
}
void scrie_etichete(vector<string> &etichete)
{
  init_matrice(matriceAFE,nrStari,nrStari,-1);
  for(int i=0; i<nrStari+1; i++)
    {
      for(int j=0; j<nrStari+1; j++)
        {
          string eticheta = construieste_eticheta(i,j);
          matriceAFE[i][j] = cauta_eticheta(eticheta,etichete);
        }
    }
}
//cautam si setam noua stare finala

void afisare_etichete(vector<string> &etichete)
{
  int i = 0;
  for(string s:etichete)
    {
      cout<<i++<<": "<<s<<endl;
    }
}
void afisare_AFE(int matriceAFE[VEC_SIZE][VEC_SIZE],int dim)
{// e o matrice patratica
  cout<<"----------\n"<<"Matreice AFE\n";
  cout<<"  ";
  for(int i=0;i<dim;i++)
    {
      cout<<i<<" ";
    }
  cout<<endl;
  for(int i=0;i<dim;i++)
    {
      cout<<i<<":";
      for(int j=0;j<dim;j++)
        {
          cout<<matriceAFE[i][j]<<" ";
        }
      cout<<endl;
    }
}
int main()
{
  cout<<"Salutare!\n";
  ifstream f("date.in");
  citire_fisier(f);
  afisare();
  afisare_matrice(matrice,nrStari+1);
  scrie_etichete(etichete);
  afisare_etichete(etichete);
  afisare_AFE(matriceAFE, nrStari+1);
  return 0;
}
