import java.util.ArrayList;

public class BNode implements Comparable<BNode> {
	
	String word;
	ArrayList<String> meaning = new ArrayList<String>();
	
	public BNode (String input)
	{
		word = input.trim().replaceAll("\\s+", " ");
		String[] split = input.trim().split(",");
		// Check input
		if (split.length <= 1) // Input contain only word
		{
			// Remove space
			word = input.trim();
			word = word.replaceAll("\\s+"," ");
		}
		else // Split word and meaning
		{
			// Remove space
			word = split[0].trim();
			meaning.add("(" + split[2].trim() + ")" + split[1].trim()); // Combined type and meaning string
		}
	}
	
	// Add meaning
	public void add (String _meaning)
	{
		meaning.add(_meaning);
	}
	
	// Compare ignore case, trim and remove undesired space
	@Override
	public int compareTo (BNode target)
	{
		return (int) word.trim().replaceAll("\\s+", " ").compareToIgnoreCase(target.word.trim().replaceAll("\\s+", " "));
	}
	
	// Print node
	public void Print ()
	{
		for (int i = 0; i < meaning.size(); i++)
		{
			if (i == 0) // Show the word only at first item of list
				System.out.format("%-20s %-2s %-20s\n", word, i + 1, meaning.get(i));
			else 
				System.out.format("%-20s %-2s %-20s\n", "", i + 1, meaning.get(i));
		}
	}

}
