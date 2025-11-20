#include <functional>
#include <queue>
#include <iostream>

int main() {
    std::priority_queue<int, std::vector<int>, std::greater<>> pq;
    pq.push(1);
    pq.push(2);
    std::cout << pq.top() << (pq.pop(), pq.top());
    return 0;
}
