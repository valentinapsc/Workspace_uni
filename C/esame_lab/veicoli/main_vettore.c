#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLATE_LENGTH 10  // Lunghezza massima della targa

typedef struct {
    char plate[MAX_PLATE_LENGTH];
    float speed;  // Velocità del veicolo
    float limit;  // Limite di velocità
} Vehicle;        // Struttura dati per contenere i dati di un veicolo

typedef struct {
    Vehicle *data;  // Array dinamico di veicoli
    // int capacity;   // Capacità dell'array
    int size;       // Numero di veicoli nell'array
} Report;           // Struttura dati per contenere i veicoli

/*
La funzione initReport inizializza la struttura dati Report con una capacità
specificata per l'array dinamico data.

Se il numero di veicoli nel file di input supera la capacità iniziale, l'array verrà
ridimensionato dinamicamente per adattarsi al numero effettivo di veicoli

L'impostazione di una capacità iniziale può essere utile per ottimizzare
l'allocazione della memoria e ridurre il numero di ridimensionamenti dell'array.
Tuttavia, l'array può crescere dinamicamente grazie alla realloc all'interno della funzione
pushReport
*/

void initReport(Report *report/*, int capacity*/) {
    report->data = NULL;
    // report->capacity = capacity;
    report->size = 0;
}

/*
* La funzione pushReport aggiunge un veicolo alla fine dell'array dinamico data.
* ogni volta che viene aggiunto un veicolo, la dimensione dell'array viene incrementata 
* di 1 e di conseguenza viene riallocata la memoria 
*/
void pushReport(Report *report, Vehicle veicolo) {
    if(report->size == 0){
        Vehicle* veicolo = (Vehicle*)malloc(sizeof(Vehicle));
        report->data = veicolo;
    } else{
        report->data = (Vehicle *)realloc(report->data, (report->size+1) * sizeof(Vehicle));
    }

    strcpy((*(report->data + report->size)).plate, veicolo.plate);
    (*(report->data + report->size)).limit = veicolo.limit;
    (*(report->data + report->size)).speed = veicolo.speed;

    report->size++;


    /*if (report->size == report->capacity) {
        report->capacity *= 2;
        report->data = (Vehicle *)realloc(report->data, report->capacity * sizeof(Vehicle));
    }
    report->data[report->size++] = vehicle;*/

    /*if (report->size == report->capacity) { // se il vettore è pieno
        report->capacity += 1; // aumento la capacità di 1 così da poter aggiungere un nuovo veicolo 
        report->data = (Vehicle *)realloc(report->data, report->capacity * sizeof(Vehicle)); // rialloco la memoria
    }

    strcpy(report->data[report->size].plate, veicolo.plate); // copio la targa nel vettore
    report->data[report->size].limit = veicolo.limit; // copio il limite di velocità nel vettore
    report->data[report->size].speed = veicolo.speed; // copio la velocità nel vettore

    report->size++; // aumento il numero di veicoli nel vettore*/
}

// Legge i veicoli dal file e li aggiunge all'array
void loadVehiclesFromFile(Report *report, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Errore durante l'apertura del file\n");
        return;
    }

    char plate[MAX_PLATE_LENGTH];
    float speed, limit;

    while (fscanf(file, "%s %f %f", plate, &speed, &limit) == 3) { // Legge una riga del file e controlla che ci siano 3 valori
        Vehicle vehicle; // Crea un nuovo veicolo

        strcpy(vehicle.plate, plate); // Copia la targa nel veicolo appena creato
        vehicle.speed = speed; 
        vehicle.limit = limit;
        pushReport(report, vehicle); // Aggiunge il veicolo alla fine dell'array
    }

    fclose(file);
}

// Ritorna 1 se il veicolo ha superato il limite di velocità, 0 altrimenti
int isCrime(Vehicle vehicle) {
    float tolerance = vehicle.limit * 0.05; // Tolleranza del 5% sul limite di velocità 
    float maxLimit = vehicle.limit + tolerance; // Limite di velocità massimo 
    return (vehicle.speed > maxLimit); 
}

// Calcola la multa in base alla differenza tra la velocità del veicolo e il limite di velocità
float calculateFine(float speedDiff) {
    if (speedDiff <= 10)
        return 173.0;
    else if (speedDiff <= 40)
        return 695.0;
    else if (speedDiff <= 60)
        return 2170.0;
    else
        return 3382.0;
}

// Scrive le multe sul file
void writeCrimesOnFile(Report *report, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Errore durante l'apertura del file\n");
        return;
    }

    for (int i = 0; i < report->size; i++) {
        if (isCrime(report->data[i])) {
            float speedDiff = report->data[i].speed - report->data[i].limit; // Differenza tra la velocità del veicolo e il limite di velocità
            float fine = calculateFine(speedDiff); // Calcola la multa

            fprintf(file, "%s %.1f %.1f\n", report->data[i].plate, speedDiff, fine); // Scrive la targa, la differenza di velocità e la multa sul file
        }
    }

    fclose(file);
}

// Dealloca la memoria dell'array dinamico
void cleanupReport(Report *report) {
    free(report->data);
    report->data = NULL;
    // report->capacity = 0;
    report->size = 0;
}

int main() {
    Report report;
    initReport(&report/*, 10*/);

    loadVehiclesFromFile(&report, "input.txt");
    writeCrimesOnFile(&report, "output.txt");

    cleanupReport(&report);

    return 0;
}