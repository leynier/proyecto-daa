def dijkstra(G, s):
    initialize_single_source(G, s)
    S = set()
    Q = G.V
    while Q != 0:
        u = extract_min(Q)
        S = S + u
        for v in G.Adj[u]:
            relax(u, v, w)