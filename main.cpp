#include "graph.h"
#include "ismorphism.h"
#include <vector>
#include <chrono>

int main(int argc, char const *argv[])
{
	if (argc > 2) {
		unsigned long tStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		Graph g1(argv[1], Graph::undirected);
		Graph g2(argv[2], Graph::undirected);
		std::vector<Graph::Node> c1 = center(g1);
		std::vector<Graph::Node> c2 = center(g2);
		//for (auto node : c) {
		//	std::cout << node.id() << "\n";
		//}
		if (c1.size() == c2.size()) {
			for (auto root : c1) {
				bool res = areIsomorph(g1, root, g2, c2[0]);
				if (res) {
					std::cout << "trees are isomorph\n";
					unsigned long tEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					std::cout << "took " << tEnd -tStart << " ms\n";
					return 0;
				} else {
					std::cout << "failed\n";
				}
			}
		} else {
			std::cout << "centers not equal\n";
		}
		std::cout << "trees are NOT isomorph :(\n";
		unsigned long tEnd = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		std::cout << "took " << tEnd -tStart << " ms\n";
	}
	return 0;
}
