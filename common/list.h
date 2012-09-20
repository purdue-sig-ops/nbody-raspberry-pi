typedef struct {
	void * data;
	struct l_node * prev;
	struct l_node * next;
} l_node;

typedef void(* map_fn)(void * key, void * val);
typedef void(* red_fn)(void * key, void * val, void * red_data);

typedef struct {
	struct l_node * head;
	struct l_node * tail;
} list;

void init_list (list *);

void push (list *, void *);
void * pop (list *);
void * peek (list *);

void enqueue (list *, void *);
void * dequeue (list *);
void * qpeek (list *);

void map (list *, map_fn);
void reduce (list *, red_fn, void *);
