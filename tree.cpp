#include "graph.h"
#include "tree.h"
#include <vector>

Tree::Node::~Node() {
	std::cout << "deleting Node with id " << id << "\n";
	for (auto child : children()) {
		delete child;
	}
	//delete this;
}

Tree::Node::Node(Graph::NodeId id, Node *parent) : id(id), parent(parent) {}
void Tree::Node::addChildren(Tree::Node* child) {
	std::cout << "adding child with id " << child->id << " to parent with id " << id << "\n";
	_children.push_back(child);
}

const std::vector<Tree::Node*> &Tree::Node::children() const {
	return _children;
}

Tree::Tree() {
	root = nullptr;
}

//void postOrderDelete(Tree::Node *root) {
//	for (auto child : root->children) {
//		postOrderDelete(child);
//	}
//	delete root;
//}
//
Tree::~Tree() {
	delete root;
}

Tree::Tree(Graph &g, Graph::Node root) {
	std::vector<bool> visited(g.num_nodes());
	Tree::Node *treeRoot = new Tree::Node(root.id(), nullptr);
	buildTree(g, visited, &root, treeRoot);
	this->root = treeRoot;
}

void buildTree(Graph &g, std::vector<bool> &visited, Graph::Node *gN, Tree::Node *tN) {
	visited[gN->id()] = true;
	for (auto neighbour : gN->adjacent_nodes()) {
		if (!visited[neighbour.id()]) {
			Tree::Node *treeNode = new Tree::Node(neighbour.id(), tN);
			tN->addChildren(treeNode);
			buildTree(g, visited, &g.get_node(neighbour.id()), treeNode);
		}
	}
}

//void _heightList(Tree::Node &node, std::vector<std::vector<Tree::Node>> &heighList, int depth);

void _heightList(Tree::Node *node, std::vector<std::vector<Tree::Node*>> &heighList, int depth) {
	//std::cout << "height " << depth << " with node " << node->id << "\n";
	if (heighList.size() > depth) {
		heighList[depth].push_back(node);
	} else {
		//std::cout << "new level\n";
		std::vector<Tree::Node*> innerList;
		innerList.push_back(node);
		heighList.push_back(innerList);
	}
	for (auto child : node->children()) {
		_heightList(child, heighList, depth + 1);
	}
}

std::vector<std::vector<Tree::Node*>> Tree::heightList() {
	std::vector<std::vector<Tree::Node*>> heighList;
	_heightList(root, heighList, 0);
	return heighList;
}

void _printPreOrder(Tree::Node *root) {
	std::cout << root->id << " ";
	for (auto child : root->children()) {
		_printPreOrder(child);
	}
}

void Tree::printPreOrder() {
	std::cout << "preorder: ";
	_printPreOrder(root);
	std::cout << "\n";
}