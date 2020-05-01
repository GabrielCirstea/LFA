# Transformarea expresiilor regulate simple in AFN 
## Expresii regulate simple
* Dupa ce o sa citesc definitia expresiilor regulate o sa o pun si aici.
* Programul lucreaza cu expresii regulate ce presupun operatiile de concatenare si reuniune(*,+,|);
* _"simple"_ pentru ca in aces program nu accepta expresii cu paranteze
ex: (ab)*
## Algoritm
* Se parseaza expresia dupa semnul |
  * se imparte in expresii separate retinute intr-o lista/array de string-uri
  * acestea se tin separate pt ca operatia | presupune un "sau" adica tranzitii separate in automat
* se despart expresiile extrase(ex ab, a+) in "noduri logice"
  * aceste noduri sunt structuri in care retine litera si daca aceasta are un simbol special: *,+.
* se parcurg expresiile(string-uri), se retin caracterele
  * la intalnirea unui simbol, acesta este atasat ultimului caracter citit.
* generarea automatului se face prin afisarea directa a tranzitiilor
  * Pentru fiecare expresie( serie de noduri) se construieste un sir de tranzitii intre starea initiala(0) si cea finala(1, pentru a fi mai usor).
  * Pentru caractere fara simboluri se afisaza tranzitie cu caracterul respectiv catre starea urmatoare.
  * La caracterele cu simbot(* sau +) se face o lambda tranzitie catre o stare in care se incepe expresia
    * pt * se face circuit in starea respectiva
    * pt + se face tranzitie cu caracter la o alta stare din care ne intoarce cu lambda tranzitie.
___
Programul citeste dintr-un fisier expresii scrie pe linii si afiseaza automatul construit pe ecran.
