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

		CreateEdgeSet(graph, edgeSet);
//		PrintEdgeSet(edgeSet);
		Kruskal kruskal = new Kruskal(graph, edgeSet);
		PrintTree(kruskal.tree);
	}
	
	public static void CreateEdgeSet (int graph[][], PriorityQueue<Edge> edgeSet)	{
		for (int i = 0; i < graph.length; i++) {
			for (int j = 0; j < graph[i].length; j++) {
				if (graph[i][j] != 0) {
					Edge e = new Edge( i, j, graph[i][j]);
					edgeSet.add(e);
				}
			}
		}
	}
	
	
	
	public static boolean Warshall (int graph[][], ArrayList<Edge> tree) {
		
		int tempGraph[][] = graph;
		for (int i = 0; i < graph.length; i++) 
			for(int j = 0; j < graph[i].length; j++)
				graph[i][j] = 0;
		
		for (int i = 0; i < tree.size(); i++) {
			
		}
		
		
		return false;
	}
	
	public static boolean Traversal () {
		
		return false;
	}
	
	public static String GetNodeName (int node) {
		if (node == 0)
			return "A";
		else if (node == 1)
			return "B";
		else if (node == 2)
			return "C";
		else if (node == 3)
			return "D";
		else if (node == 4)
			return "E";
		else if (node == 5)
			return "F";
		return "G";
	}
	
	public static void PrintTree (ArrayList<Edge> tree) {
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
