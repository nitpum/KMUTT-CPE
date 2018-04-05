import java.util.ArrayList;

public class BNode implements Comparable<BNode> {
	
	String word;
	ArrayList<String> meaning;
	
	public BNode (String _word)
	{
		word = _word;
		meaning = new ArrayList<String>();
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
		System.out.println(word + "	" + meaning);
	}
	
	public void Print (int index)
	{
		System.out.format("%2d) %-20s %-20s\n", index, word, meaning);
	}

}
