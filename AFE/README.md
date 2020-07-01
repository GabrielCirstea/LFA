# Transformare AF intr-o expresie regulata
## Construrire AFE

### Ce trebuie sa iasa:
Dintr-un automat finit oarecare(eventual AFN lambda) vrem sa scoatem o expresie regulata.  

### Idei/Algoritm:
* se aduce la un AFN cu o stare initiala in care nu intra nici o alta tranzitie
	* se shifteaza toate starile si tranzitiile a.i in starea 0(noua stare initiala) sa nu intre nici o tranzitie.
	* se adauga o noua stare finala la care se ajunge cu lambda tranzitii din toatea starile finale initiale
* matricea pentru AFE este o matrice de string-uri care reprezinta tranzitia dintre oricare 2 stari
	* popularea matricei sa face prin a se trece in aceasta tranzitia dintre starile automatului initial
	* daca intre 2 stari exista mai multe tranzitii in matricea AFE va fi reuniunea acestora "|" sau "+"
* se incepe eliminarea starilor de la starea 0
	* eliminarea se face incepand din starea i si trecand prin starea j, legandu-se i cu toate starile cu care j este legata.
	* apoi se elimina tranzitia i - j
* la sfarsit ar trebui sa ramana o singura tranzitie care reprezinta expresia cautata.
___
## Stadiu curent
Programul aplica algoritmul descris mai sus.
Rezultatul nu este inca cel corect.
