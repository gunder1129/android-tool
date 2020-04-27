package stack;

import java.io.IOException;


public class InfixToPostFixApp {
	public static void main(String[] args) throws IOException {
		
		String infixInput, infixOutput;
		Integer postfixOutput;//保存解析的后缀表达式的值
		while(true){
			System.out.print("输入中缀表达式：");
			System.out.flush();
			infixInput = Util.getString();
			if (infixInput.equals(""))
				break;
			InToPost trans = new InToPost(infixInput);//中缀表达式转换成后缀表达式
			infixOutput = trans.doTrans();
			System.out.println("后缀表达式： " + infixOutput);
			
			ParsePost parsePost = new ParsePost(infixOutput);
			postfixOutput = parsePost.doParse();//后缀表达式求值
			System.out.println("解析后缀表达式的值： " + postfixOutput);
		}
	}

}
