#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef enum {Bot = 0 , Organization = 1, User = 2} Type;

struct tm lowest_year ();
struct tm current_year ();
int is_valid_date (struct tm date);
int isNum (char* str);
int strtonum (char* str, int *num);

typedef struct gh_user 
{
    int id;
    char *login;
    Type type;
    struct tm created_at;
    int followers;
    int *follower_list;
    int following;
    int *following_list;
    int public_gists;
    int public_repos;
} *GH_USER;

typedef struct gh_user_array 
{
    int max_size;
    int size;
    GH_USER *array;
} *GH_USER_ARRAY;

typedef struct gh_commit
{
    int repo_id;
    int author_id;
    int commiter_id;
    struct tm commit_at;
    char* message;
} *GH_COMMIT;

typedef struct gh_commit_array
{
    int max_size;
    int size;
    GH_COMMIT *array;
} *GH_COMMIT_ARRAY;


typedef struct gh_repo
{
    int id;
    int owner_id;
    char* full_name;
    char* license;
    int has_wiki;
    char* description;
    char* language;
    char* default_branch;
    struct tm created_at;
    struct tm updated_at;
    int forks_count;
    int open_issues;
    int stargazers_count;
    int size;
} *GH_REPO;

typedef struct gh_repo_array
{
    int max_size;
    int size;
    GH_REPO *array;
} *GH_REPO_ARRAY;