def initialize_single_source(G, s):
    for v in G.V:
        v.d = infinite
        v.p = None
    s.d = 0