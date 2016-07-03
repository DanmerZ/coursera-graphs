#ifndef DISJSET
#define DISJSET

#include <vector>


/* Disjoint set: https://en.wikipedia.org/wiki/Disjoint-set_data_structure
 * Provides two operations:
 * 1) Union: join two subsets into one
 * 2) Find: specify which subset a particular element is in
 *
 * Disjoint set is used to determine whether some edge is in the spanning tree or not.
 */
class DisjSet
{
public:
    explicit DisjSet(int numElements);

    int find(int x);
    void unionSets(int root1, int root2);

private:
    std::vector<int> s;

};

#endif // DISJSET

