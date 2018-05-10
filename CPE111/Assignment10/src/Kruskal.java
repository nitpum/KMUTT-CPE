import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;

public class Kruskal {
	
	ArrayList<Edge> tree = new ArrayList<Edge>();
	HashMap<Integer, Integer> rootMap = new HashMap<Integer, Integer>();
	HashMap<Integer, Integer> childCount = new HashMap<Integer, Integer>();
	
	public Kruskal (int graph[][], PriorityQueue<Edge> edgeSet) {
		
		// Initialized root map and child count
		for (int i = 0; i < graph.length; i++) {
			rootMap.put(new Integer(i), new Integer(i)); // value is same as key
			childCount.put(new Integer(i), new Integer(0)); // value is 0
		}
		// Get edge from edge set
		// And then check if edge in tree not add edge to edge
		Edge edge;
		while ((edge = edgeSet.poll()) != null) {
			boolean added = false;
			// Check tree contain edge or not
			for (int i = 0; i < tree.size(); i++) {
				if (edge.sameEdge(tree.get(i)))
					added = true; // Tree contain this edge
			}
			// Tree not contain the edge then add it to tree
			if (added == false)
				addEdgeTree(tree, edge);
		}
	}
	
	// Check edge before add to tree
	public void addEdgeTree (ArrayList<Edge> tree, Edge edge) {
		// Before add to tree check their root
		// Check node1 root and node2 root
		// If they are same edge it mean graph will loop
		if (getRoot(edge.node1) == getRoot(edge.node2))
			return; // Cancel this function
		else if (getRoot(edge.node1) > getRoot(edge.node2))
			setRoot(edge.node1, edge.node2);
		else 
			setRoot(edge.node2, edge.node1);
		// Add edge to tree
		tree.add(edge);
	}
	
	// Set new root to target node and update child count
	public void setRoot (int root, int target) {
		// Update new root to target
		rootMap.put(new Integer(target), new Integer(root));
		// Update child count of root node and add child count of target node to root node
		childCount.put(new Integer(root), childCount.get(new Integer(root)) + 1 + childCount.get(new Integer(target)));
	}
	
	// Get node's root from root map
	public int getRoot (int node) {
		// root is node itself
		if (rootMap.get(new Integer(node)) == node)
			return node;
		// root is the other node 
		// Get node root from root map then use in getRoot function
		return getRoot(rootMap.get(new Integer(node)));
	}
	
}
