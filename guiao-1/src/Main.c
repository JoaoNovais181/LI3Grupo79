#include "include/Exercicios.h"

int main (int argc, char const *argv[]) 
{
    if (argc == 1) return -1;

    for (int i = 1 ; i<argc ; i++)
    {
        if (!strcmp(argv[i], "Exercicio1")) 
            if (Exercicio1() == -1) return -1; 
    }

    return 0;
}