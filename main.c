#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//123000000000000 ---> chunk
//000 -->index 0
//000 -->      2
//000 -->      3
//000 -->      4
//123 -->      5


typedef struct num{
    char * requivalent;
    struct num * next;
}result;

result * root = NULL;

char * num1[] = {"","one","two","three","four","five","six","seven","eight","nine"};
char * num2[] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
char * num3[] = {" ","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninty"};
char * num4[] = {" ","thousand","million","billion","thrillion"};

void result_hundredths(int number){
    int hundred = floor(number/100);
    int remainder = number % 100;

    char * output;
    output = (char *)malloc(254);
    strcpy(output, " ");
    if(hundred > 0){
        strcat(output, num1[hundred]);
        strcat(output, " hundred");
        strcat(output, " ");
    }

    if(remainder > 10 && remainder < 20){
        strcat(output, " ");
        strcat(output, num2[remainder - 10]);
        strcat(output, " ");
    }else{
        if(remainder == 10){
            strcat(output, " ");
            strcat(output, num2[0]);
            strcat(output, " ");
        }else{
            int tense = floor(remainder/10);
            int ones = remainder%10;
            if(tense > 0){
                strcat(output, " ");
                strcat(output, num3[tense - 1]);
                strcat(output, " ");
            }
            if(ones > 0){
                strcat(output, " ");
                strcat(output, num1[ones]);
                strcat(output, " ");
            }
        }
    }


    printf(" --%s-- ", output);
    result * newNode = (result *)malloc(sizeof(result));
    newNode->requivalent = (char *)malloc(256);
    strcpy(newNode->requivalent, output);
    newNode->next = NULL;

    if(root == NULL){
        root = newNode;
    }else{
        result * pointing = root;
        while(pointing->next != NULL){
            pointing = pointing->next;
        }
        pointing->next = newNode;
    }


}

void chunkString(const char *number, char chunk[][4], int numChunks, int size) {
    // Reverse the input string
    char *number1 = malloc(size);
    int x = 0;
    for (int i = size - 1; i >= 0; i--) {
        number1[x] = number[i];
        x++;
    }
    printf("\n---->reverse: %s", number1);

    for (int i = 0; i < numChunks; i++) {
        strncpy(chunk[i], number1 + i * 3, 3);  // Copy up to three characters into each chunk
        chunk[i][strnlen(chunk[i], 3)] = '\0';  // Null-terminate each chunk based on its actual length
    }

    free(number1);
}

char * reverse(char * num){
    int len = strlen(num);
    char * output;
    output = (char *)malloc(4);
    int x = 0;
    for(int i = len - 1; i >= 0; i--){
        output[x] = num[i];
        x++;
    }
    output[len] = '\0';
    return output;
}

void numberToWords(char * number, int size){
    printf("number input: %s and size: %d", number, size);


    if(size == 1 && number[0] == '0'){
        result * newWord = (result *)malloc(sizeof(result));
        newWord ->requivalent = (char *)malloc(4);
        strcpy(newWord->requivalent, "zero");
        newWord ->next = NULL;
        root = newWord;
    }else{
        int numChunks = (size + 2)/3; //Number of chunks needed
        char chunk[numChunks][4]; //declare the chunks


        chunkString(number, chunk, numChunks, size);

        char * output;
        output = (char *)malloc(256);

        int sizeChunk = numChunks - 1;
        printf("\n---Size chunk: %d", sizeChunk );
        for(int i = numChunks - 1; i >= 0 ; i--){
            char * numString = malloc(4);
            strcpy(numString, chunk[i]);
            numString = reverse(numString);
            int n = atoi(numString);
            printf("\nchunk: %d", n);
            result_hundredths(n);

            strcat(output, " ");
            if(sizeChunk == 4){
                strcpy(output, num4[sizeChunk]);
                sizeChunk--;
            }else if(sizeChunk == 3){
                strcpy(output, num4[sizeChunk]);
                sizeChunk--;
            }else if(sizeChunk == 2){
                strcpy(output, num4[sizeChunk]);
                sizeChunk--;
            }else if(sizeChunk == 1){
                strcpy(output, num4[sizeChunk]);
                sizeChunk--;
            }else{
                strcpy(output, num4[sizeChunk]);
                sizeChunk--;
            }

            strcat(output, " ");

            result * newWord = (result *)malloc(sizeof(result));
            newWord->requivalent = (char *)malloc(256);
            strcpy(newWord->requivalent, output);
            newWord->next = NULL;

            printf(" --%s-- ", output);
            result * pointing = root;
            while(pointing->next != NULL){
                pointing = pointing->next;
            }
            pointing->next = newWord;
        }
    }
}

void display(result * root){
    result * disp = root;
    char * string_result;
    string_result = (char *)malloc(1024);
    strcpy(string_result, "--> ");
    while(disp != NULL){
        strcat(string_result, " ");
        strcat(string_result, disp->requivalent);
        disp = disp->next;
    }
    printf("\n\nresult: %s", string_result);
}

int main(){

    char * number;
    int size = 15;

    number = (char *)malloc((size + 1) * sizeof(char));
    printf("ENTER A NUMBER: ");
    scanf(" %[^\n]", number);

    size = strlen(number);
    numberToWords(number, size);

    display(root);

    return 0;
}
