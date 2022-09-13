/**
 * Barrier.java
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts with Java - Eighth Edition
 * Copyright John Wiley & Sons - 2010.
 */

public interface Barrier 
{
    /**
	 * Each thread calls this method when it reaches the barrier.
     * All threads are released to continue processing when the 
     * last thread calls this method.
	*/
	public void waitForOthers();


	/**
	 * Release all threads from waiting for the barrier.
	 * Any future calls to waitForOthers() will not wait
	 * until the Barrier is set again with a call to the constructor.
	 */
	public void freeAll();
}
