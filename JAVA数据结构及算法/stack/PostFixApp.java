package stack;

import java.io.IOException;
public class PostFixApp {
	public static void main(String[] args) throws IOException {
		String input;
		Integer output;
		while (true){
			System.out.print("输入后缀表达式： ");
			System.out.flush();
			input = Util.getString();//从键盘输入
			if (input.equals(""))
				break;
			ParsePost parsePost = new ParsePost(input);
			output = parsePost.doParse();//后缀表达式求值
			System.out.println("解析后缀表达式后的值： " + output);
		}
	}

}
