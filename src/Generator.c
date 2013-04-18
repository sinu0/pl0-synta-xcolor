#include <fcntl.h>
#include "../include/Scanner.h"
#include "../include/Generator.h"
#include <stdlib.h>

char* bottom(){
  return "</pre</body><footer><div class=\"Footer\"><b>Copyright - 2013</b></div></footer></html>";
}

char* header(){
  return "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\"><html><head><rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\" /><meta http-equiv=\"content-type\" content=\"text/php; charset=utf-8\" /><title>PL0 syntax highlight </title></head><body bgcolor=#C9C7F0><pre >";
}

char* convertTokenToHtml(struct Token* token,char **colorTable){
  
  char *buffer =(char*)malloc(sizeof(char)*2048);
  if(buffer == NULL){
      perror("problem with malloc:");
      exit(EXIT_FAILURE);
  }

  memset(buffer,'\0',2048);
  if(token->type == whitespace){
    strcat(buffer,token->buffer);
    return buffer;
  }
  strcat(buffer,"<font color=#");
  strcat(buffer,colorTable[token->type]);
  strcat(buffer,">");
  strcat(buffer,token->buffer),
  strcat(buffer,"</font>"); 
  return buffer;
}
void converToHtml(char *path,char **colorTable)
{
   struct File file=init(path);
   struct Token token;
   FILE *f = createFile("./output.html");
   fwrite(header(),sizeof(char),strlen(header()),f);
   while(token.type != eof){
       token = scan(&file);
       appendTofile(convertTokenToHtml(&token,colorTable),f); 
   }
   fwrite(bottom(),sizeof(char),strlen(bottom()),f);
   fclose(f);
}

void appendTofile(char* string,FILE *file){
  fwrite(string,sizeof(char),strlen(string),file);
  free(string);  
}

FILE* createFile(char* name)
{
  FILE *f = fopen(name,"w+");
  if(f==NULL){
    perror("Problem with creation of file");
    exit(EXIT_FAILURE);
  }
  return f;
  
}

