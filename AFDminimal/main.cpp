#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

#define VEC_SIZE 20     ///pt alocarea statica
#define forit(it,lista) for(list<int>::iterator it=lista.begin();it!=lista.end();it++)
int nrStari;
int stariFinale[VEC_SIZE];
string alfabet;
int matrice[VEC_SIZE][VEC_SIZE];
//-----
//pentru AFD-ul minimal
int stariMIN, finaleMIN[VEC_SIZE];
int matriceMIN[VEC_SIZE][VEC_SIZE];
void afisare()
{///afisarea datelor cititea din fisier
    cout<<"NrStari: "<<nrStari<<endl;
    cout<<"Alfabet: "<<alfabet<<endl;
    cout<<"Stari finale: ";
    for(int i=0;i<=nrStari;i++)
        cout<<stariFinale[i]<<" ";
    cout<<endl;
}
void afisare_matrice(int matrice[20][20],int dimMatrice, int col)      ///afisarea pt AFD
{
    cout<<"   ";
    for(unsigned int i = 0;i<alfabet.length();i++)
        cout<<alfabet[i]<<" ";
    cout<<endl;
    for(int i = 0;i<dimMatrice;i++)
    {
        cout<<i<<":";
        for(int j = 0;j<col;j++)
        {
            cout<<matrice[i][j]<<" ";
        }
        cout<<endl;
    }
}
void initMatrice(int matrice[VEC_SIZE][VEC_SIZE],int n)
{
  for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
        matrice[i][j] = -1;
    }
}
void citire_fisier(ifstream &f)
{
    f>>nrStari;
    f.get();
    initMatrice(matrice,nrStari+1);
    getline(f,alfabet);
    //citire stari finale
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
        matrice[sursa][alfabet.find(litera,0)] = dest;
    }
    ///pt afisare
    afisare();  ///afisarea datelor citite din fisier
    afisare_matrice(matrice, nrStari+1,alfabet.size());
}
int delta(int stare, char c)
{
    return matrice[stare][alfabet.find(c,0)];
}
int verificareStare(int stare, int X[VEC_SIZE][VEC_SIZE])
{//ne zice daca starea este echivalenta cu alte stari
  for(int i=0;i<nrStari;i++)
    {
      if( i!=stare && X[stare][i]==0)
        return 1;
    }
  return 0;
}
void renotare(int X[VEC_SIZE][VEC_SIZE],int notare[VEC_SIZE])
{
  for(int i=0;i<nrStari+1;i++)
    //initiem vectorul cu -1, adica valori goale
    notare[i] = -1;
  cout<<"Acum, o sa luam starile pe rand si o sa vedem daca au stari echivalente\n";
  cout<<"Vom face o renotare, fiecare stare v-a avea un corespondent in AFD-ul minimal\n";
  cout<<"Starile echivalente vor avea acelas corespondent.\n";
  int indiceStare = 0;
  for(int i=0;i<nrStari+1;i++)
    {//pentru fiecare stare nenotata verificam daca are stari echivalente
      if(notare[i]<0)
        {
          notare[i] = indiceStare;
		  cout<<"Corespondentul lui "<<i<<" este "<<indiceStare<<endl;
          for(int j=i+1;j<nrStari;j++)
          {//trecem toate starile echivalente ca aceeasi stare in noul AFD
            if(!X[i][j])
			{
			  notare[j] = indiceStare;
			  cout<<j<<" este echivalent cu el\n";
			}
          }
          indiceStare++; // trecem la starea urmatoare
        }
    }
  stariMIN = indiceStare-1;   //Asta va fi noul nr de stari
}

void populareMIN(int notare[VEC_SIZE])
{
  for(int i=0;i<nrStari+1;i++)
    {
      for(int c = 0;alfabet[c];c++)
        {
          int src = notare[i];                // luam starea renotata pt AFD minimal
          int dest = delta(i,alfabet[c]);   //destinatia normala
          //nu luam tranzitiile cu alte stari care se unesc cu asta
          //putem pastra tranzitiile cu starea inseasi x - x
          //daca avem tranzitie cu starea insasi
          //sau nu este tranzitie cu o stare cu care se uneste
          if(dest == i || notare[dest] != src)
            //trecem in matri starea renotata
            matriceMIN[src][c] = notare[dest];
        }
    }
}
void setareFinale(int notare[VEC_SIZE])
{//seteaza starile finale ale AFD-ului minimal
  for(int i = 0;i<nrStari+1;i++)
    {
      if(stariFinale[i])
        finaleMIN[notare[i]] = 1;
    }
}
int minimizare()
{
    ///avem matricea si alfabetul
    int X[VEC_SIZE][VEC_SIZE]={{0}};
    for(int i=0;i<nrStari+1;i++)
    {
        for(int j=i;j<nrStari+1;j++)
        {
            if(stariFinale[i] != stariFinale[j])
                X[i][j] = 1,X[j][i] =1;
            else
                X[i][j] = 0,X[j][i] = 0;
        }
    }
	cout<<"Matricea de echivalenta la primul pas\n";
    afisare_matrice(X,nrStari+1,nrStari+1);
	cout<<"Acutm cautam combinatii de stari echivalente care au tranzitii in stari ne-echivalente...\n";
    bool changed;
    do
    {
        changed = false;
        for(int i=0;i<nrStari+1;i++)
        {
            for(int j=i+1;j<nrStari+1;j++)
            {
                if(!X[i][j])
                {//verificam daca din starile i si j ajunge in stari ne echiv
                    for(int k=0;alfabet[k];k++)
                    {
                        if(X[delta(i,alfabet[k])][delta(j,alfabet[k])])
                        {
                            X[i][j] = 1;
                            X[j][i] = 1;
                            changed = true;
							cout<<"Am gasit ("<<i<<","<<j<<") ";
							cout<<"care merg cu "<<alfabet[k]<<" in ";
							cout<<delta(i,alfabet[k])<<","<<delta(j,alfabet[k]);
							cout<<"\n";
                        }
                    }
                }
            }// for
        }// for
    }while(changed);
    cout<<"Matrice echivalenta:\n";
    afisare_matrice(X,nrStari+1,nrStari+1);

    // o sa renotam starile, cu noi indici
    //inclusiv starile pe care le unim
    //cand facem o tranzitie din starea x in y
    //il cautam pe y in noua renotare a starilor
    int notare[VEC_SIZE];
    renotare(X,notare);
    if(nrStari == stariMIN)
      {
        cout<<"Nu poate fi minimizat!\n";
        return 0;
      }
    cout<<"Renotarile starilor:\n";
    for(int i=0;i<nrStari+1;i++)
      {
        cout<<i<<": "<<notare[i]<<endl;
      }
    populareMIN(notare);
    setareFinale(notare);

    return 1; // poate fi minimizat
}
void scrieAFD(ostream &out)
{
  out<<stariMIN<<endl;
  out<<alfabet<<endl;
  for(int i=0;i<stariMIN;i++)
    out<<finaleMIN[i]<<" "; // problema: lasa un spatiu la sfarsit
  out<<finaleMIN[stariMIN];	//se pune ultimul elemente, apoi \n
  out<<endl;
  // alfabet.size() * nr_de_stari daca ar fi complet
  // din asta scadem campurile == -1 din matrice
  int nrTranzitii = alfabet.size() * (stariMIN+1);
  for(int i=0;i<stariMIN+1;i++)
    {
      for(int j=0;alfabet[j];j++)
        {
          if(matriceMIN[i][j]<0)
            nrTranzitii--;
        }
    }
  out<<nrTranzitii<<endl;
  for(int i=0;i<stariMIN+1;i++)
    {
      for(int j=0;alfabet[j];j++)
        {
          if(matriceMIN[i][j]>-1)
            out<<alfabet[j]<<" "<<i<<" "<<matriceMIN[i][j]<<endl;
        }
    }
}
int AFDcomplet(int nrStari, int matrice[VEC_SIZE][VEC_SIZE],string alfabet)
{//verifica daca AFD-ul este complet
  for(int i = 0;i<nrStari+1;i++)
    {
      for(int j=0;j<alfabet[j];j++)
        if(matrice[i][j]<0)
          return 0;
    }
  return 1;
}
int main()
{
    cout << "Hello world!" << endl;
    ifstream f("date.in");
    ofstream F("iesire.out");
    ostream& out = F;
    citire_fisier(f);
    if(!AFDcomplet(nrStari,matrice,alfabet))
      {
        out<<"Nu e complet!\n;";
        return 0;
      }
    if(!minimizare())
      {
        out<<"NU!\n";
        return 0;
      }
    cout<<"Matrice adiacenta AFD minimal\n";
    afisare_matrice(matriceMIN,stariMIN+1,alfabet.size());
    scrieAFD(out);
    f.close();
    F.close();
    return 0;
}
