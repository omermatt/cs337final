	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>

typedef struct hints {
    
        char phrase[30];
        char hint[30] ;
        
    } hints;

int hangman(char* answer);
int main()
{
	 struct hints records;
	int client = socket(AF_UNIX, SOCK_STREAM, 0);
	if(client == -1)
	{
		printf("FAILS1");
		return -1;
	}

	struct sockaddr name = {AF_UNIX, "ServerX"};
	socklen_t name_len = sizeof(struct sockaddr) + 8;

	if( connect(client, &name, name_len) == -1)
	{
		printf("fails2");
		return -1;
	}

	read(client, &records, sizeof(hints));

	printf("%s\n", records.phrase); 
    
    hangman(records.hint);

	close(client);

	return 0;
}

int hangman(char* answer){
  

    
    int N = strlen(answer);
    int mask[N];
    for (int i=0; i < N; ++i) {
	if(isspace(answer[i])){
            mask[i] = 1;
        }else{
     		 mask[i] = 0;
	}
    }

   
    int gameover = 0;
    while (! gameover) {
	 printf("Common Phrase \n");
      printf("------------- \n");
      for(int j=0; j < N; ++j) {
        if (mask[j] ) {
          printf("%c", answer[j]);
        }
        else {
          printf("*");
        }
      }
      printf("\n");
      char guess;
      fflush(stdout);
	 printf("Enter a single character guess : ");
      scanf(" %c", &guess);
      printf("\n\n\n");

      for(int k=0; k < N; ++k) {
        if (answer[k] == guess) {
      mask[k] = 1;
        }
      }

      
      gameover = 1;
      for(int m = 0; m < N; ++m) {
        if (!mask[m]) {
          gameover = 0;
          break;
        }
      }
    }
    printf("Victory! The word is \"%s\".\n", answer);
    return 0;
    
}


