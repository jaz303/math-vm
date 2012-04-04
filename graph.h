#ifndef GRAPH_H
#define GRAPH_H

typedef short node_id;

typedef struct {
    node_id *incoming;
    node_id num_incoming;
} node_t;

typedef struct {
    node_t  *nodes;
    node_id num_nodes;
} graph_t;

#endif