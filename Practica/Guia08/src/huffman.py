#! /usr/bin/python3
# @author Juan Cruz Mateos
from pprint import pprint


class Nodo:
    def __init__(self, simb: str, prob: int, izq=None, der=None):
        self.simb = simb
        self.prob = prob
        self.izq = izq
        self.der = der

    def is_hoja(self):
        return self.izq == None and self.der == None

    def __str__(self) -> str:
        return f"simb={self.simb}, prob={self.prob}"


def calc_frecuencies(input: str) -> dict:
    frec = {}
    for char in input:
        frec[char] = frec.get(char, 0) + 1
    return frec


def calc_probabilities(frec: dict) -> dict:
    prob = {}
    total = sum(frec.values())
    for char in frec:
        prob[char] = frec[char] / total
    return prob


def create_tree(prob: dict) -> Nodo:
    minHeap = []
    for char, p in prob.items():
        minHeap.append(Nodo(char, p))

    while len(minHeap) > 1:
        minHeap.sort(key=lambda nodo: nodo.prob)
        # print(*minHeap)
        hijoIzq = minHeap.pop(0)
        hijoDer = minHeap.pop(0)
        # print(hijoIzq.simb, hijoIzq.prob, hijoDer.simb, hijoDer.prob)
        padre = Nodo(None, hijoIzq.prob + hijoDer.prob, hijoIzq, hijoDer)
        minHeap.append(padre)
    return minHeap.pop()


def encode(code: dict, nodo: Nodo, huff: str = ""):
    if nodo.is_hoja():
        code[nodo.simb] = huff
    else:
        encode(code, nodo.izq, huff + "0")
        encode(code, nodo.der, huff + "1")


def printable(c: str) -> str:
    if not c.isalpha():
        return "' '"
    return c


def print_codes(huff_codes: dict):
    print(f"{'simb':^10s}|{'huffman':^10s}")
    print('-' * 21)
    for simb, code in huff_codes.items():
        print(f"{printable(simb):^10s}|{code:^10s}")


def main():
    huff_codes = {}
    string = "CALIDO AMANECER SOLEADO"

    frecuencias = calc_frecuencies(string)
    # pprint(frecuencias)
    # s = sorted(frecuencias.items(), key=lambda item: item[1], reverse=True)
    # pprint(s)
    probabilidades = calc_probabilities(frecuencias)
    # pprint(probabilidades)
    # p = sorted(probabilidades.items(), key=lambda item: item[1], reverse=True)
    # pprint(p)
    # # prob = {"s1": 0.6, "s2": 0.2, "s3": 0.1, "s4": 0.1}
    root = create_tree(probabilidades)
    encode(huff_codes, root)
    print_codes(huff_codes)


if __name__ == "__main__":
    main()
