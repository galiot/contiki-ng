var express = require('express');
var request = require('request');
var app = express();
var http = require('http').Server(app);

app.use(express.static('public'));

app.get('/', function(req, res){
    res.send('WebSense DB');
});

http.listen(3000, function(){
    console.log('listening on *:3000');
    console.log('websense db was started');
});

// function encryptDecrypt(input) {
//     // var key = ['K', 'C', 'Q']; //Can be any chars, and any size array
//     var key = ['K'];
// 	var output = [];
	
// 	for (var i = 0; i < input.length; i++) {

//         if ((input.charCodeAt(i) == '{') || (input.charCodeAt(i) == '}') || (input.charCodeAt(i) == ':') || (input.charCodeAt(i) == '\"') || (input.charCodeAt(i) == '.')) {
//             var charCode = input.charCodeAt(i);
//             output.push(String.fromCharCode(charCode));
//         }
//         else {
//             var charCode = input.charCodeAt(i) ^ key[i % key.length].charCodeAt(0);
// 		    output.push(String.fromCharCode(charCode));
//         }	
// 	}
// 	return output.join("");
// }

function encryptDecrypt(input) {
	var key = ['K', 'C', 'Q']; //Can be any chars, and any size array
	var output = [];
	
	for (var i = 0; i < input.length; i++) {
		var charCode = input.charCodeAt(i) ^ key[i % key.length].charCodeAt(0);
		output.push(String.fromCharCode(charCode));
	}
	return output.join("");
}

// blue
var dataPusher = setInterval(function () {

    request.get('http://[fd00::212:4b00:f83:b601]/',function(err,res,body){ 
        if(err){
            console.log(err);
            return;
        }
        
        var d = new Date(); // for now
        console.log(d);
        console.log("");
        console.log(body);
        console.log("");

        var decrypted = encryptDecrypt(body.toString());
        console.log("");
        console.log(decrypted);
        
        if(body){
            try {
                // var obj = JSON.parse(body);
                var obj = JSON.parse(decrypted);
                console.log("VALID JSON");
                console.log("");
                console.log(obj);
            } catch(e) {
                console.error("INVALID JSON");
                console.log("");
                console.error(e); // error in the above string (in this case, yes)!
                console.log("");
            }
        }

        
    });

    
}, 10000);