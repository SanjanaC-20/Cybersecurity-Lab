#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

/* Create Playfair matrix */
void generateMatrix(char key[])
{
    int used[26] = {0};
    int k = 0;

    for(int i=0; key[i]; i++)
    {
        char ch = tolower(key[i]);
        if(ch == 'j') ch = 'i';

        if(!used[ch-'a'])
        {
            used[ch-'a'] = 1;
            matrix[k/5][k%5] = ch;
            k++;
        }
    }

    for(char ch='a'; ch<='z'; ch++)
    {
        if(ch=='j') continue;
        if(!used[ch-'a'])
        {
            matrix[k/5][k%5] = ch;
            k++;
        }
    }
}

/* Find position */
void findPos(char c,int *r,int *c2)
{
    if(c=='j') c='i';

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(matrix[i][j]==c)
            {
                *r=i;
                *c2=j;
            }
}

/* Prepare plaintext */
void prepareText(char text[])
{
    char temp[200];
    int k=0;

    for(int i=0;text[i];i++)
    {
        if(isalpha(text[i]))
            temp[k++] = tolower(text[i]);
    }
    temp[k]='\0';
    strcpy(text,temp);

    for(int i=0;text[i];i+=2)
    {
        if(text[i]==text[i+1])
        {
            memmove(&text[i+2],&text[i+1],strlen(text)-i);
            text[i+1]='x';
        }
    }

    if(strlen(text)%2!=0)
        strcat(text,"x");
}

/* Encrypt */
void encrypt(char text[])
{
    int r1,c1,r2,c2;

    for(int i=0;text[i];i+=2)
    {
        findPos(text[i],&r1,&c1);
        findPos(text[i+1],&r2,&c2);

        if(r1==r2)
        {
            text[i]   = matrix[r1][(c1+1)%5];
            text[i+1] = matrix[r2][(c2+1)%5];
        }
        else if(c1==c2)
        {
            text[i]   = matrix[(r1+1)%5][c1];
            text[i+1] = matrix[(r2+1)%5][c2];
        }
        else
        {
            text[i]   = matrix[r1][c2];
            text[i+1] = matrix[r2][c1];
        }
    }
}

/* Decrypt */
void decrypt(char text[])
{
    int r1,c1,r2,c2;

    for(int i=0;text[i];i+=2)
    {
        findPos(text[i],&r1,&c1);
        findPos(text[i+1],&r2,&c2);

        if(r1==r2)
        {
            text[i]   = matrix[r1][(c1+4)%5];
            text[i+1] = matrix[r2][(c2+4)%5];
        }
        else if(c1==c2)
        {
            text[i]   = matrix[(r1+4)%5][c1];
            text[i+1] = matrix[(r2+4)%5][c2];
        }
        else
        {
            text[i]   = matrix[r1][c2];
            text[i+1] = matrix[r2][c1];
        }
    }
}

/* Display matrix */
void printMatrix()
{
    printf("Playfair Matrix:\n");
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            printf("%c ",matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    char key[]="cryptology";
    char text[200]="The British Army used the Playfair Cipher during World War One";

    generateMatrix(key);
    printMatrix();

    prepareText(text);
    printf("\nPrepared Text : %s\n",text);

    encrypt(text);
    printf("Encrypted Text: %s\n",text);

    decrypt(text);
    printf("Decrypted Text: %s\n",text);

    return 0;
}
