package stack;
import java.io.IOException;
public class ReverseApp {
	public static void main(String[] args) throws IOException{
		String input, output;
		while (true){
			System.out.print("Enter a string: ");
			System.out.flush();//刷新缓存区
			input = Util.getString();
			if (input.equals("q")){// read a string from kbd
				System.out.println("exit main");
				break;// quit if input q
			}
			Reverser reverser = new Reverser(input);
			//利用栈的后进先出原理，先将字符串中的字符入栈，然后再将字符串中的字符出栈，实现字符串逆序
			output = reverser.doRev();
			System.out.println("reversed: " + output);
		}//end while
	}// end main
}
