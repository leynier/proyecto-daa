def segmented_sieve(n):
    limit = int(sqrt(n)) + 1
    primes = sieve(limit)
    low = limit
    high = limit * 2
    while low < n:
        if high >= n:
            high = n
        mark = [True] * (limit + 1)
        for prime in primes:
            lo_lim = int(low / prime) * prime
            if lo_lim < low:
                lo_lim += prime
            for j in range(lo_lim, high, prime):
                mark[j - low] = False
        for i in range(low, high):
            if mark[i - low]:
                print(i)
        low = low + limit
        high = high + limit