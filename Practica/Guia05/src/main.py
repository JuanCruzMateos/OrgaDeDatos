#! /usr/bin/python3
import os

def main():
    dic = {}
    for root, dirs, files in os.walk("./"):
        for name in files:
            parse(dic, os.path.join(root, name))
    askfile = input("filename = ")



def parse(dic, filename):

    with open(filename, "rt") as file:
        all = file.read()
        arr = all.split()
        print(arr)


if __name__ == "__main__":
    main()
