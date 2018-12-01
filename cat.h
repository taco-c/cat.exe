#ifndef CATEXE_CAT_H
#define CATEXE_CAT_H

/* Platform specific functions for delaying execution.
   Both mapped to SLEEP for convenience. */
#ifdef _WIN32
#include <winbase.h> /* Sleep */
#define SLEEP Sleep
#endif

#ifdef __linux__
#include <unistd.h> /* sleep */
#define SLEEP sleep
#endif

#ifdef DEBUG
#define TIME_BETWEEN_ACTIONS 1000
#define MAX_CAT_SLEEPING_TIME 1
#else
#define TIME_BETWEEN_ACTIONS 20000
#define MAX_CAT_SLEEPING_TIME 1200
#endif

typedef unsigned char bool;
#define true 1
#define false 0

/* Used by most action function for repeating actions (or not). */
#define AGAIN true
#define FIRST_TIME false

/* Used by the walk function, TO_FOOD will make the cat go to the food. */
#define TO_FOOD true
#define TO_ANYWHERE false

typedef struct
{
    char *name;
	int hunger;
	int mood;
	int sleepiness;
	int dirtiness;
} CAT;

/* Places where the cat can be. */
char *LOCATIONS[] = {
    "by it's bowl",
	"in it's bed",
    "on the sofa",
    "under the sofa",
    "in the kitchen",
    "on the human bed",
    "in the bathroom",
    "on the toilet lid",
    "on the table",
    "under the table",
    "under the human bed",
    "in the hallway",
    "in the bedroom",
    "in the sink",
    "in the window",
    "in the door",
    "under the chair",
    "in front of the fridge",
    "in front of the door"
};

/* Refers to the index of LOCATIONS[]. */
const int LOCATION_COUNT = 19;
#define CLOSE_TO_FOOD 0

void printSleepyCat ();
void cat_think (CAT);
void cat_sleep (CAT, bool);
void cat_dream (CAT);
void cat_eat (CAT);
void cat_walk (CAT, bool);
void cat_stretch (CAT, bool);
void cat_wash (CAT, bool);
void cat_stare (CAT, bool);
void cat_sit (CAT, bool);

#endif /* CATEXE_CAT_H */
