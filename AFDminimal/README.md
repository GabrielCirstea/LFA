# AFD minimal
Se cauta un AFD echivalent cu cel dat, dar care sa aiba mai putine noduri.  

___
Programul citeste un AFD dintr-un fisier cu accelas format ca celelalte programe ce lucreaza cu automate si calculeaza AFD-ul minima, daca este posibil si il scrie intr-un fisier.  
Pentru a fi acceptat de program AFD-ul trebuie sa fie __complet__, adica 
sa aiba tranzitii cu toate literele din alfabet din fiecare stare.

## Idei principale
* trebuie aflate care sunt starile echivalente.
* doua sau mai multe stari sunt __echivalente__ daca plecand din ele cu un sir 
de caractere din alfabetul nostru ajungem in:
    * stari finale
    * sau in stari nefinale
* starile __echivalente__ se unesc intr-o singura stare.
### Algoritm
* prima data se calculeaza o matrice de echivalenta pentru a sti care stari 
sunt __echivalente__:
    * matricea este simetrica si are 0 pe diagonala principala
    * daca la intersectia liniilor si coloanelor i si j este 0 atunci starile 
    i si j sunt echivalente
	* daca avem o stare finala i si o stare nefinala j, atunci pe pozitia i,j in matrice vom avea 1
    * apoi se parcurge matricea la intalnirea unei valori 0, verificam daca plecand din starile i si j, ajungem in stari neechivalente, in caz afirmativ pe pozitia i,j se pune 1.
    * matricea se parcurge astefel cat timp se produ asemenea schimbari
* pentru a fi mai usor de tinut socoteala am facut o renotare a starilor pentru noul AFD
* renotarea este un vector, in care indicii sunt starile AFD-ului normal 
si valorile sunt starile din AFD-ul minimal.
    * pentru fiecare stare ne renotata din AFD-ul normal, se face renotarea si se cauta si stari echivalente cu aceasta.
* renotarea ne permite sa construim mai usor matricea de adiacenta a AFD-ului minim
* pt starile din AFD nomal, se face tranzitia pt fiecare litera:
  * in matricea pt AFD minim se trece tranzitia intre renotare[stare] si renotare[dest]
  * se face renotarea atat pe starea din care pleaca tranzitia cat si pe cea 
  in care ajunge
* in cazul in care AFD-ul nu mai poate fi minimizat programul se opreste si scrie in fisier "NU!"
* dupa ce minimizarea se opreste, in fisierul de iesire vor fi scrise informatiile urmant formatul folosit si pentru fisierul de intrare.
