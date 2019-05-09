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




















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WEB SCRPAING ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const rp = require('request-promise');

// contiki-ng RPL border router runs an HTTP server (http://[fd00::212:4b00:f24:8385]/)
// to help finding out global IPv6 node addresses. The index.html served looks like: 

// <html>
//   <head>
//     <title>Contiki-NG</title>
//   </head>
// <body>
//   Neighbors
//   <ul>
//     <li>fe80::212:4b00:f83:b601</li>
//     <li>fe80::212:4b00:f82:a600</li>
//     <li>fe80::212:4b00:f82:da03</li>
//   </ul>
//   Routing links
//   <ul>
//     <li>fd00::212:4b00:f83:b601 (parent: fd00::212:4b00:f24:8385) 1500s</li>
//     <li>fd00::212:4b00:f82:a600 (parent: fd00::212:4b00:f24:8385) 960s</li>
//     <li>fd00::212:4b00:f82:da03 (parent: fd00::212:4b00:f24:8385) 1680s</li>
//   </ul>
// </body>
// </html>

// regular expression that matches any string:
// - starting with the two characters "fd"
// - contains any number of non-white characters
// - and does not end with ')' character
// - case insensitive and global (find all)

const nodesRegExp = /fd\S*(?<!\))\s/gi

// excecution order: the scraping function passes nodes in callback

function scrap(nodes, borderRouter, callback) {
    rp(borderRouter)
    .then(function(html) {

        console.log();
        console.log('BORDER ROUTER: ' + borderRouter);
        
        console.log();
        console.log(html);
        
        // [ 'fd00::212:4b00:f83:b601 ', 
        //   'fd00::212:4b00:f82:a600 ', 
        //   'fd00::212:4b00:f82:da03 ' ]

        nodes = html.match(nodesRegExp)

        if (nodes != null) {
            // nodes arrray contains all matching strings 
            // but with a space charactet appended at the end
            // (side effect of out regular expression lacking kung fu)
            // this white space character must be removed

            nodes = nodes.map((node) => node.slice(0, -1))
            
            // [ 'fd00::212:4b00:f83:b601', 
            //   'fd00::212:4b00:f82:a600', 
            //   'fd00::212:4b00:f82:da03' ]

            console.log(nodes);
            
            callback(nodes);

        } else {
            
            console.log("NO MOTES FOUND, RESTARTING SCRAPE");
            // scrap(nodes, borderRouter, callback);
        }

    
        
    })
    .catch(function(err){
        console.log(err);
    });
}




















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MONGODB CREDENTIALS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// mongodb configuration logic : 
// config for production or development

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

var energestSchema = new mongoose.Schema({
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
    energest: {
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

var stats_network_ipSchema = new mongoose.Schema({
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
    stats_network_ip: {
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

var stats_network_icmpSchema = new mongoose.Schema({
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
    stats_network_icmp: {
        uipStatistics: Boolean,
        icmp: {
            icmpRecv: Number,    
            icmpSent: Number,     
            icmpDrop: Number,
            icmTypeerr: Number,     
            icmpChkerr: Number  
        } 
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var stats_transportSchema = new mongoose.Schema({
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
    stats_transport: {
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
            udpDrop: Number,
            udpRecv: Number,  
            udpSent: Number,  
            udpChkerr: Number
        } 
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var stats_discoverySchema = new mongoose.Schema({
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
    stats_discovery: {
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

var cmd_ipAddrSchema = new mongoose.Schema({
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
    cmd_ipAddr: {
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

var cmd_IpNeighbors_ipAddrSchema = new mongoose.Schema({
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
    cmd_IpNeighbors_ipAddr: {
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

var cmd_ipNeighbors_llAddrSchema = new mongoose.Schema({
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
    cmd_ipNeighbors_llAddr: {
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

var cmd_ipNeighbors_infoSchema = new mongoose.Schema({
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
    cmd_ipNeighbors_info: {
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

var cmd_tschStatusSchema = new mongoose.Schema({
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
    cmd_tschStatus: {
        tsch: Boolean,
        isCoordinator: Boolean,
        isAssociated: Boolean,
        panID: String,
        panSecured: Boolean,
        joinPriority: Number,
        timeSource: String,
        lastSynchronized: Number,
        driftWRTCoordinator: Number,
        networkUptime: Number
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var tschScheduleSlotframeLinkSchema = new mongoose.Schema({
    options: String,
    type: Number,
    timeslot: Number,
    channelOffest: Number,
    address: String
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var tschScheduleSlotframeSchema = new mongoose.Schema({
    handle: Number,
    size: Number,
    links: [tschScheduleSlotframeLinkSchema]
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var cmd_tschScheduleSchema = new mongoose.Schema({
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
    cmd_tschSchedule: {
        tsch: Boolean,
        isLocked: Boolean,
        schedule: Boolean,
        slotframes: [tschScheduleSlotframeSchema]
    },
    checksum: {
        hash: Number,
        check: Boolean
    },
    update: { type: Date, default: Date.now }
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

var cmd_routesSchema = new mongoose.Schema({
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
    cmd_routes: {
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

var cmd_routes_routingLinks_sourcesSchema = new mongoose.Schema({
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
    cmd_routes_routingLinks_sources: {
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

var cmd_routes_routingLinks_destinationsSchema = new mongoose.Schema({
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
    cmd_routes_routingLinks_destinations: {
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

var cmd_routes_routingEntries_routesSchema = new mongoose.Schema({
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
    cmd_routes_routingEntries_routes: {
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

var cmd_routes_routingEntries_viasSchema = new mongoose.Schema({
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
    cmd_routes_routingEntries_vias: {
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

var cmd_rplStatusSchema = new mongoose.Schema({
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
    cmd_rplStatus: {
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

var cmd_rplStatus_dagSchema = new mongoose.Schema({
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
    cmd_rplStatus_dag: {
        rplLite: Boolean,
        instance: mongoose.Schema.Types.Mixed,
        dagRole: String,
        dagId: String,
        dagVersion: Number,
        dagPrefix: String,
        dagPrefixLength: Number,
        dagPreferedParent: String,
        dagPreferedParentLastDTSN: Number,
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

var cmd_rplStatus_trickleTimerSchema = new mongoose.Schema({
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
    cmd_rplStatus_trickleTimer: {
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

var cmd_rplNbr_addrSchema = new mongoose.Schema({
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
    cmd_rplNbr_addr: {
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

var cmd_rplNbr_ranksSchema = new mongoose.Schema({
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
    cmd_rplNbr_ranks: {
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

var cmd_rplNbr_valuesSchema = new mongoose.Schema({
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
    cmd_rplNbr_values: {
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

var cmd_rplNbr_parensSchema = new mongoose.Schema({
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
    cmd_rplNbr_parens: {
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

var errorReportSchema = new mongoose.Schema({
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

var System                                  = mongoose.model('System',                                  systemSchema);
var Device                                  = mongoose.model('Device',                                  deviceSchema);
var Energest                                = mongoose.model('Energest',                                energestSchema);
var Stats_network_ip                        = mongoose.model('Stats_network_ip',                        stats_network_ipSchema);
var Stats_network_icmp                      = mongoose.model('Stats_network_icmp',                      stats_network_icmpSchema);
var Stats_transport                         = mongoose.model('Stats_transport',                         stats_transportSchema);
var Stats_discovery                         = mongoose.model('Stats_discovery',                         stats_discoverySchema);

var NodeIPv6address                         = mongoose.model('NodeIPv6addres',                          nodeIPv6ddressSchema);
var Cmd_ipAddr                              = mongoose.model('Cmd_ipAddr',                              cmd_ipAddrSchema);

var NodeIPv6neighborIpAddress               = mongoose.model('NodeIPv6neighborIpAddress',               nodeIPv6neighborIpAddressSchema);
var Cmd_IpNeighbors_ipAddr                  = mongoose.model('Cmd_IpNeighbors_ipAddr',                  cmd_IpNeighbors_ipAddrSchema);

var NodeIPv6neighborLlAddress               = mongoose.model('NodeIPv6neighborLlAddress',               nodeIPv6neighborLlAddressSchema);
var Cmd_ipNeighbors_llAddr                  = mongoose.model('Cmd_ipNeighbors_llAddr',                  cmd_ipNeighbors_llAddrSchema);

var NodeIPv6neighborInfo                    = mongoose.model('NodeIPv6neighborInfo',                    nodeIPv6neighborInfoSchema);
var Cmd_ipNeighbors_info                    = mongoose.model('Cmd_ipNeighbors_info',                    cmd_ipNeighbors_infoSchema);

var Cmd_tschStatus                          = mongoose.model('Cmd_tschStatus',                          cmd_tschStatusSchema);

var TschScheduleSlotframeLink               = mongoose.model('TschScheduleSlotframeLink',               tschScheduleSlotframeLinkSchema);
var TschScheduleSlotframe                   = mongoose.model('TschScheduleSlotframe',                   tschScheduleSlotframeSchema);
var Cmd_tschSchedule                        = mongoose.model('Cmd_tschSchedule',                        cmd_tschScheduleSchema);

var Cmd_routes                              = mongoose.model('Cmd_routes',                              cmd_routesSchema);

var LinkSource                              = mongoose.model('LinkSource',                              linkSourceSchema);
var Cmd_routes_routingLinks_sources         = mongoose.model('Cmd_routes_routingLinks_sources',         cmd_routes_routingLinks_sourcesSchema);

var LinkDestination                         = mongoose.model('LinkDestination',                         linkDestinationSchema);
var Cmd_routes_routingLinks_destinations    = mongoose.model('Cmd_routes_routingLinks_destinations',    cmd_routes_routingLinks_destinationsSchema);

var EntryRoute                              = mongoose.model('EntryRoute',                              entryRouteSchema);
var Cmd_routes_routingEntries_routes        = mongoose.model('Cmd_routes_routingEntries_routes',        cmd_routes_routingEntries_routesSchema);

var EntryVia                                = mongoose.model('EntryVia',                                entryViaSchema);
var Cmd_routes_routingEntries_vias          = mongoose.model('Cmd_routes_routingEntries_vias',          cmd_routes_routingEntries_viasSchema);

var Cmd_rplStatus                           = mongoose.model('Cmd_rplStatus',                           cmd_rplStatusSchema);
var Cmd_rplStatus_dag                       = mongoose.model('Cmd_rplStatus_dag',                       cmd_rplStatus_dagSchema);
var Cmd_rplStatus_trickleTimer              = mongoose.model('Cmd_rplStatus_trickleTimer',              cmd_rplStatus_trickleTimerSchema);

var RplAddress                              = mongoose.model('RplAddress',                              rplAddressSchema);
var Cmd_rplNbr_addr                         = mongoose.model('Cmd_rplNbr_addr',                         cmd_rplNbr_addrSchema);

var RplRanks                                = mongoose.model('RplRanks',                                rplRanksSchema);
var Cmd_rplNbr_ranks                        = mongoose.model('Cmd_rplNbr_ranks',                        cmd_rplNbr_ranksSchema);

var RplValues                               = mongoose.model('RplValues',                               rplValuesSchema);
var Cmd_rplNbr_values                       = mongoose.model('Cmd_rplNbr_values',                       cmd_rplNbr_valuesSchema);

var RplParens                               = mongoose.model('RplParens',                               rplParensSchema);
var Cmd_rplNbr_parens                       = mongoose.model('Cmd_rplNbr_parens',                       cmd_rplNbr_parensSchema);

var ErrorReport                             = mongoose.model('ErrorReport',                             errorReportSchema);




















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// checkProcessSaveReturn /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function checkProcessSaveReturn(obj, doReturn) {

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

                if(doReturn) {

                    return(system);
                } else {

                    system.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- system COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };
            
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

                if(doReturn) {
                    
                    return(device);

                } else {

                    device.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- device COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 2:
                var energest = new Energest({
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
                    energest: {
                        energest: obj.nrg.en,
                        cpu: obj.nrg.cp,
                        lpm: obj.nrg.lp,
                        deepLpm: obj.nrg.dL,
                        totalTime: obj.nrg.tT,
                        radioListening: obj.nrg.rL,
                        radioTransmiting: obj.nrg.rT,
                        radioOff: obj.nrg.rO
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                console.log("");
                console.log(energest);

                if(doReturn) {

                    return(energest);

                } else {

                    energest.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- energest COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                }

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 3:
                var stats_network_ip = new Stats_network_ip({
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
                    stats_network_ip: {
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
                console.log(stats_network_ip);

                if(doReturn) {

                    return(stats_network_ip);

                } else {

                    stats_network_ip.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- stats_network_ip COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 4:
                var stats_network_icmp = new Stats_network_icmp({
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
                    stats_network_icmp: {
                        uipStatistics: obj.icSt.uS,
                        icmp: {
                            icmpRecv: obj.icSt.ic.rx,    
                            icmpSent: obj.icSt.ic.tx,     
                            icmpDrop: obj.icSt.ic.dr,
                            icmpTypeerr: obj.icSt.ic.tE,     
                            icmpChkerr: obj.icSt.ic.cE  
                        } 
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                console.log("");
                console.log(stats_network_icmp);

                if(doReturn) {

                    return(stats_network_icmp);
                
                } else {

                    stats_network_icmp.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- stats_network_icmp COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 5:
                var stats_transport = new Stats_transport({
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
                    stats_transport: {
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
                            udpDrop: obj.tSt.udp.dr,
                            udpRecv: obj.tSt.udp.rx,  
                            udpSent: obj.tSt.udp.tx,  
                            udpChkerr: obj.tSt.udp.cE
                        } 
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                console.log("");
                console.log(stats_transport);

                if(doReturn) {
                    return(stats_transport);
                } else {

                    stats_transport.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- stats_transport COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 6:
                var stats_discovery = new Stats_discovery({
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
                    stats_discovery: {
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
                console.log(stats_discovery);

                if(doReturn) {

                    return(stats_discovery);

                } else {

                    stats_discovery.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- stats_discovery COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 7:
                var cmd_ipAddr = new Cmd_ipAddr({
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
                    cmd_ipAddr: {
                        ipv6: obj.addr.IPv6,
                        nodeIPv6addresses: [null]
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                obj.addr.ad.forEach((address, index) => cmd_ipAddr.cmd_ipAddr.nodeIPv6addresses[index] = new NodeIPv6address({nodeIPv6address: address}));
                
                console.log("");
                console.log(cmd_ipAddr);

                

                if(doReturn) {

                    return(cmd_ipAddr);
                
                } else {

                    cmd_ipAddr.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_ipAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 8:
                var cmd_IpNeighbors_ipAddr = new Cmd_IpNeighbors_ipAddr({
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
                    cmd_IpNeighbors_ipAddr: {
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
                        cmd_IpNeighbors_ipAddr.cmd_IpNeighbors_ipAddr.nodeIPv6neighborIpAddresses[index] = new NodeIPv6neighborIpAddress({nodeIPv6neighborIpAddress: neighbor.ipAddr})
                    } else {
                        cmd_IpNeighbors_ipAddr.cmd_IpNeighbors_ipAddr.nodeIPv6neighborIpAddresses[index] = null
                    }
                })

                console.log("");
                console.log(cmd_IpNeighbors_ipAddr);
                
                

                if(doReturn) {

                    return(cmd_IpNeighbors_ipAddr);

                } else {
                    
                    cmd_IpNeighbors_ipAddr.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_IpNeighbors_ipAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 9:
                var cmd_ipNeighbors_llAddr = new Cmd_ipNeighbors_llAddr({
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
                    cmd_ipNeighbors_llAddr: {
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
                        cmd_ipNeighbors_llAddr.cmd_ipNeighbors_llAddr.nodeIPv6neighborLlAddresses[index] = new NodeIPv6neighborLlAddress({nodeIPv6neighborLlAddress: neighbor.llAddr})
                    } else {
                        cmd_ipNeighbors_llAddr.cmd_ipNeighbors_llAddr.nodeIPv6neighborLlAddresses[index] = null
                    }
                });

                console.log("");
                console.log(cmd_ipNeighbors_llAddr);

                if(doReturn) {

                    return(cmd_ipNeighbors_llAddr);
                
                } else {

                    cmd_ipNeighbors_llAddr.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_ipNeighbors_llAddr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 10:
                var cmd_ipNeighbors_info = new Cmd_ipNeighbors_info({
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
                    cmd_ipNeighbors_info: {
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
                        cmd_ipNeighbors_info.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = new NodeIPv6neighborInfo({nodeIPv6neighborRouter: neighbor.router, nodeIPv6neighborState: neighbor.state})
                    } else {
                        cmd_ipNeighbors_info.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = null
                    }
                });

                console.log("");
                console.log(cmd_ipNeighbors_info);

                if(doReturn) {

                    return(cmd_ipNeighbors_info);
                
                } else {

                    cmd_ipNeighbors_info.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_ipNeighbors_info COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 11:
                var cmd_tschStatus = new Cmd_tschStatus({
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
                    cmd_tschStatus: {
                        tsch: obj.tsch.tsch,
                        isCoordinator: obj.tsch.coo,
                        isAssociated: obj.tsch.ass,
                        panID: obj.tsch.panid,
                        panSecured: obj.tsch.pansec,
                        joinPriority: obj.tsch.joinp,
                        timeSource: obj.tsch.tsrc,
                        lastSynchronized: obj.tsch.lsyn,
                        driftWRTCoordinator: obj.tsch.drift,
                        networkUptime: obj.tsch.netup
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                console.log("");
                console.log(cmd_tschStatus);

                if(doReturn) {

                    return(cmd_tschStatus);
                
                } else {

                    cmd_tschStatus.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_tschStatus COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 12:
                var cmd_tschSchedule = new Cmd_tschSchedule({
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
                    cmd_tschSchedule: {
                        tsch: obj.tschSch.tsch,
                        isLocked: obj.tschSch.lock,
                        schedule: obj.tschSch.sch,
                        slotframes: [null]
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                obj.tschSch.slts.forEach(function(slotframe, index) {
                    if (slotframe != null) {
                        cmd_tschSchedule.cmd_tschSchedule.slotframes[index] = new TschScheduleSlotframe({handle: slotframe.hdl, size: neighbor.sz, links: [null]})
                        obj.tschSch.slts.lnks.forEach(function(link, linkindex) {
                            if (link != null) {
                                cmd_tschSchedule.cmd_tschSchedule.slotframes[index].links[linkindex] = new TschScheduleSlotframeLink({options: link.opt, type: link.tp, timeslot: link.tslt, channelOffset: link.chOf, address: link.ad});
                            } else {
                                cmd_tschSchedule.cmd_tschSchedule.slotframes[index].links[linkindex] = null
                            }
                        }) 
                    } else {
                        cmd_tschSchedule.cmd_tschSchedule.slotframes[index] = null
                    }
                });

                console.log("");
                console.log(cmd_tschSchedule);

                if(doReturn) {

                    return(cmd_tschSchedule);
                
                } else {

                    cmd_tschSchedule.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_tschSchedule COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 13:
                var cmd_routes = new Cmd_routes({
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
                    cmd_routes: {
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
                console.log(cmd_routes);

                if(doReturn) {

                    return(cmd_routes);
                
                } else {

                    cmd_routes.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_routes COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 14:
                var cmd_routes_routingLinks_sources = new Cmd_routes_routingLinks_sources({
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
                    cmd_routes_routingLinks_sources: {
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
                        cmd_routes_routingLinks_sources.cmd_routes_routingLinks_sources.routeSources[index] = new LinkSource({linkSourceAddr: link.from, dodagRoot: link.dodagRoot})
                    } else {
                        cmd_routes_routingLinks_sources.cmd_routes_routingLinks_sources.routeSources[index] = null
                    }
                });

                console.log("");
                console.log(cmd_routes_routingLinks_sources);

                if(doReturn) {

                    return(cmd_routes_routingLinks_sources);
                
                } else {

                    cmd_routes_routingLinks_sources.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_routes_routingLinks_sources COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                }

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 15:
                var cmd_routes_routingLinks_destinations = new Cmd_routes_routingLinks_destinations({
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
                    cmd_routes_routingLinks_destinations: {
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
                        cmd_routes_routingLinks_destinations.cmd_routes_routingLinks_destinations.routeDestinations[index] = new LinkDestination({linkDestinationAddr: link.to, lifetime: link.lf})
                    } else {
                        cmd_routes_routingLinks_destinations.cmd_routes_routingLinks_destinations.routeDestinations[index] = null
                    }
                });

                console.log("");
                console.log(cmd_routes_routingLinks_destinations);

                if(doReturn) {

                    return(cmd_routes_routingLinks_destinations);
                
                } else {

                    cmd_routes_routingLinks_destinations.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_routes_routingLinks_destinations COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 16:
                var cmd_routes_routingEntries_routes = new Cmd_routes_routingEntries_routes({
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
                    cmd_routes_routingEntries_routes: {
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
                        cmd_routes_routingEntries_routes.cmd_routes_routingEntries_routes.routes[index] = new EntryRoute({entryRouteAddr: entry.rt})
                    } else {
                        cmd_routes_routingEntries_routes.cmd_routes_routingEntries_routes.routes[index] = null
                    }
                });

                console.log("");
                console.log(cmd_routes_routingEntries_routes);

                if(doReturn) {

                    return(cmd_routes_routingEntries_routes);
                
                } else {

                    cmd_routes_routingEntries_routes.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_routes_routingEntries_routes COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 17:
                var cmd_routes_routingEntries_vias = new Cmd_routes_routingEntries_vias({
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
                    cmd_routes_routingEntries_vias: {
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
                        cmd_routes_routingEntries_vias.cmd_routes_routingEntries_vias.vias[index] = new EntryVia({entryViaAddr: entry.via, lifetime: entry.lf})
                    } else {
                        cmd_routes_routingEntries_vias.cmd_routes_routingEntries_vias.vias[index] = null
                    }
                });

                console.log("");
                console.log(cmd_routes_routingEntries_vias);

                if(doReturn) {

                    return(cmd_routes_routingEntries_vias);
                
                } else {

                    cmd_routes_routingEntries_vias.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_routes_routingEntries_vias COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 18:
                var cmd_rplStatus = new Cmd_rplStatus({
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
                    cmd_rplStatus: {
                        rplLite: obj.rSt.rL,
                        instance: obj.rSt.iId,
                        modeOfOperation: obj.rSt.mop,
                        objectiveCodePoint: obj.rSt.of,
                        hopRankIncrement: obj.rSt.hRkI,
                        defaultLifetime: obj.rSt.dLt,
                        dtsnOut: obj.rSt.dtsnO
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                console.log("");
                console.log(cmd_rplStatus);

                if(doReturn) {

                    return(cmd_rplStatus);

                } else {

                    cmd_rplStatus.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplStatus COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 19:
                var cmd_rplStatus_dag = new Cmd_rplStatus_dag({
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
                    cmd_rplStatus_dag: {
                        rplLite: obj.rStDag.rL,
                        instance: obj.rStDag.iId,
                        dagRole: obj.rStDag.dT,
                        dagId: obj.rStDag.dId,
                        dagVersion: obj.rStDag.dVer,
                        dagPrefix: obj.rStDag.dPf,
                        dagPrefixLength: obj.rStDag.dPfL,
                        dagState: obj.rStDag.st,
                        dagPreferedParent: obj.rStDag.pP,
                        dagPreferedParentLastDTSN: obj.rStDag.lD,
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
                console.log(cmd_rplStatus_dag);

                if(doReturn) {

                    return(cmd_rplStatus_dag);

                } else {

                    cmd_rplStatus_dag.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplStatus_dag COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 20:
                var cmd_rplStatus_trickleTimer = new Cmd_rplStatus_trickleTimer({
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
                    cmd_rplStatus_trickleTimer: {
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
                console.log(cmd_rplStatus_trickleTimer);

                if(doReturn) {

                    return(cmd_rplStatus_trickleTimer);
                
                } else {

                    cmd_rplStatus_trickleTimer.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplStatus_trickleTimer COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 21:
                var cmd_rplNbr_addr = new Cmd_rplNbr_addr({
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
                    cmd_rplNbr_addr: {
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
                        cmd_rplNbr_addr.cmd_rplNbr_addr.addresses[index] = new RplAddress({rplAddress: neighbor.ad})
                    } else {
                        cmd_rplNbr_addr.cmd_rplNbr_addr.addresses[index] = null
                    }
                });

                console.log("");
                console.log(cmd_rplNbr_addr);

                if(doReturn) {

                    return(cmd_rplNbr_addr);
                
                } else {

                    cmd_rplNbr_addr.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplNbr_addr COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 22:
                var cmd_rplNbr_ranks = new Cmd_rplNbr_ranks({
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
                    cmd_rplNbr_ranks: {
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
                        cmd_rplNbr_ranks.cmd_rplNbr_ranks.ranks[index] = new RplRanks({rplNeighborRank: neighbor.rk, rplNeighborLinkMetric: neighbor.lM, rplNeighborRankViaNeighbor: neighbor.rkN})
                    } else {
                        cmd_rplNbr_ranks.cmd_rplNbr_ranks.ranks[index] = null
                    }
                });

                console.log("");
                console.log(cmd_rplNbr_ranks);

                if(doReturn) {

                    return(cmd_rplNbr_ranks);
                
                } else {

                    cmd_rplNbr_ranks.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplNbr_ranks COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 23:
                var cmd_rplNbr_values = new Cmd_rplNbr_values({
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
                    cmd_rplNbr_values: {
                        rplLite: obj.rNV.rL,
                        instance: obj.rNV.iId,
                        rplNeighborCount: obj.rNV.c,
                        values: [null]
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                obj.rNV.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_values.cmd_rplNbr_values.values[index] = new RplValues({rplNeighborStatsFreshness: neighbor.fr, rplNeighborRootRank: neighbor.r, rplNeighborBest: neighbor.b, rplNeighborAcceptableRankParent: neighbor.a, rplNeighborLinkStatsFresh: neighbor.f, rplNeighborDagPreferredParent: neighbor.p})
                    } else {
                        cmd_rplNbr_values.cmd_rplNbr_values.values[index] = null
                    }
                });

                console.log("");
                console.log(cmd_rplNbr_values);

                if(doReturn) {

                    return(cmd_rplNbr_values);

                } else {

                    cmd_rplNbr_values.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplNbr_values COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });

                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 24:
                var cmd_rplNbr_parens = new Cmd_rplNbr_parens({
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
                    cmd_rplNbr_parens: {
                        rplLite: obj.rNP.rL,
                        instance: obj.rNP.iId,
                        rplNeighborCount: obj.rNP.c,
                        parens: [null]
                    },
                    checksum: {
                        hash: payloadHash,
                        check: (sdbm(goa.substr(0, goa.length -1) + "," )) == payloadHash ? true : false
                    },
                    update: new Date
                });

                obj.rNP.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_parens.cmd_rplNbr_parens.parens[index] = new RplParens({rplNeighborLastTXtimeSeconds: neighbor.lTx, rplNeighborBetterParentSinceSeconds: neighbor.bS})
                    } else {
                        cmd_rplNbr_parens.cmd_rplNbr_parens.parens[index] = null
                    }
                });

                console.log("");
                console.log(cmd_rplNbr_parens);
                
                

                if(doReturn) {

                    return(cmd_rplNbr_parens);
                
                } else {

                    cmd_rplNbr_parens.save(function (err) {
                        if (err) console.log(err);
                        
                        // saved!
                        
                        console.log("");
                        console.log(`<--- <--- <--- cargo DATABASE <--- cmd_rplNbr_parens COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
                    });
                    
                    break;
                };

            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            default: 
                console.log("");
                console.log("ERROR: INDEX OUT OF RANGE");
        };

    } else {

        // --> --> --> --> --> --> --> --> --> --> --> --> --> -->
        // ERROR PACKET TO CARGO /////////////////////////////////
        // --> --> --> --> --> --> --> --> --> --> --> --> --> -->

        console.log("");
        console.log('ERROR RECIEVED FROM OAR');

        var errorReport = new ErrorReport({
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

        if(doReturn) {

            return(errorReport);
        
        } else {

            errorReport.save(function (err) {
                if (err) console.log(err);
                
                // saved!
                
                console.log("");
                console.log(`<--- <--- <--- cargo DATABASE <--- errorReport COLLECTION <--- (record: ${obj.rcrd} / index: ${obj.ndx}) DOCUMENT <--- <--- <---`);
            });
        };
    };
}



















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



















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTROLLER SETUP ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var tug = {



    system: {
        index: function (req, res) {
            System.find(function (err, system) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: system                
                    });
                };
            });
        },
        drop: function (req, res) {
            System.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            System.findById(req.params.system_id, function(err, system) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: system 
                    });
                };
            });
        },
        erase: function (req, res) {
            System.deleteOne({_id: req.params.system_id}, function(err, system) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    device: {
        index: function (req, res) {
            Device.find(function (err, device) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: device                
                    })
                }
            })
        },
        drop: function (req, res) {
            Device.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Device.findById(req.params.device_id, function(err, device) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: device 
                    });
                };
            });
        },
        erase: function (req, res) {
            Device.deleteOne({_id: req.params.device_id}, function(err, device) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    energest: {
        index: function (req, res) {
            Energest.find(function (err, energest) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: energest                
                    })
                }
            })
        },
        drop: function (req, res) {
            Energest.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Energest.findById(req.params.energest_id, function(err, energest) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: energest 
                    });
                };
            });
        },
        erase: function (req, res) {
            Energest.deleteOne({_id: req.params.energest_id}, function(err, energest) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    stats_network_ip: {
        index: function (req, res) {
            Stats_network_ip.find(function (err, stats_network_ip) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_network_ip      
                    })
                }
            })
        },
        drop: function (req, res) {
            Stats_network_ip.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Stats_network_ip.findById(req.params.stats_network_ip_id, function(err, stats_network_ip) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_network_ip 
                    });
                };
            });
        },
        erase: function (req, res) {
            Stats_network_ip.deleteOne({_id: req.params.stats_network_ip_id}, function(err, stats_network_ip) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },


    
    stats_network_icmp: {
        index: function (req, res) {
            Stats_network_icmp.find(function (err, stats_network_icmp) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_network_icmp    
                    })
                }
            })
        },
        drop: function (req, res) {
            Stats_network_icmp.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Stats_network_icmp.findById(req.params.stats_network_icmp_id, function(err, stats_network_icmp) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_network_icmp 
                    });
                };
            });
        },
        erase: function (req, res) {
            Stats_network_icmp.deleteOne({_id: req.params.stats_network_icmp_id}, function(err, stats_network_icmp) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    stats_transport: {
        index: function (req, res) {
            Stats_transport.find(function (err, stats_transport) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_transport       
                    })
                }
            })
        },
        drop: function (req, res) {
            Stats_transport.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Stats_transport.findById(req.params.stats_transport_id, function(err, stats_transport) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_transport 
                    });
                };
            });
        },
        erase: function (req, res) {
            Stats_transport.deleteOne({_id: req.params.stats_transport_id}, function(err, stats_transport) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    stats_discovery: {
        index: function (req, res) {
            Stats_discovery.find(function (err, stats_discovery) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_discovery       
                    })
                }
            })
        },
        drop: function (req, res) {
            Stats_discovery.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Stats_discovery.findById(req.params.stats_discovery_id, function(err, stats_discovery) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: stats_discovery 
                    });
                };
            });
        },
        erase: function (req, res) {
            Stats_discovery.deleteOne({_id: req.params.stats_discovery_id}, function(err, stats_discovery) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_ipAddr: {
        index: function (req, res) {
            Cmd_ipAddr.find(function (err, cmd_ipAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_ipAddr       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_ipAddr.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_ipAddr.findById(req.params.cmd_ipAddr_id, function(err, cmd_ipAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_ipAddr 
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_ipAddr.deleteOne({_id: req.params.cmd_ipAddr_id}, function(err, cmd_ipAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_IpNeighbors_ipAddr: {
        index: function (req, res) {
            Cmd_IpNeighbors_ipAddr.find(function (err, cmd_IpNeighbors_ipAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_IpNeighbors_ipAddr       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_IpNeighbors_ipAddr.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_IpNeighbors_ipAddr.findById(req.params.cmd_IpNeighbors_ipAddr_id, function(err, cmd_IpNeighbors_ipAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_IpNeighbors_ipAddr
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_IpNeighbors_ipAddr.deleteOne({_id: cmd_IpNeighbors_ipAddr_id}, function(err, cmd_IpNeighbors_ipAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_IpNeighbors_llAddr: {
        index: function (req, res) {
            Cmd_ipNeighbors_llAddr.find(function (err, cmd_IpNeighbors_llAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_IpNeighbors_llAddr       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_ipNeighbors_llAddr.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_ipNeighbors_llAddr.findById(req.params.cmd_IpNeighbors_llAddr_id, function(err, cmd_IpNeighbors_llAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_IpNeighbors_llAddr
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_ipNeighbors_llAddr.deleteOne({_id: req.params.cmd_IpNeighbors_llAddr_id}, function(err, cmd_IpNeighbors_llAddr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_IpNeighbors_info: {
        index: function (req, res) {
            Cmd_ipNeighbors_info.find(function (err, cmd_IpNeighbors_info) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_IpNeighbors_info       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_ipNeighbors_info.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_ipNeighbors_info.findById(req.params.cmd_IpNeighbors_info_id, function(err, cmd_IpNeighbors_info) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_IpNeighbors_info
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_ipNeighbors_info.deleteOne({_id: req.params.cmd_IpNeighbors_info_id}, function(err, cmd_IpNeighbors_info) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },

    cmd_tschStatus: {
        index: function (req, res) {
            Cmd_tschStatus.find(function (err, cmd_tschStatus) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_tschStatus       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_tschStatus.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_tschStatus.findById(req.params.cmd_tschStatus_id, function(err, cmd_tschStatus) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_tschStatus
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_tschStatus.deleteOne({_id: req.params.cmd_tschStatus_id}, function(err, cmd_tschStatus) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },

    cmd_tschSchedule: {
        index: function (req, res) {
            Cmd_tschSchedule.find(function (err, cmd_tschSchedule) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_tschSchedule       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_tschSchedule.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_tschSchedule.findById(req.params.cmd_tschSchedule_id, function(err, cmd_tschSchedule) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_tschSchedule
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_tschSchedule.deleteOne({_id: req.params.cmd_tschSchedule_id}, function(err, cmd_tschSchedule) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },

    cmd_routes: {
        index: function (req, res) {
            Cmd_routes.find(function (err, cmd_routes) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_routes.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_routes.findById(req.params.cmd_routes_id, function(err, cmd_routes) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_routes.deleteOne({_id: req.params.cmd_routes_id}, function(err, cmd_routes) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },

    cmd_routes_routingLinks_sources: {
        index: function (req, res) {
            Cmd_routes_routingLinks_sources.find(function (err, cmd_routes_routingLinks_sources) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingLinks_sources       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_routes_routingLinks_sources.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_routes_routingLinks_sources.findById(req.params.cmd_routes_routingLinks_sources_id, function(err, cmd_routes_routingLinks_sources) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingLinks_sources
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_routes_routingLinks_sources.deleteOne({_id: req.params.cmd_routes_routingLinks_sources_id}, function(err, cmd_routes_routingLinks_sources) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_routes_routingLinks_destinations: {
        index: function (req, res) {
            Cmd_routes_routingLinks_destinations.find(function (err, cmd_routes_routingLinks_destinations) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingLinks_destinations       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_routes_routingLinks_destinations.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_routes_routingLinks_destinations.findById(req.params.cmd_routes_routingLinks_destinations_id, function(err, cmd_routes_routingLinks_destinations) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingLinks_destinations
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_routes_routingLinks_destinations.deleteOne({_id: req.params.cmd_routes_routingLinks_destinations_id}, function(err, cmd_routes_routingLinks_destinations) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_routes_routingEntries_routes: {
        index: function (req, res) {
            Cmd_routes_routingEntries_routes.find(function (err, cmd_routes_routingEntries_routes) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingEntries_routes       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_routes_routingEntries_routes.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_routes_routingEntries_routes.findById(req.params.cmd_routes_routingEntries_routes_id, function(err, cmd_routes_routingEntries_routes) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingEntries_routes
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_routes_routingEntries_routes.deleteOne({_id: req.params.cmd_routes_routingEntries_routes_id}, function(err, cmd_routes_routingEntries_routes) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_routes_routingEntries_vias: {
        index: function (req, res) {
            Cmd_routes_routingEntries_vias.find(function (err, cmd_routes_routingEntries_vias) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingEntries_vias       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_routes_routingEntries_vias.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_routes_routingEntries_vias.findById(req.params.cmd_routes_routingEntries_vias_id, function(err, cmd_routes_routingEntries_vias) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_routes_routingEntries_vias
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_routes_routingEntries_vias.deleteOne({_id: req.params.cmd_routes_routingEntries_vias_id}, function(err, cmd_routes_routingEntries_vias) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },

    cmd_rplStatus: {
        index: function (req, res) {
            Cmd_rplStatus.find(function (err, cmd_rplStatus) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplStatus       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplStatus.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplStatus.findById(req.params.cmd_rplStatus_id, function(err, cmd_rplStatus) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplStatus
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplStatus.deleteOne({_id: req.params.cmd_rplStatus_id}, function(err, cmd_rplStatus) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_rplStatus_dag: {
        index: function (req, res) {
            Cmd_rplStatus_dag.find(function (err, cmd_rplStatus_dag) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplStatus_dag       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplStatus_dag.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplStatus_dag.findById(req.params.cmd_rplStatus_dag_id, function(err, cmd_rplStatus_dag) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplStatus_dag
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplStatus_dag.deleteOne({_id: req.params.cmd_rplStatus_dag_id}, function(err, cmd_rplStatus_dag) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_rplStatus_trickleTimer: {
        index: function (req, res) {
            Cmd_rplStatus_trickleTimer.find(function (err, cmd_rplStatus_trickleTimer) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplStatus_trickleTimer       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplStatus_trickleTimer.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplStatus_trickleTimer.findById(req.params.cmd_rplStatus_trickleTimer_id, function(err, cmd_rplStatus_trickleTimer) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplStatus_trickleTimer
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplStatus_trickleTimer.deleteOne({_id: req.params.cmd_rplStatus_trickleTimer_id}, function(err, cmd_rplStatus_trickleTimer) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_rplNbr_addr: {
        index: function (req, res) {
            Cmd_rplNbr_addr.find(function (err, cmd_rplNbr_addr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_addr       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplNbr_addr.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplNbr_addr.findById(req.params.cmd_rplNbr_addr_id, function(err, cmd_rplNbr_addr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_addr
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplNbr_addr.deleteOne({_id: req.params.cmd_rplNbr_addr_id}, function(err, cmd_rplNbr_addr) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_rplNbr_ranks: {
        index: function (req, res) {
            Cmd_rplNbr_ranks.find(function (err, cmd_rplNbr_ranks) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_ranks       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplNbr_ranks.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplNbr_ranks.findById(req.params.cmd_rplNbr_ranks_id, function(err, cmd_rplNbr_ranks) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_ranks
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplNbr_ranks.deleteOne({_id: req.params.cmd_rplNbr_ranks_id}, function(err, cmd_rplNbr_ranks) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_rplNbr_values: {
        index: function (req, res) {
            Cmd_rplNbr_values.find(function (err, cmd_rplNbr_values) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_values       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplNbr_values.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplNbr_values.findById(req.params.cmd_rplNbr_values_id, function(err, cmd_rplNbr_values) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_values
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplNbr_values.deleteOne({_id: req.params.cmd_rplNbr_values_id}, function(err, cmd_rplNbr_values) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    cmd_rplNbr_parens: {
        index: function (req, res) {
            Cmd_rplNbr_parens.find(function (err, cmd_rplNbr_parens) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_parens       
                    })
                }
            })
        },
        drop: function (req, res) {
            Cmd_rplNbr_parens.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            Cmd_rplNbr_parens.findById(req.params.cmd_rplNbr_parens_id, function(err, cmd_rplNbr_parens) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: cmd_rplNbr_parens
                    });
                };
            });
        },
        erase: function (req, res) {
            Cmd_rplNbr_parens.deleteOne({_id: req.params.cmd_rplNbr_parens_id}, function(err, cmd_rplNbr_parens) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    },



    errorReport: {
        index: function (req, res) {
            ErrorReport.find(function (err, errorReport) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null,  
                        data: null                  
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: errorReport       
                    })
                }
            })
        },
        drop: function (req, res) {
            ErrorReport.collection.drop(function (err) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        },
        view: function (req, res) {
            ErrorReport.findById(req.params.errorReport_id, function(err, errorReport) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: errorReport
                    });
                };
            });
        },
        erase: function (req, res) {
            ErrorReport.deleteOne({_id: req.params.errorReport_id}, function(err, errorReport) {
                if (err) {
                    res.json({
                        status: 'error',  
                        text: err, 
                        goto: null, 
                        data: null
                    })
                } else {
                    res.json({
                        status: 'ok',     
                        text: null, 
                        goto: null, 
                        data: null 
                    });
                };
            });
        }
    }
}



















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WEB SERVER SETUP ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// create app using express
// and initialize the app

const app = express();

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// Cross-origin resource sharing (CORS) is a mechanism that allows many resources (e.g., fonts, JavaScript, etc.) on a web page 
// to be requested from another domain outside the domain the resource originated from. https://www.wikiwand.com/en/Cross-origin_resource_sharing

// (CLIENT) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// (CLIENT) Access to XMLHttpRequest at 'http://localhost:8080/api/system' from origin 'null' has been blocked by CORS policy: XXXXXXXXXXXXXX
// (CLIENT) No 'Access-Control-Allow-Origin' header is present on the requested resource. XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// (CLIENT) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// (CLIENT) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// (CLIENT) Cross-Origin Read Blocking (CORB) blocked cross-origin response http://localhost:8080/api/system with MIME type application/json. 
// (CLIENT) See https://www.chromestatus.com/feature/5629709824032768 for more details. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// (CLIENT) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// filter and setting the allowed origin that can access the server
const corsOptions = {origin: true, credentials: true};
app.use(cors(corsOptions)); // app.use(cors());

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// Initialize express router
let router = require('express').Router();

// Set default API response
// for given api routes

router.get('/', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/nuke', '/oar', '/cargo', '/buoy'],
        data: null
    });
});

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

router.get('/cargo', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/system', '/device', '/energy', '/stats', '/cmd', '/errors'],
        data: null
    });
});

// ~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/ cargo/GOTOs

router.get('/cargo/stats', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/network', '/transport', '/discovery'],
        data: null
    });
});

router.get('/cargo/stats/network', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/ip', '/icmp'], 
        data: null
    });
});

router.get('/cargo/cmd', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/ipaddr', '/ipnbr', '/tschstatus', '/tschschedule', '/routes', '/rplstatus', '/rplnbr'], 
        data: null
    });
});

router.get('/cargo/cmd/ipnbr', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/ipaddr', '/lladdr', '/info'], 
        data: null
    });
});

router.get('/cargo/cmd/routes', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/default', '/links', '/entries'], 
        data: null
    });
});

router.get('/cargo/cmd/routes/links', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/sources', '/destinations'], 
        data: null
    });
});

router.get('/cargo/cmd/routes/entries', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/routes', '/vias'], 
        data: null
    });
});

router.get('/cargo/cmd/rplstatus', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/id', '/dag', '/time'],
        data: null
    });
});

router.get('/cargo/cmd/rplnbr', function (req, res) {
    res.json({
        status: null, 
        text: null,
        goto: ['/addr', '/ranks', '/values', '/parens'],
        data: null
    });
});

// ~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/ cargo/read/collections

// routes for API accordingly
// each send rest jsons

router.route('/cargo/system')
    .get(tug.system.index)
    .delete(tug.system.drop);
router.route('/cargo/system/:system_id')
    .get(tug.system.view)
    .delete(tug.system.erase);

router.route('/cargo/device')
    .get(tug.device.index)
    .delete(tug.device.drop);
router.route('/cargo/device/:device_id')
    .get(tug.device.view)
    .delete(tug.device.erase);

router.route('/cargo/energy')
    .get(tug.energest.index)
    .delete(tug.energest.drop);
router.route('/cargo/energy/:energest_id')
    .get(tug.energest.view)
    .delete(tug.energest.erase);

// <><><><><><><><><><><><><><><><><><><><><><><>

router.route('/cargo/stats/network/ip')
    .get(tug.stats_network_ip.index)
    .delete(tug.stats_network_ip.drop);
router.route('/cargo/stats/network/ip/:stats_network_ip_id')
    .get(tug.stats_network_ip.view)
    .delete(tug.stats_network_ip.erase);

router.route('/cargo/stats/network/icmp')
    .get(tug.stats_network_icmp.index)
    .delete(tug.stats_network_icmp.drop);
router.route('/cargo/stats/network/icmp/:stats_network_icmp_id')
    .get(tug.stats_network_icmp.view)
    .delete(tug.stats_network_icmp.erase);

router.route('/cargo/stats/transport')
    .get(tug.stats_transport.index)
    .delete(tug.stats_transport.drop);
router.route('/cargo/stats/transport/:stats_transport_id')
    .get(tug.stats_transport.view)
    .delete(tug.stats_transport.erase);

router.route('/cargo/stats/discovery')
    .get(tug.stats_discovery.index)
    .delete(tug.stats_discovery.drop);
router.route('/cargo/stats/discovery/:stats_discovery_id')
    .get(tug.stats_discovery.view)
    .delete(tug.stats_discovery.erase);

// <><><><><><><><><><><><><><><><><><><><><><><>

router.route('/cargo/cmd/ipaddr')
    .get(tug.cmd_ipAddr.index)
    .delete(tug.cmd_ipAddr.drop);
router.route('/cargo/cmd/ipaddr/:cmd_ipAddr_id')
    .get(tug.cmd_ipAddr.view)
    .delete(tug.cmd_ipAddr.erase);

router.route('/cargo/cmd/ipnbr/ipaddr')
    .get(tug.cmd_IpNeighbors_ipAddr.index)
    .delete(tug.cmd_IpNeighbors_ipAddr.drop);
router.route('/cargo/cmd/ipnbr/ipaddr/:cmd_IpNeighbors_ipAddr_id')
    .get(tug.cmd_IpNeighbors_ipAddr.view)
    .delete(tug.cmd_IpNeighbors_ipAddr.erase);

router.route('/cargo/cmd/ipnbr/lladdr')
    .get(tug.cmd_IpNeighbors_llAddr.index)
    .delete(tug.cmd_IpNeighbors_llAddr.drop);
router.route('/cargo/cmd/ipnbr/lladdr/:cmd_IpNeighbors_llAddr_id')
    .get(tug.cmd_IpNeighbors_llAddr.view)
    .delete(tug.cmd_IpNeighbors_llAddr.erase);

router.route('/cargo/cmd/ipnbr/info')
    .get(tug.cmd_IpNeighbors_info.index)
    .delete(tug.cmd_IpNeighbors_info.drop);
router.route('/cargo/cmd/ipnbr/info/:cmd_IpNeighbors_info_id')
    .get(tug.cmd_IpNeighbors_info.view)
    .delete(tug.cmd_IpNeighbors_info.erase);

router.route('/cargo/cmd/tschstatus')
    .get(tug.cmd_tschStatus.index)
    .delete(tug.cmd_tschStatus.drop);
router.route('/cargo/cmd/tschstatus/:cmd_tschStatus_id')
    .get(tug.cmd_tschStatus.view)
    .delete(tug.cmd_tschStatus.erase);

router.route('/cargo/cmd/tschschedule')
    .get(tug.cmd_tschSchedule.index)
    .delete(tug.cmd_tschSchedule.drop);
router.route('/cargo/cmd/tschdchedule/:cmd_tschdchedule_id')
    .get(tug.cmd_tschSchedule.view)
    .delete(tug.cmd_tschSchedule.erase);

router.route('/cargo/cmd/routes/default')
    .get(tug.cmd_routes.index)
    .delete(tug.cmd_routes.drop);
router.route('/cargo/cmd/routes/default/:cmd_routes_id')
    .get(tug.cmd_routes.view)
    .delete(tug.cmd_routes.erase);

router.route('/cargo/cmd/routes/links/sources')
    .get(tug.cmd_routes_routingLinks_sources.index)
    .delete(tug.cmd_routes_routingLinks_sources.drop);
router.route('/cargo/cmd/routes/links/sources/:cmd_routes_routingLinks_sources_id')
    .get(tug.cmd_routes_routingLinks_sources.view)
    .delete(tug.cmd_routes_routingLinks_sources.erase);

router.route('/cargo/cmd/routes/links/destinations')
    .get(tug.cmd_routes_routingLinks_destinations.index)
    .delete(tug.cmd_routes_routingLinks_destinations.drop);
router.route('/cargo/cmd/routes/links/destinations/:cmd_routes_routingLinks_destinations_id')
    .get(tug.cmd_routes_routingLinks_destinations.view)
    .delete(tug.cmd_routes_routingLinks_destinations.erase);

router.route('/cargo/cmd/routes/entries/routes')
    .get(tug.cmd_routes_routingEntries_routes.index)
    .delete(tug.cmd_routes_routingEntries_routes.drop);
router.route('/cargo/cmd/routes/entries/routes/:cmd_routes_routingEntries_routes_id')
    .get(tug.cmd_routes_routingEntries_routes.view)
    .delete(tug.cmd_routes_routingEntries_routes.erase);

router.route('/cargo/cmd/routes/entries/vias')
    .get(tug.cmd_routes_routingEntries_vias.index)
    .delete(tug.cmd_routes_routingEntries_vias.drop);
router.route('/cargo/cmd/routes/entries/vias/:cmd_routes_routingEntries_vias_id')
    .get(tug.cmd_routes_routingEntries_vias.view)
    .delete(tug.cmd_routes_routingEntries_vias.erase);

router.route('/cargo/cmd/rplstatus/id')
    .get(tug.cmd_rplStatus.index)
    .delete(tug.cmd_rplStatus.drop);
router.route('/cargo/cmd/rplstatus/id/:cmd_rplStatus_id')
    .get(tug.cmd_rplStatus.view)
    .delete(tug.cmd_rplStatus.erase);

router.route('/cargo/cmd/rplstatus/dag')
    .get(tug.cmd_rplStatus_dag.index)
    .delete(tug.cmd_rplStatus_dag.drop);
router.route('/cargo/cmd/rplstatus/dag/:cmd_rplStatus_dag_id')
    .get(tug.cmd_rplStatus_dag.view)
    .delete(tug.cmd_rplStatus_dag.erase);

router.route('/cargo/cmd/rplstatus/time')
    .get(tug.cmd_rplStatus_trickleTimer.index)
    .delete(tug.cmd_rplStatus_trickleTimer.drop);
router.route('/cargo/cmd/rplstatus/time/:cmd_rplStatus_trickleTimer_id')
    .get(tug.cmd_rplStatus_trickleTimer.view)
    .delete(tug.cmd_rplStatus_trickleTimer.erase);

router.route('/cargo/cmd/rplnbr/addr')
    .get(tug.cmd_rplNbr_addr.index)
    .delete(tug.cmd_rplNbr_addr.drop);
router.route('/cargo/cmd/rplnbr/addr/:cmd_rplNbr_addr_id')
    .get(tug.cmd_rplNbr_addr.view)
    .delete(tug.cmd_rplNbr_addr.erase);

router.route('/cargo/cmd/rplnbr/ranks')
    .get(tug.cmd_rplNbr_ranks.index)
    .delete(tug.cmd_rplNbr_ranks.drop);
router.route('/cargo/cmd/rplnbr/ranks/:cmd_rplNbr_ranks_id')
    .get(tug.cmd_rplNbr_ranks.view)
    .delete(tug.cmd_rplNbr_ranks.erase);

router.route('/cargo/cmd/rplnbr/values')
    .get(tug.cmd_rplNbr_values.index)
    .delete(tug.cmd_rplNbr_values.drop);
router.route('/cargo/cmd/rplnbr/values/:cmd_rplNbr_values_id')
    .get(tug.cmd_rplNbr_values.view)
    .delete(tug.cmd_rplNbr_values.erase);

router.route('/cargo/cmd/rplnbr/parens')
    .get(tug.cmd_rplNbr_parens.index)
    .delete(tug.cmd_rplNbr_parens.drop);
router.route('/cargo/cmd/rplnbr/parens/:cmd_rplNbr_parens_id')
    .get(tug.cmd_rplNbr_parens.view)
    .delete(tug.cmd_rplNbr_parens.erase);

// <><><><><><><><><><><><><><><><><><><><><><><>

router.route('/cargo/errors')
    .get(tug.errorReport.index)
    .delete(tug.errorReport.drop);
router.route('/cargo/errors/:errorReport_id')
    .get(tug.errorReport.view)
    .delete(tug.errorReport.erase);

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// Body-parser enables your app to parse data 
// from incoming request like form data via urlencode. 
// We need to import this to our app and use them.

// Configure bodyparser to handle post requests
app.use(bodyParser.urlencoded({
    extended: true
 }));
 
// parsing body request to json
app.use(bodyParser.json());

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// Send message for default URL:
// http://localhost:8080

app.get('/', function(req, res){
    res.send('BUOY');
});

// Use Api routes in the App:
// http://localhost:8080/api

app.use('/api', router)

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// express configuration logic : 
// config for production or development

if(process.env.NODE_ENV === 'production') {

    // var PORT = null;

} else {

    var PORT = process.env.PORT || 8080;

}

// Launch app to listen to:
// http://localhost:8080

app.listen(PORT, function() {
    console.log("");
    console.log('~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~');
    console.log('buoy (listening on port: ' + PORT + ')');
    console.log('~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~');
});





















// https://stackoverflow.com/questions/9177049/express-js-req-body-undefined
// https://stackoverflow.com/a/13779626

// https://stackoverflow.com/questions/43227729/express-js-req-body-returns-empty
// https://stackoverflow.com/questions/43227729/express-js-req-body-returns-empty#comment73525765_43227729

// {"pckt":{"vld":true,"err":null},"rcrd":2,"ndx":0,"id":{"sT":7886,"adr":"0012.4b00.0f82.da03","cd":"BLUE"},"sys":{"cV":"Contiki-NG-release/v4.2-335-ga95cf54ef-dirty","rt":"RPL Lite","net":"sicslowpan","pId":"0xabcd","mac":{"t":"CSMA","tDhS":null,"dCh":26},"nId":55811,"tIad":"fe80::212:4b00:f82:da03"},"hash":392888623}

// $%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%
// POST /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%

app.post("/api/cargo", function(req, res) {

    const obj = checkProcessSaveReturn(req.body, true);

    obj.save()

        .then(data => {

            console.log();
            console.log('<<< POST: raw = ' + req.body);
            console.log('<<< POST: obj = ' + data);
            
            res.send({
                
                status: 'ok', 
                text: null,
                goto: null,
                data: data 
            });
    })
        
        .catch(err => {

            console.log();
            console.log('<<< POST: raw = ' + req.body);
            console.log('<<< POST: err = ' + err);
            
            res.send({
                
                status: 'error', 
                text: err,
                goto: null,
                data: null 
        });
    })

});

// $%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%
// POST /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// $%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%
// REPLACE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// $%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%

app.put("/api/cargo/:obj_id", function(req, res) {

    const obj = checkProcessSaveReturn(req.body, true);

    function getCollection(obj) {

        if(obj.packet.valid == true) {

            switch(obj.index) {

                case 0:
                    return System;
                case 1:
                    return Device;
                case 2:
                    return Energest;
                case 3:
                    return Stats_network_ip;
                case 4:
                    return Stats_network_icmp;
                case 5:
                    return Stats_transport;
                case 6:
                    return Stats_discovery;
                case 7:
                    return Cmd_ipAddr;
                case 8:
                    return Cmd_IpNeighbors_ipAddr;
                case 9:
                    return Cmd_ipNeighbors_llAddr;
                case 10:
                    return Cmd_ipNeighbors_info;
                case 11:
                    return Cmd_tschStatus;
                case 12:
                    return Cmd_tschSchedule;
                case 13:
                    return Cmd_routes;
                case 14:
                    return Cmd_routes_routingLinks_sources;
                case 15:
                    return Cmd_routes_routingLinks_destinations;
                case 16:
                    return Cmd_routes_routingEntries_routes;
                case 17:
                    return Cmd_routes_routingEntries_vias;
                case 18:
                    return Cmd_rplStatus;
                case 19:
                    return Cmd_rplStatus_dag;
                case 20:
                    return Cmd_rplStatus_trickleTimer;
                case 21:
                    return Cmd_rplNbr_addr;
                case 22:
                    return Cmd_rplNbr_ranks;
                case 23:
                    return Cmd_rplNbr_values;
                case 24:
                    return Cmd_rplNbr_parens;
            };
        
        } else {

            return ErrorReport;
        }         
        
    };
        
    getCollection(obj).deleteOne({_id: req.params.obj_id}, function(err, reply) {
        
        if (err) {

            console.log();
            console.log('<<< PUT: _id = '+ req.params.obj_id);
            console.log('<<< PUT: raw = '+ req.body);
            console.log('<<< PUT: obj = '+ obj);
            console.log('<<< PUT: err = '+ err);

            res.json({
                status: 'error',  
                text: err, 
                goto: null, 
                data: null
            })

        } else {
            
            if(reply.deletedCount == 0) {

                console.log();
                console.log('<<< PUT: _id = '+ req.params.obj_id);
                console.log('<<< PUT: raw = '+ req.body);
                console.log('<<< PUT: obj = '+ obj);
                console.log('<<< PUT: res = '+ reply);
                console.log('<<< PUT: err = '+ '_id unavailable');

                res.json({
                    status: 'error',  
                    text: '_id unavailable', 
                    goto: null, 
                    data: null
                })

            } else {

                obj.save()
                
                .then(data => {

                    console.log();
                    console.log('<<< PUT: _id = '+ req.params.obj_id);
                    console.log('<<< PUT: raw = '+ req.body);
                    console.log('<<< PUT: obj = '+ obj);
                    console.log('<<< PUT: res = '+ reply);
                    console.log('<<< PUT: dat = '+ data);
                    
                    res.send({
                        
                        status: 'ok', 
                        text: null,
                        goto: null,
                        data: data 
                    });
                })
                .catch(err => {

                    console.log();
                    console.log('<<< PUT: _id = '+ req.params.obj_id);
                    console.log('<<< PUT: raw = '+ req.body);
                    console.log('<<< PUT: obj = '+ obj);
                    console.log('<<< PUT: res = '+ reply);
                    console.log('<<< PUT: err = '+ err);
                    
                    res.send({
                        
                        status: 'error', 
                        text: err,
                        goto: null,
                        data: null 
                    });
                })
            };
        };
    })
});

// $%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%$%
// REPLACE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


app.patch("/api/cargo/:obj_id", function(req, res) {

    const raw = req.body;

    function getCollection(raw) {

        if(raw.pckt.vld == true) {

            switch(raw.ndx) {

                case 0:
                    return System;
                case 1:
                    return Device;
                case 2:
                    return Energest;
                case 3:
                    return Stats_network_ip;
                case 4:
                    return Stats_network_icmp;
                case 5:
                    return Stats_transport;
                case 6:
                    return Stats_discovery;
                case 7:
                    return Cmd_ipAddr;
                case 8:
                    return Cmd_IpNeighbors_ipAddr;
                case 9:
                    return Cmd_ipNeighbors_llAddr;
                case 10:
                    return Cmd_ipNeighbors_info;
                case 11:
                    return Cmd_tschStatus;
                case 12:
                    return Cmd_tschSchedule;
                case 13:
                    return Cmd_routes;
                case 14:
                    return Cmd_routes_routingLinks_sources;
                case 15:
                    return Cmd_routes_routingLinks_destinations;
                case 16:
                    return Cmd_routes_routingEntries_routes;
                case 17:
                    return Cmd_routes_routingEntries_vias;
                case 18:
                    return Cmd_rplStatus;
                case 19:
                    return Cmd_rplStatus_dag;
                case 20:
                    return Cmd_rplStatus_trickleTimer;
                case 21:
                    return Cmd_rplNbr_addr;
                case 22:
                    return Cmd_rplNbr_ranks;
                case 23:
                    return Cmd_rplNbr_values;
                case 24:
                    return Cmd_rplNbr_parens;
            };
        
        } else {

            return ErrorReport;
        }         
        
    };

    function checksum(obj) {

        try{
            
            let payloadHash = obj.hash;
            let goa = obj;
            delete goa.hash;
            goa = JSON.stringify(goa);
            let intact = sdbm(goa.substr(0, goa.length -1) + "," ) == payloadHash ? true : false;
            return intact;
        }
        catch(error) {
            console.log(error);
            let intact = false;
            return intact;
        }
    }

    function replace(obj, raw) {

        if(raw.pckt.vld === true) {
    
            switch(raw.ndx) {
    
                case 0: 
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.system = {
                        contikiVersion: raw.sys.cV,
                        networkStackRouting: raw.sys.rt,
                        networkStackNetwork: raw.sys.net,
                        ieee802154PANID: raw.sys.pId,
            
                        networkStackMac: {
                            name: raw.sys.mac.t,
                            tschDefaultHoppingSequence: raw.sys.mac.tDhS,
                            defaultChannel: raw.sys.mac.dCh
                        },
                        nodeId: raw.sys.nId,
                        tentaticeLinkLocalIPv6address: raw.sys.tIad
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                
                    return obj;
    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 1:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.device = {
                        temperatureSensor: raw.dev.tp,
                        humiditySensor: raw.dev.hd
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    return obj;
    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                
                case 2:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.energest = {
                        energest: raw.nrg.en,
                        cpu: raw.nrg.cp,
                        lpm: raw.nrg.lp,
                        deepLpm: raw.nrg.dL,
                        totalTime: raw.nrg.tT,
                        radioListening: raw.nrg.rL,
                        radioTransmiting: raw.nrg.rT,
                        radioOff: raw.nrg.rO
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    return obj;
                   
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 3:
                
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.stats_network_ip = {
                        uipStatistics: raw.ipSt.uS,
                        ip: {
                            ipRecv: raw.ipSt.ip.rx,
                            ipSent: raw.ipSt.ip.tx,
                            ipForwarded: raw.ipSt.ip.fw,
                            ipDrop: raw.ipSt.ip.dr,    
                            ipVhlerr: raw.ipSt.ip.vE,  
                            ipHblenerr: raw.ipSt.ip.hE,
                            ipLblenerr: raw.ipSt.ip.lE,
                            ipFragerr: raw.ipSt.ip.fE, 
                            ipChkerr: raw.ipSt.ip.cE, 
                            ipProtoerr: raw.ipSt.ip.pE
                        }
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    return obj;
                   
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 4:

                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj. mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.stats_network_icmp = {
                        uipStatistics: raw.icSt.uS,
                        icmp: {
                            icmpRecv: raw.icSt.ic.rx,    
                            icmpSent: raw.icSt.ic.tx,     
                            icmpDrop: raw.icSt.ic.dr,
                            icmpTypeerr: raw.icSt.ic.tE,     
                            icmpChkerr: raw.icSt.ic.cE  
                        } 
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 5:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.stats_transport = {
                        uipStatistics: raw.tSt.uS,
                        tcp: {
                            tcp: raw.tSt.tcp.use,        
                            tcpRecv: raw.tSt.tcp.rx,    
                            tcpSent: raw.tSt.tcp.tx,    
                            tcpDrop: raw.tSt.tcp.dr,    
                            tcpChkerr: raw.tSt.tcp.cE,  
                            tcpAckerr: raw.tSt.tcp.aA,  
                            tcpRst: raw.tSt.tcp.rst,     
                            tcpRexmit: raw.tSt.tcp.rM,  
                            tcpSyndrop: raw.tSt.tcp.sD, 
                            tcpSynrst: raw.tSt.tcp.sR  
                        },
                        udp: {
                            udp: raw.tSt.udp.use,  
                            udpDrop: raw.tSt.udp.dr,
                            udpRecv: raw.tSt.udp.rx,  
                            udpSent: raw.tSt.udp.tx,  
                            udpChkerr: raw.tSt.udp.cE
                        } 
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date

                    return obj;
                   
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 6:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.stats_discovery = {
                        uipStatistics: raw.dSt.uS,
                        nd6: {
                            nd6drop: raw.dSt.nd6.dr,
                            nd6recv: raw.dSt.nd6.rx,
                            nd6sent: raw.dSt.nd6.tx
                        } 
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 7:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    },
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_ipAddr = {
                        ipv6: raw.addr.IPv6,
                        nodeIPv6addresses: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
    
                    raw.addr.ad.forEach((address, index) => obj.cmd_ipAddr.nodeIPv6addresses[index] = {nodeIPv6address: address});
                    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 8:

                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_IpNeighbors_ipAddr = {
                        ipv6: raw.nsIP.IPv6,
                        nodeIPv6neighborIpAddresses: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                   
                    raw.nsIP.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                            obj.cmd_IpNeighbors_ipAddr.nodeIPv6neighborIpAddresses[index] = {nodeIPv6neighborIpAddress: neighbor.cmd_ipAddr}
                        } else {
                            obj.cmd_IpNeighbors_ipAddr.nodeIPv6neighborIpAddresses[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 9:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_ipNeighbors_llAddr = {
                        ipv6: raw.nsLL.IPv6,
                        nodeIPv6neighborLlAddresses: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    raw.nsLL.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                            obj.cmd_ipNeighbors_llAddr.nodeIPv6neighborLlAddresses[index] = {nodeIPv6neighborLlAddress: neighbor.llAddr}
                        } else {
                            obj.cmd_ipNeighbors_llAddr.nodeIPv6neighborLlAddresses[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 10:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_ipNeighbors_info = {
                        ipv6: raw.nsSt.IPv6,
                        nodeIPv6neighborInfo: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    raw.nsSt.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                           obj.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = {nodeIPv6neighborRouter: neighbor.router, nodeIPv6neighborState: neighbor.state}
                        } else {
                            obj.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = null
                        }
                    });
                    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 11:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_tschStatus = {
                        tsch: obj.tsch.tsch,
                        isCoordinator: obj.tsch.coo,
                        isAssociated: obj.tsch.ass,
                        panID: obj.tsch.panid,
                        panSecured: obj.tsch.pansec,
                        joinPriority: obj.tsch.joinp,
                        timeSource: obj.tsch.tsrc,
                        lastSynchronized: obj.tsch.lsyn,
                        driftWRTCoordinator: obj.tsch.drift,
                        networkUptime: obj.tsch.netup
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                   
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                case 12:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.tschSchedule = {
                        tsch: obj.tschSch.tsch,
                        isLocked: obj.tschSch.lock,
                        schedule: obj.tschSch.sch,
                        slotframes: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date

                    obj.tschSch.slts.forEach(function(slotframe, index) {
                        if (slotframe != null) {
                            cmd_tschSchedule.cmd_tschSchedule.slotframes[index] = {handle: slotframe.hdl, size: neighbor.sz, links: [null]}
                            obj.tschSch.slts.lnks.forEach(function(link, linkindex) {
                                if (link != null) {
                                    cmd_tschSchedule.cmd_tschSchedule.slotframes[index].links[linkindex] = {options: link.opt, type: link.tp, timeslot: link.tslt, channelOffset: link.chOf, address: link.ad}
                                } else {
                                    cmd_tschSchedule.cmd_tschSchedule.slotframes[index].links[linkindex] = null
                                }
                            }) 
                        } else {
                            cmd_tschSchedule.cmd_tschSchedule.slotframes[index] = null
                        }
                    });
                   
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
                
                case 13:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_routes = {
                        ipv6: raw.rt.IPv6,
                        defaultRoute: raw.rt.df,
                        lifetime: raw.rt.lt
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                   
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 14:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_routes_routingLinks_sources = {
                        ipv6: raw.rtLS.IPv6,
                        rpl: raw.rtLS.rpl,
                        totalRoutingLinks: raw.rtLS.totLs,
                        routeSources: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
    
                    raw.rtLS.ls.forEach(function(link, index) {
                        if (link != null) {
                            obj.cmd_routes_routingLinks_sources.routeSources[index] = {linkSourceAddr: link.from, dodagRoot: link.dodagRoot}
                        } else {
                            obj.cmd_routes_routingLinks_sources.routeSources[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 15:
                    
                        obj.packet = {
                            valid: raw.pckt.vld,
                            error: null
                        }
                        obj.record = raw.rcrd
                        obj.index = raw.ndx
                        obj.mote = {
                            systemTime: raw.id.sT,
                            linkLayerAddress: raw.id.adr,
                            moteCode: raw.id.cd
                        }
                        obj.cmd_routes_routingLinks_destinations = {
                            ipv6: raw.rtLD.IPv6,
                            rpl: raw.rtLD.rpl,
                            totalRoutingLinks: raw.rtLD.totLs,
                            routeDestinations: [null]
                        }
                        obj.checksum = {
                            hash: raw.hash,
                            check: checksum(raw)
                        }
                        obj.update = new Date
                    
    
                    raw.rtLD.ls.forEach(function(link, index) {
                        if (link != null) {
                            obj.cmd_routes_routingLinks_destinations.routeDestinations[index] = {linkDestinationAddr: link.to, lifetime: link.lf}
                        } else {
                            obj.cmd_routes_routingLinks_destinations.routeDestinations[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 16:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_routes_routingEntries_routes = {
                        ipv6: raw.rtERt.IPv6,
                        maxRoutesNon0: raw.rtERt.maxRtsN0,
                        totalRoutingEntries: raw.rtERt.totEs,
                        routes: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                
                    raw.rtERt.es.forEach(function(entry, index) {
                        if (entry != null) {
                            obj.cmd_routes_routingEntries_routes.routes[index] = {entryRouteAddr: entry.rt}
                        } else {
                            obj.cmd_routes_routingEntries_routes.routes[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 17:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_routes_routingEntries_vias = {
                        ipv6: raw.rtEVia.IPv6,
                        maxRoutesNon0: raw.rtEVia.maxRtsN0,
                        totalRoutingEntries: raw.rtEVia.totEs,
                        vias: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
    
                    raw.rtEVia.es.forEach(function(entry, index) {
                        if (entry != null) {
                            obj.cmd_routes_routingEntries_vias.vias[index] = {entryViaAddr: entry.via, lifetime: entry.lf}
                        } else {
                            obj.cmd_routes_routingEntries_vias.vias[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 18:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_rplStatus = {
                        rplLite: raw.rSt.rL,
                        instance: raw.rSt.iId,
                        modeOfOperation: raw.rSt.mop,
                        rawectiveCodePoint: raw.rSt.of,
                        hopRankIncrement: raw.rSt.hRkI,
                        defaultLifetime: raw.rSt.dLt,
                        dtsnOut: raw.rSt.dtsnO
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 19:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_rplStatus_dag = {
                        rplLite: raw.rStDag.rL,
                        instance: raw.rStDag.iId,
                        dagRole: raw.rStDag.dT,
                        dagId: raw.rStDag.dId,
                        dagVersion: raw.rStDag.dVer,
                        dagPrefix: raw.rStDag.dPf,
                        dagPrefixLength: raw.rStDag.dPfL,
                        dagState: raw.rStDag.st,
                        dagPreferedParent: raw.rStDag.pP,
                        dagPreferedParentLastDTSN: raw.rStDag.lD,
                        dagRank: raw.rStDag.rk,
                        dagLowestRank: raw.rStDag.lRk,
                        maxRankIncrement: raw.rStDag.mRkI,
                        dao: {
                            daoSequenceLastSent: raw.rStDag.dao.lS,
                            daoSequenceLastAcked: raw.rStDag.dao.lA
                        }
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                   
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 20:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_rplStatus_trickleTimer = {
                        rplLite: raw.rStTt.rL,
                        instance: raw.rStTt.iId,
                        current: raw.rStTt.cur,
                        min: raw.rStTt.min, 
                        max: raw.rStTt.max,
                        redundancy: raw.rStTt.red
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 21:
                    
                        obj.packet = {
                            valid: raw.pckt.vld,
                            error: null
                        }
                        obj.record = raw.rcrd
                        obj.index = raw.ndx
                        obj.mote = {
                            systemTime: raw.id.sT,
                            linkLayerAddress: raw.id.adr,
                            moteCode: raw.id.cd
                        }
                        obj.cmd_rplNbr_addr = {
                            rplLite: raw.rN.rL,
                            instance: raw.rN.iId,
                            rplNeighborCount: raw.rN.c,
                            addresses: [null]
                        }
                        obj.checksum = {
                            hash: raw.hash,
                            check: checksum(raw)
                        }
                        obj.update = new Date
                    
    
                    raw.rN.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                            obj.cmd_rplNbr_addr.addresses[index] = {rplAddress: neighbor.ad}
                        } else {
                            obj.cmd_rplNbr_addr.addresses[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 22:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_rplNbr_ranks = {
                        rplLite: raw.rNR.rL,
                        instance: raw.rNR.iId,
                        rplNeighborCount: raw.rNR.c,
                        ranks: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    raw.rNR.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                            obj.cmd_rplNbr_ranks.ranks[index] = {rplNeighborRank: neighbor.rk, rplNeighborLinkMetric: neighbor.lM, rplNeighborRankViaNeighbor: neighbor.rkN}
                        } else {
                            obj.cmd_rplNbr_ranks.ranks[index] = null
                        }
                    });
    
                    return obj;
                    
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 23:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_rplNbr_values = {
                        rplLite: raw.rNV.rL,
                        instance: raw.rNV.iId,
                        rplNeighborCount: raw.rNV.c,
                        values: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    raw.rNV.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                            obj.cmd_rplNbr_values.values[index] = {rplNeighborStatsFreshness: neighbor.fr, rplNeighborRootRank: neighbor.r, rplNeighborBest: neighbor.b, rplNeighborAcceptableRankParent: neighbor.a, rplNeighborLinkStatsFresh: neighbor.f, rplNeighborDagPreferredParent: neighbor.p}
                        } else {
                            obj.cmd_rplNbr_values.values[index] = null
                        }
                    });
    
                    return obj;
                   
                // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
                case 24:
                    
                    obj.packet = {
                        valid: raw.pckt.vld,
                        error: null
                    }
                    obj.record = raw.rcrd
                    obj.index = raw.ndx
                    obj.mote = {
                        systemTime: raw.id.sT,
                        linkLayerAddress: raw.id.adr,
                        moteCode: raw.id.cd
                    }
                    obj.cmd_rplNbr_parens = {
                        rplLite: raw.rNP.rL,
                        instance: raw.rNP.iId,
                        rplNeighborCount: raw.rNP.c,
                        parens: [null]
                    }
                    obj.checksum = {
                        hash: raw.hash,
                        check: checksum(raw)
                    }
                    obj.update = new Date
                    
                    raw.rNP.ns.forEach(function(neighbor, index) {
                        if (neighbor != null) {
                            obj.cmd_rplNbr_parens.parens[index] = {rplNeighborLastTXtimeSeconds: neighbor.lTx, rplNeighborBetterParentSinceSeconds: neighbor.bS}
                        } else {
                            obj.cmd_rplNbr_parens.parens[index] = null
                        }
                    });
    
                    return obj;              
            }
        } else {
    
            
                obj.packet = {
                    valid: raw.pckt.vld,
                    error: {
                        text: raw.err.txt,
                        code: raw.err.cd
                    }
                }
                obj.mote = {
                    systemTime: raw.id.sT,
                    linkLayerAddress: raw.id.adr,
                    moteCode: raw.id.cd
                }
                obj.checksum = {
                    hash: raw.hash,
                    check: checksum(raw)
                }
                obj.update = new Date
            
            return obj;
        }
    
    }
        
    getCollection(raw).findById(req.params.obj_id, function(err, obj) {
        if (err) {

            console.log();
            console.log('<<< PATCH: _id = '+ req.params.obj_id);
            console.log('<<< PATCH: raw = '+ req.body);
            console.log('<<< PATCH: chk = '+ checksum(raw));
            console.log('<<< PATCH: col = '+ getCollection(raw));
            console.log('<<< PATCH: err = '+ err);

            res.json({
                status: 'error',  
                text: err, 
                goto: null, 
                data: null
            })
        } else {
            
            console.log();
            console.log('<<< PATCH: _id = '+ req.params.obj_id);
            console.log('<<< PATCH: raw = '+ req.body);
            console.log('<<< PATCH: chk = '+ checksum(raw));
            console.log('<<< PATCH: col = '+ getCollection(raw));
            console.log('<<< PATCH: obj = '+ obj);

            if(obj == null) {
                res.json({
                    status: 'error',  
                    text: '_id unavailable', 
                    goto: null, 
                    data: null
                })
            } else {

                replace(obj, raw).save(function(err) {
                    if (err) {
                        res.json({
                            status: 'error',  
                            text: err, 
                            goto: null, 
                            data: null
                        })
                    } else {
                        res.json({
                            status: 'ok',     
                            text: null, 
                            goto: null, 
                            data: obj 
                        });
                    };
                })
            }
        }
    })
});
















// // secure express apps: protect the express app with various HTTP Header Protection)
// app.use(helmet());

// // filter and setting the allowed origin that can access the server
// const corsOptions = {origin: true, credentials: true};
// app.use(cors(corsOptions));

// // parsing body request to json
// // Body-parser enables your app to parse data from incoming request like form data via urlencode. 
// // We need to import this to our app and use them.
// app.use(bodyParser.json());

// // HTTP request logger with Morgan








































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

// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// PEACE BUOY // NUKE DISABLED //////////////////////////////////////////////////////////////////////////////////////
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// function moor() {
//     request.get('http://[fd00::212:4b00:f82:da03]/',function(err, res, body ){ 
        
//         if(err) {
//                 console.log(err);
//                 return;
//             }

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// WAR BUOY // NUKE ENABLED /////////////////////////////////////////////////////////////////////////////////////////
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

function moor(host, port, path) {
    request.get(`http://[${host}]:${port}/${path}`,function(err, res, body ){ 
        
        if(err) {
            console.log();
            console.log(err);
            return;
        }

// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
        
        // console.log("");
        // console.log('<--- oar (http://[fd00::212:4b00:f83:b601]/) <--- <--- <---');
        
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
                
                checkProcessSaveReturn(obj, false);

            } catch(e) {

                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                // JSON PARSE: FAIL ///////////////////////////////////////////////////////////////
                // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

                // print that json failed to parse 
                // to console for debugging purposes

                // console.log("");
                // console.error(e);

                // print the error that caused parse to fail 
                // to console for debugging purposes

                console.log();
                console.error(e); // error in the above string (in this case, yes)!
                
            }
        }
    });
}



















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// moor() EVERY 5000 ms ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/
// !/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/!/

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// PEACE BUOY // NUKE DISABLED //////////////////////////////////////////////////////////////////////////////////////
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// setInterval(moor, 5000);

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// WAR BUOY // NUKE ENABLED /////////////////////////////////////////////////////////////////////////////////////////
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// nodeHosts[] array will hold the nodes scraped addr
// found at the index.html served by border router

// nodePaths[] array will hold the paths of the GET 
// (every path corresponds to a discrete resource)
// requests that our middleware sends to the nodes

var nodeHosts = new Array; // scrapted nodes' host addresses
var nodePorts = new Array; // nodes' http server port (default: 80)
var nodePaths = new Array; // nodes' requested resource



// attempting to scrap border router's index.html

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function activateScrap(borderRouter, interval) {

    scrap(nodeHosts, borderRouter, function(nodeHosts) {

        // initializations
    
        nodeHosts.forEach(function(node, index){
            
            nodePorts[index] = 80;
    
            // paths are being initialized: -1 
            // will be incremented to 0 at first call
            
            nodePaths[index] = -1;
        });
        
        console.log();
        console.log("HOSTS: " + nodeHosts);
        console.log("PORTS: " + nodePorts);
        console.log("PATHS: " + nodePaths);
        
        // console.log("TOTAL NODES: " + nodeHosts.length);
    
        let activeNodeIndex = -1;
    
        var monitorInterval = setInterval(function() {
        
            activeNodeIndex++;              
            activeNodeIndex = activeNodeIndex % nodeHosts.length; // incerement the active node index
            
            nodePaths[activeNodeIndex]++;   
            nodePaths[activeNodeIndex] = nodePaths[activeNodeIndex] % 25;
        
            console.log();
            console.log('</> </> </> </> </> </> </> </> </>');
            console.log(`</> QUERING NODE: ${activeNodeIndex + 1} / TOTAL: ${nodeHosts.length}  </>`);
            console.log('</> </> </> </> </> </> </> </> </>');
        
            console.log();
            console.log(`---> ---> ---> GET ---> http://[${nodeHosts[activeNodeIndex]}:${nodePorts[activeNodeIndex]}/${nodePaths[activeNodeIndex]} ---> ---> ---> ---> ---> ---> ---> ---> --->`);
            
            moor(nodeHosts[activeNodeIndex], nodePorts[activeNodeIndex], nodePaths[activeNodeIndex]);
            
        }, interval)
        
    });    
};




















// *-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*
// *-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*
// *-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*-|-*

// https://medium.com/the-node-js-collection/making-your-node-js-work-everywhere-with-environment-variables-2da8cdf6e786

const borderRouter = 'http://[fd00::212:4b00:f24:8385]/'; 

if(process.env.auto) {
    if(process.env.br) {
        
        console.log();
        console.log();
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]');
        console.log('[!][!][!] AUTO > BORDER ROUTER SCRAPE:   ACTIVATED [!][!][!]');
        console.log('[!][!][!] AUTO > PERIODIC NODE QUERY:    ACTIVATED [!][!][!]');
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]');
        
        console.log();
        console.log('INTERVAL: ' + process.env.auto + 'ms');

        activateScrap(process.env.br, process.env.auto);
    
    } else {

        console.log();
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]');
        console.log('[!][!][!] AUTO > BORDER ROUTER SCRAPE:   ACTIVATED [!][!][!]');
        console.log('[!][!][!] AUTO > PERIODIC NODE QUERY:    ACTIVATED [!][!][!]');
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]');
        
        console.log();
        console.log('INTERVAL: ' + process.env.auto + 'ms');
        
        activateScrap(borderRouter, process.env.auto);
    };

} else {

    if(process.argv[2] == '--auto') {

        console.log();
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]');
        console.log('[!][!][!] AUTO > BORDER ROUTER SCRAPE:   ACTIVATED [!][!][!]');
        console.log('[!][!][!] AUTO > PERIODIC NODE QUERY:    ACTIVATED [!][!][!]');
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!][!]');
        
        console.log();
        console.log('INTERVAL: ' + 5000 + 'ms');

        activateScrap(borderRouter, 5000);

    } else {

        console.log();
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!]');
        console.log('[!][!][!] AUTO: DISABLED   [!][!][!]');
        console.log('[!][!][!][!][!][!][!][!][!][!][!][!]');
    }
}




















// yellow:  fd00::212:4b00:f24:8385
// red:     fd00::212:4b00:f83:b601
// green:   fd00::212:4b00:f82:a600
// blue:    fd00::212:4b00:f82:da03

