/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 **/
void	str_lower(char *s) {
    for (; *s != '\0'; ++s) {
        *s = tolower(*s);
    }
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 **/
void	str_upper(char *s) {
    for (; *s != '\0'; ++s) {
        *s = toupper(*s);
    }
}

/**
 * Convert all characters in string to titlecase.
 * @param   s       String to convert
 **/
void	str_title(char *s) {
    *s = toupper(*s);
    ++s;

    for (; *s != '\0'; ++s) {
        if (!(isalpha(*(s-1)))) {
            *s = toupper(*s);
        } else {
            *s = tolower(*s);
        }
    }
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 **/
void    str_chomp(char *s) {
    s += strlen(s) - 1;
    if (*s == '\n') *s = '\0';
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 **/
void    str_strip(char *s) {
    char *end = s + strlen(s) - 1; 
    while ((end >= s) && isspace(*end)) --end; 

    char *start = s;
    while (isspace(*start)) ++start;
    
    while (start <= end) *(s++) = *(start++);
    *s = '\0';
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 **/
void    str_reverse(char *s) {
    char *end = s + strlen(s) - 1;
    while (end > s) {
        char temp = *s;
        *(s++) = *end;
        *(end--) = temp;
    }
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 **/
void    str_translate(char *s, char *from, char *to) {
    char trans[1<<8] = {'\0'};
    while ((*from != '\0') && (*to != '\0')) {
        trans[(int)*(from++)] = *(to++);
    }

    for (; *s != '\0'; ++s) {
        char t = trans[(int)*s];
        if (t != '\0') *s = t;
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
