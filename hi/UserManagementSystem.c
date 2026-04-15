#include "UserManagementSystem.h"

/* Helper: return group name string */
static const char *group_name(int g) {
    switch (g) {
        case root_user:      return "root_user";
        case system_users:   return "system_users";
        case operator_users: return "operator_users";
        case observer_users: return "observer_users";
        default:             return "unknown";
    }
}

/* Helper: print groups array */
static void print_groups(int groups[], FILE *out) {
    fprintf(out, "[");
    int first = 1;
    for (int i = 0; i < MAXIMUM_GROUPS; i++) {
        if (groups[i] != -1) {
            if (!first) fprintf(out, ", ");
            fprintf(out, "%s", group_name(groups[i]));
            first = 0;
        }
    }
    fprintf(out, "]");
}

/* Creates and returns the root user on the heap */
User *init() {
    User *root = (User *)malloc(sizeof(User));
    if (!root) {
        fprintf(stderr, "Memory allocation failed for root user.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(root->name, "root");
    root->age = 33;
    strcpy(root->ID, "0");
    root->groups[0] = root_user;
    root->groups[1] = system_users;
    root->groups[2] = operator_users;
    root->groups[3] = observer_users;
    root->next_user = NULL;
    return root;
}

/* Returns total number of users in the system */
int count_users(User *root) {
    int count = 0;
    User *cur = root;
    while (cur) {
        count++;
        cur = cur->next_user;
    }
    return count;
}

/* Prints a single user's details by ID */
void print_user(User *root, const char *userID) {
    User *cur = root;
    while (cur) {
        if (strcmp(cur->ID, userID) == 0) {
            printf("User ID : %s\n", cur->ID);
            printf("Name    : %s\n", cur->name);
            printf("Age     : %d\n", cur->age);
            printf("Groups  : ");
            print_groups(cur->groups, stdout);
            printf("\n");
            return;
        }
        cur = cur->next_user;
    }
    printf("User with ID '%s' not found.\n", userID);
}

/* Creates a new user and appends it to the end of the list */
void create_user(User *root, const char *name, int age, const char *ID, int groups[], int numGroups) {
    /* Prevent duplicate IDs */
    User *cur = root;
    while (cur) {
        if (strcmp(cur->ID, ID) == 0) {
            printf("Error: User with ID '%s' already exists.\n", ID);
            return;
        }
        cur = cur->next_user;
    }

    /* Prevent non-root users from being in root_user group */
    for (int i = 0; i < numGroups && i < MAXIMUM_GROUPS; i++) {
        if (groups[i] == root_user) {
            printf("Error: Only the root user can be in the root_user group.\n");
            return;
        }
    }

    User *newUser = (User *)malloc(sizeof(User));
    if (!newUser) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    strcpy(newUser->name, name);
    newUser->age = age;
    strcpy(newUser->ID, ID);

    for (int i = 0; i < MAXIMUM_GROUPS; i++)
        newUser->groups[i] = -1;
    for (int i = 0; i < numGroups && i < MAXIMUM_GROUPS; i++)
        newUser->groups[i] = groups[i];

    newUser->next_user = NULL;

    /* Append to end of list */
    cur = root;
    while (cur->next_user)
        cur = cur->next_user;
    cur->next_user = newUser;

    printf("User '%s' created successfully.\n", name);
}

/* Modifies an existing user's name, age, and groups */
void modify_user(User *root, const char *userID, const char *newName, int newAge, int newGroups[], int numGroups) {
    /* Root user cannot be modified */
    if (strcmp(userID, "0") == 0) {
        printf("Error: Root user cannot be modified.\n");
        return;
    }
    User *cur = root;
    while (cur) {
        if (strcmp(cur->ID, userID) == 0) {
            if (newName && strlen(newName) > 0)
                strcpy(cur->name, newName);
            if (newAge > 0)
                cur->age = newAge;
            if (newGroups && numGroups > 0) {
                for (int i = 0; i < MAXIMUM_GROUPS; i++)
                    cur->groups[i] = -1;
                for (int i = 0; i < numGroups && i < MAXIMUM_GROUPS; i++)
                    cur->groups[i] = newGroups[i];
            }
            printf("User '%s' modified successfully.\n", userID);
            return;
        }
        cur = cur->next_user;
    }
    printf("User with ID '%s' not found.\n", userID);
}

/* Deletes a user by ID — root user cannot be deleted */
void delete_user(User *root, const char *userID) {
    if (strcmp(userID, "0") == 0) {
        printf("Error: Root user cannot be deleted.\n");
        return;
    }
    User *cur = root;
    User *prev = NULL;
    while (cur) {
        if (strcmp(cur->ID, userID) == 0) {
            if (prev)
                prev->next_user = cur->next_user;
            free(cur);
            printf("User '%s' deleted successfully.\n", userID);
            return;
        }
        prev = cur;
        cur = cur->next_user;
    }
    printf("User with ID '%s' not found.\n", userID);
}

/* Adds a group to a user — max 4 groups */
void add_group(User *root, const char *userID, Groups group) {
    /* Only root can be in root_user group */
    if (group == root_user && strcmp(userID, "0") != 0) {
        fprintf(stderr, "Error: Only the root user can be in the root_user group.\n");
        return;
    }
    User *cur = root;
    while (cur) {
        if (strcmp(cur->ID, userID) == 0) {
            for (int i = 0; i < MAXIMUM_GROUPS; i++) {
                if (cur->groups[i] == (int)group) {
                    printf("User '%s' is already in that group.\n", userID);
                    return;
                }
            }
            for (int i = 0; i < MAXIMUM_GROUPS; i++) {
                if (cur->groups[i] == -1) {
                    cur->groups[i] = (int)group;
                    printf("Group added to user '%s' successfully.\n", userID);
                    return;
                }
            }
            fprintf(stderr, "Error: User '%s' already has the maximum number of groups.\n", userID);
            return;
        }
        cur = cur->next_user;
    }
    printf("User with ID '%s' not found.\n", userID);
}

/* Prints all users in the system */
void print_system(User *root) {
    printf("\n%-10s %-20s %-6s %s\n", "User ID", "User Name", "Age", "Groups");
    printf("--------------------------------------------------------------\n");
    User *cur = root;
    while (cur) {
        printf("%-10s %-20s %-6d ", cur->ID, cur->name, cur->age);
        print_groups(cur->groups, stdout);
        printf("\n");
        cur = cur->next_user;
    }
}

/* Exports all users to a file */
void export_system(User *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Failed to open file '%s' for writing.\n", filename);
        return;
    }
    fprintf(file, "%-10s %-20s %-6s %s\n", "User ID", "User Name", "Age", "Groups");
    fprintf(file, "--------------------------------------------------------------\n");
    User *cur = root;
    while (cur) {
        fprintf(file, "%-10s %-20s %-6d ", cur->ID, cur->name, cur->age);
        print_groups(cur->groups, file);
        fprintf(file, "\n");
        cur = cur->next_user;
    }
    fclose(file);
    printf("System exported to '%s' successfully.\n", filename);
}
