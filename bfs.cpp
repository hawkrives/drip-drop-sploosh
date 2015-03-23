#include <fstream>
using std::ifstream;
#include <string>
using std::string;
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
	const unsigned long numEdges = stoul(dimacs.at(3));

	vector<vector<string>> vertices;
	vertices.reserve(numNodes);

	cout << "loading lines" << endl;

	while(getline(f, s)) {
		vertices.push_back(split(s));
	}

	cout << "creating adjacencies list" << endl;

	map<string, set<string>> adjList;
	// map<unsigned long, vector<unsigned long>> adjList;
	// for (auto i = 0; i < numNodes; i++)
		// adjList.insert({i, {}});

	for (const auto vertex : vertices) {
		// const unsigned long fromVertex = stoul(vertex.at(1));
		// const unsigned long toVertex = stoul(vertex.at(2));
		const string fromVertex = vertex.at(1);
		const string toVertex = vertex.at(2);

		auto search = adjList.find(fromVertex);
		if (search != adjList.end()) {
			search->second.insert(toVertex);
		}
		else {
			adjList.insert({fromVertex, {toVertex}});
		}
	}
	for (const auto vertex : adjList) {
		for (const auto to : vertex.second) {
			auto search = adjList.find(to);
			if (search != adjList.end()) {
				search->second.insert(vertex.first);
			}
			else {
				adjList.insert({to, {vertex.first}});
			}
		}
	}

	print_header("printing dimacs file");
	print_dimacs(adjList, numEdges);

	print_line();

	print_header("DFS-ing the entire graph");
	string start = "S";
	map<string, pair<long, long>> explored_dfs = walk_dfs(adjList, start);
	print_dfs_results(explored_dfs);

	print_line();

	print_header("BFS-ing the entire graph");
	start = "S";
	map<string, long> explored_bfs = walk_bfs(adjList, start);
	print_bfs_results(explored_bfs);

	// print_line();

	// size_t start = 581;
	// cout << "Walking a chunk of the graph, starting at " << start << endl;
	// map<size_t, pair<long, long>> walked = walk(adjList, start);
	// check_dfs_results_for_buckets(walked);

	return 0;
}
