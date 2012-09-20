#include "../common/util.h"
#include "../common/clientinfo.h"

#define UPDATE_THRESHOLD 16

struct client {
	int ip_addr;
};

extern Planet ** curr_frame;
extern Planet ** next_frame;
int num_planet;
int num_client;

/* don't worry about this for now
int hasUpdate (int client, int planetId);
void regUpdate (int client, int planetId);
*/
