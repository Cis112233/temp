extern int mafialib_ready;

typedef struct {
	char name[64];
	int role;
} player_t;

extern player_t * players;
extern int NPLAYERS;
void get_players();
player_t * get_player(int n);
int get_cycle();
