#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t childPid;
  int pipeFd[2];
  pipe(pipeFd);
  childPid = fork();
  if(childPid == 0){
    /* Дочерний процесс */
    close(pipeFd[1]);
    float mas1[2];
    float x, y;
    if(read(pipeFd[0], &mas1, sizeof(mas1)) ){ 
      x=mas1[0];
      y=mas1[1];
      /* Проверка, в какой четверти точка */
      if(x==.0 && y==.0){
        printf("Point is at the origin\n");
        return 0;
        }
      if(x==.0){
        printf("Point is situated at the axis Y\n");
        return 0;
      }
      if(y==.0){
        printf("Point is situated at the axis X\n");
        return 0;
      }
      if(x>.0){
        if(y>.0){
          printf("First quarter\n");
        }
        else{
          printf("Fourth quarter\n");
        }
      }
      if(x<.0){
        if(y>.0){
          printf("Second quarter\n");
        }
        else{
          printf("Third quarter\n");
        }
      }
    }
    else 
      close(pipeFd[0]);
  }
  
  else{
    /* родительский процесс */
    close(pipeFd[0]);
    float mas[2];
    /* Считываем x и y в массив */
    printf("Enter x: ");
    scanf("%f", &mas[0]);
    printf("Enter y: ");
    scanf("%f", &mas[1]);
    /* Пишем в ТРУБУ */
    write(pipeFd[1], &mas, sizeof(mas));
  }
}
