package queue;
public class QueueTest {
	public static void main(String[] args) {
		Queue<String> queue = new QueueImp<String>(5);
		try {
			//向队列尾添加元素
			queue.add("1");//向队列尾添加元素1
			queue.add("2");//向队列尾添加元素2
			queue.add("4");//向队列尾添加元素4
			queue.add("6");//向队列尾添加元素6
			queue.add("9");//向队列尾添加元素9
			System.out.println("queue size: " + queue.size());//打印队列长度
			System.out.println(queue.toString());////打印队列
			//获取队列头元素，不会从队列中删除该元素
			String peekTop = queue.peek();
			System.out.println("queue size after peek: " + queue.size() + " ,peekTop = " + peekTop);
			System.out.println(queue.toString());////打印队列
			//获取队列头元素并且从队列中删除该元素
			String removeTop = queue.remove();//删除队列中的队头元素1，2变成新的队头元素
			System.out.println("queue size after remove: " + queue.size() + " ,removeTop = " + removeTop);
			System.out.println(queue.toString());////打印队列
			removeTop = queue.remove();//删除队列中的队头元素2，4变成新的队头元素
			System.out.println("queue size after remove: " + queue.size() + " ,removeTop = " + removeTop);
			System.out.println(queue.toString());////打印队列
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
