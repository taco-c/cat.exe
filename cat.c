/* Cat.exe: Cat Simulator 2019
   Last updated 2018-11-30 */

#include <stdio.h> /* printf */
#include <stdlib.h> /* rand srand */
#include <time.h> /* time */

#include "cat.h"

int tick;
int location;
int prev_location;
int foodAmount = 10;
int prevAction = 5;

int
main (int argc, char **argv)
{
	CAT kitty;
	
	srand(time(NULL));
	
	kitty.hunger = rand() % 10;
	kitty.mood = rand() % 10;
	kitty.sleepiness = rand() % 10;
	kitty.dirtiness = rand() % 10;
	
	if (argc > 1)
		{ kitty.name = *(argv + 1); }
	else
		{ kitty.name = "Cat"; }
	
	location = CLOSE_TO_FOOD;
	
	printf("This is %s.\n\n", kitty.name);

	/* Infinite cat loop goodness. */
	while (1)
	{
		think(kitty);

		#ifdef DEBUG
		printf("[ [%d] H:%d, M:%d, S:%d, D:%d ]\n",
				tick,
				kitty.hunger,
				kitty.mood,
				kitty.sleepiness,
				kitty.dirtiness);
		#endif

		if (kitty.sleepiness > 20)
		{
			kitty.mood--;
			sleep(kitty, FIRST_TIME);
		}
		else if (kitty.dirtiness > 20)
		{
			kitty.mood--;
			wash(kitty, FIRST_TIME);
		}
		else if (kitty.hunger > 20)
		{
			kitty.mood--;
			SLEEP(TIME_BETWEEN_ACTIONS);

			if (location == CLOSE_TO_FOOD) { eat(kitty); }
			else { walk(kitty, TO_FOOD); eat(kitty); }
		}

		tick++;
		SLEEP(TIME_BETWEEN_ACTIONS);
	}

	printf("Cat.exe has stopped working.\n\n");
	return 0;
}

/* Cat decides what to do. */
void
think (CAT kitty)
{
	int action = rand() % 7;
	
	/* If cat thinks about the same thing again,
	   make cat think it over again */
	if (action == prevAction)
	{
		think(kitty);
	}
	else
	{
		prevAction = action;
		switch (action)
		{
			case 0:
				sleep(kitty, FIRST_TIME);
				break;
			case 1:
				eat(kitty);
				break;
			case 2:
				walk(kitty, TO_ANYWHERE);
				break;
			case 3:
				stretch(kitty, FIRST_TIME);
				break;
			case 4:
				wash(kitty, FIRST_TIME);
				break;
			case 5:
				stare(kitty, FIRST_TIME);
				break;
			case 6:
				sit(kitty, FIRST_TIME);
				break;
		}
	}
}

void
printSleepyCat ()
{
	printf("  |\\	  _,,,---,,_\n");
	printf("  /,`.-'`'	-.  ;-;;,_\n");
	printf(" |,4-  ) )-,_..;\\ (  `'-'\n");
	printf("'---''(_/--'  `-'\\_)\n");
}

void
sleep (CAT kitty, bool again)
{
	int sleepTimeInSec = rand() % MAX_CAT_SLEEPING_TIME;
	time_t awakeTime = time(NULL) + sleepTimeInSec;

	if (again == true)
	{
		printSleepyCat();
		printf("... and goes back to sleep.\n\n");
	}
	else
	{
		printSleepyCat();
		printf("%s sleeps.\n\n", kitty.name);
	}

	while ( time(NULL) < awakeTime )
	{
		/* Cat dreams every second while asleep. */
		dream(kitty);
		SLEEP(1000);
	}

	kitty.mood++;
	kitty.sleepiness /= 2;
	kitty.dirtiness++;
	kitty.hunger--;

	printf("%s wakes up.\n\n", kitty.name);

	if (rand() % 100 < 25 + kitty.sleepiness)
	{
		SLEEP(TIME_BETWEEN_ACTIONS);
		sleep(kitty, AGAIN);
	}
}

/* Dreaming will allow the cat's mood to normalize. */
void
dream (CAT kitty)
{
	if (rand() % 100 < (50 + kitty.mood)) { kitty.mood--; } /* Bad dream. */
	else { kitty.mood++; } /* Good dream. */
}

void
eat (CAT kitty)
{
	if (location == CLOSE_TO_FOOD)
	{
		printf("%s eats some food %s.\n\n", kitty.name, LOCATIONS[location]);

		if (foodAmount > 0)
		{
			foodAmount--;
			kitty.hunger = 0;
			kitty.mood++;
		}
		else
		{
			printf("No more food in %s's food bowl. ", kitty.name);
			printf("Refilling for next meal.\n\n");
			foodAmount = 10;
			kitty.mood--;
		}
	}
	else /* Cat is not close to food. Do nothing. */
	{
		kitty.mood--;
		SLEEP(TIME_BETWEEN_ACTIONS);
		walk(kitty, TO_ANYWHERE);
	}

	kitty.dirtiness++;
	kitty.sleepiness++;
}

void
walk (CAT kitty, bool toFood) {
	prev_location = location;
	
	if (toFood == TO_FOOD) { location = CLOSE_TO_FOOD; }
	else { location = rand() % LOCATION_COUNT; }
	
	printf("%s walks around,", kitty.name);

	if (location == prev_location)
	{
		printf(" but decides to go back %s.\n\n", LOCATIONS[location]);
	}
	else
	{
		printf(" and is now %s.\n\n", LOCATIONS[location]);
	}

	kitty.dirtiness++;
	kitty.sleepiness++;
	kitty.hunger++;
	kitty.mood--;
}

void
stretch (CAT kitty, bool again)
{
	printf("%s stretches", kitty.name);
	if (again == AGAIN) { printf(" some more.\n\n"); }
	else { printf(".\n\n"); }

	kitty.mood++;
	kitty.dirtiness++;
	kitty.hunger++;
	kitty.sleepiness++;

	if (rand() % 100 < 25 + kitty.mood)
	{
		SLEEP(TIME_BETWEEN_ACTIONS);
		stretch(kitty, AGAIN);
	}
}

void
wash (CAT kitty, bool again)
{
	printf("%s washes itself", kitty.name);
	
	if (again == AGAIN) { printf(" again.\n\n"); }
	else { printf(".\n\n"); }

	kitty.mood++;
	kitty.dirtiness /= 2;
	kitty.sleepiness++;
	kitty.hunger++;

	if (rand() % 100 < 25 + kitty.dirtiness)
	{
		SLEEP(TIME_BETWEEN_ACTIONS);
		wash(kitty, AGAIN);
	}
}

void
stare (CAT kitty, bool again)
{
	printf("%s stares into the wall", kitty.name);
	
	if (again == AGAIN) { printf(" a little more.\n\n"); }
	else { printf(".\n\n"); }

	kitty.dirtiness++;
	kitty.sleepiness++;
	kitty.hunger++;

	if (rand() % 100 < 50 + kitty.mood)
	{
		SLEEP(TIME_BETWEEN_ACTIONS);
		stare(kitty, AGAIN);
	}
}

void
sit (CAT kitty, bool again)
{
	printf("%s sits", kitty.name);
	
	if (again == AGAIN) { printf(" some more.\n\n"); }
	else { printf(".\n\n"); }
	
	kitty.dirtiness++;
	kitty.sleepiness++;
	kitty.hunger++;
	
	if (rand() % 100 < 50 + kitty.mood)
	{
		SLEEP(TIME_BETWEEN_ACTIONS);
		sit(kitty, AGAIN);
	}
}