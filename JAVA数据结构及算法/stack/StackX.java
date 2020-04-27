package stack;
/**
 * 通过long的数组实现自定义的栈
 *
 */
public class StackX {
	private int maxSize;//size of stack array
	private long[] stackArray;
	private int top; //top of stack
	
	//初始化栈，s是栈的大小
	public StackX(int s){
		maxSize = s;//set array size
		stackArray = new long[maxSize]; //create array
		top = -1;// no items yet
	}
	
	//将item压入栈顶
	public void push(long item) {// put item on top of stack
		stackArray[++top] = item; //increment top, insert item
	}
	
	//将栈顶元素弹出并删除栈顶元素
	public long pop() {//take item from top of stack
		return stackArray[top--];//access item, decrement top
	}
	//将栈顶元素弹出,不会删除栈顶元素
	public long peek(){//peek at top of stack
		return stackArray[top];
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
}
