#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tweeterStruct{
	char* tweeter;
	int tweetCount;
};

struct tweeterStruct tweeterArray[20000];

void initializeTweeterArray() {
	int i;
	for(i=0; i < 20000; i++) {
		tweeterArray[i].tweeter = (char*)calloc(1, sizeof(char));
	}
}

char* getfield(char* line, int num);
char* cleanString(char *str);
int tweeterCheck(char* name);
void updateTweeter(char* name);
void printTweeters();

int main(int argc, char** argv)
{
	char line[1024];
    float lines = 0;
    float lenTotal = 0;

	printf("Input file: %s\n", argv[1]);
    FILE* stream = fopen(argv[1], "r");

    initializeTweeterArray();

    while (fgets(line, 1024, stream)){
    	int i=0;
        char* tmp = strdup(line);
        //printf("%s\n", tmp);
        
        char* name = getfield(tmp, 9);
        name = cleanString(name);
        
        // strcpy(tweeterArray[i].tweeter, name);
       	if (tweeterCheck(name) == -1){
       		printf("Tweeter doesn't exist\n");
       		strcpy(tweeterArray[i].tweeter,name);
       		printf("%s\n",tweeterArray[i].tweeter);
       		tweeterArray[i].tweetCount = 1;
       	} else {
       		printf("Tweeter exists\n");
       		updateTweeter(name);
       	}
        i++;
    }

    printTweeters();


}

char* cleanString(char *str)
{
	int i,j;
	i = 0;
	while(i<strlen(str))
	{
	    if (str[i]=='"')
	    {
	        for (j=i; j<strlen(str); j++)
	            str[j]=str[j+1];
	    }
	    else i++;
	}
	return str;
}

//This offsets by 1
char* getfield(char* line, int num)
{
    char* tok;

    for (tok = strtok(line, ","); ; tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int tweeterCheck(char* name)
{
	int i;
	for(i=0; i < 20000; i++) {
			if (tweeterArray[i].tweeter == name){
				return 1;
			}
	}
	return -1;
}

void updateTweeter(char* name){
	for (int i = 0; i < 20000; i++){
		if (tweeterArray[i].tweeter == name){
			tweeterArray[i].tweetCount++;
			break;
		}
	}
}

void printTweeters(){
	for (int i = 0; i < 40; i++){
		printf("%s %d\n", tweeterArray[i].tweeter, tweeterArray[i].tweetCount);
	}
}