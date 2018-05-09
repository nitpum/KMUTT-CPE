import java.util.ArrayList;

public class BNode implements Comparable<BNode> {
	
	String word;
	ArrayList<String> meaning = new ArrayList<String>();
	
	public BNode (String input)
	{
		String[] split = input.toLowerCase().trim().split(",");
		// Check input
		if (split.length <= 1) // Input contain only word
		{
			// Remove space
			word = input.trim().replaceAll("\\s+"," ");
		}
		else // Split word, type and meaning
		{
			// Remove space
			word = split[0].trim().replaceAll("\\s+"," ");
			meaning.add("(" + split[2].trim() + ")" + split[1].trim()); // Combined type and meaing string
		}
	}
	
	// Add new meaning
	public void add (String _meaning)
	{
		 // Add only new meaning
		if(!meaning.contains(_meaning))
			meaning.add(_meaning);
	}
	
	// Add meaning from the list to Bnode's meaning list
	public void add (ArrayList<String> list)
	{
		for (String _meaning : list)
		{
			add(_meaning);
		}
	}
	
	// Compare ignore case, trim and remove undesired space
	@Override
	public int compareTo (BNode target)
	{
		return (int) word.trim().replaceAll("\\s+", " ").compareToIgnoreCase(target.word.trim().replaceAll("\\s+", " "));
	}
	
	// Print word
	public void Print ()
	{
		for (int i = 0; i < meaning.size(); i++)
		{
			if (i == 0) // Only show the word at first index
				System.out.format("%-20s %-2s %-20s\n", word, i + 1, meaning.get(i));
			else 
				System.out.format("%-20s %-2s %-20s\n", "", i + 1, meaning.get(i));
		}
	}

}
