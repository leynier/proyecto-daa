def dijkstra(G, s):
    p = [None] * len(G)
    d = [infinite] * len(G)
    d[s] = 0
    Q = [(0, s)]
    while Q:
        u = heappop(Q)[1]
        for v, w in G.edges[u]:
            if d[v] > d[u] + w:
                d[v] = d[u] + w
                p[v] = u
                heappush(Q, (d[v], v))
    return d, p