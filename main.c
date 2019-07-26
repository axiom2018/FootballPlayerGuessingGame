#include <stdio.h>
#include <stdlib.h>
#include "World.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* Game concept: Guessing the names of famous footballers from various overseas leagues such as the premiership, la liga, serie a, etc. You'll go against a computer.
Each of you will have 3 tries at one footballers name. If you get it right, you'll score points. The one with the most points at the end of 3 rounds is the winner.
In the case of a tie, sudden death!

Design patterns are used in the code as well. Although frequent searching on engines such as Google are done, one central place for pattern ideas are from a book
written by Adam Petersen, called "Patterns in C". Book here https://mafiadoc.com/patterns-in-c-adam-petersen_59cf3e921723dd8cf17d3796.html
 */

int main()
{
    // Begin the game with the abstract data type pattern in order to hide the implementation or inner workings of our system.
    WorldPtr gameWorld = World_Init();

    // Simply update the game to keep going.
    UpdateWorld(gameWorld);

    // Clear screen and display a post message.
    // ClearScreen(gameWorld);

    // Free memory of the pointer when the game is done.
    World_Destroy(gameWorld);

    return 0;
}
