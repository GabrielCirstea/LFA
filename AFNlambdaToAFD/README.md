# Trecerea de la AFN lambda la AFD
O teorema spune ca pentru orice AFN lambda se poate construi un AFD echivalent.
___
Programul citeste un AFNlambda dintr-un fisier cu acelas format ca emulatorul de AFN, si construieste un AFD echivalent.

### Algoritm
Asemenea cu trecerea de la AFN la AFD, plecam din prima stare si scriem multimea de stari in care ajunge ca o noua stare intr-un AFD.
* avem o coada cu multimi de verificat
* o lista de multimi salvate/notate
* pentru fiecare multime din coada
  * luam starile si le parcurgem cu literele din alfabet  
  **Este AFN** vom face parcurgerea pronind din __lambda inchiderea__ starilor.
  * cautam starile formate in lista de multimi salvate
    * daca u sunt acolo le adaugam in lista
    * le adaugam si in coada, pentru a le parcurge in continuare
    * trecem indicele multimii in matricea pentru AFD
* dupa ce am parcurs o multime cu toare literele avansam pe urmatoarea linie a matricei AFD cu umratoarea multime din coada.
___
Programul trece AFN-ul intr-un AFD echivalent si il scrie intr-un fisier, folosind acelas format ca fisierul de intrare:
* indecele ultimei stari
* vector caracteristic pentri starile finale
* alfabet
* nr de tranzitii N
* N tranzitii de forma :litera stare stare:  
Apoi vor fi M linii, unde M este numarul de cuvinte citite, pe care se 
va afisa acceptanta cuvantului in AFD-ul optinut: 1 - este acceptate, 0 - nu este acceptat.
