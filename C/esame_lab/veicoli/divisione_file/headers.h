#define maxPlateLenght 10

typedef struct{
    char plate[maxPlateLenght];
    float speed;
    float limit;
}Vehicle;

typedef struct node{
    Vehicle vehicle;
    struct node *next;
}Node;

typedef struct{
    Node *head;
}Report;

void initReport(Report *report);
int isReportEmpty(Report *report);
void pushVehicle(Report *report, Vehicle vehicle);
Vehicle popVehicle(Report *report);
void load_vehicles_from_file(Report *report, const char *filename);
int isCrime(Vehicle vehicle);
float calculateFine(float speedDiff);
void write_crimes_on_file(Report *report, const char *filename);
