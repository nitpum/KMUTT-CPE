
public class Node implements Comparable<Node> {

	int f;
	
	public Node (int _f) {
		f = _f;
	}
	
	@Override
	public int compareTo (Node target) {
		return f - target.f;
	}
	
}
