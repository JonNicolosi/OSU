package edu.osu.cs362;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.*;

public class CardCollectionTest{
	
	
	@Test
	public void testGetCard(){
	    CardCollection c = new CardCollection();
        Card c1 = new Card(Card.Face.ACE,Card.Suit.HEART);
        c.add(c1);
        Card c2 = c.getCards().get(0);
        assertEquals(c1.suit,c2.suit);
        assertEquals(c2.face.getValue(),11);
		c.getCards().get(1);
	}
	
	@Test
	public void testAddCard(){
		ArrayList<Card> decky = Card.newDeck();
		decky.add(new Card(Card.Face.ACE,Card.Suit.HEART));
		assertEquals(decky.size(), 53);
	}
	
	
	@Test
	public void testDiscardCard(){
		ArrayList<Card> decky = Card.newDeck();
		decky.add(new Card(Card.Face.ACE,Card.Suit.HEART));
		assertEquals(decky.size(), 53);
		CardCollection f = new CardCollection();
		f.add(decky);
		assertEquals(f.discardCard(52).toString(), "ACEHEART");
		f.discardCard(52);
	}
	
	@Test
	public void testAddAll(){
		ArrayList<Card> decky = Card.newDeck();
		decky.add(new Card(Card.Face.ACE,Card.Suit.HEART));
		CardCollection x = new CardCollection();
		x.add(decky);
	}
	
	@Test
	public void testDiscardThenAdd(){
		
		ArrayList<Card> decky = Card.newDeck();
		CardCollection cc1 = new CardCollection();
		cc1.add(decky); 
		String s = cc1.getCards().get(40).toString();
		cc1.discardCard(40);
		ArrayList<Card> deckyClone = new ArrayList<Card>();
		for(int i = 0; i < cc1.cards.size(); i++){
			deckyClone.add(cc1.getCards().get(i));
		}
		CardCollection cc2 = new CardCollection();
		cc2.add(deckyClone);
		assertNull(cc1.getCards().get(40));
		assertEquals(cc1.getCards().get(40), cc2.getCards().get(40));
	}
	
	
}