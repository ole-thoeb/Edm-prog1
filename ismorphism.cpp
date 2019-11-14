
#include "graph.h"
#include "ismorphism.h"
#include "tree.h"
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

class Word {
public:
	std::vector<int> chars;
	void push_back(int c) {
		chars.push_back(c);
	}
	Tree::Node *node;
	int number;

	bool operator == (Word &w) {
		if (chars.size() != w.chars.size()) return false;

		for (size_t i = 0; i < chars.size(); i++) {
			if (chars[i] != w.chars[i]) return false;
		}
		return true;
	}

	bool operator != (Word &w) {
		return !(*this == w);
	}
};

struct IsmorphismData {
	Tree *t;
	std::vector<Word> w;
	std::vector<int> f;
	std::vector<std::vector<Tree::Node*>> heighList;
	std::vector<Word> tempWords;
};

bool cleanupRet(IsmorphismData data[], size_t len, bool retVal) {
	for (size_t i = 0; i < len; i++) {
		delete data[i].t;
	}
	return retVal;
}

bool areIsomorph(Graph &t1, Graph::Node r1, Graph &t2, Graph::Node r2) {
	if (t1.num_nodes() != t2.num_nodes()) return false;

	IsmorphismData d1;
	d1.t = new Tree(t1, r1);
	d1.w = std::vector<Word>(t1.num_nodes());
	d1.f = std::vector<int>(t1.num_nodes());
	d1.heighList = d1.t->heightList();

	IsmorphismData d2;
	Tree tree2(t2, r2);
	d2.t = new Tree(t2, r2);
	d2.w = std::vector<Word>(t2.num_nodes());
	d2.f = std::vector<int>(t2.num_nodes());
	d2.heighList = d2.t->heightList();

	IsmorphismData data[] = {d1, d2};

	if (d1.heighList.size() != d2.heighList.size()) return cleanupRet(data, 2, false);

	size_t height = d1.heighList.size();
	for (size_t h = height - 1; h > 0; h--) {
		
		if (d1.heighList[h - 1].size() != d2.heighList[h - 1].size()) return cleanupRet(data, 2, false);
	
		for (auto d : data) {
			//algo line: 7

			std::vector<int> localF = d.f;
			std::sort(d.heighList[h].begin(), d.heighList[h].end(), [localF](Tree::Node *n1, Tree::Node *n2) {
				return localF[n1->id] < localF[n2->id];
			});

			//algo line: 8
			for (auto node : d.heighList[h]) {
				d.w[node->parent->id].push_back(d.f[node->id]);
			}

			//copy words from one level into new list
			d.tempWords = std::vector<Word>(d1.heighList[h - 1].size());
			for (size_t i = 0; i < d.heighList[h - 1].size(); i++) {
				Tree::Node *node = d.heighList[h- 1][i];
				Word w = d.w[node->id];
				w.node = node;
				d.tempWords[i] = w;
			}

			//algo line: 9
			std::sort(d.tempWords.begin(), d.tempWords.end(), [](Word w1, Word w2) {
				size_t size = w1.chars.size() < w2.chars.size() ? w1.chars.size() : w2.chars.size();
				for (size_t i = 0; i < size; i++) {
					if (w1.chars[i] != w2.chars[i]) {
						return w1.chars[i] < w2.chars[i];
					}
				}
				return w1.chars.size() < w2.chars.size();
			});
		}

		for (size_t i = 0; i < d1.tempWords.size(); i++) {
			if (d1.tempWords[i] != d2.tempWords[i]) return cleanupRet(data, 2, false);
		}

		for (auto d : data) {
			//maybe same words must have same number
			for (size_t i = 0; i < d.tempWords.size(); i++) {
				d.f[d.tempWords[i].node->id] = i;
			}
		}
	}
	
	for (auto d : data) {
		std::cout << "levels with f and w:\n";
		for (auto level : d.heighList) {
			for(auto n: level) {
				std::cout << "(id=" << n->id << ", f=" << d.f[n->id] << ", w={";
				for (auto c : d.w[n->id].chars) std::cout << c << ", ";
				std::cout << "}) ";
			}
			std::cout <<  "\n";
		}
	}

	
	//delete tree1.root;
	return cleanupRet(data, 2, true);
}