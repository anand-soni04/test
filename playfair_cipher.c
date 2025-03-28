#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char key[] = "Parul";
char matrix[SIZE][SIZE];
void preparematrix(char *x) {
    int used[26] = {0};
    used['J' - 'A'] = 1; // J and I share the same slot in the Playfair matrix
    int index = 0;
    for (int i = 0; x[i] != '\0'; i++) {
        char ch = toupper(x[i]);
        if (!used[ch - 'A'] && isalpha(ch)) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            matrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
}
void displayMatrix() {
    printf("Playfair Cipher Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}
void FindPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';  // J and I are treated as the same character
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void decryptplayfair(char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int i = 0;
    if (len % 2 != 0) {
        ciphertext[len] = 'X';
        ciphertext[len + 1] = '\0';
        len++;
    }
    for (i = 0; i < len; i += 2) {
        char a = toupper(ciphertext[i]);
        char b = toupper(ciphertext[i + 1]);
        int row1, col1, row2, col2;
        FindPosition(a, &row1, &col1);
        FindPosition(b, &row2, &col2);
        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            plaintext[i + 1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        }
        else if (col1 == col2) {
            plaintext[i] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            plaintext[i + 1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        }
        else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}
int main() {
    char ciphertext[100];
    char plaintext[100];
    printf("Enter the ciphertext: ");
    scanf("%s", ciphertext);
    preparematrix(key);
    displayMatrix();
    decryptplayfair(ciphertext, plaintext);
    printf("Encrypted plaintext: %s\n", plaintext);
    return 0;
}