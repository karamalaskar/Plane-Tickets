#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct flight
{
    char number[5 + 1];
    char cities[32];
    char date[10 + 1];
    char seatmap[12][12];
    int menu[6];
} flight;

typedef struct node
{
    flight data;
    struct node *next;
} node;

void search_flight(node **database, char *flight);
char *search_city(node *database, char *city);
void buy_ticket(node **database, char *flight);
void free_list(node *database);
void add_node(node **database, node *new_node);
node *add_flights_data(void);
void back(void);
bool flight_exists(node *database, char *flight);

#endif
