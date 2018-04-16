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
		if (list.containsKey(node.word))
		{
			BNode existsNode = list.get(node.word);
			existsNode.add(node.meaning);
		}
		else
		{
			// Use word as key
			list.put(node.word, node);
		}
	}

	// Function search and print word
	public void SearchAndPrintWord (String _word)
	{
		BNode key = new BNode(_word.toLowerCase());
		
		// Search
		if (list.containsKey(key.word)) // Found word in dictionary
		{
			// Loop find word
			Print(list.get(key.word));
		}
		else
		{
			System.out.println(_word + " not found");
		}
	}
	
	// Find maximum word
	public BNode FindMaximumWord ()
	{
		BNode node = new BNode("");
		for (String key : list.keySet())
		{
			BNode item = list.get(key);
			
			// Set first max node
			if (node.word == "") node = item; 
				
			// Repalce old maximum word with new word
			if (item.meaning.size() > node.meaning.size())
				node = item;
		}
		return node;
	}
	
	// Print dict from start index to end int
//	public void Print ()
//	{
//		for (BNode item : list)
//		{
//			item.Print();
//		}
//	}

	public void Print (BNode node)
	{
		node.Print();
	}
	
}
