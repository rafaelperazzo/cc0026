/**
 * TunnelController.java
 *
 * This class contains the methods called by the  trains.
 *
 */

 
public class TunnelController
{  
   protected int northBoundCount;
   protected int southBoundCount;
            
   protected boolean northBound;
   protected boolean southBound; 
   
   public TunnelController()
   {
      northBoundCount = 0;
      southBoundCount = 0;
      northBound = false;
      southBound = false;
   }


   public synchronized void enterTunnelNorthBound(int t) {
      while (southBound == true) {
         try { wait(); }
         catch(InterruptedException e) {}
      }  
      
      // ok, we can enter the tunnel now.
      
      ++northBoundCount;
      
      // if I'm the first north-bound train, set the flag
      if (northBoundCount == 1)
         northBound = true;
         
   }
             

   public synchronized void enterTunnelSouthBound(int t) {
      while (northBound == true) {
         try { wait(); }
         catch(InterruptedException e) {}
      }  
      
      // ok, we can enter the tunnel now.
      
      ++southBoundCount;
      
      // if I'm the first south-bound train, set the flag
      if (southBoundCount == 1)
         southBound = true;
         
   }

   
   public synchronized void exitTunnelNorthBound(int t) {
      --northBoundCount;
      
      if (northBoundCount == 0)
         northBound = false;
         
      notifyAll();
   }

   
   public synchronized void exitTunnelSouthBound(int t) {
      --southBoundCount;
      
      if (southBoundCount == 0)
         southBound = false;
         
      notifyAll();
   }

}
