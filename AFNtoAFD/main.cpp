//trecerea de la AFN la AFD
//citim AFN-ul si trebuie sa creem noi stari
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
using namespace std;
#define forit(it,lista) for(list<int>::iterator it=lista.begin();it!=lista.end();it++)
#define LOG(X) cout<<#X<<" "<<X<<endl;
// pt AFN
int nrStari, stariFinale[20];
string alfabet;
/// adiacente alfabet stari
list<int> matrice[20][20];
int dimMatrice;
int nrCuv;

void afisare_matrice(list<int> matrice[20][20],int dimMatrice)      ///afisarea pt AFN
{
    cout<<"    ";
    for(int i = 0;alfabet[i];i++)
        cout<<alfabet[i]<<"  ";
    cout<<endl;
    for(int i = 0;i<dimMatrice;i++)
    {
        cout<<i<<":";
        for(int j = 0;alfabet[j];j++)
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
    cout<<"nrStari = "<<nrStari<<endl;
    fisier.get();
    //fisier>>nrStariFinale;
    for(int i=0;i<=nrStari;i++)
        fisier>>stariFinale[i];
    fisier.get();  // de 2 ori pt linux probleme cu \r\n
    getline(fisier,alfabet);
    cout<<"alfabet:"<<alfabet<<endl;
    fisier>>dimMatrice;
    cout<<"Stari Finale ";
    for(int i=0;i<nrStari+1;i++)
    {
        cout<<stariFinale[i]<<" ";
    }
    cout<<endl;
    cout<<"dim:"<<dimMatrice<<endl;
    for(int i = 0;i<dimMatrice;i++){
        char litera;
        int sursa,dest;
        fisier>>litera;
        fisier>>sursa;
        fisier>>dest;
        matrice[sursa][alfabet.find(litera,0)].push_back(dest);
    }
    dimMatrice = nrStari+1;
    afisare_matrice(matrice,dimMatrice);
}
void delta(int stare, char c,list<int> &lista)
{
  forit(it,matrice[stare][alfabet.find(c)])
    lista.push_back(*it);
}
int comparareStare(list<int> &stare, list<int> &tranzitii)
{
  //stare.sort(); //vedem cum facem mai eficient
  if(stare.size() != tranzitii.size())
    return 0;
  forit(it,stare)
        {
          bool ok = false;
          forit(it2,tranzitii)
            if(*it == *it2)
              ok = true;
          if(!ok)
            return 0;
        }
  return 1;
}
// pt AFD
  int stariAFD = 0;
  int finaleAFD[20]={0};  // starile finale AFD
  //va fi acelas alfabet
  int matriceAFD[20][20] = {{0}};
void toAFD()
{

  list<int> tranzitiiAFD[20];
  int nrTranzitii = 1, indiceStare = 0;
  tranzitiiAFD[0].push_back(0);
  queue<list<int> > coada;
  coada.push(tranzitiiAFD[0]);
  while(!coada.empty())
    {
      list<int> stareCurenta = coada.front();
      coada.pop();
      for(int c=0;alfabet[c];c++)
        {
          list<int> nou;
          forit(it,stareCurenta)
            {
              delta(*it,alfabet[c],nou);
            }
          //cautam starea in cele inregistrate
          for(int i=0;i<nrTranzitii;i++)
            {
              if(comparareStare(nou,tranzitiiAFD[i]))
                {// daca exista deja starea o punem in matrice
                  //daca lista e goala, atunci nu avem tranzitie
                  if(tranzitiiAFD[i].empty())
                    matriceAFD[indiceStare][c] = -1;
                  else
                    matriceAFD[indiceStare][c]=i;
                  break;
                }
            }
          if(!matriceAFD[indiceStare][c])
            {
              // creem o noua stare in vectorul de stari
              forit(it,nou)
                tranzitiiAFD[nrTranzitii].push_back(*it);
              // daca lista e goala, atunci nu avem tranzitie
              if(tranzitiiAFD[nrTranzitii].empty())
                matriceAFD[indiceStare][c] = -1;
              else
                matriceAFD[indiceStare][c] = nrTranzitii;
              nrTranzitii++;
              // ar trebui sa bagam nou in coada
              //if(!nou.empty())
              coada.push(nou);  // bagam si campurile goale
                                // ca sa fie
            }
        }// for alfabet
      indiceStare++; // trecem la stara urmatoare;
    }// while coada
  stariAFD = indiceStare-1;
  // vectorul de stari finale
  for(int i=0;i<nrTranzitii;i++)
    {
      forit(it,tranzitiiAFD[i])
        {
          if(stariFinale[*it])
            finaleAFD[i] = 1;
        }
    }
  cout<<"Tranzitii\n";
  for(int i=0;i<stariAFD;i++)
    {
      cout<<i<<":";
      for(int j=0;alfabet[j];j++)
        cout<<matriceAFD[i][j]<<" ";
      cout<<endl;
    }
  cout<<"Stari finale AFD: ";
  for(int i=0;i<stariAFD+1;i++)
    cout<<finaleAFD[i]<<" ";
  cout<<endl;
}
void scrieAFD(ostream &out)
{
  out<<stariAFD<<endl;
  for(int i=0;i<stariAFD+1;i++)
    out<<finaleAFD[i]<<" "; // problema: lasa un spatiu la sfarsit
  out<<endl;
  out<<alfabet<<endl;
  // alfabet.size() * nr_de_stari daca ar fi complet
  // din asta scadem campurile == -1 din matrice
  int nrTranzitii = alfabet.size() * (stariAFD+1);
  for(int i=0;i<stariAFD+1;i++)
    {
      for(int j=0;alfabet[j];j++)
        {
          if(matriceAFD[i][j]<0)
            nrTranzitii--;
        }
    }
  out<<nrTranzitii<<endl;
  for(int i=0;i<stariAFD+1;i++)
    {
      for(int j=0;alfabet[j];j++)
        {
          if(matriceAFD[i][j]>-1)
            out<<alfabet[j]<<" "<<i<<" "<<matriceAFD[i][j]<<endl;
        }
    }
}
int main()
{
    cout<<"Hello Word!\n";
    ifstream fisier("date.in");
    citire_imput(fisier);
    toAFD();
    ofstream o("date.out");
    scrieAFD(o);
    fisier.close();
    o.close();
    return 0;
}
