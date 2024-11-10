#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char *buffer){
char *keywords[23]={"break", 
"case", "char", "const", "continue", 
"default", "do", "double", "else", 
"enum", "extern", "float", "goto", 
"if", "int", "long", "register",
"return", "while", "printf", "scanf", "void", "main"};

for (int i=0; i<23; i++){
    if (strcmp(keywords[i], buffer)==0){
        return 1;
    }
}
return 0;
}


    

int main(){
int ch, lineno=1, i=0;
char buffer[50], nextchar;
FILE *fp1, *fp2;
char operators[5]={'+', '-', '*', '/', '%'};
char relop[3]={'<', '>', '='};

//-----------initialization done--------------------------------------

fp1=fopen("input.txt", "r");
fp2=fopen("output.txt", "w");

//--------------files declared-----------------------------------

while ((ch=fgetc(fp1))!=EOF){
    if (ch=='\n'){
        lineno++;
        fprintf(fp2, "\n");
        }

//-------------line number updation done------------------------------------------------
    for (int i=0; i<5; i++){
        if (ch==operators[i]){
            fprintf(fp2, "%c\t -> Arithmetic Operator\n", ch);
        }
    }

//-------------operators--------------------------------------------

    if (ch=='<'||ch=='>'||ch=='='){
        nextchar=fgetc(fp1);
        if(nextchar=='='){
            if (ch=='<' && nextchar=='='){
                fprintf(fp2, "<=\t ->Relational Operator LTE\n");
            }
            if (ch=='>' && nextchar=='='){
                fprintf(fp2, ">=\t ->Relational Operator GTE\n");
            }
            if (ch=='=' && nextchar=='='){
                fprintf(fp2, "<=\t ->Relational Operator ET\n");
            } 
        }
        
        else{
            if (ch=='<'){
                fprintf(fp2, "<\t ->Relational Operator LT\n");
            }
            if (ch=='>'){
                fprintf(fp2, ">\t ->Relational Operator GT\n");
            }
            if (ch=='=' && nextchar!='='){
                fprintf(fp2, "=\t ->Assignment Operator\n");
            }
        }
        ungetc(nextchar, fp1);
    }

//---------------relational operator--------------------------------


    if (isalnum(ch)){
            buffer[i++]=(char)ch;}
    else {
     // End of a word
        buffer[i] = '\0';  // Null-terminate the word
        i = 0;
        
//--------------words taken in buffer------------------------------
    if (isKeyword(buffer)==1){
        fprintf(fp2, "%s\t -> keyword\n", buffer);
    }
//--------------keywords-----------------------------------------------
    else{
        if(strcmp(buffer, "a")==0 || strcmp(buffer, "b")==0|| strcmp(buffer, "c")==0){
        fprintf(fp2, "%s\t -> identifier\n", buffer);}
    }
    buffer[0]='\0';
//---------------identifier---------------------------------------------    
}

    
}


fclose(fp1);
fclose(fp2);
}




