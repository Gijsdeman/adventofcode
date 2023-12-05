import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;

class Node {
    public HashMap<String, Node> children;
    public Node parent;

    public String name;
    public int value;

    public Node(String name) {
        this.name = name;
        this.parent = null;
        this.children = new HashMap<>();
    }

    public Node(String name, int value) {
        this.name = name;
        this.value = value;
        this.children = new HashMap<>();
    }

    public int calculateValue() {
        if (!this.children.isEmpty()) {
            for (HashMap.Entry<String, Node> entry : this.children.entrySet()) {
                this.value += entry.getValue().calculateValue();
            }
        }
        return this.value;
    }
}

public class day7 {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("2022/day7.input");
        Scanner scanner = new Scanner(file);

        // Remove initial line
        scanner.nextLine();
        Node root = new Node("/");
        Node currentNode = root;
        boolean skipRead = false;
        String line = "";

        // Create tree structure from files
        while (scanner.hasNextLine()) {
            if (!skipRead) line = scanner.nextLine();
            skipRead = false;

            if (line.startsWith("$ cd")) {
                if (line.substring(5).equals("..")) {
                    currentNode = currentNode.parent;
                } else {
                    String folderName = line.substring(5);
                    currentNode = currentNode.children.get(folderName);
                }
            } else {
                while(scanner.hasNextLine()) {
                    line = scanner.nextLine();
                    if (line.startsWith("$")) {
                        skipRead = true;
                        break;
                    }

                    Node childNode;
                    String name;
                    if (line.startsWith("dir")) {
                        name = line.substring(4);
                        childNode = new Node(name);
                    } else {
                        String[] lsLine = line.split(" ");
                        name = lsLine[1];
                        childNode = new Node(name, Integer.parseInt(lsLine[0]));
                    }
                    currentNode.children.put(name, childNode);
                    childNode.parent = currentNode;
                }
            }
        }

        // Calculate values of each directory
        root.calculateValue();

        // BFS to calculate total value
        LinkedList<Node> queue = new LinkedList<>();
        for (HashMap.Entry<String, Node> childEntry : root.children.entrySet()) {
            queue.add(childEntry.getValue());
        }
        int totalValue = 0;

        while(!queue.isEmpty()) {
            Node node = queue.pop();
            if (!node.children.isEmpty()) {
                if (node.value < 100000) totalValue += node.value;
                for (HashMap.Entry<String, Node> childEntry : node.children.entrySet()) {
                    Node child = childEntry.getValue();
                    queue.push(child);
                }
            }
        }

        System.out.println("Part 1");
        System.out.println(totalValue);

        int totalSpace = 70000000;
        int usedSpace = root.value;
        int unusedSpace = totalSpace - usedSpace;
        int toBeFreedSpace = 30000000 - unusedSpace;

        queue = new LinkedList<>();
        queue.add(root);
        int minDirectory = Integer.MAX_VALUE;

        while(!queue.isEmpty()) {
            Node node = queue.pop();
            if (!node.children.isEmpty()) {
                if (node.value >= toBeFreedSpace) minDirectory = Math.min(minDirectory, node.value);
                for (HashMap.Entry<String, Node> childEntry : node.children.entrySet()) {
                    Node child = childEntry.getValue();
                    queue.push(child);
                }
            }
        }

        System.out.println("Part 2");
        System.out.println(minDirectory);

    }
}