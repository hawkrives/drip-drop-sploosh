#include <fstream>
using std::ifstream;
#include "breadth-first-search.h"
#include "common.h"

void print_line() {
	cout << endl << "-----" << endl << endl;
}

void print_header(std::string str) {
	cout << str << endl;
}

int main(int argc, const char* argv[]) {
	string filename = "dimacs.txt";
	if (argc == 2)
		filename = argv[1];
	ifstream f(filename);
	if (!f.good()) {
		std::cerr << "Error reading " << filename << std::endl;
		return 1;
	}
	string s;
	getline(f, s);

	const vector<string> dimacs = split(s, " ");
	const unsigned long numNodes = stoul(dimacs.at(2));
	// const unsigned long numEdges = stoul(dimacs.at(3));

	vector<vector<string>> vertices;
	vertices.reserve(numNodes);

	cout << "loading lines" << endl;

	while(getline(f, s)) {
		vertices.push_back(split(s));
	}

	cout << "creating adjacencies list" << endl;

	map<unsigned long, vector<unsigned long>> adjList;
	for (size_t i = 0; i < numNodes; i++)
		adjList.insert({i, {}});

	for (const auto vertex : vertices) {
		const unsigned long fromVertex = stoul(vertex.at(1));
		const unsigned long toVertex = stoul(vertex.at(2));

		auto search = adjList.find(fromVertex);
		if (search != adjList.end()) {
			search->second.push_back(toVertex);
		}
		else {
			adjList.insert({fromVertex, {toVertex}});
		}
	}

	print_header("printing dimacs file");
	print_dimacs(adjList);

	print_line();

	print_header("DFS-ing the entire graph");
	map<size_t, pair<long, long>> explored_dfs = explore_dfs(adjList);
	print_dfs_results(explored_dfs);

	print_line();

	print_header("BFS-ing the entire graph");
	map<size_t, pair<long, long>> explored_bfs = explore_bfs(adjList);
	print_bfs_results(explored_bfs);

	// print_line();

	// size_t start = 581;
	// cout << "Walking a chunk of the graph, starting at " << start << endl;
	// map<size_t, pair<long, long>> walked = walk(adjList, start);
	// check_dfs_results_for_buckets(walked);

	return 0;
}
