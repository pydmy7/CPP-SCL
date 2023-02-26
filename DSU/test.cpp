#include <iostream>
#include <cassert>
#include "DSU.h"

using namespace scl;

int main() {
    
    int n;
    std::cin >> n;
    DSU cur(n);

    int a, b;
    std::cin >> a >> b;
    cur.merge(a, b);
    assert(cur.same(a, b));

    int x;
    std::cin >> x;
    std::cout << "size of " << x << " == " << cur.size(x) << '\n';

    std::cout << "number of connected blocks: " << cur.count() << std::endl;
    
    return 0;
}