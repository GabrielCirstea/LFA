# Emulare AFN
## Automat Finit Nedeterminist

Programul simuleaza un AFN, citi dintr-un fisier.
__Formatul fisierului__:
* Pe prima linie este indicele ultimei stari.
* Urmeaza un sir de 0 si 1, reprezentat starile finale
  * 1 starea este finala, 0 - nu este
* Alfabetul: sir de caractere
* n - Numarul de tranzitii
* Urmeaza n tranzitii de forma:
  * caracter sursa destinatie
  * intre sursa si destinatie se poate face tranzitia cu caracterul citit
* m - numarul de cuvinte care vor fi testate
* Se citest cele m linii care vor fi testate de automat.

## Algoritm
Tranzitiile au fost retinute asemanator cu cele de la AFD, dar acum elementele matricei sunt o serie/multime de stari in care se poate ajunge plecand de la starea sursa cu litera respectiva.  
* Se pleaca din starea 0
* Pentru fiecare litera a cuvantului se fac tranzitiile din starile curente
* Si se retin noile stari
* La final se cauta starile finale in starile in care am ajuns.
* Daca nu se gaseste nici o stare finala, ori daca nu am ramas cu nici o stare, cuvantul nu este acceptat de automat.
