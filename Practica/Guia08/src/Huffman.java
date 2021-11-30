import java.util.*;

public class Huffman {
    protected TreeMap<String, Integer> frec = new TreeMap<>();
    protected TreeMap<String, Double> prob = new TreeMap<>();
    protected final TreeMap<String, String> huffcodes = new TreeMap<>();
    protected String msgToEncode;
    protected Nodo root;

    public static String printable(String c) {
        if (c.equals(" ")) {
            return "' '";
        }
        return c;
    }

    public static void main(String[] args) {
        Huffman h = new Huffman();
        String msg = "CALIDO AMANECER SOLEADO";

        h.analizeInput(msg);

        // TreeMap<String, Double> p = new TreeMap<>();
        // p.put("s1", 0.6);
        // p.put("s2", 0.2);
        // p.put("s3", 0.1);
        // p.put("s4", 0.1);
        // h.setProb(p);
        h.generarArbolCodificacion();
        // h.generarCodigos();
        // System.out.println(h);
        // System.out.println("Encoded msg = " + h.getEncodedMsg());
    }

    public void setProb(TreeMap<String, Double> prob) {
        this.prob = prob;
    }

    public void analizeInput(String msg) {
        this.msgToEncode = msg;
        for (int i = 0; i < msg.length(); i++) {
            String c = String.valueOf(msg.charAt(i));
            this.frec.put(c, this.frec.getOrDefault(c, 0) + 1);
        }
        // System.out.println(this.frec);
        this.frec.forEach((k, v) -> this.prob.put(k, (double) v / msg.length()));
        // System.out.println(this.prob);
        // this.frec.forEach((k, v) -> System.out.println(k + " " + v));
        // this.prob.forEach((k, v) -> System.out.println(k + " " + v));
    }

    public void generarArbolCodificacion() {
        PriorityQueue<Nodo> pq = new PriorityQueue<>();
        Nodo hijoIzq, hijoDer, padre;

        for (String s : this.prob.keySet()) {
            pq.add(new Nodo(s, this.prob.get(s), null, null));
        }
        while (pq.size() > 1) {
            hijoIzq = pq.poll();
            hijoDer = pq.poll();
            System.out.println(hijoIzq.simb + " " + hijoIzq.prob + ", " + hijoDer.simb + " " + hijoDer.prob);
            padre = new Nodo(null, hijoIzq.prob + hijoDer.prob, hijoIzq, hijoDer);
            pq.add(padre);
        }
        this.root = pq.poll();
    }

    public void generarCodigos() {
        this.encode(this.root, "");
    }

    private void encode(Nodo root, String s) {
        if (root.isHoja()) {
            this.huffcodes.put(root.simb, s);
        } else {
            encode(root.izq, s + "0");
            encode(root.der, s + "1");
        }
    }

    public String getEncodedMsg() {
        String result = "";
        for (int i = 0; i < this.msgToEncode.length(); i++) {
            String c = String.valueOf(this.msgToEncode.charAt(i));
            result += this.huffcodes.get(c);
        }
        result += "\n";
        return result;
    }

    @Override
    public String toString() {
        StringBuilder huff = new StringBuilder();
        huff.append("Huffman Codes").append("\n");
        for (String s : this.huffcodes.keySet()) {
            huff.append(String.format("word=%s, frec=%d, code=%s\n", Huffman.printable(s), this.frec.get(s),
                    this.huffcodes.get(s)));
        }
        return huff.toString();
    }

    public static class Nodo implements Comparable<Nodo> {
        public final String simb;
        public final double prob;
        public final Nodo izq;
        public final Nodo der;

        public Nodo(String simb, double prob, Nodo izq, Nodo der) {
            this.simb = simb;
            this.prob = prob;
            this.izq = izq;
            this.der = der;
        }

        public boolean isHoja() {
            return this.izq == null && this.der == null;
        }

        @Override
        public int compareTo(Nodo o) {
            return Double.compare(this.prob, o.prob);
        }

        @Override
        public String toString() {
            return "{ simb=" + this.simb + ", prob=" + this.prob + " }";
        }

        public double getProb() {
            return prob;
        }
    }
}