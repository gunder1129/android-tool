package stack;
/**
 * 中缀表达式转换成后缀表达式
 */
public class InToPost {
	private StackE<String> stack;
	private String input;//输入中缀表达式
	private String output = "";//输出后缀表达式
	//加减（+-）的优先权
	private static final int PRECEDENCE_1 = 1;
	//乘除（*/）的优先权
	private static final int PRECEDENCE_2 = 2;
	
	public InToPost(String in){
		input = in;
		int stackSize = input.length();
		stack = new StackE<String>(stackSize);
	}
	//中缀表达式转换成后缀表达式
	public String doTrans(){
		for (int i = 0; i < input.length(); i++) {
			char ch = input.charAt(i);//中缀表达式中的字符
			stack.displayStack("For " + ch + " ");
			switch (ch) {
			case '+':
			case '-':	
				getOper(ch, PRECEDENCE_1);//判断加减（+-）号是入栈，还是直接添加到字符串output中
				break;
			case '*':
			case '/':
				getOper(ch, PRECEDENCE_2);//判断乘除（*/）号是入栈，还是直接添加到字符串output中
				break;
			case '(':
				stack.push(ch+"");//遇到的字符是左括号'('，就直接压入栈顶
				break;
			case ')':
				//将栈顶元素弹出栈并加入到字符串output中，直到弹出的元素是右括号')'为止，但是最后弹出的左括号不加入字符串output中
				getParen(ch);
				break;
			default:
				output += ch;
				break;
			}//end switch
		}//end for
		while (!stack.isEmpty()){
			stack.displayStack("while ");
			output += stack.pop();
		}
		stack.displayStack("End ");
		return output;
	}
	/**
	 * 操作符opThis是加减乘除时，通过跟栈顶元素opTop对比优先权，如果opThis的优先权大于opTop，
	 * 那么直接将opThis压入栈顶，否则先将opTop弹出栈顶，然后再将opThis压入栈顶
	 * @param opThis 输入的操作符
	 * @param prec1  opThis的优先权，1代表加减；2代表乘除
	 */
	public void getOper(char opThis, int prec1){
		while( !stack.isEmpty()){
			char opTop = stack.pop().charAt(0);//弹出了栈顶元素，如果opThis的优先权大于opTop，那么需要重新压入opTop到栈顶
			//如果栈顶元素是'('，那么重新压入刚弹出的栈顶元素'(',跳出循环并且将opThis直接压入栈顶
			if (opTop == '('){
				stack.push(opTop+"");
				break;
			}else{//如果栈顶元素是操作符，那么对比opThis跟opTop的优先权。
				int prec2;//用来保存栈顶元素opTop的优先权
				if (opTop == '+' || opTop == '-')
					prec2 = 1;//如果栈顶元素为操作符'+'或者'-',那么优先权为1
				else
					prec2 = 2;//如果栈顶元素为操作符'*'或者'/',那么优先权为2
				if (prec2 < prec1){//由于opThis的优先权大于opTop，所以opTop不需要弹出栈，因此需要重新把出栈的opTop重新压入栈顶
					stack.push(opTop+"");//重新把出栈的opTop重新压入栈顶并且跳出循环，然后会把opThis压入栈顶
					break;
				}else{
					output += opTop;//将操作符添加到输入字符串output中
				}
			}
		}//end while
		stack.push(opThis+"");//将opThis压入栈顶
	}
	/**
	 * 当输入字符opThis是右括号')'时，如果栈顶元素opTop不是左括号'(',就将栈顶元素opTop添加到字符串output中
	 * @param opThis
	 */
	public void getParen(char opThis){
		while (!stack.isEmpty()){
			char opTop = stack.pop().charAt(0);//弹出栈顶元素opTop
			if (opThis == ')' && opTop == '(')//如果栈顶元素opTop是左括号'('，就退出循环
				break;
			else
				output += opTop;//栈顶元素opTop不是左括号'(',将栈顶元素opTop添加到字符串output中
		}
	}
}
