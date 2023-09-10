#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLATE_LENGHT 10

typedef struct{
    char plate[MAX_PLATE_LENGHT];  // targa
    float speed;                   // velocità
    float limit;                   // limite di velocità
}Vehicle;                          // struct per il veicolo

typedef struct node{    // nodo della lista concatenata
    Vehicle vehicle;    // veicolo
    struct node *next;  // puntatore al prossimo nodo
}Node;                  // struct che contiene il nodo  

typedef struct{
    Node *head;  // puntatore alla testa della lista, scorrere la lista 
}Report;         // struct che contiene la lista concatenata dei veicoli

void initReport(Report *report){
    report->head = NULL;
}

int isReportEmpty(Report *report){
    return(report->head == NULL);
}

// inserisce il veicolo in testa alla lista (politica LIFO)
void pushVehicle(Report *report, Vehicle vehicle){
    Node *newNode = (Node*)malloc(sizeof(Node));  // allocazione dinamica del nodo

    if(newNode == NULL){
        perror("");
        return;
    }

    newNode->vehicle = vehicle; // inserimento del veicolo nel nodo 
    newNode->next = report->head; // inserimento del nodo nella lista concatenata, il prossimo nodo è la testa della lista
    report->head = newNode; // la testa della lista è il nuovo nodo 
}

// rimuove il veicolo dalla testa della lista
Vehicle popVehicle(Report *report){
    if (isReportEmpty(report)){ // se la lista è vuota ritorna un veicolo vuoto
        Vehicle emptyVehicle; // crea un veicolo vuoto

        strcpy(emptyVehicle.plate, ""); // copia la targa nel veicolo vuoto
        emptyVehicle.speed = 0.0; // velocità del veicolo vuoto
        emptyVehicle.limit = 0.0; // limite di velocità del veicolo vuoto

        return emptyVehicle; 
    }
    Node *topNode = report->head; // nodo in testa alla lista è il primo nodo
    Vehicle vehicle = topNode->vehicle; // veicolo in testa alla lista è il veicolo del primo nodo
    report->head = topNode->next; // la testa della lista è il prossimo nodo

    free(topNode);
    return vehicle;
}

void load_vehicles_from_file(Report *report, const char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL){
        perror("");
        return;
    }

    char plate[MAX_PLATE_LENGHT];
    float speed, limit; // dichiaro questi così da poterli passare alla funzione fscanf

    while (fscanf(file, "%s %f %f", plate, &speed, &limit) == 3){ // Legge una riga del file e controlla che ci siano 3 valori
        Vehicle vehicle; // Crea un nuovo veicolo
 
        strcpy(vehicle.plate, plate); // Copia la targa nel veicolo appena creato
        vehicle.speed = speed; // Copia la velocità nel veicolo appena creato
        vehicle.limit = limit; // Copia il limite di velocità nel veicolo appena creato

        pushVehicle(report, vehicle); // Aggiunge il veicolo alla fine dell'array
    }
    fclose(file);
}

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

void write_crimes_on_file(Report *report, const char *filename){
    FILE *file = fopen(filename, "w");

    if (file == NULL){
        perror("");
        return;
    }

    while (!isReportEmpty(report)){
        Vehicle vehicle =  popVehicle(report);

        if (isCrime(vehicle)){
            float speedDiff = vehicle.speed - vehicle.limit; // Differenza tra la velocità del veicolo e il limite di velocità
            float fine = calculateFine(speedDiff); // Calcola la multa
            
            fprintf(file, "%s %.1f %.1f\n", vehicle.plate, speedDiff, fine);
        }
    }
    fclose(file);
}

int main(){
    Report report;

    initReport(&report);
    load_vehicles_from_file(&report, "input.txt");
    write_crimes_on_file(&report, "output.txt");

    return 0;
}