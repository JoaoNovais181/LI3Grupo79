#include "include/Repos.h"

int set_id_repo (char* line, GH_REPO repo)
{
    int valid = strtonum(line, &(repo->id));

    return repo->id && valid;
}

int set_owner_id (char* line, GH_REPO repo)
{
    int valid = strtonum(line, &(repo->owner_id));

    return repo->owner_id && valid;
}

int set_forks_count (char* line, GH_REPO repo)
{
    int valid = strtonum(line, &(repo->forks_count));

    return  valid;
}

int set_open_issues (char* line, GH_REPO repo)
{
    int valid = strtonum(line, &(repo->open_issues));

    return  valid;
}

int set_stargazers_count (char* line, GH_REPO repo)
{
    int valid = strtonum(line, &(repo->stargazers_count));

    return  valid;
}

int set_size (char* line, GH_REPO repo)
{
    int val = atoi(line);
    repo->size = val;

    return (val >= 0) ; //&& isNum(line);
}

int set_full_name (char* line, GH_REPO repo)
{
    repo->full_name = strdup(line);

    return strlen(line) > 0;
}

int set_license (char* line, GH_REPO repo)
{
    repo->license = strdup(line);

    return strlen(line) > 0;
}

int set_description (char* line, GH_REPO repo)
{
    repo->description = strdup(line);

    return strlen(line) > 0;
}

int set_default_branch (char* line, GH_REPO repo)
{
    repo->default_branch = strdup(line);

    return strlen(line) > 0;
}

int set_language (char* line, GH_REPO repo)
{
    repo->language = strdup(line);

    return strlen(line) > 0;
}

int set_has_wiki (char* line, GH_REPO repo)
{
    if (!strcmp(line, "False")) repo->has_wiki = 0;
    else if (!strcmp(line, "True")) repo->has_wiki = 1;
    else return 0;

    return 1;
}

int set_created_at_repo (char* line, GH_REPO repo)
{
    if (strlen(line)<19) return 0;   // Se a linha tiver menos de 19 caracteres não tem informação suficente para fazer o parse


    sscanf(line, "%d-%d-%d %d:%d:%d", &repo->created_at.tm_year, &repo->created_at.tm_mon, &repo->created_at.tm_mday, &repo->created_at.tm_hour, &repo->created_at.tm_min, &repo->created_at.tm_sec);
    repo->created_at.tm_year -= 1900; 
    repo->created_at.tm_mon -= 1;     
    repo->created_at.tm_isdst = 1;
    repo->created_at.tm_wday = 3;
    repo->created_at.tm_yday = (repo->created_at.tm_mon * 30) + repo->created_at.tm_mday; 

    return (is_valid_date(repo->created_at)); 
}

int set_updated_at (char* line, GH_REPO repo)
{
    if (strlen(line)<19) return 0;   // Se a linha tiver menos de 19 caracteres não tem informação suficente para fazer o parse


    sscanf(line, "%d-%d-%d %d:%d:%d", &repo->updated_at.tm_year, &repo->updated_at.tm_mon, &repo->updated_at.tm_mday, &repo->updated_at.tm_hour, &repo->updated_at.tm_min, &repo->updated_at.tm_sec);
    repo->updated_at.tm_year -= 1900; 
    repo->updated_at.tm_mon -= 1;     
    repo->updated_at.tm_isdst = 1;
    repo->updated_at.tm_wday = 3;
    repo->updated_at.tm_yday = (repo->updated_at.tm_mon * 30) + repo->updated_at.tm_mday; 

    return (is_valid_date(repo->updated_at)); 
}

GH_REPO build_repo (char* line)
{
    GH_REPO repo = malloc(sizeof(struct gh_repo));  // Alocar memoria para o utilizador
    int i = 0;   // Contador de iteraçoes para auxilio ao metodo utilizado para fazer o parse da linha
    int valid = 1;    // Utilizado como bool para saber se o utilizador é valido ou nao, como auxilio ao metodo utilizador
    char* buffer;   // Variavel utilizada para fazer o parse da linha

    while  ((buffer = strsep(&line, ";\n")))     // Enquanto for possivel separar a linha por ; faz o parse dela
    {
        switch (i++)    // Dependendo do numero da iteraçao
        {
            case 0:    // Se for a primeira é o campo do id do repositorio
                valid = set_id_repo(buffer, repo);
                break;
            case 1:    // Se for a segunda é o campo do id do dono
                valid = set_owner_id(buffer, repo);
                break;
            case 2:    // Se for a terceira é o campo do nome completo do repositorio
                valid = set_full_name(buffer, repo);
                break;
            case 3:    // Se for a quarta é o campo da licensa
                valid = set_license(buffer, repo);
                break;
            case 4:    // Se for a quinta é o campo do has_wiki
                valid = set_has_wiki(buffer, repo);
                break;
            case 5:    // Se for a sexta é o campo da descrição
                valid = set_description(buffer, repo);
                break;
            case 6:    // Se for a setima é o campo da linguagem
                valid = set_language(buffer, repo);
                break;
            case 7:    // Se for a oitava é o campo do nome do default branch
                valid = set_default_branch(buffer, repo);
                break;
            case 8:    // Se for a nona é o campo da data de criaçao
                valid = set_created_at_repo(buffer, repo);
                break;
            case 9:    // Se for a decima é o campo da data de update
                valid = set_updated_at(buffer, repo);
                break;
            case 10:    // Se for a decima primeira é o campo do numero de forks
                valid = set_forks_count(buffer, repo);
                break;
            case 11:    // Se for a decima segunda é o campo do numero de open issues
                valid = set_open_issues(buffer, repo);
                break;
            case 12:    // Se for a decima terceira é o campo do numero de stargazers
                valid = set_stargazers_count(buffer, repo);
                break;
            case 13:    // Se for a decima quarta é o campo do tamanho do repositorio
                valid = set_size(buffer, repo);
                break;
            default:   // Caso haja mais algum parse feito a partir da decima iteração, é considerado na mesma um utilizador valido
                valid = 1;
                break;
        }

        if (!valid)    // Se o utilizador nao for valido liberta a memoria ocupada pelo mesmo e retorna NULL
        {
            // printf("Invalido, id: %d iter: %d\n", repo->id, i);
            free(repo);
            return NULL;  
        }
        // i++;
    }

    free(line);      // Libertar o espaço ocupado pela linha
    return repo;      // Retorna o utilizador com as informaçoes provenientes do parse
}


GH_REPO_ARRAY read_repos_from_file (char* file_path)
{
    FILE *file = fopen(file_path, "r");
    if (!file) return NULL;
    char buffer[1000000], *buffer2;
    GH_REPO_ARRAY repos = malloc(sizeof(struct gh_repo_array));
    repos->max_size = 100;
    repos->size = 0;
    repos->array = (GH_REPO*)malloc(repos->max_size * sizeof(struct gh_repo));

    while (fgets(buffer, 1000000, file))
    {
        buffer2 = buffer;
        repos->array[repos->size] = build_repo(buffer2);

        if(repos->array[repos->size]) 
        {
            repos->size++;

            if (repos->max_size == repos->size)
            {
                repos->max_size += (int)((float)repos->max_size * 0.2);
                repos->array = (GH_REPO*)realloc(repos->array, repos->max_size * sizeof(struct gh_user));
            }
        }

    }

    fclose(file);


    sort_repo_array(repos->array, 0 , repos->size);

    return repos;
}

void write_repo_to_file (FILE *file, GH_REPO repo)
{
    fprintf(file, "%d;%d;%s;%s;%s;%s;%s;%s;%04d-%02d-%02d %02d:%02d:%02d;%04d-%02d-%02d %02d:%02d:%02d;%d;%d;%d;%d\n",
        repo->id, repo->owner_id, repo->full_name, repo->license, (repo->has_wiki) ?"True" :"False", repo->description, repo->language,
        repo->default_branch, repo->created_at.tm_year+1900, repo->created_at.tm_mon+1, repo->created_at.tm_mday, repo->created_at.tm_hour, repo->created_at.tm_min, repo->created_at.tm_sec,
        repo->updated_at.tm_year + 1900, repo->updated_at.tm_mon+1, repo->updated_at.tm_mday, repo->updated_at.tm_hour, repo->updated_at.tm_min, repo->updated_at.tm_sec,
        repo->forks_count, repo->open_issues, repo->stargazers_count, repo->size);
}

int write_repos_to_file (char* file_path, GH_REPO_ARRAY repos)
{
    if (!repos) return -1;
    
    FILE *file = fopen(file_path, "w");

    if (!file) return -1;

    fprintf(file, "id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size\n");

    for (int i = 0 ; i<repos->size ; i++)
        write_repo_to_file(file, repos->array[i]);
        
    fclose(file);

    return 0;
}


void sort_repo_array (GH_REPO *array, int inicio, int fim)
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
            GH_REPO temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    if (j>inicio)
        sort_repo_array(array, inicio, j+1);
    if (i<fim)
        sort_repo_array(array, i, fim);
}