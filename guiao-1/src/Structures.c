#include "include/Structures.h"

struct tm lowest_year ()
{
    struct tm rv;

    rv.tm_year = 105;
    rv.tm_mon  = 3;
    rv.tm_mday = 7;
    rv.tm_hour = 0;
    rv.tm_min  = 0;
    rv.tm_sec  = 0;

    return rv;
}

struct tm current_year ()
{
    time_t t = time(NULL);
    struct tm cur = *localtime(&t);

    return cur;
}

int is_valid_date (struct tm date)  // Retorna um bool que indica se a data esta entre a data atual e 2005-07-04 00:00:00
{
    time_t fst, snd, trd;
    // struct tm cur = current_year();

    fst = mktime(&date);
    snd = time(NULL);
    trd = 1112832000;

    return (difftime(snd, fst)) && (difftime(fst, trd));
}


int isNum (char* str)  // Funçao que retorna um bool dependendo se todos os caracteres na string são digitos/numeros ou nao
{
    if (!strlen(str)) return 0;

    for (int i = 0 ; str[i] ; i++) 
        if (!isdigit(str[i])) return 0;

    return 1;
}


int strtonum (char* str, int *num)
{
    *num = 0;
    for (int i = 0 ; str[i] ; i++)
    {
        if (isdigit(str[i]))
            (*num) = ((*num) * 10) + (str[i] - 48);
        else 
        {
            (*num) = 0;
            return 0;
        }
    }

    return 1;
}