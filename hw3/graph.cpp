#include "graph.h"

/* Returns minimum spanning tree as vector of edges.
 * Implements Kruskal algorithm using priority queue of edges
 * and find/union algorithms of disjoint set class.
 */
vector<Edge> Graph::get_Kruskal_mst()
{
    DisjSet ds(n); // initialize disjoint set
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // priority queue of edges
    vector<Edge> mst; // minimum spanning tree

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++ )
        {
            if (adjacent(i,j))
                pq.push(Edge(j,i,get_edge_value(i,j))); // store all edges in the priority queue based on their weights
        }
    }

    while (mst.size() != static_cast<unsigned int>(n-1)) // size of tree is n-1
    {
        Edge e = pq.top(); // get the top edge from queue
        pq.pop();

        // check the sets of start and end vertices of the currect edge; the same set means the cycle
        int uset = ds.find(e.startFrom);
        int vset = ds.find(e.pointTo);

        // if vertices from different sets
        if (uset != vset)
        {
            mst.push_back(e); // push edge into tree
            ds.unionSets(uset, vset); // join vertices to the same subset
        }
    }
    return mst;
}

// Initialize graph by default zeroes and reserve enough memory
void Graph::init()
{
    matrix.reserve(n);
    for (int i = 0; i < n; i++)
    {
        matrix.push_back(std::vector<int>());
        matrix[i].reserve(n);
        for (int j = 0; j < n; j++)
        {
            matrix[i].push_back(0.0); // initialize by zero
        }
    }
}

// Initialize by zeroes graph of size _n
Graph::Graph(int _n)
    : n(_n), e(0)
{
    assert(n >= 0);
    init();
}

/* Open text file with graph information,
 * read it and create a graph
 */

Graph::Graph(const char file_name[])
{
    ifstream ifs(file_name);
    assert(ifs.good());
    istream_iterator<int> start(ifs), end;
    vector<int> nums(start, end);
    ifs.close();
    assert((nums.size()-1)%3 == 0);

    n = nums[0];
    init();

    for (int i = 1; i < static_cast<int>(nums.size()); i += 3)
    {
        add_edge(nums[i],nums[i+1],nums[i+2]);
    }
}

// Check whether two vertices have edge between them
bool Graph::adjacent(int x, int y) const
{
    assert(x >= 0 || y >= 0);
    return matrix[x][y] != 0.0;
}

// Get the vector of edges which start from given vertix x
vector<Edge> Graph::neighbors(int x)
{
    assert(x >= 0);
    std::vector<Edge> nbrs;
    for (int i = 0; i < n; i++)
        if (matrix[x][i] != 0)
            nbrs.push_back(Edge(i,x,matrix[x][i]));
    return nbrs;
}

// Connect x and y vertices by edge with weight w
void Graph::add_edge(int x, int y, int w)
{
    assert(x >= 0 || y >= 0 || w >= 0);
    if (matrix[x][y] == 0.0)
        e++;
    matrix[x][y] = w;
}

// Get weight of edge between x and y
int Graph::get_edge_value(int x, int y)
{
    assert(x >= 0 || y >= 0);
    return matrix[x][y];
}

// Calculate total cost of spanning tree
int Graph::min_span_tree_cost_Kruskal()
{
    vector<Edge> mst = get_Kruskal_mst();
    int sum = 0;
    for (auto &edge : mst)
        sum += edge.weight;
    return sum;
}

// Print out graph
void Graph::print()
{
    cout << "Matrix-based graph\n";
    cout << "Number of vertices: " << n << endl;
    cout << "Number of edges: " << e << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "V" << i << ": ";
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != 0)
                cout << "[" << j << ",w" << matrix[i][j] << "] ";
        }
        cout << endl;
    }
}

// Overloaded operators to compare edges for priority queue
bool operator<(const Edge &e1, const Edge &e2)  { return e1.weight < e2.weight; }
bool operator>(const Edge &e1, const Edge &e2) { return e1.weight > e2.weight; }
bool operator==(const Edge &e1, const Edge &e2)
{ return e1.weight == e2.weight
      && e1.pointTo == e2.pointTo
      && e1.startFrom == e2.startFrom;
}

