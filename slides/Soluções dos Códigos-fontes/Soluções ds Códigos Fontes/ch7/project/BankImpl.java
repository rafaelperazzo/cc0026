/**
 * The Bank
 */

import java.io.*;
import java.util.*;

public class BankImpl implements Bank
{
	private int n;			// the number of threads in the system
	private int m;			// the number of resources

	private int[] available; 	// the amount available of eah resource 
	private int[][] maximum; 	// the maximum demand of each thread 
	private int[][] allocation;	// the amount currently allocated to each thread	
	private int[][] need;		// the remaining needs of each thread		

	/**
	 * Create a new bank with resources.
	 */
	public BankImpl(int[] resources) {
		// m is the number of resources
		m = resources.length;
                n = Customer.COUNT;

		// initialize the resources array
		available = new int[m];
		System.arraycopy(resources,0,available,0,m);

                // create the array for storing the maximum demand by  each thread
                maximum = new int[Customer.COUNT][];
                allocation = new int[Customer.COUNT][];
                need = new int[Customer.COUNT][];
	}
        
        /**
         * This method is invoked by a thread when it enters the system. It records
         * its maximum demand with the bank.
         */
        public void addCustomer(int threadNum, int[] maxDemand) {
            maximum[threadNum] = new int[m];
            allocation[threadNum] = new int[m];
            need[threadNum] = new int[m];
            
            System.arraycopy(maxDemand, 0, maximum[threadNum], 0, maxDemand.length);
            System.arraycopy(maxDemand, 0, need[threadNum], 0, maxDemand.length);
        }

	/**
	 * Outputs the state for each thread
	 */
	        
        public void getState() {
            System.out.print("Available = [");
            for (int i = 0; i < m-1; i++)
                System.out.print(available[i]+" ");
            System.out.println(available[m-1]+"]");
            System.out.print("\nAllocation = ");
            for (int i = 0; i < n; i++) {
                System.out.print("[");
                for (int j = 0; j < m-1; j++)
                    System.out.print(allocation[i][j]+" ");
                System.out.print(allocation[i][m-1]+"]");
            }
            System.out.print("\nMax = ");
            for (int i = 0; i < n; i++) {
                System.out.print("[");
                for (int j = 0; j < m-1; j++)
                    System.out.print(maximum[i][j]+" ");
                System.out.print(maximum[i][m-1]+"]");
            }
            System.out.print("\nNeed = ");
            for (int i = 0; i < n; i++) {
                System.out.print("[");
                for (int j = 0; j < m-1; j++)
                    System.out.print(need[i][j]+" ");
                System.out.print(need[i][m-1]+"]");
            }

	    System.out.println();
        }


	/**
	 * Determines whether granting a request results in leaving
	 * the system in a safe state or not.
	 *
	 * @return  true - the system is in a safe state.
	 * @return  false - the system is NOT in a safe state.
	 */
	private boolean isSafeState (int threadNum, int[] request) {
                System.out.print("\n Customer # " + threadNum + " requesting ");
                for (int i = 0; i < m; i++) System.out.print(request[i] + " ");
                
                System.out.print("Available = ");
                for (int i = 0; i < m; i++)
                    System.out.print(available[i] + "  ");
                    
                // first check if there are sufficient resources available
                for (int i = 0; i < m; i++) 
                    if (request[i] > available[i]) {
                        System.err.println("INSUFFICIENT RESOURCES");
                        return false;
                    }
            
                // ok, they're are. Now let's see if we can find an ordering of threads to finish
		boolean[] canFinish = new boolean[n];
		for (int i = 0; i < n; i++)
			canFinish[i] = false;

		// copy the available matrix to avail
		int[] avail = new int[m];
		System.arraycopy(available,0,avail,0,available.length);

		// Now decrement avail by the request.
                // Temporarily adjust the value of need for this thread.
                // Temporarily adjust the value of allocation for this thread.
		for (int i = 0; i < m; i++) {
                        avail[i] -= request[i];
                        need[threadNum][i] -= request[i];
                        allocation[threadNum][i] += request[i];
                }
                           
		/**
		 * Now try to find an ordering of threads so that
		 * each thread can finish.
		 */

		for (int i = 0; i < n; i++) {
			// first find a thread that can finish
			for (int j = 0; j < n; j++) {
				if (!canFinish[j]) {
					boolean temp = true;
					for (int k = 0; k < m; k++) {
						if (need[j][k] > avail[k])
							temp = false;
					}
					if (temp) { // if this thread can finish
						canFinish[j] = true;
						for (int x = 0; x < m; x++)
							avail[x] += allocation[j][x];
					}
				}	
			}
		}
       
                // restore the value of need and allocation for this thread
                for (int i = 0; i < m; i++) {
                    need[threadNum][i] += request[i];
                    allocation[threadNum][i] -= request[i];
                }
                
                // now go through the boolean array and see if all threads could complete
		boolean returnValue = true;
		for (int i = 0; i < n; i++)
			if (!canFinish[i]) {
				returnValue = false;
				break;
			}

		return returnValue;
	}
        
	/**
	 * Make a request for resources. This is a blocking method that returns
	 * only when the request can safely be satisfied.
 	 *
	 * @return  true - the request is granted.
	 * @return  false - the request is not granted.
         */
	
	public synchronized boolean requestResources(int threadNum, int[] request)  {
		if (!isSafeState(threadNum,request)) {
                        //System.out.println("Customer # " + threadNum + " is denied.");
			return false;
                }

		// if it is safe, allocate the resources to thread threadNum 
		for (int i = 0; i < m; i++) {
                        available[i] -= request[i];
			allocation[threadNum][i] += request[i];
			need[threadNum][i] = maximum[threadNum][i] - allocation[threadNum][i];
		}
                /*
                System.out.println("Customer # " + threadNum + " using resources.");
                 System.out.print("Available = ");
                for (int i = 0; i < m; i++)
                    System.out.print(available[i] + "  ");
                 System.out.print("Allocated = [");
                for (int i = 0; i < m; i++)
                    System.out.print(allocation[threadNum][i] + "  "); 
                    System.out.print("]");  
                */
                return true;
	}


	/**
	 * Make a request for resources. This is a blocking method that returns
	 * only when the request can safely be satisfied.
 	 *
	 * @return  true - the request is granted.
	 * @return  false - the request is not granted.
	
	public synchronized void requestResources(int threadNum, int[] request) throws InterruptedException {
		while (!isSafeState(threadNum,request))
			wait();

		// if it is safe, allocate the resources to thread threadNum 
		for (int i = 0; i < m; i++) {
                        available[i] -= request[i];
			allocation[threadNum][i] += request[i];
			need[threadNum][i] = maximum[threadNum][i] - allocation[threadNum][i];
		}
                System.out.println("Customer # " + threadNum + " using resources.");
                 System.out.print("Available = ");
                for (int i = 0; i < m; i++)
                    System.out.print(available[i] + "  ");
	}
         */

        /**
         * Release resources
	 *
	 * @param int[] release - the resources to be released.
         */
        public  synchronized void releaseResources(int threadNum, int[] release)  {
                System.out.print("\n Customer # " + threadNum + " releasing ");
                for (int i = 0; i < m; i++) System.out.print(release[i] + " ");
                
		for (int i = 0; i < m; i++) {
			available[i] += release[i];
			allocation[threadNum][i] -= release[i];
			need[threadNum][i] = maximum[threadNum][i] + allocation[threadNum][i];
		}
                
                System.out.print("Available = ");
                for (int i = 0; i < m; i++)
                    System.out.print(available[i] + "  ");
                    
                System.out.print("Allocated = [");
                for (int i = 0; i < m; i++)
                    System.out.print(allocation[threadNum][i] + "  "); 
                    System.out.print("]"); 

		// there may be some threads that can now proceed
		//notifyAll();
        }
        
}
