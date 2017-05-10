/**
 * To be used with Asg6, creates an object with string operator and 
 * integer priority to help sort in array stack
 * @author ahinh
 *
 */
public class operatorObj {
	private String content;
	private int priority;
	
	public operatorObj () {
		content = null;
		priority = 0;
	}
	
	public operatorObj(String content, int priority) {
		this.content = content;
		this.priority = priority;
	}

	public int priority() {
		return this.priority;
	}
}