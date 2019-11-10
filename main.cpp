#include "graph.h"
#include "ismorphism.h"
#include <vector>

int main(int argc, char const *argv[])
{
	if (argc > 1) {
		Graph g(argv[1], Graph::undirected);
		g.print();
		std::vector<Graph::Node> c = center(g);
		//for (auto node : c) {
		//	std::cout << node.id() << "\n";
		//}
		areIsomorph(g, c[0], g, c[0]);
	}
	return 0;
}
