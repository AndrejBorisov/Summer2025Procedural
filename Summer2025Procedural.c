//github repository https://github.com/AndrejBorisov/Summer2025Procedural

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
	char travelFrom[15];
	char travelClass[15];
	char travelFrequency[50];

	struct node* NEXT;

}Passenger;

int login();
void addPassenger(Passenger** head);
void loadPassengers(Passenger** head);
void savePassengers(Passenger* head);
void clearInputBuffer();
void displayAll(Passenger* head);
void displayPassenger(Passenger* head);
void updatePassenger(Passenger* head);
void deletePassenger(Passenger** head);

Passenger* createPassengerNode(Passenger p);

void main()
{
	Passenger* head = NULL;
	int choice;

    while (!login()) {
        printf("\nLogin failed. Try again.\n\n");
        return 0;
    }
    system("cls");
    printf("Login successful. Welcome to the Rail Ireland system!\n");


    loadPassengers(&head);

    do {
        printf("\n--- Rail Ireland Passenger Statistics Menu ---\n");
        printf("1. Add passenger\n");
        printf("2. Display all passengers\n");
        printf("3. Display passenger details\n");
        printf("4. Update a passenger statistic\n");
        printf("5. Delete passenger\n");
        printf("6. Generate travel class statistics\n");
        printf("7. Print all passenger details into a report file\n");
        printf("8. List all passengers by year born\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
        case 1: addPassenger(&head);
            break;
        case 2: displayAll(head);
            break;
        case 3: displayPassenger(head);
            break;
        case 4: updatePassenger(head);
            break;
        case 5: deletePassenger(&head);
            break;
        case 0: savePassengers(head);
            printf("Exiting...\n");
            break;
        default: printf("Invalid input!\n");
        }
    } while (choice != 0);

    return 0;
}

//username: Adam, pass: Eve
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
            return 1;
        }
    }
    return 0;
}

//adding Passenger details
void addPassenger(Passenger** head) {
    Passenger p;

    printf("Enter PPS Number: ");
    fgets(p.ppsNumber, sizeof(p.ppsNumber), stdin);
    strtok(p.ppsNumber, "\n");

    printf("First Name: ");
    fgets(p.firstName, sizeof(p.firstName), stdin);
    strtok(p.firstName, "\n");

    printf("Last Name: ");
    fgets(p.lastName, sizeof(p.lastName), stdin);
    strtok(p.lastName, "\n");

    printf("Year Born: ");
    scanf("%d", &p.yearBorn);
    clearInputBuffer();

    printf("Email Address: ");
    fgets(p.email, sizeof(p.email), stdin);
    strtok(p.email, "\n");

    printf("Travel From (Dublin/Leinster/Connacht/Ulster/Munster): ");
    fgets(p.travelFrom, sizeof(p.travelFrom), stdin);
    strtok(p.travelFrom, "\n");

    printf("Travel Class (Economy/First Class): ");
    fgets(p.travelClass, sizeof(p.travelClass), stdin);
    strtok(p.travelClass, "\n");

    printf("Frequency (Less than 3/5, or More than 5 per year): ");
    fgets(p.travelFrequency, sizeof(p.travelFrequency), stdin);
    strtok(p.travelFrequency, "\n");

    Passenger* newNode = createPassengerNode(p);
    newNode->NEXT = *head;
    *head = newNode;

    savePassengers(*head);
}

//load from file
void loadPassengers(Passenger** head) {
    FILE* fp = fopen("passenger.txt", "r");
    if (!fp) return;

    Passenger p;
    while (fscanf(fp, "%s %s %s %d %s %s %s %[^\n]",
        &p.ppsNumber, p.firstName, p.lastName, &p.yearBorn,
        p.email, p.travelFrom, p.travelClass, p.travelFrequency) == 8) {
       
    }
    fclose(fp);
}

//save to file
void savePassengers(Passenger* head) {
    FILE* fp = fopen("passenger.txt", "w");
    Passenger* current = head;
    while (current) {
        fprintf(fp, "%s %s %s %d %s %s %s %s\n", current->ppsNumber,
            current->firstName, current->lastName, current->yearBorn,
            current->email, current->travelFrom,
            current->travelClass, current->travelFrequency);
        current = current->NEXT;
    }
    fclose(fp);
}

Passenger* createPassengerNode(Passenger p) {
    Passenger* newNode = (Passenger*)malloc(sizeof(Passenger));
    *newNode = p;
    newNode->NEXT = NULL;
    return newNode;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void displayAll(Passenger* head) 
{
    Passenger* cur = head;
    if (!cur) {
        printf("No passengers found.\n");
        return;
    }
    while (cur) {
        printf("%s %s %s %d %s %s %s %s\n",
            cur->ppsNumber, cur->firstName, cur->lastName,
            cur->yearBorn, cur->email, cur->travelFrom,
            cur->travelClass, cur->travelFrequency);
        cur = cur->NEXT;
    }
}

// Display one passenger (by PPS number)
void displayPassenger(Passenger* head) 
{
    char search[10];
    printf("Enter PPS Number: ");
    fgets(search, sizeof(search), stdin);
    strtok(search, "\n");

    Passenger* cur = head;
    while (cur) {
        if (strcmp(cur->ppsNumber, search) == 0) {
            printf("%s %s %s %d %s %s %s %s\n",
                cur->ppsNumber, cur->firstName, cur->lastName,
                cur->yearBorn, cur->email, cur->travelFrom,
                cur->travelClass, cur->travelFrequency);
            return;
        }
        cur = cur->NEXT;
    }
    printf("Passenger not found.\n");
}

void updatePassenger(Passenger* head) 
{
    char search[10];
    printf("Enter PPS Number to update: ");
    fgets(search, sizeof(search), stdin);
    strtok(search, "\n");

    Passenger* cur = head;
    while (cur) {
        if (strcmp(cur->ppsNumber, search) == 0) {
            printf("Updating %s %s\n", cur->firstName, cur->lastName);
            printf("Enter new email: ");
            fgets(cur->email, sizeof(cur->email), stdin);
            strtok(cur->email, "\n");
            printf("Enter new travel class: ");
            fgets(cur->travelClass, sizeof(cur->travelClass), stdin);
            strtok(cur->travelClass, "\n");
            printf("Enter new frequency: ");
            fgets(cur->travelFrequency, sizeof(cur->travelFrequency), stdin);
            strtok(cur->travelFrequency, "\n");
            printf("Updated successfully.\n");
            return;
        }
        cur = cur->NEXT;
    }
    printf("Passenger not found.\n");
}


void deletePassenger(Passenger** head) 
{
    char search[10];
    printf("Enter PPS Number to delete: ");
    fgets(search, sizeof(search), stdin);
    strtok(search, "\n");

    Passenger* cur = *head;
    Passenger* prev = NULL;

    while (cur) {
        if (strcmp(cur->ppsNumber, search) == 0) {
            if (prev) prev->NEXT = cur->NEXT;
            else *head = cur->NEXT;
            free(cur);
            printf("Passenger deleted.\n");
            savePassengers(*head);
            return;
        }
        prev = cur;
        cur = cur->NEXT;
    }
    printf("Passenger not found.\n");
}