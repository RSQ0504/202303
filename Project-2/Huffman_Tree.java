import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Huffman_Tree {
    private Node root;
    private static class Node {
        int value;           
        int frequency;     
        Node left;   
        Node right;  

        Node(int value, int frequency) {
            this.value = value;
            this.frequency = frequency;
        }

        private boolean isLeaf() {
            return left == null && right == null;
        }
    }
    public Huffman_Tree(Node root) {
        this.root = root;
    }

    public Huffman_Tree buildTree (Map<Integer, Integer> table) {
        List<Node> nodes = new ArrayList<>();

        for (int value : table.keySet()) {
            Node node = new Node(value, table.get(value));
            nodes.add(node);
        }

        while (nodes.size() > 1) {
            nodes.sort(Comparator.comparingInt(node -> node.frequency));
            Node left = nodes.remove(0);
            Node right = nodes.remove(0);
            Node interval = new Node(999999999, left.frequency + right.frequency);
            interval.left = left;
            interval.right = right;
            nodes.add(interval);
        }
        return new Huffman_Tree(nodes.get(0));
    }

    public static Map<Integer, String> generating(Huffman_Tree tree) {
        Map<Integer, String> code_map = new HashMap<>();
        generateCode(tree.root, "", code_map);
        return code_map;
    }

    private static void generateCode(Node node, String code, Map<Integer, String> code_map) {
        if (node.isLeaf()) {
            code_map.put(node.value, code);
            return;
        }

        if (node.left != null) {
            generateCode(node.left, code + "0", code_map);
        }
        if (node.right != null) {
            generateCode(node.right, code + "1", code_map);
        }
    }

    public static double avgLength(Map<Integer, Integer> table, Map<Integer, String> code_map) {
        double totalLength = 0.0;
        int totalFrequency = 0;

        for (int value : table.keySet()) {
            int frequency = table.get(value);
            String code = code_map.get(value);
            totalLength += frequency * code.length();
            totalFrequency += frequency;
        }

        return totalLength / totalFrequency;
    }

}