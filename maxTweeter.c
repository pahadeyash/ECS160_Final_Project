#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cleanString(char *str);

int main(int argc, char **argv)
{	
	FILE *stream;
	char *line = NULL;
    size_t len = 0;
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
    while( token != NULL ){
    	token = cleanString(token);
    	if (strcmp("name", token) == 0){
    		isValid = 1;
      		break;
      	}

      	token = strtok(NULL, s);
   	}

   	if (isValid == 0){
   		fprintf(stderr, "File isn't valid\n");
   		return -1;
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