#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct node {
    void        * payload;
    struct node * next;
    bool          free_payload;
} ll_node_t;

ll_node_t * ll_create_node(void * payload, bool needs_freeing);
void ll_insert_end(ll_node_t ** head, ll_node_t * node);
void ll_insert_front(ll_node_t ** head, ll_node_t * node);
void ll_remove_node(ll_node_t ** head, ll_node_t * node);
void ll_destroy_list(ll_node_t ** head);