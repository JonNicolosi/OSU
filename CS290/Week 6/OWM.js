var btn = document.createElement("button");     // Create a <button> element
btn.id = "button";								// Declare btn's id
var t = document.createTextNode("Submit");      // Create a text node
btn.appendChild(t);                             // Append the text to <button>
document.body.appendChild(btn);                	// Append <button> to <body>

	var p1 = document.createElement("p");
	var p2 = document.createElement("p");
	var p3 = document.createElement("p");
	p1.id = "p1";
	p2.id = "p2";
	p3.id = "p3";
	var append1 = document.createTextNode("Temperature: ");
	var append2 = document.createTextNode("Pressure: ");
	var append3 = document.createTextNode("Humidity: ");
	p1.appendChild(append1);
	p2.appendChild(append2);
	p3.appendChild(append3);
	document.body.appendChild(p1);
	document.body.appendChild(p2);
	document.body.appendChild(p3);
	
var display = function(temperature, pressure, humidity){
	
	p1.appendChild(document.createTextNode(temperature.textContent));
	p2.appendChild(document.createTextNode(pressure.textContent));
	p3.appendChild(document.createTextNode(humidity.textContent));
	
}

var apiKey = "6576ef7b318585f726057569d71b36f6"

document.getElementById("button").addEventListener("click", function(){
    
	var city = document.getElementById("city").value;
	var zip = document.getElementById("zip").value;
	
	if(city==null || city==""){
	var req = new XMLHttpRequest();
	req.open('GET', "http://api.openweathermap.org/data/2.5/weather?q=" + zip + "&appid=" + apiKey, false);
	req.send(JSON.stringify(city));
	var response = JSON.parse(req.responseText);
	var temperature = document.createTextNode(response.main.temp);
	var pressure = document.createTextNode(response.main.pressure);
	var humidity = document.createTextNode(response.main.humidity);
	display(temperature, pressure, humidity);
	}
	else{
	var req = new XMLHttpRequest();
	req.open('GET', "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey, false);
	req.send(JSON.stringify(city));
	var response = JSON.parse(req.responseText);
	var temperature = document.createTextNode(response.main.temp);
	var pressure = document.createTextNode(response.main.pressure);
	var humidity = document.createTextNode(response.main.humidity);
	display(temperature, pressure, humidity);
	}
	
});


