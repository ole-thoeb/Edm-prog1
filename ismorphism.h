#ifndef ISOMORPHISM_H
#define ISOMORPHISM_H

#include "graph.h"

std::vector<Graph::Node> center (Graph &g);
bool areIsomorph(Graph &t1, Graph::Node r1, Graph &t2, Graph::Node r2);

#endif