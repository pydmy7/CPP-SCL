template<class T>
class LazyEraseHeap {
private:
    std::priority_queue<T> info, del;

public:
    void push(const T& a) {
        info.push(a);
    }
    void update() {
        while (!del.empty() && info.top() == del.top()) {
            info.pop();
            del.pop();
        }
    }
    void pop() {
        update();
        info.pop();
    }
    void erase(const T& a) {
        del.push(a);
    }
    bool empty() {
        update();
        return info.empty();
    }
    T top() {
        update();
        return info.top();
    }
};