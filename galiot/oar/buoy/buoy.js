//////////////////////////////
// galiot       (2018/2019) //
//////////////////////////////
// galiot/jib   (2018) ///////
// galiot/oar   (2019) ///////
// galiot/buoy  (2018/2019) //
// galiot/cargo (2019) ///////
// galiot/rope  (2019) /////// 
//////////////////////////////







const atob = require('atob');
const bodyParser = require("body-parser");
const cors = require("cors");
const express = require('express');
const helmet = require("helmet");
const mongoose = require("mongoose");
const mongoosePaginate = require('mongoose-paginate');

const morgan = require("morgan");
const sdbm = require('sdbm');







// configuration (logic config for development or production)
if(process.env.NODE_ENV === 'production') {

    // var PORT = null;
    // var MONGO_URI = null;
    // var MONGO_USER = null;
    // var MONGO_PASSWORD = null;
    
  } else {

    var PORT = process.env.PORT || 8080;
    var MONGO_URI = "mongodb://localhost:27017/cargo";
    var MONGO_USER = "galiot";
    var MONGO_PASSWORD = "eat_sleep_code_repeat";

  }


// create app using express
const app = express();














// With Mongoose, everything is derived from a Schema. 
// Let's get a reference to it and define our system.

var systemSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    system: {
        contikiVersion: String,
        networkStackRouting: String,
        networkStackNetwork: String,
        ieee802154PANID: String,
        networkStackMac: {
            name: String,
            tschDefaultHoppingSequence: Number,
            defaultChannel: Number
        },
        nodeId: Number,
        tentaticeLinkLocalIPv6address: String
    },
    checksum: Number
});

var deviceSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    device: {
        temperatureSensor: Number,
        humiditySensor: Number
    },
    checksum: Number
});

var energySchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    energy: {
        energest: Boolean,
        cpu: Number,
        lpm: Number,
        deepLpm: Number,
        totalTime: Number,
        radioListening: Number,
        radioTransmiting: Number,
        radioOff: Number
    },
    checksum: Number
});

var networkIpSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    networkIp: {
        uipStatistics: Boolean,
        ip: {
            ipRecv: Number,
            ipSent: Number,
            ipForwarded: Number,
            ipDrop: Number,    
            ipVhlerr: Number,  
            ipHblenerr: Number,
            ipLblenerr: Number,
            ipFragerr: Number, 
            ipChkerr: Number, 
            ipProtoerr: Number
        }
    },
    checksum: Number
});

var networkIcmpSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    networkIcmp: {
        uipStatistics: Boolean,
        icmp: {
            ipRecv: Number,    
            ipSent: Number,     
            ipForwarded: Number,
            ipDrop: Number,     
            ipVhlerr: Number  
        } 
    },
    checksum: Number
});

var transportSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    transport: {
        uipStatistics: Boolean,
        tcp: {
            tcp: Boolean,        
            tcpRecv: Number,    
            tcpSent: Number,    
            tcpDrop: Number,    
            tcpChkerr: Number,  
            tcpAckerr: Number,  
            tcpRst: Number,     
            tcpRexmit: Number,  
            tcpSyndrop: Number, 
            tcpSynrst: Number  
        },
        udp: {
            udp: Boolean,  
            tcpDrop: Number,
            tcpRecv: Number,  
            tcpSent: Number,  
            tcpChkerr: Number
        } 
    },
    checksum: Number
});

var discoverySchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    moteId: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    discovery: {
        uipStatistics: Boolean,
        nd6: {
            nd6drop: Number,
            nd6recv: Number,
            nd6sent: Number
        } 
    },
    checksum: Number
});




// next step is compiling our schema into a Model.

var System      = mongoose.model('System',      systemSchema);
var Device      = mongoose.model('Device',      deviceSchema);
var Energy      = mongoose.model('Energy',      energySchema);
var NetworkIp   = mongoose.model('NetworkIp',   networkIpSchema);
var NetworkIcmp = mongoose.model('NetworkIcmp', networkIcmpSchema);
var Transport   = mongoose.model('Transport',   transportSchema);
var Discovery   = mongoose.model('Discovery',   discoverySchema);






















// The first thing we need to do is include mongoose in our project 
// and open a connection to the test database on our locally running instance of MongoDB.

// Connect to the MongoDB
mongoose.connect(MONGO_URI, {user: MONGO_USER, pass: MONGO_PASSWORD, useNewUrlParser: true}).then(
    () => console.log('connected to Cargo'),
    (err) => console.log(err)
)

// We have a pending connection to the test database running on localhost. 
// We now need to get notified if we connect successfully or if a connection error occurs:

const db = mongoose.connection;

db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function() {
    
    // we're connected!
});















// secure express apps: protect the express app with various HTTP Header Protection)
app.use(helmet());

// filter and setting the allowed origin that can access the server
const corsOptions = {origin: true, credentials: true};
app.use(cors(corsOptions));

// parsing body request to json
app.use(bodyParser.json());

// HTTP request logger with Morgan
app.use(morgan("dev"));










const request = require('request');
var http = require('http').Server(app);


app.get('/', function(req, res){
    res.send('BUOY');
});

app.listen(PORT, function() {
    console.log('buoy (listening on port: ' + PORT + ')');
})







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

    request.get('http://[fd00::212:4b00:f83:b601]/',function(err, res, body ){ 
        
    if(err) {
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
                console.log("JSON: VALID");
                console.log("");
                console.log(obj);
                
                
                // how to check the hash:
                // get the hash value from JSON
                // remove the "hash" keypair from JSON
                // stringify the JSON
                // remove last character '}'
                // concatenate a comma ','
                // calculate the hash of the string
                // check with original hash value
                let hash = obj.hash;
                // console.log("");
                // console.log(hash);
                // console.log("");
                let goa = obj;
                // console.log(goa);
                // console.log("");
                delete goa.hash;
                // console.log(goa);
                // console.log("");
                goa = JSON.stringify(goa);
                // console.log(goa);
                // console.log("");
                // console.log(goa.length);
                // console.log("");
                // console.log(sdbm (goa.substr(0, goa.length -1) + "," ));
                console.log("");
                console.log( (sdbm(goa.substr(0, goa.length -1) + "," )) == hash ? "HASH CHECK: SUCCESS" : "HASH CHECK: FAIL" );

                if (obj.pckt.vld == true) {

                    switch(obj.ndx) {

                        case 0: 
                            var system = new System({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                system: {
                                    contikiVersion: obj.sys.cV,
                                    networkStackRouting: obj.sys.rt,
                                    networkStackNetwork: obj.sys.net,
                                    ieee802154PANID: obj.sys.pId,
                        
                                    networkStackMac: {
                                        name: obj.sys.mac.t,
                                        tschDefaultHoppingSequence: obj.sys.mac.tDhS,
                                        defaultChannel: obj.sys.mac.dCh
                                    },
                                    nodeId: obj.sys.nId,
                                    tentaticeLinkLocalIPv6address: obj.sys.tIad
                                },
                                checksum: obj.hash
                            });
        
                            system.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > system COLLECTION`);
                            });

                            break;
                        
                        case 1:
                            var device = new Device({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                device: {
                                    temperatureSensor: obj.dev.tp,
                                    humiditySensor: obj.dev.hd
                                },
                                checksum: obj.hash
                            })

                            device.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > device COLLECTION`);
                            });

                            break;
                        
                        case 2:
                            var energy = new Energy({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                energy: {
                                    energest: obj.nrg.en,
                                    cpu: obj.nrg.cp,
                                    lpm: obj.nrg.lp,
                                    deepLpm: obj.nrg.dL,
                                    totalTime: obj.nrg.tT,
                                    radioListening: obj.nrg.rL,
                                    radioTransmiting: obj.nrg.rT,
                                    radioOff: obj.nrg.r0
                                },
                                checksum: obj.hash
                            })

                            energy.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > energy COLLECTION`);
                            });

                            break;
                        
                        case 3:
                            var networkIp = new NetworkIp({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                networkIp: {
                                    uipStatistics: obj.ipSt.uS,
                                    ip: {
                                        ipRecv: obj.ipSt.ip.rx,
                                        ipSent: obj.ipSt.ip.tx,
                                        ipForwarded: obj.ipSt.ip.fw,
                                        ipDrop: obj.ipSt.ip.dr,    
                                        ipVhlerr: obj.ipSt.ip.vE,  
                                        ipHblenerr: obj.ipSt.ip.hE,
                                        ipLblenerr: obj.ipSt.ip.lE,
                                        ipFragerr: obj.ipSt.ip.fE, 
                                        ipChkerr: obj.ipSt.ip.cE, 
                                        ipProtoerr: obj.ipSt.ip.pE
                                    }
                                },
                                checksum: obj.hash
                            })

                            networkIp.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > networkIp COLLECTION`);
                            });

                            break;
                        
                        case 4:
                            var networkIcmp = new NetworkIcmp({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                networkIcmp: {
                                    uipStatistics: obj.icSt.uS,
                                    icmp: {
                                        ipRecv: obj.icSt.ic.rx,    
                                        ipSent: obj.icSt.ic.tx,     
                                        ipForwarded: obj.icSt.ic.dr,
                                        ipDrop: obj.icSt.ic.tE,     
                                        ipVhlerr: obj.icSt.ic.cE  
                                    } 
                                },
                                checksum: obj.hash
                            })

                            networkIcmp.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > networkIcmp COLLECTION`);
                            });

                            break;
                        
                        case 5:
                            var transport = new Transport({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                transport: {
                                    uipStatistics: obj.tSt.uS,
                                    tcp: {
                                        tcp: obj.tSt.tcp.use,        
                                        tcpRecv: obj.tSt.tcp.rx,    
                                        tcpSent: obj.tSt.tcp.tx,    
                                        tcpDrop: obj.tSt.tcp.dr,    
                                        tcpChkerr: obj.tSt.tcp.cE,  
                                        tcpAckerr: obj.tSt.tcp.aA,  
                                        tcpRst: obj.tSt.tcp.rst,     
                                        tcpRexmit: obj.tSt.tcp.rM,  
                                        tcpSyndrop: obj.tSt.tcp.sD, 
                                        tcpSynrst: obj.tSt.tcp.sR  
                                    },
                                    udp: {
                                        udp: obj.tSt.udp.use,  
                                        tcpDrop: obj.tSt.udp.dr,
                                        tcpRecv: obj.tSt.udp.rx,  
                                        tcpSent: obj.tSt.udp.tx,  
                                        tcpChkerr: obj.tSt.udp.cE
                                    } 
                                },
                                checksum: obj.hash
                            })

                            transport.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > transport COLLECTION`);
                            });

                            break;

                        case 6:
                            var discovery = new Discovery({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                moteId: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                discovery: {
                                    uipStatistics: obj.dSt.uS,
                                    nd6: {
                                        nd6drop: obj.dSt.nd6.dr,
                                        nd6recv: obj.dSt.nd6.rx,
                                        nd6sent: obj.dSt.nd6.tx
                                    } 
                                },
                                checksum: obj.hash
                            })

                            discovery.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`DOCUMENT (RECORD: ${obj.rcrd}) --> cargo DB > discovery COLLECTION`);
                            });

                            break;
                        
                        


                    }


                } else {
                    console.log('ERROR JSON RECIEVED');
                }
                
                
    









            } catch(e) {
                console.log("");
                console.error("JSON: INVALID");
                console.log("");
                console.error(e); // error in the above string (in this case, yes)!
                console.log("");
            }
        }
    });

    
}, 5000);