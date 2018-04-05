import java.util.ArrayList;

public class BNode implements Comparable<BNode> {
	
	String word;
	ArrayList<String> meaning = new ArrayList<String>();
	
	public BNode (String input)
	{
		word = input.trim().replaceAll("\\s+", " ");
		String[] split = input.trim().split(",");
		if (split.length <= 1) // Construct only word
		{
			word = input.trim();
			word = word.replaceAll("\\s+"," ");
		}
		else
		{
			word = split[0].trim();
			meaning.add("(" + split[2].trim() + ")" + split[1].trim());
		}
	}
	
	public void add (String _meaning)
	{
		meaning.add(_meaning);
	}
	
	@Override
	public int compareTo (BNode target)
	{
		return (int) word.trim().replaceAll("\\s+", " ").compareToIgnoreCase(target.word.trim().replaceAll("\\s+", " "));
	}
	
//	public boolean compareAll (BNode a)
//	{
//		if (	word.trim().replaceAll("\\s+", " ").equalsIgnoreCase(a.word.trim().replaceAll("\\s+", " ")) 
//				&& meaning.equalsIgnoreCase(a.meaning) 
//				&& type.equalsIgnoreCase(a.type)
//			)
//			return true;
//		return false;
//	}
	
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
