#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Login struct
typedef struct {
	char username[10];
	char password[7];
} Login;

//Passenger struct
typedef struct node
{
	char ppsNumber[10];
	char firstName[50];
	char lastName[50];
	int yearBorn;
	char email[100];
	char travelFrom[10];
	char travelClass[12];
	char travelFrequency[50];

	struct node* NEXT;

}Passenger;

int login();

void main()
{
	Passenger* head = NULL;
	int choice;

    while (!login()) {
        printf("\nLogin failed. Try again.\n\n");
    }
    system("cls");
    printf("Login successful. Welcome to the Rail Ireland system!\n");

    return 0;
}

int login() {
    Login logins[3];
    FILE* fp = fopen("logins.txt", "r");
    if (!fp) {
        printf("Cannot open logins.txt\n");
        return 0;
    }

    for (int i = 0; i < 3; i++) {
        fscanf(fp, "%s %s", logins[i].username, logins[i].password);
    }
    fclose(fp);

    char inputUser[10], inputPass[7], ch;
    int i = 0;

    printf("Enter Username: ");
    scanf("%9s", inputUser);
    printf("Enter Password: ");

    i = 0;
    while ((ch = getch()) != '\r' && i < 6) {
        if (ch == '\b' && i > 0) {
            i--;
            printf("\b \b");
        }
        else if (ch != '\b') {
            inputPass[i++] = ch;
            printf("*");
        }
    }
    inputPass[i] = '\0';
    printf("\n");

    for (i = 0; i < 3; i++) {
        if (strcmp(logins[i].username, inputUser) == 0 &&
            strcmp(logins[i].password, inputPass) == 0) {
            return 1; // login success
        }
    }
    return 0;
}


