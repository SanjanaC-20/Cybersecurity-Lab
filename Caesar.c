#include <stdio.h>

int main() {
    char text[200];
    int shift, choice;

    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter shift key: ");
    scanf("%d", &shift);

    switch (choice) {

        case 1: 
            for (int i = 0; text[i] != '\0'; i++) {
                if (text[i] >= 'A' && text[i] <= 'Z') {
                    text[i] = (text[i] - 'A' + shift) % 26 + 'A';
                }
                else if (text[i] >= 'a' && text[i] <= 'z') {
                    text[i] = (text[i] - 'a' + shift) % 26 + 'a';
                }
            }
            printf("\nEncrypted text: %s", text);
            break;

        case 2: 
            for (int i = 0; text[i] != '\0'; i++) {
                if (text[i] >= 'A' && text[i] <= 'Z') {
                    text[i] = (text[i] - 'A' - shift + 26) % 26 + 'A';
                }
                else if (text[i] >= 'a' && text[i] <= 'z') {
                    text[i] = (text[i] - 'a' - shift + 26) % 26 + 'a';
                }
            }
            printf("\nDecrypted text: %s", text);
            break;

        default:
            printf("\nInvalid choice!");
    }

    return 0;
}