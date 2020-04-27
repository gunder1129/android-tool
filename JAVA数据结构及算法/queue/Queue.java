package queue;
/**
 * 队列的操作接口定义
 * @param <E> 泛型，匹配各种数据类的定义
 */
public interface Queue<E> {
	
	boolean add(E e) throws Exception;
	
	E remove() throws Exception;
	 
	E peek() throws Exception;
	
	int size();
	
	String toString();
}
