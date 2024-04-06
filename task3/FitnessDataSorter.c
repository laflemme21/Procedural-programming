#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	char date[11];
	char time[6];
	char steps[9];
} FILE_DATA;

float line_counter(char filename[]){
    FILE *file=fopen(filename,"r");
    char char_in_file[100];
    int lines_count=0;
    while(fgets(char_in_file,100,file)!=NULL){
        lines_count++;
    }
    fclose(file);
    return lines_count;
}

int tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    char *inputCopy = strdup(input);
    
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    else{
        return 1;
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    else{
        return 1;
    }
    
    token = strtok(NULL, delimiter);
    if (token == NULL || atoi(token) == 0){
        
        return 1;
    }
    else{
        strcpy(steps, token);
    }
    
    free(inputCopy);

}

int main(){
    char filename[160];
    char newfilename[164];
    int var;
    FILE* copy;
    float lines_num;
    FILE_DATA file[200];
    FILE_DATA temp;
    char line_buffer[100];
    char date[11];

    printf("Input filename:");
    scanf("%s",filename);
    copy=fopen(filename,"r");
    if(copy==NULL){
        printf("Error: Could not find or open the file.\n");
        return 1;
    }
    lines_num=line_counter(filename);
    while (fgets(line_buffer, 100, copy) != NULL) {
        if(tokeniseRecord(line_buffer, ",", file[var].date, file[var].time, file[var].steps)==1){
            return 1;}
        var++;
    }
    fclose(copy);


    for(int i=0;i<160;i++){
        if(!(filename[i])){
            newfilename[i]='.';
            newfilename[i+1]='t';
            newfilename[i+2]='s';
            newfilename[i+3]='v';
            newfilename[i+4]='\0';
            break;
        }
        newfilename[i]=filename[i];
    }

    for(int i=0;i<lines_num;i++){
        for(int j=0;j<lines_num-1;j++){
            if(atoi(file[j].steps)<atoi(file[j+1].steps)){
                temp=file[j];
                file[j]=file[j+1];
                file[j+1]=temp;
            }
        }
    }

    copy=fopen(newfilename,"w");
    for(int i=0;i<lines_num;i++){
        fprintf(copy,"%s\t%s\t%s",file[i].date,file[i].time,file[i].steps);
    }
    fclose(copy);
    return 0;
}