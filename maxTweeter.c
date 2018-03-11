#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*TODO
1. Take in the path of file from argument.
2. Handle errors properly
3. Store the info in the array
*/

char *cleanString(char *str);

struct tweeterStruct{
	char *tweeter;
	int tweetCount;
};

struct tweeterStruct lineArray[20000];

int main(int argc, char **argv)
{
	int count = 0;
	int c;
	FILE *stream;
	char *line = NULL;
  	size_t len = 0;
	int lineCount = 0;
 	const char s[2] = ",";
 	char *token;
 	int isValid = 0;

	stream = fopen("cl-tweets-short.csv", "r");
  	
  	//checking if the file exists	
  	if (stream == NULL) {
    	perror("fopen");
    	exit(EXIT_FAILURE);
  	}

  	// checking if file is valid
  	getline(&line, &len, stream);
  	token = strtok(line, s);
	int columnCount = 0;

	while( token != NULL ){
	  	token = cleanString(token);
	  	if (strcmp("name", token) == 0){
	  		isValid = 1;
			break;
	    }

		columnCount++;
	    token = strtok(NULL, s);
 	}

 	if (isValid == 0){
 		fprintf(stderr, "Invalid input format\n");
 		return -1;
 	}

	while (getline(&line, &len,stream) != -1) {
		char c[1000];
		printf("%s",line);
		strcpy(c, line);
		printf("%s\n",c);
	}

	/*
		Need to rethink counting logic.
	*/

	if(isValid != 0){
		for (c = getc(stream); c != EOF; c = getc(stream))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

			if (count > 20000){
				return -1;
			} else {
				printf("%d\n",count);
			}
	}

	free(line);
	fclose(stream);
	exit(EXIT_SUCCESS);

	return 0;
}

// function trims the " out of the strings so its easier to compare
char *cleanString(char *str)
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
