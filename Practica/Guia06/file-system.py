#! /usr/bin/python3
# @authors Noelia Echeverria, Juan Cruz Mateos
from datetime import date
from lxml import etree
import os


class Tag:
    DIR = "dir"
    FILE = "file"


class Attribute:
    NAME = "name"
    SIZE = "size"
    DATE = "date"


def help():
    return """ XML File system commands:
      *  cd [path] :: navigate to path
      *  ls [dir] :: list all files & directories on current directory
      *  mkdir [new dir] :: create new directory in current dir
      *  touch [new file] :: create new file on current dir"""


def ls(currentdir: etree.Element) -> None:
    """List all dirs & files on current directory"""
    for child in currentdir:
        if child.tag == "dir":
            print(f"--d {child.attrib[Attribute.NAME]}")
        else:
            print(f"--f {child.attrib[Attribute.NAME]}")


def cd(currentPath: list, currentDir: etree.Element, dirName: str) -> etree.Element:
    """Changes current directory to dirName"""
    if dirName == "..":
        currentPath.pop()
        return currentDir.find("..")
    currentPath.append(dirName)
    return currentDir.find(f".//{Tag.DIR}[@name='{dirName}']")


def mkdir(currentDir: etree.Element, newDirName: str) -> None:
    """Creates a new directory on current directory"""
    newDir = etree.Element(Tag.DIR)
    newDir.set(Attribute.NAME, newDirName)
    newDir.set(Attribute.DATE, str(date.today()))
    currentDir.append(newDir)


def touch(currentDir: etree.Element, newFileName: str) -> None:
    """Creates a new file on current directory"""
    newFile = etree.Element(Tag.FILE)
    newFile.set(Attribute.NAME, newFileName)
    newFile.set(Attribute.DATE, str(date.today()))
    newFile.set(Attribute.SIZE, "0")
    newFile.text = ""
    currentDir.append(newFile)


def append(node: etree.Element, file: str,  content: str) -> None:
    filenode = node.find(f".//{Tag.FILE}[@name='{file}']")
    filenode.text = filenode.text + content
    filenode.attrib[Attribute.SIZE] = str(int(
        filenode.attrib[Attribute.SIZE]) + len(content))


def cat(node: etree.Element, file: str) -> None:
    filenode = node.find(f".//{Tag.FILE}[@name='{file}']")
    return filenode.text


def main():
    filename = "filesystem.xml"
    fullPath = os.path.abspath(filename)
    xml_parser = etree.XMLParser(remove_blank_text=True)
    xml_tree = etree.parse(fullPath, xml_parser)
    root = xml_tree.getroot()

    currentPath = [root.attrib['name']]
    currentNode = root

    command = input(f" >>> {'/'.join(currentPath)} ")
    while command.split()[0] != "exit":
        command_list = command.split()
        if len(command_list) == 1:      # help, ls, exit
            command = command_list[0]
        elif len(command_list) == 2:    # cd, mkdir, touch
            command, op = command_list
        else:                           # >>
            command = command_list[0]
            op = command_list[1]
            file_content = "".join(command_list[2:])

        if command == "ls":
            ls(currentNode)
        elif command == "cd":
            currentNode = cd(currentPath, currentNode, op)
        elif command == "mkdir":
            mkdir(currentNode, op)
        elif command == "touch":
            touch(currentNode, op)
        elif command == ">>":
            append(currentNode, op, file_content)
        elif command == "cat":
            print(cat(currentNode, op))
        elif command == "help":
            print(help())
        else:
            print(" Unknown command")
        command = input(f" >>> {'/'.join(currentPath)} ")

    et = etree.ElementTree(root)
    et.write(filename, pretty_print=True)


if __name__ == "__main__":
    main()
