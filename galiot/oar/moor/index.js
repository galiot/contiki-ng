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

// blue
var dataPusher = setInterval(function () {

    request.get('http://[fd00::212:4b00:f83:b601]/',function(err,res,body){ 
        if(err){
            console.log(err);
            return;
        }
        
        console.log(body);
        console.log("ok");
        var obj = JSON.parse(body);
        console.log(obj);
    });

    
}, 10000);