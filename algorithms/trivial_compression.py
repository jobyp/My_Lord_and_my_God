#!/usr/bin/env python3

import sys
from typing import List


class CompressedGene:
    def __init__(self, gene: str) -> None:
        self._compress(gene)

    def _compress(self, gene: str) -> None:
        self.bit_string: int = 1  # start with sentinel
        for nucleotide in gene.upper():
            self.bit_string <<= 2
            if nucleotide == "A":
                self.bit_string |= 0b00
            elif nucleotide == "C":
                self.bit_string |= 0b01
            elif nucleotide == "G":
                self.bit_string |= 0b10
            elif nucleotide == "T":
                self.bit_string |= 0b11
            else:
                raise ValueError("Invalid Nucleotide:{}".format(nucleotide))
        return

    def decompress(self) -> str:
        chars: List[str] = []
        for i in range(0, self.bit_string.bit_length() - 1, 2):
            bits: int = (self.bit_string >> i) & 0b11
            c: str = ""
            if bits == 0b00:
                c = "A"
            elif bits == 0b01:
                c = "C"
            elif bits == 0b10:
                c = "G"
            else:  # bits == 0b11
                c = "T"
            chars.append(c)
        return "".join(reversed(chars))

    def __str__(self) -> str:
        return self.decompress()


def main():
    from sys import getsizeof

    original: str = (
        "TAGGGATTAACCGTTATATATATATAGCCATGGATCGATTATATAGGGATTAACCGTTATATATATATAGCCATGGATCGATTATA"
        * 100
    )
    print("original is {} bytes".format(getsizeof(original)))
    compressed: CompressedGene = CompressedGene(original)
    print("compressed is {} bytes".format(getsizeof(compressed.bit_string)))
    print(compressed)
    print("original and compressed are same: {}".format(original == str(compressed)))
    return 0


if __name__ == "__main__":
    main()
    sys.exit(0)
