#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include//Structures.h"

int main ()
{
    FILE *f = fopen("../Ficheiros_Guiao_1/userstest.csv", "w");

    if (!f) return -1;

    fprintf(f, "id;login;type;created_at;followers;follower_list;following;following_list;public_gists;public_repos\n");

    for (int i = 3000001 ; i>0 ; i--)
        fprintf(f, "%d;cxt521;User;2015-11-20 05:45:13;3;[13426994, 17634081, 20762495];2;[13070645, 13426994];0;13\n", i);

    fclose(f);

    FILE *f2 = fopen("../Ficheiros_Guiao_1/commitstest.csv", "w");

    fprintf(f2, "repo_id;author_id;committer_id;commit_at;message\n");

    for (int i = 10000000 ; i>0 ; i--)
        fprintf(f2, "%d;30438508;30438508;2017-07-25 10:56:08;Set theme jekyll-theme-merlot\n", i);

    fclose(f2);

    FILE *f3 = fopen("../Ficheiros_Guiao_1/repostest.csv", "w");

    fprintf(f3, "id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size\n");

    for (int i = 10000000 ; i>0 ; i--)
        fprintf(f3, "%d;23609;lmanolov/mongo-session;Eclipse Public License 1.0;True;A mongodb session store for ring;Clojure;develop;2012-06-05 12:12:57;2013-01-09 12:47:30;0;0;1;75\n",i);

    fclose(f3);

    return 0;
}