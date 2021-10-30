#pragma once

#include "Structures.h"

int set_id_repo (char* line, GH_REPO repo);
int set_owner_id (char* line, GH_REPO repo);
int set_forks_count (char* line, GH_REPO repo);
int set_open_issues (char* line, GH_REPO repo);
int set_stargazers_count (char* line, GH_REPO repo);
int set_size (char* line, GH_REPO repo);
int set_full_name (char* line, GH_REPO repo);
int set_license (char* line, GH_REPO repo);
int set_description (char* line, GH_REPO repo);
int set_default_branch (char* line, GH_REPO repo);
int set_language (char* line, GH_REPO repo);
int set_has_wiki (char* line, GH_REPO repo);
int set_created_at_repo (char* line, GH_REPO repo);
int set_updated_at (char* line, GH_REPO repo);
GH_REPO build_repo (char* line);
GH_REPO_ARRAY read_repos_from_file (char* file_path);
int write_repos_to_file (char* file_path, GH_REPO_ARRAY repos);
void sort_repo_array (GH_REPO *array, int inicio, int fim);
