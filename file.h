#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void read_seatmap(node *database, char *number);
bool print_flights(node *database);
void meals(node *database, char *flight);


#endif
