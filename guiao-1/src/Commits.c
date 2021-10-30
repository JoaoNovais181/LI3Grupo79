#include "include/Commits.h"

int set_repo_id(char* line, GH_COMMIT commit)
{
    int valid = strtonum(line, &(commit->repo_id));

    return (commit->repo_id && valid);
}

int set_author_id(char* line, GH_COMMIT commit)
{
    int valid = strtonum(line, &(commit->author_id));

    return (commit->author_id && valid);
}

int set_commiter_id(char* line, GH_COMMIT commit)
{
    int valid = strtonum(line, &(commit->commiter_id));

    return (commit->commiter_id && valid);
}

int set_commit_at (char* line, GH_COMMIT commit)
{
    if (strlen(line)<19) return 0;   // Se a linha tiver menos de 19 caracteres não tem informação suficente para fazer o parse


    //Coloca na data os valores segundo o formato especificado
    sscanf(line, "%d-%d-%d %d:%d:%d", &commit->commit_at.tm_year, &commit->commit_at.tm_mon, &commit->commit_at.tm_mday, &commit->commit_at.tm_hour, &commit->commit_at.tm_min, &commit->commit_at.tm_sec);
    commit->commit_at.tm_year -= 1900; // Subtrai 1900 ao ano (porque na estrutura struct tm, o campo tm_year conta o numero de anos que passou desde 1900)
    commit->commit_at.tm_mon -= 1;     // Subtrai 1 ao mes (porque na estrutura struct tm, o campo tm_mon conta o numero de meses que passou desde janeiro)
    commit->commit_at.tm_isdst = 1;
    commit->commit_at.tm_wday = 3;
    commit->commit_at.tm_yday = (commit->commit_at.tm_mon * 30) + commit->commit_at.tm_mday; 

    return (is_valid_date(commit->commit_at));   // Retorna o valor que a função retorna, que é verdadeiro se estiver entre a data atual e 2005-07-04 00:00:00
}

int set_message (char* line, GH_COMMIT commit)
{
    commit->message = strdup(line);

    return 1;
}

GH_COMMIT build_commit(char* line)
{
    GH_COMMIT commit = malloc(sizeof(struct gh_commit));  // Alocar memoria para o utilizador
    int i = 0;   // Contador de iteraçoes para auxilio ao metodo utilizado para fazer o parse da linha
    int valid = 1;    // Utilizado como bool para saber se o utilizador é valido ou nao, como auxilio ao metodo utilizador
    char* buffer;   // Variavel utilizada para fazer o parse da linha

    while  ((buffer = strsep(&line, ";\n")) != NULL)     // Enquanto for possivel separar a linha por ; faz o parse dela
    {
        switch (i)    // Dependendo do numero da iteraçao
        {
            case 0:    // Se for a primeira é o campo do id do repositorio
                valid = set_repo_id(buffer, commit);
                break;
            case 1:    // Se for a segunda é o campo do id do autor
                valid = set_author_id(buffer, commit);
                break;
            case 2:    // Se for a terceira é o campo do id de quem deu commit
                valid = set_commiter_id(buffer, commit);
                break;
            case 3:    // Se for a quarta é o campo da data do commit
                valid = set_commit_at(buffer, commit);
                break;
            case 4:    // Se for a quinta é o campo do numero da mensagem
                valid = set_message(buffer, commit);
                break;
            default:   // Caso haja mais algum parse feito a partir da decima iteração, é considerado na mesma um utilizador valido
                valid = 1;
                break;
        }

        if (!valid)    // Se o utilizador nao for valido liberta a memoria ocupada pelo mesmo e retorna NULL
        {
            // printf("Invalido, id: %d\n", commit->repo_id);
            free(commit);
            return NULL;  
        }
        i++;
    }

    free(line);      // Libertar o espaço ocupado pela linha
    return commit;      // Retorna o utilizador com as informaçoes provenientes do parse
}

void write_commit_to_file (FILE *file, GH_COMMIT commit)
{
    fprintf(file, "%d;%d;%d;%04d-%02d-%02d %02d:%02d:%02d;%s\n", commit->repo_id, commit->author_id, commit->commiter_id, commit->commit_at.tm_year+1900, commit->commit_at.tm_mon+1, commit->commit_at.tm_mday, commit->commit_at.tm_hour, commit->commit_at.tm_min, commit->commit_at.tm_sec, commit->message);
}

int write_commits_to_file (char* file_path, GH_COMMIT_ARRAY commits)
{
    if (!commits) return  -1;
    
    FILE *file = fopen(file_path, "w");

    if (!file) return -1;

    fprintf(file, "repo_id;author_id;committer_id;commit_at;message\n");

    for (int i = 0 ; i<commits->size ; i++)
        write_commit_to_file(file, commits->array[i]);
    
    fclose(file);

    return 0;
}

GH_COMMIT_ARRAY read_commits_from_file (char* file_path)
{
    FILE *f = fopen(file_path, "r");
    GH_COMMIT_ARRAY commits = malloc(sizeof(struct gh_commit_array));
    commits->max_size = 100;
    commits->size = 0;
    commits->array = malloc(commits->max_size * sizeof(struct gh_commit));
    char buffer[1000000], *buffer2;

    while (fgets(buffer, 1000000, f))
    {
        buffer2 = buffer;
        commits->array[commits->size] = build_commit(buffer2);

        if (commits->array[commits->size]) 
        {
            commits->size++;

            if (commits->size==commits->max_size)
            {
                commits->max_size += (int)((float)commits->max_size * 0.2);
                commits->array = (GH_COMMIT*)realloc(commits->array, commits->max_size * sizeof(struct gh_commit));
            }
        }
    }

    fclose(f);


    sort_commit_array(commits->array, 0, commits->size);

    return commits;
}

void sort_commit_array (GH_COMMIT *array, int beg, int end)
{
    int i = beg, j = end-1;
    int pivot = array[(beg+end)/2]->repo_id;

    while (i<=j)
    {
        while ((array[i]->repo_id < pivot) && i<end)
            i++;
        while ((array[j]->repo_id > pivot) && j<beg)
            j--;

        if (i<=j)
        {
            GH_COMMIT temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    if (j>beg)
        sort_commit_array(array, beg, j+1);
    if (i<end)
        sort_commit_array(array, i, end);
}