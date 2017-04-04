<!DOCTYPE html>
<html>
<head>
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<!-- jQuery library -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

<!-- Latest compiled JavaScript -->
<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<link rel="stylesheet" type="text/css" href="style.css">
</head>



<div class="jumbotron">
  <h1>Fantasy Team Creator</h1>
  <p>Fantasy Team Creator allows you to query statistics about current NBA players and add them to a fantasy roster.</p>
</div>

<div>

1. Choose a search option from the list below. 
<br>2. Press enter to submit query. 
<br>3. Check the boxes of the players you want to add to your team. 
<br>4. Press submit.
<br>You will see the players you've selected populate in the panel entitled "Fantasy Team".
<br></br>

Try searching for "Duke" to pull up all current NBA players that graduated from Duke University.
<br>Or search for "Knicks" to pull up all players on the current Knicks roster.
<br>Or search for "MVP" to pull up all players who have ever won an MVP.
<br></br>

</div>

<div class="dropdown">
  <button class="btn btn-primary dropdown-toggle" type="button" data-toggle="dropdown">Search By
  <span class="caret"></span></button>
  <ul class="dropdown-menu">
  
    <li><a href="#" onclick="teamfunction()">By Team</a></li>
    <li><a href="#" onclick="collegefunction()">By College</a></li>
	<li><a href="#" onclick="accoladefunction()">By Accolade</a></li>

  </ul>
</div>

<form action="index.php" method="post">
<div id = "byteam" class="form-group">

</div>
</form>


<form action="index.php" method="post">
<div id = "bycollege" class="form-group"></div>
</form>


<form action="index.php" method="post">
<div id = "byaccolade" class="form-group"></div>
</form>

<script>

function teamfunction() {
    document.getElementById("byteam").innerHTML = '<label for="usr">Team:</label><input type="text" class="form-control" id="usr" name="teamphp">';
}


function collegefunction() {
    document.getElementById("bycollege").innerHTML = '<label for="usr">College:</label><input type="text" class="form-control" id="usr" name="collegephp">';
}

function accoladefunction() {
    document.getElementById("byaccolade").innerHTML = '<label for="usr">Accolade:</label><input type="text" class="form-control" id="usr" name="accoladephp">';
}


</script>



<form action="#" method="post">

<div>
<?php  

if(isset($_POST['teamphp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$team  = $_POST['teamphp'];

	

	$sqlsearchbyteam = "SELECT players.id, players.firstname, players.lastname, players.college, players.team, team.coach, coaches.regrecord, coaches.playrecord FROM players JOIN team ON players.team = team.name JOIN coaches ON team.coach = coaches.name WHERE team LIKE '%" .$team. "%' AND team.season='2015-16'";
	$teamresult = mysqli_query($dbConnection, $sqlsearchbyteam);
		
	if(mysqli_fetch_assoc($teamresult)){
		echo '<table class="table table-hover">';
		echo '<thead>
		<tr><th>Select</th><th>First Name</th><th>Last Name</th><th>Team</th><th>Coach</th><th>Coach Regular Season Record</th><th>Coach Playoff Record</th></tr></thead>';
		echo '<tbody>';
		
	
		while($bleh = mysqli_fetch_assoc($teamresult)){
				
				echo '<tr>';
				echo '<td>';
				echo '<div class="checkbox">';
				echo '<label><input type="checkbox" name = "team_array[]" value="'.$bleh["id"].'">';
				echo '</td>';				
				echo '<td>';
				echo $bleh["firstname"];
				echo '</td>';
				echo '<td>';
				echo $bleh["lastname"];
				echo '</td>';
				echo '<td>';
				echo $bleh["team"];
				echo '</td>';
				echo '<td>';
				echo $bleh["coach"];
				echo '</td>';
				echo '<td>';
				echo $bleh["regrecord"];
				echo '</td>';
				echo '<td>';
				echo $bleh["playrecord"];
				echo '</td>';
		}
		
	}
	else {
		echo "0 results";
	}	
	echo '</tbody>';
	echo '</table>';
	echo '</div>';

	
}


?>
</div>



<div>

<?php 

	if(isset($_POST['collegephp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$college  = $_POST['collegephp'];

	

	$sqlsearchbycollege = "SELECT players.id, players.firstname, players.lastname, players.college, players.team, team.coach, coaches.regrecord, coaches.playrecord FROM players JOIN team ON players.team = team.name JOIN coaches ON team.coach = coaches.name WHERE college LIKE '%" .$college. "%' AND team.season='2015-16'";
	$collegeresult = mysqli_query($dbConnection, $sqlsearchbycollege);
		
	if(mysqli_fetch_assoc($collegeresult)){
		echo '<table class="table table-hover">';
		echo '<thead>
		<tr><th>Select</th><th>First Name</th><th>Last Name</th><th>Team</th><th>Coach</th><th>Coach Regular Season Record</th><th>Coach Playoff Record</th></tr></thead>';
		echo '<tbody>';
		
	
		while($blah = mysqli_fetch_assoc($collegeresult)){
				echo '<tr>';
				echo '<td>';
				echo '<div class="checkbox">';
				echo '<label><input type="checkbox" name = "college_array[]" value="'.$blah["id"].'">';
				echo '</td>';				
				echo '<td>';
				echo $blah["firstname"];
				echo '</td>';
				echo '<td>';
				echo $blah["lastname"];
				echo '</td>';
				echo '<td>';
				echo $blah["team"];
				echo '</td>';
				echo '<td>';
				echo $blah["coach"];
				echo '</td>';
				echo '<td>';
				echo $blah["regrecord"];
				echo '</td>';
				echo '<td>';
				echo $blah["playrecord"];
				echo '</td>';
				echo '<td>';
				echo $blah["award"];
				echo '</td>';
		}
		
	}
	else {
		echo "0 results";
	}	
	echo '</tbody>';
	echo '</table>';
	echo '</div>';

	
}


?>

</div>

<div>

<?php 

	if(isset($_POST['accoladephp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$accolade  = $_POST['accoladephp'];

	

	$sqlsearchbyaccolade = "SELECT accolades.id, accolades.firstname, accolades.lastname, accolades.season, accolades.award FROM accolades WHERE award LIKE '%" .$accolade. "%' ";
	$accoladeresult = mysqli_query($dbConnection, $sqlsearchbyaccolade);
		
	if(mysqli_fetch_assoc($accoladeresult)){
		echo '<table class="table table-hover">';
		echo '<thead>
		<tr><th>Select</th><th>First Name</th><th>Last Name</th><th>Season</th><th>Award Earned</th></tr></thead>';
		echo '<tbody>';
		
	
		while($darn = mysqli_fetch_assoc($accoladeresult)){
				echo '<tr>';
				echo '<td>';
				echo '<div class="checkbox">';
				echo '<label><input type="checkbox" name = "accolade_array[]" value="'.$darn["id"].'">';
				echo '</td>';				
				echo '<td>';
				echo $darn["firstname"];
				echo '</td>';
				echo '<td>';
				echo $darn["lastname"];
				echo '</td>';
				echo '<td>';
				echo $darn["season"];
				echo '</td>';
				echo '<td>';
				echo $darn["award"];
				echo '</td>';
		}
		
	}
	else {
		echo "0 results";
	}	
	echo '</tbody>';
	echo '</table>';
	echo '</div>';

	
}


?>

</div>




<input type="submit" name="submit2" value="Add Player(s) to Roster" class="btn btn-primary">
</form>





<br></br>



<?php
		
		if(isset($_POST['submit2'])){
			if(!empty($_POST['college_array'])){
			
				foreach($_POST['college_array'] as $selected2){
				$dbHost = 'oniddb.cws.oregonstate.edu';
				$dbName = 'nicolosj-db';
				$dbUserName = 'nicolosj-db';
				$dbPassword = 'ViEUlekIRBrslSgM';
			
				$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}
					$sqlinsertchecked = "INSERT INTO fantasy (fantasy.id, fantasy.firstname, fantasy.lastname, fantasy.team) SELECT players.id, players.firstname, players.lastname, players.team FROM players WHERE id = '".$selected2."'";
					mysqli_query($dbConnection, $sqlinsertchecked);
					
				}
			}
			else if(!empty($_POST['team_array'])){
			foreach($_POST['team_array'] as $selected2){
				$dbHost = 'oniddb.cws.oregonstate.edu';
				$dbName = 'nicolosj-db';
				$dbUserName = 'nicolosj-db';
				$dbPassword = 'ViEUlekIRBrslSgM';
			
				$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}
					$sqlinsertchecked = "INSERT INTO fantasy (fantasy.id, fantasy.firstname, fantasy.lastname, fantasy.team) SELECT players.id, players.firstname, players.lastname, players.team FROM players WHERE id = '".$selected2."'";
					mysqli_query($dbConnection, $sqlinsertchecked);
					
				}
			
			
			
			}
			else if(!empty($_POST['accolade_array'])){
			foreach($_POST['accolade_array'] as $selected2){
			
			
				$dbHost = 'oniddb.cws.oregonstate.edu';
				$dbName = 'nicolosj-db';
				$dbUserName = 'nicolosj-db';
				$dbPassword = 'ViEUlekIRBrslSgM';
			
				$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
				if($dbConnection->connect_errno){
					echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
				} 	
				else {
					#echo "Connection to Database established!";
				}
					$sqlinsertchecked = "INSERT INTO fantasy (fantasy.id, fantasy.firstname, fantasy.lastname) SELECT accolades.id, accolades.firstname, accolades.lastname FROM accolades WHERE id = '".$selected2."'";
					mysqli_query($dbConnection, $sqlinsertchecked);
				}
		

			}
	}
		

?>

		
<br></br>
<br></br>






<div class="dropdown">
  <button class="btn btn-primary dropdown-toggle" type="button" data-toggle="dropdown">Add Arbitrary Values To Tables
  <span class="caret"></span></button>
  <ul class="dropdown-menu">
  
    <li><a href="#" onclick="addtoplayers()">Players Table</a></li>
    <li><a href="#" onclick="addtoteam()">Team Table</a></li>
	<li><a href="#" onclick="addtocoaches()">Coaches Table</a></li>
	<li><a href="#" onclick="addtoaccolades()">Accolades Table</a></li>
  </ul>
</div>



<script>

function addtoplayers() {
    document.getElementById("ATP").innerHTML = '<label for="usr">Player:</label><input type="text" class="form-control" id="usr" name="atpphp">';
}

function addtoteam() {
    document.getElementById("ATT").innerHTML = '<label for="usr">Team:</label><input type="text" class="form-control" id="usr" name="attphp">';
}

function addtocoaches() {
    document.getElementById("ATC").innerHTML = '<label for="usr">Coach:</label><input type="text" class="form-control" id="usr" name="atcphp">';
}

function addtoaccolades() {
    document.getElementById("ATA").innerHTML = '<label for="usr">Accolade:</label><input type="text" class="form-control" id="usr" name="ataphp">';
}


</script>
		


<form action="index.php" method="post">
<div id = "ATP" class="form-group"></div>		
		
<?php
if(isset($_POST['atpphp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$atpphp  = $_POST['atpphp'];

	

	$insertATPPHP = "INSERT INTO players (players.lastname) VALUES ('".$atpphp."')";
	$atpphpResult = mysqli_query($dbConnection, $insertATPPHP) or die("Could Not Insert Value");
	echo '<br><p class="bg-success">Insertion Successfull</p></br>';
}

?>		
		

</form>
		

		
<form action="index.php" method="post">
<div id = "ATT" class="form-group"></div>		
		
<?php
if(isset($_POST['attphp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$attphp  = $_POST['attphp'];

	

	$insertATTPHP = "INSERT INTO team (team.name) VALUES ('".$attphp."')";
	$attphpResult = mysqli_query($dbConnection, $insertATTPHP) or die("Could Not Insert Value");
	echo '<br><p class="bg-success">Insertion Successfull</p></br>';
}

?>		
		

</form>


<form action="index.php" method="post">
<div id = "ATC" class="form-group"></div>		
		
<?php
if(isset($_POST['atcphp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$atcphp  = $_POST['atcphp'];

	

	$insertATCPHP = "INSERT INTO coaches (coaches.name) VALUES ('".$atcphp."')";
	$atcphpResult = mysqli_query($dbConnection, $insertATCPHP) or die("Could Not Insert Value");
	echo '<br><p class="bg-success">Insertion Successfull</p></br>';
}

?>		
		

</form>

<form action="index.php" method="post">
<div id = "ATA" class="form-group"></div>		
		
<?php
if(isset($_POST['ataphp'])){


	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$ataphp  = $_POST['ataphp'];

	

	$insertATAPHP = "INSERT INTO accolades(accolades.award) VALUES ('".$ataphp."')";
	$ataphpResult = mysqli_query($dbConnection, $insertATAPHP) or die("Could Not Insert Value");
	echo '<br><p class="bg-success">Insertion Successfull</p></br>';
}

?>		
		

</form>

		
<br></br>

<div>
<?php

	$dbHost = 'oniddb.cws.oregonstate.edu';
	$dbName = 'nicolosj-db';
	$dbUserName = 'nicolosj-db';
	$dbPassword = 'ViEUlekIRBrslSgM';
			
			$dbConnection = new mysqli($dbHost, $dbUserName, $dbPassword, $dbName);
			if($dbConnection->connect_errno){
				echo "Connection error " . $dbConnection->connect_errno . " " . $dbConnection->connect_error;
			} else {
				#echo "Connection to Database established!";
			}

	$displayFantasy = "SELECT * FROM fantasy";
	$fantasyresult = mysqli_query($dbConnection, $displayFantasy);
	
	echo '<div class="panel panel-primary">
			<div class="panel-heading">Fantasy Team</div>
				<div class="panel-body">';
	if (mysqli_num_rows($fantasyresult) > 0) {
			// output data of each row
			
			echo '<table class="table table-hover">';
			echo '<thead>
			<tr>
			<th>First Name</th>
			<th>Last Name</th>
			<th>Team</th>
			</tr>
			</thead>';
			echo '<tbody>';
			while($acme = mysqli_fetch_assoc($fantasyresult)) {
				
				echo '<tr>';
				echo '<td>';
				echo $acme["firstname"];
				echo '</td>';
				echo '<td>';
				echo $acme["lastname"];
				echo '</td>';
				echo '<td>';
				echo $acme["team"];
				echo '</td>';
				echo '<td>';
				echo '<form action="index.php" method = "post">
<input type="submit" name="'.$acme["id"].'" value="Delete" class="btn btn-danger">
</form>';
				echo '</td>';
				echo '</tr>';
				if (isset($_POST[$acme["id"]]))
				{	
				
					$deletequery = "DELETE FROM fantasy WHERE id = '".$acme["id"]."'";
					$deleteresult = mysqli_query($dbConnection, $deletequery);
					echo '<script>location.reload();</script>';
					
				}
				
				
			}
		echo '</tbody>';
		echo '</table>';
	}
	
?>
</div>
</div>
</div>



</html>