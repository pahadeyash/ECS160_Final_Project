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
int getColumnNum(char *line);


int main(int argc, char** argv)
{
	char line[1024];
	char *line1 = NULL;
	size_t len = 0;
	const char s[2] = ",";
	char *token;
	int isValid = 0;
	int lineCount = 0;
	int columnCount = 0;
	int nameColCount = 0;

	FILE* stream = fopen(argv[1], "r");

	if (stream == NULL){
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	// checking if file is valid
	getline(&line1, &len, stream);
	token = strtok(line1, s);

	// checking if there is name column
	while( token != NULL ){
	    if (strcmp("\"name\"", token) == 0){
				nameColCount = columnCount;
	      isValid = 1;
	    }

		columnCount++;
		token = strtok(NULL, s);
	}


	// getting the number of line in the csv file
	while (fgets (line, 1024, stream)){
		lineCount++;
	}

	// checking if the file is valid
	if (isValid != 1 || lineCount > 20000){
		fprintf(stderr, "This isn't a valid file\n");
		return -1;
	}

	stream = fopen(argv[1], "r");

  	initializeTweeterArray();

    // adjusting column count for get field
	nameColCount++;

    int i =0;

    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);

		int tokenNum = getColumnNum(line);


		if(i > 0){
			if((tokenNum-1) != columnCount){
				fprintf(stderr, "This isn't a valid file\n");
				return -1;
			}
		}

        char* name = getfield(tmp, nameColCount);
        name = cleanString(name);
        // if tweeter doesn't exists add it
       	if (tweeterCheck(name) == -1){
       		tweeterArray[i].tweeter = name;
       		tweeterArray[i].tweetCount = 1;
       	} else { // if tweeter already exists increment the count
       		updateTweeter(name);
       	}

        i++;
    }
	
    initializeCopyArray();
    printTopTen();
	
    return 0;

}

/**
 * cleanString - Strips " from the string 
 * @str: String to strip
 *
 * Return: a string withouth the "
 */

char* cleanString(char *str)
{
	int i,j;
	i = 0;
	if(str != NULL){
		while(i<strlen(str))
		{
		    if (str[i]=='"')
		    {
		        for (j=i; j<strlen(str); j++)
		            str[j]=str[j+1];
		    }
		    else i++;
		}
	}
	return str;
}

/**
 * getfieled - returns the token at a particular column
 * @str: line that will be tokenized 
 * @num: the column number 
 *
 * Return: token from the specified field
 * or NULL if no token in the field found
 */
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


/**
 * tweeterCheck - checks if a tweeter with the name already exists
 * @name: name of the tweeter
 *
 * Return: 1 if a tweeter with the name already exits and -1
 * if it doesn't exist
 */
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


/**
 * initializeTweeterArray - allocated memory for the tweeter array
 */
void initializeTweeterArray() 
{
	int i;
	for(i=0; i < 20000; i++) {
		tweeterArray[i].tweeter = (char*)calloc(1, sizeof(char));
	}
}

/**
 * updateTweeter - checks if tweeter exists with the name already exists and update the count
 * @name: name of the tweeter
 */
void updateTweeter(char* name)
{
	for (int i = 0; i < 20000; i++){
		if (strcmp(tweeterArray[i].tweeter,name) == 0){
			tweeterArray[i].tweetCount++;
			break;
		}
	}
}

/**
 * printTweeters - prints out all the Tweeters for debugging purpose
 */
void printTweeters()
{
	for (int i = 0; i < 20000; i++){
		if(copyArray[i].tweetCount != 0){
		printf("CopyTweeter:%s CopyTweeter Count: %d\n", copyArray[i].tweeter, copyArray[i].tweetCount);
		}
	}
}

/**
 * initializeCopyArray - create the a copy array so that the max can be calculated for printing
 */
void initializeCopyArray()
{
	int i;
	for(i=0; i < 20000; i++) {
		copyArray[i].tweeter = (char*)calloc(1, sizeof(char));
		if ( strcmp(tweeterArray[i].tweeter,"name") != 0 ){
			copyArray[i].tweeter = tweeterArray[i].tweeter;
			copyArray[i].tweetCount = tweeterArray[i].tweetCount;
		}
	}
}

/**
 * printTopTen - takes the copy array and prints the top tweeter and sets its max to 0
 */
void printTopTen()
{
	for (int i =0; i <10; i++){
		int max =0;
		for (int i=0; i <20000; i++){
			if (copyArray[i].tweetCount > max){
				max = copyArray[i].tweetCount;
			}
		}

		if (max == 0){
			break;
		}

		for (int i =0; i <20000; i++){
			if (copyArray[i].tweetCount == max){
				printf("%s:%d\n", copyArray[i].tweeter, copyArray[i].tweetCount);
				copyArray[i].tweetCount = 0;
				break;
			}
		}
	}
}

/**
 * getColumnNum - gets the total number of columms
 * @str: the line in the csv file to get the number of columns
 *
 * Return: the number of columns
 */
int getColumnNum(char *str)
{
	char s[2] = ",";
	int count = 0;

	char* token = strtok(str, s);
	count = 1;
	while( token != NULL ) {
		count++;
		token = strtok(NULL, s);
	}

	return count;
}
