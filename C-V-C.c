#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

// ------------------ Caesar Cipher ------------------
void caesarEncrypt(char *text, int shift) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
}

void caesarDecrypt(char *text, int shift) {
    caesarEncrypt(text, 26 - shift);
}

// ------------------ Vigenere Cipher ------------------
void vigenereEncrypt(char *text, char *key) {
    int i, j = 0;
    int keyLen = strlen(key);

    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base + shift) % 26 + base;
            j++;
        }
    }
}

void vigenereDecrypt(char *text, char *key) {
    int i, j = 0;
    int keyLen = strlen(key);

    for (i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            int shift = toupper(key[j % keyLen]) - 'A';
            char base = islower(text[i]) ? 'a' : 'A';
            text[i] = (text[i] - base - shift + 26) % 26 + base;
            j++;
        }
    }
}

// ------------------ Columnar Transposition ------------------
void columnarEncrypt(char *text, char *key, char *result) {
    int len = strlen(text);
    int col = strlen(key);
    int row = (len + col - 1) / col;

    char matrix[row][col];
    int k = 0;

    // Fill matrix row-wise
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (k < len)
                matrix[i][j] = text[k++];
            else
                matrix[i][j] = 'X';
        }
    }

    // Column order (simple sorted key)
    for (int k1 = 0; k1 < col; k1++) {
        for (int i = 0; i < col; i++) {
            if (key[i] == 'A' + k1) {
                for (int j = 0; j < row; j++) {
                    *result++ = matrix[j][i];
                }
            }
        }
    }
    *result = '\0';
}

// ------------------ MAIN ------------------
int main() {
    char text[MAX] = "Information security depends on confidentiality and integrity";
    char key1[] = "CYBER";
    char key2[] = "NETWORK";

    char step1[MAX], step2[MAX], step3[MAX];

    strcpy(step1, text);

    // Step 1: Caesar
    caesarEncrypt(step1, 5);
    printf("After Caesar: %s\n\n", step1);

    // Step 2: Vigenere
    strcpy(step2, step1);
    vigenereEncrypt(step2, key1);
    printf("After Vigenere: %s\n\n", step2);

    // Step 3: Columnar
    columnarEncrypt(step2, key2, step3);
    printf("After Columnar Transposition: %s\n\n", step3);

    // ------------------ Decryption ------------------
    char d1[MAX], d2[MAX];

    strcpy(d2, step2);
    vigenereDecrypt(d2, key1);
    printf("After Vigenere Decryption: %s\n\n", d2);

    caesarDecrypt(d2, 5);
    printf("Final Decrypted Text: %s\n\n", d2);

    return 0;
}