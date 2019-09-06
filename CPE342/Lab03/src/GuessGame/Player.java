package GuessGame;

public class Player {
	
	String name;
	int number;
	boolean correct;
	
	public Player(String name) {
		this.name = name;
		this.correct = false;
	}
	
	void guess() {
		number  = (int)(Math.random() * 10);
		System.out.println("I'm guessing " + number);
	}

}
