package edu.osu.sort;

import static org.junit.Assert.*;
import org.junit.Test;
import java.util.*;

public class SortTest  {



    private static List<Integer> randomIntegerArray(int n){
		Random r = new Random();
		List<Integer> li = new ArrayList<Integer>();
		for(int i = 0; i < n; i++){
			li.add(r.nextInt());
		}
		
		return li;
    }

    /*
    @Test // This test is an example template using an oracle
    public void randomTestExample() {
	int n_runs = 10;
	for(int i=0;i<n_runs;i++){
	    
	    // Generate a random array of size 10
	    List<Integer> sorted = randomIntegerArray(10);

	    // Copy the sorted array before sorting it 
	    List<Integer> original = new ArrayList(sorted);

	    // Sort it
	    Sort.sort(sorted);

	    // Test the result 
	    assertTrue(SortOracle.isSorted(original,sorted));
	}
    }
    */
    
    @Test
    public void randomTestOracle() {    
		int n_runs = 100;
	for(int i=0;i<n_runs;i++){
	    
	    // Generate a random array of size 10
	    List<Integer> sorted = randomIntegerArray(1000);

	    // Copy the sorted array before sorting it 
	    List<Integer> original = new ArrayList(sorted);

	    // Sort it
	    Sort.sort(sorted);

	    // Test the result 
	    assertTrue(SortOracle.isSorted(original,sorted));
	
    }
		
		
		
    }

    @Test
    public void randomTestAssertion() { 

	    List<Integer> first = randomIntegerArray(1000);

	    List<Integer> second = new ArrayList(first);
		
		Sort.sort(first);
		
		Sort.sort(second);
		
		
		//Assert that the first element of the first list equals the first
		//element of the second list.
		assertEquals(first.get(0), second.get(0));
		
		//Assert that the last element is larger than the second to last element.
		assertTrue(first.get(first.size()-1)>first.get(first.size()-2));
		assertTrue(second.get(first.size()-1)>second.get(first.size()-2));
		
		//Assert that the second element is larger than the first.
		assertTrue(first.get(0)<first.get(1));
		assertTrue(second.get(0)<second.get(1));
		
		int firstsum = 0;
		int secondsum = 0;
		
		
		for(int i = 0; i < first.size()-500; i++){
			firstsum = first.get(i) + firstsum;
		}
		for(int j = 0; j < second.size()-500; j++){
			secondsum = second.get(j) + secondsum;
		}
		//Assert that a subset of the first list and a subset of the second
		//list have the same sum.
		assertEquals(firstsum, secondsum);
		
		Sort.sort(first);
		
		Sort.sort(second);
		//Assert that the sorting procedure is consistent by sorting a 
		//second time.
		for(int i = 1; i < first.size(); i++){
			assertTrue(first.get(i)>first.get(i-1));
		}
		for(int i = 1; i < second.size(); i++){
			assertTrue(second.get(i)>second.get(i-1));
		}
		
    }
}
