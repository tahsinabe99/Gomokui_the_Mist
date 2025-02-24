// name: Tahsinul Abedin
// unikey: tabe5206
// SID: 490227237

// code here

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFLEN (11)

int x_mist_coordinate(int x_coordinate){
    int x_mist=  (1+(5*(x_coordinate*x_coordinate)+(3*x_coordinate)))%19;
    return x_mist;
}

int y_mist_coordinate(int y_coordinate){
    int y_mist= (1+(4*(y_coordinate*y_coordinate)+(2*y_coordinate)-4))%19;
    return y_mist;

}

//we check if the coordinates given after place is valid
//first we check if length is correct aka 2 coordinates are given
//Then we check if its between A and S
//Then we check if the number given is between 1 and 19

int check_coordinate_validity(char * coordinates){
    if(strlen(coordinates)<3 || strlen(coordinates)>4){
        return 0;
    }
    char c=coordinates[0];
    if(c>='A' && c<='S'){
        

    }else{
        return 0;
    }
    
    int r= atoi(&coordinates[1]);
    int len=strlen(coordinates);

    if(r<=9 && len>3){
        return 0;
    }

    if(r==0 || r>19 || r<1){
        return 0;
    }

    return 1;
    
}


//convert the X coordinate alphabet to a number ranging from 0-18
int convert_x_coordinate(char* coordinate){
    char c= coordinate[0];
    int ascii_value=c-65;
    return ascii_value;
}

int convert_y_coordinate(char* coordinate){
    int r= atoi(&coordinate[1]);
    r=r-1;
    return r;
}

//check if there is a match of 5 consecutive matches horizontally
int check_horizontal(int player_moves[19][19]){
    int count=0;
    int yes=0;

    for(int y=0;y<19; y++){       
        for(int x=0; x<19; x++){
            if (player_moves[x][y]==1){
                count++;
            }
            else{
                count=0;
            }

            if(count==5){
                yes=1;
                return yes;
            }
        }
    }

    return yes;
}


int check_vertical(int player_moves[19][19]){
    int count=0;
    int yes=0;

    for(int x=0;x<19; x++){       
        for(int y=0; y<19; y++){
            if (player_moves[x][y]==1){
                count++;
            }
            else{
                count=0;
            }

            if(count==5){
                yes=1;
                return yes;
            }
        }
    }
    return yes;
}



// //DOES NOT WORK, come back if have time
// void print_history(char **history, int count){
//     for(int i=0; i< count; i++){
//         printf("%s",history[i]);
//     }
//     printf("\n");
//}


int main(int argc, char *argv[]){
    
    //we use this number to determine which player's turn is it
    //0 indicates Black; 1 indicates White players turn 
    int active_player=0;    
    //win_flag is used to determine if the game is over
    int win_flag=0;

    char buf[BUFLEN];
    char history[361][4];
    int move_count=0;
    int b_moves[19][19];
    int w_moves[19][19];

    for(int i=0; i<19; i++){
        for(int y=0; y<19; y++){
            b_moves[i][y]=0;
            w_moves[i][y]=0;
        }
    }



    //Note: fgets adds an extra "\n" after reading from stdin
    while(fgets(buf, BUFLEN, stdin)!=NULL){

        //check if the input is longer than what buf can hold                              
        if(strchr(buf, '\n')==NULL){
            int whitespace_count = 0;
            int a=0;
            char copy_buf[BUFLEN];
            strcpy(copy_buf, buf);
            while(a<strlen(copy_buf)){
                if(copy_buf[a]==' '){
                    whitespace_count++;
                }
                a++;
            }

            int c;
            while((c=getc(stdin))!='\n' && c!=EOF){
                if(c==' '){
                    whitespace_count++;
                }
            }
            
            if(whitespace_count>1){
                printf("Invalid!\n");
                continue;
            }
          }

        //check if user input starts with a whitespace character  
        if(isspace(buf[0])!=0){
             printf("Invalid!\n");
             continue;
         }


        //WHO command logic
        if(strcmp("who\n", buf)==0){
            if(active_player==0){
                printf("B\n");
            }
            else if(active_player==1){
                printf("W\n");
            }
        }

        //TERM command logic
        else if(strcmp("term\n", buf)==0){
            exit(1);
        }

        //RESIGN command logic
        else if(strcmp("resign\n", buf)==0){
            if(active_player==0){
                printf("White wins!\n");
            }
            else if(active_player==1){
                printf("Black wins!\n");
            }

            //show history
            for(int i=0; i<move_count; i++){
                printf("%s", history[i]);
            }
            printf("\n");
            printf("Thank you for playing!\n");
            exit(0);
        }


        //HISTORY command logic
        else if(strcmp("history\n", buf)==0){
            for(int i=0; i<move_count; i++){
                printf("%s", history[i]);
            }
            printf("\n");
        }


        //VIEW command logic
        else  if(strcmp("view\n", buf)==0){

        }

        //PLACE <C><R> command logic
        //we first check "place" exist in the string inputted //strstr checks if substring exists in a string
        else if(strstr(buf, "place")!=NULL){     
            int buf_len=strlen(buf)-2;      
            int check=0;        
            char *coordinate=strtok(buf," ");  
            check=strcmp(coordinate, "place");
            coordinate=strtok(NULL, "");
            if(coordinate==NULL || isspace(coordinate[0]) ||isspace(buf[buf_len]) ||check!=0){
                printf("Invalid!\n");
                continue;
            }
            
            //chekc if the coordinates inputted is valid
            int validity=check_coordinate_validity(coordinate);
            if(validity==0){
                printf("Invalid coordinate\n");
                continue;
            }

            //check if coordinate is occupied
            int len=strcspn(coordinate, "\n");
            coordinate[len]='\0';
            // check history if the string exists there. If not place in history.
            int coordinate_occupied=0;
            for(int i=0; i<move_count; i++){
                if(strcmp(history[i],coordinate)==0){
                    printf("Occupied coordinate\n");
                    coordinate_occupied=1;
                    break;
                }
            }
            if(coordinate_occupied==1){
                continue;
            }

            
            //putting the coordinate in history
            strcpy(history[move_count], coordinate);
            move_count++;
            
            //check tie condition
            if (move_count==361 && win_flag==0){
                printf("Wow, a tie!\n");
                for(int i=0; i<361; i++){
                    printf("%s", history[i]);
                }
                printf("\n");
                printf("Thank you for playing!\n");
                exit(0);
            }

            
            if(active_player==0){
                b_moves[convert_x_coordinate(coordinate)][convert_y_coordinate(coordinate)]=1;

            }
            else if(active_player==1){
                w_moves[convert_x_coordinate(coordinate)][convert_y_coordinate(coordinate)]=1;
            }

            //check win condition
            if(active_player==0){
                if(check_horizontal(b_moves)==1 || check_vertical(b_moves)==1){
                    win_flag=1;
                }
            }
            else if(active_player==1){
                if(check_horizontal(w_moves)==1 || check_vertical(w_moves)==1){
                    win_flag=1;
                }
            }
            
            if(win_flag==1){
                if(active_player==1){
                    printf("White ");
                }
                else if(active_player==0){
                    printf("Black ");
                }
                printf("wins!\n");
                for(int i=0; i<move_count; i++){
                    printf("%s", history[i]);
                }
                printf("\n");
                printf("Thank you for playing!\n");
                exit(0);
            }

            if(active_player==0){
                active_player=1;
                
            }
            else if(active_player==1){
                active_player=0;
            }
            

        }
        else{
            printf("Invalid!\n");
        }       

    }


}