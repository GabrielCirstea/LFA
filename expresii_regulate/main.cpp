#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
#define VEC_SIZE 40
#define LAMBDA 'l'
#define LOG(x) cout<<#x<<" "<<x<<endl;
int S = 1;	// numarul de stari si ultima stare scris in automat
int cursor = 0;
string REZ[VEC_SIZE]; // tranzitiile
int nREZ;  // nr de tranziiti

string getTranzitie(int start, char s, int end)
{
  string rez = to_string(start);
  rez += " - ";
  rez += s;
  rez += " - ";
  rez += to_string(end);
  return rez;
}
void removeWhiteSpaces(string& s)
{//eliminam spatiile de la inceputul si sfarsitul expresiei
  int n = -1;
  while(s[++n] == ' ');
  s.erase(0,n);
  string::iterator it = s.end()-1;
  while((*it)==' ') it--;
  s.erase(it+1,s.end());
}
int verificare_paranteze(string& expresie)
{
	int paranteze = 0;
	for(char c:expresie)
	{
		if(c == '(')
			paranteze++;
		if(c == ')')
			paranteze--;
		if(paranteze<0)
			return 0;	// nu e bine
	}
	if(!paranteze)
		return 1;	//e bine
	return 0;
}
int paranteze_redundante(string& expresie, int pos)
{// cauta paranteze redundate si le sterge
	for(int i=pos;i<expresie.size();i++)
	{
		if(expresie[i] == '(')
		{
			i = paranteze_redundante(expresie,i+1);
		}
		else if(expresie[i] == ')')
		{
			int beg = (pos-1) > 0 ? (pos-1) : 0;	// trebuie ster la pos-1
			if(i == expresie.size()-1)
			{// e pe ultima pozitie
				expresie.erase(i);
				expresie.erase(beg,1);
				//expresie[beg] = ' ';	// erase la sfarsit nu merge dupa erase-ul de mai devreme.
			}
			else if(expresie[i+1]!='*' && expresie[i+1]!='+')	// stergem parantezele
			{
				expresie.erase(i,1);
				expresie.erase(beg,1);
				//expresie[beg] = ' ';
			}
			return i+1;
		}
	}
	return 0;
}
long unsigned int split_pipe(const string& expresie, int start=0)
{
	int paranteze = 0;
	int n = expresie.size();
	for(int i=start;i<n;i++)
	{
		if(expresie[i] == '(')
			paranteze++;
		if(expresie[i] == ')')
			paranteze--;
		if(expresie[i] == '|')
		{
			if(!paranteze)
				return i;
		}
	}
	return string::npos;
}
int search_simbol(const string& exp, int start)
{// cautam seimbolul pt paranteza curenta
	if(exp[start]!='(')
	{	// cazul in care e caracter
		if(start == exp.size()-1)
			return 0;
		if(exp[start+1] == '*')
			return 1;
		if(exp[start+1] == '+')
			return 2;
		return 0;
	}
	int n=exp.size(),i, paranteze = 0;
	for(i=start;i<n;i++)
	{
		if(exp[i] == '(')
			paranteze++;
		if(exp[i]==')')
		{
			paranteze--;
			if(!paranteze)
				break;
		}
	}
	if(i!=n)
	{// cauta simbolul dincolo de spatiile goale
		for(;i<n;i++)
		{
			if(exp[i] == '*')
				return 1;
			if(exp[i] == '+')
				return 2;
		}
	}
	return 0;
}
string get_substr(string& exp,int start)
{
	if(exp[start]!='(')
		return "";
	int n=exp.size(),i, paranteze = 0;
	for(i=start;i<n;i++)
	{
		if(exp[i] == '(')
			paranteze++;
		if(exp[i]==')')
		{
			paranteze--;
			if(!paranteze)
				break;
		}
	}
	return exp.substr(start,i-start+1);
}
void afisare_bucati(string& expresie,int);
void sparge(string expresie, int cursor)
{
  removeWhiteSpaces(expresie);
	int n=expresie.size();
	for(int i=0;i<n;i++)
	{
		if(expresie[i]!='(')	// trebuie sa punem si simbolurile
		{
			int simbol = search_simbol(expresie,i);
			switch(simbol)
			{
				case 1:
					{
            REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
            REZ[nREZ++]=getTranzitie(S,expresie[i],S);
						cursor = S;
						S++;
					}break;
				case 2:
					{
            REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
						cursor = S;
						S++;
            REZ[nREZ++]=getTranzitie(cursor,expresie[i],S);
            REZ[nREZ++]=getTranzitie(S,LAMBDA,cursor);
						cursor = S;
						S++;
					}break;
				case 0:
					{
            REZ[nREZ++]=getTranzitie(cursor,expresie[i],S);
						cursor = S;
						S++;
					}break;
			}
			if(simbol) i++;	// daca are simbol, vom sari peste simbol
			//	sa nu afisam simbolul la urmatoarea iteratie
		}
		else
		{
			int simbol = search_simbol(expresie,i);
			string next = get_substr(expresie,i);
			i+= next.size();	// avansam dincolo de paranteza
			//LOG(next);
			//cin.get();
			switch(simbol)
			{
				case 1:
					{
            REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
						cursor = S++;
						afisare_bucati(next,cursor);
            REZ[nREZ++]=getTranzitie(S-1,LAMBDA,cursor);
            REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
					}break;
				case 2:
					{
            REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
						cursor = S++;
						afisare_bucati(next,cursor);
            REZ[nREZ++]=getTranzitie(S-1,LAMBDA,cursor);
					}break;
			}
			cursor = S++;
		}
	}
}
void afisare_bucati(string& expresie, int initial=0)
{// practi functia principala
	paranteze_redundante(expresie,0);
	removeWhiteSpaces(expresie);
	int pos = -1,oldPos = pos;
	int stareComuna=0;
	// daca este pipe, atunci o sa avem o stare finala comuna
	if(split_pipe(expresie,0)!= string::npos)
		stareComuna= S++;
	do
	{
		oldPos=pos+1;
		pos = split_pipe(expresie,oldPos);
		cursor = initial;
		sparge(expresie.substr(oldPos,pos-oldPos),cursor);
		//aceeasi stari la final
		if(stareComuna)
      REZ[nREZ++]=getTranzitie(S-1,LAMBDA,stareComuna),S++;
	}while(pos!=string::npos);
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
  ifstream f("regexhard.in");
  ofstream F("regexhard.out");
  string expresie;
  while(getline(f,expresie))
    {
      nREZ = 0;
      //cout<<exp<<endl;
      //cout<<"----------\n";
      if(!verificare_paranteze(expresie))
        {
          cout<<"Paranteze incorecte\n";
          continue;
        }
      removeWhiteSpaces(expresie);
      afisare_bucati(expresie);
      afisare(F);
      //cout<<"...........\n";
    }
	return 0;
}
