import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;

public class Kruskal {
	
	ArrayList<Edge> tree = new ArrayList<Edge>();
	static PriorityQueue<Edge> edgeSet = new PriorityQueue<Edge>();
	HashMap<Integer, Integer> rootMap = new HashMap<Integer, Integer>();
	HashMap<Integer, Integer> childCount = new HashMap<Integer, Integer>();
	
	public Kruskal (int graph[][], PriorityQueue<Edge> edgeSet) {		
		this.edgeSet = edgeSet; 
		// Initialized root map
		for (int i = 0; i < graph.length; i++) {
			rootMap.put(new Integer(i), new Integer(i));
			childCount.put(new Integer(i), new Integer(0));
		}
		Edge edge;
		while ((edge = this.edgeSet.poll()) != null) {
			boolean added = false;
			for (int i = 0; i < tree.size(); i++) {
				if (edge.sameEdge(tree.get(i))) {
					added = true;
				}
			}
			if (added == false)
				AddToTree(tree, edge);
		}
	}
	
	public void AddToTree (ArrayList<Edge> tree, Edge edge) {
		if (findRoot(edge.node1) == findRoot(edge.node2))
			return;
		else if (findRoot(edge.node1) > findRoot(edge.node2))
			SetRoot(edge.node1, edge.node2);
		else 
			SetRoot(edge.node2, edge.node1);
		tree.add(edge);
	}
	
	public void SetRoot (int root, int target) {
		rootMap.put(new Integer(target), new Integer(root));
		childCount.put(new Integer(root), childCount.get(new Integer(root)) + 1 + childCount.get(new Integer(target)));
	}
	
	public ArrayList<Edge> getTree () {
		return tree;
	}
	
	public int findRoot (int node) {
		if (rootMap.get(new Integer(node)) == node)
			return node;
		return findRoot(rootMap.get(new Integer(node)));
	}
	
}
