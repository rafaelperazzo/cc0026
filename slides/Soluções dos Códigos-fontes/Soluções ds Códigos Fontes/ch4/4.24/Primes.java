/**
 * Java solution to exercise 4.24
 * This algorithm is the "Sieve of Eratosthenes"
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */
class PrimesThread implements Runnable
{
	private int num;
	private int[] primeNums;

	public PrimesThread(int num) {
		if (num < 2)
			throw new IllegalArgumentException();

		this.num = num;
	}
	
	public void run() {
		int i, j;
		primeNums = new int[num + 1];

		primeNums[1] = 0;

		for (i = 2; i <= num; i++)
			primeNums[i] = 1;

		for (i = 2; i <= num/2; i++)
			for (j = 2; j <= num/i; j++)
				primeNums[i*j] = 0;

		for (i = 1; i <= num; i++)
			if (primeNums[i] > 0)
				System.out.println(i); 
	}
}

public class Primes
{
	public static void main(String args[]) {
		if (args.length == 0) {
			System.out.println("Usage: Primes <num>");
			System.exit(0);
		}
		else 
			new Thread(new PrimesThread(Integer.parseInt(args[0]))).start();
	}
}
