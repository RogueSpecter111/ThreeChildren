
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

int argArray[7];	

int fd[2];
pipe(fd);

int fd2[2];
pipe(fd2);

int fd3[2];
pipe(fd3);

int sum=0;
int t; 
t=atoi(argv[1]);

printf("number of children: %d\n", t); 

for(int i=1; i<argc; i++){
	 argArray[i-1] = atoi(argv[i]);	 
}

//int array1[6] = {2,3,7,-1,10,6};

//____________________________________________________________________________________________________________________

if(t==1){
 

 printf("hello world, I am Parent the only one with process ID: (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
       // fork failed; exit
        fprintf(stderr, "fork failed\n");
         exit(1);
        
        } else if (rc == 0) {
        close(fd[0]);
        int i;
        for(i=1; i<7; i++){  //first correction here from 0-3
          //sum = sum+array1[i];
		  sum = sum+argArray[i];
         }
          write(fd[1], &sum, sizeof(sum));
          printf(" I am process %d and I am sending : %d to my parent\n", (int) getpid(),  sum);
         close(fd[1]);
        exit(0);   //I am includeing exit(0) to kill the process after is done !!!!@
    }
   else {
        int sum1;
        int final=0;
        close(fd[1]);
        read(fd[0], &sum1, sizeof(sum));
        final = sum1;
        close(fd[0]);
        printf("I am the parent at the end with ID %d with a final sum of: %d \n" , (int) getpid(), final);
    }
}

//____________________________________________________________________________________________________________________

if(t==2){
printf("hello world, I am Parent the only one with process ID: (pid:%d)\n", (int) getpid());
    int rc0 = fork();
    if (rc0 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
 
    } else if (rc0 == 0) {
       close(fd[0]);
       int i;
      for(i=1; i<4; i++){  //first correction here from 0-3
          //sum = sum+array1[i];
		  sum = sum+argArray[i];
       }
      write(fd[1], &sum, sizeof(sum));
     printf(" I am process %d and I am sending : %d to my parent\n", (int) getpid(),  sum);
     close(fd[1]);
     exit(0);   //I am includeing exit(0) to kill the process after is done !!!!@
    }  
   int rc1=fork();
   if (rc1==0){
          close(fd2[0]);
           int k;
           for (k=4; k<7; k++){
           //sum = sum+array1[k];
		   sum = sum+argArray[k];
            }
          write(fd2[1], &sum, sizeof(sum));
          printf("I am process with id number %d  sending the  value:%d\n", (int) getpid(), sum);
          close(fd2[1]);
         exit(0);
      } 

   else {
        int sum1, sum2;
        int final=0;
          
       close(fd[1]);
      read(fd[0], &sum1, sizeof(sum));
      final = final + sum1;
      close(fd2[1]);
      read(fd2[0], &sum2, sizeof(sum2));
      
    final = final +sum2;
    
    printf("I am the parent at the end with ID %d with a final sum of: %d \n" , (int) getpid(), final);
    close(fd[0]);
    close(fd2[0]);
    }
}

//____________________________________________________________________________________________________________________

if(t==3){
printf("hello world, I am Parent the only one with process ID: (pid:%d)\n", (int) getpid());
    int rc0 = fork();
    if (rc0 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
 
    } else if (rc0 == 0) {
       close(fd[0]);
       int i;
      for(i=1; i<3; i++){  //first correction here from 0-3
          //sum = sum+array1[i];
		  sum = sum+argArray[i];
       }
      write(fd[1], &sum, sizeof(sum));
     printf(" I am process %d and I am sending : %d to my parent\n", (int) getpid(),  sum);
     close(fd[1]);
     exit(0);   //I am includeing exit(0) to kill the process after is done !!!!@
    }  
   int rc1=fork();
   if (rc1==0){
          close(fd2[0]);
           int k;
           for (k=3; k<5; k++){
           //sum = sum+array1[k];
		   sum = sum+argArray[k];
            }
          write(fd2[1], &sum, sizeof(sum));
          printf("I am process with id number %d  sending the  value:%d\n", (int) getpid(), sum);
          close(fd2[1]);
         exit(0);
      } 
	
	int rc2=fork();
   if (rc2==0){
          close(fd3[0]);
           int j;
           for (j=5; j<7; j++){
           //sum = sum+array1[j];
		   sum = sum+argArray[j];
            }
          write(fd3[1], &sum, sizeof(sum));
          printf("I am process with id number %d  sending the  value:%d\n", (int) getpid(), sum);
          close(fd3[1]);
         exit(0);
      } 

   else {
        int sum1, sum2, sum3;
        int final=0;
          
       close(fd[1]);
      read(fd[0], &sum1, sizeof(sum));
      final = final + sum1;
      close(fd2[1]);
      read(fd2[0], &sum2, sizeof(sum2));
	  final = final + sum2;
	  close(fd3[1]);
      read(fd3[0], &sum3, sizeof(sum3));
      
    final = final +sum3;
    
    printf("I am the parent at the end with ID %d with a final sum of: %d \n" , (int) getpid(), final);
    close(fd[0]);
    close(fd2[0]);
	close(fd3[0]);
    }
}

//____________________________________________________________________________________________________________________

    return 0;
}
