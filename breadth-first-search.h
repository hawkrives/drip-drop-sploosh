#ifndef HMR_BFS
#define HMR_BFS true

#include <vector>
using std::vector;
#include <map>
using std::map;
#include <set>
using std::set;
#include <utility>
using std::pair;
// #include <numeric>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <deque>
using std::deque;
#include <algorithm>
using std::sort;
#include <stack>
using std::stack;

#include "ostream.h"


// bool isDestination(string possibility) {
// 	// cout << possibility << endl;
// 	return (possibility.at(0) == '2' || possibility.at(1) == '2');
// }

size_t clk = 0;
template<typename T>
bool follow(map<T, size_t> *pre, map<T, size_t> *post, set<T> *visited, const map<T, set<T>> adjList, const T start) {
	// if start is in visited
	if (visited->find(start) != visited->end())
		return true;

	visited->insert(start);

	auto search = adjList.find(start);

	pre->insert({start, clk++});
	bool go_on;
	// if (!isDestination(start)) {
		for (const auto point : search->second) {
			go_on = follow(pre, post, visited, adjList, point);
			if (!go_on) {
				break;
			}
		}
	// }
	// else {
	// 	cout << "destination! " << start << endl;
	// }
	post->insert({start, clk++});
	return go_on;
}


template<typename T>
map<T, pair<long, long>> walk_dfs(const map<T, set<T>> adjList, T start) {
	map<T, size_t> pre;
	map<T, size_t> post;
	set<T> visited;

	// cout << adjList << endl;

	follow(&pre, &post, &visited, adjList, start);
	clk = 0;

	map<T, pair<long, long>> results;
	for (const auto point : visited) {
		auto preSearch = pre.find(point);
		auto postSearch = post.find(point);

		results.insert({point, {
			(preSearch != pre.end()) ? preSearch->second : -1,
			(postSearch != post.end()) ? postSearch->second : -1,
		}});
	}

	return results;
}


template<typename T>
map<T, pair<long, long>> explore_dfs(const map<T, set<T>> adjList) {
	map<T, size_t> pre;
	map<T, size_t> post;
	set<T> visited;

	for (const auto pair : adjList)
		follow(&pre, &post, &visited, adjList, pair.first);
	clk = 0;

	map<T, pair<long, long>> results;
	for (const auto point : visited) {
		auto preSearch = pre.find(point);
		auto postSearch = post.find(point);

		results.insert({point, {
			(preSearch != pre.end()) ? static_cast<long>(preSearch->second) : -1,
			(postSearch != post.end()) ? static_cast<long>(postSearch->second) : -1,
		}});
	}

	return results;
}


template<typename T>
map<T, long> walk_bfs(const map<T, set<T>> adjList, T start) {
	map<T, long> distance;
	set<T> visited;

	cout << "start: " << start << endl;

	distance.insert({start, 0});
	deque<T> q;
	q.push_back(start);
	T current;
	while (q.size()) {
		// cout << current << " " << q << endl;

		current = q.front();
		q.pop_front();
		visited.insert(current);

		// if (isDestination(current))
		// 	break;

		auto search = adjList.find(current);
		if (search != adjList.end()) {
			// cout << search->second << endl;
			for (const auto edge : search->second) {
				if (visited.find(edge) == visited.end()) {
					q.push_back(edge);
					auto edgeInDistance = distance.find(edge);
					if (edgeInDistance == distance.end()) {
						distance.insert({edge, distance.at(current) + 1});
					}
					visited.insert(edge);
				}
			}
		}
	}

	// cout << distance << endl;

	return distance;
}

////////

template<typename T>
int sizeOfSet(pair<T, set<T>> first, pair<T, set<T>> second) {
	return first.second.size() + second.second.size();
}


template<typename T>
size_t count_edges(const map<T, set<T>> adjList) {
	size_t totalEdges = 0;
	for (const auto node : adjList) {
		totalEdges += node.second.size();
	}
	return totalEdges;
}

template<typename T>
size_t count_vertices(const map<T, set<T>> adjList) {
	// cout << "counting vertices" << endl;
	set<T> seen;
	for (const auto point : adjList) {
		seen.insert(point.first);
		for (const auto subpoint : point.second) {
			seen.insert(subpoint);
		}
	}
	return seen.size();
}

template<typename T>
void print_dimacs(const map<T, set<T>> graph) {
	cout << "p\t" << "edge\t" << count_vertices(graph) << "\t" << count_edges(graph) << endl;
	for (const auto fromVertex : graph)
		for (const auto toVertex : fromVertex.second)
			cout << "e\t" << fromVertex.first << "\t" << toVertex << endl;
}

template<typename T>
void print_dfs_results(const map<T, pair<long, long>> explored) {
	vector<pair<T, pair<long, long>>> sorted;
	for (const auto pair : explored)
		sorted.push_back(pair);

	std::sort(sorted.begin(), sorted.end(), [](pair<T, pair<long, long>> a, pair<T, pair<long, long>> b) {
        return a.second.first < b.second.first;
    });

	// cout << "vertex: (pre, post)" << endl;
	for (const auto point : sorted) {
		if (point.second.first >= 0 && point.second.second >= 0)
			cout << point.first << ": " << point.second << endl;
	}
}

template<typename T>
void print_bfs_results(const map<T, long> explored) {
	// vector<pair<size_t, pair<long, long>>> sorted;
	// for (const auto pair : explored)
	// 	sorted.push_back(pair);
	//
	// std::sort(sorted.begin(), sorted.end(), [](pair<size_t, pair<long, long>> a, pair<size_t, pair<long, long>> b) {
    //     return a.second.first < b.second.first;
    // });

	// cout << "vertex: (pre, post)" << endl;
	cout << explored << endl;
	// for (const auto point : explored) {
	// 	cout << point.first << ": " << point.second << endl;
	// }
}

void check_dfs_results_for_buckets(const map<size_t, pair<long, long>> explored) {
	vector<pair<size_t, pair<long, long>>> sorted;
	for (const auto pair : explored)
		sorted.push_back(pair);

	sort(sorted.begin(), sorted.end(), [](pair<size_t, pair<long, long>> a, pair<size_t, pair<long, long>> b) {
        return a.second.first < b.second.first;
    });

	for (const auto point : sorted) {
		if (point.second.first >= 0 && point.second.second >= 0) {
			string at = to_string(point.first);
			int first = stoi(at.substr(0, 1)) - 1;
			int second = stoi(at.substr(1, 1)) - 1;
			int third = stoi(at.substr(2, at.size())) - 1;
			cout << first << ", " << second << ", " << third << ": " << point.second.first << endl;
			if (first == 2 || second == 2) {
				break;
			}
		}
	}
}

#endif
