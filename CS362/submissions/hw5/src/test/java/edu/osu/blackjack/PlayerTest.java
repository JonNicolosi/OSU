package edu.osu.blackjack;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.Random;
import java.util.*;
import edu.osu.blackjack.Card.Face;
import edu.osu.blackjack.Card.Suit;


public class PlayerTest{
	
	@Test
	public void testAcceptCard(){
		Player player1 = new Player();
		int currentdecksize = player1.currentHand.size();
		Card a = new Card(Card.Face.FIVE,Card.Suit.CLUB);	
		player1.acceptCard(a);	
		assertEquals(player1.currentHand.size(),currentdecksize+1);
	}
	
	@Test
	public void testMakeBet(){
		Player player1 = new Player();
		player1.makeBet();
		int cb = player1.currentBet;
		assertEquals(cb, 10);
	}
	
	@Test
	public void testDoubleDownBet(){
		Player player1 = new Player();
		player1.makeBet();
		int cb = player1.currentBet;
		player1.doubleDownBet();
		cb = cb*2;
		assertEquals(cb, 20);
	}
	
	@Test
	public void testMakeInsuranceBet(){
		Player player1 = new Player();
		player1.currentInsurance = 50;
		player1.makeInsuranceBet();
		int ib = player1.currentInsurance;
		assertEquals(ib, 50);
	}
	
	@Test
	public void testGetAction(){
		Player player1 = new Player();
		assertEquals(player1.getAction().toString(), "STAND");
	}
	
	@Test
	public void testGetHand(){
		Player player1 = new Player();
		Card a = new Card(Card.Face.FIVE,Card.Suit.CLUB);	
		player1.acceptCard(a);
		for(int i = 0; i < player1.currentHand.size(); i++){
			assertEquals(player1.currentHand.get(i),player1.getHand().get(i));
		}
	}
	
	@Test
	public void testGetCurrentBet(){
		Player player1 = new Player();
		player1.currentBet = 10;
		assertEquals(player1.getCurrentBet(), player1.currentBet.intValue());
	}
	
	@Test
	public void testAcceptMoney(){
		Player player1 = new Player();
		int oldwallet = player1.currentWallet;
		player1.acceptMoney(10);
		int newwallet = oldwallet+10;
		assertEquals(newwallet, oldwallet+10);
	}
	
	@Test
	public void testMoveMoneyToInsurance(){
		Player player1 = new Player();
		player1.moveMoneyToInsurance(2000);
	}
	
	@Test
	public void testMoveMoneyToBet(){
		Player player1 = new Player();
		player1.moveMoneyToBet(2000);
	}
	
	@Test
	public void testNextHand(){
		Player player1 = new Player();
		player1.nextHand();
		assertNull(player1.currentBet);
		assertNull(player1.currentWallet);
		assertNull(player1.currentInsurance);
	}
	
	
	
	
}