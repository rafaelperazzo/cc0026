/**
 * ChooChoo.java
 *
 * This class contains the methods called by trains
 * to simulate entering the tunnel and keeping busy 
 * before they request entering the tunnel.
 */

public class ChooChoo
{
   private static int TRAVEL_TIME = 5;
   private static int DONUT_TIME = 2;

   // trains will call this when they are in the tunnel
   public static void chugChug()
   {
     int sleepTime = (int) (TRAVEL_TIME * Math.random() );
     try { Thread.sleep(sleepTime*1000); } 
     catch(InterruptedException e) {}
   }
   
   public static void eatDonut()
   {
     int sleepTime = (int) (DONUT_TIME * Math.random() );
     try { Thread.sleep(sleepTime*1000); } 
     catch(InterruptedException e) {}
   }
}

