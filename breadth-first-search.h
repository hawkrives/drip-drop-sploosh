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
#include <queue>
using std::queue;
#include <algorithm>
using std::sort;

#include "ostream.h"


size_t clk = 0;
template<typename T>
void follow(map<T, size_t> *pre, map<T, size_t> *post, set<T> *visited, const map<T, vector<T>> adjList, const T start) {
	if (visited->find(start) != visited->end())
		return;

	visited->insert(start);

	auto search = adjList.find(start);
	if (search == adjList.end())
		return;

	pre->insert({start, clk++});
	for (const auto point : search->second) {
		follow(pre, post, visited, adjList, point);
	}
	post->insert({start, clk++});
}


template<typename T>
map<T, pair<long, long>> walk(const map<T, vector<T>> adjList, T start) {
	map<T, size_t> pre;
	map<T, size_t> post;
	set<T> visited;

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
map<T, pair<long, long>> explore_dfs(const map<T, vector<T>> adjList) {
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
void follow_bfs(map<T, size_t> *pre, map<T, size_t> *post, set<T> *visited, queue<T> to_visit, const map<T, vector<T>> adjList, const T start) {
	if (visited->find(start) != visited->end())
		return;

	visited->insert(start);

	auto search = adjList.find(start);
	if (search == adjList.end())
		return;

	pre->insert({start, clk++});
	for (const auto point : search->second) {
		follow_bfs(pre, post, visited, adjList, point);
	}
	post->insert({start, clk++});
}

template<typename T>
map<T, pair<long, long>> explore_bfs(const map<T, vector<T>> adjList) {
	map<T, size_t> pre;
	map<T, size_t> post;

	set<T> visited;
	queue<T> to_visit;

	for (const auto node : adjList)
		for (const auto connection : node.second)
			to_visit.push(connection);

	auto next = to_visit.front();
	while ((next = to_visit.front())) {
		to_visit.pop();

	}
	// for (const auto node : to_visit) {

	// }
	// follow_bfs(&pre, &post, &visited, &to_visit, adjList, *adjList.begin().second);
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
size_t count_edges(const map<T, vector<T>> adjList) {
	set<T> visited;
	map<T, size_t> pre;
	map<T, size_t> post;

	for (const auto pair : adjList) {
		if (pair.second.size()) {
			follow(&pre, &post, &visited, adjList, pair.first);
			clk = 0;
		}
	}

	auto size = visited.size();

	return size;
}

template<typename T>
size_t count_vertices(const map<T, vector<T>> adjList) {
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

void print_dimacs(const map<size_t, vector<size_t>> graph) {
	cout << "p\t" << "edge\t" << count_vertices(graph) << "\t" << count_edges(graph) << endl;
	for (const auto fromVertex : graph)
		for (const auto toVertex : fromVertex.second)
			cout << "e\t" << fromVertex.first << "\t" << toVertex << endl;
}

void print_dfs_results(const map<size_t, pair<long, long>> explored) {
	vector<pair<size_t, pair<long, long>>> sorted;
	for (const auto pair : explored)
		sorted.push_back(pair);

	std::sort(sorted.begin(), sorted.end(), [](pair<size_t, pair<long, long>> a, pair<size_t, pair<long, long>> b) {
        return a.second.first < b.second.first;
    });

	// cout << "vertex: (pre, post)" << endl;
	for (const auto point : sorted) {
		if (point.second.first >= 0 && point.second.second >= 0)
			cout << point.first << ": " << point.second << endl;
	}
}

void print_bfs_results(const map<size_t, pair<long, long>> explored) {
	vector<pair<size_t, pair<long, long>>> sorted;
	for (const auto pair : explored)
		sorted.push_back(pair);

	std::sort(sorted.begin(), sorted.end(), [](pair<size_t, pair<long, long>> a, pair<size_t, pair<long, long>> b) {
        return a.second.first < b.second.first;
    });

	// cout << "vertex: (pre, post)" << endl;
	for (const auto point : sorted) {
		if (point.second.first >= 0 && point.second.second >= 0)
			cout << point.first << ": " << point.second << endl;
	}
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
