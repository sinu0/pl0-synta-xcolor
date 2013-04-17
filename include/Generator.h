/* 
 * File:   Generator.h
 * Author: mar
 *
 * Created on 17 kwiecień 2013, 19:52
 */

#ifndef GENERATOR_H
#define	GENERATOR_H
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


char* header();
struct Token getToken();
char* bottom();
char* convertTokenToHtml(struct Token *token,char **colorTable);
void converToHtml(char *path,char **colorTable);
void appendTofile(char *string,FILE *file);
FILE *createFile(char *name);
#endif	/* GENERATOR_H */

