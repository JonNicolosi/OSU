package osu.cs362.URLValidator;

import java.util.*;
import static org.junit.Assert.*;
import org.junit.Test;

public class ResultPairTest {
	
   @Test
   public void ResultPairTest(){
	   ResultPair RP = new ResultPair("item", true);
	   assertTrue(RP.item.toString() == "item");
	   assertTrue(RP.valid);
   }
}
