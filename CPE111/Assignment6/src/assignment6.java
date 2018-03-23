import java.util.Scanner;

public class assignment6 {

	public static void main(String[] args) {
		
		String[] input;
		boolean end = false;
		Scanner scanner = new Scanner(System.in);
		do
		{
			input = new String[0];
			System.out.print("Enter String: ");
			input = scanner.nextLine().split(" ", -1);
			// Check is end command
			if (input.length == 1 && input[0].toLowerCase().equals("end")) end = true;
			else {
				// Not end command then print data
				displayArray(input);
			}
		} while(end == false); // Do it again if input is not end command
		scanner.close();
		// End program
		System.out.println("End Program");
	}
	
	// Print data in array and print data type
	public static void displayArray (String[] _data)
	{
		for (int i = 0; i < _data.length; i++) 
		{
			// Start line with data index
			String output = "data[" + i + "] ";
			// If data is number print by double
			if (isNumber(_data[i])) output += Double.parseDouble(_data[i]) + " ";
			else output += _data[i] + " ";
			// Print data type
			if (isFunction(_data[i]))		output += "is Function";
			else if (isNumber(_data[i])) 	output += "is Number";
			else 							output += "is Error";
			// Print line
			System.out.println(output);
		}
	}
	
	// Check if string is number
	public static boolean isNumber (String _input)
	{
		// Check by number regex matches
		if (_input.matches("(-?)([0-9])+(\\.?)([0-9]?)")) return true;
		return false;
	}
	
	// Check if string is function
	public static boolean isFunction (String _input)
	{
		// fn list
		String[] list = new String[]{ "sin", "cos", "tan", "log", "exp", "sqrt" };
		for (int i = 0; i < list.length; i++)
		{
			// Return true if fn list contain input
			if (list[i].equals(_input.toLowerCase())) return true; // set to lower for easier check
		}
		return false;
	}

}
