var httpbinbtn = document.createElement("button");     // Create a <button> element
httpbinbtn.id = "httpbinbtn";								// Declare btn's id
var x = document.createTextNode("Submit to HttpBin");      // Create a text node
httpbinbtn.appendChild(x);                             // Append the text to <button>
document.body.appendChild(httpbinbtn);                	// Append <button> to <body>

var p4 = document.createElement("p");
p4.id = "p4";
var append4 = document.createTextNode("Response: ");
p4.appendChild(append4);
document.body.appendChild(p4);

document.getElementById("httpbinbtn").addEventListener("click", function(){
	var sendText = document.getElementById("httpbinInputField").value;
	var req = new XMLHttpRequest();
	req.open('POST', "http://httpbin.org/post", true);
	req.setRequestHeader('Content-Type', 'application/json');
        req.addEventListener('load', function() {
            if(req.status >= 200 && req.status < 400) {
                var parsedJson = JSON.parse(req.responseText);
                var parsedText = JSON.stringify(parsedJson.json);
				console.log(parsedText);
                if(parsedText === 'null')
					p4.appendChild(document.createTextNode("Invalid JSON"));
                else
                    p4.appendChild(document.createTextNode(parsedText));
            }
        });
        req.send(sendText);
        event.preventDefault();
});