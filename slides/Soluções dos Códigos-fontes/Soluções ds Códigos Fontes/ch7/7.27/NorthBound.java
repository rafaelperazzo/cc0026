/**
 * NorthBound.java
 *
 * A northbound train.
 *
 */

public class NorthBound implements Runnable
{
   private TunnelController   server;
   private int                trainNum;

   public NorthBound(int t, TunnelController tc)
   {
      trainNum = t;
      server = tc;
   }

   public void run() {
       System.out.println("NorthBound Train " + trainNum + " wants to enter the tunnel.");
       server.enterTunnelNorthBound(trainNum);
   
       // you can enter the tunnel
       System.out.println("NorthBound Train " + trainNum + " is in the tunnel.");      
       ChooChoo.chugChug();
       
       System.out.println("NorthBound Train " + trainNum + " is exiting the tunnel.");        
       server.exitTunnelNorthBound(trainNum);
   }  
   
}
