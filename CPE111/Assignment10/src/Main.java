import java.util.ArrayList;
import java.util.PriorityQueue;

public class Main {
	
	static int graph[][] = new int[][] {
		{ 0, 2, 4, 1, 0, 0, 0 },
		{ 2, 0, 0, 3,10, 0, 0 },
		{ 4, 0, 0, 2, 0, 5, 0 },
		{ 1, 3, 2, 0, 7, 8, 4 },
		{ 0,10, 0, 7, 0, 0, 6 },
		{ 0, 0, 5, 8, 0, 0, 1 },
		{ 0, 0, 0, 4, 6, 1, 0 } };
		
	static PriorityQueue<Edge> edgeSet = new PriorityQueue<Edge>();

	public static void main(String[] args) {
		createEdgeSet(graph, edgeSet);
		// Create kruskal instance
		Kruskal kruskal = new Kruskal(graph, edgeSet);
		// Print kruskal result
		System.out.println("Kruskal: ");
		printTree(kruskal.tree);
	}
	
	// Create edge set from graph
	public static void createEdgeSet (int graph[][], PriorityQueue<Edge> edgeSet)	{
		for (int i = 0; i < graph.length; i++) {
			for (int j = 0; j < graph[i].length; j++) {
				if (graph[i][j] != 0) {
					Edge e = new Edge( i, j, graph[i][j]);
					edgeSet.add(e);
				}
			}
		}
	}
	
	// Get node name by ASIIC
	public static String GetNodeName (int node) {
		return String.format("%c", node + 'a');
	}
	
	// Print edge tree and weight
	public static void printTree (ArrayList<Edge> tree) {
		for (int i = 0; i < tree.size(); i++) {
			Edge edge = tree.get(i);
			System.out.println(GetNodeName(edge.node1) + GetNodeName(edge.node2) + " : " + edge.weight);
		}
	}
	
	public static void PrintEdgeSet (PriorityQueue<Edge> edgeset) {
		for (Edge e : edgeset) {
			System.out.println(e.node1 + " > " + e.node2 + " : " + e.weight);
		}
	}

}
