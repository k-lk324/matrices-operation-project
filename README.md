# Πράξεις Πινάκων
## Περιεχόμενα
#### 1. Οδηγίες
#### 2. Περιγραφή
#### 3. Πηγές

## Οδηγίες
- Για την εκτέλεση του προγράμματος χρειάζονται τα αρχεία: main.c, prakseis.c και prakseis.h
- Τo πρόγραμμα έχει δοκιμαστεί σε windows 10, ωστόσο δεν περιέχει χαρακτηριστικά τετοια ωστε να περιορίσει( να λειτουργησει σε οποιοδηποτε λειτουργικο συστημα) 
- Το πρόγραμμα λειτουργεί με διαδραστικά μενού, ο χρήστης μπορεί να διαλέξει μία επιλογή γράφοντας τον αριθμό από μπροστά της. Για παράδειγμα:

![image](https://user-images.githubusercontent.com/97043061/150507535-1505374a-5cd1-4762-814a-806d5c2a1e81.png)

 > Σημείωση: Για προβολή διαθέσιμων συστοιχιών ή επιλογή από διαθέσιμες συστοιχίες χρειάζεται πρώτα δημιουργία ή φόρτωση συστοιχιών

## Περιγραφή

![image](https://user-images.githubusercontent.com/97043061/151072773-08e5df7e-779e-4856-9ac4-bb6406fb321b.png)



```flow
s=>start:  Αρχή
e=>end: Τέλος
pm=>inputoutput: Αρχικό Μενού και
Επιλογή Χρήστη
cond1=>condition: Έξοδος;
cond2=>condition: Δημιουγία Συστοιχίας
cond3=>condition: Προβολή Συστοιχιών
cond4=>condition: Φόρτωση συστοιχίας
cond5=>condition: Διαγραφή συστοιχίας
cond6=>condition: Πράξεις πινάκων
cond7=>condition: Πράξεις διανυσμάτων

iom =>inputoutput: Εισαγωγή συστοιχίας
subr_save=>operation: Αποθήκευση συστοιχίας σε αρχείο

subr_show=>inputoutput: προβολή αποθηκευμένων 
συστοιχιών σε λίστα και 
επιλογή ενός από το χρήστη
subr_elements=>inputoutput: προβολή στοιχείων συστοιχίας

io2=>inputoutput: Εισαγωγή ονόματος αρχείου συστοιχίας
op3=>operation: προσθήκη ονόματος στις διαθέσιμες συστοιχίες

io4=>inputoutput: προβολή 
αποθηκευμένων συστοιχιών
op12=>operation: διαγραφή αναγνωριστικού
op13=>operation: διαγραφή αρχείου συστοιχίας

choice_op=>inputoutput: επιλογή πράξης
choice2=>condition: εισαγωγή συστοιχίας/ών 
από αρχείο;
io5=>inputoutput: Εισαγωγή διαστάσεων και τιμών από χρήστη
op56=>operation: εισαγωγή από αρχείο
opop=>operation: εκτέλεση πράξης
io100=>inputoutput: προβολή αποτελέσματος
savem=>condition: Αποθήκευση συστοιχίας;
opsa=>operation: Αποθήκευση συστοιχίας σε αρχείο

vector=>operation: Ομοίως με πράξεις πινάκων



s->pm->cond2
cond2(no, right)->cond3
cond2(yes)->iom ->subr_save->pm
cond3(no, right)->cond4
cond3(yes)->subr_show->subr_elements(right)->pm
cond4(no, right)->cond5
cond4(yes)->io2->op3(right)->pm
cond5(no,right)->cond6
cond5(yes)->io4->op12->op13(right)->pm
cond6(no,right)->cond7
cond6(yes)->choice_op->choice2
choice2(yes)->op56->opop->io100->savem
savem(yes)->opsa(right)->pm
savem(no)->pm
choice2(no)->io5->opop
cond7(no,right)->cond1
cond7(yes)->vector(right)->pm
cond1(yes)->e

```
