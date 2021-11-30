import urllib.request
import xml.etree.ElementTree as ET

url = "http://www.agencia.mincyt.gob.ar/frontend/agencia/rss_feed"
uh = urllib.request.urlopen(url)
data = uh.read()
commentinfo = ET.fromstring(data)
print(commentinfo)
tree = ET.ElementTree(commentinfo)
tree.write("rss.xml")
