package edu.osu.cs362;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.*;

public class WarmupTest  {
    @Test
    public void testFindIntegerExample() {

		int result = WarmUp.findInteger(new int[] { 1, 2, 3, 4, 5 }, 100);
		assertEquals(result, -1);

		for (int i = 1; i < 5; i++) {
			int result2 = WarmUp.findInteger(new int[] { 1, 2, 3, 4, 5 }, i + 1);
			assertEquals("findInteger(new int[]{1,2,3,4,5}," + i + ")", result2, i);
		}
	}
	
	@Test
	public void testLastZero(){
		
		int result = WarmUp.lastZero(new int[] {1,2,0,4,5});
		assertEquals(result, 2);
		
		int result2 = WarmUp.lastZero(new int[] {0});
		assertEquals(result2, 0);
		
		int result3 = WarmUp.lastZero(new int[] {1,2,3,4,5});
		assertEquals(result3, -1);
		
	}
	
	@Test
	public void testLast(){
		
		int result = WarmUp.last(new int[] {1,2,3,4}, 2);
		assertEquals(result, 1);
		
		int result2 = WarmUp.last(new int[] {1,2,3,4}, 0);
		assertEquals(result2, -1);
	
		
	}
	
	@Test
	public void testPositive(){
		
	int result = WarmUp.positive(new int[] {-1,-2,-3});
	assertEquals(result, 0);
		
	int result2 = WarmUp.positive(new int[] {1,2,3});
	assertEquals(result2, 3);
		
	}
	
	@Test public void testOddOrPos(){
		
	int result = WarmUp.positive(new int[] {2,4,5});
	assertEquals(result, 3);
		
	int result2 = WarmUp.positive(new int[] {1,2,3});
	assertEquals(result2, 3);
		
	}
	
}
