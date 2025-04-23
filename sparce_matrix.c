#include <stdio.h>
#include <stdlib.h>
struct sparce {
    int non_rows;
    int non_cols;
    int non_zero_val;
    int total;
} sp[100];

void inputMatrix(int matrix[100][100], int *rows, int *cols) {
    printf("Enter the number of rows and columns: ");
    scanf("%d", rows);
    scanf("%d", cols);

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display_matrix(){
    
}

void toSparseMatrix(int matrix[100][100],int rows, int cols) {
    struct sparce sp[100];
    int row_no[100],col_no[100],z=1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sp[z].non_rows = i;
                sp[z].non_cols = j;
                sp[z].non_zero_val = matrix[i][j];
                z=z+1;
            }
        }
    }
    sp[0].total = z-1;
}

void printSparseMatrix(int rows,int cols) {
    struct sparce sp[100];
    printf("Sparce Matrix:\n");
    printf("%d\t\t",rows);
    printf("%d\t\t",cols);
    printf("%d\t\t\n",sp[0].total);
    for(int i = 1;i<=sp[0].total;i++){
        printf("%d\t\t%d\t\t%d\n",sp[i].non_rows,sp[i].non_cols,sp[i].non_zero_val);
    }
}

int main() {
    int matrix[100][100];
    int rows, cols;

    inputMatrix(matrix, &rows, &cols);

    toSparseMatrix(matrix, rows ,cols);

    printSparseMatrix(rows,cols);

    return 0;
}
