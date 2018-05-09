import java.util.Collections;
import java.util.HashMap;

public class Dictionary {
	
	public HashMap<String, BNode> list = new HashMap<String, BNode>();
	
	public int duplicateCount = 0; // Removed duplicate count

	// Maximum word
	public int indexMaxWord;
	public int maxWordCount = 0;
	
	// Use for collect list of max duplicate word
	public HashMap<String, BNode> duplicate = new HashMap<String, BNode>();
	
	// Function add word
	public void Add (String input)
	{
		BNode node = new BNode(input);
		// Check 
		if (list.containsKey(node.word.toLowerCase()))
		{
			// HashMap contain the key
			// Grab the node and add meaning
			BNode existsNode = list.get(node.word);
			existsNode.add(node.meaning);
		}
		else 
		{
			// HashMap not contain the key
			// Use word as key
			// Then add node to HashMap
			list.put(node.word, node);
		}
	}

	// Function search and print word
	public void SearchAndPrintWord (String _word)
	{
		BNode key = new BNode(_word.toLowerCase());
		
		// Check word as key in HashMap
		if (list.containsKey(key.word)) 
		{
			// Found word in dictionary
			// Grab the word node and then print it
			Print(list.get(key.word));
		}
		else
		{
			// Not found
			System.out.println(_word + " not found");
		}
	}
	
	// Find maximum word
	public BNode FindMaximumWord ()
	{
		// Define empty node to be max node
		BNode node = new BNode("");
		for (String key : list.keySet())
		{
			BNode item = list.get(key);
			
			// If max node is empty set the node to be max node 
			if (node.word == "") node = item; 
				
			// Repalce old maximum word with new word
			if (item.meaning.size() > node.meaning.size())
				node = item;
		}
		return node;
	}
	
	// Print node
	public void Print (BNode node)
	{
		node.Print();
	}
	
}
