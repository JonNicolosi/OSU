package edu.osu.blackjack;


import static org.junit.Assert.*;
import org.junit.Test;
import java.util.Random;
import java.util.*;
import edu.osu.blackjack.Card.Face;
import edu.osu.blackjack.Card.Suit;

public class DealerTest{
	
	@Test
	public void testAcceptCard(){
		Dealer dealer = new Dealer();
		Card c1 = new Card(Card.Face.ACE,Card.Suit.HEART);
		dealer.acceptCard(c1);
		Card c2 = dealer.getHand().get(52);
		assertEquals(c1.toString(), c2.toString());
	}
	
	@Test
	public void testShuffleDeck(){
		
		Dealer dealer1 = new Dealer();
		Dealer dealer2 = new Dealer();
		for(int i = 0; i < 52; i++){
			assertEquals(dealer1.getHand().get(i).toString(),dealer2.getHand().get(i).toString());
		}
		
		dealer1.shuffleDeck();
		for(int i = 0; i < 52; i++){
			assertEquals(dealer1.getHand().get(i).toString(),dealer2.getHand().get(i).toString());
		}
		
	}
	
	@Test
	public void testDealCard(){
		
		Dealer dealer1 = new Dealer();
		Dealer dealer2 = new Dealer();
		Player player1 = new Player();
		Player player2 = new Player();
		
		assertEquals(dealer1.getHand().size(), 52);
		
		dealer1.dealCard(player1);
		
		assertEquals(dealer1.getHand().size(), 51);
		
		assertEquals(player1.currentHand.size(), 1);
		
		//check for out-of-bounds exception
		for(int i = 0; i < 53; i++){
			
			dealer2.dealCard(player2);
			
		}
		//check to make sure that the entire deck has been added to the player's hand
		assertEquals(player2.currentHand.size(), 52);
		
	}
	
	@Test
	public void testCompareHandAndSettle(){
		
		Dealer dealer1 = new Dealer();
		Player player1 = new Player();
		
		dealer1.dealCard(player1);
		dealer1.dealCard(player1);
		
		player1.makeBet();
		
		dealer1.compareHandAndSettle(player1);
		
		assertNull(player1.currentBet);
		assertNull(player1.currentWallet);
		assertNull(player1.currentInsurance);
		
	}
	
	@Test
	public void testReset(){
		
		Dealer dealer1 = new Dealer();
		Card c1 = new Card(Card.Face.ACE,Card.Suit.HEART);
		dealer1.acceptCard(c1);
		dealer1.reset();
		assertEquals(dealer1.getHand().size(), 52);
		
	}
	
	@Test
	public void testSetDeck(){
		
		Dealer dealer1 = new Dealer();
		Card c1 = new Card(Card.Face.ACE,Card.Suit.HEART);
		ArrayList<Card> decky = Card.newDeck();
		decky.add(new Card(Card.Face.ACE,Card.Suit.HEART));
		dealer1.setDeck(decky);
		assertEquals(dealer1.getHand().get(0).toString(), c1.toString());
		
		for(int i=0; i < 53; i++){
			
			decky.remove(i);
			
		}
		
		assertEquals(decky.size(), 53);
		dealer1.setDeck(decky);
		assertEquals(dealer1.getHand().get(0).toString(), c1.toString());
		
	}
	
	
	@Test
	public void testdumpDeck(){
		
		Dealer dealer1 = new Dealer();
		Player player1 = new Player();
		dealer1.dumpDeck(dealer1.getHand());
		for(int i = 0; i < 52; i++){
			
			dealer1.dealCard(player1);
			
		}
		
		dealer1.dumpDeck(dealer1.getHand());
		
	}
	
	
}