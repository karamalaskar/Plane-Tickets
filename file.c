#include "file.h"



void read_seatmap(node *database, char *number)
{

    while (database != NULL)
    {
        if (strcmp(database->data.number, number) == 0)
        {
            printf("\n");
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    printf("%c", database->data.seatmap[i][j]);
                }
                printf("\n");
            }
        }
        database = database->next;
    }
}

bool print_flights(node *database)
{
    if (database == NULL)
    {
        printf("\nNo flights available :(\n");
        back();
        return false;
    }

    else
    {
        while (database != NULL)
        {
            printf(" %s |", database->data.number);
            printf(" %s |", database->data.cities);
            printf(" %s \n", database->data.date);

            database = database->next;
        }
    }
    return true;
}

void meals(node *database, char *flight)
{
    while (database != NULL)
    {
        if (strcmp(database->data.number, flight) == 0)
        {
            int sum = database->data.menu[0] + database->data.menu[1] + database->data.menu[2] + database->data.menu[3] +
                      database->data.menu[4] + database->data.menu[5];
            printf("\nCaviar: %i\nSteak:% i\nSushi: %i\nCheeseburger: %i\nVegan Burger: %i\nLactose Free Pasta: %i\n\n",
                   database->data.menu[0], database->data.menu[1], database->data.menu[2], database->data.menu[3], database->data.menu[4], database->data.menu[5]);
            printf("There are %i passengers on flight %s.\n", sum, database->data.number);
        }

        database = database->next;
    }
}
