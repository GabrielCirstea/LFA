#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define VEC_SIZE 40
#define LAMBDA 'l'
#define LOG(x) cout<<#x<<" "<<x<<endl;
string E[VEC_SIZE]; // expresiile dintre pipe-uri
string REZ[VEC_SIZE];
int nREZ;
int nE = 0;
struct node{
  char s;
  int simbol;
  node(char s,int sim=0)
  {
    this->s = s;
    simbol = sim;
  }
};
ostream& operator<<(ostream& out, node& o)
{
  out<<"\t"<<o.s<<"--"<<o.simbol<<endl;
  return out;
}
vector<node> Noduri[VEC_SIZE];


void removeWhiteSpaces(string& s)
{//eliminam spatiile de la inceputul si sfarsitul expresiei
  int n = -1;
  while(s[++n] == ' ');
  s.erase(0,n);
  string::iterator it = s.end()-1;
  while((*it)==' ') it--;
  s.erase(it+1,s.end());
}
void parsare(const string& expresie)
{
  int start, to = -1;
  int i = 0;
  do
    {
      start = to + 1;  // vrem sa sarim peste pipe-ul curent
      to = expresie.find("|",start+1);
      E[i++] = expresie.substr(start,to-start);
    }while(to != string::npos);
  nE = i;
  for(int i=0;i<nE;i++)
    removeWhiteSpaces(E[i]);
}
void initNodes()
{
  for(int i=0;i<nE;i++)
    {
      Noduri[i].reserve(VEC_SIZE); // rezervam spatiu pt vector
    }
}
void getNodes()
{
  initNodes();
  for(int i=0;i<nE;i++)
    {
      int cursor = 0;
      for(char e:E[i])
        {
          if(e=='*')
            {
              if(cursor==0)
                {
                  cout<<"Eroare: simbol la inceput\n";
                  return;
                }
              Noduri[i][cursor-1].simbol = 1;
            }
          else
            {
              if(e == '+')
                {
                  if(cursor==0)
                    {
                      cout<<"Eroare: simbol la inceput\n";
                      return;
                    }
                  Noduri[i][cursor-1].simbol = 2;
                }
              else
                {// e litera
                  Noduri[i].emplace_back(e);  // daca e vector trebuie adaugate.
                  // daca era array simplu mergea prin adresare cu index
                  cursor++;
                }
            }
        }
    }
}
string getTranzitie(int start, char s, int end)
{
  string rez = to_string(start);
  rez += " - ";
  rez += s;
  rez += " - ";
  rez += to_string(end);
  return rez;
}
void showAFN(vector<node> e[VEC_SIZE], int n)
{
  //avem 2 stari
  // 0 stare initiala, 1 - stare finala
  int S = 2;
  for(int i=0;i<n;i++)
    {
      int cursor = 0;
      for(node& o:e[i])
        {
          switch(o.simbol)
            {
            case 0:
              {
                REZ[nREZ++]=getTranzitie(cursor,o.s,S);
                cursor = S;
                S++;
              }break;
            case 1:
              {
                REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
                REZ[nREZ++]=getTranzitie(S,o.s,S);
                cursor = S;
                S++;
              }break;
            case 2:
              {
                REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
                cursor = S;
                S++;
                REZ[nREZ++]=getTranzitie(cursor,o.s,S);
                REZ[nREZ++]=getTranzitie(S,LAMBDA,cursor);
                cursor = S;
                S++;
              }break;
            }
        }
      // legaturi cu starea finala
      REZ[nREZ++]=getTranzitie(cursor,LAMBDA,1);
    }
}
void afisare(ostream& out)
{
  out<<nREZ<<endl;
  for(int i=0;i<nREZ;i++)
    {
      out<<REZ[i]<<endl;
    }
  // starea finala
  out<<1<<endl;
}
int main()
{
  cout<<"Salutare!\n";
  ifstream f("regexeasy.in");
  ofstream F("regexeasy.out");
  string exp;
  while(getline(f,exp))
    {
      nREZ = 0;
      //cout<<exp<<endl;
      //cout<<"----------\n";
      parsare(exp);
      getNodes();
      showAFN(Noduri,nE);
      afisare(F);
      //cout<<"...........\n";
    }
  return 0;
}
