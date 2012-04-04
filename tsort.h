#ifndef TSORT_H
#define TSORT_H

#include "graph.h"

/*
 * performs a topological sort of graph g, storing the sorted nodes
 * in o. o should be large enough to store size(g) node_ids.
 * returns 1 if toplogical successful, 0 if graph is not sortable.
 *
 * this function allocates size(g) * 3 bytes on the stack
 */
int tsort(graph_t *g, node_id *o);

#endif