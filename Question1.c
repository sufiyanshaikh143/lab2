#include <stdio.h>
#include <stdbool.h>

#define SIZE 5
#define nRows 2
#define nCols 3

void print_array(int array[], int length); 
void print_matrix(int mat[], int rows, int cols); 
bool isValid(int length, int pos); 
void remove_element(int arr[], int *length, int pos); 
void insert_element(int arr[], int *length, int pos, int value); 
void reshape(int arr[], int length, int arr2d[nRows][nCols]); 
void trans_matrix(int arr2d[nRows][nCols], int matT[nCols][nRows]); 
bool found_duplicate(int arr[], int length); 

bool isValid(int length, int pos) {
    return (pos >= 0 && pos < length);
}

void remove_element(int arr[], int *length, int pos) {
    if (isValid(*length, pos)) {
        for (int i = pos; i < *length - 1; i++) {
            arr[i] = arr[i + 1];
        }
        (*length)--;  
    } else {
        printf("Error: Position %d is out of bounds\n", pos);
    }
}

void insert_element(int arr[], int *length, int pos, int value) {
    if (isValid(*length + 1, pos)) {
        for (int i = *length; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = value;
        (*length)++;  
    } else {
        printf("Error: Position %d is out of bounds\n", pos);
    }
}

void print_array(int array[], int length){
   for (int i = 0; i < length; i++) {
      printf("array[%d] = %d\n", i, array[i]);
   }
}

void print_matrix(int mat[], int rows, int cols){
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           printf("mat[%d][%d] = %d ", i, j, mat[i * cols + j]);
       }
       printf("\n");
   }
}

void reshape(int arr[], int length, int arr2d[nRows][nCols]) {
    if (length == (nRows * nCols)) {
        int position = 0;
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                arr2d[i][j] = arr[position++];
            }
        }
    } else {
        printf("Error: Array length does not match the product of rows and columns of the 2D array.\n");
    }
}

void trans_matrix(int arr2d[nRows][nCols], int matT[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            matT[j][i] = arr2d[i][j];
        }
    }
}

bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50}; 
    int length = SIZE; 

    printf("Original array:\n");
    print_array(arr, length);

    printf("\nRemoving element at position 2:\n");
    remove_element(arr, &length, 2);
    print_array(arr, length);

    printf("\nInserting 80 at position 2:\n");
    insert_element(arr, &length, 2, 80);
    print_array(arr, length);

    int arr1D[] = {1, 2, 3, 4, 5, 6}; 
    int arr2d[2][3]; 
    printf("\nReshaping 1D array to 2x3 2D array:\n");
    reshape(arr1D, 6, arr2d);
    print_matrix((int*)arr2d, nRows, nCols); 

    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}}; 
    int matT[3][2]; 
    printf("\nTransposing 2x3 matrix:\n");
    trans_matrix(mat, matT);
    print_matrix((int*)matT, nCols, nRows); 

    printf("\nChecking for duplicates in the original array:\n");
    bool hasDuplicate = found_duplicate(arr, length);
    if (hasDuplicate) {
        printf("Duplicate found\n");
    } else {
        printf("No duplicate found\n");
    }

    return 0;
}
