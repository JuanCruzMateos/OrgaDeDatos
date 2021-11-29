#! /usr/bin/python3
# Juan Cruz Mateos
from ast import increment_lineno
import math
from typing import Hashable


def hash(x: int) -> int:
    return x % 1301


def p(x: int, N: int, r: int) -> float:
    return ((r/N)**x) * math.e**(-r/N) / math.factorial(x)


def main():
    claves = [10168, 21362, 8515, 7993, 32434, 29786, 35175,
              50255, 32305, 24971, 10177, 53101, 12901]

    hashes = set()
    index = ord('a')
    for key in claves:
        address = hash(key)
        print(f"{chr(index)}) {key:5d} -> h({key:5d}) = {address}")
        hashes.add(address)
        index += 1

    N = 1300
    r = len(hashes)
    print(f"\nFactor de ocupacion = {r/N}")

    r = 1500
    print(f"p(0) = {p(0, N, r)}")
    print(f"prob. colisiones = 1-p(0)-p(1) = {1-p(0, N, r)-p(1, N, r)}")
    print(f"expected # of overflow records = {N*p(0, N, r) - (N-r)}")


if __name__ == "__main__":
    main()
