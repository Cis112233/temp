#include "mafia.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cycle = -1;
int NPLAYERS = -1;
player_t * players;

void panic();

void get_players(){
	FILE * f = fopen("players", "r");

	// Fail? Just give up.
	if(!f){panic();}

	// read the file to figure out how many players there are
	// discard the result; we don't want it yet.
	while(feof(f)==0){
		char buf[256];
		fscanf(f, "%s", buf);
		NPLAYERS++;
	}
	fclose(f);
	
	fprintf(stderr, "Players: %d\n",NPLAYERS);

	// now that we know how much to allocate, we can 
	// actually allocate memory.

	players = calloc(NPLAYERS, sizeof(player_t));

	// now read the file again (but pay attention)
	f = fopen("players", "r");
	if(!f){panic();}

	int i=0;
	while(feof(f)==0){
		fscanf(f, "%s", players[i].name);
		if(feof(f)!=0)break;
		fprintf(stderr, "- %s\n", players[i++].name);
	}
}

player_t * get_player(int n){
	return &players[n];
}


int get_cycle( void (*day0)(void)){
	FILE * f = fopen("from_server", "r");
	if(!f){panic();}
	int cycle;
	char word[10];
	fscanf(f,"%s",word);
	
	if(strcmp("Rise",word) == 0){
		(*day0)();
		fprintf(stderr, "cycle = 0 (FIRSTDAY)\n");
		exit(0);
	}
	
	if(strcmp("Dawn",word) == 0){
		fscanf(f, " of day %d.", &cycle);
	} else if(strcmp("It", word) == 0){
		cycle = 0;
	} else {
		cycle = -1;
	}
	
	fclose(f);

	fprintf(stderr, "cycle = %d ",cycle);
	if(cycle > 0){
		fprintf(stderr, "(DAWN)");
	}
	if(cycle == 0){
		fprintf(stderr, "(NIGHT)");
	}
	if(cycle == -1){
		fprintf(stderr, "(DAY)");
	}
	
	fprintf(stderr, "\n");
	return cycle;
}

void panic(){
	printf("fopen() error.\n");
	printf("Panic :(\n");
	exit(1);
}
