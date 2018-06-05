
public class KruskalWithWarShall {
	
	int[][] distance;
	
	
	public KruskalWithWarShall (int vertexCount, int graph[][]) {
		distance = new int[vertexCount][vertexCount];
		
		// Set distance to itself to 0
		for (int i = 0; i < vertexCount; i++)
			distance[i][i] = 0;
		
		// 
		for (int i = 0; i < vertexCount; i++) {
			for (int j = 0; j < vertexCount; j++) {
				// Check vertext i can go to j directly
				if (graph[i][j] != 0)
					 // Set distance
					distance[i][j] = graph[i][j];
				else 
					// Vertext i can't go to j directly
					// Set distance to infinity
					distance[i][j] = -1; 
			}
		}
		
		for (int k = 0; k < vertexCount; k++) {
			for (int i = 0; i < vertexCount; i++) {
				for (int j = 0; j < vertexCount; j++) {
					if (
							// distance is infinity
							// i->k->j is shorter than i -> j
							(distance[i][j] <= -1 && (distance[i][j] < distance[i][k] + distance[k][j]))
							||
							// distance is not infinity
							// i->k->j is shorter than i -> j
							(distance[i][j] > -1 && (distance[i][j] > distance[i][k] + distance[k][j]))
						)
						// Set distance i to j by i -> k -> j
						distance[i][j] = distance[i][k] + distance[k][j];
				}
			}
		}
		
	}

}
