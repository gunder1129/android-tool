package stack;
public class Reverser {
	private String input;//input string
	private String output;//output string
	public Reverser(String in){//constructor
		input = in;
	}
	public String doRev(){//reverse the string
		int stackSize = input.length();// get max stack size
		StackE<String> stackX = new StackE<String>(stackSize);// make stack
		String tmp = "";
		for (int i = 0; i < input.length(); i++){
			char ich = input.charAt(i); //get a char from input
			tmp += ich;
			stackX.push(tmp); // push ch stack
			tmp = "";
		}
		output = "";
		while (!stackX.isEmpty()){
			String och = stackX.pop(); //pop a char
			output += och; // append to output
		}
		return output;
	}
}
