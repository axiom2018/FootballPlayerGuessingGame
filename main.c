#include <stdio.h>
#include <stdlib.h>
#include "World.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>

/** Game concept: Guessing the names of famous footballers from various overseas leagues such as the premiership, la liga, serie a, etc. You'll go against a computer.
Each of you will have 3 tries at one footballers name. If you get it right, you'll score points. The one with the most points at the end of 3 rounds is the winner.
In the case of a tie, sudden death!

Design patterns are used in the code as well. Although frequent searching on engines such as Google are done, one central place for pattern ideas are from a book
written by Adam Petersen, called "Patterns in C". Book here https://mafiadoc.com/patterns-in-c-adam-petersen_59cf3e921723dd8cf17d3796.html

I KNEW C had to have SOME sort of design patterns for writing professional level C code, so thankfully I found it. So here's the Football player guessing game. Hope
you enjoy the code.

There are several patterns Adam goes over in the book, and they are:

1) First Class ADT.
2) State.
3) Strategy.
4) Observer.
5) Reactor.

See link: https://stackoverflow.com/questions/4112796/are-there-any-design-patterns-in-c

As you read the code you'll notice some are used but not others, and that's normal, for the games purposes, we don't just throw in patterns, only when they're necessary.
Now I'll explain why some design patterns were used or not in the code.

1) V First class ADT - The state, in my own words after reading the book, is a design pattern that is the closest to an actual class we can get in languages like C++
or Java. For example, a class in C++ has private functions/variables and public ones. The same can be done in C with the first class ADT. In the .c file, we need only
use the static keyword on variables or functions because it restricts visibility to just that one module (opposite of extern which EXTENDS visibility). We have can have
multiple structure pointer just like in C++ we can have multiple class objects.

2) X State - The state, in my own words after reading the book, is a design pattern that lets an objects behavior change when its state changes. I was CLOSE to putting
this one in during string manipulation and string interface design but decided against it for a better approach. Because primarily the CpuSmartStringGuess works on strings
dynamic ones and always allocates memory for it of course. Inserting a state pattern on TOP of using dynamic arrays will of course introduce unnecessary code, but also
take up even MORE memory. There's no need to use MORE memory when we don't have to do that.

3) X Strategy - The strategy, in my own words after reading the book, is a design pattern that lets us have various different algorithms and give us the ability to switch
them out when we see fit with ease. This one was ALMOST in the game but I decided against it because the outline or structure of the strategy didn't accommodate all that
the cpu NEEDED. What I mean if you follow the link above and hit strategy is we have a primary typedef (CustomerPriceStrategy), then 3 typedef's following the same format
(bronze, silver, gold). Ours isn't too simple. We need to give the cpu strategy the REAL string to make it work, passing it every single time is unnecessary. On top of the
various dynamic arrays and functions needed. The pattern to fit the cpu algorithm is the first class adt. The structure will hold all the data it needs accomplish the algorithm.

4) X Observer - The observer, in my own words after reading the book, is a design pattern that lets multiple entities/interfaces/objects know about a certain change
in state. Obviously this is unnecessary for a string guessing game. Most definitely necessary for say something like Metal Gear Solid, when snake gets caught/detected,
all other enemies or guards are alerting and start rushing after him. Maybe that's how metal gear solid works, I've actually never played any of them. :D

5) X Reactor - The reactor, in my own words after reading the book, is a design pattern that helps clients in an event driven, event oriented system. The example given
were subsystems that needed to connect to a server with TCP/IP. The subsystems request a connection, if established, send info. But we didn't need any of that here.
We have the player, and cpu interfaces and neither one needs to communicate with each other for whatever purpose.

Hopefully you enjoy the game and like the code written!

*/

int main()
{
    // Seed for random numbers.
    srand(time(NULL));

    // Begin the game with the first class abstract data type pattern in order to hide the implementation or inner workings of our system.
    WorldPtr gameWorld = World_Init();

    // Simply update the game to keep going.
    World_Update(gameWorld);

    // Free memory of the pointer when the game is done.
    World_Destroy(gameWorld);

    // Give prompt to exit.
    printf("Press [enter] to exit game.\n");
    getchar();

    return 0;
}
