/*

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
 */


#include <iostream>
#include <string>

using namespace std;

class MiniCCB {
public:
    int id;
    double Dare;
    double Avere;

    string Pin;
    string Puk;
    int Tentativi;

    MiniCCB() {
        id = 000;
        Dare = 0;
        Avere = 0;

        Pin = "351EW";
        Puk = "0000000";
        Tentativi = 3;
    }

    //Setter
    void setId(int Id) {
        id = Id;
    }

    void setSaldo(double Saldo) {
        Avere = Saldo;
    }

    //Getter
    double getSaldo() {
        return Avere - Dare;
    }

    int getId() {
        return id;
    }


    //Gestione Pin
    bool controllo_Pin(string pin) {
        if (Tentativi <= 0) {
            cout << "\nConto bloccato. Troppi tentativi falliti.\n";
            return false;
        }

        if (pin == Pin) {
            Tentativi = 3;
            return true;
        }

        Tentativi--;

        cout << "\nPIN errato. Operazione negata." << endl;
        cout << "Tentativi rimasti: " << Tentativi << endl;

        if (Tentativi == 1) {
            cout << "⚠Attenzione: 1 solo tentativo rimasto prima del blocco del conto!\n";
        } else if (Tentativi == 0) {
            cout << "Hai esaurito i tentativi. Il conto è ora bloccato.\n";
        }

        return false;
    }
    bool controlloTentativi(int Tentativi) {
        if (Tentativi <= 0) {
            return false;
        }
        return true;
    }


    //Operazioni effettive sul pin
    bool cambiaPIN(string oldPIN, string newPIN) {
        cout << oldPIN << endl;
        if (controllo_Pin(oldPIN) && oldPIN.length() >= 5) {
            Pin = newPIN;
            return true;
        }
        return false;
    }

    bool Sblocca(string mioPUK, string newPIN) {
        if (mioPUK == Puk) {
            Pin = newPIN;
            Tentativi = 3;
            return true;
        }
        return false;
    }


    //Gestione operazioni
    double Saldo(string pin) {
        if (controllo_Pin(pin)) {
            return Avere - Dare;
        }
        return 0.0;
    };

    void Deposito(string pin) {
        double importo = 0;
        if (controllo_Pin(pin)) {
            cout << "Importo da versare: ";
            cin >> importo;
            Avere += importo;
        }
    }

    void Prelievo(string pin) {
        double importo = 0;
        if (controllo_Pin(pin)) {
            cout << "Importo da prelevare: ";
            cin >> importo;
            Dare += importo;
        }
    }

    bool invia(double importo, string pin) {
        if (controllo_Pin(pin)) {
            if (importo <= 0) {
                cout << "Importo non valido. Deve essere maggiore di zero." << endl;
                return false;
            }

            if (importo > Avere - Dare) {
                cout << "Saldo insufficiente per completare l'operazione." << endl;
                return false;
            }

            Dare += importo;
            return true;
        }
        return false;
    }

    void riceve(double importo) {
        if (importo <= 0) {
            cout << "Importo non valido. Deve essere maggiore di zero." << endl;
            return;
        }

        Avere += importo;
    }

};

bool bonifico(MiniCCB &mioCC, string mioPIN, MiniCCB &suoCC, double importo) {
    if (mioCC.invia(importo, mioPIN)) {
        suoCC.riceve(importo);
        return true;
    }
    return false;
}


int main() {
    bool ancora = true;
    int scelta = 0, identificativo;
    double importoB = 0.0;
    string pin, newPin, puk;

    MiniCCB Conto;
    Conto.setId(432);
    Conto.setSaldo(4000);

    MiniCCB Conto1;
    Conto1.setId(543);
    Conto1.setSaldo(0);

    cout << "==============================================" << endl;
    cout << "   Simulazione di un C/C Bancario v.1         " << endl;
    cout << "==============================================" << endl;

    do {
        pin = "";
        newPin = "";
        importoB = 0;

        cout << "\n\n============= MENU OPERAZIONI =============\n";
        cout << "1: Deposito\n";
        cout << "2: Prelievo\n";
        cout << "3: Visualizza Saldo\n";
        cout << "4: Bonifico\n";
        cout << "0: Uscita\n";

        cout << "\n----------- MENU ASSISTENZA -----------\n";
        cout << "5: Cambia PIN\n";

        cout << "==============================================\n";
        cout << "Inserisci la tua scelta: ";
        cin >> scelta;
        cout << "----------------------------------------------\n";

        switch (scelta) {
            case 0:
                cout << "\nGrazie per aver utilizzato il sistema. Arrivederci!\n";
                ancora = false;
                break;

            case 1:
                cout << "\n[Deposito] Inserisci il PIN: ";
                cin >> pin;
                Conto.Deposito(pin);
                cout << "[Deposito] Operazione completata.\n";
                break;

            case 2:
                cout << "\n[Prelievo] Inserisci il PIN: ";
                cin >> pin;
                Conto.Prelievo(pin);
                cout << "[Prelievo] Operazione completata.\n";
                break;

            case 3:
                cout << "\n[Saldo] Inserisci il PIN: ";
                cin >> pin;
                cout << "\nSaldo attuale del conto ID " << Conto.getId() << ": "
                     << Conto.Saldo(pin) << " euro\n";
                break;

            case 4:
                cout << "\n[Bonifico] Inserisci l'identificativo del conto destinatario: ";
                cin >> identificativo;
                cout << "Inserisci l'importo da trasferire: ";
                cin >> importoB;
                cout << "Inserisci il tuo PIN: ";
                cin >> pin;

                if (identificativo == Conto1.getId()) {
                    cout << "\nAvvio bonifico di " << importoB << " euro da conto " << Conto.getId()
                         << " a conto " << Conto1.getId() << "...\n";

                    if (bonifico(Conto, pin, Conto1, importoB)) {
                        cout << "\nBonifico riuscito!\n";
                        cout << "Saldo aggiornato:\n";
                        cout << "- Conto " << Conto.getId() << ": " << Conto.getSaldo() << " euro\n";
                        cout << "- Conto " << Conto1.getId() << ": " << Conto1.getSaldo() << " euro\n";
                    } else {
                        cout << "Bonifico fallito. Verifica il PIN o i fondi disponibili.\n";
                    }
                } else {
                    cout << "Conto destinatario non trovato.\n";
                }
                break;

            case 5:
                cout << "\n[Cambio PIN] Inserisci il vecchio PIN: ";
                cin >> pin;
                cout << "Inserisci il nuovo PIN [minimo 5 caratteri]: ";
                cin >> newPin;
                if (!Conto.cambiaPIN(pin, newPin)) {
                    cout << "\nImpossibile cambiare il PIN. Verifica di aver inserito correttamente quello vecchio e che il nuovo abbia almeno 5 caratteri.\n";
                } else {
                    cout << "\nPIN modificato con successo!\n";
                }
                break;

            default:
                cout << "⚠Scelta non valida. Riprova.\n";
                break;
        }

        // Controllo blocco per errori PIN
        if (!Conto.controlloTentativi(Conto.Tentativi)) {
            cout << "\nConto bloccato per troppi tentativi errati.\n";
            cout << "Inserisci il PUK per sbloccare il conto: ";
            cin >> puk;
            cout << "Inserisci un nuovo PIN: ";
            cin >> newPin;
            if (Conto.Sblocca(puk, newPin)) {
                cout << "Conto sbloccato e PIN aggiornato!\n";
                ancora = true;
            } else {
                cout << "Sblocco fallito. Fine sessione.\n";
                ancora = false;
            }
        }

        cout << "\n==============================================\n";

    } while (ancora);

    return 0;
}

