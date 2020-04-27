package stack;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
public class Util {
	public static String getString() throws IOException{
		InputStreamReader isr = new InputStreamReader(System.in);//¥”º¸≈Ã ‰»Î
		BufferedReader br = new BufferedReader(isr);
		String s = br.readLine();
		return s;
	}
}
