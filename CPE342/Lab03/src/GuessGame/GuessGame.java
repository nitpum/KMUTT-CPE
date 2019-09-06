package GuessGame;

public class GuessGame {

	Player p1;
	Player p2;
	Player p3;
	int number;
	int winner = 0;
	
	void startGame() {
		p1 = new Player("one");
		p2 = new Player("two");
		p3 = new Player("three");		
		System.out.println("I'm thinking of a number betweej 0 and 9...");
		playing();
	}
	
	void playing() {
		number = (int)(Math.random() * 10);
		System.out.println("Number to guess is " + number);
			
		do {		
			p1.guess();
			p2.guess();
			p3.guess();
			
			System.out.printf("Player %s guessed %d\n", p1.name, p1.number);
			System.out.printf("Player %s guessed %d\n", p2.name, p2.number);
			System.out.printf("Player %s guessed %d\n", p3.name, p3.number);
			
			if (gotWinner() == false) {
				System.out.println("Player will have to try again.");
			}
		} while (gotWinner() == false);
		
		System.out.printf("We have a winner!\n");
		System.out.printf("Player %s got it right? %s\n", p1.name, p1.number == number);
		System.out.printf("Player %s got it right? %s\n", p2.name, p2.number == number);
		System.out.printf("Player %s got it right? %s\n", p3.name, p3.number == number);
		System.out.printf("Game is over");
	}
	
	boolean gotWinner() {
		return p1.number == number || p2.number == number || p3.number == number;
	}
	
}
