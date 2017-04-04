package osu.cs362.URLValidator;

import java.util.*;
import static org.junit.Assert.*;
import org.junit.Test;

public class RegexValidatorTest {
   @Test
   public void exampleRegexTest() {
      String regex = "abcdefghijklmnopqrstuvwxyz";
      String[] regexArray = new String[] {regex};
      RegexValidator regg = new RegexValidator(regexArray);
      RegexValidator caseSenReg = new RegexValidator(regexArray, true);
      RegexValidator noCaseReg = new RegexValidator(regexArray, false);
      String test1 = "catscratch";
      String test2 = "ca75cr47ch";
      String test3 = "CatScratch";
      // error! case sensitivity doesn't work.
      assertFalse("should be valid", noCaseReg.isValid(test3));
      assertFalse("casesensitive should error", caseSenReg.isValid(test3));
      assertFalse("should not use numbers", regg.isValid(test2));
      String empty = "";
      assertNull(regg.validate(empty));
      assertNull(regg.validate(null));
   }

   
   @Test(expected=IllegalArgumentException.class)
   public void illegalArgTest() {
      String regex = "abcdefghijklmnopqrstuvwxyz";
      String[] regexArray = new String[] {regex};
      String empty = "";
      RegexValidator noCaseReg = new RegexValidator(empty, false);
   }
   
   @Test(expected=IllegalArgumentException.class)
   public void illegalArgTest1() {
      String regex = "abcdefghijklmnopqrstuvwxyz";
      String[] regexArray = new String[] {"a", "b", null, "c"};
      String empty = "";
      RegexValidator noCaseReg = new RegexValidator(regexArray, false);
   }

   
   @Test(expected=IllegalArgumentException.class)
   public void illegalArgTest2() {
      String regex = "abcdefghijklmnopqrstuvwxyz";
      String[] regexArray = new String[] {regex};
      String empty = null;
      RegexValidator noCaseReg = new RegexValidator(empty, false);
   }

   @Test
   public void testValidStuff() {
      String regex = "abcdefghijklmnopqrstuvwxyz";
      String[] regexArray = new String[] {regex};
      RegexValidator regg = new RegexValidator(regexArray);
      RegexValidator caseSenReg = new RegexValidator(regexArray, true);
      RegexValidator noCaseReg = new RegexValidator(regexArray, false);
      String test1 = "catscratch";
      String nullstr = null;
      assertFalse("nullstr should be false.", regg.isValid(nullstr));
      // error! should be true!
      assertFalse("test1 should be valid", regg.isValid(test1));
      assertNull("nullstr should return null", regg.match(nullstr));    
      String validatorstr = regg.toString();
      System.out.print(validatorstr);
      assertEquals("RegexValidator{abcdefghijklmnopqrstuvwxyz}", validatorstr);
      String partialthing = "abcd";
      assertTrue(regg.isValid(regex));
   } 
}
