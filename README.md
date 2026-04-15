# CUserManager(Project/Stage Name)
A C program implementing a linked-list based User Management System in C. Users can be created, modified, deleted, and organised into permission groups. The system enforces rules such as root user protection and a maximum of 4 groups per user, with support for printing and exporting the full user list.

# User Management System(Project Design)

A C console application that simulates a Unix-style user management system.
Users are stored as a singly linked list on the heap. The system enforces
permission group rules, protects the root user, and supports full CRUD
operations through an interactive menu.

---

## Project Structure
hi/
├── UserManagementSystem.h # Type definitions, macros, enum, function declarations
├── UserManagementSystem.c # Full implementation of all functions
└── main.c # Entry point, interactive menu

---

## Data Structures

### Macro
```c
#define MAXIMUM_GROUPS 4
Defines the maximum number of groups a user can belong to.

Groups Enumtypedef enum {
    root_user      = 0,
    system_users   = 201,
    operator_users = 1001,
    observer_users = 1002
} Groups;
Defines the four permission groups available in the system.

User Struct
typedef struct User {
    char        name[100];
    int         age;
    char        ID[50];
    int         groups[MAXIMUM_GROUPS];
    struct User *next_user;
} User;

name — the user's display name

age — the user's age

ID — unique string identifier (e.g. "0", "uniID6")

groups — array of up to 4 group values, unfilled slots default to -1

next_user — pointer to the next user in the linked list, NULL if last

Functions
User *init()
Creates and returns the root user on the heap.

Name: "root", Age: 33, ID: "0"

Groups: {root_user, system_users, operator_users, observer_users}

next_user set to NULL

The root user cannot be deleted or modified

The root user is the only user allowed in the root_user group

Example:
Program starts → root user automatically created

int count_users(User *root)
Traverses the linked list from root and returns the total number of users.

Example:
Enter your choice: 1
Total users: 1

void print_user(User *root, const char *userID)
Searches for a user by ID and prints their details in a formatted style.
Prints an error message if the user is not found.

Example:
Enter your choice: 2
Enter user ID: 0
User ID : 0
Name    : root
Age     : 33
Groups  : [root_user, system_users, operator_users, observer_users]

void create_user(User *root, const char *name, int age, const char *ID, int groups[], int numGroups)
Creates a new user on the heap and appends them to the end of the linked list.

Rejects duplicate IDs

Rejects any attempt to assign the root_user group to a non-root user

Unfilled group slots are set to -1

Example:
Enter your choice: 3
Enter name: Alice
Enter age: 25
Enter ID: uniID6
How many groups (0-4): 2
  Group 1 (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): 201
  Group 2 (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): 1002
User 'Alice' created successfully.

void modify_user(User *root, const char *userID, const char *newName, int newAge, int newGroups[], int numGroups)
Finds a user by ID and updates their name, age, and groups.

Root user (ID = "0") cannot be modified

Prints an error if the user is not found

Example:
Enter your choice: 4
Enter user ID to modify: uniID6
Enter new name: AliceUpdated
Enter new age: 26
How many groups (0-4): 1
  Group 1 (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): 1001
User 'uniID6' modified successfully.

void delete_user(User *root, const char *userID)
Finds a user by ID, unlinks them from the list, and frees their memory.

Root user (ID = "0") cannot be deleted

Prints an error if the user is not found

Example:
Enter your choice: 5
Enter user ID to delete: uniID6
User 'uniID6' deleted successfully.

Trying to delete root: Error: Root user cannot be deleted.

void add_group(User *root, const char *userID, Groups group)
Adds a group to the first available (-1) slot in the user's groups array.

Prints an error to stderr if the user already has 4 groups

Prevents adding root_user group to any non-root user

Prevents adding a duplicate group

Example:
Enter your choice: 6
Enter user ID: uniID6
Enter group (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): 1001
Group added to user 'uniID6' successfully.

If already at 4 groups: Error: User 'uniID6' already has the maximum number of groups.

void print_system(User *root)
Prints a formatted table of all users in the system.

Example:
Enter your choice: 7

User ID    User Name            Age    Groups
--------------------------------------------------------------
0          root                 33     [root_user, system_users, operator_users, observer_users]
uniID6     Alice                25     [system_users, observer_users]

void export_system(User *root, const char *filename)
Writes the same formatted table as print_system to a file (users.txt).
Creates the file if it does not exist, overwrites it if it does.

Example:
Enter your choice: 8
System exported to 'users.txt' successfully.

Creates users.txt in the same directory with the same table as option 7.

Menu Options
Option	Action
1	Count total users
2	Print a user by ID
3	Create a new user
4	Modify an existing user
5	Delete a user
6	Add a group to a user
7	Print all users
8	Export system to users.txt
9	Exit

Rules Enforced
Root user (ID = "0") cannot be deleted or modified

Only the root user can belong to the root_user group

Each user can belong to a maximum of 4 groups

Duplicate user IDs are not allowed

Unfilled group slots are stored as -1

How to Compile and Run
gcc -Wall -o UserManagementSystem UserManagementSystem.c main.c && ./UserManagementSystem

Copy
bash

```
Built With
C (C99)

Standard libraries: stdio.h, stdlib.h, string.h

Heap memory allocation via malloc / free

Singly linked list data structure


