package queue;

public class QueueImp<E> implements Queue<E>{
	private int maxSize;//队列最大容量
	private Object[] queArray;//保存队列的数据
	private int front;//队列头下标
	private int rear;//队列尾下标
	private int nItems;//队列当前元素个数
	//初始化队列成员变量
	public QueueImp(int s) {
		maxSize = s;
		queArray = new Object[maxSize];
		front = 0;
		rear = -1;
		nItems = 0;
	}
	
	//从队列尾部添加元素
	public boolean add(E e) throws Exception{
		if (isFull())
			throw new Exception("queue is full");
		if (rear == maxSize - 1)
			rear = -1;
		queArray[++rear] = e;
		nItems++;
		return true;
	}

	//获取队列头元素并且从队列中删除该元素
	public E remove() throws Exception{
		if (isEmpty())
			throw new Exception("queue is empty");
		E e = (E) queArray[front++];
		if (front == maxSize)
			front = 0;
		nItems--;
		return e;
	}
	
	//获取队列头元素
	public E peek() throws Exception{
		if (isEmpty())
			throw new Exception("queue is empty");
		return (E) queArray[front];
	}
	
	//判断队列是否为空
	public boolean isEmpty(){
		return nItems == 0;
	}
	//判断队列是否溢出
	public boolean isFull(){
		return nItems == maxSize;
	}
	//获取队列长度
	public int size(){
		return nItems;
	}
	//打印队列
	public String toString() {
		if (isEmpty())
			return "";
		String str = "queue: [ ";
		for (int i = front; i < maxSize; i++)
			str += queArray[i] + " ";
		str += "]";
		return str;
	}
}
