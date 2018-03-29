
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
	
	@Override
	public int compareTo (DNode target)
	{
		return (int) word.trim().replaceAll("\\s+", " ").compareToIgnoreCase(target.word.trim().replaceAll("\\s+", " "));
	}
	
	public boolean compareAll (DNode a)
	{
		if (	word.trim().replaceAll("\\s+", " ").equalsIgnoreCase(a.word.trim().replaceAll("\\s+", " ")) 
				&& meaning.equalsIgnoreCase(a.meaning) 
				&& type.equalsIgnoreCase(a.type)
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
