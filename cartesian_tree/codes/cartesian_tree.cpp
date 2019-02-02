template<typename T>
Node<T> *build_cartesian_tree(vector<T> *sequence) {
    auto root = new Node<T>(sequence->at(0));
    auto last = root;
    for (auto i = 1; i < sequence->size(); ++i) {
        auto node = new Node<T>(sequence->at(i));
        while (node->value <= last->value and last->parent != nullptr)
            last = last->parent;
        if (last->parent != nullptr) {
            last->parent->right = node;
            node->parent = last->parent;
        }
        node->left = last;
        last = last->parent = node;
        root = node->parent != nullptr ? root : node;
    }
    return root;
}