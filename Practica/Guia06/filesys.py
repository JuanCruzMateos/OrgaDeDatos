#! /usr/bin/python3
from ast import NodeTransformer
import xml.etree.ElementTree as ET
import os


class Tag:
    DIR = "dir"
    FILE = "file"


class Attribute:
    NAME = "name"
    SIZE = "size"


def help():
    return """ XML File system commands:
      *  cd [path] :: navigate to path
      *  ls [dir] :: list all files & directories on current directory
      *  mkdir [new dir] :: create new directory in current dir
      *  touch [new file] :: create new file on current dir"""


def ls(currentdir: ET.Element) -> None:
    """List all dirs & files on current directory"""
    for child in currentdir:
        if child.tag == "dir":
            print(f"--d {child.attrib[Attribute.NAME]}")
        else:
            print(f"--f {child.attrib[Attribute.NAME]}")


def cd(currentDir: ET.Element, dirName: str) -> ET.Element:
    """Changes current directory to dirName"""
    # if dirName == "..":
    #     parent = currentDir.find("dir[..]")
    return currentDir.find(f".//{Tag.DIR}[@name='{dirName}']")


def mkdir(currentDir: ET.Element, newDirName: str) -> None:
    """Creates a new directory on current directory"""
    pass


def touch(currentDir: ET.Element, newFileName: str) -> None:
    """Creates a new file on current directory"""
    newFile = ET.Element(Tag.FILE)
    newFile.set(Attribute.NAME, newFileName)
    newFile.set(Attribute.SIZE, "0")
    currentDir.append(newFile)


def append(node: ET.Element, file: str,  content: str) -> None:
    filenode = node.find(f".//{Tag.FILE}[@name='{file}']")
    filenode.text += filenode.text + content


def main():
    filename = "filesystem.xml"
    fullPath = os.path.abspath(filename)
    tree = ET.parse(fullPath)
    root = tree.getroot()

    # currentPath = root.attrib['name']
    # currentNode = root

    # command = input(f" >>> {currentPath} ")
    # while command.split()[0] != "exit":
    #     if command == "ls":
    #         ls(currentNode)
    #     elif command == "cd":
    #         cd()
    #     elif command == "mkdir":
    #         pass
    #     elif command == "touch":
    #         pass
    #     else:
    #         print(" Unknown command")
    #     command = input(f" >>> {currentPath} ")

    # bin = cd(root, "bin")
    # ls(bin)
    # touch(bin, "")
    mkdir(root, "src")
    src = cd(root, "src")
    touch(src, "main.c")
    append(src, "main.c", "#include <stdio.h>")
    ls(root)

    tree.write(fullPath)


if __name__ == "__main__":
    main()
