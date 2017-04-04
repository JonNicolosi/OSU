package edu.osu.blackjack;


import static org.junit.Assert.*;
import org.junit.Test;
import java.util.Random;

public class SimpleBlackjackTest {
	
    @Test
    public void testPlayRound(){
		
		for(int a = 0; a < 10; a++){	
		
			int n;
			int p;
			Random r = new Random();
			n = r.nextInt(4 - 1 + 1) + 1;
				
			Dealer dealer = new Dealer();
			dealer.shuffleDeck();
			Player[] players  = new Player[n];
			
			Random q  = new Random();
			long seed = System.currentTimeMillis();
			q = new Random(seed);
			
			p = q.nextInt(1000-1+1) + 1;
			
			for(int i = 0; i < n; i++){
				players[i] = new Player();
				players[i].currentWallet = p;
			}
				

			SimpleBlackjack j = new SimpleBlackjack(dealer,players);
			j.playRound();
			
			for(int i = 0; i < n; i++){
				assertNotNull(players[i].currentHand.get(0));
				//Following attributes should be set to NULL by nextHand 
				//which is called by compareHandandSettle
				assertNull(players[i].currentBet);
				assertNull(players[i].currentWallet);
				assertNull(players[i].currentInsurance);
				
			}
			//Assert that addAll gives dealer new hand for the next hand.
			assertNotNull(dealer.getHand());
		}
	}
	
	
	
	
}
