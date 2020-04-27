package stack;
public class BracketChecker {
	private String input;//input string
	public BracketChecker(String in){//constructor
		input = in;
	}
	public void check(){
		int stackSize = input.length();//get max stack size
		StackE<String> stackE = new StackE<String>(stackSize); //make stack
		for(int i = 0; i < input.length(); i++){
			char ch = input.charAt(i);
			switch (ch) {
			case '{':
			case '[':
			case '(':
				stackE.push(ch+"");
				break;
			case '}':
			case ']':
			case ')':
				if (!stackE.isEmpty()){
					char pch = stackE.pop().charAt(0);
					if ((ch == '}' && pch != '{') ||
							(ch == ']' && pch != '[') ||
							(ch == ')' && pch != '('))
						System.out.println("Error: " + ch + " at " + i);
				}else{
					System.out.println("Error: " + ch + " at " + i);
				}
			default:
				break;
			}//end switch
		}//end for
		if (!stackE.isEmpty()){
			System.out.println("Error: missing right delimiter");
		}
	}
}
