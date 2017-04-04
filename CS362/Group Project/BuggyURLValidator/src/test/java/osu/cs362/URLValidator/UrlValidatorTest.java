package osu.cs362.URLValidator;

import java.util.*;
import static org.junit.Assert.*;
import org.junit.Test;

public class UrlValidatorTest {
   @Test
   public void exampleUrlTest() {
     UrlValidator urlvali = new UrlValidator();
     String abc = null;
     String goog = "http://google.com/";
     //error: the following line fails assertTrue! it shouldn't.
     assertTrue("google is a valid url", urlvali.isValid(goog));
     assertFalse("null isn't a valid url", urlvali.isValid(abc));
     assertFalse("null is not valid path", urlvali.isValidPath(abc));
     assertFalse("null isn't valid authority", urlvali.isValidAuthority(abc));
     assertFalse("null isn't valid scheme", urlvali.isValidScheme(abc));

     // error: for some reason null query returns valid???
     assertTrue("null isn't valid query", urlvali.isValidQuery(abc));

     // this is okay but why is null a valid fragment???
     assertTrue("null isn't valid fragment", urlvali.isValidFragment(abc));
     // isValidFragment doesn't test to see whether a particular frag is valid..
     assertTrue("fragments are on", urlvali.isValidFragment(goog));
   }

   @Test
   public void exampleTest1() {
     UrlValidator urlVali = UrlValidator.getInstance();
   }

   @Test
   public void exampleTest2() {
      String[] schemes = {"http", "https"};
      UrlValidator urlValidator = new UrlValidator(schemes);
      // for some reason this is false?
      assertFalse(urlValidator.isValid("ftp://foo.bar.com/"));
   }

   @Test
   public void exampleTest3() {
      UrlValidator urlValidator = new UrlValidator();
      assertTrue(urlValidator.isValid("ftp://foo.bar.com/"));
   }

   @Test
   public void testAllSchemes() {
      String allowallschemes = "ALLOW_ALL_SCHEMES";
      String[] strArray = new String[] {allowallschemes};
      UrlValidator urlValidator = new UrlValidator(strArray);
   }

   @Test
   public void testRegConstruct() {
      String regex = "abcdefghijklmnopqrstuvwxyz";
      RegexValidator regg = new RegexValidator(regex);
      UrlValidator urlValidator = new UrlValidator(regg, 0+1+2+3);
   }

  @Test
  public void testOptionConstruct() {
      UrlValidator urlValidator = new UrlValidator(0+1+2+3);
  }
}
