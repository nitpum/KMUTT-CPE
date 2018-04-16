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
	
	// Function add word
	public void Add (String input)
	{
		BNode node = new BNode(input);
		if (list.contains(node))
		{
			TreeSet<BNode> data = (TreeSet<BNode>) list.subSet(node, true, node, true);
			if (!data.first().meaning.contains(node.meaning.get(0)))
				data.first().meaning.addAll(node.meaning);
		}
		else
		{
			list.add(node);
		}
	}

	// Function search and print word
	public void SearchAndPrintWord (String _word)
	{
		BNode key = new BNode(_word);
		// Search
		
		if (list.contains(key)) // Found word in dictionary
		{
			TreeSet<BNode> node = (TreeSet<BNode>)list.subSet(key, true, key, true);
			System.out.println("found " + _word);
			Print(node);
		}
		else
		{
			System.out.println(_word + " not found");
		}
	}
	
	// Find maximum word
	public BNode FindMaximumWord ()
	{
		BNode node = list.first();
		for (BNode item : list)
		{
			// Repalce old maximum word with new word
			if (item.meaning.size() > node.meaning.size())
				node = item;
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

	public void Print (TreeSet<BNode> _list)
	{
		for (BNode item : _list)
		{
			item.Print();
		}
	}
	
}
