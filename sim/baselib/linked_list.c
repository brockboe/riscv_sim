#include <assert.h>
#include "linked_list.h"

static inline ll_node_t * ll_get_tail(ll_node_t * head)
{
    ll_node_t * curr = head;
    while(curr->next != NULL)
        { curr = curr->next; }
    return curr;
}

static inline ll_node_t * ll_get_node_before(ll_node_t * head, ll_node_t * node)
{
    ll_node_t * curr = head;
    if(head == node) { return head; }
    while(curr->next != node)
        { curr = curr->next; }
    return curr;
}

ll_node_t * ll_create_node(void * payload, bool needs_freeing)
{
    ll_node_t * node = (ll_node_t *)malloc(sizeof(ll_node_t));
    node->payload = payload;
    node->free_payload = needs_freeing;
    return node;
}

void ll_insert_end(ll_node_t ** head, ll_node_t * node)
{
    ll_node_t * tail = ll_get_tail(*head);
    tail->next = node;
    node->next = NULL;
}

void ll_insert_front(ll_node_t ** head, ll_node_t * node)
{
    node->next = *head;
    *head = node;
}

void ll_remove_node(ll_node_t ** head, ll_node_t * node)
{
    if(*head == node)
    {
        if((*head)->free_payload) { free((*head)->payload); }
        ll_node_t * next = (*head)->next;
        free(*head);
        *head = next;
    }
    else
    {
        ll_node_t * before = ll_get_node_before(*head, node);
        ll_node_t * after  = node->next;
        if(node->free_payload) { free(node->payload); }
        free(node);
        before->next = after;
    }
}

void ll_destroy_list(ll_node_t ** head)
{
    ll_node_t * to_delete = *head;
    ll_node_t * next;

    while(to_delete != NULL)
    {
        next = to_delete->next;
        if(to_delete->free_payload) { free(to_delete->payload); }
        free(to_delete);
        to_delete = next;
    }
}