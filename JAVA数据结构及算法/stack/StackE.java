package stack;
/**
 * 通过Object的数组实现自定义的栈
 *
 */
public class StackE<E> {
	private int maxSize;//size of stack array
	private Object[] stackArray;
	private int top; //top of stack
	
	//初始化栈，s是栈的大小
	public StackE(int s){
		maxSize = s;//set array size
		stackArray = new Object[maxSize]; //create array
		top = -1;// no items yet
	}
	
	//将item压入栈顶
	public void push(E item) {// put item on top of stack
		stackArray[++top] = item; //increment top, insert item
	}
	
	//将栈顶元素弹出并删除栈顶元素
	public E pop() {//take item from top of stack
		return (E) stackArray[top--];//access item, decrement top
	}
	//将栈顶元素弹出,不会删除栈顶元素
	public E peek(){//peek at top of stack
		return (E) stackArray[top];
	}
	
	//判断栈是否为空
	public boolean isEmpty(){//true if stack is empty
		return top == -1;
	}
	
	//判断栈是否满了
	public boolean isFull(){//true if stack is full
		return top == maxSize - 1;
	}
	//返回栈顶位置
	public int getTop(){
		return top;
	}
	
	//将栈中的第n个元素弹出,不会删除该元素
	public E peekN(int n){//peek at top of stack
		return (E) stackArray[n];
	}
	
	//获取栈的元素个数
	public int size(){
		return top+1;
	}
	
	public void displayStack(String s){
		System.out.print(s);
		System.out.print("Stack (bottom-->top): ");
		for (int i = 0; i < size(); i++) {
			System.out.print(peekN(i));
			System.out.print(' ');
		}
		System.out.println();
	}
}
