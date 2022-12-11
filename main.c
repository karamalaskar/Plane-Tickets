#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "database.h"

// menu prototypes
void menu(node **database);
void flights_menu(node **database);
void flight_search_menu(node **database);
void administrator_menu(node **database);


int main(void)
{
    // pointer to the first node in the database
    node *all_flights = NULL;
    
    // main menu
    menu(&all_flights);
    
    // free database
    free_list(all_flights);
}

void menu(node **database)
{

    while (1)
    {
        char input = 0;
        do
        {
            // menu
            printf("\nWelcome! What would you like to do:\n"
                   "[1] Browse flights\n"
                   "[2] Search flights\n"
                   "[3] Administrator\n"
                   "[4] Exit\n");

            scanf(" %c", &input);

            switch (input)
            {
            case '1':
                flights_menu(&*database);
                break;

            case '2':
                flight_search_menu(&*database);
                break;

            case '3':
                administrator_menu(&*database);
                break;

            case '4':
                return;
            }
        } while (input != '1' && input != '2' && input != '3' && input != '4');
    }
}

void flights_menu(node **database)
{

    char flight[6];
    if (print_flights(*database))
    {
        do
        {
            printf("Choose a Flight: ");
            scanf(" %s", flight);
        } while (flight_exists(*database, flight) == false);

        buy_ticket(&*database, flight);
        back();
    };
}

void flight_search_menu(node **database)
{
    while (1)
    {
        char input = 0;
        do
        {
            printf("\nHow would you like to search: \n"
                   "[1] Search by flight number\n"
                   "[2] Search by cities\n"
                   "[3] Back\n");
            scanf(" %c", &input);
        } while (input != '1' && input != '2' && input != '3');
        char search[6];
        char *search2;
        switch (input)
        {
        case '1':

            do
            {
                printf("Flight number: ");
                scanf(" %s", search);
            } while (flight_exists(*database, search) == false);
            buy_ticket(&*database, search);
            back();
            break;
        case '2':
            do
            {
                printf("[Departure-Destination]: ");
                scanf(" %s", search);
                search2 = search_city(*database, search);
            } while (flight_exists(*database, search2) == false);
            buy_ticket(&*database, search2);
            back();
            break;
        case '3':
            return;
            break;
        }
    }
}

void administrator_menu(node **database)
{
    char *password = "password";
    char input[24];
    printf("Password: ");
    scanf("%s", input);

    // if the password is correct
    if (strcmp(password, input) == 0)
    {
        while (1)
        {
            char input = 0;
            do
            {
                printf("\nWhat would you like to do: \n"
                       "[1] Register a new flight\n"
                       "[2] View flight data\n"
                       "[3] back\n");
                scanf(" %c", &input);

            } while (input != '1' && input != '2' && input != '3');

            node *new_flight;
            switch (input)
            {
            case '1':
                new_flight = add_flights_data();
                add_node(&*database, new_flight);
                break;
            case '2':
                if (print_flights(*database))
                {
                    char flight[6];
                    do
                    {
                        printf("Choose a flight: ");
                        scanf(" %s", flight);
                    } while (flight_exists(*database, flight) == false);
                    read_seatmap(*database, flight);
                    meals(*database, flight);
                    back();
                };
                break;
            case '3':
                return;
                break;
            }
        }
    }
}
