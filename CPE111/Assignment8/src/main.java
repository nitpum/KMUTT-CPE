import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.TreeSet;

public class main {
	
	static Dictionary dictionary;
	static int readCount = 0;
	
	public static void main(String[] args) {
		dictionary = new Dictionary();
		
		// Read file
		ReadFile("utf8lexitron.csv");
//		
//		// Sort
//		dictionary.Sort();
		System.out.println("Total Read: " + readCount);
		System.out.println("TreeSet total: " + dictionary.list.size());
//		dictionary.Print();
//		// Remove duplicate
//		dictionary.RemoveDuplicate();
//		System.out.println("Duplicate: " + dictionary.duplicateCount);
//		System.out.println("Remaining: " + dictionary.list.size());
//		// Find maximum word
		BNode maxMeaning = dictionary.FindMaximumWord();
		System.out.println("Maximumn meaning word " + maxMeaning.word + " have " + maxMeaning.meaning.size() + " meaning.");
		maxMeaning.Print();
//		dictionary.PrintMaxWordList();
		
		// Scanner
		Scanner sc = new Scanner(System.in);
		
		String input;
		boolean endProgram = false;
		boolean command;
		do
		{
			command = false;
			// Recieve input
			System.out.print("Enter word: ");
			input = sc.nextLine();
			// Check input is not end program command
			endProgram = (input.trim().compareToIgnoreCase("/end") == 0)? true : false;
			if (!endProgram || !command)
			{
//				// Set start and end index to null
				int start[] = {-1};
				int end [] = {-1};
				// Search
				
				dictionary.SearchAndPrintWord(input); // Search 
			}
		} while (endProgram == false);
		sc.close();
		System.out.println("End Program");
		
		
	}
	
	public static void ReadFile (String filePath)
	{
		FileInputStream in = null;
		try {
			in = new FileInputStream(filePath);
		} catch (Exception e) {
		 
		}
		InputStreamReader fr = null;
		try {
			fr = new InputStreamReader(in, "UTF-8");
		} catch (Exception e){
			
		}
		
		if (in != null && fr != null) {
			Scanner sc = new Scanner(fr);
			while (sc.hasNext()) {
				dictionary.Add(sc.nextLine().trim().replace("\uFEFF","").replaceAll("\\s+", " "));
				readCount++;
			}
			sc.close();
		}
	}

}
