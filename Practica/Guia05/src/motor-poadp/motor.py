#! /usr/bin/python3
# Juan Cruz Mateos
import os
import re
import csv


def write_to_csv(filename: str, table: list, *titles: str):
    with open(filename, "w") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(titles)
        for row in table:
            writer.writerow(row)


def print_table(title: str, table: list, *titles: str):
    print(title)
    count = 1
    print("|", end="")
    for tit in titles:
        print(f"{tit:^20s}|", end="")
        count += 21
    print()
    print("-" * count)
    for row in table:
        print("|", end="")
        for item in row:
            print(f"{str(item):^20s}|", end="")
        print()
    print()


def parseo(base_path="./") -> tuple:
    """Retorna una tupla con dos elementos: t[0] = dict(id_doc, file); t[1] tuplas con los valores (palabra, id_doc)"""
    files_dic = {}
    parsed = []
    txt_files = []
    for root, _, files in os.walk(base_path):
        for file in files:
            if file[-4:] == ".txt":
                full_path = os.path.join(root, file)
                txt_files.append(full_path)
    print(f"{len(txt_files)} archivo(s) encontrado(s)")
    print("Parseando...", end="")
    id_doc = 1
    for file in txt_files:
        files_dic[id_doc] = file
        with open(file, "rt") as txt:
            palabras = txt.read().split()
            procesadas = [re.sub("[\W_]+", "", palabra).lower()
                          for palabra in palabras]
            for palabra in procesadas:
                parsed.append((palabra, id_doc))
        id_doc += 1
    print(" 100% listo")
    return files_dic, parsed


def ordenamiento(parsed: list) -> list:
    """Retorna una lista de tuplas con los valores (palabra, id_doc) ordenada por palabra"""
    print("Ordenando... 100% listo")
    return sorted(parsed, key=lambda palabra: palabra[0])


def agrupamiento(ordenado: list):
    """Retorna una lista de tuplas con los valores (palabra, id_doc, frec)"""
    print("Agrupando...", end="")
    agrupado = []
    i = 0
    cant = 1
    while i < len(ordenado) - 1:
        if ordenado[i][0] == ordenado[i+1][0] and ordenado[i][1] == ordenado[i+1][1]:
            cant += 1
        else:
            agrupado.append((ordenado[i][0], ordenado[i][1], cant))
            cant = 1
        i += 1
    agrupado.append((ordenado[i][0], ordenado[i][1], cant))
    print(" 100% listo")
    return agrupado


def dic_posting(agrupado: list) -> tuple:
    """Retona una tupla: (diccionario, posting) como listas -> para imprimier: sino usar dict"""
    print("Generando diccionario y posteando...", end="")
    dic = []
    post = []

    i = 0
    rr = 0
    rr_ptr = rr
    frec_tot = 0
    while i < len(agrupado) - 1:
        frec_tot += agrupado[i][2]
        if agrupado[i][0] == agrupado[i+1][0]:
            post.append((rr, agrupado[i][1], agrupado[i][2], rr + 1))
            # post[rr] = (agrupado[i][1], agrupado[i][2], rr + 1)
            rr += 1
        else:
            post.append((rr, agrupado[i][1], agrupado[i][2], -1))
            # post[rr] = (agrupado[i][1], agrupado[i][2], -1)
            dic.append((agrupado[i][0], agrupado[i][1], frec_tot, rr_ptr))
            # dic[agrupado[i][0]] = (agrupado[i][1], frec_tot, rr_ptr)
            rr += 1
            rr_ptr = rr
            frec_tot = 0
        i += 1
    if frec_tot == 0:
        frec_tot = agrupado[i][2]
    post.append((rr, agrupado[i][1], agrupado[i][2], -1))
    # post[rr] = (agrupado[i][1], agrupado[i][2], -1)
    dic.append((agrupado[i][0], agrupado[i][1], frec_tot, rr_ptr))
    print(" 100% listo")
    return dic, post


def buscar(palabra: str, dic: list, post: list, files_id: list):
    i = 0
    while i < len(dic) and dic[i][0] != palabra:
        i += 1
    if i == len(dic):
        print("no hay coincidencias")
    else:
        index = dic[i][3]
        while index != -1:
            _, d, f, index = post[index]
            print(f"file={files_id[d]:<35s} frec={f}")


def main(args):
    base = "./" if len(args) == 1 else args[1]
    files_id, parsed = parseo(base)
    # print_table("Parseo", parsed, "Termino", "D#")
    write_to_csv("parseo.csv", parsed, "Termino", "D#")

    if len(files_id) > 0:
        ordered = ordenamiento(parsed)
        # print_table("Ordenamiento", ordered, "Termino", "D#")
        write_to_csv("ordenamiento.csv", ordered, "Termino", "D#")

        grouped = agrupamiento(ordered)
        # print_table("Agrupamiento", grouped, "Termino", "D#", "F#")
        write_to_csv("agrupamiento.csv", grouped, "Termino", "D#", "F#")

        dic, pos = dic_posting(grouped)
        # print_table("Diccionario", dic, "Termino", "TD#", "FT#", "#RR")
        write_to_csv("diccionario.csv", dic, "Termino", "TD#", "FT#", "#RR")
        # print_table("Posting", pos, "#RR", "D#", "F#", "#PR")
        write_to_csv("posting.csv", pos, "#RR", "D#", "F#", "#PR")

        res = 'y'
        while res == 'y':
            ask = input("palabra = ")
            buscar(ask, dic, pos, files_id)
            res = input("\nBuscar otra palabra? (y/n) ")


if __name__ == "__main__":
    import sys
    main(sys.argv)
