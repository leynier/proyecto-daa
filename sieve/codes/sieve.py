def sieve(n):
    primes = [True] * n
    primes[0] = primes[1] = False
    for i in range(2, int(sqrt(n))):
        if primes[i]:
            for j in range(i * i, n, i):
                primes[j] = False
    return [i for i, x in enumerate(primes) if x]