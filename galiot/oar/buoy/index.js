var express = require('express');
var request = require('request');
var app = express();
var http = require('http').Server(app);
var atob = require('atob');

app.use(express.static('public'));

app.get('/', function(req, res){
    res.send('WebSense DB');
});

http.listen(3000, function(){
    console.log('MOOR MIDDLEWARE > PORT 3000');
});

function oarCrypt(input) {
	var key = ['!', '@', '#', '$', '%', '^', '&', '*'];
    var output = [];
	
	for (var i = 0; i < input.length; i++) {
		var charCode = input.charCodeAt(i) ^ (key[i % key.length].charCodeAt(0));
		output.push(String.fromCharCode(charCode));
	}
	return output.join("");
}

// yellow:  fd00::212:4b00:f24:8385
// red:     fd00::212:4b00:f83:b601
// green:   fd00::212:4b00:f82:a600
// blue:    fd00::212:4b00:f82:da03

var dataPusher = setInterval(function () {

    request.get('http://[fd00::212:4b00:f83:b601]/',function(err,res,body){ 
        if(err){
            console.log(err);
            return;
        }
        
        console.log("");
        var d = new Date(); // for now
        console.log(d);
        console.log("");
        console.log(body);
        console.log("");

        var decoded = atob(body.toString());
        console.log("");
        console.log(decoded);

        // var decrypted = oarCrypt(body.toString());
        var decrypted = oarCrypt(decoded);
        
        console.log("");
        console.log(decrypted);
        
        if(body){
            try {
                var obj = JSON.parse(decrypted);
                console.log("");
                console.log("VALID JSON");
                console.log("");
                console.log(obj);
            } catch(e) {
                console.log("");
                console.error("INVALID JSON");
                console.log("");
                console.error(e); // error in the above string (in this case, yes)!
                console.log("");
            }
        }
    });

    
}, 5000);