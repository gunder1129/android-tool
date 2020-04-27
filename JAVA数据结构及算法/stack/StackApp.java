package stack;
public class StackApp {
	public static void main(String[] args) {
		StackX stackX = new StackX(5); //make new stack
		stackX.push(1);
		stackX.push(2);
		stackX.push(3);
		System.out.println("top = " + stackX.getTop());
		long vpeek = stackX.peek();//获取栈顶元素，不是弹出栈顶元素，栈的元素个数不会减少
		System.out.println("value after peek method: " + vpeek + " , top = " + stackX.getTop());
		long vpop = stackX.pop();//弹出栈顶元素，栈的元素个数减1
		System.out.println("value after pop method: " + vpop + " , top = " + stackX.getTop());
		while (!stackX.isEmpty()){
			long value = stackX.pop();//弹出栈顶元素，栈的元素个数减1
			System.out.print(value);
			System.out.print(" ");
		}
		System.out.println("\ntop = " + stackX.getTop());
		if (stackX.isEmpty())
			System.out.println("stack is empty after pop");
	}
}
