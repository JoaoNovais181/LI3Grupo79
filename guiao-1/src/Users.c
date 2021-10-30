#include "include/Users.h"

char* type_to_str (Type type)  // Função que retorna a string correspondente ao valor da variável do tipo Type
{
    char* str = strdup ((type==Bot) ?"Bot" :((type==Organization ?"Organization" :"User")));
    return str;
}

void print_date (GH_USER usr)  // Funcao utilizada para imprimir na consola a data de criaçao
{
    printf("%02d-%02d-%02d %02d:%02d:%02d;", usr->created_at.tm_year + 1900, usr->created_at.tm_mon + 1, usr->created_at.tm_mday, usr->created_at.tm_hour, usr->created_at.tm_min, usr->created_at.tm_sec);
}

void write_date (FILE *file, GH_USER usr)  // Funcao utilizada para ecrever num ficheiro a data de criaçao
{
    fprintf(file, "%02d-%02d-%02d %02d:%02d:%02d;", usr->created_at.tm_year + 1900, usr->created_at.tm_mon + 1, usr->created_at.tm_mday, usr->created_at.tm_hour, usr->created_at.tm_min, usr->created_at.tm_sec);
}

void print_following_list (GH_USER usr) // Função utilizada para imprimir na consola a lista de utilizadores que segue
{
    if (usr->following == 0)
    {
        printf("[];");
    }
    else
    {
        printf("[");
        int i = 0;

        while (i<usr->following-1)
        {
            printf("%d, ", usr->following_list[i++]);
        }

        printf("%d]", usr->following_list[i]);
    }
}

void write_following_list (FILE *file, GH_USER usr) // Função utilizada para escrever num ficheiro a lista de utilizadores que segue
{
    if (usr->following == 0)
    {
        fprintf(file, "[];");
    }
    else
    {
        fprintf(file, "[");
        int i = 0;

        while (i<usr->following-1)
        {
            fprintf(file, "%d, ", usr->following_list[i++]);
        }

        fprintf(file, "%d]", usr->following_list[i]);
    }
}

void print_follower_list (GH_USER usr)  // Função utilizada para imprimir na consola a lista de seguidores
{
    if (usr->followers == 0)
    {
        printf("[];");
    }
    else
    {
        printf("[");
        int i = 0;

        while (i<usr->followers-1)
        {
            printf("%d, ", usr->follower_list[i++]);
        }

        printf("%d]", usr->follower_list[i]);
    }
}

void write_follower_list (FILE *file, GH_USER usr)  // Função utilizada para escrever num ficheiro a lista de seguidores
{
    if (usr->followers == 0)
    {
        fprintf(file, "[];");
    }
    else
    {
        fprintf(file, "[");
        int i = 0;

        while (i<usr->followers-1)
        {
            fprintf(file, "%d, ", usr->follower_list[i++]);
        }

        fprintf(file, "%d]", usr->follower_list[i]);
    }
}

int print_user_info (GH_USER usr) // Function used to print a user's information
{
    if(!usr) 
        return 0;

    printf("%d;", usr->id);
    printf("%s;", usr->login);
    printf("%s;", type_to_str(usr->type));
    print_date(usr);
    printf("%d;", usr->followers);
    print_follower_list(usr);
    printf("%d;", usr->following);
    print_following_list(usr);
    printf("%d;", usr->public_gists);
    printf("%d", usr->public_repos);
    putchar('\n');
    return 1;
}

int write_user_info (FILE *file, GH_USER usr)
{
    if(!usr) 
        return 0;

    fprintf(file, "%d;", usr->id);
    fprintf(file, "%s;", usr->login);
    fprintf(file, "%s;", type_to_str(usr->type));
    write_date(file, usr);
    fprintf(file, "%d;", usr->followers);
    write_follower_list(file, usr);
    fprintf(file, "%d;", usr->following);
    write_following_list(file, usr);
    fprintf(file, "%d;", usr->public_gists);
    fprintf(file, "%d", usr->public_repos);
    fputc('\n', file);
    return 1;
}

int set_pub_repo (char*line , GH_USER usr)
{
    int val = atoi(line);  // Extrair da linha o valor para colocar no campo
    usr->public_repos = val;

    return (val>=0);   // Retorna 1 se o valor for nao negativo
}

int set_id (char*line , GH_USER usr)
{
    int val = atoi(line);  // Extrair da linha o valor para colocar no campo
    usr->id = val;

    return (val>=0 && isNum(line)); // retorna 1 se o valor for nao negativo e a linha conter apenas numeros
}

int set_followers (char*line , GH_USER usr)
{
    int val = atoi(line);  // Extrair da linha o valor para colocar no campo
    usr->followers = val;

    return (val>=0 && isNum(line)); // retorna 1 se o valor for nao negativo e a linha conter apenas numeros
}

int set_following (char*line , GH_USER usr)
{
    int val = atoi(line);  // Extrair da linha o valor para colocar no campo
    usr->following = val;

    return (val>=0 && isNum(line)); // retorna 1 se o valor for nao negativo e a linha conter apenas numeros
}

int set_type (char*line , GH_USER usr)   // Função utilizada para prenncher o campo do tipo
{
    if (!strcmp(line, "Bot")) usr->type = Bot;
    else if (!strcmp(line, "Organization")) usr->type = Organization;
    else if (!strcmp(line, "User")) usr->type = User;
    else return 0;  // Se nao corresponder a nenhum dos tipos retorna 0


    return 1;
}

int set_public_gists (char*line , GH_USER usr)  // Função utilizada para prenncher o campo de public_gists
{
    int val = atoi(line);  // Extrair da linha o valor para colocar no campo  // Extrair da linha o valor para colocar no campo
    usr->public_gists = val;

    return (val>=0 && isNum(line)); // retorna 1 se o valor for nao negativo e a linha conter apenas numeros
}

int set_login (char*line , GH_USER usr)  // Função utilizada para preencher o campo do login
{
    usr->login = strdup(line);

    return (strlen(line) > 0);
}

int set_created_at (char* line, GH_USER usr)  // Funçao utilizada para preencher o campo da data de criaçao
{
    if (strlen(line)<19) return 0;   // Se a linha tiver menos de 19 caracteres não tem informação suficente para fazer o parse


    //Coloca na data os valores segundo o formato especificado
    sscanf(line, "%d-%d-%d %d:%d:%d", &usr->created_at.tm_year, &usr->created_at.tm_mon, &usr->created_at.tm_mday, &usr->created_at.tm_hour, &usr->created_at.tm_min, &usr->created_at.tm_sec);
    usr->created_at.tm_year -= 1900; // Subtrai 1900 ao ano (porque na estrutura struct tm, o campo tm_year conta o numero de anos que passou desde 1900)
    usr->created_at.tm_mon -= 1;     // Subtrai 1 ao mes (porque na estrutura struct tm, o campo tm_mon conta o numero de meses que passou desde janeiro)
    usr->created_at.tm_isdst = 1;
    usr->created_at.tm_wday = 3;
    usr->created_at.tm_yday = (usr->created_at.tm_mon * 30) + usr->created_at.tm_mday; 

    return (is_valid_date(usr->created_at));   // Retorna o valor que a função retorna, que é verdadeiro se estiver entre a data atual e 2005-07-04 00:00:00
}


int set_following_list (char* line, GH_USER usr) // Função utilizada para preencher o campo da lista de a seguir
{
    int i = 0;
    usr->following_list = malloc(usr->following * sizeof(int));  // Aloca memoria para o numero de pessoas que segue
    int valid = 1;   // Variavel usada como bool para auxiliar o parse
    char* buffer;

    while ((buffer = strsep(&line, ", ]")) != NULL)
    {
        if (isNum(buffer))   // Se o valor do buffer for uma string com numeros apenas faz o parse do numero
        {
            usr->following_list[i] = atoi(buffer);    // O valor do array de a seguir fica com o valor que esta na linha
            valid = (usr->following_list[i++] >  0);   // Se for um id nao valida variavel fica falsa
        }
    }

    if (usr->following != i)   // Se o numero de a seguir for diferente do numero de a seguir que deu parse é considerado invalido
        valid = 0;

    return valid;
}


int set_follower_list (char* line, GH_USER usr)  // Função utilizada para preencher o campo da lista de seguidores
{
    int i = 0;
    usr->follower_list = malloc(usr->followers * sizeof(int));    // Aloca memoria para o numero de seguidores que possui
    int valid = 1;  // Variavel usada como bool para auxiliar o parse
    char* buffer;

    while ((buffer = strsep(&line, ", ]")) != NULL)  
    {
        if (isNum(buffer))   // Se o valor do buffer for uma string com numeros apenas faz o parse do numero
        {
            usr->follower_list[i] = atoi(buffer);  // O valor do array de seguidores fica com o valor que esta na linha
            valid = (usr->follower_list[i++] >  0); // Se o seguidor tiver um id negativo não é valido
        }
    }

    if (usr->followers != i) // Se o numero de seguidores for diferente do numero de seguidores que deu parse é considerado invalido
        valid = 0;

    if (!valid) free(usr->follower_list);

    return valid;
}

GH_USER build_user(char *line)   // Função utilizada para criar o utilizador fazendo o parse da linha
{
    GH_USER usr = malloc(sizeof(struct gh_user));  // Alocar memoria para o utilizador
    int i = 0;   // Contador de iteraçoes para auxilio ao metodo utilizado para fazer o parse da linha
    int valid = 1;    // Utilizado como bool para saber se o utilizador é valido ou nao, como auxilio ao metodo utilizador
    char* buffer;   // Variavel utilizada para fazer o parse da linha


    /*   METODO UTILIZADO PARA O PARSE

        Para o parse o metodo utilizado foi o seguinte, existem funcoes para fazer a extraçao do buffer da informaçao relativa a esse campo, que retorna um bool
    que indica se esse campo foi preenchido com um valor válido ou não (por exemplo, no campo do if, se for um inteiro negativo retorna 0), sendo esse valor colocado
    na variável valid, e no final da iteração, se o valor de valid for falso (0), a função retorna NULL 

    */

    while  ((buffer = strsep(&line, ";\n")) != NULL)     // Enquanto for possivel separar a linha por ; faz o parse dela
    {
        switch (i++)    // Dependendo do numero da iteraçao
        {
            case 0:    // Se for a primeira é o campo do id
                valid = set_id(buffer, usr);
                break;
            case 1:    // Se for a segunda é o campo do login
                valid = set_login(buffer, usr);
                break;
            case 2:    // Se for a terceira é o campo do type
                valid = set_type(buffer, usr);
                break;
            case 3:    // Se for a quarta é o campo da data de criaçao
                valid = set_created_at(buffer, usr);
                break;
            case 4:    // Se for a quinta é o campo do numero de seguidores
                valid = set_followers(buffer, usr);
                break;
            case 5:    // Se for a sexta é o campo da lista de seguidores
                valid = set_follower_list(buffer+1, usr);
                break;
            case 6:    // Se for a setima é o campo do  numero de utilizadores que segue
                valid = set_following(buffer, usr);
                break;
            case 7:    // Se for a oitava é o campo da lista de utilizadores que segue
                valid = set_following_list(buffer+1,usr); 
                break;
            case 8:    // Se for a nona é o campo dos public gists
                valid = set_public_gists(buffer, usr);
                break;
            case 9:    // Se for a decima é o campo do numero de repositorios publicos
                valid = set_pub_repo(buffer, usr);
                break;
            default:   // Caso haja mais algum parse feito a partir da decima iteração, é considerado na mesma um utilizador valido
                valid = 1;
                break;
        }

        if (!valid)    // Se o utilizador nao for valido liberta a memoria ocupada pelo mesmo e retorna NULL
        {
            // printf("Iter: %d\n", i);
            free(usr);
            return NULL;  
        }
    }

    free(line);      // Libertar o espaço ocupado pela linha
    return usr;      // Retorna o utilizador com as informaçoes provenientes do parse
}

int write_users_to_file (char *path, GH_USER_ARRAY users)
{
    FILE *file = fopen(path, "w");
    
    if (!file) return -1;

    fprintf(file, "id;login;type;created_at;followers;follower_list;following;following_list;public_gists;public_repos\n");

    for (int i = 0 ; i<users->size ; i++)
        write_user_info(file, users->array[i]);

    fclose(file);

    return 0;
}


GH_USER_ARRAY read_users_from_file (char* file_path) // Função para ler do ficheiro em file_path os dados dos utilizadores e que coloca em N o numero total de utilizadores
{
    FILE *f = fopen(file_path, "r");  // Abrir o ficheiro em modo leitura

    if (!f) return NULL; // Se o ficheiro nao existir e f ficar NULL, retorna NULL

    char buffer[1000000], *buffer2;  // Buffer usado para guardar uma linha e buffer2 usado como auxiliar
    GH_USER_ARRAY users = malloc(sizeof(struct gh_user_array)); // Array de utilizadores, que é aconselhavel ser dinâmico
    users->max_size = 100;
    users->size = 0;
    users->array = calloc(users->max_size, sizeof(struct gh_user));

    while(fgets(buffer, 1000000, f)) // Enquanto ler uma linha continua o ciclo
    {
        buffer2 = buffer;  // Colocar buffer2 a apontar para o buffer
        users->array[users->size] = build_user(buffer2); // Construir o user


        if(users->array[users->size])   // Se o user existir incremento o numero de utilizadores
        {
            users->size++;

            if (users->size == users->max_size)   // Se for ocupado 100% do espaço do array é alocado mais 40% do tamanho atual
            {
                users->max_size += (int)((float)users->max_size * 0.2);   // Aumentar o tamanho máximo para mais 40% do atual
                users->array = (GH_USER *)realloc(users->array, users->max_size * sizeof(struct gh_user));   // Realocar a memória
            }
        }
        
    }

    fclose(f);

    sort_user_array(users->array, 0, users->size);

    return users;
}


void sort_user_array (GH_USER *array, int inicio, int fim)
{
    int i = inicio, j = fim-1;
    int pivot = array[(inicio + fim)/2]->id;

    while (i<=j)
    {
        while ((array[i]->id < pivot) && (i<fim))
            i++;

        while ((array[j]->id > pivot) && (j>inicio))
            j--;

        if (i<=j)
        {
            GH_USER temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    if (j>inicio)
        sort_user_array(array, inicio, j+1);
    if (i<fim)
        sort_user_array(array, i, fim);
}