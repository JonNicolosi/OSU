# How to run code and tests:
## Note: If you do not have ‘mvn’ configured to indicate the path to which Maven is installed, replace ‘mvn’ with the path to where you’ve installed Maven.

## To run basic tests:
	mvn clean
	mvn compile test

## To run PIT mutations:
	mvn org.pitest:pitest-maven:mutationCoverage

## You can find the current PIT reports here:
http://web.engr.oregonstate.edu/~nicolosj/report/pit-reports/

## You can find the current Cobertura coverage here:
http://web.engr.oregonstate.edu/~nicolosj/report/cobertura/

## If you choose to recompile the cobertura coverage:
	mvn compile test
  	mvn clean
	mvn cobertura:clean cobertura:cobertura
  	./deploy
	
  	Note: Cobertura coverage often takes a while to update, so it may be helpful to do one of the following if results do not update: 
		Clear your cache
		Use a different browser
	  	If you’re using Chrome: open in an incognito window.
