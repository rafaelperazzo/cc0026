/**
 * Implementation of the Barrier interface.
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts with Java - Eighth Edition
 * Copyright John Wiley & Sons - 2010.
 */


public class BarrierImpl implements Barrier  
{
	// the number of threads to wait for
	private int waitForCount;

	// Constructor that defines the number of threads in the group for this
	// Barrier.
	public BarrierImpl (int waitForCount) {
		this.waitForCount = waitForCount;
	}


    /**
	 * Each thread calls this method when it reaches the barrier.
     * All threads are released to continue processing when the 
     * last thread calls this method.
	 */
	public synchronized void waitForOthers() {
		--waitForCount;

		if (waitForCount<= 0)
			notifyAll();

		while (waitForCount> 0) {
			try {
				wait();
			}
			catch (InterruptedException ie) { }
		}
	}


	/**
	 * Release all threads from waiting for the barrier.
	 * Any future calls to waitForOthers() will not wait
	 * until the Barrier is set again with a call to the constructor.
	 */
	public synchronized void freeAll() {
		waitForCount= 0;
		notifyAll();
	}
}
