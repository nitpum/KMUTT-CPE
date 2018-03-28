
public class DNode implements Comparable<DNode> {

	String word;
	String meaning;
	String type;	
	
	public DNode (String input)
	{
		String[] split = input.trim().split(",");
		if (split.length <= 1) // Construct only word
		{
			word = input.trim();
			word = word.replaceAll("\\s+"," ");
		}
		else
		{
			word = split[0].trim();
			meaning = split[1].trim();
			type = split[2].trim();
		}
	}	
	
	// Overload equalWord
	public boolean equalWord (DNode _target)
	{
		return equalWord(_target.word);
	}
	
	// Check between a and b word is equalIgnoreCase, trim and remove middle space
	public boolean equalWord (String _target)
	{
		return word.trim().replaceAll("\\s+", " ").toLowerCase().equalsIgnoreCase(_target.trim().replaceAll("\\s+", " ").toLowerCase());
	}
	
	@Override
	public int compareTo (DNode a)
	{
		return (int) word.trim().replaceAll("\\s+", " ").compareToIgnoreCase(a.word.trim().replaceAll("\\s+", " "));
	}
	
	public boolean compareAll (DNode a)
	{
		if (	word.trim().replaceAll("\\s+", " ").toLowerCase().compareToIgnoreCase(a.word.trim().replaceAll("\\s+", " ").toLowerCase()) == 0 
				&& meaning.compareToIgnoreCase(a.meaning) == 0 
				&& type.compareToIgnoreCase(a.type) == 0
			)
			return true;
		return false;
	}
	
	public void Print ()
	{
		System.out.println(word + "	" + meaning + "(" + type + ")");
	}
	
	public void Print (int index)
	{
		System.out.format("%2d) %-20s %-20s\n", index, word, meaning + "(" + type +")");
	}
	
}
