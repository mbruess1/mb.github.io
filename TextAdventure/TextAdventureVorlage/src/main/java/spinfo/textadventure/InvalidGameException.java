package spinfo.textadventure;


public class InvalidGameException extends Exception {

	private static final long serialVersionUID = 3482038015540582811L;

	public InvalidGameException(String message, Exception e) {
		super(message, e);
	}

}
