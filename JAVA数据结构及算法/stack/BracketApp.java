package stack;
import java.io.IOException;
public class BracketApp {
	public static void main(String[] args) throws IOException{
		String input;
		while(true){
			System.out.print("Enter string containing delimiters: ");
			System.out.flush();
			input = Util.getString();
			if (input.equals("q")){// read a string from kbd
				System.out.println("exit main");
				break;// quit if input 
			}
			BracketChecker bracketChecker = new BracketChecker(input);
			bracketChecker.check();
		}//end while
	}//end main
	
	

}
