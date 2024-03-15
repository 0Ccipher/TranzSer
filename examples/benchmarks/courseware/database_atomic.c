#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>
// #include <genmc.h>

// Define constants
#define MAX_TABLE_SIZE 15
#define MAX_ROWS 15
#define MAX_STR_SIZE 100
#define MAX_TABLES 10

#define SC memory_order_seq_cst

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
   _Atomic(Table *) tables[MAX_TABLES];
   _Atomic(int) size;
} Database;

// Define global database instance
Database database;

static Table *new_table()
{
	return malloc(sizeof(Table));
}

// Define database functions
void initDatabase() {
    atomic_init(&database.size , 0);
}

void initWritetoTable(Table *gtable,char * table, int rowIndex, char *row, char *value) {
    // printf("WRITE TABLE : %p , %d , %s \n",gtable , rowIndex , value);
    Table * currentTable = gtable;

    currentTable->rows[rowIndex].row = strdup(row);
    currentTable->rows[rowIndex].table = strdup(table);
    currentTable->size++;
    
    // strcpy(currentTable->rows[rowIndex].value, value);
    currentTable->rows[rowIndex].value = strdup(value);
}

void writetoTable(int tableIndex,char * table, char *row, char *value) {
    // printf("WRITE TABLE : %p , %d , %s \n",gtable , rowIndex , value);
    Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
    if (currentTable == NULL) return ;
    int rowIndex = -1;
    for (int i = 0; i < currentTable->size; i++) {
        if(currentTable->rows[i].row == NULL) continue;
        if (strcmp(currentTable->rows[i].row, row) == 0) {
            rowIndex = i;
            break;
        }
    }
    if (rowIndex == -1) {
        rowIndex = currentTable->size;
        currentTable->rows[rowIndex].row = strdup(row);
        currentTable->rows[rowIndex].table = strdup(table);
        currentTable->size++;
    }
    
    // strcpy(currentTable->rows[rowIndex].value, value);
    currentTable->rows[rowIndex].value = strdup(value);
    atomic_store_explicit(&database.tables[tableIndex], currentTable, SC);
}


char *readRowFromTable(int tableIndex, char * table , char *row) {
    Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
     if (currentTable == NULL) return NULL;
        for (int j = 0; j < currentTable->size; j++) {
            if(currentTable->rows[j].row == NULL) continue;
            if (strcmp(currentTable->rows[j].row, row) == 0) {
                char * value = strdup(currentTable->rows[j].value);
                return value;
            }
        }
    
    return NULL;
}

bool deleteRowFromTable(int tableIndex, char * table , char *row) {
    Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
     if (currentTable == NULL) return false;
    int rowIndex = -1;
    for (int i = 0; i < currentTable->size; i++) {
        if(currentTable->rows[i].row == NULL) continue;
        if (strncmp(currentTable->rows[i].row, row , strlen(row)) == 0) {
            rowIndex = i;
             printf("Deleting- %d :row %s \n",tableIndex ,currentTable->rows[i].row);
            break;
        }
    }

    if (rowIndex == -1) {
        printf("Table : %d Row not found\n",tableIndex);
        return false;
    }

    for (int i = rowIndex; i < currentTable->size - 1; i++) {
        currentTable->rows[i] = currentTable->rows[i + 1];
    }

    currentTable->size--;
    atomic_store_explicit(&database.tables[tableIndex], currentTable, SC);
    return true;
}

static Table *getAllRows(int tableIndex) {
    Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
    return currentTable;
}

static char **readIfIDStartsWith(int tableIndex , char *table, char *row) {
    Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
     if (currentTable == NULL) return NULL;
    char **rows = malloc(MAX_ROWS * sizeof(char *));
    if (rows == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    int rowcount = -1;
    for (int i = 0; i < currentTable->size; i++) {
        if(currentTable->rows[i].row == NULL) continue;
        if (strncmp(currentTable->rows[i].row, row,strlen(row)) == 0) {
            rowcount++;
            rows[rowcount] = strdup(currentTable->rows[i].value);
            if (rows[rowcount] == NULL) {
                printf("Memory allocation failed\n");
                return NULL;
            }
        }
    }
    if(rowcount == -1) return NULL;
    return rows;
}

int countIfIDStartsWith(int tableIndex , char *table, char *row) {
    Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
    if (currentTable == NULL) return -1;

    int rowcount = 0;
    for (int i = 0; i < currentTable->size; i++) {
        if(currentTable->rows[i].row == NULL) continue;
        if (strncmp(currentTable->rows[i].row, row,strlen(row)) == 0) {
            rowcount++;
        }
    }

    return rowcount;
}



// void write(char *table, char *row, char *value) {
//     printf("WRITE TABLE : %s , %s , %s \n",table , row , value);
//     int tableIndex = -1;
//     for (int i = 0; i < atomic_load_explicit(&database.size, SC); i++) {
//         Table * currentTable = atomic_load_explicit(&database.tables[i], SC);
//         if (strcmp(currentTable->rows[0].table, table) == 0) {
//             tableIndex = i;
//             break;
//         }
//     }
//     Table * currentTable;
//     if (tableIndex == -1) {
//         printf("Create TABLE : %s \n",table);
//         tableIndex = atomic_fetch_add_explicit(&database.size, 1, SC);
//         // atomic_store_explicit(&database.tables[tableIndex] , new_table() ,SC);
//         currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
//         // strcpy(currentTable->rows[0].table,table);
//         currentTable->rows[0].table = strdup(table);
//         currentTable->size = 0;
//     }
//     else{
//         currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
//     }

//     int rowIndex = -1;
//     for (int i = 0; i < currentTable->size; i++) {
//         if (strcmp(currentTable->rows[i].row, row) == 0) {
//             rowIndex = i;
//             break;
//         }
//     }

//     if (rowIndex == -1) {
//         rowIndex = currentTable->size;
//         // strcpy(currentTable->rows[rowIndex].row, row);
//         // strcpy(currentTable->rows[rowIndex].table, table);
//         currentTable->rows[rowIndex].row = strdup(row);
//         currentTable->rows[rowIndex].table = strdup(table);
//         currentTable->size++;
//     }
//     // strcpy(currentTable->rows[rowIndex].value, value);
//     currentTable->rows[rowIndex].value = strdup(value);
//     atomic_store_explicit(&database.tables[tableIndex], currentTable, SC);
// }

// char *read(char *table, char *row) {
//     for (int i = 0; i < atomic_load_explicit(&database.size, SC); i++) {
//         Table * currentTable = atomic_load_explicit(&database.tables[i], SC);
//         if (strcmp(currentTable->rows[0].table, table) == 0) {
//             for (int j = 0; j < currentTable->size; j++) {
//                 if (strcmp(currentTable->rows[j].row, row) == 0) {
//                     char * value = strdup(currentTable->rows[j].value);
//                     return value;
//                 }
//             }
//             break;
//         }
//     }

//     return NULL;
// }

// bool deleteRow(char *table, char *row) {
//     int tableIndex = -1;
//     for (int i = 0; i < atomic_load_explicit(&database.size, SC); i++) {
//         Table * currentTable = atomic_load_explicit(&database.tables[i], SC);
//         if (strcmp(currentTable->rows[0].table, table) == 0) {
//             tableIndex = i;
//             break;
//         }
//     }

//    if (tableIndex == -1) {
//         printf("Err : Table not found\n");
//         return false;
//     }

//     Table * currentTable = atomic_load_explicit(&database.tables[tableIndex], SC);
//     int rowIndex = -1;
//     for (int i = 0; i < currentTable->size; i++) {
//         if (strncmp(currentTable->rows[i].row, row , strlen(row)) == 0) {
//             rowIndex = i;
//             break;
//         }
//     }

//     if (rowIndex == -1) {
//         printf("Row not found\n");
//         return false;
//     }

//     for (int i = rowIndex; i < currentTable->size - 1; i++) {
//         currentTable->rows[i] = currentTable->rows[i + 1];
//     }

//     currentTable->size--;
//     atomic_store_explicit(&database.tables[tableIndex], currentTable, SC);
//     return true;
// }

// static Table *getAllRows(char *table) {
//     printf("DB Size : %d\n",atomic_load_explicit(&database.size, SC));
//     int tableIndex = -1;
//     for (int i = 0; i < atomic_load_explicit(&database.size, SC); i++) {
//         Table * currentTable = atomic_load_explicit(&database.tables[i], SC);
//         if (strcmp(currentTable->rows[0].table, table) == 0) {
//             tableIndex = i;
//             break;
//         }
//     }

//     if (tableIndex == -1) {
//         printf("Err : Table not found %s\n", table);
//         return NULL;
//     }
//     Table * t = atomic_load_explicit(&database.tables[tableIndex],SC);
//     return t;
// }

// char **readIfIDStartsWith(char *table, char *row) {
//     Table *currentTable = getAllRows(table);
//     if (currentTable == NULL) return NULL;

//     char **rows = malloc(MAX_ROWS * sizeof(char *));
//     if (rows == NULL) {
//         printf("Memory allocation failed\n");
//         return NULL;
//     }

//     int rowcount = -1;
//     for (int i = 0; i < currentTable->size; i++) {
//         if (strncmp(currentTable->rows[i].row, row,strlen(row)) == 0) {
//             rowcount++;
//             rows[rowcount] = strdup(currentTable->rows[i].value);
//             if (rows[rowcount] == NULL) {
//                 printf("Memory allocation failed\n");
//                 return NULL;
//             }
//         }
//     }

//     return rows;
// }

// char **readIfIDEquals(char *table, char *row) {
//     Table *currentTable = getAllRows(table);
//     if (currentTable == NULL) return NULL;

//     char **rows = malloc(MAX_ROWS * sizeof(char *));
//     if (rows == NULL) {
//         printf("Memory allocation failed\n");
//         return NULL;
//     }

//     int rowcount = -1;
//     for (int i = 0; i < currentTable->size; i++) {
//         if (strcmp(currentTable->rows[i].row, row) == 0) {
//             rowcount++;
//             rows[rowcount] = strdup(currentTable->rows[i].value);
//             if (rows[rowcount] == NULL) {
//                 printf("Memory allocation failed\n");
//                 return NULL;
//             }
//         }
//     }

//     return rows;
// }

// int countIfIDStartsWith(char *table, char *row) {
//     Table *currentTable = getAllRows(table);
//     if (currentTable == NULL) return -1;

//     int rowcount = 0;
//     for (int i = 0; i < currentTable->size; i++) {
//         if (strncmp(currentTable->rows[i].row, row,strlen(row)) == 0) {
//             rowcount++;
//         }
//     }

//     return rowcount;
// }

// int countIfIDEquals(char *table, char *row) {
//     Table *currentTable = getAllRows(table);
//     if (currentTable == NULL) return -1;

//     int rowcount = -1;
//     for (int i = 0; i < currentTable->size; i++) {
//         if (strcmp(currentTable->rows[i].row, row) == 0) {
//             rowcount++;
//         }
//     }

//     return rowcount;
// }