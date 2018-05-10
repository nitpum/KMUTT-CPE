
public class Edge implements Comparable {

	public int node1, node2;
	public int weight;
	
	public Edge (int n1, int n2, int weight) {
		node1 = n1;
		node2 = n2;
		this.weight = weight;
	}

	@Override
	public int compareTo(Object target) {
		return this.weight - ((Edge)target).weight;
	}
	
	public boolean sameEdge (Edge target) {
		if ((node1 == target.node1 && node2 == target.node2) || (node1 == target.node2 && node2 == target.node1))
			return true;
		return false;
	}
	
	public boolean sameNode (Edge target) {
		if (node1 == target.node1 || node1 == target.node2 || node2 == target.node1 || node2 == target.node2)
			return true;
		return false;
	}
	
}
