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
