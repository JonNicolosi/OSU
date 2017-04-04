package edu.osu.cs362;

import static org.junit.Assert.*;
import org.junit.Test;

//assertTrue (boolean)
//assertTrue (String, boolean)
//assertEquals (Object, Object)
//assertNull (Object)
//Fail(String)

public class CardTest{
	

	
	@Test
	public void testEquals(){
		
		Card a = new Card(Card.Face.FIVE,Card.Suit.CLUB);
		Card b = new Card(Card.Face.FIVE,Card.Suit.CLUB);
		assertEquals(a,b);
		
		Card c = new Card(Card.Face.FIVE,Card.Suit.CLUB);
		Card d = new Card(Card.Face.SIX,Card.Suit.HEART);
		assertEquals(c,d);
		
		Card e = new Card(Card.Face.SEVEN,Card.Suit.CLUB); 
		assertEquals(e.face.getValue(),7);
		
	}
	
	
	@Test
	public void testToString(){
		
		Card e = new Card(Card.Face.FIVE, Card.Suit.CLUB);
		assertEquals(e.toString(), "FIVECLUB");
		
	}
	
	@Test
	public void testNewDeck(){
		assertNotNull(Card.newDeck());
		assertEquals(Card.newDeck().size(), 52);
		Card e = new Card(Card.Face.FIVE, Card.Suit.CLUB);
		for(int i = 0; i < Card.newDeck().size(); i++){
			Card.newDeck().get(i).equals(e);
		}
	}
	
	
	@Test
	public void suitTest(){
		assertEquals(Card.Suit.CLUB.ordinal(), 0);
	}
	
	
	@Test
	public void setVisibleTest(){
		
		Card a = new Card(Card.Face.FIVE, Card.Suit.CLUB);
		a.setVisible(true);
		assertTrue(a.isVisible());
	}
	
}