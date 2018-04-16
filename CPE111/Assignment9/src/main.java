import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.TreeSet;

public class main {
	
	static Dictionary dictionary;
	static int readCount = 0;
	
	public static void main(String[] args) {
		// Create new dictionary
		dictionary = new Dictionary();
		
		// Read file
		ReadFile("utf8lexitron.csv");
		// Print count
		System.out.println("Total Read: " + readCount);
		System.out.println("TreeSet total: " + dictionary.list.size());
		// Find and print maximum word
		BNode maxMeaning = dictionary.FindMaximumWord();
		System.out.println("Maximumn meaning word " + maxMeaning.word + " have " + maxMeaning.meaning.size() + " meaning.");
		maxMeaning.Print();
		
		// Scanner
		Scanner sc = new Scanner(System.in);
		
		String input;
		boolean endProgram = false; // end command
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
				// Search and print word
				dictionary.SearchAndPrintWord(input); // Search 
			}
		} while (endProgram == false); // Check end command 
		sc.close();
		// End program
		System.out.println("End Program");		
	}
	
	// Function readfile
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
			// Each line
			while (sc.hasNext()) {
				// Add word to dictionary
				// Before add word trim and remove buffer
				dictionary.Add(sc.nextLine().trim().replace("\uFEFF","").replaceAll("\\s+", " "));
				readCount++; // Count word
			}
			sc.close();
		}
	}

}
