import java.util.ArrayList;
import java.util.Collections;
import java.util.TreeSet;

public class Dictionary {
	
	public TreeSet<BNode> list = new TreeSet<BNode>();
	
	public int duplicateCount = 0; // Removed duplicate count

	// Maximum word
	public int indexMaxWord;
	public int maxWordCount = 0;
	
	// Use for collect list of max duplicate word
	public TreeSet<BNode> duplicate = new TreeSet<BNode>();
	
	// Function add word to dictionary
	public void Add (String input)
	{
		BNode node = new BNode(input);
		// Check word is exists in dictionary
		if (list.contains(node))
		{
			// Grab node from dictionary
			TreeSet<BNode> data = (TreeSet<BNode>) list.subSet(node, true, node, true);
			// Add new meaning to the ndoe
			if (!data.first().meaning.contains(node.meaning.get(0)))
				data.first().meaning.addAll(node.meaning);
		}
		else
		{
			// Dictionary don't contain the word
			// Add word to dictionary
			list.add(node);
		}
	}

	// Function search and print word
	public void SearchAndPrintWord (String _word)
	{
		BNode key = new BNode(_word);

		// Check key is HashMap
		if (list.contains(key)) // Found word in dictionary
		{
			// Grab the node from dictionary
			TreeSet<BNode> node = (TreeSet<BNode>)list.subSet(key, true, key, true);
			System.out.println("found " + _word);
			Print(node); // Print the node
		}
		else
		{
			// Word not found
			System.out.println(_word + " not found");
		}
	}
	
	// Find maximum word
	public BNode FindMaximumWord ()
	{
		// Set first to be maximum word
		BNode node = list.first();
		for (BNode item : list)
		{
			// Check if next node's meaning count is more than current maxiumn's meaning count
			if (item.meaning.size() > node.meaning.size())
				node = item;// Repalce old maximum word with new word
		}
		return node;
	}
	
	// Print dict from start index to end int
	public void Print ()
	{
		for (BNode item : list)
		{
			item.Print();
		}
	}

	// Print BNode from list
	public void Print (TreeSet<BNode> _list)
	{
		for (BNode item : _list)
		{
			item.Print();
		}
	}
	
}
