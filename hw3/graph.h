#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "disjset.h"

using namespace std;

struct Edge
{
    int pointTo;
    int startFrom;
    int weight;
    Edge(int to, int from, int w) : pointTo(to), startFrom(from), weight(w) {}
};
bool operator<(const Edge& e1, const Edge& e2);
bool operator>(const Edge& e1, const Edge& e2);
bool operator==(const Edge& e1, const Edge& e2);



class Graph
{
private:
    int n, e;
    vector<vector<int>> matrix;

    void init();


public:
    Graph() {}
    Graph(int _n);
    Graph(const char file_name[]);

    ~Graph() {}

    int V() const { return n; }
    int E() const { return e; }

    bool adjacent(int x, int y) const;


    vector<Edge> neighbors(int x);


    void add_edge(int x, int y, int w);


    int get_edge_value(int x, int y);


    int min_span_tree_cost_Kruskal();


    vector<Edge> get_Kruskal_mst();


    void print();


};

#endif // GRAPH_H
