#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UserManagementSystem.h"

int main() {
    User *rootUser = init();
    int choice;

    do {
        printf("\n===== User Management System =====\n");
        printf("1. Count users\n");
        printf("2. Print a user\n");
        printf("3. Create a user\n");
        printf("4. Modify a user\n");
        printf("5. Delete a user\n");
        printf("6. Add group to a user\n");
        printf("7. Print all users\n");
        printf("8. Export system to file\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Total users: %d\n", count_users(rootUser));
                break;
            }
            case 2: {
                char userID[50];
                printf("Enter user ID: ");
                scanf("%s", userID);
                print_user(rootUser, userID);
                break;
            }
            case 3: {
                char name[100], userID[50];
                int age, numGroups;
                int groups[MAXIMUM_GROUPS] = {-1, -1, -1, -1};

                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                printf("Enter ID: ");
                scanf("%s", userID);
                printf("How many groups (0-%d): ", MAXIMUM_GROUPS);
                scanf("%d", &numGroups);
                if (numGroups > MAXIMUM_GROUPS) numGroups = MAXIMUM_GROUPS;
                for (int i = 0; i < numGroups; i++) {
                    printf("  Group %d (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): ", i + 1);
                    scanf("%d", &groups[i]);
                }
                create_user(rootUser, name, age, userID, groups, numGroups);
                break;
            }
            case 4: {
                char userID[50], newName[100];
                int newAge, numGroups;
                int newGroups[MAXIMUM_GROUPS] = {-1, -1, -1, -1};

                printf("Enter user ID to modify: ");
                scanf("%s", userID);
                printf("Enter new name: ");
                scanf("%s", newName);
                printf("Enter new age: ");
                scanf("%d", &newAge);
                printf("How many groups (0-%d): ", MAXIMUM_GROUPS);
                scanf("%d", &numGroups);
                if (numGroups > MAXIMUM_GROUPS) numGroups = MAXIMUM_GROUPS;
                for (int i = 0; i < numGroups; i++) {
                    printf("  Group %d (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): ", i + 1);
                    scanf("%d", &newGroups[i]);
                }
                modify_user(rootUser, userID, newName, newAge, newGroups, numGroups);
                break;
            }
            case 5: {
                char userID[50];
                printf("Enter user ID to delete: ");
                scanf("%s", userID);
                delete_user(rootUser, userID);
                break;
            }
            case 6: {
                char userID[50];
                int group;
                printf("Enter user ID: ");
                scanf("%s", userID);
                printf("Enter group (0=root_user, 201=system_users, 1001=operator_users, 1002=observer_users): ");
                scanf("%d", &group);
                add_group(rootUser, userID, (Groups)group);
                break;
            }
            case 7: {
                print_system(rootUser);
                break;
            }
            case 8: {
                export_system(rootUser, "users.txt");
                break;
            }
            case 9: {
                printf("Exiting...\n");
                break;
            }
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 9);

    return 0;
}
