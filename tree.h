#ifndef TREE_H
#define TREE_H

#include "graph.h"
#include <vector>

class Tree {
	public:
		class Node {
			private:
				std::vector<Node*> _children;
			public:
				Graph::NodeId id;
				void addChildren(Node* child);
				const std::vector<Node*> &children() const;
				Node *parent;
				std::vector<int> word;
				Node(Graph::NodeId id, Node *parent);
				~Node();
		};
		
		Node *root;

		~Tree();
		Tree(Graph &g, Graph::Node root);
		Tree();
		std::vector<std::vector<Node*>>* heightList();
		void printPreOrder();
};

//Tree treeFromGraph(Graph &g, Graph::Node root);
void buildTree(Graph &g, std::vector<bool> &visited, Graph::Node *gN, Tree::Node *tN);
//oid postOrderDelete(Tree::Node *root);

#endif