// // https://github.com/sindresorhus/sdbm
// const sdbm = string => {
// 	let hash = 0;

// 	for (let i = 0; i < string.length; i++) {
// 		hash = string.charCodeAt(i) + (hash << 6) + (hash << 16) - hash;
// 	}

// 	// Convert it to an unsigned 32-bit integer
// 	return hash >>> 0;
// };

// https://stackoverflow.com/a/7220510
// function syntaxHighlight(json) {
//     if (typeof json != 'string') {
//          json = JSON.stringify(json, undefined, 2);
//     }
//     json = json.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
//     return json.replace(/("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g, function (match) {
//         var cls = 'number';
//         if (/^"/.test(match)) {
//             if (/:$/.test(match)) {
//                 cls = 'key';
//             } else {
//                 cls = 'string';
//             }
//         } else if (/true|false/.test(match)) {
//             cls = 'boolean';
//         } else if (/null/.test(match)) {
//             cls = 'null';
//         }
//         return '<span class="' + cls + '">' + match + '</span>';
//     });
// }


// https://stackoverflow.com/questions/36631762/returning-html-with-fetch
// https://stackoverflow.com/a/50812705
// https://www.codecademy.com/articles/what-is-cors

// http://[fd00::212:4b00:f24:8385]/

console.log('hello world');


///////////////////////////////////////////////////////////////////////////////
// FUNCTIONS //////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

function oarCrypt(input, key) {
    // var key = ['!', '@', '#', '$', '%', '^', '&', '*'];
    var output = [];
    
    for (var i = 0; i < input.length; i++) {
        var charCode = input.charCodeAt(i) ^ (key[i % key.length].charCodeAt(0));
        output.push(String.fromCharCode(charCode));
    }
    return output.join("");
}

// SDBM non-cryptographic hash function
// https://github.com/sindresorhus/sdbm

const sdbm = string => {
	let hash = 0;

	for (let i = 0; i < string.length; i++) {
		hash = string.charCodeAt(i) + (hash << 6) + (hash << 16) - hash;
	}

	// Convert it to an unsigned 32-bit integer
	return hash >>> 0;
};

// generate nodes-input section
// construct GET requests to nodes
// query nodes specifying path

function nodesInputHTML(nodesAddr) {
    
    let nodesInputHTML = ''

    if(nodesAddr == undefined) {

        nodesInputHTML += ` 
        <div class="p-2 p-auto m-2 m-auto input-group"> 
            <div class="input-group-prepend"> 
                <button class="btn btn-secondary" type="button" id="nodes-button-0">GET</button>  
            </div> 
            <div class="input-group-prepend"> 
                <span class="input-group-text bg-dark border-secondary text-secondary">http://</span>  
            </div> 
            <input type="text" class="form-control" placeholder="[fd:: ]" id="nodes-addr-input-0"></input> 
            <div class="input-group-append"> 
                <span class="input-group-text bg-dark border-secondary text-secondary">/</span> 
            </div>
                <input type="number" class="form-control bg-dark text-light border-secondary"  id="nodes-path-input-0"></input> 
            </div>
            <div class="row text-center justify-content-center" id="nodes-output-0">
        </div>`
    }

    nodesAddr.forEach((node, index) => {

        nodesInputHTML += `
            <div class="p-2 p-auto m-2 m-auto input-group"> 
                <div class="input-group-prepend"> 
                    <button class="btn btn-primary" type="button" id="nodes-button-${index}">GET</button>  
                </div> 
                <div class="input-group-prepend"> 
                    <span class="input-group-text">http://</span>  
                </div> 
                <input type="text" class="form-control" value='${node}' id="nodes-addr-input-${index}"></input> 
                <div class="input-group-append"> 
                    <span class="input-group-text">/</span> 
                </div>
                    <input type="number" class="form-control"  id="nodes-path-input-${index}"></input> 
            </div>
            <div class="row text-center justify-content-center" id="nodes-output-${index}">
        </div>`
    })

    nodesInputHTML += `<div class="container" id="nodes-response"></div>`

    return nodesInputHTML;

}

function constructLegend(content, appendix) {

    legendDiv.classList.replace('d-none', 'd-block');

    legendContent.innerHTML = content;
    legendAppendix.innerHTML = appendix;
}

function elaborate(obj, intact) {

    if(obj.pckt.vld === true) {

        switch(obj.ndx) {

            case 0: 
                
                var system = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return system;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 2:
                
                var energest = {
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
                        radioOff: obj.nrg.r0
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return energest;
               
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 3:
                
                var stats_network_ip = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };
                
                return stats_network_ip;
               
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 4:
                
                var stats_network_icmp = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return stats_network_icmp;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 5:
                var stats_transport = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return stats_transport;
               
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 6:
                var stats_discovery = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return stats_discovery;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 7:
                var cmd_ipAddr = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.addr.ad.forEach((address, index) => cmd_ipAddr.cmd_ipAddr.nodeIPv6addresses[index] = {nodeIPv6address: address});
                
                return cmd_ipAddr;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 8:
                var cmd_IpNeighbors_ipAddr = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.nsIP.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_IpNeighbors_ipAddr.cmd_IpNeighbors_ipAddr.nodeIPv6neighborIpAddresses[index] = {nodeIPv6neighborIpAddress: neighbor.cmd_ipAddr}
                    } else {
                        cmd_IpNeighbors_ipAddr.cmd_IpNeighbors_ipAddr.nodeIPv6neighborIpAddresses[index] = null
                    }
                });

                return cmd_IpNeighbors_ipAddr;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 9:
                var cmd_ipNeighbors_llAddr = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.nsLL.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_ipNeighbors_llAddr.cmd_ipNeighbors_llAddr.nodeIPv6neighborLlAddresses[index] = {nodeIPv6neighborLlAddress: neighbor.llAddr}
                    } else {
                        cmd_ipNeighbors_llAddr.cmd_ipNeighbors_llAddr.nodeIPv6neighborLlAddresses[index] = null
                    }
                });

                return cmd_ipNeighbors_llAddr;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 10:
                var cmd_ipNeighbors_info = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.nsSt.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_ipNeighbors_info.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = new{nodeIPv6neighborRouter: neighbor.router, nodeIPv6neighborState: neighbor.state}
                    } else {
                        cmd_ipNeighbors_info.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = null
                    }
                });
                
                return cmd_ipNeighbors_info;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 11:
                var cmd_routes ={
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_routes;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 12:
                var cmd_routes_routingLinks_sources = new {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rtLS.ls.forEach(function(link, index) {
                    if (link != null) {
                        cmd_routes_routingLinks_sources.cmd_routes_routingLinks_sources.routeSources[index] = new LinkSource({linkSourceAddr: link.from, dodagRoot: link.dodagRoot})
                    } else {
                        cmd_routes_routingLinks_sources.cmd_routes_routingLinks_sources.routeSources[index] = null
                    }
                });

                return cmd_routes_routingLinks_sources;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 13:
                var cmd_routes_routingLinks_destinations = new {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rtLD.ls.forEach(function(link, index) {
                    if (link != null) {
                        cmd_routes_routingLinks_destinations.cmd_routes_routingLinks_destinations.routeDestinations[index] = new {linkDestinationAddr: link.to, lifetime: link.lf}
                    } else {
                        cmd_routes_routingLinks_destinations.cmd_routes_routingLinks_destinations.routeDestinations[index] = null
                    }
                });

                return cmd_routes_routingLinks_destinations;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 14:
                var cmd_routes_routingEntries_routes = new {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rtERt.es.forEach(function(entry, index) {
                    if (entry != null) {
                        cmd_routes_routingEntries_routes.cmd_routes_routingEntries_routes.routes[index] = {entryRouteAddr: entry.rt}
                    } else {
                        cmd_routes_routingEntries_routes.cmd_routes_routingEntries_routes.routes[index] = null
                    }
                });

                return cmd_routes_routingEntries_routes;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 15:
                var cmd_routes_routingEntries_vias = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rtEVia.es.forEach(function(entry, index) {
                    if (entry != null) {
                        cmd_routes_routingEntries_vias.cmd_routes_routingEntries_vias.vias[index] = new {entryViaAddr: entry.via, lifetime: entry.lf}
                    } else {
                        cmd_routes_routingEntries_vias.cmd_routes_routingEntries_vias.vias[index] = null
                    }
                });

                return cmd_routes_routingEntries_vias;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 16:
                var cmd_rplStatus = {
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
                        dtsnOut: obj.rSt.dtsn0
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_rplStatus;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 17:
                var cmd_rplStatus_dag = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_rplStatus_dag;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 18:
                var cmd_rplStatus_trickleTimer = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_rplStatus_trickleTimer;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 19:
                var cmd_rplNbr_addr = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rN.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_addr.cmd_rplNbr_addr.addresses[index] = new {rplAddress: neighbor.ad}
                    } else {
                        cmd_rplNbr_addr.cmd_rplNbr_addr.addresses[index] = null
                    }
                });

                return cmd_rplNbr_addr;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 20:
                var cmd_rplNbr_ranks = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rNR.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_ranks.cmd_rplNbr_ranks.ranks[index] = {rplNeighborRank: neighbor.rk, rplNeighborLinkMetric: neighbor.lM, rplNeighborRankViaNeighbor: neighbor.rkN}
                    } else {
                        cmd_rplNbr_ranks.cmd_rplNbr_ranks.ranks[index] = null
                    }
                });

                return cmd_rplNbr_ranks;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 21:
                var cmd_rplNbr_values = {
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
                        values: [rplValuesSchema]
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rNV.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_values.cmd_rplNbr_values.values[index] = {rplNeighborStatsFreshness: neighbor.fr, rplNeighborRootRank: neighbor.r, rplNeighborBest: neighbor.b, rplNeighborAcceptableRankParent: neighbor.a, rplNeighborLinkStatsFresh: neighbor.f, rplNeighborDagPreferredParent: neighbor.p}
                    } else {
                        cmd_rplNbr_values.cmd_rplNbr_values.values[index] = null
                    }
                });

                return cmd_rplNbr_ranks;
               
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 22:
                var cmd_rplNbr_parens = {
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
                        parens: [rplParensSchema]
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rNP.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_parens.cmd_rplNbr_parens.parens[index] = {rplNeighborLastTXtimeSeconds: neighbor.lTx, rplNeighborBetterParentSinceSeconds: neighbor.bs}
                    } else {
                        cmd_rplNbr_parens.cmd_rplNbr_parens.parens[index] = null
                    }
                });

                return cmd_rplNbr_parens;              
        }
    } else {

        var errorReport = {
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
                hash: obj.hash,
                check: intact
            },
            update: new Date
        };

        return errorReport;
    }

}


///////////////////////////////////////////////////////////////////////////////
// STATIC HTML ELEMENTS GLOBAL DECLARATIONS ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

const brDiv = document.getElementById('br-div');
const brButton = document.getElementById('br-button');

const brInput = document.getElementById('br-input');
const brOutput = document.getElementById('br-output');

const neighborsElement = document.getElementById('neighbors');
const routingLinksElement = document.getElementById('routing-links');

const brButtonReload = document.getElementById('br-button-reload');
const brButtonClear = document.getElementById('br-button-clear');
const brButtonContinue = document.getElementById('br-button-continue');

// NODES

const nodesDiv = document.getElementById('nodes-div');
const nodesH1 = document.getElementById('nodes-h1');

const nodesButtonIndex = document.getElementById('nodes-button-index');

const nodesInput = document.getElementById('nodes-input');

const nodesEncodedResponseDiv = document.getElementById('nodes-encoded-response-div');
const nodesButtonDecode = document.getElementById('nodes-button-decode');

const nodesEncryptedResponseDiv = document.getElementById('nodes-encrypted-response-div');
const nodesButtonDecrypt = document.getElementById('nodes-button-decrypt');

// const nodesKeySpan = document.getElementById('nodes-key-span');
const nodesKeyInput = document.getElementById('nodes-key-input');

const nodesStringifiedResponseDiv = document.getElementById('nodes-stringified-response-div');

const nodesButtonParse = document.getElementById('nodes-button-parse');
const nodesButtonChecksum = document.getElementById('nodes-button-checksum');

const nodesOutputChecksum = document.getElementById('nodes-output-checksum');
const nodesParsedResponseDiv = document.getElementById('nodes-parsed-response-div');

const nodesButtonReload = document.getElementById('nodes-button-reload');
const nodesButtonClear = document.getElementById('nodes-button-clear');
const nodesButtonContinue = document.getElementById('nodes-button-continue');

// CONSOLE

const consoleDiv = document.getElementById('console-div');
const consoleH1 = document.getElementById('console-h1');

const consoleButtonReload = document.getElementById('console-button-reload');
const consoleButtonClear = document.getElementById('console-button-clear');
const consoleButtonContinue = document.getElementById('console-button-continue');

// LEGEND

const legendDiv = document.getElementById('legend-div');
const legendContent = document.getElementById('legend-content');
const legendAppendix = document.getElementById('legend-appendix')










///////////////////////////////////////////////////////////////////////////////
// RELOAD BUTTONS FUNCTIONALITY ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

brButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});

// NODES

nodesButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});


///////////////////////////////////////////////////////////////////////////////
// CLEAR BUTTONS FUNCTIONALITY ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

brButtonClear.addEventListener('click', () => {
                        
    brDiv.classList.remove('border-danger', 'border-warning', 'border-success');
    brDiv.classList.add('border-info');
    
    neighborsElement.innerHTML = '';
    routingLinksElement.innerHTML = '';
    
    brOutput.classList.replace('d-block', 'd-none');
    nodesEncodedResponseDiv.innerText = ''
})

// NODES

nodesButtonClear.addEventListener('click', () => {

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-success');
    nodesDiv.classList.add('border-primary');

    nodesButtonIndex.classList.replace('d-none', 'd-block');

    nodesInput.innerHTML = '';

    nodesEncodedResponseDiv.classList.replace('d-block', 'd-none');
    nodesEncryptedResponseDiv.classList.replace('d-block', 'd-none');
    nodesStringifiedResponseDiv.classList.replace('d-block', 'd-none');
    
    nodesEncodedResponseDiv.classList.replace('text-dark', 'text-light');
    nodesEncodedResponseDiv.innerText = '_';
    nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-light');
    nodesEncryptedResponseDiv.innerText = '_';
    nodesStringifiedResponseDiv.classList.replace('text-dark', 'text-light');
    nodesStringifiedResponseDiv.innerText = '_';

    nodesButtonDecode.classList.replace('d-block', 'd-none');
    nodesButtonDecrypt.classList.replace('d-block', 'd-none');
    nodesButtonChecksum.classList.replace('d-block', 'd-none');
    nodesButtonParse.classList.replace('d-block', 'd-none');
    
    nodesButtonDecode.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonDecode.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonDecode.classList.add('btn-muted');
    nodesButtonDecrypt.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonDecrypt.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonDecrypt.classList.add('btn-muted');
    nodesButtonChecksum.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonChecksum.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonChecksum.classList.add('btn-muted');
    nodesButtonParse.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary', 'btn-outline-secondary');
    nodesButtonParse.classList.remove('btn-danger', 'btn-warning', 'btn-success', 'btn-primary', 'btn-secondary');
    nodesButtonParse.classList.add('btn-muted');

    nodesEncodedResponseDiv.classList.replace('bg-dark', 'bg-secondary');
    nodesEncodedResponseDiv.classList.replace('text-secondary', 'text-light');
    nodesEncryptedResponseDiv.classList.replace('bg-dark', 'bg-secondary');
    nodesEncryptedResponseDiv.classList.replace('text-secondary', 'text-light');

    // nodesKeySpan.classList.remove('border-success');
    nodesKeyInput.classList.remove('border-success', 'border-secondary');
    nodesKeyInput.classList.add('border-primary');
    nodesKeyInput.classList.replace('text-secondary', 'text-light');
    // nodesKeySpan.classList.replace('d-block', 'd-none');
    nodesKeyInput.classList.replace('d-block', 'd-none');

    nodesOutputChecksum.classList.replace('d-block', 'd-none');

})



///////////////////////////////////////////////////////////////////////////////
// CONTINUE BUTTONS FUNCTIONALITY /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

brButtonContinue.addEventListener('click', () => nodesDiv.classList.replace('d-none', 'd-block'));
nodesButtonContinue.addEventListener('click', () => consoleDiv.classList.replace('d-none', 'd-block'));













// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// NODES ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

function constructResponse_OK() {

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-info'); nodesDiv.classList.add('border-success');

    document.getElementById(`nodes-output-${index}`).innerText = 'OK';
    
    document.getElementById(`nodes-output-${index}`).classList.remove('bg-danger', 'bg-warning', 'bg-info'); document.getElementById(`nodes-output-${index}`).classList.add('bg-success');
    document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
    
    document.getElementById('nodes-h2-encoded-response').classList.replace('d-none', 'd-block')

    nodesEncodedResponseDiv.classList.replace('d-none', 'd-block')
    nodesEncodedResponseDiv.innerText = text;

    
    nodesButtonDecode.classList.replace('d-none', 'd-block')
}

function constructDecoding(text) {

    let decodedResponse = atob(text);
    
    nodesEncodedResponseDiv.classList.replace('text-light', 'text-dark');
    nodesButtonDecode.classList.replace('btn-primary', 'btn-outline-success');

    nodesEncryptedResponseDiv.classList.replace('d-none', 'd-block');
    nodesEncryptedResponseDiv.innerText = decodedResponse;

    return decodedResponse
}

function constructDecryption(decodedResponse) {

    nodesEncryptedResponseDiv.classList.replace('text-light', 'text-dark');
    nodesButtonDecrypt.classList.replace('btn-primary', 'btn-outline-success');

    // nodesKeySpan.classList.add('border-success');
    // nodesKeySpan.classList.add('bg-dark');

    nodesKeyInput.classList.add('border-success');
    nodesKeyInput.classList.add('bg-dark');

    let decryptedResponse = oarCrypt(decodedResponse, nodesKeyInput.value);
    
    nodesStringifiedResponseDiv.classList.replace('d-none', 'd-block');
    nodesStringifiedResponseDiv.innerText = decryptedResponse;

    nodesOutputChecksum.classList.replace('d-block', 'd-none');
    nodesButtonChecksum.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary','btn-outline-secondary', 'btn-outline-muted'); nodesButtonChecksum.classList.add('btn-primary');
    nodesButtonParse.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary','btn-outline-secondary', 'btn-outline-muted', 'btn-muted'); nodesButtonParse.classList.add('btn-primary');

    return decryptedResponse;
}

function checksum(decryptedResponse) {

    try{
        let obj = JSON.parse(decryptedResponse);
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

function constructIntactness() {

    nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-success');                                                        
    nodesOutputChecksum.innerText = 'INTACT';
    nodesOutputChecksum.classList.remove('bg-danger', 'bg-warning'); nodesOutputChecksum.classList.add('bg-success');
    nodesOutputChecksum.classList.replace('d-none', 'd-block');

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-primary'); nodesDiv.classList.add( 'border-success');

    nodesButtonChecksum.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary','btn-outline-secondary', 'btn-outline-muted'); nodesButtonChecksum.classList.add('btn-outline-success')
}

function constructCorruptness() {

    nodesButtonChecksum.classList.replace('btn-primary', 'btn-outline-warning')                                                    
    nodesOutputChecksum.innerText = 'CORRUPTED';
    nodesOutputChecksum.classList.remove('bg-danger', 'bg-success'); nodesOutputChecksum.classList.add('bg-warning');
    nodesOutputChecksum.classList.replace('d-none', 'd-block')

    nodesDiv.classList.remove('border-danger', 'border-success', 'border-info'); nodesDiv.classList.add('border-warning');
}

function constructParse_OK(parsedResponse) {

    nodesParsedResponseDiv.classList.replace('d-none', 'd-block');
    nodesParsedResponseDiv.innerHTML = JSON.stringify(parsedResponse, null, 2);

    nodesEncodedResponseDiv.classList.replace('text-dark', 'text-secondary');
    nodesEncodedResponseDiv.classList.replace('bg-secondary', 'bg-dark');
    nodesEncodedResponseDiv.classList.replace('border-dark', 'border-secondary');
    
    nodesEncryptedResponseDiv.classList.replace('text-dark', 'text-secondary');
    nodesEncryptedResponseDiv.classList.replace('bg-secondary', 'bg-dark');
    nodesEncryptedResponseDiv.classList.replace('border-dark', 'border-secondary');

    nodesButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

    nodesButtonDecode.classList.replace('btn-outline-success', 'btn-outline-secondary');
    nodesButtonDecrypt.classList.replace('btn-outline-success', 'btn-outline-secondary');
    nodesButtonChecksum.classList.replace('btn-outline-success', 'btn-outline-secondary');

    nodesKeyInput.classList.replace('border-success', 'border-secondary');
    nodesKeyInput.classList.replace('text-light', 'text-secondary');

    nodesButtonParse.classList.remove('btn-primary', 'btn-outline-danger'); nodesButtonParse.classList.add('btn-outline-success');

    nodesOutputChecksum.classList.remove('bg-danger', 'bg-warning'); nodesOutputChecksum.classList.add('bg-success');
    nodesOutputChecksum.innerText = "OK";

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-primary'); nodesDiv.classList.add( 'border-success');
}

function constructParse_FAIL(error) {
    
    nodesDiv.classList.remove('border-warning', 'border-success', 'border-primary'); nodesDiv.classList.add('border-danger');

    nodesOutputChecksum.innerText = error;

    nodesOutputChecksum.classList.remove('bg-warning', 'bg-success'); nodesOutputChecksum.classList.add('bg-danger');
    nodesOutputChecksum.classList.replace('d-none', 'd-block');

    nodesButtonChecksum.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-success', 'btn-outline-primary','btn-outline-muted'); nodesButtonChecksum.classList.add('btn-outline-secondary')
    nodesButtonParse.classList.replace('btn-primary', 'btn-outline-danger');
}





brButton.addEventListener('click', scrap);

// BUTTON RELOAD








function scrap() {
    
    console.log(brInput.value)

    fetch(`http://${brInput.value}/`)
        
        .then(function(response) {
            // console.log(response);
            return response.text()
        })
            
            .then(function(text) {
                // Initialize the DOM parser
                var parser = new DOMParser();

                // Parse the text
                var br_doc = parser.parseFromString(text, "text/html");

                const uls = br_doc.querySelectorAll('ul');
                console.log(uls);

                try {

                    neighborsNodeList = uls[0].querySelectorAll('li');
                    neighborsArray = Array.from(neighborsNodeList);

                    routingLinksNodeList = uls[1].querySelectorAll('li');
                    routingLinksArray = Array.from(routingLinksNodeList);
                    
                    console.log(neighborsArray);
                    console.log(routingLinksArray);

                    brDiv.classList.remove('border-info', 'border-warning', 'border-danger'); brDiv.classList.add('border-success');
                
                    brOutput.innerText = 'OK';
                    brOutput.classList.remove('bg-info', 'bg-warning', 'bg-danger'); brOutput.classList.add('bg-success');
                    brOutput.classList.replace('d-none', 'd-block')

                    document.getElementById('br-h2-neighbors').classList.replace('d-none', 'd-block')
                    document.getElementById('br-h2-routing-links').classList.replace('d-none', 'd-block')
                    
                    

                    neighborsElement.classList.replace('d-none', 'd-block');
                    routingLinksElement.classList.replace('d-none', 'd-block');

                    let neighborsListHTML = '';
                    let routingLinksListHTML = '';

                    neighborsArray.forEach((neighbor, index) => neighborsListHTML += `<li class="list-group-item text-center bg-dark text-light border-secondary rounded"> ${neighbor.innerText} </li>`);
                    neighborsElement.innerHTML = neighborsListHTML;

                    routingLinksArray.forEach((routingLink, index) => routingLinksListHTML += `<li class="list-group-item text-center bg-dark text-light border-secondary rounded""> ${routingLink.innerText} </li>`);
                    routingLinksElement.innerHTML = routingLinksListHTML;
                    
                    brButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    

                    const nodesRegExp = /fd\S*\s/gi
                    var nodesAddr = [];
                    let regExpResults = text.match(nodesRegExp);

                    if (nodesAddr != null) {
                        regExpResults = regExpResults.map((node) => node.slice(0, -1))
                        regExpResults.forEach((node, index) => {
                            if (index % 2  == 0) {
                                nodesAddr.push(node)
                            }
                        })
                        console.log(nodesAddr);
                    }


                    
                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    // NODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    
                    nodesDiv.classList.remove('border-secondary', 'border-success', 'border-warning', 'border-danger');
                    nodesDiv.classList.add('border-info');
                    nodesH1.classList.replace('text-muted', 'text-light');
                    nodesButtonIndex.classList.replace('btn-muted', 'btn-outline-primary');
                    
                    
                    
                    
                    nodesButtonIndex.classList.replace('d-none', 'd-block');
                    nodesButtonIndex.addEventListener('click', () => {
                        
                        nodesButtonIndex.classList.replace('d-block', 'd-none')
                        nodesInput.innerHTML = nodesInputHTML(nodesAddr);

                        nodesAddr.forEach((node, index) => {

                            document.getElementById(`nodes-button-${index}`).addEventListener('click', () => {
    
                                console.log('getgetget');
                                let addr = document.getElementById(`nodes-addr-input-${index}`).value;
                                let path = document.getElementById(`nodes-path-input-${index}`).value;
                                
                                fetch(`http://[${addr}]/${path}`)
                                    
                                    .then(function(response) {
                                        
                                        return response.text()
                                    })
                                        
                                        .then(function(text) {
                                            
                                            nodesDiv.classList.remove('border-danger', 'border-warning', 'border-info'); nodesDiv.classList.add('border-success');
                                            
                                            document.getElementById(`nodes-output-${index}`).innerText = 'OK';

                                            document.getElementById(`nodes-output-${index}`).classList.remove('bg-danger', 'bg-warning'); document.getElementById(`nodes-output-${index}`).classList.add('bg-success');
                                            document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                            
                                            
                                            
                                            
                                            document.getElementById('nodes-h2-encoded-response').classList.replace('d-none', 'd-block')
    
                                            nodesEncodedResponseDiv.classList.replace('d-none', 'd-block')
                                            nodesEncodedResponseDiv.innerText = text;
                                            


                                            nodesButtonDecode.classList.replace('btn-muted', 'btn-primary');
                                            nodesButtonDecode.classList.replace('d-none', 'd-block')
                                            nodesButtonDecode.addEventListener('click', () => {
                                                
                                                let decodedResponse = constructDecoding(text);
                                                
                                                // nodesKeySpan.classList.replace('d-none', 'd-block');
                                                nodesKeyInput.classList.replace('d-none', 'd-block');

                                                nodesButtonDecrypt.classList.replace('btn-muted', 'btn-primary');
                                                nodesButtonDecrypt.classList.replace('d-none', 'd-block')
                                                nodesButtonDecrypt.addEventListener('click', () => {
    
                                                    let decryptedResponse = constructDecryption(decodedResponse);
                                                    let intact = checksum(decryptedResponse);
    
                                                    

                                                    nodesButtonChecksum.classList.replace('btn-muted', 'btn-primary');
                                                    nodesButtonChecksum.classList.replace('d-none', 'd-block');
                                                    nodesButtonChecksum.addEventListener('click', () => {
    
                                                        if(intact) {
                                                            constructIntactness(); 
                                                        } else {
                                                            constructCorruptness();
                                                        }
                                                    })
                                                    
                                                    nodesButtonParse.classList.replace('btn-muted', 'btn-primary');
                                                    nodesButtonParse.classList.replace('d-none', 'd-block');
                                                    nodesButtonParse.addEventListener('click', () => {
                                                        
                                                        try{
                                                            
                                                            let parsedResponse = JSON.parse(decryptedResponse);

                                                            constructParse_OK(parsedResponse);

                                                            console.log(JSON.stringify(elaborate(parsedResponse, checksum(decryptedResponse)), null, 2));
                                                            

                                                            constructLegend('<pre>' + JSON.stringify(elaborate(parsedResponse, checksum(decryptedResponse)), null, 2) + '</pre>');

                                                            
    
                                                        } 
                                                        catch(error) {
                                                            
                                                            constructParse_FAIL(error);

                                                        }
                                                    })
                                                })
                                            })
                                        })
                                    
                                    .catch(function(error) {

                                        nodesDiv.classList.remove('border-warning', 'border-success', 'border-info'); nodesDiv.classList.add('border-danger');
                                    
                                        document.getElementById(`nodes-output-${index}`).innerText = error;

                                        document.getElementById(`nodes-output-${index}`).classList.remove('bg-warning', 'bg-success'); document.getElementById(`nodes-output-${index}`).classList.add('bg-danger');
                                        document.getElementById(`nodes-output-${index}`).classList.replace('d-none', 'd-block')
                                        
                                        console.log(error);
                                    }
                                )  
                            })
                        })
                    })
                    
                } catch {
                    
                    if(uls.length < 2) {

                        brDiv.classList.remove('border-info');
                        brDiv.classList.remove('border-success');
                        brDiv.classList.remove('border-danger');
                        brDiv.classList.add('border-warning');

                        brOutput.innerText = 'INCOMPLETE';

                        brOutput.classList.remove('bg-danger');
                        brOutput.classList.remove('bg-success');
                        brOutput.classList.add('bg-warning');
                        brOutput.classList.replace('d-none', 'd-block')

                        brButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-muted');

                    }
                }
            })

        .catch(function(error) {

            brDiv.classList.remove('border-info');
            brDiv.classList.remove('border-success');
            brDiv.classList.remove('border-warning');
            brDiv.classList.add('border-danger');

            brOutput.innerText = error;
            
            brOutput.classList.remove('bg-success');
            brOutput.classList.remove('bg-warning');
            brOutput.classList.add('bg-danger');
            brOutput.classList.replace('d-none', 'd-block')
            console.log(error);
        })
}

function simConsole(nodesAddr) {
    console.log(nodesAddr);
}


