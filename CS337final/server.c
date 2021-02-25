
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>
#define MAX 1024


 typedef struct hints {
    
        char phrase[30];
        char hint[30] ;
        
    } hints;


void ctrlc();


int main()
{
    printf("\n");
    
    struct hints *records;
    char buff[1000];
    char* temp_phrase;
    char* temp_hint;
    hints *temp_record;
    int i=0;
    int j=0;
   records = (struct hints*) malloc(sizeof(hints)*30);

    FILE *fp = fopen("file.txt", "r");
    
    while(fgets(buff, 1000, (FILE*)fp) != NULL) {
                if(buff != NULL) {
                    j=0;
                    
                    temp_phrase = strtok(buff, ",");
                    //temp_len = atoi(strtok(NULL, ","));
                    temp_hint = strtok(NULL, ",");
                    
                    
                    strcpy(records[i].phrase , temp_phrase);
                    strcpy(records[i].hint , temp_hint);
                    i++;
                    
                }
            }
    
    
    
	int soc = socket(AF_UNIX, SOCK_STREAM, 0);
	if (soc == -1)
	{
		printf("fails1");
		return -1;
	}

	struct sockaddr name = {AF_UNIX, "ServerX"};
	socklen_t name_len = sizeof(struct sockaddr) + 8;

	int id = bind(soc, &name, name_len);
	if (id == -1)
	{
		printf("fails2");
		return -1;
	}
    
    int var = 1;
    
    void ctrlc()
    {
      printf("\nI will not be stopped! %d\n", var);
      ++var;
    }
    
      printf("\n");
    
      struct sigaction news;
      struct sigaction olds;
    
      news.sa_handler = ctrlc;
      news.sa_flags = 0;
    
    
      sigaction( SIGINT, &news, &olds);
    
    
      printf("Natural termination \n");

	do
	{
		if (listen(soc, 1) == -1)
		{
			printf("fails3");
			return -1;
		}

		int temp_client;
		if (((temp_client = accept(soc, NULL, NULL)) == -1))
		{
                        printf("fails4");
                        return -1;

		}
        
        
        
        int r = rand() % 8;
     
	printf("connected");
	printf(records[r].phrase);
        write(temp_client,&records[r], sizeof(hints));
	fflush(stdout);	
        
		close(temp_client);


	}while(1);
    
    pclose(fp);
	
	return 0;
}

void ctrlc()
{
    printf("\n I will not be stopped! \n");
    
}


