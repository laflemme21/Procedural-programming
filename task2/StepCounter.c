#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// prints the menu and returns the users input
char menu(){
    char option_selected;
    printf("Menu Options:\n");
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the data and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Exit the program.\n");
    scanf("%s", &option_selected);
    return option_selected;
}

// returns the number of lines in the given file
float line_counter(char filename[30]){
    FILE *file=fopen(filename,"r");
    char char_in_file[100];
    int lines_count=0;
    while(fgets(char_in_file,100,file)!=NULL){
        lines_count++;
    }
    fclose(file);
    return lines_count;
}

// stores the file in a tyoedef struct
//FILE_DATA File_storer(char filename[],float number_of_lines){
//    FILE_DATA Data=malloc(500*sizeof(number_of_lines-1));
  //  FILE file = fopen(filename, "r");

    //return Data;
//}


int main(){
    char filename[50]="FitnessData_2023.csv";
    float lines_num;
    FILE_DATA file[500];

    int line=0;
    char line_buffer[100];
    FILE *copy;

    char input;
    int var;
    int F1;
    int F2;
    int var2;
    int F3;
    int F4;

    while(input!='Q'){
        var=0;
        var2=0;
        input=menu();

        switch(input){
        case'A':
            printf("Input filename:");
            scanf("%s",filename);
            copy=fopen(filename,"r");
            if(copy==NULL){
                printf("Error: Could not find or open the file.\n");
                return 1;
                }
            lines_num=line_counter(filename);
            while (fgets(line_buffer, 100, copy) != NULL) {
                tokeniseRecord(line_buffer, ",", file[var].date, file[var].time, file[var].steps);
                var++;
    }
            break;

        case'B':
            var=lines_num;
            printf("Total records: %d\n", var);
            break;

        case'C':
            for(int i=0;i<lines_num;i++){
                if (atoi(file[i].steps)<atoi(file[var].steps)){
                    var=i;
                }
            }
            printf("Fewest steps: %s %s\n",file[var].date,file[var].time);
            break;

        case'D':
            for(int i=0;i<lines_num;i++){
                printf("%d=%s>%s\n",i,file[i].steps,file[var].steps);
                if (atoi(file[i].steps)>atoi(file[var].steps)){
                    var=i;
                }
            }
            printf("Largest steps: %s %s\n",file[var].date,file[var].time);
            break;

        case'E':
            for(int i=0;i<lines_num;i++){
                var+=atoi(file[i].steps);
            }
            var2=var/lines_num;
            if((var/lines_num)-var2>=0.5){
                var2+=1;
            }
            printf("Mean step count: %d\n",var2);
            break;
        case'F':
            for(int i=0;i<lines_num;i++){
                var=0;
                while(atoi(file[i].steps)>500 || i>lines_num){
                    var+=1;
                    if(var==1){
                        F1=i;
                        F2=i;
                    }
                    else{
                        F2=i;
                    }
                    i+=1;
                }
                if(var2<var){
                    F3=F1;
                    F4=F2;
                    var2=var;
                }
            }
            printf("Longest period start: %s %s\nLongest period end: %s %s\n",file[F3].date,file[F3].time,file[F4].date,file[F4].time);
            break;
        case'Q':
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
    }
    }
    return 0;
}