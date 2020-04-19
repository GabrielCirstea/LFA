# Transformare AF intr-o expresie regulata
## Construrire AFE

### Ce trebuie sa iasa:
Dintr-un automat finit oarecare(eventual AFN lambda) vrem sa scoatem o expresie regulata.  

### Idei/Algoritm:
* Vom renota tranzitiile cu etichete:
  * daca intre 2 stari exista mai multe tranzitii, atunci eticheta va fi reuniunea tranzitiilor(simbolurulor).
___
Vom avea starile si etichetele dintre stari.
Etichetele:
| index | eticheta        |
|-------+-----------------|
|     1 | ab              |
|     2 | b               |
|     3 | alta eticheta   |
|     4 | inca o eticheta |
|     5 | inca o eticheta |
|     6 | inca o eticheta |
|-------+-----------------|
Se retinem starile si etichetele in: 
- liste de muchi?
- sau lista de adiacenta?
- o matrice cu starile pe liniis si coloane si indicele ethichetei...
| index |       1 |   2 |   3 | ceva comentarii                        |
|-------+---------+-----+-----+----------------------------------------|
|     1 | 0(NULL) |   3 |   0 | # 0 sau -1 pt NULL adica valoare goala |
|     2 |       1 |   2 |   3 |                                        |
|     3 |       0 |   0 |   0 | # 3 e capat de linie.                  |
|     4 |     ... | ... | ... |                                        |
|     5 |     ... | ... | ... |                                        |
* Pentru starile finale:
  * daca sunt mai multe stari finale sau daca din starea finala exsta tranzitii care ies din aceasta, atunci se va creea o noua stare finala si toate starile finale anterioare vor avea o lambda trnazitie catre aceasa.
  * analog se va proceda si in cazul starilor initiale
___
## Stadiu curent
Programul citeste un automat(AFN) dintr-un fisier si face notarea etichetelor intr-o matrice cu formatul de mai sus.  
## TO BE CONTINUED:
* Crearea unei noi stari finale si initiale daca este nevoie.
* Combinarea etichetelor prin reuniune(sumare) sau concatenare. Adica algoritmul propriu zis.
