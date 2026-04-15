#ifndef USERMANAGEMENTSYSTEM_H
#define USERMANAGEMENTSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_GROUPS 4

typedef enum {
    root_user     = 0,
    system_users  = 201,
    operator_users = 1001,
    observer_users = 1002
} Groups;

typedef struct User {
    char        name[100];
    int         age;
    char        ID[50];
    int         groups[MAXIMUM_GROUPS];
    struct User *next_user;
} User;

User *init();
int   count_users(User *root);
void  print_user(User *root, const char *userID);
void  create_user(User *root, const char *name, int age, const char *ID, int groups[], int numGroups);
void  modify_user(User *root, const char *userID, const char *newName, int newAge, int newGroups[], int numGroups);
void  delete_user(User *root, const char *userID);
void  add_group(User *root, const char *userID, Groups group);
void  print_system(User *root);
void  export_system(User *root, const char *filename);

#endif
