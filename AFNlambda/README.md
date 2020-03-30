# Emulare AFN lambda
Un automat AFN cu lambda tranzitii.
__Lamnda tranzitiile__ "se intampla mereu".
Dintr-o stare se poate pleca cu o lambda tranzitie fara a se utiliza nici un caracter din cuvantul respectiv.

## Algoritm
Asemanator cu algortmul pentru AFN-ul normal, dar aici la fiecare stare, se adauga in coada, starile in care se ajunge cu lamnda tranzitii.  
Pentru a fi mai usor de calculat se calculeaza __lambda inchiderea__ unei stari.  
### Lambda Inchidere
Reprezinta multimea de stari in care se ajunge dintr-o stare mergand numai pe tranzitii cu lambda.
**Determinarea** lambda inchiderii este facuta cu un simplu DF (se poate si BF):
* avem nodul, matricea de adiacenta, si un vector in care tinem evidenta starilor vizitate pentru a evita ciclurile.
* se adauga nodul curent in lista
* se adauga DF-ul pentru fiecare stare in care putem ajunge cu lambda
* se returneaza lista creata.

__Diferenata in algoritmul pentru AFNlambda:__  
* pentru fiecare stare in care am ajuns se pleaca din lambda inchiderea ei
Asemenea cu AFN-ul normal:
* Plecam din prima stare.
* O adaugam in lista/coada de parcurs
* Pentru fiecare litera din cuvant
  * Pentru fiecare stare din coada adaugam in coada tranzitiile cu litera curenta din labda inchiderea starii.
  * Din starea x, se calculeaza lambda inchiderea;
  * Din fiecare stare din lambda inchiderea lui x plecam cu litera curenta
  * Adaugam aceste noi stari in coada de parcus.
