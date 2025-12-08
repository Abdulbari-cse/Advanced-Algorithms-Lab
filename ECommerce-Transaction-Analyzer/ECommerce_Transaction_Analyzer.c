#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1024
#define MAX_DESC 256
#define MAX_COUNTRY 100

typedef struct {
    char InvoiceNo[50];
    char StockCode[50];
    char Description[MAX_DESC];
    int Quantity;
    char InvoiceDate[50];
    double UnitPrice;
    char CustomerID[50];
    char Country[MAX_COUNTRY];
} Transaction;

long long comparisons = 0, swapsCount = 0;
Transaction *data = NULL;
int dataSize = 0;
int isSortedByInvoice = 0; // Flag to track if sorted by InvoiceNo

/* =============== CSV PARSING =============== */
char** parseCSVLine(char *line, int *count) {
    char *fields = (char) malloc(10 * sizeof(char));
    *count = 0;
    char *start = line;
    char *end;

    while (*start != '\0' && *start != '\n' && *count < 10) {
        if (*start == '"') {
            start++;
            end = strstr(start, "\"");
            if (end == NULL) end = start + strlen(start);
        } else {
            end = strstr(start, ",");
        }

        if (end == NULL) end = start + strlen(start);
        
        int len = end - start;
        fields[count] = (char) malloc(len + 1);
        strncpy(fields[*count], start, len);
        fields[*count][len] = '\0';
        (*count)++;
        
        start = end;
        if (*start == '"') start++;
        if (*start == ',') start++;
    }
    return fields;
}

void loadCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[MAX_LINE];
    fgets(line, MAX_LINE, file); // skip header

    while (fgets(line, MAX_LINE, file)) {
        int count;
        char **fields = parseCSVLine(line, &count);
        if (count < 8) {
            for (int i = 0; i < count; i++) free(fields[i]);
            free(fields);
            continue;
        }

        data = (Transaction*) realloc(data, (dataSize + 1) * sizeof(Transaction));
        if (data == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        Transaction *t = &data[dataSize];

        strcpy(t->InvoiceNo, fields[0]);
        strcpy(t->StockCode, fields[1]);
        strcpy(t->Description, fields[2]);
        t->Quantity = atoi(fields[3]);
        strcpy(t->InvoiceDate, fields[4]);
        t->UnitPrice = atof(fields[5]);
        strcpy(t->CustomerID, fields[6]);
        strcpy(t->Country, fields[7]);

        dataSize++;

        for (int i = 0; i < count; i++) free(fields[i]);
        free(fields);
    }
    fclose(file);
    printf("Loaded %d records.\n", dataSize);
}

/* =============== DISPLAY =============== */
void display(int limit) {
    printf("Showing first %d records:\n", limit);
    for (int i = 0; i < limit && i < dataSize; i++) {
        printf("%s | %s | %d | %.2f | %s | %s\n",
               data[i].InvoiceNo, data[i].Description,
               data[i].Quantity, data[i].UnitPrice,
               data[i].CustomerID, data[i].Country);
    }
}

/* =============== COMPARISON =============== */
int compare(Transaction *a, Transaction *b, int column) {
    comparisons++;
    switch (column) {
        case 1: return strcmp(a->InvoiceNo, b->InvoiceNo);
        case 2: return strcmp(a->StockCode, b->StockCode);
        case 3: return strcmp(a->Description, b->Description);
        case 4: return a->Quantity - b->Quantity;
        case 5: return strcmp(a->InvoiceDate, b->InvoiceDate);
        case 6: return (a->UnitPrice > b->UnitPrice) - (a->UnitPrice < b->UnitPrice);
        case 7: return strcmp(a->CustomerID, b->CustomerID);
        case 8: return strcmp(a->Country, b->Country);
        default: return strcmp(a->InvoiceNo, b->InvoiceNo);
    }
}

/* =============== MERGE SORT =============== */
void merge(int l, int m, int r, int column) {
    int n1 = m - l + 1, n2 = r - m;
    Transaction L = (Transaction) malloc(n1 * sizeof(Transaction));
    Transaction R = (Transaction) malloc(n2 * sizeof(Transaction));
    for (int i = 0; i < n1; i++) L[i] = data[l+i];
    for (int j = 0; j < n2; j++) R[j] = data[m+1+j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (compare(&L[i], &R[j], column) <= 0) {
            data[k++] = L[i++];
        } else {
            data[k++] = R[j++];
        }
        swapsCount++;
    }
    while (i < n1) { data[k++] = L[i++]; swapsCount++; }
    while (j < n2) { data[k++] = R[j++]; swapsCount++; }

    free(L); free(R);
}

void mergeSort(int l, int r, int column) {
    if (l < r) {
        int m = l + (r-l)/2;
        mergeSort(l, m, column);
        mergeSort(m+1, r, column);
        merge(l, m, r, column);
    }
}

/* =============== QUICK SORT =============== */
void swap(Transaction *a, Transaction *b) {
    Transaction temp = *a;
    *a = *b;
    *b = temp;
    swapsCount++;
}

int partition(int low, int high, int column, int randomized) {
    if (randomized) {
        int randomPivot = low + rand() % (high-low+1);
        swap(&data[randomPivot], &data[high]);
    }
    Transaction pivot = data[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compare(&data[j], &pivot, column) <= 0) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[high]);
    return i + 1;
}

void quickSort(int low, int high, int column, int randomized) {
    if (low < high) {
        int pi = partition(low, high, column, randomized);
        quickSort(low, pi - 1, column, randomized);
        quickSort(pi + 1, high, column, randomized);
    }
}

/* =============== BINARY SEARCH =============== */
int binarySearch(const char *key) {
    if (!isSortedByInvoice) {
        printf("Warning: Data is not sorted by InvoiceNo! Binary search may fail.\n");
    }
    int l = 0, r = dataSize - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int cmp = strcmp(data[mid].InvoiceNo, key);
        if (cmp == 0) return mid;
        else if (cmp < 0) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

/* =============== SAVE CSV =============== */
void saveCSV(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error writing file!\n");
        return;
    }
    fprintf(file, "InvoiceNo,Stock Code,Description,Quantity,InvoiceDate,UnitPrice (GBP),CustomerID,Country\n");
    for (int i = 0; i < dataSize; i++) {
        fprintf(file, "%s,%s,\"%s\",%d,%s,%.2f,%s,%s\n",
                data[i].InvoiceNo, data[i].StockCode, data[i].Description,
                data[i].Quantity, data[i].InvoiceDate, data[i].UnitPrice,
                data[i].CustomerID, data[i].Country);
    }
    fclose(file);
    printf("Sorted data saved to %s\n", filename);
}

/* =============== MAIN MENU =============== */
int main() {
    srand(time(NULL));
    loadCSV("ecommerce_transiction.csv");
      
    int choice, column;
    while (1) {
        printf("\nMENU:\n");
        printf("1. Display records\n");
        printf("2. Merge Sort\n");
        printf("3. Quick Sort (pivot)\n");
        printf("4. Quick Sort (randomized)\n");
        printf("5. Binary Search by InvoiceNo\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            display(10);
        } else if (choice >= 2 && choice <= 4) {
            do {
                printf("Choose column (1=InvoiceNo,2=StockCode,3=Description,4=Quantity,5=InvoiceDate,6=UnitPrice,7=CustomerID,8=Country): ");
                scanf("%d", &column);
            } while (column < 1 || column > 8);

            comparisons = swapsCount = 0;
            if (choice == 2) mergeSort(0, dataSize - 1, column);
            else if (choice == 3) quickSort(0, dataSize - 1, column, 0);
            else quickSort(0, dataSize - 1, column, 1);

            printf("Sorting done. Comparisons=%lld, Swaps=%lld\n", comparisons, swapsCount);
            saveCSV("sorted_output.csv");
            isSortedByInvoice = (column == 1);
        } else if (choice == 5) {
            char key[50];
            printf("Enter InvoiceNo to search: ");
            scanf("%s", key);
            int idx = binarySearch(key);
            if (idx != -1) {
                printf("Found: %s | %s | %d | %.2f\n",
                       data[idx].InvoiceNo, data[idx].Description,
                       data[idx].Quantity, data[idx].UnitPrice);
            } else {
                printf("Not found!\n");
            }
        } else {
            break;
        }
    }
    free(data);
    return 0;
}
