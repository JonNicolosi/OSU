package osu.cs362.URLValidator;

import java.util.*;
import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.Before;

public class InetAddressValidatorTest {
	
	InetAddressValidator IAV;
	
	@Before
	public void init(){
		IAV = InetAddressValidator.getInstance();
		
	}
	
	@Test
	public void isValidInet4AddressTest() {
	   
	assertTrue("68.199.224.252 is a real IP. This should return true.",IAV.isValidInet4Address("68.199.224.252"));
	assertTrue("999.999.999.999 is not a real IP. This should return error.",IAV.isValidInet4Address("999.999.999.999"));

	}
   
   
	@Test
	public void isValidTest(){
	   
	assertTrue("68.199.224.252 is a real IP. This should return true.",IAV.isValid("68.199.224.252"));
	assertTrue("999.999.999.999 is not a real IP. This should return error.",IAV.isValid("999.999.999.999"));
	assertFalse("Illegal subgroup. Should return error", IAV.isValid("blah.blah.blah.blah"));
	
	
	}
   
   
}
