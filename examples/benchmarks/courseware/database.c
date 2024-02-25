#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define constants
#define MAX_TABLE_SIZE 20
#define MAX_ROWS 20
#define MAX_STR_SIZE 100
#define MAX_TABLES 10

// Define data structures
typedef struct {
    char *table;
    char *row;
    char *value;
} DatabaseRow;

typedef struct {
    DatabaseRow rows[MAX_TABLE_SIZE];
    int size;
} Table;

typedef struct {
    Table tables[MAX_TABLES];
    int size;
} Database;

// Define global database instance
Database database;

// Define database functions
void initDatabase() {
    database.size = 0;
}

void write(char *table, char *row, char *value) {
    // Find table in database
    int tableIndex = -1;
    for (int i = 0; i < database.size; i++) {
        if (strcmp(database.tables[i].rows[0].table, table) == 0) {
            tableIndex = i;
            break;
        }
    }

    // If table does not exist, create it
    if (tableIndex == -1) {
        tableIndex = database.size;
        // strcpy(database.tables[tableIndex].rows[0].table, table);
        database.tables[tableIndex].rows[0].table = strdup(table);
        database.tables[tableIndex].size = 0;
        database.size++;
    }

    // Find row in table
    Table *currentTable = &database.tables[tableIndex];
    int rowIndex = -1;
    for (int i = 0; i < currentTable->size; i++) {
        if (strcmp(currentTable->rows[i].row, row) == 0) {
            rowIndex = i;
            break;
        }
    }

    // If row does not exist, create it
    if (rowIndex == -1) {
        rowIndex = currentTable->size;
        // strcpy(currentTable->rows[rowIndex].row, row);
        currentTable->rows[rowIndex].row = strdup(row);
         currentTable->rows[rowIndex].table = strdup(table);
        currentTable->size++;
    }

    // Write value to row
    // strcpy(currentTable->rows[rowIndex].value, value);
    currentTable->rows[rowIndex].value = strdup(value);
}

char* read(char *table, char *row) {
    char * value;
    // Find table in database
    for (int i = 0; i < database.size; i++) {
        if (strcmp(database.tables[i].rows[0].table, table) == 0) {
            // Find row in table
            Table *currentTable = &database.tables[i];
            for (int j = 0; j < currentTable->size; j++) {
                if (strcmp(currentTable->rows[j].row, row) == 0) {
                    // Return value
                    value = strdup(currentTable->rows[j].value);
                    return value;
                }
            }
            break;
        }
    }

    return NULL;
}


bool deleteRow(char *table, char *row) {
    // Find table in database
    int tableIndex = -1;
    for (int i = 0; i < database.size; i++) {
        if (strcmp(database.tables[i].rows[0].table, table) == 0) {
            tableIndex = i;
            break;
        }
    }

    // If table does not exist, return
    if (tableIndex == -1) {
        printf("Err : Table not found\n");
        return false;
    }

    // Find row in table
    Table *currentTable = &database.tables[tableIndex];
    int rowIndex = -1;
    for (int i = 0; i < currentTable->size; i++) {
        if (strcmp(currentTable->rows[i].row, row) == 0) {
            rowIndex = i;
            break;
        }
    }

    // If row does not exist, return
    if (rowIndex == -1) {
        printf("Row not found\n");
        return false;
    }

    // Free memory for row and shift rows
    // free(currentTable->rows[rowIndex].row);
    // free(currentTable->rows[rowIndex].value);
    for (int i = rowIndex; i < currentTable->size - 1; i++) {
        currentTable->rows[i] = currentTable->rows[i + 1];
    }

    // Decrement table size
    currentTable->size--;
    return true;
}

Table * getAllRows(char *table) {
    // Find table in database
    int tableIndex = -1;
    for (int i = 0; i < database.size; i++) {
        if (strcmp(database.tables[i].rows[0].table, table) == 0) {
            tableIndex = i;
            break;
        }
    }

    // If table does not exist, return
    if (tableIndex == -1) {
        printf("Err : Table not found %s\n",table);
        return NULL;
    }

    // Return all rows in table
    Table *currentTable = &database.tables[tableIndex];
    return currentTable;
}

char ** readIfIDStartsWith(char *table , char *row){
    Table * currentTable = getAllRows(table);
    char ** rows = malloc(MAX_ROWS * sizeof(char *));
    int rowcount = -1;
    if(currentTable == NULL) return NULL;
    for (int i = 0; i < currentTable->size; i++) {
       if(strcmp(currentTable->rows[i].row , row) == 0){
            rowcount++;
            rows[rowcount] = strdup(currentTable->rows[i].value);
       }
    }
    return rows;
}

int countIfIDStartsWith(char *table , char *row){
    Table * currentTable = getAllRows(table);
    if(currentTable == NULL) return -1;
    int rowcount = -1;
    for (int i = 0; i < currentTable->size; i++) {
       if(strcmp(currentTable->rows[i].row , row) == 0){
            rowcount++;
       }
    }
    return rowcount;
}

