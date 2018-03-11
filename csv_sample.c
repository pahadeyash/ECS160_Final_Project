#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getWordCount(const char* text, int length)
{
    int wordCount = 0;
    if(length >= 2) //Due to quotes;
    {
        wordCount += 1;
    }
    int i = 0;
    for(i = 0; i < length; i++){
	if(' ' == text[i])
        {
	    wordCount++;
        }
    }
    return wordCount;
}

const char* getfield(char* line, int num)
{
    const char* tok;
    //for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
    for (tok = strtok(line, ","); ; tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int main(int argc, char** argv)
{
    printf("Input file: %s\n", argv[1]);
    FILE* stream = fopen(argv[1], "r");

    char line[1024];
    float lines = 0;
    float lenTotal = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        const char* out = getfield(tmp, 12);
        float nextLength = strlen(out);
        lines++;
        printf("Text: %s\n", out);
        printf("Length: %f\n", nextLength);

        float wC = getWordCount(out, nextLength);
        printf("Word Count: %f\n", wC);
        int aveCPW = (nextLength - (wC-1))/wC;
	printf("Chars per word: %d\n", aveCPW);
        char* wordTwoGuess = (char *) malloc(aveCPW+1 * sizeof(char));
        memcpy(wordTwoGuess, &out[aveCPW + 1], aveCPW);
        printf("Guess at second word: %s\n", wordTwoGuess);


        if(wC == 2)
	{
      	  printf("%c\n", out[2000048]);
	}

	if(wC > 5)
	{
	  free(tmp);
	}
        lenTotal += nextLength;
        // NOTE strtok clobbers tmp
        free(tmp);
    }

    printf("Average Tweet Length: %f\n", lenTotal/lines);
}
