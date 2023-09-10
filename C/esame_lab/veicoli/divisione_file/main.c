#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    Report report;

    initReport(&report);
    load_vehicles_from_file(&report, "input.txt");
    write_crimes_on_file(&report, "multe.txt");

    return 0;
}
