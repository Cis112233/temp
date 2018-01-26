/*  Citizens of the State, rejoice!

    Today, a great milestone has been achieved by our glorious leaders.
    A stepping stone in the grand story of our empire has been traversed.
    Our individual fears may be quietened;
    the safety of our great nation has been secured.

    Today, unyielding, we have walked the way of the warrior.
    In our hands have our fates been molded.
    On the Leviathan's back will our civilization be carried home
    and the taint of the Enemy purged from our souls.
    
    Rejoice, citizens! Victory is at hand.
    
    -Caldari State Information Bureau Pamphlet, YC 12
*/

#include <stdio.h>
#include <stdlib.h>
#include "mafia.h"

void day0(){
	FILE * index = fopen("idx", "w");
	
	fprintf(index,"0");
	
	fclose(index);
}

int main(){
	get_players();
	int i, cycle = get_cycle(day0);
	
	FILE * out = fopen("to_server", "w");
	FILE * idx = fopen("idx", "r");
	
	fscanf(idx, "%d", &i);
	fclose(idx);
	
	char * target;
	target = get_player(i)->name;
	
	fprintf(stderr, "Idx: %d\n", i);
	fprintf(stderr, "Target: %s\n", target);
	
	if(cycle > 0){
		idx = fopen("idx", "w");
		i++;
		i = i%NPLAYERS;
		fprintf(idx, "%d", i);
		fprintf(out, "vote %s\n", target);
	} else if (cycle == -1) {
        printf("> saying 6, 10 at %s\n", target);
        fprintf(out, "say 6 %s\n", target);
        fprintf(out, "say 10 %s\n", target);
    }
	
	fclose(out);
}
