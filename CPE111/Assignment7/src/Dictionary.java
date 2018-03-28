import java.util.ArrayList;
import java.util.Collections;

public class Dictionary {
	
	public ArrayList<DNode> list = new ArrayList<DNode>();
	
	public int duplicateCount = 0; // Removed duplicate count
	public String maxWord; // Most duplicate word
	public int maxWordCount = 0; // Most duplicate word count
	
	// Use for collect list of max duplicate word
	public Dictionary maxWordList;
	
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
		// Make node for search
		DNode node = new DNode(_word);
		// Search
		int index = Collections.binarySearch(list, node);
		System.out.println(index);
		int endIndex = -1;
		// Check found word
		if (index >= 0) {
			endIndex = index; // Set end index
			for (int i = index + 1; i < list.size(); i++) {
				if (list.get(i).equalWord(node)) {
					endIndex++; // Move end index
				}
			}
			// Return data
			_start[0] = index; // start index
			_end[0] = endIndex; // end index
		}
		else
		{
			System.out.println(node.word + " not found");
		}
		
	}
	
	public void Print (int _start, int _end)
	{
		Print(_start, _end, false);
	}
	
	public void Print (int _start, int _end, boolean realIndex)
	{
		for (int i = _start; i <= _end && i < list.size(); i++) {
			DNode dict = list.get(i);
			if (realIndex)
				dict.Print(i);
			else dict.Print( (_end - _start + 1) - (_end - i)  );
		}
	}	
	
	public void RemoveDuplicate ()
	{
		for (int i = 0; i < list.size(); i++)
		{
			DNode word = list.get(i);
			for (int j = i + 1; j < list.size() && word.compareAll(list.get(j)); j++)
			{
//				list.remove(j);
				duplicateCount++;
			}
		}
	}
	
//	public void RemoveDuplicate ()
//	{
//		maxWordCount = 0; // Reset max duplicate count
//		maxWordList = new Dictionary(); // Reset list
//		
//		// Max word counter
//		int dCount = 0;
//		String dWord = list.get(0).word;
//		Dictionary tmpDup = new Dictionary();
//		
//		for (int i = list.size() - 1; i >= 0; i--) {			
//			DNode word = list.get(i);
//			
//			// Counting duplicate word
////			if (word.equalWord(dWord))
////			{
////				// Add Dnode to temp list
////				tmpDup.list.add(word);
////				dCount++;
////			}
////			else 
////			{
////				// Set new max count
////				if (dCount > maxWordCount) 
////				{
////					maxWordList.list.clear(); // Clear list
////					// Copy list item
////					for (DNode item : tmpDup.list) {
////						maxWordList.Add(item);
////					}
//////					System.out.println(dWord + "  " + dCount);A
////					// Set new max word
////					maxWordCount = dCount;
////					maxWord = dWord;
////				}
////				// Reset counter
////				tmpDup.list.clear();
////				dCount = 0;
////				dWord = word.word;
////				
////				// Add current
////				tmpDup.list.add(word);
////				dCount++;
////			}
//			// Check word, meaning and type if match then remove
//			if (word.word.equalsIgnoreCase("gamine"))
//				System.out.println(i + " > gamine" );
//			for (int j = i - 1; j >= 0 && word.compareAll(list.get(j)) == true; j--) {
//				if (list.get(j).word.equalsIgnoreCase("gamine"))
//					System.out.println(j + " > gamine" );
//				
//				list.remove(j); // Remove duplicate word
//				duplicateCount++; // Add removed duplicate count
//			}
//		}
////		System.out.println(dWord + "  " + dCount);
//		if (dCount > maxWordCount) maxWordCount = dCount;
//	}
	
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
