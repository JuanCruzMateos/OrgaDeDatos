#! /usr/bin/python3
import xml.etree.ElementTree as ET
import datetime


def main():
    tree = ET.parse('country_data.xml')
    root = tree.getroot()


if __name__ == "__main_":
    main()
