#! /usr/bin/python3
import math


def main():
    claves = [10168, 21362, 8515, 7993, 32434, 29786, 35175,
              50255, 32305, 24971, 10177, 53101, 12901]

    hashes = []
    index = ord('a')
    for key in claves:
        address = hash(key)
        print(f"{chr(index)}) {key:5d} -> h({key:5d}) = {address}")
        hashes.append(address)
        index += 1

    N = 1300
    r = 1500

    print(N * (1 - prob(0, r, N) - prob(1, r, N)))
    print(N * prob(0, r, N) - (N-r))


def hash(x: int) -> int:
    return x % 1301


def prob(x: int, r: int, N: int) -> float:
    dens = r / N
    return (dens**x) * (math.e**-dens) / math.factorial(x)


if __name__ == "__main__":
    main()
