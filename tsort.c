#include "tsort.h"

#define UNVISITED                       0
#define VISITED_PREVIOUSLY              1
#define VISITED_FROM_CURRENT_ENDPOINT   2

static int tsort_r(graph_t *g, node_id *o, unsigned char *visited, node_id n) {
    if (visited[n] == VISITED_PREVIOUSLY) {
        return 0;
    } else if (visited[n] == VISITED_FROM_CURRENT_ENDPOINT) {
        return -1; /* cycle! */
    } else {
        int total_added = 0;
        visited[n] = VISITED_FROM_CURRENT_ENDPOINT;
        int i, num_incoming = g->nodes[n].num_incoming;
        for (i = 0; i < num_incoming; i++) {
            int num_added = tsort_r(g, o, visited, g->nodes[n].incoming[i]);
            if (num_added == -1) {
                return -1;
            }
            o += num_added;
            total_added += num_added;
        }
        *o = n;
        return total_added + 1;
    }
}

int tsort(graph_t *g, node_id *o) {
    
    int             i;
    unsigned char   visited[g->num_nodes];
    node_id         s[g->num_nodes];
    
    for (i = 0; i < g->num_nodes; ++i) {
        visited[i] = UNVISITED;
        s[i] = 0;
    }
    
    for (i = 0; i < g->num_nodes; ++i) {
        int j;
        for (j = 0; j < g->nodes[i].num_incoming; ++j) {
            s[g->nodes[i].incoming[j]]++;
        }
    }
    
    for (i = 0; i < g->num_nodes; ++i) {
        if (s[i] == 0) {
            int nodes_added = tsort_r(g, o, visited, i);
            if (nodes_added == -1) {
                return 0;
            }
            o += nodes_added;
            int j;
            for (j = 0; j < g->num_nodes; ++j) {
                if (visited[j]) visited[j] = VISITED_PREVIOUSLY;
            }
        }
    }
    
    return 1;
    
}