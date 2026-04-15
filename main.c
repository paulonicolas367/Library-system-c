#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
    char bookName[50];
    char author[50];
    int code;
    int qntBk;
};

struct User
{
    char nameUser[80];
    char cpfUser[15];
    char email[90];
    char password[30];
    int phone;
    int borrowedBooks;
    int borrowedCode[10];
};

int main()
{
    struct Book *b = NULL;
    struct User *u = NULL;
    int option;
    int rightPassword = 123;
    int adminPassword;
    int qntBooks = 0;
    int qntUsers = 0;

    printf("Welcome to Library\n");

    do
    {
        printf("\nChoose the option:\n");
        printf("[1] Administrator Page\n");
        printf("[2] Client Page\n");
        printf("[0] Exit\n>");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            printf("Input your password: ");
            scanf("%d", &adminPassword);

            if (rightPassword == adminPassword)
            {
                int subOption;

                do
                {
                    printf("\nAdm Menu\n");
                    printf("[1] Add Book\n");
                    printf("[2] Delete Book\n");
                    printf("[3] List Books\n");
                    printf("[0] Return\n>");
                    scanf("%d", &subOption);

                    switch (subOption)
                    {
                    case 1:
                    {
                        struct Book *temp = realloc(b, (qntBooks + 1) * sizeof(struct Book));
                        if (temp == NULL)
                        {
                            printf("Memory error!\n");
                            break;
                        }
                        b = temp;

                        while (getchar() != '\n');

                        printf("Book Name: ");
                        fgets(b[qntBooks].bookName, 50, stdin);
                        b[qntBooks].bookName[strcspn(b[qntBooks].bookName, "\n")] = 0;

                        printf("Author: ");
                        fgets(b[qntBooks].author, 50, stdin);
                        b[qntBooks].author[strcspn(b[qntBooks].author, "\n")] = 0;

                        printf("Code: ");
                        scanf("%d", &b[qntBooks].code);

                        printf("Quantity: ");
                        scanf("%d", &b[qntBooks].qntBk);

                        qntBooks++;
                        break;
                    }

                    case 2:
                    {
                        if (qntBooks == 0)
                        {
                            printf("No books available!\n");
                            break;
                        }

                        for (int i = 0; i < qntBooks; i++)
                        {
                            printf("\n[%d] %s - %s (Code: %d | Qty: %d)\n",
                                   i + 1, b[i].bookName, b[i].author, b[i].code, b[i].qntBk);
                        }

                        int choice;
                        printf("Choose book to delete: ");
                        scanf("%d", &choice);

                        if (choice < 1 || choice > qntBooks)
                        {
                            printf("Invalid option!\n");
                            break;
                        }

                        for (int i = choice - 1; i < qntBooks - 1; i++)
                        {
                            b[i] = b[i + 1];
                        }

                        qntBooks--;

                        struct Book *temp = realloc(b, qntBooks * sizeof(struct Book));
                        if (temp != NULL)
                            b = temp;

                        printf("Book deleted!\n");
                        break;
                    }

                    case 3:
                    {
                        if (qntBooks == 0)
                        {
                            printf("No books registered.\n");
                            break;
                        }

                        for (int i = 0; i < qntBooks; i++)
                        {
                            printf("\n[%d] %s - %s (Code: %d | Qty: %d)\n",
                                   i + 1, b[i].bookName, b[i].author, b[i].code, b[i].qntBk);
                        }
                        break;
                    }

                    }

                } while (subOption != 0);
            }
            else
            {
                printf("Incorrect password!\n");
            }
            break;
        }

        case 2:
        {
            int subOption;

            do
            {
                printf("\nClient Page\n");
                printf("[1] Login\n");
                printf("[2] Register\n");
                printf("[0] Back\n>");
                scanf("%d", &subOption);

                switch (subOption)
                {
                case 1:
                {
                    char email[90];
                    char userPassword[30];
                    int userIndex = -1;

                    while (getchar() != '\n');

                    printf("Email: ");
                    fgets(email, 90, stdin);
                    email[strcspn(email, "\n")] = 0;

                    for (int i = 0; i < qntUsers; i++)
                    {
                        if (strcmp(u[i].email, email) == 0)
                        {
                            userIndex = i;
                            break;
                        }
                    }

                    if (userIndex == -1)
                    {
                        printf("Email not found!\n");
                        break;
                    }

                    printf("Password: ");
                    fgets(userPassword, 30, stdin);
                    userPassword[strcspn(userPassword, "\n")] = 0;

                    if (strcmp(u[userIndex].password, userPassword) == 0)
                    {
                        int userMenu;

                        do
                        {
                            printf("\nWelcome %s\n", u[userIndex].nameUser);
                            printf("[1] Take a Book\n");
                            printf("[0] Logout\n>");
                            scanf("%d", &userMenu);

                            if (userMenu == 1)
                            {
                                if (qntBooks == 0)
                                {
                                    printf("No books available!\n");
                                    break;
                                }

                                for (int i = 0; i < qntBooks; i++)
                                {
                                    printf("\n[%d] %s - %s (Qty: %d)\n",
                                           i + 1, b[i].bookName, b[i].author, b[i].qntBk);
                                }

                                int choice;
                                printf("Choose a book: ");
                                scanf("%d", &choice);

                                if (choice < 1 || choice > qntBooks)
                                {
                                    printf("Invalid option!\n");
                                    continue;
                                }

                                int index = choice - 1;

                                if (b[index].qntBk > 0)
                                {
                                    b[index].qntBk--;
                                    u[userIndex].borrowedBooks++;
                                    printf("Book borrowed successfully!\n");
                                }
                                else
                                {
                                    printf("No copies available!\n");
                                }
                            }

                        } while (userMenu != 0);
                    }
                    else
                    {
                        printf("Incorrect password!\n");
                    }

                    break;
                }

                case 2:
                {
                    struct User *temp = realloc(u, (qntUsers + 1) * sizeof(struct User));
                    if (temp == NULL)
                    {
                        printf("Memory error!\n");
                        break;
                    }
                    u = temp;

                    while (getchar() != '\n');

                    printf("Name: ");
                    fgets(u[qntUsers].nameUser, 80, stdin);
                    u[qntUsers].nameUser[strcspn(u[qntUsers].nameUser, "\n")] = 0;

                    printf("CPF: ");
                    fgets(u[qntUsers].cpfUser, 15, stdin);
                    u[qntUsers].cpfUser[strcspn(u[qntUsers].cpfUser, "\n")] = 0;

                    printf("Email: ");
                    fgets(u[qntUsers].email, 90, stdin);
                    u[qntUsers].email[strcspn(u[qntUsers].email, "\n")] = 0;

                    printf("Password: ");
                    fgets(u[qntUsers].password, 30, stdin);
                    u[qntUsers].password[strcspn(u[qntUsers].password, "\n")] = 0;

                    printf("Phone: ");
                    scanf("%d", &u[qntUsers].phone);

                    u[qntUsers].borrowedBooks = 0;
                    qntUsers++;

                    printf("User registered!\n");
                    break;
                }

                }

            } while (subOption != 0);

            break;
        }

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid option!\n");
        }

    } while (option != 0);

    free(b);
    free(u);

    return 0;

}
