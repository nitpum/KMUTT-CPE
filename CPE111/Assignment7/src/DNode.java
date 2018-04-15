
public class DNode implements Comparable<DNode> {

	String word;
	String meaning;
	String type;	
	
	public DNode (String input)
	{
		String[] split = input.trim().split(",");
		if (split.length <= 1) // Input contain only word
		{
			word = input.trim();
			word = word.replaceAll("\\s+"," ");
		}
		else // Input contain word, meaning and type
		{
			word = split[0].trim();
			meaning = split[1].trim();
			type = split[2].trim();
		}
	}	
	
	// Compare word with ignore case, tirm and remove space
	@Override
	public int compareTo (DNode target)
	{
		return (int) word.trim().replaceAll("\\s+", " ").compareToIgnoreCase(target.word.trim().replaceAll("\\s+", " "));
	}
	
	// Compare word, meaing and type with ignore case, trim and remove space
	public boolean compareAll (DNode a)
	{
		if (	word.trim().replaceAll("\\s+", " ").equalsIgnoreCase(a.word.trim().replaceAll("\\s+", " ")) 
				&& meaning.equalsIgnoreCase(a.meaning) 
				&& type.equalsIgnoreCase(a.type)
			)
			return true;
		return false;
	}
	
	// Print word
	public void Print ()
	{
		System.out.println(word + "	" + meaning + "(" + type + ")");
	}
	
	// Print word with index
	public void Print (int index)
	{
		System.out.format("%2d) %-20s %-20s\n", index, word, meaning + "(" + type +")");
	}
	
}
