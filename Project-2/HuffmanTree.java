import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class HuffmanTree {
    private HuffmanNode root;
    private static class HuffmanNode {
        int value;           
        int frequency;     
        HuffmanNode left;   
        HuffmanNode right;  

        HuffmanNode(int value, int frequency) {
            this.value = value;
            this.frequency = frequency;
        }

        private boolean isLeaf() {
            return left == null && right == null;
        }
    }
    public HuffmanTree(HuffmanNode root) {
        this.root = root;
    }

    public HuffmanTree buildHuffmanTree (Map<Integer, Integer> frequencyTable) {
        List<HuffmanNode> nodes = new ArrayList<>();

        for (int value : frequencyTable.keySet()) {
            HuffmanNode node = new HuffmanNode(value, frequencyTable.get(value));
            nodes.add(node);
        }

        while (nodes.size() > 1) {
            nodes.sort(Comparator.comparingInt(node -> node.frequency));
            HuffmanNode left = nodes.remove(0);
            HuffmanNode right = nodes.remove(0);
            HuffmanNode interval = new HuffmanNode(999999999, left.frequency + right.frequency);
            interval.left = left;
            interval.right = right;
            nodes.add(interval);
        }
        return new HuffmanTree(nodes.get(0));
    }

    public static Map<Integer, String> generating(HuffmanTree tree) {
        Map<Integer, String> huffmanCodes = new HashMap<>();
        generateCode(tree.root, "", huffmanCodes);
        return huffmanCodes;
    }

    private static void generateCode(HuffmanNode node, String code, Map<Integer, String> huffmanCodes) {
        if (node.isLeaf()) {
            huffmanCodes.put(node.value, code);
            return;
        }

        if (node.left != null) {
            generateCode(node.left, code + "0", huffmanCodes);
        }
        if (node.right != null) {
            generateCode(node.right, code + "1", huffmanCodes);
        }
    }

    public static double avgLength(Map<Integer, Integer> frequencyTable, Map<Integer, String> huffmanCodes) {
        double totalLength = 0.0;
        int totalFrequency = 0;

        for (int value : frequencyTable.keySet()) {
            int frequency = frequencyTable.get(value);
            String code = huffmanCodes.get(value);
            totalLength += frequency * code.length();
            totalFrequency += frequency;
        }

        return totalLength / totalFrequency;
    }

}