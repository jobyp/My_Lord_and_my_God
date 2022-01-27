#!/usr/bin/env python3

from functools import lru_cache
from typing import Dict, Generator
import sys

memo: Dict[int, int] = {0: 0, 1: 1}


def fib1(n: int) -> int:
    # Case for negative numbers
    if n < 0:
        return 0

    if n in memo:
        return memo[n]

    memo[n] = fib1(n - 1) + fib1(n - 2)
    return memo[n]


@lru_cache(maxsize=None)
def fib2(n: int) -> int:
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib2(n - 1) + fib2(n - 2)


def fib3(n: int) -> int:
    if n <= 0:
        return 0
    if n == 1:
        return 1

    a: int = 0  # initially set to fib(0)
    b: int = 1  # initially set to fib(1)

    for _ in range(1, n):
        a, b = b, (a + b)
    return b


def fib4(n: int) -> Generator[int, None, None]:
    yield 0
    if n > 0:
        yield 1
    a: int = 0
    b: int = 1
    for _ in range(1, n):
        a, b = b, (a + b)
        yield b


def main():
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 50
    print("fib3({}) is {}".format(n, fib3(n)))
    for i in fib4(50):
        print(i)
    return 0


if __name__ == "__main__":
    main()
    sys.exit(0)
