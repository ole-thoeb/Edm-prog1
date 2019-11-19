
#include "graph.h"
#include "ismorphism.h"
#include "tree.h"
#include "bucketsort.h"
#include <algorithm>

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
		//std::cout << "leafs: ";
		//for (auto n : leafs) {
		//	std::cout << n.id() << ", ";
		//}
		//std::cout <<  "\n";
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

class IsmorphismData {
public:
	Tree *t;
	std::vector<int> &f;
	std::vector<std::vector<Tree::Node*>> &heighList;
	IsmorphismData(Tree *tree, std::vector<int> &f, std::vector<std::vector<Tree::Node*>> &hList) : t(tree), f(f), heighList(hList) {}
};

bool cleanupRet(IsmorphismData data[], size_t len, bool retVal) {
	for (size_t i = 0; i < len; i++) {
		delete data[i].t;
		delete &data[i].heighList;
		delete &data[i].f;
	}
	return retVal;
}

bool areIsomorph(Graph &t1, Graph::Node r1, Graph &t2, Graph::Node r2) {
	if (t1.num_nodes() != t2.num_nodes()) return false;

	Tree *tree1 = new Tree(t1, r1);
	IsmorphismData d1(tree1, *(new std::vector<int>(t1.num_nodes())), *(tree1->heightList()));

	Tree *tree2 = new Tree(t2, r2);
	IsmorphismData d2(tree2, *(new std::vector<int>(t2.num_nodes())), *(tree2->heightList()));


	IsmorphismData data[] = {d1, d2};

	if (d1.heighList.size() != d2.heighList.size()) return cleanupRet(data, 2, false);

	size_t height = d1.heighList.size();
	for (size_t h = height - 1; h > 0; h--) {
		
		if (d1.heighList[h - 1].size() != d2.heighList[h - 1].size()) return cleanupRet(data, 2, false);
	
		for (auto &d : data) {
			//algo line: 7

			std::vector<int> localF = d.f;
			bucketsort(d.heighList[h], d.heighList[h].size(), [](Tree::Node *n) { return 1; }, [&localF](Tree::Node *n, size_t i) -> int {
				return localF[n->id];
			});
		
			//algo line: 8
			for (auto node : d.heighList[h]) {
				node->parent->word.push_back(d.f[node->id]);
			}

			//algo line: 9
			bucketsort(d.heighList[h - 1], d.heighList[h].size(), [](Tree::Node *n) { return n->word.size(); }, [](Tree::Node *n, size_t i) {
				long long index = n->word.size() - i - 1;
				if (index < 0) return -1;
				//std::cout << "id: " << w.node->id << "\n";
				//for (auto c : w.chars) {
				//	std::cout << c << ", ";
				//}
				//std::cout << "\n";
				return n->word[index];
			});
		}

		for (size_t i = 0; i < d1.heighList[h - 1].size(); i++) {
			if (d1.heighList[h - 1][i]->word != d2.heighList[h - 1][i]->word) {
				return cleanupRet(data, 2, false);
			}
		}

		for (auto &d : data) {
			//maybe same words must have same number
			for (size_t i = 0; i < d.heighList[h - 1].size(); i++) {
				
				d.f[d.heighList[h - 1][i]->id] = i;
			}
		}
	}
	
	//for (auto d : data) {
	//	std::cout << "levels with f and w:\n";
	//	for (auto level : d.heighList) {
	//		for(auto n: level) {
	//			std::cout << "(id=" << n->id << ", f=" << d.f[n->id] << ", w={";
	//			for (auto c : d.w[n->id].chars) std::cout << c << ", ";
	//			std::cout << "}) ";
	//		}
	//		std::cout <<  "\n";
	//	}
	//}

	
	//delete tree1.root;
	return cleanupRet(data, 2, true);
}