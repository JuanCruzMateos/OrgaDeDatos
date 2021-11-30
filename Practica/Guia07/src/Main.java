package Practica.Guia07.src;

import java.io.File;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.DOMImplementation;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Text;

public class Main {

    public static void main(String[] args)
            throws ParserConfigurationException, TransformerFactoryConfigurationError, TransformerException {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        DOMImplementation implementation = builder.getDOMImplementation();

        Document documento = implementation.createDocument(null, "Toma_de_Temperaturas", null);
        documento.setXmlVersion("1.0");

        Element tomaDeTemperaturas = documento.createElement("Toma_de_Temperaturas");

        Element t1 = documento.createElement("Toma_de_Temperatura");
        Element dia = documento.createElement("Dia");
        Text textDia = documento.createTextNode("21-11-2016");
        dia.appendChild(textDia);
        t1.appendChild(dia);

        Element lugar1 = documento.createElement("Lugar_1");
        Text textLugar1 = documento.createTextNode("15");
        lugar1.appendChild(textLugar1);

        Element lugar2 = documento.createElement("Lugar_2");
        Text textLugar2 = documento.createTextNode("20");
        lugar2.appendChild(textLugar2);

        Element lugar3 = documento.createElement("Lugar_3");
        Text textLugar3 = documento.createTextNode("18");
        lugar3.appendChild(textLugar3);

        t1.appendChild(lugar1);
        t1.appendChild(lugar2);
        t1.appendChild(lugar3);

        Element t2 = documento.createElement("Toma_de_Temperatura");
        Element dia2 = documento.createElement("Dia");
        Text textDia2 = documento.createTextNode("22-11-2016");
        dia2.appendChild(textDia2);
        t2.appendChild(dia2);

        Element lugar12 = documento.createElement("Lugar_1");
        Text textLugar12 = documento.createTextNode("22");
        lugar12.appendChild(textLugar12);

        Element lugar22 = documento.createElement("Lugar_2");
        Text textLugar22 = documento.createTextNode("20");
        lugar22.appendChild(textLugar22);

        Element lugar32 = documento.createElement("Lugar_3");
        Text textLugar32 = documento.createTextNode("28");
        lugar32.appendChild(textLugar32);

        t2.appendChild(lugar12);
        t2.appendChild(lugar22);
        t2.appendChild(lugar32);

        documento.getDocumentElement().appendChild(t1);
        documento.getDocumentElement().appendChild(t2);

        Source source = new DOMSource(documento);
        Result result = new StreamResult(new File("Toma_de_Temperaturas.xml"));

        Transformer transformer = TransformerFactory.newInstance().newTransformer();
        transformer.transform(source, result);

    }

}