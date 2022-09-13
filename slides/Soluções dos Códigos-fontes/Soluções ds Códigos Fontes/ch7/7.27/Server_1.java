/**
 * Server.java
 *
 * This creates the trains and then eats a donut before
 * creating another.
 *
 */
 
public class Server 
{  
   private static final int NUM_OF_NORTHBOUND = 3;
   private static final int NUM_OF_WRITERS = 2;
 
   public static void main(String args[])
   {
      TunnelController controller = new TunnelController();
      
      int n = 0;
      int count = 0;
      
      while (true) {
         ChooChoo.eatDonut();
         
         if (n == 0) {
            Thread northerner = new Thread(new NorthBound(count, controller));
            northerner.start();
            n = 1;
         }
         else {
            Thread southerner = new Thread(new SouthBound(count, controller));
            southerner.start();
            n = 0;
         }
         ++count;
      }
   }
}
