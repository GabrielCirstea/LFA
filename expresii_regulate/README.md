# Expresii regulate
Acum expresiile pot constine si paranteze
ex: ```(ab)*b|a((bc+)*|a)b+c*```
## Algoritm
* se cauta si elimina parantezele redundante:
  * pt fiecare paranteza se cauta perechea ei, daca perchea este urmata de un simbol(* sau +) atunci nu poate fi eliminata.
* se desparte expresia dupa semnul pipe ("|"):
  * se tine cont de paranteze si se iau in considerare doar semnele care nu sunt prinse intre paranteze
* pentru fecare expresie selectata se parcurg caracterele si se afiseaza tranzitiile:
  * pt fiecare caracter se cauta simbolul(* sau +) daca exista
  * la intalnirea unei paranteze: se selecteaza toata expresia din paranteza si se aplica intregul algoritm pe paranteza respectiva
  * inainte de aplicarea pe paranteza respectiva se cauta semnul care o precede, pentru a afisa tranzitiile corespunzatoare.
* la spargerea dupa pipe-uri se tine minte o stare comuna la care se intalnesc laturile create.
___
Programul citeste imputul dintr-un fisier "regexhard.in" si afiseaza rezultatul in "regexhard.out"
* pe prima line se afla numarul de tranzitii ale automatului.
* tranzitiile
* pe ultima linie este nr starii finale, care, prin conventie, este 1.
