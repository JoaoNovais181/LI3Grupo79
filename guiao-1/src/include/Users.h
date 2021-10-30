#pragma once

#include "Structures.h"


char* type_to_str (Type type);
void print_date (GH_USER usr) ;
void write_date (FILE *file, GH_USER usr);
void print_following_list (GH_USER usr) ;
void write_following_list (FILE *file, GH_USER usr);
void print_follower_list (GH_USER usr);
void write_follower_list (FILE *file, GH_USER usr) ;
int print_user_info (GH_USER usr);
int write_user_info (FILE *file, GH_USER usr);
int set_pub_repo (char*line , GH_USER usr);
int set_id (char*line , GH_USER usr);
int set_followers (char*line , GH_USER usr);
int set_following (char*line , GH_USER usr);
int set_type (char*line , GH_USER usr);
int set_public_gists (char*line , GH_USER usr);
int set_login (char*line , GH_USER usr);
int is_valid_date (struct tm date);
int set_created_at (char* line, GH_USER usr);
int set_following_list (char* line, GH_USER usr);
int set_follower_list (char* line, GH_USER usr);
GH_USER build_user(char *line);
int write_users_to_file (char *path, GH_USER_ARRAY users);
GH_USER_ARRAY read_users_from_file (char* file_path);
void sort_user_array (GH_USER *array, int inicio, int fim);