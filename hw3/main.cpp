/* Homework 3: Prim and Kruskal Minimum Spanning Tree algorithms
 * Author: Oleh Pomazan oleh.pomazan@gmail.com
 *
 * Description
 *
 * In this homework I implemented Kruskal algorithm
 * for matrix-based graph and added additional constructor
 * for reading and initializing graph from text file.
 *
 * I decided to simplify graph representation because the template-based
 * solution was more than 500 lines and hard to read:
 * https://github.com/DanmerZ/coursera-graphs/blob/master/main.cpp
 *
 * The core of Kruskal algorithm is to select the edges in order of
 * smallest weight and accept an edge if it does not cause a cycle.
 * The main dificulty was to detect the cycle and to decide whether edge
 * should be accepted or rejected to join the tree.
 *
 * The appropriate data structure for such problem is disjoint set with
 * union/find algorithm. Initially algorithm starts with single-node trees (forest).
 * Adding an edge merges two trees into one. When the algoritm terminates, there is
 * only one tree which is the minimum spaning tree.
 *
 * There are 3 classes: Edge, Graph and DisjSet.
 * Kruskal algorithm is implemented in Graph::get_Kruskal_mst() function.
 *
 * Also there's test_Kruskal() function which check the correctness of the implementation
 * using the simple graph.
 *
 *
*/

#include "graph.h"


/*  Simple test graph
 *
 *  B -- 11 -- D
 *  | \        |
 *  5    \4    5
 *  |        \ |
 *  A -- 10 -- C
 *
 * Minimum spanning tree: A-B-C-D with 5+4+5 = 14 cost
 */
void test_Kruskal()
{
    cout << "Test Kruskal algorithm for simple graph:\n";
    char str[] = "B -- 11 -- D\n"
                 "| \\        |\n"
                 "5    \\4    5\n"
                 "|        \\ |\n"
                 "A -- 10 -- C\n";
    cout << str << endl;

    Graph g(4);
    // A: 0
    g.add_edge(0, 1, 5);
    g.add_edge(0, 2, 10);
    // B: 1
    g.add_edge(1, 0, 5);
    g.add_edge(1, 2, 4);
    g.add_edge(1, 3, 11);
    // C: 2
    g.add_edge(2, 0, 10);
    g.add_edge(2, 1, 4);
    g.add_edge(2, 3, 5);
    // D: 3
    g.add_edge(3, 1, 11);
    g.add_edge(3, 2, 5);

    cout << "Minimum spanning tree: ";
    for (auto &edge : g.get_Kruskal_mst())
    {
        cout << "(" << edge.startFrom << "," << edge.pointTo  << "), ";
    }
    cout << endl;

    cout << "Cost: " << g.min_span_tree_cost_Kruskal() << endl;
}

int main()
{
    test_Kruskal();

    cout << "\n\nRead graph from file: graph.txt\n";
    Graph g("graph.txt");
    cout << "Minimal spanning tree as pairs of vertices:\n";
    for (auto &edge : g.get_Kruskal_mst())
    {
        cout << "(" << edge.startFrom << "," << edge.pointTo  << "), ";
    }
    cout << endl;

    cout << "Cost: " << g.min_span_tree_cost_Kruskal() << endl;
    return 0;
}






