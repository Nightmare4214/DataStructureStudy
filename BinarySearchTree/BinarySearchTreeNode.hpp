template<typename T>
class Node {
public:
    T value;
    Node* parent, *left, *right;
    Node() :parent(nullptr), left(nullptr), right(nullptr) {}
    Node(const T &value) :value(value), parent(nullptr), left(nullptr), right(nullptr) {}

};
