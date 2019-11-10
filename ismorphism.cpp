
#include "graph.h"
#include "ismorphism.h"
#include "tree.h"

std::vector<Graph::Node> center (Graph &g) {
	std::vector<int> ranks;
	std::vector<Graph::Node> leafs;
	int remainingNodes = g.num_nodes();
	for (Graph::NodeId nodeid = 0; nodeid < g.num_nodes(); nodeid++) {
		Graph::Node node = g.get_node(nodeid);
		//std::cout << node.id() << ", ";
		int rank = node.adjacent_nodes().size();
		ranks.push_back(rank);
		if (rank == 1) leafs.push_back(node);
	}
	while (remainingNodes > 2) {
		std::cout << "leafs: ";
		for (auto n : leafs) {
			std::cout << n.id() << ", ";
		}
		std::cout <<  "\n";
		std::vector<Graph::Node> newLeafs;
		for (Graph::Node leaf : leafs) {
			for (Graph::Neighbor neighbor : leaf.adjacent_nodes()) {
				ranks[neighbor.id()]--;
				if (ranks[neighbor.id()] == 1) {
					newLeafs.push_back(g.get_node(neighbor.id()));
				}
			}
		}
		remainingNodes -= leafs.size();
		leafs = newLeafs;
	}
	return leafs;
}

bool areIsomorph(Graph &t1, Graph::Node r1, Graph &t2, Graph::Node r2) {
	if (t1.num_nodes() != t2.num_nodes()) return false;

	Tree tree1(t1, r1);
	tree1.printPreOrder();
	std::vector<std::vector<int>> words1(t1.num_nodes());
	std::vector<int> f1(t1.num_nodes());
	std::vector<std::vector<Tree::Node*>> heighList1 = tree1.heightList();

	std::cout << "levels: ";
	for (auto level : heighList1) {
		for(auto n: level) {
			std::cout << n->id << ", ";
		}
		std::cout <<  "\n";
	}
	
	//delete tree1.root;
}