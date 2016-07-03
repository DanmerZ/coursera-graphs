#include "disjset.h"

DisjSet::DisjSet(int numElements) : s(numElements, -1) { }

// Return the set containing x
int DisjSet::find(int x)
{
    if (s[x] < 0)
        return x;
    else
        return find(s[x]);
}

// Join two subsets
void DisjSet::unionSets(int root1, int root2)
{
    if (s[root2] < s[root1])
        s[root1] = root2;
    else
    {
        if (s[root1] == s[root2])
            --s[root1];
        s[root2] = root1;
    }
}
