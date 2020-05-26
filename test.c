#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (){

    char  text[100];

    strcat(text,"Hello");
    printf("%s   \n",text);

   strcat(text,"\n");
    printf("%s   \n",text);

 strcat(text,"How are you?");
    printf("%s   \n",text);

    strcpy(text, "aaa");
    printf("%s\n",text);

return 0;

}