import java.util.ArrayList;
import java.util.Comparator;
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
            HuffmanNode mergedNode = new HuffmanNode(-1, left.frequency + right.frequency);
            mergedNode.left = left;
            mergedNode.right = right;
            nodes.add(mergedNode);
        }
        return new HuffmanTree(nodes.get(0));
    }
}