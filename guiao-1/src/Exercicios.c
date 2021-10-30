#include "include/Exercicios.h"

int Exercicio1 ()
{
    clock_t fst, snd;
    
    fst = clock();

    GH_USER_ARRAY array_users = read_users_from_file("entrada/users.csv");

    if (write_users_to_file("saida/users-ok.csv", array_users) == -1) return -1;

    GH_COMMIT_ARRAY array_commits = read_commits_from_file("entrada/commits.csv");

    if (write_commits_to_file("saida/commits-ok.csv", array_commits) == -1) return -1;

    GH_REPO_ARRAY array_repos = read_repos_from_file("entrada/repos.csv");

    if (write_repos_to_file("saida/repos-ok.csv", array_repos) == -1) return -1;


    snd = clock();

    printf("A execuçao demorou %lf segundos a verificar %d Users, %d Commits e %d Repos\n", (double)(snd - fst) / CLOCKS_PER_SEC, array_users->size, array_commits->size, array_repos->size);

    return 0;
}

// int Ecercicio2 ()
// {
    // GH_USER_ARRAY = read_users_from_file("saida/users-ok.csv");
// }