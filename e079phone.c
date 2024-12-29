#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 3
#define FILENAME "contacts.dat"

//Structure for user's credentials
typedef struct UserCredentials
{
    char username[50];
    char password[20];
}user;

//structure for Diet App Profile stats
typedef struct profiles {
    char name[50];
    double height;
    double weight; 
} prof;

//structure for calorie tracker for Diet App
typedef struct food {
    char name[50];
    double calories;
} cal;

//structure for contacts app 
typedef struct {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

//Function to check validity of password (8 or more characters)
int isValidPassword(char password[]) 
{
    if (strlen(password) >= 8)
    return 1;
    else
    return 0;
}

//authenticate userID and password
int authenticateUser(user users[], int size, char email[], char password[]) 
{
    for (int i = 0; i < size; i++) 
    {
        if(strcmp(users[i].username, email) == 0 && strcmp(users[i].password, password) == 0) 
        return 1;
    }
    return 0;
}

void initializeBoard(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++)
        board[i][j] = ' ';
    }
}

void printBoard(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
        printf("---|---|---\n");
    }
    printf("\n");
}

int checkWin(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) 
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
        return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    return 1;

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    return 1;
    return 0;
}

int isBoardFull(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (board[i][j] == ' ')
            return 0;
        }
    }
    return 1;
}

int noughtsandcrosses() {
    char board[SIZE][SIZE];
    int row, col;
    int a, b, turn = 0; // Even terms for player 'X', Odd terms for player 'O'
    char currentPlayer;

    printf("------NOUGHTS AND CROSSES-------\n\n");
    initializeBoard(board);

    while (1) 
    {
        printBoard(board);
        if (turn % 2 == 0)
        currentPlayer = 'X';
        else
        currentPlayer = 'O';

        // Input from the current player
        printf("Player %c, enter row (1-3) and column (1-3): ", currentPlayer);
        scanf("%d %d", &a, &b);

        row = a-1;
        col = b-1;
        // Check if the position is valid and empty
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') 
        {
            printf("Invalid move! Try again.\n\n");
            continue;
        }
        board[row][col] = currentPlayer;

        // Check for win or draw
        if (checkWin(board, currentPlayer)) 
        {
            printBoard(board);
            printf("Player %c wins!\n\n", currentPlayer);
            break;
        }

        if (isBoardFull(board)) 
        {
            printBoard(board);
            printf("It's a draw!\n\n");
            break;
        }
        turn++;
    }
    return 0;
}

int dietapp() {
    prof e079[3] = {{"Naren",160,60},{"Aadhithya",180,95},{"Hemnath",183,70}};
    printf("Welcome to Nutriboom\n");
    printf("Choose your profile (1-3): ");
    int i;
    scanf("%d", &i);
    i--;  // Adjusting index for 0-based array (since user inputs 1, 2, or 3)

    printf("Enter a choice to do the following\n1. View your current stats\n2. Check your current diet plan\nIf you wish to exit the app press 0!\n");
    int fmenu;
    scanf("%d", &fmenu);

    while (fmenu != 0) {
        switch (fmenu) {
            case 1: 
                printf("You have chosen to view your stats\n"); 
                // For viewing stats (height, weight, BMI)
                double BMI;
                char mode = 'V', modify;
                while (mode != 'e' && mode != 'E') {
                    switch (mode) {  
                        case 'v': 
                        case 'V':  
                            printf("Here are your stats\nHeight(in cm): %.2lf\nWeight(in kg): %.2lf\nBMI: %.2lf\n",
                                    e079[i].height, e079[i].weight,
                                    (e079[i].weight / pow((e079[i].height / 100), 2)));
                            printf("Would you like to modify any stat? press M for modifying\nIf you wish to exit press E\n");

                            getchar();  // To clear the newline character left by the previous scanf
                            scanf("%c", &mode);
                            break;
                        
                        case 'm':
                        case 'M':  
                            printf("Click a key\nH-Height\nW-Weight\nE-Exit\n");

                            getchar();  // To clear the newline character left by the previous scanf
                            scanf("%c", &modify);

                            while (modify != 'E' && modify != 'e') {
                                switch (modify) { // Decides which stat is modified
                                    case 'h':
                                    case 'H': 
                                        printf("Please enter new height\n");
                                        getchar();  // To clear the newline character
                                        scanf("%lf", &e079[i].height); 
                                        break;

                                    case 'w':
                                    case 'W':   
                                        printf("Enter new weight\n");
                                        getchar();  // To clear the newline character
                                        scanf("%lf", &e079[i].weight);
                                        break;

                                    default:    
                                        printf("Invalid choice. Try again\n");
                                        break;
                                }

                                printf("Updated stats\n");
                                printf("Height: %.2lf\n", e079[i].height);
                                printf("Weight: %.2lf\n", e079[i].weight);
                                BMI = e079[i].weight / pow((e079[i].height / 100), 2);
                                printf("BMI: %.2lf\n", BMI);

                                printf("Want to modify another stat? (H/W) or press E for exit\n"); 
                                getchar();
                                scanf("%c", &modify);
                                if (modify == 'e' || modify == 'E')
                                    mode = 'V';
                            }
                            break;
                    }
                }
                break;

            case 2: 
                printf("You have chosen to track your calories\n");
                // Entering calorie tracker
                cal *foodItem = NULL;
                int count = 0;
                char calChoice;
                do {
                    foodItem = realloc(foodItem, (count + 1) * sizeof(cal));
                    if (foodItem == NULL) {
                        printf("Memory allocation failed. Exiting program.\n");
                        return 1;
                    }

                    printf("\nEnter food item name: ");
                    getchar();  // Clear newline left by previous input
                    fgets(foodItem[count].name, 50, stdin);
                    foodItem[count].name[strcspn(foodItem[count].name, "\n")] = 0; // Remove newline

                    printf("Enter calorie count for %s: ", foodItem[count].name);
                    scanf("%lf", &foodItem[count].calories);

                    count++;

                    printf("\nDo you want to add another item? (y/n): ");
                    scanf(" %c", &calChoice); // Note space before %c to skip any lingering newline
                } while (calChoice == 'y' || calChoice == 'Y');

                printf("\nTracked Food Items:\n");
                for (int i = 0; i < count; i++) {
                    printf("%d. %s: %.2lf calories\n", i + 1, foodItem[i].name, foodItem[i].calories);
                }
                printf("\nTotal number of items tracked: %d\n", count);

                free(foodItem);  // Free allocated memory
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }

        printf("\nEnter a choice to do the following\n1. View your current stats\n2. Check your current diet plan\nIf you wish to exit the app press 0!\n");
        scanf("%d", &fmenu);  // Asking for menu again
    }

    printf("Thank you for using Nutriboom! Goodbye.\n");
    return 0;
}

// Function prototypes
void addContact();
void viewContacts();
void editContact();
void deleteContact();
void saveContacts(Contact *contacts, int count);
int loadContacts(Contact **contacts);

int contactApp() {
    int choice;

    while(1) {
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume newline character left by scanf

        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void addContact() {
    Contact newContact;
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }

    printf("Enter Name: ");
    fgets(newContact.name, 50, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0';  // Remove newline character
    printf("Enter Phone: ");
    fgets(newContact.phone, 15, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';  // Remove newline character
    printf("Enter Email: ");
    fgets(newContact.email, 50, stdin);
    newContact.email[strcspn(newContact.email, "\n")] = '\0';  // Remove newline character

    fwrite(&newContact, sizeof(Contact), 1, file);
    fclose(file);
    printf("Contact added successfully.\n");
}

void viewContacts() {
    FILE *file = fopen(FILENAME, "r");
    Contact contact;
    if (file == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("\nStored Contacts:\n");
    while (fread(&contact, sizeof(Contact), 1, file)) {
        printf("\nName: %s\nPhone: %s\nEmail: %s\n", contact.name, contact.phone, contact.email);
    }
    fclose(file);
}

void editContact() {
    Contact *contacts;
    int count = loadContacts(&contacts);
    if (count == 0) {
        printf("No contacts to edit.\n");
        return;
    }

    int index;
    printf("Enter the index of the contact to edit (1 to %d): ", count);
    scanf("%d", &index);
    getchar(); // To consume newline character left by scanf

    if (index < 1 || index > count) {
        printf("Invalid index.\n");
        free(contacts);
        return;
    }

    
    printf("Editing Contact: %s\n", contacts[index].name);
    printf("Enter new Name: ");
    fgets(contacts[index].name, 50, stdin);
    contacts[index].name[strcspn(contacts[index].name, "\n")] = '\0';  // Remove newline character
    printf("Enter new Phone: ");
    fgets(contacts[index].phone, 15, stdin);
    contacts[index].phone[strcspn(contacts[index].phone, "\n")] = '\0';  // Remove newline character
    printf("Enter new Email: ");
    fgets(contacts[index].email, 50, stdin);
    contacts[index].email[strcspn(contacts[index].email, "\n")] = '\0';  // Remove newline character

    saveContacts(contacts, count);
    free(contacts);
    printf("Contact edited successfully.\n");
}

void deleteContact() {
    Contact *contacts;
    int count = loadContacts(&contacts);
    if (count == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    int index;
    printf("Enter the index of the contact to delete (1 to %d): ", count);
    scanf("%d", &index);
    getchar(); // To consume newline character left by scanf

    if (index < 1 || index > count) {
        printf("Invalid index.\n");
        free(contacts);
        return;
    }

    index -= 1;  // Convert to 0-based index
    for (int i = index; i < count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }

    // Reduce the count of contacts and save the updated list
    count--;
    saveContacts(contacts, count);
    free(contacts);
    printf("Contact deleted successfully.\n");
}

void saveContacts(Contact *contacts, int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }

    fwrite(contacts, sizeof(Contact), count, file);
    fclose(file);
}

int loadContacts(Contact **contacts) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        *contacts = NULL;
        return 0;
    }

    // Get the number of contacts
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    int count = size / sizeof(Contact);
    fseek(file, 0, SEEK_SET);

    // Allocate memory and read contacts into array
    *contacts = (Contact *)malloc(size);
    if (*contacts == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 0;
    }

    fread(*contacts, sizeof(Contact), count, file);
    fclose(file);
    return count;
}

int calendarApp() 
{
    int option;

    do{
    printf("--------CALENDAR--------\n");
    printf("1. Check Date And Time\n");
    printf("2. Monthly Calendar\n");
    printf("3. Yearly Calendar\n");
    printf("4. Exit\n\n");
    printf("Enter option (1-3): ");

    scanf("%d",&option);
    
    switch(option)
    {
        case 1: printf("\n");
                system("date");
                printf("\n");
                break;
        case 2: system("cal");
                break;
        case 3: system("cal 2024");
                break;
        case 4: printf("Exiting Calendar App :)\n\n");
                break;
        default: printf("Invalid Option!!! Try Again\n");
    }
    }while(option!=4);
return 0;
}

int main() 
{
    char op1,op2,op3,op4,op5;
    user users[10];
    FILE *ptr;
    ptr=fopen("credentials.dat","rb");

    int i=0, numberUsers=5;
    while(fscanf(ptr,"%s\n%s",users[i].username,users[i].password)==2 && i<10) 
    i++;

   //Validation:
    int flag=0,option=0;
    char username[50], password[20];
    printf("WELCOME TO E079 PHONE:\n");
    while(flag!=1)
    {
        {
            printf("1. Login to the phone\n");
            printf("2. Exit\n");
            printf("To create new user: Get permission from existing user:\n");
            printf("Enter option: ");
            scanf("%d",&option);

            if(option==1) {
            printf("Enter Username: ");
            scanf("%s", username);
            
            printf("Enter Password: ");
            scanf("%s", password);

                if (authenticateUser(users,5,username,password)) 
                    {
                            printf("Login successful\n\n");
                            
                            do{
                            printf("\n===================================================\n");
                            printf("|                  APPLICATION MENU               |\n");
                            printf("===================================================\n");
                            printf("|  ---------------------   ---------------------  |\n");
                            printf("|  |        [1]        |   |        [2]        |  |\n");
                            printf("|  | Noughts and Cross |   |    Diet Tracker   |  |\n");
                            printf("|  |   (Tic Tac Toe)   |   |    And  Manager   |  |\n");
                            printf("|  ---------------------   ---------------------  |\n");
                            printf("|                                                 |\n");
                            printf("|  -------------   -------------   ------------- |\n");
                            printf("|  |    [3]    |   |    [4]    |   |    [5]    |  |\n");
                            printf("|  |  Contacts |   |  Calendar |   |    Exit   |  |\n");
                            printf("|  -------------   -------------   -------------  |\n");
                            printf("===================================================\n");
                            printf("Enter your choice (1-5): ");
                            scanf("%d", &option);

                            switch(option) {
                                case 1: noughtsandcrosses();
                                        break;

                                case 2: dietapp();
                                        break;

                                case 3: contactApp();
                                        break;

                                case 4: calendarApp();
                                        break;

                                case 5: printf("Exiting Application Menu :)\n\n");
                                        break;

                                default: printf("Invalid Option! Please try again :)\n\n");
                                printf("Do you want to clear the application? Yes(y)/No(n): ");
                                        scanf("%c",&op5);
                                        if(op5=='y')
                                        system("clear");
                                        break;
                            }

                        }while(option!=5);
                    }
                    else
                    printf("Invalid credentials\n\n");
                }
            
            else if(option==2)
            {
            printf("Exiting E079 Phone!!!\n\n");
            break;
            }

            else
            printf("Enter Valid Option!!!\n\n");
        }
    }
    return 0;
    fclose(ptr);
}