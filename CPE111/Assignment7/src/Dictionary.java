import java.util.ArrayList;
import java.util.Collections;

public class Dictionary {
	
	public ArrayList<DNode> list = new ArrayList<DNode>();
	
	public int duplicateCount = 0; // Removed duplicate count

	// Maximum word
	public int indexMaxWord;
	public int maxWordCount = 0;
	
	// Use for collect list of max duplicate word
	public Dictionary maxWordList;
	
	public DNode Get (int index)
	{
		return list.get(index);
	}
	
	public void Add (DNode node)
	{
		list.add(node);
	}
	
	public void Sort ()
	{
		Collections.sort(list);
	}
	
	public void SearchWord (String _word, int[] _start, int[] _end)
	{
		DNode key = new DNode(_word);
		// Search
		int index = Collections.binarySearch(list, key);
		int endIndex = -1;
		// Check found word
		if (index >= 0) {
			// Check word before
			for (int i = index - 1; i >= 0; i--) 
			{
				if (list.get(i).compareTo(key) == 0) index = i;
			}
			// Find end index
			endIndex = index; // Set end index
			for (int i = index + 1; i < list.size(); i++) 
			{
				if (list.get(i).compareTo(key) == 0) endIndex++; // Move end index
			}
			// Return data
			_start[0] = index; // start index
			_end[0] = endIndex; // end index
		}
		else
		{
			_start[0] = -1;
			_end[0] = -1;
		}
		
	}
	
	// Overload
	public void Print (int _start, int _end)
	{
		Print(_start, _end, false);
	}
	
	// Print dict from start index to end int
	public void Print (int _start, int _end, boolean realIndex)
	{
		for (int i = _start; i <= _end && i < list.size(); i++) 
		{
			DNode dict = list.get(i);
			if (realIndex) // Print real index
				dict.Print(i);
			else dict.Print( (_end - _start + 1) - (_end - i)  ); // Print order index
		}
	}	
	
	public int FindMaximumWord ()
	{
		maxWordCount = 0; // Reset count
		
		// Word Counter
		int wordCounter = 0;
		int index = 0;
		String lastWord = "";
		for (int i = 0; i < list.size(); i++)
		{
			DNode dict = list.get(i);
			
			if (dict.compareTo(new DNode(lastWord)) == 0) // Same last word count incease
			{
				wordCounter++;
			}
			else // Found new wrod
			{
				// If last word is more than maximum word then set it to maximum word
				if (wordCounter > maxWordCount)
				{
					indexMaxWord = index;
					maxWordCount = wordCounter;
				}
				
				// Count new word
				index = i;
				wordCounter = 1;
			}
			lastWord = dict.word; // Set last word
		}
		return indexMaxWord;
	}
	
	public void RemoveDuplicate ()
	{
		maxWordCount = 0; // Reset max duplicate count
		maxWordList = new Dictionary(); // Reset list
		
		// Max word counter
		int dCount = 0;
		
		for (int i = list.size() - 1; i >= 0; i--) {			
			DNode word = list.get(i);
			// Check word, meaning and type if match then remove
			for (int j = i - 1; j >= 0 && word.compareAll(list.get(j)) == true; j--) 
			{				
				list.remove(j); // Remove duplicate word
				duplicateCount++; // Add removed duplicate count
			}
		}
		
		if (dCount > maxWordCount) maxWordCount = dCount;
	}
	
	public void PrintMaxWordList ()
	{
		if (maxWordList.list.size() <= 0) return;
		// Print list of max duplicate word
		for (int i = 0; i < maxWordList.list.size(); i++) {
			maxWordList.list.get(i).Print(i + 1);
		}
	}
	
	// Print all data in dictionary
	public void Print ()
	{
		for (int i = 0; i < list.size(); i++)
		{
			DNode dict = list.get(i);
			dict.Print(i);
		}
	}

}
