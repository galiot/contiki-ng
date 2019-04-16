/////////////////////////////////////////////
// galiot   (2018/2019) /////////////////////
/////////////////////////////////////////////
// jib      (2018) /////// backend (light) //
// oar      (2019) /////// backend (heavy) //
// -------------------- // --------------- //
// buoy     (2018/2019) // middleware ///////
// bridge   (2019) /////// frontend /////////
// cargo    (2019) /////// database /////////
/////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// require() //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const atob = require('atob');
const bodyParser = require("body-parser");
const cors = require("cors");
const express = require('express');
const helmet = require("helmet");
const mongoose = require("mongoose");
const mongoosePaginate = require('mongoose-paginate');

const morgan = require("morgan");
const sdbm = require('sdbm');

// create app using express
const app = express();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MONGODB CREDENTIALS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MONGOOSE SCHEMAS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// With Mongoose, everything is derived from a Schema. 
// Let's get a reference to it and define our system.

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var systemSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
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
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var deviceSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    device: {
        temperatureSensor: Number,
        humiditySensor: Number
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var energySchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
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
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var networkIpSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
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
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var networkIcmpSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
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
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var transportSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
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
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var discoverySchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
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
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var nodeIPv6ddressSchema = new mongoose.Schema({
    nodeIPv6address: String
});

var ipAddrSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    ipAddr: {
        ipv6: Boolean,
        nodeIPv6addresses: [nodeIPv6ddressSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var nodeIPv6neighborIpAddressSchema = new mongoose.Schema({
    nodeIPv6neighborIpAddress: String
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var ipNeighborsIpAddrSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    ipNeighborsIpAddr: {
        ipv6: Boolean,
        nodeIPv6neighborIpAddresses: [nodeIPv6neighborIpAddressSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var nodeIPv6neighborLlAddressSchema = new mongoose.Schema({
    nodeIPv6neighborLlAddress: String
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var ipNeighborsLlAddrSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    ipNeighborsLlAddr: {
        ipv6: Boolean,
        nodeIPv6neighborLlAddresses: [nodeIPv6neighborLlAddressSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var nodeIPv6neighborInfoSchema = new mongoose.Schema({
    nodeIPv6neighborRouter: Number,
    nodeIPv6neighborState: String
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var ipNeighborsInfoSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    ipNeighborsInfo: {
        ipv6: Boolean,
        nodeIPv6neighborInfo: [nodeIPv6neighborInfoSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var routeSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    route: {
        ipv6: Boolean,
        defaultRoute: String,
        lifetime: mongoose.Schema.Types.Mixed
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var linkSourceSchema = new mongoose.Schema({
    linkSourceAddr: String,
    dodagRoot: Boolean
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var routingLinksSourcesSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    routingLinksSources: {
        ipv6: Boolean,
        rpl: Boolean,
        totalRoutingLinks: Number,
        routeSources: [linkSourceSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var linkDestinationSchema = new mongoose.Schema({
    linkDestinationAddr: String,
    lifetime: mongoose.Schema.Types.Mixed
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var routingLinksDestinationsSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    routingLinksDestinations: {
        ipv6: Boolean,
        rpl: Boolean,
        totalRoutingLinks: Number,
        routeDestinations: [linkDestinationSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var entryRouteSchema = new mongoose.Schema({
    entryRouteAddr: String
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var routingEntriesRoutesSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    routingEntriesRoutes: {
        ipv6: Boolean,
        maxRoutesNon0: Boolean,
        totalRoutingEntries: Number,
        routes: [entryRouteSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var entryViaSchema = new mongoose.Schema({
    entryViaAddr: String,
    lifetime: mongoose.Schema.Types.Mixed
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var routingEntriesViasSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    routingEntriesVias: {
        ipv6: Boolean,
        maxRoutesNon0: Boolean,
        totalRoutingEntries: Number,
        vias: [entryViaSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplStatusSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplStatus: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        modeOfOperation: String,
        objectiveCodePoint: String,
        hopRankIncrement: Number,
        defaultLifetime: mongoose.Schema.Types.Mixed,
        dtsnOut: Number
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplStatusDagSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplStatusDag: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        dagRole: String,
        dagId: String,
        dagPrefix: String,
        dagPrefixLength: Number,
        dagPreferedParent: String,
        dagState: String,
        dagRank: Number,
        dagLowestRank: Number,
        maxRankIncrement: Number,
        dao: {
            daoSequenceLastSent: Number,
            daoSequenceLastAcked: Number
        }
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplStatusTrickleTimerSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplStatusTrickleTimer: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        current: Number,
        min: Number, 
        max: Number,
        redundancy: Number
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplAddressSchema = new mongoose.Schema({
    rplAddress: String
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplNeighborAddrSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplNeighborAddr: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        rplNeighborCount: Number,
        addresses: [rplAddressSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplRanksSchema = new mongoose.Schema({
    rplNeighborRank: Number,
    rplNeighborLinkMetric: Number,
    rplNeighborRankViaNeighbor: Number
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplNeighborRanksSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplNeighborRanks: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        rplNeighborCount: Number,
        ranks: [rplRanksSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplValuesSchema = new mongoose.Schema({
    rplNeighborStatsFreshness: Number,
    rplNeighborRootRank: Boolean,
    rplNeighborBest: Boolean,
    rplNeighborAcceptableRankParent: Boolean,
    rplNeighborLinkStatsFresh: Boolean,
    rplNeighborDagPreferredParent: Boolean,
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplNeighborValuesSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplNeighborValues: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        rplNeighborCount: Number,
        values: [rplValuesSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplParensSchema = new mongoose.Schema({
    rplNeighborLastTXtimeSeconds: Number,
    rplNeighborBetterParentSinceSeconds: Number
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var rplNeighborParensSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: String
    },
    record: Number,
    index: Number,
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    rplNeighborParens: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        rplNeighborCount: Number,
        parens: [rplParensSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var errorPacketSchema = new mongoose.Schema({
    packet: {
        valid: Boolean,
        error: {
            text: String,
            code: Number
        }
    },
    mote: {
        systemTime: Number,
        linkLayerAddress: String,
        moteCode: String
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MONGOOSE MODELS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// next step is compiling our schema into a Model.

var System                      = mongoose.model('System',                      systemSchema);
var Device                      = mongoose.model('Device',                      deviceSchema);
var Energy                      = mongoose.model('Energy',                      energySchema);
var NetworkIp                   = mongoose.model('NetworkIp',                   networkIpSchema);
var NetworkIcmp                 = mongoose.model('NetworkIcmp',                 networkIcmpSchema);
var Transport                   = mongoose.model('Transport',                   transportSchema);
var Discovery                   = mongoose.model('Discovery',                   discoverySchema);

var NodeIPv6address             = mongoose.model('NodeIPv6addres',              nodeIPv6ddressSchema);
var IpAddr                      = mongoose.model('IpAddr',                      ipAddrSchema);

var NodeIPv6neighborIpAddress   = mongoose.model('NodeIPv6neighborIpAddress',   nodeIPv6neighborIpAddressSchema);
var IpNeighborsIpAddr           = mongoose.model('IpNeighborsIpAddr',           ipNeighborsIpAddrSchema);

var NodeIPv6neighborLlAddress   = mongoose.model('NodeIPv6neighborLlAddress',   nodeIPv6neighborLlAddressSchema);
var IpNeighborsLlAddr           = mongoose.model('IpNeighborsLlAddr',           ipNeighborsLlAddrSchema);

var NodeIPv6neighborInfo        = mongoose.model('NodeIPv6neighborInfo',        nodeIPv6neighborInfoSchema);
var IpNeighborsInfo             = mongoose.model('IpNeighborsInfo',             ipNeighborsInfoSchema);

var Route                       = mongoose.model('Route',                       routeSchema);

var LinkSource                  = mongoose.model('LinkSource',                  linkSourceSchema);
var RoutingLinksSources         = mongoose.model('RoutingLinksSources',         routingLinksSourcesSchema);

var LinkDestination             = mongoose.model('LinkDestination',             linkDestinationSchema);
var RoutingLinksDestinations    = mongoose.model('RoutingLinksDestinations',    routingLinksDestinationsSchema);

var EntryRoute                  = mongoose.model('EntryRoute',                  entryRouteSchema);
var RoutingEntriesRoutes        = mongoose.model('RoutingEntriesRoutes',        routingEntriesRoutesSchema);

var EntryVia                    = mongoose.model('EntryVia',                    entryViaSchema);
var RoutingEntriesVias          = mongoose.model('RoutingEntriesVias',          routingEntriesViasSchema);

var RplStatus                   = mongoose.model('RplStatus',                   rplStatusSchema);
var RplStatusDag                = mongoose.model('RplStatusDag',                rplStatusDagSchema);
var RplStatusTrickleTimer       = mongoose.model('RplStatusTrickleTimer',       rplStatusTrickleTimerSchema);

var RplAddress                  = mongoose.model('RplAddress',                  rplAddressSchema);
var RplNeighborAddr             = mongoose.model('RplNeighborAddr',             rplNeighborAddrSchema);

var RplRanks                    = mongoose.model('RplRanks',                    rplRanksSchema);
var RplNeighborRanks            = mongoose.model('RplNeighborRanks',            rplNeighborRanksSchema);

var RplValues                   = mongoose.model('RplValues',                   rplValuesSchema);
var RplNeighborValues           = mongoose.model('RplNeighborValues',           rplNeighborValuesSchema);

var RplParens                   = mongoose.model('RplParens',                   rplParensSchema);
var RplNeighborParens           = mongoose.model('RplNeighborParens',           rplNeighborParensSchema);

var ErrorPacket                = mongoose.model('ErrorPacket',                  errorPacketSchema);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MONGOOSE CONNECTION ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The first thing we need to do is include mongoose in our project 
// and open a connection to the test database on our locally running instance of MongoDB.

// Connect to the MongoDB
mongoose.connect(MONGO_URI, {user: MONGO_USER, pass: MONGO_PASSWORD, useNewUrlParser: true}).then(
    () => {
        console.log("");
        console.log('+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-');
        console.log('connected to cargo (mongodb://localhost:27017/cargo)');
        console.log('+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-');
    },
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











var http = require('http').Server(app);


app.get('/', function(req, res){
    res.send('BUOY');
});

app.listen(PORT, function() {
    console.log("");
    console.log('~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~');
    console.log('buoy (listening on port: ' + PORT + ')');
    console.log('~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~');
})





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ENCRYTION/DECRYPTION ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function oarCrypt(input) {
	var key = ['!', '@', '#', '$', '%', '^', '&', '*'];
    var output = [];
	
	for (var i = 0; i < input.length; i++) {
		var charCode = input.charCodeAt(i) ^ (key[i % key.length].charCodeAt(0));
		output.push(String.fromCharCode(charCode));
	}
	return output.join("");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// moor() FUNCTION: PROCESS JSON FROM OAR ---> SAVE TO CARGO //////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const request = require('request');

// yellow:  fd00::212:4b00:f24:8385
// red:     fd00::212:4b00:f83:b601
// green:   fd00::212:4b00:f82:a600
// blue:    fd00::212:4b00:f82:da03

function moor() {
    request.get('http://[fd00::212:4b00:f83:b601]/',function(err, res, body ){ 
        
        if(err) {
                console.log(err);
                return;
            } 
            
        
        console.log("");
        console.log('<--- <--- <--- <--- <--- <--- <--- <--- <--- <--- <---');
        console.log('get JSON  <--- oar (http://[fd00::212:4b00:f83:b601]/)');
        console.log('<--- <--- <--- <--- <--- <--- <--- <--- <--- <--- <---');
        
        // ----------------------------------------------------------------------------------------
        // RECEIVE JSON ///////////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------------------------------------------

        // print the current time and date 
        // to console for debugging purposes

        console.log("");
        var d = new Date(); // for now
        console.log(d);
        
        // print the base64 encoded json received 
        // to console for debugging purposes

        console.log("");
        console.log(body);

        // ----------------------------------------------------------------------------------------
        // BASE64 DECODE JSON /////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------------------------------------------
        
        var decoded = atob(body.toString());

        // print the base64 decoded json 
        // to console for debugging purposes

        console.log("");
        console.log(decoded);

        // ----------------------------------------------------------------------------------------
        // XOR DECRYPT JSON ///////////////////////////////////////////////////////////////////////
        // ----------------------------------------------------------------------------------------
        
        // var decrypted = oarCrypt(body.toString());
        var decrypted = oarCrypt(decoded);
        
        // print the base64 decoded json 
        // to console for debugging purposes
        
        console.log("");
        console.log(decrypted);
            
        if(body){
            try {
                
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // JSON PARSE: OK /////////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                var obj = JSON.parse(decrypted);
                
                // print that json parsed successfully 
                // to console for debugging purposes

                console.log("");
                console.log("JSON: VALID");

                // print the object that created parsing 
                // to console for debugging purposes
                
                console.log("");
                console.log(obj);
                
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // CHECKSUM CHECK /////////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                
                /////////////////////////////////////////
                // how to recalculate the checksum:    //
                // ----------------------------------- //
                // get the hash value from JSON        //
                // remove the "hash" keypair from JSON //
                // stringify the JSON                  //
                // remove last character '}'           //
                // concatenate a comma ','             //
                // calculate the hash of the string    //
                // check with original hash value      //
                /////////////////////////////////////////

                let payloadHash = obj.hash;
                let goa = obj;
                delete goa.hash;
                goa = JSON.stringify(goa);
                
                // print if checksum matches the inlcuded one 
                // to console for debugging purposes

                console.log("");
                console.log( (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? "CHECKSUM: VALID" : "CHECKSUM: INVALID" );
                console.log('PAYLOAD HASH: ' + payloadHash);

                if (obj.pckt.vld == true) {

                    // --> --> --> --> --> --> --> --> --> --> --> --> --> -->
                    // VALID PACKET TO CARGO /////////////////////////////////
                    // --> --> --> --> --> --> --> --> --> --> --> --> --> -->

                    switch(obj.ndx) {

                        case 0: 
                            var system = new System({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
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
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(system);
        
                            system.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- system COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;
                        
                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                        
                        case 1:
                            var device = new Device({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                device: {
                                    temperatureSensor: obj.dev.tp,
                                    humiditySensor: obj.dev.hd
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(device);

                            device.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- device COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                        
                        case 2:
                            var energy = new Energy({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
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
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(energy);

                            energy.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- energy COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;
                        
                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                        
                        case 3:
                            var networkIp = new NetworkIp({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
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
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(networkIp);

                            networkIp.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- networkIp COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                        
                        case 4:
                            var networkIcmp = new NetworkIcmp({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
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
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(networkIcmp);

                            networkIcmp.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- networkIcmp COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                        
                        case 5:
                            var transport = new Transport({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
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
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(transport);

                            transport.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- transport COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 6:
                            var discovery = new Discovery({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
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
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(discovery);

                            discovery.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- discovery COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 7:
                            var ipAddr = new IpAddr({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                ipAddr: {
                                    ipv6: obj.addr.IPv6,
                                    nodeIPv6addresses: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.addr.ad.forEach((address, index) => ipAddr.ipAddr.nodeIPv6addresses[index] = new NodeIPv6address({nodeIPv6address: address}));
                            
                            console.log("");
                            console.log(ipAddr);

                            ipAddr.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- ipAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 8:
                            var ipNeighborsIpAddr = new IpNeighborsIpAddr({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                ipNeighborsIpAddr: {
                                    ipv6: obj.nsIP.IPv6,
                                    nodeIPv6neighborIpAddresses: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.nsIP.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    ipNeighborsIpAddr.ipNeighborsIpAddr.nodeIPv6neighborIpAddresses[index] = new NodeIPv6neighborIpAddress({nodeIPv6neighborIpAddress: neighbor.ipAddr})
                                } else {
                                    ipNeighborsIpAddr.ipNeighborsIpAddr.nodeIPv6neighborIpAddresses[index] = null
                                }
                            })

                            console.log("");
                            console.log(ipNeighborsIpAddr);
                            
                            ipNeighborsIpAddr.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- ipNeighborsIpAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 9:
                            var ipNeighborsLlAddr = new IpNeighborsLlAddr({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                ipNeighborsLlAddr: {
                                    ipv6: obj.nsLL.IPv6,
                                    nodeIPv6neighborLlAddresses: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.nsLL.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    ipNeighborsLlAddr.ipNeighborsLlAddr.nodeIPv6neighborLlAddresses[index] = new NodeIPv6neighborLlAddress({nodeIPv6neighborLlAddress: neighbor.llAddr})
                                } else {
                                    ipNeighborsLlAddr.ipNeighborsLlAddr.nodeIPv6neighborLlAddresses[index] = null
                                }
                            });

                            console.log("");
                            console.log(ipNeighborsLlAddr);
                            
                            ipNeighborsLlAddr.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- ipNeighborsLlAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 10:
                            var ipNeighborsInfo = new IpNeighborsInfo({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                ipNeighborsInfo: {
                                    ipv6: obj.nsSt.IPv6,
                                    nodeIPv6neighborInfo: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.nsSt.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    ipNeighborsInfo.ipNeighborsInfo.nodeIPv6neighborInfo[index] = new NodeIPv6neighborInfo({nodeIPv6neighborRouter: neighbor.router, nodeIPv6neighborState: neighbor.state})
                                } else {
                                    ipNeighborsInfo.ipNeighborsInfo.nodeIPv6neighborInfo[index] = null
                                }
                            });

                            console.log("");
                            console.log(ipNeighborsInfo);
                            
                            ipNeighborsInfo.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- ipNeighborsInfo COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 11:
                            var route = new Route({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                route: {
                                    ipv6: obj.rt.IPv6,
                                    defaultRoute: obj.rt.df,
                                    lifetime: obj.rt.lt
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(route);
                            
                            route.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- route COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 12:
                            var routingLinksSources = new RoutingLinksSources({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                routingLinksSources: {
                                    ipv6: obj.rtLS.IPv6,
                                    rpl: obj.rtLS.rpl,
                                    totalRoutingLinks: obj.rtLS.totLs,
                                    routeSources: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rtLS.ls.forEach(function(link, index) {
                                if (link != null) {
                                    routingLinksSources.routingLinksSources.routeSources[index] = new LinkSource({linkSourceAddr: link.from, dodagRoot: link.dodagRoot})
                                } else {
                                    routingLinksSources.routingLinksSources.routeSources[index] = null
                                }
                            });

                            console.log("");
                            console.log(routingLinksSources);
                            
                            routingLinksSources.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- routingLinksSources COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 13:
                            var routingLinksDestinations = new RoutingLinksDestinations({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                routingLinksDestinations: {
                                    ipv6: obj.rtLD.IPv6,
                                    rpl: obj.rtLD.rpl,
                                    totalRoutingLinks: obj.rtLD.totLs,
                                    routeDestinations: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rtLD.ls.forEach(function(link, index) {
                                if (link != null) {
                                    routingLinksDestinations.routingLinksDestinations.routeDestinations[index] = new LinkDestination({linkDestinationAddr: link.to, lifetime: link.lf})
                                } else {
                                    routingLinksDestinations.routingLinksDestinations.routeDestinations[index] = null
                                }
                            });

                            console.log("");
                            console.log(routingLinksDestinations);
                            
                            routingLinksDestinations.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- routingLinksDestinations COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 14:
                            var routingEntriesRoutes = new RoutingEntriesRoutes({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                routingEntriesRoutes: {
                                    ipv6: obj.rtERt.IPv6,
                                    maxRoutesNon0: obj.rtERt.maxRtsN0,
                                    totalRoutingEntries: obj.rtERt.totEs,
                                    routes: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rtERt.es.forEach(function(entry, index) {
                                if (entry != null) {
                                    routingEntriesRoutes.routingEntriesRoutes.routes[index] = new EntryRoute({entryRouteAddr: entry.rt})
                                } else {
                                    routingEntriesRoutes.routingEntriesRoutes.routes[index] = null
                                }
                            });

                            console.log("");
                            console.log(routingEntriesRoutes);
                            
                            routingEntriesRoutes.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- routingEntriesRoutes COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 15:
                            var routingEntriesVias = new RoutingEntriesVias({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                routingEntriesVias: {
                                    ipv6: obj.rtEVia.IPv6,
                                    maxRoutesNon0: obj.rtEVia.maxRtsN0,
                                    totalRoutingEntries: obj.rtEVia.totEs,
                                    vias: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rtEVia.es.forEach(function(entry, index) {
                                if (entry != null) {
                                    routingEntriesVias.routingEntriesVias.vias[index] = new EntryVia({entryViaAddr: entry.via, lifetime: entry.lf})
                                } else {
                                    routingEntriesVias.routingEntriesVias.vias[index] = null
                                }
                            });

                            console.log("");
                            console.log(routingEntriesVias);
                            
                            routingEntriesVias.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- routingEntriesVias COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 16:
                            var rplStatus = new RplStatus({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplStatus: {
                                    rplLite: obj.rSt.rL,
                                    instance: obj.rSt.iId,
                                    modeOfOperation: obj.rSt.mop,
                                    objectiveCodePoint: obj.rSt.of,
                                    hopRankIncrement: obj.rSt.hRkI,
                                    defaultLifetime: obj.rSt.dLt,
                                    dtsnOut: obj.rSt.dtsn0
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(rplStatus);
                            
                            rplStatus.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplStatus COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 17:
                            var rplStatusDag = new RplStatusDag({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplStatusDag: {
                                    rplLite: obj.rStDag.rL,
                                    instance: obj.rStDag.iId,
                                    dagRole: obj.rStDag.dT,
                                    dagId: obj.rStDag.dId,
                                    dagPrefix: obj.rStDag.dPf,
                                    dagPrefixLength: obj.rStDag.dPfL,
                                    dagState: obj.rStDag.st,
                                    dagPreferedParent: obj.rStDag.pP,
                                    dagRank: obj.rStDag.rk,
                                    dagLowestRank: obj.rStDag.lRk,
                                    maxRankIncrement: obj.rStDag.mRkI,
                                    dao: {
                                        daoSequenceLastSent: obj.rStDag.dao.lS,
                                        daoSequenceLastAcked: obj.rStDag.dao.lA
                                    }
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(rplStatusDag);
                            
                            rplStatusDag.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplStatusDag COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 18:
                            var rplStatusTrickleTimer = new RplStatusTrickleTimer({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplStatusTrickleTimer: {
                                    rplLite: obj.rStTt.rL,
                                    instance: obj.rStTt.iId,
                                    current: obj.rStTt.cur,
                                    min: obj.rStTt.min, 
                                    max: obj.rStTt.max,
                                    redundancy: obj.rStTt.red
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            console.log("");
                            console.log(rplStatusTrickleTimer);
                            
                            rplStatusTrickleTimer.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplStatusTrickleTimer COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 19:
                            var rplNeighborAddr = new RplNeighborAddr({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplNeighborAddr: {
                                    rplLite: obj.rN.rL,
                                    instance: obj.rN.iId,
                                    rplNeighborCount: obj.rN.c,
                                    addresses: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rN.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    rplNeighborAddr.rplNeighborAddr.addresses[index] = new RplAddress({rplAddress: neighbor.ad})
                                } else {
                                    rplNeighborAddr.rplNeighborAddr.addresses[index] = null
                                }
                            });

                            console.log("");
                            console.log(rplNeighborAddr);
                            
                            rplNeighborAddr.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplNeighborAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 20:
                            var rplNeighborRanks = new RplNeighborRanks({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplNeighborRanks: {
                                    rplLite: obj.rNR.rL,
                                    instance: obj.rNR.iId,
                                    rplNeighborCount: obj.rNR.c,
                                    ranks: [null]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rNR.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    rplNeighborRanks.rplNeighborRanks.ranks[index] = new RplRanks({rplNeighborRank: neighbor.rk, rplNeighborLinkMetric: neighbor.lM, rplNeighborRankViaNeighbor: neighbor.rkN})
                                } else {
                                    rplNeighborRanks.rplNeighborRanks.ranks[index] = null
                                }
                            });

                            console.log("");
                            console.log(rplNeighborRanks);
                            
                            rplNeighborRanks.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplNeighborRanks COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 21:
                            var rplNeighborValues = new RplNeighborValues({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplNeighborValues: {
                                    rplLite: obj.rNV.rL,
                                    instance: obj.rNV.iId,
                                    rplNeighborCount: obj.rNV.c,
                                    values: [rplValuesSchema]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rNV.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    rplNeighborValues.rplNeighborValues.values[index] = new RplValues({rplNeighborStatsFreshness: neighbor.fr, rplNeighborRootRank: neighbor.r, rplNeighborBest: neighbor.b, rplNeighborAcceptableRankParent: neighbor.a, rplNeighborLinkStatsFresh: neighbor.f, rplNeighborDagPreferredParent: neighbor.p})
                                } else {
                                    rplNeighborValues.rplNeighborValues.values[index] = null
                                }
                            });

                            console.log("");
                            console.log(rplNeighborValues);
                            
                            rplNeighborValues.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplNeighborValues COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        case 22:
                            var rplNeighborParens = new RplNeighborParens({
                                packet: {
                                    valid: obj.pckt.vld,
                                    error: null
                                },
                                record: obj.rcrd,
                                index: obj.ndx,
                                mote: {
                                    systemTime: obj.id.sT,
                                    linkLayerAddress: obj.id.adr,
                                    moteCode: obj.id.cd
                                },
                                rplNeighborParens: {
                                    rplLite: obj.rNP.rL,
                                    instance: obj.rNP.iId,
                                    rplNeighborCount: obj.rNP.c,
                                    parens: [rplParensSchema]
                                },
                                checksum: {
                                    hash: payloadHash,
                                    check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                                },
                                update: new Date
                            });

                            obj.rNP.ns.forEach(function(neighbor, index) {
                                if (neighbor != null) {
                                    rplNeighborParens.rplNeighborParens.parens[index] = new RplParens({rplNeighborLastTXtimeSeconds: neighbor.lTx, rplNeighborBetterParentSinceSeconds: neighbor.bs})
                                } else {
                                    rplNeighborParens.rplNeighborParens.parens[index] = null
                                }
                            });

                            console.log("");
                            console.log(rplNeighborParens);
                            
                            rplNeighborParens.save(function (err) {
                                if (err) console.log(err);
                                
                                // saved!
                                
                                console.log("");
                                console.log(`cargo DATABASE <--- rplNeighborParens COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                            });

                            break;

                        // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                        default: 
                            console.log("");
                            console.log("ERROR: INDEX OUT OF RANGE");
                    }
                } else {

                    // --> --> --> --> --> --> --> --> --> --> --> --> --> -->
                    // ERROR PACKET TO CARGO /////////////////////////////////
                    // --> --> --> --> --> --> --> --> --> --> --> --> --> -->

                    console.log("");
                    console.log('ERROR RECIEVED FROM OAR');

                    var errorPacket = new ErrorPacket({
                        packet: {
                            valid: obj.pckt.vld,
                            error: {
                                text: obj.err.txt,
                                code: obj.err.cd
                            }
                        },
                        mote: {
                            systemTime: obj.id.sT,
                            linkLayerAddress: obj.id.adr,
                            moteCode: obj.id.cd
                        },
                        checksum: {
                            hash: payloadHash,
                            check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                        },
                        update: new Date
                    });

                    console.log("");
                    console.log(route);
                    
                    errorPacket.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`cargo DATABASE <--- errorPacket COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT`);
                    });
                }
            } catch(e) {

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // JSON PARSE: FAIL ///////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // print that json failed to parse 
                // to console for debugging purposes

                console.log("");
                console.error("JSON: INVALID");

                // print the error that caused parse to fail 
                // to console for debugging purposes

                console.error(e); // error in the above string (in this case, yes)!
                console.log("");
            }
        }
    });
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// moor() EVERY 5000 ms ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

setInterval(moor, 5000);