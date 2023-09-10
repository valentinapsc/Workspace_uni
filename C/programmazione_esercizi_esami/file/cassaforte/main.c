#include <stdio.h>
#include <stdlib.h>

#define filename "cassaforte.bin"

struct Cassaforte {
    int combinazione;
    int stato; // 0 = chiusa, 1 = aperta
    float cifraContenuta;
};

void init_struct(struct Cassaforte *);
void crea_cassaforte(struct Cassaforte *);
void apri_cassaforte(struct Cassaforte *, int);
void visualizza_stato(struct Cassaforte);
void visualizza_ammontare(struct Cassaforte);
void deposita_somma(struct Cassaforte *, float);
void preleva_somma(struct Cassaforte *, float);
void chiudi_cassaforte(struct Cassaforte *);

int main(){
    struct Cassaforte cassa;

    int choice = -1;

    init_struct(&cassa);

    while (choice != 0){

        printf("scegli quale operazione effettuare tra queste:\n");
        printf("1. vuoi creare una nuova cassaforte? (ti avverto che se gia' ne esiste una sara' annientata)\n");
        printf("2. se vuoi aprire questa stupenda cassaforte\n");
        printf("3. se vuoi visualizzare lo stato (cioe' se e' aperta o chiusa)\n");
        printf("4. vuoi visualizzare l'ammontare? con cio' che guadagni penso sia vuota\n");
        printf("5. deposita una somma (se ne hai una)\n");
        printf("6. preleva una somma (se ce n'e' qualcuna)\n");
        printf("7. chiudi cassaforte (tanto aperta e' inutile)\n");
        printf("0. esci (ma se hai fatto delle modifiche verranno eliminate)\n\n");
        printf("quindi scegli: ");
        scanf("%d", &choice);

        system("cls");

        // crea nuova cassaforte
        if (choice == 1)
        {
            crea_cassaforte(&cassa);
            printf("\n\n");
        }

        // apri cassaforte
        else if (choice == 2)
        {
            int combinazioneSegreta;
            printf("inserisci la combinazione segreta: ");
            scanf("%d", &combinazioneSegreta);
            apri_cassaforte(&cassa, combinazioneSegreta);
            printf("\n\n");
        }

        // visualizza stato cassaforte
        else if (choice == 3)
        {
            visualizza_stato(cassa);
        }

        // visualizza ammontare nella cassaforte
        else if (choice == 4)
        {
            visualizza_ammontare(cassa);
            printf("\n\n");
        }

        // deposita una somma nella cassaforte
        else if (choice == 5)
        {
            float sommaDepositata;
            printf("inserisci la somma da depositare (se non sei povero): ");
            scanf("%2f", &sommaDepositata);
            deposita_somma(&cassa, sommaDepositata);
            printf("\n\n");
        }

        // preleva dalla cassaforte
        else if (choice == 6)
        {
            float sommaPrelevata;
            printf("inserisci la somma da prelevare (se la cassaforte non e' vuota): ");
            scanf("%2f", &sommaPrelevata);
            preleva_somma(&cassa, sommaPrelevata);
            printf("\n\n");
        }

        // chiudi cassaforte
        else if (choice == 7)
        {
            chiudi_cassaforte(&cassa);
            printf("\n\n");
        }

        // scelta sbagliata
        else if (choice != 0)
        {
            printf("non hai scelto niente, hai sbagliato");
            printf("\n\n");
        }
        
    }
    

    return 0;
}

void init_struct(struct Cassaforte *cassa){
    cassa -> stato = 0;
    cassa -> cifraContenuta = 0; 
}

// se la scelta è 1
void crea_cassaforte(struct Cassaforte *new){
    printf("per creare una nuova cassaforte scegli prima una combinazione: ");
    scanf("%d", &new -> combinazione);

    init_struct(new);

    FILE *fp = fopen(filename, "wb");

    // nel caso ci fossero problemi nell'apertura del file
    if (fp == NULL){
        perror("");
        exit(-1);
    }

    // numeri inseriti nel file con successo
    int numScritti = fwrite(new, sizeof(struct Cassaforte), 1, fp);

    // controllo se c'è stato qualche problema durante la scrittura
    if (numScritti < 1){
        perror("");
        fclose(fp);
        exit(-1);
    }
    
    fclose(fp);
}

void apri_cassaforte(struct Cassaforte * apri, int combinazioneCassaforte){

    FILE *fp = fopen(filename, "rb");

    // nel caso ci fossero problemi nell'apertura del file
    if (fp == NULL){
        perror("");
        exit(-1);
    }

    struct Cassaforte tmp; // mi servirà per confrontare la combinazione

    // numeri letti con successo
    int numLetti = fread(&tmp, sizeof(struct Cassaforte), 1, fp);

    // controllo se c'è stato qualche problema durante la lettura
    if (numLetti < 1){
        perror("");
        fclose(fp);
        exit(-1);
    }
    
    fclose(fp);

    // controllo se la combinazione data è corretta
    if (combinazioneCassaforte == tmp.combinazione){
        *apri = tmp;
        apri -> stato = 1;
    } else ("combinazione errata, continua cosi'!\n\n");
}

void visualizza_stato(struct Cassaforte stato){
    if (stato.stato == 0)
        printf("se proprio lo vuoi sapere la cassaforte e' chiusa\n\n");
    else
        printf("ti informo del fatto che la cassaforte e' aperta\n\n");
}

void visualizza_ammontare(struct Cassaforte ammontare){
    // prima di visualizzare la somma controlla se la cassaforte è chiusa (nel caso lo segnala) o aperta
    if (ammontare.stato == 0)
        printf("la cassaforte e' chiusa, che vuoi vedere");
    else
        printf("beh, non hai molti soldi perche' ne sono %2f\n", ammontare.cifraContenuta);
}

void deposita_somma(struct Cassaforte *deposita, float sommaDepositata){
    // prima di depositare una somma controlla se la cassaforte è chiusa o aperta
    if (deposita -> stato == 0) 
        printf("stai cercando di depositare soldi con la cassaforte chiusa, grande\n\n");
    else
        deposita->cifraContenuta += sommaDepositata;
}

void preleva_somma(struct Cassaforte *preleva, float sommaPrelevata){
    // prima di prelevare una somma controlla se la cassaforte è chiusa o aperta
    if (preleva -> stato == 0) 
        printf("stai cercando di prelevare soldi con la cassaforte chiusa :/ ottimo\n\n");
    else
        preleva->cifraContenuta -= sommaPrelevata;
}

void chiudi_cassaforte(struct Cassaforte *chiudi){
    FILE *fp = fopen(filename, "wb");

    // nel caso ci fossero problemi nell'apertura del file
    if (fp == NULL){
        perror("");
        exit(-1);
    }

    // numeri inseriti nel file con successo
    int numScritti = fwrite(chiudi, sizeof(struct Cassaforte), 1, fp);

    // controllo se c'è stato qualche problema durante la scrittura
    if (numScritti < 1){
        perror("");
        fclose(fp);
        exit(-1);
    }
    
    fclose(fp);

    chiudi -> stato = 0;
}