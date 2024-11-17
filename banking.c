#include <stdio.h>

int main(){
    int balance = 1000;
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int no_of_transactions = sizeof(transactions) / sizeof(transactions[0]);  
    int tobeprocessed[100];
    int tobeprocessed_count = 0;

    for (int i = 0; i < no_of_transactions; i++) {
        int transaction = transactions[i];
        
        if (transaction < 0 && -transaction > balance) {
            printf("Transaction %d is invalid (not enough money).\n", transaction);
            tobeprocessed[tobeprocessed_count++] = transaction;
            continue;
        }

        balance += transaction;

        // Stop processing further transactions if balance becomes zero
        if (balance == 0) {
            printf("No transactions will be processed from now.\n");
            tobeprocessed[tobeprocessed_count++] = transaction;  
            break;  
        }
    }

    printf("Final Balance: %d AED\n", balance);
    printf("Unprocessed Transactions:\n");
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
