#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* const MONTH_NAMES[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

typedef struct {
    double sales; // e.g. 23458.01
    // sales should really be an integer number of cents
    size_t month; // 0..11
} salesMonth_t;

void printData( salesMonth_t* sales ) {
    // max month name is 9 characters + 2 padding spaces
    puts("Month      Sales\n");
    for ( size_t i = 0; i < 12; ++i ) {
        printf( "%-9s  $%.2lf\n", MONTH_NAMES[sales[i].month], sales[i].sales );
    }
}

void printMovingAverages( salesMonth_t* sales ) {
    size_t start = 0;
    size_t end = 5;
    double sum = 0;

    // set up+print initial range
    for ( size_t i = 0; i <= 5; ++i ) {
        sum += sales[i].sales;
    }
    printf("%-9s - %-9s  $%.2lf\n", MONTH_NAMES[start], MONTH_NAMES[end], sum/6);

    // compute the rest:
    while ( end < 11 ) {
        sum -= sales[start].sales;
        start++;
        end++;
        sum += sales[end].sales;
        printf("%-9s - %-9s  $%.2lf\n", MONTH_NAMES[start], MONTH_NAMES[end], sum/6);
    }
}

double computeSummary( salesMonth_t* sales, salesMonth_t* *out_min, salesMonth_t* *out_max ) {
    double sum = sales[0].sales;
    *out_min = &sales[0];
    *out_max = &sales[0];

    for ( size_t i = 1; i < 12; ++i ) {
        sum += sales[i].sales;
        if ( sales[i].sales < (*out_min)->sales ) {
            *out_min = &sales[i];
        }
        if ( sales[i].sales > (*out_max)->sales ) {
            *out_max = &sales[i];
        }
    }

    return sum/12;
}

// TODO: consider epsilon range for float equality?
int compareSalesHighToLow( const void* p1, const void* p2 ) {
    salesMonth_t* a = (salesMonth_t*)p1;
    salesMonth_t* b = (salesMonth_t*)p2;

    if ( a->sales > b->sales ) {
        return -1;
    } else if ( a->sales < b->sales ) {
        return 1;
    } else {
        return 0;
    }

    // TODO: make subtraction work here?
    // return (int)(b.sales - a.sales);
}

int main() {
    // TODO: verify `getline` alloc'd and read something!
    char* filename;
    size_t filename_size = 0;
    fputs("Please enter the name of the input file: ", stdout);
    getline( &filename, &filename_size, stdin );

    // strip trailing newline, if a line was properly read
    if ( filename[0] != '\0' ) {
        filename[strlen(filename) - 1] = '\0';
    }

    // read the input!
    FILE* inputFile = fopen(filename, "r");
    if ( inputFile == NULL ) {
        printf("Could not open file '%s' for reading.\n", filename);
        return 0;
    }

    // expected: 12 values with 2 digits after the decimal, one per line
    salesMonth_t sales[12];
    for ( size_t i = 0; i < 12; ++i ) {
        sales[i].month = i;
        int err = fscanf( inputFile, "%lf", &(sales[i].sales) );
        if ( err == 0 || err == EOF ) {
            printf("File '%s' has an invalid format!\n", filename);
            return 0;
        }
    }
    fclose(inputFile);
    free(filename);


    // process the data and print everything
    puts("\n\nMonthly sales report for 2023:\n");
    printData( sales );

    salesMonth_t *min, *max;
    double average = computeSummary( sales, &min, &max );
    puts("\n\nSales summary:\n");
    printf( "Minimum sales: $%.2lf (%s)\n", min->sales, MONTH_NAMES[min->month] );
    printf( "Maximum sales: $%.2lf (%s)\n", max->sales, MONTH_NAMES[max->month] );
    printf( "Average sales: $%.2lf\n", average );

    puts("\n\nSix-Month Moving Average Report:\n");
    printMovingAverages( sales );

    qsort( sales, 12, sizeof(salesMonth_t), compareSalesHighToLow );
    puts("\n\nSales Report (Highest to Lowest):\n");
    printData( sales );

    return 0;
}