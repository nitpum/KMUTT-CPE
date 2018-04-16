import java.util.ArrayList;

public class BNode implements Comparable<BNode> {
	
	String word;
	ArrayList<String> meaning = new ArrayList<String>();
	
	public BNode (String input)
	{
//		word = input.trim().replaceAll("\\s+", " ");
		String[] split = input.trim().split(",");
		// Check input
		if (split.length <= 1) // Input contain only word
		{
			word = input.trim().replaceAll("\\s+"," ");
		}
		else // Split word and meaning
		{
			word = split[0].trim().replaceAll("\\s+"," ");
			meaning.add("(" + split[2].trim() + ")" + split[1].trim());
		}
	}
	
	// Add meaning
	public void add (String _meaning)
	{
		if(!meaning.contains(_meaning)) // Not add duplicate meaning
			meaning.add(_meaning);
	}
	
	// Add meaning from list
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
			if (i == 0)
				System.out.format("%-20s %-2s %-20s\n", word, i + 1, meaning.get(i));
			else 
				System.out.format("%-20s %-2s %-20s\n", "", i + 1, meaning.get(i));
		}
	}

}
