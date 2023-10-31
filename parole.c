#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    FILE *file = fopen(".\\parole.txt", "r");
    char *words;

    size_t n = 0;
    int c;
  
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);

    fseek(file, 0, SEEK_SET);
    words = malloc(f_size);

    while ((c = fgetc(file)) != EOF) {
        words[n++] = (char)c;
    }
    words[n] = '\0'; 

    srand (time(NULL));  

    char wordToGuess[5];
    long int twelvePossibleWordsToStart[12];
    int wordAmongTwelve = rand()%12;

    long int halfSize = f_size / 2;

    for (int i = 0; i < 12; i++)
        twelvePossibleWordsToStart[i] = rand()% halfSize;

    for (int i = 1; i < 12; i+=2)
        twelvePossibleWordsToStart[i]*=2;

    long int wordsStartingChar = twelvePossibleWordsToStart[wordAmongTwelve];

    while (words[wordsStartingChar] != ' ') 
        wordsStartingChar--;
        
    for (size_t i = 0; i < 5; i++) 
        wordToGuess[i] = words[wordsStartingChar+i+1];

    fclose(file); 

    free(file); 
    file = NULL;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("\n\t\t\t\t\t\t\t PA");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("RO");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("LE");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    printf("\n\t\t\t\t\t\t5 lettere <-> 6 tentativi\n\n\n\n\tLegenda:");

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("\n\t\tVerde = lettera nel posto giusto.");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("\n\t\tRosso = lettera presente nella parola ma non nel posto giusto.");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    printf("\n\t\tBianco = lettera non presente nella parola.\n\n");

    //printf("\n\n\t%c%c%c%c%c\n\n\t", wordToGuess[0], wordToGuess[1], wordToGuess[2], wordToGuess[3], wordToGuess[4]);

    char userWord[6];
    char redCaseCopyString[5];
    int flag[5] = {0,0,0,0,0};
    int kWin = 0, nTentativi, checkExistingWord;

    for (nTentativi = 0; nTentativi < 6 && kWin != 5; nTentativi++) {

        checkExistingWord = 0;
        kWin = 0;

        for (size_t l = 0; l < 5; l++)
        redCaseCopyString[l] = wordToGuess[l];

        printf("\n\tTentativo %d: ", nTentativi+1);
        scanf("%s", userWord);

        while (userWord[5] != '\0' || userWord[4] == '\0' || userWord[3] == '\0' || userWord[2] == '\0' || userWord[1] == '\0' || userWord[0] == '\0') {
            printf("\tErrore, riprova: ");
            scanf("%s", userWord);            
        }

        for (size_t j = 0; j < 5; j++)
            userWord[j] = toupper(userWord[j]);
      
        for (size_t s = 0; s < f_size; s++) {

                if (userWord[0] == words[s+1] && userWord[1] == words[s+2] && userWord[2] == words[s+3] && userWord[3] == words[s+4] && userWord[4] == words[s+5])
                    checkExistingWord++;     
        }

        while (checkExistingWord == 0) {

            printf("\tParola non esistente: ");
            scanf("%s", userWord); 

            for (size_t j = 0; j < 5; j++)
            userWord[j] = toupper(userWord[j]);
      
            for (size_t s = 0; s < f_size; s++) {

                if (userWord[0] == words[s+1] && userWord[1] == words[s+2] && userWord[2] == words[s+3] && userWord[3] == words[s+4] && userWord[4] == words[s+5])
                    checkExistingWord++;     
            }
        }

        printf("\t\t\t\t\t\t\t\t\t\t\t");

        for (size_t j = 0; j < 5; j++)
        {
            if (userWord[j] == wordToGuess[j]) 
                redCaseCopyString[j] = ' ';        
        }

        for (size_t j = 0; j < 5; j++)
        {
            flag[j] = 0;

            if (userWord[j] == wordToGuess[j]) 
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("%c ", userWord[j]);
                SetConsoleTextAttribute(hConsole, saved_attributes);
                redCaseCopyString[j] = ' ';
                flag[j] = 1;
                kWin++;
            }

            if (kWin != 5) {

                    for (size_t o = 0; o < 5; o++) {

                        if (userWord[j] == redCaseCopyString[o] && redCaseCopyString[o] != ' ' && flag[j] == 0) {

                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                            printf("%c ", userWord[j]);
                            SetConsoleTextAttribute(hConsole, saved_attributes);
                            redCaseCopyString[o] = ' ';
                            flag[j] = 1;
                        }
                    }

                if (flag[j] == 0) 
                        printf("%c ", userWord[j]);            
            }
        }
    }

    if (kWin == 5) {
        switch (nTentativi) {

            case 1: printf("\n\tTop numero 1.");break;
            case 2: printf("\n\tGrandissimoo.");break;
            case 3: printf("\n\tYess, ottimo!");break;
            case 4: printf("\n\tYess, grande!");break;
            case 5: printf("\n\tYes!");break;
            case 6: printf("\n\tChe culo!");break;
        }
    } 
    else 
        printf("\n\tLa parola era %c%c%c%c%c.", wordToGuess[0], wordToGuess[1], wordToGuess[2], wordToGuess[3], wordToGuess[4]);

    printf("\n\n\t");
          
    system("pause");    
    return 0;
}