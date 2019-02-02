def build_cartesian_tree(sequence):
    last = root = Node(sequence[0])
    for index in range(1, len(sequence)):
        node = Node(sequence[index])
        while node.value <= last.value and last.parent:
            last = last.parent
        if last.parent:
            last.parent.right = node
            node.parent = last.parent
        node.left = last
        last.parent = last = node
        root = root if node.parent else node
    return root