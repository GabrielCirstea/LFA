#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <set>
using namespace std;

#define VEC_SIZE 40     ///pt alocarea statica
#define forit(lista,it) for(auto it = lista.begin();it!=lista.end();it++)
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
void afisare_matrice(list<int> matrice[VEC_SIZE][VEC_SIZE], int dimMatrice)
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

list<int>& lambda_inchidere(int nod, char *vizitat)
{
    vizitat[nod] = 1;               ///visitam nodul curent
    list<int> &inchiderea = *new list<int>;		// poate ca cineva o sa dea si delete
    inchiderea.push_back(nod);      ///adaugam in lista nodul curent
    int lambdaI = alfabet.find('\\'); //indicele pt lambda
    forit(matrice[nod][lambdaI], it)
    {
        if(!vizitat[*it])
        {
            list<int> lista = lambda_inchidere(*it,vizitat);     ///calculam lista pt nodul viitor
            inchiderea.insert(inchiderea.end(),lista.begin(),lista.end());  ///o adaugam la lista curenta
        }
    }
    return inchiderea;
}
void delta(int stare, char c, set<int>& multime)       ///adauga starile in multime
{
    forit(matrice[stare][alfabet.find(c,0)],t)
    {
        multime.insert(*t);
    }
}
int compMultimi(set<int> multime, set<int> multime2)
{//verifica daca multimile sunt egale.
  forit(multime,it)
    if(!multime2.count(*it))
      return 0;
  return 1;
}

//informatiile AFD-ului obtinut
int stariAFD = 0;
int finaleAFD[VEC_SIZE]={0};
int matriceAFD[VEC_SIZE][VEC_SIZE]={{0}};

void toAFD()
{
  // cum apucam noi problema?
  // plecam din 0
  // adaugam in coada starile in care ajungem din inchiderea starii
  for(int i=0;i<VEC_SIZE;i++)
    for(int j=0;j<VEC_SIZE;j++)
      matriceAFD[i][j]=-1;
  set<int> multimiAFD[VEC_SIZE];  //noile stari pt AFD
  int nrMultimi=1, indexStare=0;
  multimiAFD[0] = set<int>({0});
  list<int> inchidere[VEC_SIZE];
  for(int i=0;i<=nrStari;i++)
    {
      char vizitat[VEC_SIZE]={0};
      inchidere[i]=lambda_inchidere(i,vizitat);
    }
  //afisare inchideri
  {
	  cout<<"Lambda inchiderile:\n";
	  for(int i=0;i<=nrStari;i++)
	  {
		  cout<<i<<": ";
		  forit(inchidere[i],it)
			  cout<<*it<<" ";
		  cout<<endl;
	  }
  }
  queue<set<int> > coada;
  coada.push(set<int>({0}));
  while(!coada.empty())
    {
      set<int> lista = coada.front();
      coada.pop();
      for(int c=0;alfabet[c]&&alfabet[c]!='\\';c++)
        {// pentru fiecare litera
          set<int> nou;
          forit(lista,it)
            {
              forit(inchidere[*it],t)
                delta(*t,alfabet[c],nou);
            }
          //cautam multimea in multimile noastre
          for(int i=0;i<nrMultimi;i++)
            {
              if(compMultimi(multimiAFD[i], nou))
                {
                  matriceAFD[indexStare][c] = i;
                  break;
                }
            }
          if(matriceAFD[indexStare][c]<0)
            {//inseamna ca multimea nu e in lista noastra
              if(nou.empty())
                break;
              multimiAFD[nrMultimi] = nou;
              matriceAFD[indexStare][c] = nrMultimi;
              nrMultimi++;
              //cout<<"nrMultimi "<<nrMultimi<<endl;
              coada.push(nou);
            }
        }// for litera;
      //dupa ce terminam litere trecem pe urmatoarea linie
      indexStare++;
      //cout<<"indexStare "<<indexStare<<endl;
    }// while coada
  stariAFD = indexStare-1;
  for(int i=0;i<stariAFD+1;i++)
    {
      forit(multimiAFD[i],it)
        if(stariFinale[*it]) //daca in mutime se afla o stare finala
          finaleAFD[i]=1;    //atunic multimea devine stare finala
    }
}

void scrieAFD(ostream &out)
{
  out<<stariAFD<<endl;
  for(int i=0;i<stariAFD;i++)
    out<<finaleAFD[i]<<" "; // problema: lasa un spatiu la sfarsit
  out<<finaleAFD[stariAFD]<<endl;	//ca sa nu mai avem " "(spatiu) la final
  alfabet.erase(alfabet.end()-1); //stergem '\\'
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
int AFD(string cuvant)
{
    unsigned int i = 0;
    int stareCurenta = 0;
    for(i=0;cuvant[i];i++)
	{
        stareCurenta = matriceAFD[stareCurenta][alfabet.find(cuvant[i])];
        if(stareCurenta < 0)
            break;
    }
    if(finaleAFD[stareCurenta])
        return 1;
    return 0;
}
int main()
{
  cout<<"Hello World!\n";
  ifstream fisier("date.in");
  citire_fisier(fisier);
  ///pt afisare
  afisare();  ///afisarea datelor citite din fisier
  afisare_matrice(matrice, nrStari+1);
  toAFD();
  ofstream F("iesire.out");
  scrieAFD(F);
  int nrCuv;
  fisier>>nrCuv;
  for(int i=0;i<nrCuv;i++)
  {
	string cuvant;
	fisier>>cuvant;
	F<<AFD(cuvant)<<endl;
  }
  fisier.close();
  F.close();
  return 0;
}
