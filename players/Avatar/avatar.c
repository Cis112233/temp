/*  Casting his sight on his realm, the Lord witnessed
    The cascade of evil, the torrents of war.
    Burning with wrath, He stepped 
    down from the Heavens
    To judge the unworthy,
    To redeem the pure.
    
    -The Scriptures, Revelation Verses 2:12
*/

#include <stdlib.h>
#include <stdio.h>
#include "mafia.h"

int getRandomNumber(){
	return 4; // Chosen by a fair dice roll.
	          // Garunteed to be random.
}


void day0(){
	char * target = get_player(getRandomNumber()-1)->name;
	fprintf(stderr, "Target: `%s'\n", target);
	FILE * f = fopen("target", "w");
	if(!f){exit(1);}
	fprintf(f, "%s", target);
	fclose(f);
}


int main(){
	get_players();
	int cycle = get_cycle(day0);
	FILE * out = fopen("to_server", "w");
	if(!out){exit(1);}
	FILE * targetF = fopen("target", "r");
	if(!targetF){exit(1);}
	
	char target[64];

	fscanf(targetF, "%s", target);

	fprintf(stderr, "Target: %s\n", target);
	
	if(cycle == 0){
		// night
		fprintf(out,"%s\n", target);
		fprintf(stderr, "> Voting to kill %s\n", target);
		exit(0);
	} else if (cycle > 0) {
		// day
		fprintf(out, "vote %s\n", target);
		fprintf(stderr, "> Voting to lynch %s\n", target);
		exit(0);
	} else if (cycle == -1) {
		fprintf(stderr, "> saying 6, 10 at %s\n", target);
		fprintf(out, "say 6 %s\n", target);
		fprintf(out, "say 10 %s\n", target);
	}
}


