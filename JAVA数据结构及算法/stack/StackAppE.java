package stack;

public class StackAppE {

	public static void main(String[] args) {
		StackE<String> stackX = new StackE<String>(5); //make new stack
		stackX.push("1");
		stackX.push("2");
		stackX.push("3");
		stackX.push("4");
		stackX.push("5");
		
		String vpeek = stackX.peek();
		System.out.println("value after peek method: " + vpeek + " , top = " + stackX.getTop());
		
		String vpop = stackX.pop();
		System.out.println("value after pop method: " + vpop + " , top = " + stackX.getTop());
		
		while (!stackX.isEmpty()){
			String value = stackX.pop();
			System.out.print(value);
			System.out.print(" ");
		}
		System.out.println();
		if (stackX.isEmpty())
			System.out.println("stack is empty after pop");
	}

}
