#! /usr/bin/python3
import json


def main():
    d = {
        "juan": 27,
        "cande": 26,
        "guada": 25,
        "loli": 23
    }

    print("d", d)

    # convert into JSON
    djson = json.dumps(d)

    # parse json to dict
    d_again = json.loads(djson)

    print("djson", djson)
    print("d_again", d_again)


if __name__ == "__main__":
    main()
