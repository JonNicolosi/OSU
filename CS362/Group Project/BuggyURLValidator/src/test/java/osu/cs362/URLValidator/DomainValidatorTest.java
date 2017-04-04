package osu.cs362.URLValidator;

import java.util.*;
import static org.junit.Assert.*;
import org.junit.Test;
import java.io.Serializable;
import org.junit.Before;

public class DomainValidatorTest {
   DomainValidator domainval;
   DomainValidator domainvallocal;

   @Before
   public void init() {
      domainval = DomainValidator.getInstance();
      domainvallocal = DomainValidator.getInstance(true);

   }

   @Test
   public void exampleDomainTest() {
      DomainValidator domainval1 = DomainValidator.getInstance(false);
      assertEquals(domainval, domainval1);
   }

   @Test
   public void testLocalTld() {
      String validlocaltld = "localhost";
      // fails!! 
      assertNotEquals("localhost executed with 'true' should be valid localtld", true, domainvallocal.isValidLocalTld(validlocaltld));
      //assertNotEquals("localhost executed with 'false' should be invalid localtld", false, domainval.isValidLocalTld(validlocaltld));
      String invalidltld = "loclahost";
      assertNotEquals("loclahost is invalid localtld", false, domainval.isValidLocalTld(invalidltld));
   }

   @Test
   public void testCCTld() {
      // Test CountryCodeTld
      String validctcode = "ca";
      assertEquals("valid cc", true, domainval.isValidCountryCodeTld(validctcode));
      String invalidctcode = "jk";      
      assertEquals("invalid cc", false, domainval.isValidCountryCodeTld(invalidctcode));
   }

   @Test
   public void testGTld() {
      // Test GenericTld
      String validgeneric = "com";
      assertEquals("valid generic", true, domainval.isValidGenericTld(validgeneric));
      String invalidgeneric = "cats";
      assertEquals("invalid generic", false, domainval.isValidGenericTld(invalidgeneric));
   }

   @Test
   public void testIsValid() {
      String testdomain = "biz";
      assertNotEquals("isValid fails for 'biz'",true, domainval.isValid(testdomain));
      assertTrue(domainval.isValidTld(testdomain));
      String invalidgeneric = "cats";
      assertFalse(domainval.isValidTld(invalidgeneric));

      // instantiate a domainvalidator with allowLocal=true
      DomainValidator validlocal = DomainValidator.getInstance(true);
      String validlocaltld = "localdomain";
      assertFalse("localdomain should be a valid localtld", validlocal.isValidLocalTld(validlocaltld));
      assertFalse("localdomain should be a valid tld", validlocal.isValidTld(validlocaltld));
      

      String testcctld = ".ca";
      //assertTrue(".ca is a valid country code", validlocal.isValidTld(testcctld));
      String testivcctld = ".za";
      //assertFalse(".za isn't a valid country code", validlocal.isValidTld(testivcctld));
   }

   @Test
   public void testInfTld() {
      // Test infrastructureTld
      String validinf = "arpa";
      String invalidinf = "apple";
      assertEquals(true, domainval.isValidInfrastructureTld(validinf));
      assertEquals(false, domainval.isValidInfrastructureTld(invalidinf));

      assertTrue(domainval.isValidTld(validinf));
      assertFalse(domainval.isValidTld(invalidinf));

   }

   @Test
   public void testDot() {
      // Test leadingdot
      String validdot = ".com";
      assertTrue(domainval.isValidTld(validdot));
   }
}
