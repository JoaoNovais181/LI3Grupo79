#pragma once

#include "Structures.h"


int set_repo_id(char* line, GH_COMMIT commit);
int set_author_id(char* line, GH_COMMIT commit);
int set_commiter_id(char* line, GH_COMMIT commit);
int set_commit_at (char* line, GH_COMMIT commit);
int set_message (char* line, GH_COMMIT commit);
GH_COMMIT build_commit(char* line);
int write_commits_to_file (char* file_path, GH_COMMIT_ARRAY commits);
GH_COMMIT_ARRAY read_commits_from_file (char* file_path);
void sort_commit_array (GH_COMMIT *array, int beg, int end);