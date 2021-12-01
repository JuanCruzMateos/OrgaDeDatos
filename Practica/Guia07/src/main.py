#! /usr/bin/python3
# @author Juan Cruz Mateos, Noelia Echeverria
from urllib.request import urlopen
import xml.etree.ElementTree as ET


def main():
    url = "http://www.agencia.mincyt.gob.ar/frontend/agencia/rss_feed"
    req = urlopen(url)
    # <class 'bytes'>
    xml_str = req.read()
    # <class 'xml.etree.ElementTree.Element'>
    xmlparser = ET.XMLParser(encoding="utf-8")
    xml = ET.fromstring(xml_str, xmlparser)
    # <class 'xml.etree.ElementTree.ElementTree'>
    et = ET.ElementTree(xml)
    et.write("rss.xml")


if __name__ == "__main__":
    main()
