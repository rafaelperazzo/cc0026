/**
 * Java solution to exercise 4.26
 *
 * Operating System Concepts - Ninth Edition
 * John Wiley & Sons - 2013.
 */

class FibThread implements Runnable
{
	private int[] fibNums;

	public FibThread(int[] fibNums) {
		this.fibNums = fibNums;
	}
	
	public void run() {
		int length = fibNums.length;

		if (length == 0)
			return;
		else if (length == 1)
			fibNums[0] = 0;
		else if (length == 2) {
			fibNums[0] = 0;
			fibNums[1] = 1;
		}
		else { // length > 2
			fibNums[0] = 0;
			fibNums[1] = 1;

			for (int i = 2; i < length; i++)
				fibNums[i] = fibNums[i-1] + fibNums[i-2];
		}
	}
}

public class Fib
{
	public static void main(String args[]) {
		if (args.length == 0) {
			System.out.println("Usage: Fib <num>");
			System.exit(0);
		}
		else if (Integer.parseInt(args[0]) < 0) {
			System.out.println("Sequence size must be >= 0\n");
			System.exit(0);
		}
		else {
			int[] sequence = new int[Integer.parseInt(args[0])];
			Thread worker = new Thread(new FibThread(sequence));
			worker.start();

			try {
				worker.join();
			} catch (InterruptedException ie) { }

			for (int i = 0; i < sequence.length; i++)
				System.out.println(sequence[i]);
		}
	}
}
