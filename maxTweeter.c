#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tweeterStruct{
	char* tweeter;
	int tweetCount;
};

struct tweeterStruct tweeterArray[20000];
struct tweeterStruct copyArray[20000];


char* getfield(char* line, int num);
char* cleanString(char *str);
int tweeterCheck(char* name);
void updateTweeter(char* name);
void printTweeters();
void initializeTweeterArray();
void initializeCopyArray();
void printTopTen();

int main(int argc, char** argv)
{
	char line[1024];
    float lines = 0;
    float lenTotal = 0;

	printf("Input file: %s\n", argv[1]);
    FILE* stream = fopen(argv[1], "r");

    initializeTweeterArray();

    int i =0;

    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);

        char* name = getfield(tmp, 9);
        name = cleanString(name);

       	if (tweeterCheck(name) == -1){
       		tweeterArray[i].tweeter = name;
       		tweeterArray[i].tweetCount = 1;

       	} else {
       		updateTweeter(name);
       	}

        i++;
    }

    initializeCopyArray();
    // printTweeters();
    printTopTen();

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
			if (strcmp(tweeterArray[i].tweeter,name) == 0){
				return 1;
			}
	}
	return -1;
}

void initializeTweeterArray() {
	int i;
	for(i=0; i < 20000; i++) {
		tweeterArray[i].tweeter = (char*)calloc(1, sizeof(char));
	}
}

void updateTweeter(char* name){
	for (int i = 0; i < 20000; i++){
		if (strcmp(tweeterArray[i].tweeter,name) == 0){
			tweeterArray[i].tweetCount++;
			break;
		}
	}
}

void printTweeters(){
	for (int i = 0; i < 20000; i++){
		if(copyArray[i].tweetCount != 0){
		printf("CopyTweeter:%s CopyTweeter Count: %d\n", copyArray[i].tweeter, copyArray[i].tweetCount);
	}
	}
}

void initializeCopyArray(){
	int i;
	for(i=0; i < 20000; i++) {
		copyArray[i].tweeter = (char*)calloc(1, sizeof(char));
		copyArray[i].tweeter = tweeterArray[i].tweeter;
		copyArray[i].tweetCount = tweeterArray[i].tweetCount;
	}
}

void printTopTen(){
	for (int i =0; i <10; i++){
		int max =0;
		for (int i=0; i <20000; i++){
			if (copyArray[i].tweetCount > max){
				max = copyArray[i].tweetCount;
				//printf("max: %d\n", max);
			}
		}

		for (int i =0; i <20000; i++){
			if (copyArray[i].tweetCount == max){
				printf("%s:%d\n", copyArray[i].tweeter, copyArray[i].tweetCount);
				copyArray[i].tweetCount = 0;
				//printf("%s:%d\n", copyArray[i].tweeter, copyArray[i].tweetCount);
				break;
			}
		}
	}
}
