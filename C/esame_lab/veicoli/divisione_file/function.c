#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initReport(Report *report){
    report->head = NULL;
}

int isReportEmpty(Report *report){
    return(report->head == NULL);
}

void pushVehicle(Report *report, Vehicle vehicle){
     Node *newnode = (Node*)malloc(sizeof(Node));

     newnode->vehicle = vehicle;
     newnode->next = report->head;
     report->head = newnode;
}

Vehicle popVehicle(Report *report){
    if(isReportEmpty(report)){
	Vehicle emptyvehicle;

	strcpy(emptyvehicle.plate, "");
	emptyvehicle.speed = 0.0;
	emptyvehicle.limit = 0.0;

	return emptyvehicle;
    }
    Node *topnode = report->head;
    Vehicle vehicle = topnode->vehicle;
    report->head = topnode->next;

    free(topnode);
    return vehicle;
}

void load_vehicles_from_file(Report *report, const char *filename){
    FILE *file = fopen(filename, "r");

    if(file == NULL){
	perror("");
	return;
    }

    char plate[maxPlateLenght];
    float speed, limit;

    while(fscanf(file, "%s %f %f", plate, &speed, &limit) == 3){
	Vehicle vehicle;

	strcpy(vehicle.plate, plate);
	vehicle.speed = speed;
	vehicle.limit = limit;

	pushVehicle(report, vehicle);
    }

    fclose(file);
}

int isCrime(Vehicle vehicle){
    float tolerance = vehicle.limit * 0.05;
    float maxspeed = vehicle.limit + tolerance;
    return(vehicle.speed > maxspeed);
}

float calculateFine(float speeddiff){
    if(speeddiff <= 10)
    	return 173.0;
    if(speeddiff <= 40)
    	return 695.0;
    if(speeddiff <= 60)
    	return 2170.0;
    else
    	return 3382.0;
}

void write_crimes_on_file(Report *report, const char *filename){
    FILE *file = fopen(filename, "w");

    if(file == NULL){
	perror("");
    }

    while(!isReportEmpty(report)){
	Vehicle vehicle = popVehicle(report);

	if(isCrime(vehicle)){
	    float speeddiff = vehicle.speed - vehicle.limit;
	    float fine = calculateFine(speeddiff);

	    fprintf(file, "%s %.1f %.1f\n", vehicle.plate, speeddiff, fine);
	}
    }
    fclose(file);
}

