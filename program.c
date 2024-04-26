#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fptr;

void printReport(char* months[], float sales[]) {
    printf("Monthly sales report for 2023:\n");
    printf("Month\t\tSales\n");

    for (int i = 0; i < 12; i++) {
        if (strlen(months[i]) < 8) {
            printf("%s\t\t$%0.2f\n", months[i], sales[i]);
        } else {
            printf("%s\t$%0.2f\n", months[i], sales[i]);
        }
    }
    printf("\n");
}

void printSummary(char* months[], float sales[]) {
    int minIndex = 0;
    int maxIndex = 0;
    float average = sales[0];
    for (int i = 1; i < 12; i++) {
        if (sales[i] < sales[minIndex]) {
            minIndex = i;
        } else if (sales[i] > sales[maxIndex]) {
            maxIndex = i;
        }
        average += sales[i];
    }
    average /= 12;

    printf("Sales summary:\n");
    printf("Mininum sales:\t$%0.2f\t(%s)\n", sales[minIndex], months[minIndex]);
    printf("Maximum sales:\t$%0.2f\t(%s)\n", sales[maxIndex], months[maxIndex]);
    printf("Average sales:\t$%0.2f\n\n", average);
}

void printSixMonthReport(char* months[], float sales[]) {
    printf("Six-Month Moving Average Report:\n");
    float average = 0;

    for (int i = 0; i <= 6; i++) {
        for (int j = i; j < i + 6; j++) {
            average += sales[j];
        }
        average /= 6;

        if (strlen(months[i]) < 8) {
            if (strlen(months[i+5]) <8) {
                printf("%s\t\t-\t%s\t\t$%0.2f\n", months[i], months[i+5], average);
            } else {
                printf("%s\t\t-\t%s\t$%0.2f\n", months[i], months[i+5], average);

            }
        }
        else {
            if (strlen(months[i+5]) < 8) {
                printf("%s\t-\t%s\t\t$%0.2f\n", months[i], months[i+5], average);
            } else {
                printf("%s\t-\t%s\t$%0.2f\n", months[i], months[i+5], average);
            }
        }
        average = 0;
    }
    printf("\n");
}

void printHighToLow(char* months[], float sales[]) {
    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");

    float tempSales;
    char* tempMonth;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 11-i; j++) {
            if (sales[j] < sales[j + 1]) {
                tempSales = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = tempSales;

                tempMonth = months[j];
                months[j] = months[j + 1];
                months[j + 1] = tempMonth;
            }
        }
    }

    for (int i = 0; i < 12; i++) {
        if (strlen(months[i]) < 8) {
            printf("%s\t\t$%0.2f\n", months[i], sales[i]);
        } else {
            printf("%s\t$0.2f\n", months[i], sales[i]);
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: ./sales INPUT_FILE\n");
        exit(0);
    }

    char fileString[100];
    float salesValues[12];
    int currentMonth = 0;

    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Not able to open the file.");
        fclose(fptr);
        exit(0);
    }

    while(fgets(fileString, 100, fptr)) {
        salesValues[currentMonth] = (float) atof(fileString);
        memset(fileString, 0, 100);
        currentMonth++;
    }
    fclose(fptr);

    char* salesMonths[] = {
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
    };

    printReport(salesMonths, salesValues);
    printSummary(salesMonths, salesValues);
    printSixMonthReport(salesMonths, salesValues);
    printHighToLow(salesMonths, salesValues);
    return 0;
}