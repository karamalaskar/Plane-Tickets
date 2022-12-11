#include "database.h"
#include "file.h"


void search_flight(node **database, char *flight)
{

    while (*database != NULL)
    {
        if (strcmp((*database)->data.number, flight) == 0)
        {
            printf("%s | %s | %s\n", (*database)->data.number, (*database)->data.cities, (*database)->data.date);
            break;
        }
        else
        {
            *database = (*database)->next;
        }
    }
}


char *search_city(node *database, char *city)
{
    char *flight_number = NULL;
    while (database != NULL)
    {
        if (strcmp(database->data.cities, city) == 0)
        {
            flight_number = database->data.number;
            break;
        }
        else
        {
            database = database->next;
        }
    }
    return flight_number;
}

bool flight_exists(node *database, char *flight)
{

    while (database != NULL)
    {
        if (strcmp(database->data.number, flight) == 0)
        {
            return true;
        }
        else
        {
            database = database->next;
        }
    }
    return false;
}


node *add_flights_data(void)
{
    FILE *f = fopen("flights_data.txt", "a");
    if (f == NULL)
    {
        f = fopen("flights_data.txt", "w");
    }

    node *new_node = malloc(sizeof(node));

    if (new_node == NULL)
        return NULL;

    printf("Enter flight number: ");
    scanf("\n%s", new_node->data.number);
    fprintf(f, "%s,", new_node->data.number);

    printf("[Departure-Destination] ");
    scanf("%s", new_node->data.cities);
    fprintf(f, "%s,", new_node->data.cities);


    printf("When is the flight departing? ");
    scanf("%s", new_node->data.date);
    fprintf(f, "%s,", new_node->data.cities);

    fprintf(f, "%s\n", new_node->data.cities);

    fclose(f);
    char seatmap[12][12] = {
        // ABC   DEF
        "|ooo   ooo|", // 1,
        "|ooo   ooo|", // 2,
        "|ooo   ooo|", // 3,
        "|ooo   ooo|", // 4,
        "|ooo   ooo|", // 5,
        "|ooo   ooo|", // 6,
        "|ooo   ooo|", // 7,
        "|ooo   ooo|", // 8,
        "|ooo   ooo|", // 9,
        "|ooo   ooo|"  // 10,
    };

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
            new_node->data.seatmap[i][j] = seatmap[i][j];
    }

    for (int i = 0; i < 6; i++)
    {
        new_node->data.menu[i] = 0;
    }

    return new_node;
}

void buy_ticket(node **database, char *flight)
{

    char name[16];
    printf("\nEnter your name: \n");
    scanf(" %s", name);

    // ulesterkep kinyomtat
    read_seatmap(*database, flight);

    // ulesnumber + index generalas
    char letter;
    int number;
    int row;
    int column;

    // ABCDEF TO INDEX
    printf("\nChoose a seat: e.g. A1 (A-F / 1-9) \n");
    scanf(" %c%i", &letter, &number);

    if (letter == 'A')
        column = 1;
    if (letter == 'B')
        column = 2;
    if (letter == 'C')
        column = 3;
    if (letter == 'D')
        column = 7;
    if (letter == 'E')
        column = 8;
    if (letter == 'F')
        column = 9;

    // CHAR TO INDEX
    row = number - 1;

    // x ha ures, exit ha nem
    node *current = *database;
    while (current != NULL)
    {
        if (strcmp(current->data.number, flight) == 0)
        {
            while (1)
            {
                if (current->data.seatmap[row][column] == 'x')
                {
                    printf("\nFoglalt\n");
                    return;
                }
                else
                {
                    current->data.seatmap[row][column] = 'x';
                    break;
                }
            }
            break;
        }
        else
            current = current->next;
    }
    // first class / economy menu
    int menu;
    printf("\nChoose a menu: \n");

    if (row <= 2)
    {
        printf("1. Caviar, 2. Steak, 3. Sushi 4. Cheeseburger, 5. Vegan Burger, 6. Lactose Free Pasta.\n");
    }
    else
    {
        printf("4. Cheeseburger, 5. Vegan Burger, 6. Lactose Free Pasta.\n");
    }
    scanf(" %i", &menu);

    current->data.menu[menu - 1]++;
    printf("\nFlight Booked! Thank you, %s!\n", name);
}

//node listaba
void add_node(node **database, node *new_node)
{
    node *tmp = *database;
    *database = new_node;
    new_node->next = tmp;
}

// lista felszabaditas
void free_list(node *database)
{
    node *tmp;
    while (database != NULL)
    {
        tmp = database;
        database = database->next;
        free(tmp);
    }
}

void back(void)
{
    int input;
    while (1)
    {
        printf("\n[1] Back\n");
        scanf(" %i", &input);
        if (input == 1)
            return;
    }
}

