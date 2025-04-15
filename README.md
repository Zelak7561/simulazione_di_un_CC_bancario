Inclusi eser da 8.3 a 8.6

[8.3]
Modifichiamo la classe MiniCCB per aggiungere la gestione di
un PIN, richiesto per autorizzare ogni operazione su C/C.
Il PIN di una istanza della classe è impostato dal costruttore
Deve essere inserito dall’utente prima di ogni operazione e
passato al metodo che la implementa;
La classe verifica il PIN e rifiuta l’operazione in caso sia sbagliato;
Tre errori di fila bloccano il C/C;

[8.4]
Modifichiamo la classe MiniCCB per aggiungere le seguenti
funzionalità:
Un metodo che cambi il PIN
Il PIN deve essere di almeno 5 caratteri
-bool cambiaPIN(string oldPIN, string newPIN)

[8.5]
Modifichiamo la classe MiniCCB per aggiungere le seguenti
funzionalità:
Un codice PUK che possa essere utilizzato per sbloccare un
C/C dopo tre errori di PIN consecutivi (e cambia il PIN).
Il PUK deve essere di almeno 10 caratteri
10 errori di PUK consecutivi bloccano il C/C
-bool Sblocca(string mioPUK, string newPIN)

[8.6]
Si implementi una funzione esterna alla classe MiniCCB che
permetta di effettuare un bonifico da un conto all’altro:
La funzione prende il riferimento al conto che eroga il bonifico
e il suo PIN, il riferimento al conto ricevente e l’importo della
transazione.
NB. Chi ordina un bonifico conosce il PIN del suo conto, ma
non quello del ricevente …
bool bonifico(MiniCCB &mioCC, string mioPIN, MiniCCB &suoCC, double importo)
