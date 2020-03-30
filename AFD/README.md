# Emulare AFD
## Automat Finit Determinist

Programul simuleaza un AFD, citi dintr-un fisier.
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
Tranzitiile au fost retinulte intr-o matrice:
* pe linii se afa indicii stariilor sursa
* pe coloane sunt caracterele cu care se face tranzitia
* la intersectia liniei cu coloana se afa starea in care se face tranzitia
<br><br>
Se pleaca din starea 0, se face parcurgerea din stare in stare cu literele cuvantului.
Pentru fiecare litera a cuvantului se verifica daca exista:
__Matrice[stareCurenta][litera]__;  
In caz afirmativ, aceasta devine starea curenta.  
In caz contrar nu avem tranzitie, deci cuvantul nu este acceptat.
