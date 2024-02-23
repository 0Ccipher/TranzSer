#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_TABLE_SIZE 100
#define MAX_ROW_SIZE 100
#define MAX_VALUE_SIZE 100
#define MAX_TABLES 10

// Define data structures
typedef struct {
    char table[MAX_TABLE_SIZE];
    char row[MAX_ROW_SIZE];
    char value[MAX_VALUE_SIZE];
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
        strcpy(database.tables[tableIndex].rows[0].table, table);
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
        strcpy(currentTable->rows[rowIndex].row, row);
        currentTable->size++;
    }

    // Write value to row
    strcpy(currentTable->rows[rowIndex].value, value);
}

char* read(char *table, char *row) {
    // Find table in database
    for (int i = 0; i < database.size; i++) {
        if (strcmp(database.tables[i].rows[0].table, table) == 0) {
            // Find row in table
            Table *currentTable = &database.tables[i];
            for (int j = 0; j < currentTable->size; j++) {
                if (strcmp(currentTable->rows[j].row, row) == 0) {
                    // Return value
                    return currentTable->rows[j].value;
                }
            }
            break;
        }
    }

    return NULL;
}

// Add other database functions as needed

int main() {
    initDatabase();

    write("table1", "row1", "value1");
    write("table1", "row2", "value2");

    printf("%s\n", read("table1", "row1"));
    printf("%s\n", read("table1", "row2"));

    return 0;
}
