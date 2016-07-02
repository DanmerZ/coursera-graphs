#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <random>
#include <set>

using namespace std;

struct Edge
{
    int vertex;
    int weight;
    Edge(int v, int w) : vertex(v), weight(w) {}

};

bool operator<(const Edge& e1, const Edge& e2) { return e1.weight < e2.weight; }

class Graph
{
private:
    int n, e;
    vector<vector<int>> matrix;

    void init()
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

public:
    Graph() {}
    Graph(int _n) : n(_n), e(0)
    {
        assert(n >= 0);
        init();
    }
    Graph(const char file_name[])
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
            cout << "(" << nums[i] << "," << nums[i+1] << "," << nums[i+2] << ")\n";
            //addEdge(nums[i],nums[i+1],nums[i+2]);
        }
    }
    ~Graph() {}

    int V() const { return n; }
    int E() const { return e; }

    bool adjacent(int x, int y) const
    {
        assert(x >= 0 || y >= 0);
        return matrix[x][y] != 0.0;
    }

    vector<Edge> neighbors(int x)
    {
        assert(x >= 0);
        std::vector<Edge> nbrs;
        for (int i = 0; i < n; i++)
            if (matrix[x][i] != 0)
                nbrs.push_back(Edge(i,matrix[x][i]));
        return nbrs;
    }

    void add_edge(int x, int y, int w)
    {
        assert(x >= 0 || y >= 0 || w >= 0);
        if (matrix[x][y] == 0.0)
            e++;
        matrix[x][y] = w;
    }

    int get_edge_value(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        return matrix[x][y];
    }

    vector<Edge> get_Prim_mst()
    {
        vector<Edge> mst;
        vector<int> visited;

        for (int i = 0; i < n; i++)
        {
            visited.push_back(i);

            auto nei = neighbors(i);
            int distance = 10000;
            Edge nearest_vertex(-1, 10000);
            for (auto &edge : nei)
            {
                bool isVisited = find(visited.begin(), visited.end(), edge.vertex)!=visited.end();
                if (isVisited) continue;

                if (distance > edge.weight)
                {
                    distance = edge.weight;
                    nearest_vertex = edge;
                }
            }
            if (nearest_vertex.vertex != -1)
                mst.push_back(nearest_vertex);
        }

        for (auto &edge : mst)
        {
            cout << edge.vertex << ", " << edge.weight << endl;
        }
//        cout << n;
//        for (int i = 0; i < n; i++)
//        {
//            if (visited.find(i) == visited.end()) continue;
//            visited.insert(i);

//            auto nei = neighbors(i);
//            Edge shortest_edge = *min_element(nei.begin(), nei.end());
//            mst.push_back(shortest_edge);

//            int nearest_vertex = shortest_edge.vertex;

//            cout << i << ": " << nearest_vertex << "; ";
//            for (auto &edge : neighbors(i))
//            {
//                cout << edge.weight << ",";
//            }
//            cout << endl;
//        }
        return mst;
    }

    vector<Edge> get_Kruskal_mst()
    {

    }

    void print()
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

};

/*  Simple test graph
 *
 *  B -- 11 -- D
 *  | \        |
 *  5    \4     5
 *  |        \ |
 *  A -- 10 -- C
 *
 * Minimum spanning tree: A-B-C-D with 5+4+5 = 14 cost
 */
void test_Prim()
{
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

    g.get_Prim_mst();

    //g.print();
}

int main()
{
    test_Prim();
   // Graph g("graph.txt");
    return 0;
}

