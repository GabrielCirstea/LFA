# Trecerea de la AFN la AFD
## O mare teorema zica ca pentru orice AFN se poate construi un AFD
Difetentele dintre AFN - AFD:
* la AFD dintr-o stare cu o litera se poate pleca spre o unica stare
* la AFN dintr-o stare cu o litera putem ajunge in mai multe stari

Fisierul de intrare are acelas format cu cel de la AFN si AFD.  

## Algortim
Din moment ce in AFD cu o litera ajugem din starea x doar in starea y, iar in AFN putem ajunge in mai multe adica {y1,y2,y3,...}, vom nota aceste multim ca stari normale intr-un AFD.
Pornind din prima stare (0, prin convetie):
* se noteaza ficare mutime de stari in care ajungem (cu fiecare litera) ca o alta stare.
* aceasta noua stare va avea tranzitii spre toate starile in care starile din componenta sa aveau:
  * daca x merge in {y1,y2,...} si o notam cu Y, atunci Y merge in multimea formata din starile in care mergeau y1,y2...
* stari finale in AFD vor fi toate starile care au in componenta lor o stare finala din AFN.

## Implementare
**Pentru ca a fost mai greu de implementat.**
* se ia matricea normala pentru AFD
* o lista de multimi ce reprezinta renotarea multimilor de la AFN pentru AFD
* Incepand cu prima stare se fac multimile de stari in care se ajunge plecand cu fiecare litera din alfabet.
* Tinem evidenta multimilor pe care le avem de verificat cu o coada
* La creerea unei multimi noi:
  * Verificam daca este sau nu in lista noastra de multimi:
    * daca este, punem in matricea de AFD indexul ei.
    * daca nu, o trecem in lista de multimi si punem indexul in matrice, de asemenea o trecem si in coada de multimi petru a o verifica.
* Dupa ce am verificat multimea curenta cu toate literele alfabetului trecem la urmatoarea stare a AFD-ului si repetam procesul cu urmatoarea multime din coada.
* Procesul se termina cand nu mai avem multimi ne verificate in coada.
___
Programul v-a strie AFD-ul intr-un fisier, in acelas format folosit si la 
emularea AFD si AFN, urmat de un numar de linii egal cu numarul de cuvinte 
din fisierul AFN, pe care se va scrie 1 daca cuvantul este acceptat de AFN 
sau 0 in caz contrar.
