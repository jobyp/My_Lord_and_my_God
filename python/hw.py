#!/usr/bin/env python3
# JMJ

import sys


def main():
    principal = 1000
    rate = 0.05
    numyears = 5
    year = 1
    while year <= numyears:
        principal = principal * (1 + rate)
        print(f"{year:>3d} {principal:0.2f}")
        year += 1

    return 0


if __name__ == "__main__":
    main()
    sys.exit(0)
