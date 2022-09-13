/**
 * SouthBound.java
 *
 * A southbound train.
 *
 */


public class SouthBound implements Runnable
{
   private TunnelController   server;
   private int                trainNum;

   public SouthBound(int t, TunnelController tc)
   {
      trainNum = t;
      server = tc;
   }

   public void run() {
       System.out.println("SouthBound Train " + trainNum + " wants to enter the tunnel.");
       server.enterTunnelSouthBound(trainNum);
   
       // you can enter the tunnel
       System.out.println("SouthBound Train " + trainNum + " is in the tunnel.");      
       ChooChoo.chugChug();
       
       System.out.println("SouthBound Train " + trainNum + " is exiting the tunnel.");        
       server.exitTunnelSouthBound(trainNum);
   }  
   
}
