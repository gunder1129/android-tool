package stack;
/**
 * 						后缀表达式求值
 * |----------------------------------------------------------|
 * |从后缀表达式中读取的元素  |          执行的动作                                                                 |
 * |-----------------|----------------------------------------|
 * |     操作数                      |           入栈                                                                          |
 * |     操作符                      |从栈中提取两个操作数，用操作符将其执行运算。结果入栈             |
 * |----------------------------------------------------------|
 */
public class ParsePost {
	private StackE<Integer> stack;
	private String input;
	
	public ParsePost(String s){
		input = s;
	}
	/**
	 * 求解后缀表达式求值，目前只能求解个位数的值
	 * @return 返回计算结果
	 */
	public Integer doParse(){
		stack = new StackE<Integer>(20);//初始化一个大小为20的栈
		char ch;
		Integer num1, num2, tmpSum;
		for (int i = 0; i < input.length(); i++) {
			ch = input.charAt(i);//从后缀表达式中获取一个字符
			stack.displayStack("" + ch + " ");//打印当前的字符
			if (ch > '0' && ch <= '9'){
				stack.push(Integer.parseInt(ch+""));//如果是数字就入栈
			}else{//如果是操作符，就从栈顶开始，连续获取两个栈元素
				num2 = stack.pop();//获取第一个栈元素
				num1 = stack.pop();//获取第二个栈元素
				switch (ch) {
				case '+'://操作符ch为加，操作数num1和num2进行加法运行，运算结果保存到tmpSum中
					tmpSum = num1 + num2;
					break;
				case '-':
					tmpSum = num1 - num2;
					break;
				case '*':
					tmpSum = num1 * num2;
					break;
				case '/':
					tmpSum = num1 / num2;
					break;
				default:
					tmpSum = 0;
					break;
				}//end switch
				stack.push(tmpSum);//将结算结果tmpSum入栈
			}//end else
		}//end for
		tmpSum = stack.pop();//后缀表达式中的元素读取完后，将计算结果出栈
		return tmpSum;
	}
	
}
