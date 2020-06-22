#include <iostream>
#include <fstream>

using namespace std;
#define LOG(x) cout<<#x<<": "<<x<<endl
#define VEC_SIZE 40
#define LAMBDA 'l'
int S,cursor, lastComun;
string REZ[VEC_SIZE];
int nREZ;

string getTranzitie(int start, char s, int end)
{
  string rez = to_string(start);
  rez += " - ";
  rez += s;
  rez += " - ";
  rez += to_string(end);
  return rez;
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

void removeWhiteSpaces(string& s)
{//eliminam spatiile de la inceputul si sfarsitul expresiei
  int n = -1;
  while(s[++n] == ' ');
  s.erase(0,n);
  string::iterator it = s.end()-1;
  while((*it)==' ') it--;
  s.erase(it+1,s.end());
}

int skip_space(const string& expresie,int start=0)
{
	while(expresie[start] == ' ') // \0 != ' '
		start++;
	return start;
}

int map_simbol(char s)
{
	switch(s)
	{
		case '*':
			return 1;
		case '+':
			return 2;
		default:
			return 0;
	}
}

int get_simbol(const string& expresie, int start = 0)
{	// returneaza indexul simbolului fata de start
	if(expresie[start]=='(')
	{
		int paranteze = 0;
		for(int i=start, n=expresie.size();i<n;i++)
		{	//mergem pana la inchiderea parantezei
			if(expresie[i] == '(')
				paranteze++;
			if(expresie[i] == ')')
			{
				paranteze--;
				if(!paranteze)
				{
					i = skip_space(expresie,i+1);
					// sarim peste spatiile libere
					return i;
				}//if
			}//if
		}//for
	}
	else
	{
		start = skip_space(expresie,start+1);
		return start;
	}
	return 0;
}

char look_before(const string& expresie, int begin)
{// returneaza primul caracter diferit de spatiu
	if(begin<0)
		return '(';
	while(begin && expresie[begin] == ' ')
		begin--;
	return expresie[begin];
}

int find_pipe(const string& exp, int start=0)
{
	int paranteze =0;
	for(int i=start;exp[i];i++)
	{
		if(exp[i] == '(')
			paranteze++;
		if(exp[i] == ')')
		{
			paranteze--;
		}
		if(exp[i] == '|')
		{
			if(!paranteze)
				return i;
		}
	}
	return -1;
}

int paranteze_redundante(string& expresie,int start=0)
{
	// eliminam parantezele cand in interiorul lor nu se afla un pipe
	// cand nu sunt urmate de un simbol * sau +
	int pipe = 0;
	for(int i=start;i<expresie.size();i++)
	{
		if(expresie[i] == '(')
		{
			i = paranteze_redundante(expresie,i+1);
		}
		else
		{
			if(expresie[i] == ')')
			{
				//a(a|b)
				//((a|b))
				pipe = find_pipe(expresie,start);
				if(pipe != -1 && pipe<i) 		// daca pipe-ul se afla in paranteza asta
					pipe = 1;
				else
					pipe = 0;
				// daca avem pipe si este langa alte expresii
				// ex: a(a|b)
				if(pipe)
				{
					if(!(look_before(expresie,start-2)=='(' && 
						(expresie[skip_space(expresie,i+1)] == ')' ||
						 i == expresie.size()-1)))
					{
						return i;
					}
				}
				char simbol = expresie[skip_space(expresie,i+1)];
				if(map_simbol(simbol) && i-start > 1) 	// daca paranteza e urmata de un simbol
					return i;
				// daca am ajuns pana aici
				// inseamna ca paranteza poate fi stearsa
				{
					// daca inainte de paranteza noastra avem (
					// si dupa paranteza inchisa avem tot ) atunci putem sterge parantezele
					int beg = start-1 > 0 ? start-1 : 0;
					//eliminam parantezele
					expresie.erase(i,1);
					expresie.erase(beg,1);
					i-=2;	// am sters 2 caractere, ne intoarcem 2 caractere
				}
				return i;
			}
		}
	}
	return 0;
}

void sparge(string& expresie, int initial);
void do_simbol(string& expresie, int simbol)
{
	int crs = cursor;		// un cursor local
	switch(simbol)
	{
		case 1:
			{
				REZ[nREZ++]=getTranzitie(crs,LAMBDA,S);
				crs = S++;
				sparge(expresie,crs);
				REZ[nREZ++]=getTranzitie(S-1,LAMBDA,crs);
				REZ[nREZ++]=getTranzitie(crs,LAMBDA,S);
				lastComun = S;  // tinem minte starea in care am ajuns
				// pentru cazurile in care avem simbol (+,*), care nu este afectat de pipe gen ab(ab)*;
			}break;
		case 2:
			{
				REZ[nREZ++]=getTranzitie(crs,LAMBDA,S);
				crs = S++;
				sparge(expresie,crs);
				REZ[nREZ++]=getTranzitie(S-1,LAMBDA,crs);
			}break;
		default:
			{
				sparge(expresie,crs);
				S=cursor--;		//cazul asta face practic o miscare goala
								// si creste S fara sa pastreze legatura intre stari
			}break;
		}
		cursor = S++;

}

void do_simbol(char c, int simbol)
{
	switch(simbol)
	{
		case 1:
			{
				REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
				REZ[nREZ++]=getTranzitie(S,c,S);
				cursor = S;
				S++;
			}break;
		case 2:
			{
				REZ[nREZ++]=getTranzitie(cursor,LAMBDA,S);
				cursor = S;
				S++;
				REZ[nREZ++]=getTranzitie(cursor,c,S);
				REZ[nREZ++]=getTranzitie(S,LAMBDA,cursor);
				cursor = S;
				S++;
			}break;
		case 0:
			{
				REZ[nREZ++]=getTranzitie(cursor,c,S);
				cursor = S;
				S++;
			}break;
	}
	lastComun = cursor;   // tinem minte ultima stare in care am ajuns
	// pt situatiile in care nu avem pipe-uri
}

void afisareProgers(int start)
{// afiseaza noile tranzitii create in automat
	for(int i=start;i<nREZ;i++)
	{
		cout<<REZ[i]<<endl;
	}
	cout<<endl;
}
void procesare_expresie(const string& expresie, int cursor)
{
	for(int i=0,n = expresie.size();i<n;i++)
	{
		if(expresie[i] == '(')
		{
			//avansam pana la finalul parantezei
			int end = get_simbol(expresie,i);	// indexul simbolului
			int simbol = map_simbol(expresie[end]);	// numarul simbolului
			string next = expresie.substr(i+1,end-2-i);
			if(simbol)		// daca e un simbol, vom sarii si peste el
				i = end;
			else			// daca nu e simbol, atunci ne-am oprit pe o litera
				i = end-1;
			// pt afisare paci;
			int aici = nREZ;
			do_simbol(next,simbol);
			//
			//afisare pasi
			{
				cout<<"Pt "<<next<<":\n";
				afisareProgers(aici);
			}
		}
		else
		{
			int simInd = get_simbol(expresie,i);
			int simbol = map_simbol(expresie[simInd]);
			int aici = nREZ;
			do_simbol(expresie[i],simbol);
			// afisare pasi
			{
				cout<<"Pt "<<expresie[i];
				if(simbol)
					cout<<expresie[i+1];
				cout<<":\n";
				afisareProgers(aici);
			}
			//cout<<expresie[i]<<" ";LOG(simbol);
			if(simbol)
				i = simInd;
		}
	}
}
void sparge(string& expresie, int initial=0)
{	// sparge dupa pipe-uri
	int pos = -1, prev;
	int stareComuna=0;
	// daca este pipe, atunci o sa avem o stare finala comuna
	if(find_pipe(expresie,0)!= -1)
		stareComuna= S++;
	do
	{
		prev = pos+1;
		//(a|b)a|c|a
		pos = find_pipe(expresie,prev);
		cursor = initial;
		// expresia care urmeaza sa fie prelucrata
		string next = expresie.substr(prev,pos-prev);
		LOG(next);
		// tine minte ultima tranzatie scrisa
		int aici = nREZ;
		procesare_expresie(next,cursor);
		if(stareComuna)		// daca avem pipe, ne vom intoarce cu toate laturile aici
		  REZ[nREZ++]=getTranzitie(S-1,LAMBDA,stareComuna);
		//afisare pasi
		cout<<"Am terminat "<<next<<" si am optinut:"<<endl;
		afisareProgers(aici);	// afiseaza ultimele tranzitii srise
	}while(pos != -1);
	if(stareComuna)
		lastComun = stareComuna;
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
	cout<<"Salutare\n";
	ifstream f("regexhard.in");
	ofstream F("regexhard.out");
	string expresie;
	while(getline(f,expresie))
	{
		S = 2;
		nREZ = 0;
		if(!verificare_paranteze(expresie))
		{
			cout<<"Paranteze aiurea\n";
			continue;
		}
		LOG(expresie);
		paranteze_redundante(expresie);
		LOG(expresie);
		sparge(expresie);
		REZ[nREZ++] = getTranzitie(lastComun,LAMBDA,1);
		afisare(F);
	}
	return 0;
}
