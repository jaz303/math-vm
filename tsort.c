#include "tsort.h"

static int tsort_r(graph_t *g, node_id *o, char *visited, node_id n) {
    if (!visited[n]) {
        int total_added = 0;
        visited[n] = 1;
        int i, num_incoming = g->nodes[n].num_incoming;
        for (i = 0; i < num_incoming; i++) {
            int num_added = tsort_r(g, o, visited, g->nodes[n].incoming[i]);
            o += num_added;
            total_added += num_added;
        }
        *o = n;
        return total_added + 1;
    } else {
        return 0;
    }
}

int tsort(graph_t *g, node_id *o) {
    
    int         i;
    char        visited[g->num_nodes];
    node_id     s[g->num_nodes];
    
    for (i = 0; i < g->num_nodes; ++i) {
        visited[i] = 0;
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
        }
    }
    
    return 1;
    
}