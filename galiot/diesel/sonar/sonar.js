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

    if(content) {
        legendContent.classList.replace('d-none', 'd-block');
        legendContent.innerHTML = content;
    }
    if (appendix) {
        legendAppendix.classList.replace('d-none', 'd-block');
        legendAppendix.innerHTML = appendix;
    }
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

            case 1:
                var device = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };
                
                return device;

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
                        radioOff: obj.nrg.rO
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
                        cmd_ipNeighbors_info.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = {nodeIPv6neighborRouter: neighbor.router, nodeIPv6neighborState: neighbor.state}
                    } else {
                        cmd_ipNeighbors_info.cmd_ipNeighbors_info.nodeIPv6neighborInfo[index] = null
                    }
                });
                
                return cmd_ipNeighbors_info;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 11:
                var cmd_tschStatus = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_tschStatus;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 12:
                var cmd_tschSchedule = {
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

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

                return cmd_tschSchedule;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            
            case 13:
                var cmd_routes = {
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

            case 14:
                var cmd_routes_routingLinks_sources = {
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
                        cmd_routes_routingLinks_sources.cmd_routes_routingLinks_sources.routeSources[index] = {linkSourceAddr: link.from, dodagRoot: link.dodagRoot}
                    } else {
                        cmd_routes_routingLinks_sources.cmd_routes_routingLinks_sources.routeSources[index] = null
                    }
                });

                return cmd_routes_routingLinks_sources;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 15:
                var cmd_routes_routingLinks_destinations = {
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
                        cmd_routes_routingLinks_destinations.cmd_routes_routingLinks_destinations.routeDestinations[index] = {linkDestinationAddr: link.to, lifetime: link.lf}
                    } else {
                        cmd_routes_routingLinks_destinations.cmd_routes_routingLinks_destinations.routeDestinations[index] = null
                    }
                });

                return cmd_routes_routingLinks_destinations;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 16:
                var cmd_routes_routingEntries_routes = {
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

            case 17:
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
                        cmd_routes_routingEntries_vias.cmd_routes_routingEntries_vias.vias[index] = {entryViaAddr: entry.via, lifetime: entry.lf}
                    } else {
                        cmd_routes_routingEntries_vias.cmd_routes_routingEntries_vias.vias[index] = null
                    }
                });

                return cmd_routes_routingEntries_vias;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 18:
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
                        dtsnOut: obj.rSt.dtsnO
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_rplStatus;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 19:
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
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                return cmd_rplStatus_dag;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 20:
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

            case 21:
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
                        cmd_rplNbr_addr.cmd_rplNbr_addr.addresses[index] = {rplAddress: neighbor.ad}
                    } else {
                        cmd_rplNbr_addr.cmd_rplNbr_addr.addresses[index] = null
                    }
                });

                return cmd_rplNbr_addr;
                
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 22:
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

            case 23:
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
                        values: [null]
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

                return cmd_rplNbr_values;
               
            // -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

            case 24:
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
                        parens: [null]
                    },
                    checksum: {
                        hash: obj.hash,
                        check: intact
                    },
                    update: new Date
                };

                obj.rNP.ns.forEach(function(neighbor, index) {
                    if (neighbor != null) {
                        cmd_rplNbr_parens.cmd_rplNbr_parens.parens[index] = {rplNeighborLastTXtimeSeconds: neighbor.lTx, rplNeighborBetterParentSinceSeconds: neighbor.bS}
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

const brDivDoc = document.getElementById('br-div-doc');
const brDivDocContent = document.getElementById('br-div-doc-content');

const brDivResults = document.getElementById('br-div-results');

const brDivDocParse = document.getElementById('br-div-doc-parse');
const brDivDocRegexp = document.getElementById('br-div-doc-regexp');

const brButtonParse = document.getElementById('br-button-parse');
const brButtonRegexp = document.getElementById('br-button-regexp');

const neighborsElement = document.getElementById('neighbors');
const routingLinksElement = document.getElementById('routing-links');

const brDivTable = document.getElementById('br-div-table');
const brTableTbody = document.getElementById('br-table-tbody');

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

const consoleSelectNode = document.getElementById('console-select-node');
const consoleSelectQuery = document.getElementById('console-select-query');

const consoleButtonQuery = document.getElementById('console-button-query');

const consoleOutputQuery = document.getElementById('console-output-query');

const consoleInputSpan = document.getElementById('console-input-span');
const consoleInputKey = document.getElementById('console-input-key');

const consoleTableQuery = document.getElementById('console-table-query');
const consoleTableQueryTbody = document.getElementById('console-table-query-tbody');

const consoleDataDiv = document.getElementById('console-data-div');
const consoleData = document.getElementById('console-data');

const consoleH2 = document.getElementById('console-h2');

const consoleButtonReload = document.getElementById('console-button-reload');
const consoleButtonClear = document.getElementById('console-button-clear');
const consoleButtonContinue = document.getElementById('console-button-continue');

// STORE

const storeDiv = document.getElementById('store-div');
const storeH1 = document.getElementById('store-h1');

const storeButtonSave = document.getElementById('store-button-save');
const storeDivSave = document.getElementById('store-div-save');

const storeSelect = document.getElementById('store-select');
const storeInput = document.getElementById('store-input');

const storeButtonPost = document.getElementById('store-button-post');
const storeInputAddress = document.getElementById('store-input-address');
const storeInputPort = document.getElementById('store-input-port');
const storeInputPath = document.getElementById('store-input-path');

const storeButtonSaveAll = document.getElementById('store-button-save-all');

const storeOutput = document.getElementById('store-output');

const storeH2Request = document.getElementById('store-h2-request');
const storeH2Response = document.getElementById('store-h2-response');

const storeRequest = document.getElementById('store-request');
const storeResponse = document.getElementById('store-response');

const storeTable = document.getElementById('store-table');
const storeTableTbody = document.getElementById('store-table-tbody');

const storeButtonReload = document.getElementById('store-button-reload');
const storeButtonClear = document.getElementById('store-button-clear');
const storeButtonContinue = document.getElementById('store-button-continue');

// DATABASE

const databaseDiv = document.getElementById('database-div');
const databaseH1 = document.getElementById('database-h1');

const databaseButton = document.getElementById('database-button');

const databaseInputGroup = document.getElementById('database-input-group');

const databaseSelect = document.getElementById('database-select');
const databaseButtonGet = document.getElementById('database-button-get');
const databaseInputAddress = document.getElementById('database-input-address');
const databaseInputPort = document.getElementById('database-input-port');
const databaseInputPath = document.getElementById('database-input-path');

const databaseOutput = document.getElementById('database-output');

const databaseH2Response = document.getElementById('database-h2-response');
const databaseResponse = document.getElementById('database-response');

const databaseButtonDrop = document.getElementById('database-button-drop');

const databaseButtonReload = document.getElementById('database-button-reload');
const databaseButtonClear = document.getElementById('database-button-clear');
const databaseButtonContinue = document.getElementById('database-button-continue');

//CONTROL

const controlDiv = document.getElementById('control-div');
const controlH1 = document.getElementById('control-h1');

const controlCrudDivInput =  document.getElementById('control-crud-div-input');
const controlCrudButton = document.getElementById('control-crud-button');

const controlCrudH2Create = document.getElementById('control-crud-h2-create');
const controlCrudH2Read = document.getElementById('control-crud-h2-read');
const controlCrudH2Update = document.getElementById('control-crud-h2-update');
const controlCrudH2Delete = document.getElementById('control-crud-h2-delete');

const controlCrudInputGroupPost = document.getElementById('control-crud-input-group-post');
const controlCrudInputGroupGetPath = document.getElementById('control-crud-input-group-get-path');
const controlCrudInputGroupGetOne = document.getElementById('control-crud-input-group-get-one');
const controlCrudInputGroupGetAll = document.getElementById('control-crud-input-group-get-all');
const controlCrudInputGroupPatch = document.getElementById('control-crud-input-group-patch');
const controlCrudInputGroupPut = document.getElementById('control-crud-input-group-put');
const controlCrudInputGroupDeleteOne = document.getElementById('control-crud-input-group-delete-one');
const controlCrudInputGroupDeleteAll = document.getElementById('control-crud-input-group-delete-all');

const controlCrudButtonPost = document.getElementById('control-crud-button-post');
const controlCrudButtonGetPath = document.getElementById('control-crud-button-get-path');
const controlCrudButtonGetOne = document.getElementById('control-crud-button-get-one');
const controlCrudButtonGetAll = document.getElementById('control-crud-button-get-all');
const controlCrudButtonPatch = document.getElementById('control-crud-button-patch');
const controlCrudButtonPut = document.getElementById('control-crud-button-put');
const controlCrudButtonDeleteOne = document.getElementById('control-crud-button-delete-one');
const controlCrudButtonDeleteAll = document.getElementById('control-crud-button-delete-all');

const controlCrudInputAddressPost = document.getElementById('control-crud-input-address-post');
const controlCrudInputAddressGetPath = document.getElementById('control-crud-input-address-get-path');
const controlCrudInputAddressGetOne = document.getElementById('control-crud-input-address-get-one');
const controlCrudInputAddressGetAll = document.getElementById('control-crud-input-address-get-all');
const controlCrudInputAddressPatch = document.getElementById('control-crud-input-address-patch');
const controlCrudInputAddressPut = document.getElementById('control-crud-input-address-put');
const controlCrudInputAddressDeleteOne = document.getElementById('control-crud-input-address-delete-one');
const controlCrudInputAddressDeleteAll = document.getElementById('control-crud-input-address-delete-all');

const controlCrudInputPortPost = document.getElementById('control-crud-input-port-post');
const controlCrudInputPortGetPath = document.getElementById('control-crud-input-port-get-path');
const controlCrudInputPortGetOne = document.getElementById('control-crud-input-port-get-one');
const controlCrudInputPortGetAll = document.getElementById('control-crud-input-port-get-all');
const controlCrudInputPortPatch = document.getElementById('control-crud-input-port-patch');
const controlCrudInputPortPut = document.getElementById('control-crud-input-port-put');
const controlCrudInputPortDeleteOne = document.getElementById('control-crud-input-port-delete-one');
const controlCrudInputPortDeleteAll = document.getElementById('control-crud-input-port-delete-all');

const controlCrudInputIdPost = document.getElementById('control-crud-input-id-post');
const controlCrudInputIdGetOne = document.getElementById('control-crud-input-id-get-one');
const controlCrudInputIdGetAll = document.getElementById('control-crud-input-id-get-all');
const controlCrudInputIdPatch = document.getElementById('control-crud-input-id-patch');
const controlCrudInputIdPut = document.getElementById('control-crud-input-id-put');
const controlCrudInputIdDeleteOne = document.getElementById('control-crud-input-id-delete-one');
const controlCrudInputIdDeleteAll = document.getElementById('control-crud-input-id-delete-all');

const controlCrudSelectGetOne = document.getElementById('control-crud-select-get-one');
const controlCrudSelectGetAll = document.getElementById('control-crud-select-get-all');
const controlCrudSelectDeleteOne = document.getElementById('control-crud-select-delete-one');
const controlCrudSelectDeleteAll = document.getElementById('control-crud-select-delete-all');

const controlCrudInputBodyPost = document.getElementById('control-crud-input-body-post');
const controlCrudInputBodyPatch = document.getElementById('control-crud-input-body-patch');
const controlCrudInputBodyPut = document.getElementById('control-crud-input-body-put');

const controlCrudInputPath = document.getElementById('control-crud-input-path');

const controlCrudOutputCreate = document.getElementById('control-crud-output-create');
const controlCrudOutputRead = document.getElementById('control-crud-output-read');
const controlCrudOutputUpdate = document.getElementById('control-crud-output-update');
const controlCrudOutputDelete = document.getElementById('control-crud-output-delete');

const controlCrudDivResponse = document.getElementById('control-crud-div-response');

const controlCrudH2Response = document.getElementById('control-crud-h2-response');
const controlCrudDivResponseContent = document.getElementById('control-crud-div-response-content');

const controlButtonReload = document.getElementById('control-button-reload');
const controlButtonClear = document.getElementById('control-button-clear');
const controlButtonContinue = document.getElementById('control-button-continue');

// DEMO

const demoDiv = document.getElementById('demo-div');
const demoH1 = document.getElementById('demo-h1');

const demoButtonDump = document.getElementById('demo-button-dump');

const demoOutputDump = document.getElementById('demo-output-dump');
const demoTableDump = document.getElementById('demo-table-dump');
const demoTableDumpTbody = document.getElementById('demo-table-dump-tbody');

const demoDivProcessBridge = document.getElementById('demo-div-process-bridge');
const demoDivProcessContent = document.getElementById('demo-div-process-content');

const demoButtonProcess = document.getElementById('demo-button-process');

const demoButtonProcessDistinctNodes = document.getElementById('demo-button-process-distict-nodes');
const demoOutputProcessDistinctNodes = document.getElementById('demo-output-process-distict-nodes');
const demoTableProcessDistinctNodes = document.getElementById('demo-table-process-distict-nodes');

const demoButtonProcessRecords = document.getElementById('demo-button-process-records');
const demoTableProcessRecords = document.getElementById('demo-table-process-records');

const demoButtonReload = document.getElementById('demo-button-reload');
const demoButtonClear = document.getElementById('demo-button-clear');
const demoButtonContinue = document.getElementById('demo-button-continue');

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

// CONSOLE

consoleButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});

// STORE

storeButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});

// DATABASE

databaseButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});

// CONTROL

controlButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});

// DEMO

demoButtonReload.addEventListener('click', () => {
    event.preventDefault();
    window.location.reload(true);
});


///////////////////////////////////////////////////////////////////////////////
// CLEAR BUTTONS FUNCTIONALITY ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// BORDER ROUTER

brButtonClear.addEventListener('click', () => {
                        
    brDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary');
    brDiv.classList.add('border-info');

    brDivDoc.classList.add('d-none');
    brDivDocParse.classList.add('d-none');

    // brButtonParse.classList.add('d-none');
    
    document.getElementById('br-h2-neighbors').classList.replace('d-block', 'd-none');
    document.getElementById('br-h2-routing-links').classList.replace('d-block', 'd-none');

    neighborsElement.classList.replace('d-block', 'd-none');
    routingLinksElement.classList.replace('d-block', 'd-none');
    neighborsElement.innerHTML = '';
    routingLinksElement.innerHTML = '';
    
    brOutput.classList.replace('d-block', 'd-none');
    nodesEncodedResponseDiv.innerText = ''

    brDivDocRegexp.classList.add('d-none');
    brDivTable.classList.add('d-none');

    brButtonRegexp.classList.remove('btn-outline-primary', 'btn-outline-success'); brButtonRegexp.classList.add('btn-muted');

    brDivResults.classList.add('d-none');

    brDivDocContent.classList.remove('bg-light', 'text-dark', 'bg-dark', 'text-secondary'); brDivDocContent.classList.add('bg-light', 'text-dark');
});

// NODES

nodesButtonClear.addEventListener('click', () => {

    nodesDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary');
    nodesDiv.classList.add('border-info');

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
    legendDiv.classList.replace('d-show', 'd-none');
});

// COSNOLE

consoleButtonClear.addEventListener('click', () => {

    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-info');

    consoleOutputQuery.classList.replace('d-block', 'd-none');
    consoleTableQuery.classList.replace('d-block', 'd-none');

    consoleData.innerHTML = '';
    storeButtonSave.classList.replace('d-block', 'd-none');


    consoleButtonContinue.classList.replace('btn-outline-primary', 'btn-outline-secondary');
});

// STORE

storeButtonClear.addEventListener('click', () => {

    storeDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-info');

    storeButtonSave.classList.remove('d-none');

    storeDivSave.classList.replace('d-block', 'd-none');
    storeOutput.classList.replace('d-block', 'd-none');

    storeResponse.innerHTML = '';
    storeRequest.innerHTML = '';

    storeSelect.innerHTML = '';

    storeTable.classList.replace('d-block', 'd-none');
    storeTableTbody.innerHTML = '';
});

// DATABASE

databaseButtonClear.addEventListener('click', () => {

    databaseDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary'); databaseDiv.classList.add('border-info');

    databaseOutput.classList.replace('d-block', 'd-none');

    databaseResponse.innerHTML = '';

    databaseButtonDrop.classList.replace('d-block', 'd-none');
});

// CONTROL

controlButtonClear.addEventListener('click', () => {

    controlDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary'); controlDiv.classList.add('border-info');

    controlCrudButton.classList.replace('d-block', 'd-none');

    controlCrudDiv.classList.replace('d-block', 'd-none');

    controlCrudOutputCreate.classList.replace('d-block', 'd-none');
    controlCrudOutputCreate.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-info', 'bg-secondary');
    controlCrudOutputCreate.innerText = '';
    controlCrudOutputRead.classList.replace('d-block', 'd-none');
    controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-info', 'bg-secondary');
    controlCrudOutputRead.innerText = '';
    controlCrudOutputUpdate.classList.replace('d-block', 'd-none');
    controlCrudOutputUpdate.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-info', 'bg-secondary');
    controlCrudOutputUpdate.innerText = '';
    controlCrudOutputDelete.classList.replace('d-block', 'd-none');
    controlCrudOutputDelete.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-info', 'bg-secondary');
    controlCrudOutputDelete.innerText = '';
});

// DEMO

demoButtonClear.addEventListener('click', () => {

    demoDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary'); demoDiv.classList.add('border-info');

    demoButtonDump.classList.remove('d-none');

    demoOutputDump.classList.replace('d-block', 'd-none');

    demoTableDump.classList.replace('d-block', 'd-none');
    demoTableDumpTbody.innerHTML = '';

    demoDivProcessBridge.classList.add('d-none');
    demoDivProcessContent.classList.add('d-none');
});







///////////////////////////////////////////////////////////////////////////////
// CONTINUE BUTTONS FUNCTIONALITY /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

brButtonContinue.addEventListener('click', () => nodesDiv.classList.replace('d-none', 'd-block'));
nodesButtonContinue.addEventListener('click', () => {
    consoleDiv.classList.replace('d-none', 'd-block');
    legendDiv.classList.replace('d-show', 'd-none');
});
consoleButtonContinue.addEventListener('click', () => {
    storeDiv.classList.replace('d-none', 'd-block');
    legendDiv.classList.replace('d-show', 'd-none');
});
storeButtonContinue.addEventListener('click', () => {
    databaseDiv.classList.replace('d-none', 'd-block');
    legendDiv.classList.replace('d-show', 'd-none');
});
databaseButtonContinue.addEventListener('click', () => {
    controlDiv.classList.replace('d-none', 'd-block');
    legendDiv.classList.replace('d-show', 'd-none');
});
controlButtonContinue.addEventListener('click', () => {
    demoDiv.classList.replace('d-none', 'd-block');
    legendDiv.classList.replace('d-show', 'd-none');
});














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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function runNodes(nodesAddr) {
    
    nodesDiv.classList.remove('border-secondary', 'border-success', 'border-warning', 'border-danger');
    nodesDiv.classList.add('border-info');
    nodesH1.classList.replace('text-muted', 'text-light');
    nodesButtonIndex.classList.replace('btn-muted', 'btn-outline-primary');
    
    // nodesButtonIndex.classList.replace('d-none', 'd-block');
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
                                            legendDiv.classList.replace('d-none', 'd-show');

                                            console.log(JSON.stringify(elaborate(parsedResponse, checksum(decryptedResponse)), null, 2));
                                            
                                            constructLegend('<pre>' + JSON.stringify(elaborate(parsedResponse, checksum(decryptedResponse)), null, 2) + '</pre>', undefined);

                                            switch(parsedResponse.ndx) {
                                                case 1:
                                                    document.getElementById('legend-table-device').classList.replace('d-none', 'd-show');
                                                    break;
                                                case 2:
                                                    document.getElementById('legend-table-energest').classList.replace('d-none', 'd-show');
                                                    break;
                                                case 3:
                                                    document.getElementById('legend-table-stats_network_ip').classList.replace('d-none', 'd-show');
                                                    break;
                                                case 4:
                                                    document.getElementById('legend-table-stats_network_icmp').classList.replace('d-none', 'd-show');
                                                    break;
                                                case 5:
                                                    document.getElementById('legend-table-stats_transport').classList.replace('d-none', 'd-show');
                                                    break;
                                                case 6:
                                                    document.getElementById('legend-table-stats_discovery').classList.replace('d-none', 'd-show');
                                                    break;
                                            }
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
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BORDER ROUTER ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

brButton.addEventListener('click', () => {

    brDivDocContent.classList.remove('bg-light', 'text-dark', 'bg-dark', 'text-secondary'); brDivDocContent.classList.add('bg-light', 'text-dark');
    brButtonParse.classList.remove('btn-outline-success', 'btn-outline-primary'); brButtonParse.classList.add('btn-muted');

    document.getElementById('br-h2-neighbors').classList.replace('d-block', 'd-none');
    document.getElementById('br-h2-routing-links').classList.replace('d-block', 'd-none');
    
    brDivDocContent.innerHTML = `<code style="font-size: 1rem"> scraping... </code>`

    neighborsElement.classList.replace('d-block', 'd-none');
    routingLinksElement.classList.replace('d-block', 'd-none');

    brDivDocRegexp.classList.add('d-none');
    brDivTable.classList.add('d-none');

    brButtonRegexp.classList.remove('btn-outline-primary', 'btn-outline-success'); brButtonRegexp.classList.add('btn-muted');

    brDivResults.classList.add('d-none');

    brButtonContinue.classList.replace('btn-outline-primary', 'btn-outline-secondary')
    
    scrap();
});


















































function scrap() {
    
    console.log(brInput.value)

    fetch(`http://${brInput.value}/`)
        
        .then(function(response) {
            console.log(response);
            return response.text()
        })
            
            .then(function(text) {
                // Initialize the DOM parser
                var parser = new DOMParser();

                // Parse the text
                var br_doc = parser.parseFromString(text, "text/html");

                console.log(br_doc);

                brDivDoc.classList.remove('d-none');
                brDivDocContent.innerHTML = `${text}`

                brDivDocParse.classList.remove('d-none');

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
                    
                    brButtonParse.classList.replace('btn-muted', 'btn-outline-primary');
                    brButtonParse.addEventListener('click', () => {

                        brDivResults.classList.remove('d-none');

                        brDivDocContent.classList.remove('bg-light', 'text-dark'); brDivDocContent.classList.add('bg-secondary', 'text-light');
                        brButtonParse.classList.replace('btn-outline-primary', 'btn-outline-success');

                        document.getElementById('br-h2-neighbors').classList.replace('d-none', 'd-block');
                        document.getElementById('br-h2-routing-links').classList.replace('d-none', 'd-block');
                        
                        neighborsElement.classList.replace('d-none', 'd-block');
                        routingLinksElement.classList.replace('d-none', 'd-block');

                        brDivDocRegexp.classList.remove('d-none');
                    })
                    

                    let neighborsListHTML = '';
                    let routingLinksListHTML = '';

                    neighborsArray.forEach((neighbor, index) => neighborsListHTML += `<li class="list-group-item text-center bg-dark text-light "> <code style="font-size: 1rem">${neighbor.innerText} </code></li>`);
                    neighborsElement.innerHTML = neighborsListHTML;

                    routingLinksArray.forEach((routingLink, index) => routingLinksListHTML += `<li class="list-group-item text-center bg-dark text-light ""><code style="font-size: 1rem"> ${routingLink.innerText} </code></li>`);
                    routingLinksElement.innerHTML = routingLinksListHTML;

                    const nodesRegExp = /fd\S*\s/gi // TRICKY SORCERY //
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
                    };
                    
                    if(neighborsArray.length == routingLinksArray.length) {
                        
                        brButtonRegexp.classList.replace('btn-muted', 'btn-outline-primary');

                        brButtonRegexp.addEventListener('click', () => {

                            brButtonRegexp.classList.replace('btn-outline-primary', 'btn-outline-success');
                            brButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                            brDivResults.classList.add('d-none');
                            
                            brDivDocRegexp.classList.add('d-none');

                            brDivTable.classList.remove('d-none');
                            brTableTbody.innerHTML = '';

                            brDivDocContent.classList.replace('bg-secondary', 'bg-dark');
                            brDivDocContent.classList.replace('text-light', 'text-secondary');

                            nodesAddr.forEach((address, index) => {

                                brTableTbody.innerHTML += `
                                <tr>
                                    <td colspan="1" class="text-light text-center">${address}</td>
                                </tr>`;
                            })

                        });
                        
                        runNodes(nodesAddr);
                        simConsole(nodesAddr);
                        activateStore(nodesAddr);
                    
                    } else {

                        brDiv.classList.remove('border-info');
                        brDiv.classList.remove('border-success');
                        brDiv.classList.remove('border-danger');
                        brDiv.classList.add('border-warning');

                        brOutput.innerText = 'incomplete';

                        brOutput.classList.remove('bg-danger');
                        brOutput.classList.remove('bg-success');
                        brOutput.classList.add('bg-warning');
                        brOutput.classList.replace('d-none', 'd-block')
                    };
                    
                } catch {
                    
                    if(uls.length < 2) {

                        brDiv.classList.remove('border-info');
                        brDiv.classList.remove('border-success');
                        brDiv.classList.remove('border-danger');
                        brDiv.classList.add('border-warning');

                        brOutput.innerText = 'incomplete';

                        brOutput.classList.remove('bg-danger');
                        brOutput.classList.remove('bg-success');
                        brOutput.classList.add('bg-warning');
                        brOutput.classList.replace('d-none', 'd-block')
                    };
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


















































function cargoSave (node, obj) {

    storeButtonSave.classList.add('d-none');
    
    // storeDivSave.classList.replace('d-none', 'd-block')
    // storeDivSave.innerHTML =`
    //     <table class="table table-bordered">
    //         <tbody>`;

    // obj.forEach((object, index) => {

    //     storeDivSave.innerHTML += `
    //         <tr>
    //             <td>${JSON.stringify(object)}</td>
    //             <td><button class="btn btn-primary" id="store-button-save-object">store</button></td>
    //         </tr>`    
    // });

    // storeDivSave.innerHTML += `
    //     </tbody>
    //         </table>`;

    // ----------------------------------------------------------------------------------
    
    // storeDivSave.classList.replace('d-none', 'd-block');
    
    // storeUL.innerHTML = '';
    // storeUL.classList.replace('d-none', 'd-block');
    
    // obj.forEach((object, index) => {

    //     storeUL.innerHTML += `
    //         <li class="list-group-item bg-dark text-light border-secondary rounded">
    //             ${JSON.stringify(object)}
    //         </li>`;
    // });

    // storeDivSave.innerHTML += `
    //     <br>
    //     <button class="btn btn-primary justify-content-center text-center" id="store-button-save-object">store</button>`;

    // ----------------------------------------------------------------------------------

    // storeDivSave.classList.replace('d-none', 'd-block');

    // storeDivSave.innerHTML =`<div class="container">`

    // obj.forEach((object, index) => {

    //     storeDivSave.innerHTML += `
    //         <div class="row my-5 p-auto border border-secondary justify-content-center">
    //             <div class="align-self-center col-10 text-right text-light"> ${JSON.stringify(object)} </div>
    //             <div class="align-self-center col-2"><button class="btn btn-primary" id="store-button-save-object-${index}">store</button></div>
    //         </div>`;
    // });

    // storeDivSave.innerHTML += `</div>`;


    // nodesAddr.forEach((node, index) => {

    //     nodesInputHTML += `
    //         <div class="p-2 p-auto m-2 m-auto input-group"> 
    //             <div class="input-group-prepend"> 
    //                 <button class="btn btn-primary" type="button" id="nodes-button-${index}">GET</button>  
    //             </div> 
    //             <div class="input-group-prepend"> 
    //                 <span class="input-group-text">http://</span>  
    //             </div> 
    //             <input type="text" class="form-control" value='${node}' id="nodes-addr-input-${index}"></input> 
    //             <div class="input-group-append"> 
    //                 <span class="input-group-text">/</span> 
    //             </div>
    //                 <input type="number" class="form-control"  id="nodes-path-input-${index}"></input> 
    //         </div>
    //         <div class="row text-center justify-content-center" id="nodes-output-${index}">
    //     </div>`
    // })

    // nodesInputHTML += `<div class="container" id="nodes-response"></div>`

    storeDivSave.classList.replace('d-none', 'd-block');
    
    obj.forEach((object, index) => {

        storeSelect.innerHTML += `<option value="${index}">${node} /${object.ndx}</option>`;
    });

    storeButtonPost.addEventListener('click', () => {

        console.log(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`);
        console.log(storeSelect.value);
        console.log(obj[storeSelect.value]);

        fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(obj[storeSelect.value])
        })
        .then(res => res.json())
        .then(data => {
            
            console.log(data);
            
            storeOutput.classList.replace('d-none', 'd-block');
            storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
            storeOutput.innerText = 'OK';

            storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
            
            storeH2Request.classList.replace('d-none', 'd-block');
            storeRequest.innerHTML = `<pre class="text-light">${JSON.stringify(obj[storeSelect.value], null, 2)}</pre>`;


            storeH2Response.classList.replace('d-none', 'd-block');
            storeResponse.innerHTML = `<pre class="text-light">${JSON.stringify(data, null, 2)}</pre>`;

            storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

        })
        .catch(err => {

            console.log(err);

            storeOutput.classList.replace('d-none', 'd-block');
            storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
            storeOutput.innerText = err;

            storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
        })
    });

    storeButtonSaveAll.addEventListener('click', () => {

        storeTable.classList.replace('d-none', 'd-block');
        storeTableTbody.innerHTML = '';
        
        if(obj[0].ndx == 0 || obj[0].ndx == 1 || obj[0].ndx == 2 || obj[0].ndx == 5 || obj[0].ndx == 6 || obj[0].ndx == 7 || obj[0].ndx == 11  || obj[0].ndx == 12)
        {
            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[storeSelect.value])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };

        if(obj[0].ndx == 3) {

            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[0])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                
                storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                <tr>
                    <td>stats/network/ip</td>
                    <td class="text-dark bg-success text-center">OK</td>
                </tr>`;

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(obj[1])
                })
                .then(res => res.json())
                .then(data => {
                    
                    console.log(data);
                    
                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                    storeOutput.innerText = 'saved';

                    storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                    
                    storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                    <tr>
                        <td>stats/network/icmp</td>
                        <td class="text-dark bg-success text-center">OK</td>
                    </tr>`;

                    storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                })
                .catch(err => {

                    console.log(err);

                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                    storeOutput.innerText = err;

                    storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                })
            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };

        if(obj[0].ndx == 8) {

            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[0])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                
                storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                <tr>
                    <td>cmd/ipnbr/ipaddr</td>
                    <td class="text-dark bg-success text-center">OK</td>
                </tr>`;

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(obj[1])
                })
                .then(res => res.json())
                .then(data => {
                    
                    console.log(data);
                    
                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                    storeOutput.innerText = 'saved';

                    storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                    
                    storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                    <tr>
                        <td>cmd/ipnbr/lladdr</td>
                        <td class="text-dark bg-success text-center">OK</td>
                    </tr>`;

                    storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify(obj[2])
                    })
                    .then(res => res.json())
                    .then(data => {
                        
                        console.log(data);
                        
                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                        storeOutput.innerText = 'saved';

                        storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                        
                        storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                        <tr>
                            <td>cmd/ipnbr/info</td>
                            <td class="text-dark bg-success text-center">OK</td>
                        </tr>`;

                        storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    })
                    .catch(err => {

                        console.log(err);

                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                        storeOutput.innerText = err;

                        storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                    })
                })
                .catch(err => {

                    console.log(err);

                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                    storeOutput.innerText = err;

                    storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                })
            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };

        if(obj[0].ndx == 13) {

            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[0])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                
                storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                <tr>
                    <td>cmd/routes/default</td>
                    <td class="text-dark bg-success text-center">OK</td>
                </tr>`;

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(obj[1])
                })
                .then(res => res.json())
                .then(data => {
                    
                    console.log(data);
                    
                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                    storeOutput.innerText = 'saved';

                    storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                    
                    storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                    <tr>
                        <td>cmd/routes/links/sources</td>
                        <td class="text-dark bg-success text-center">OK</td>
                    </tr>`;

                    storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify(obj[2])
                    })
                    .then(res => res.json())
                    .then(data => {
                        
                        console.log(data);
                        
                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                        storeOutput.innerText = 'saved';

                        storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                        
                        storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                        <tr>
                            <td>cmd/routes/links/destinations</td>
                            <td class="text-dark bg-success text-center">OK</td>
                        </tr>`;

                        storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                        fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify(obj[3])
                        })
                        .then(res => res.json())
                        .then(data => {
                            
                            console.log(data);
                            
                            storeOutput.classList.replace('d-none', 'd-block');
                            storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                            storeOutput.innerText = 'saved';

                            storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                            
                            storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                            <tr>
                                <td>cmd/routes/entries/routes</td>
                                <td class="text-dark bg-success text-center">OK</td>
                            </tr>`;

                            storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                            method: 'POST',
                            headers: {
                                'Content-Type': 'application/json'
                            },
                            body: JSON.stringify(obj[4])
                            })
                            .then(res => res.json())
                            .then(data => {
                                
                                console.log(data);
                                
                                storeOutput.classList.replace('d-none', 'd-block');
                                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                                storeOutput.innerText = 'saved';

                                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                                
                                storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                                <tr>
                                    <td>cmd/routes/entries/vias</td>
                                    <td class="text-dark bg-success text-center">OK</td>
                                </tr>`;

                                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                
                            })
                            .catch(err => {

                                console.log(err);

                                storeOutput.classList.replace('d-none', 'd-block');
                                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                                storeOutput.innerText = err;

                                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                            })
                        })
                        .catch(err => {

                            console.log(err);

                            storeOutput.classList.replace('d-none', 'd-block');
                            storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                            storeOutput.innerText = err;

                            storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                        })
                    })
                    .catch(err => {

                        console.log(err);

                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                        storeOutput.innerText = err;

                        storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                    })
                })
                .catch(err => {

                    console.log(err);

                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                    storeOutput.innerText = err;

                    storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                })
            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };

        if(obj[0].ndx == 18) {

            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[0])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                
                storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                <tr>
                    <td>cmd/rplstatus/id</td>
                    <td class="text-dark bg-success text-center">OK</td>
                </tr>`;

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(obj[1])
                })
                .then(res => res.json())
                .then(data => {
                    
                    console.log(data);
                    
                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                    storeOutput.innerText = 'saved';

                    storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                    
                    storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                    <tr>
                        <td>cmd/rplstatus/dag</td>
                        <td class="text-dark bg-success text-center">OK</td>
                    </tr>`;

                    storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify(obj[2])
                    })
                    .then(res => res.json())
                    .then(data => {
                        
                        console.log(data);
                        
                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                        storeOutput.innerText = 'saved';

                        storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                        
                        storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                        <tr>
                            <td>cmd/rplstatus/time</td>
                            <td class="text-dark bg-success text-center">OK</td>
                        </tr>`;

                        storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    })
                    .catch(err => {

                        console.log(err);

                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                        storeOutput.innerText = err;

                        storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                    })
                })
                .catch(err => {

                    console.log(err);

                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                    storeOutput.innerText = err;

                    storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                })
            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };

        if(obj[0].ndx == 21) {

            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[0])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                
                storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                <tr>
                    <td>cmd/rplnbr/addr</td>
                    <td class="text-dark bg-success text-center">OK</td>
                </tr>`;

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(obj[1])
                })
                .then(res => res.json())
                .then(data => {
                    
                    console.log(data);
                    
                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                    storeOutput.innerText = 'saved';

                    storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                    
                    storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                    <tr>
                        <td>cmd/rplnbr/ranks</td>
                        <td class="text-dark bg-success text-center">OK</td>
                    </tr>`;

                    storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify(obj[2])
                    })
                    .then(res => res.json())
                    .then(data => {
                        
                        console.log(data);
                        
                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                        storeOutput.innerText = 'saved';

                        storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                        
                        storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                        <tr>
                            <td>cmd/rplnbr/values</td>
                            <td class="text-dark bg-success text-center">OK</td>
                        </tr>`;

                        storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                        fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify(obj[3])
                        })
                        .then(res => res.json())
                        .then(data => {
                            
                            console.log(data);
                            
                            storeOutput.classList.replace('d-none', 'd-block');
                            storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                            storeOutput.innerText = 'saved';

                            storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');
                            
                            storeTableTbody.innerHTML = demoTableDumpTbody.innerHTML += `
                            <tr>
                                <td>cmd/rplnbr/parens</td>
                                <td class="text-dark bg-success text-center">OK</td>
                            </tr>`;

                            storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                        })
                        .catch(err => {

                            console.log(err);

                            storeOutput.classList.replace('d-none', 'd-block');
                            storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                            storeOutput.innerText = err;

                            storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                        })
                    })
                    .catch(err => {

                        console.log(err);

                        storeOutput.classList.replace('d-none', 'd-block');
                        storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                        storeOutput.innerText = err;

                        storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                    })
                })
                .catch(err => {

                    console.log(err);

                    storeOutput.classList.replace('d-none', 'd-block');
                    storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                    storeOutput.innerText = err;

                    storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
                })
            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };

        if(obj[0].pckt.vld == false)
        {
            fetch(`http://${storeInputAddress.value}:${storeInputPort.value}/${storeInputPath.value}`,{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(obj[storeSelect.value])
            })
            .then(res => res.json())
            .then(data => {
                
                console.log(data);
                
                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-warning'); storeOutput.classList.add('bg-success');
                storeOutput.innerText = 'saved';

                storeDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-success');

                storeButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            })
            .catch(err => {

                console.log(err);

                storeOutput.classList.replace('d-none', 'd-block');
                storeOutput.classList.remove('bg-danger', 'bg-success'); storeOutput.classList.add('bg-danger');
                storeOutput.innerText = err;

                storeDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); storeDiv.classList.add('border-danger');
            })
        };


    })


    console.log('>>>> obj length: ' + obj.length);
    console.log('>>>> ' + obj);

}
































function simConsole(nodesAddr) {

    consoleDiv.classList.replace('border-secondary', 'border-primary');
    consoleH1.classList.replace('text-secondary', 'text-light');
    
    consoleSelectNode.classList.remove('text-light', 'bg-dark', 'border-secondary'); consoleSelectNode.classList.add('text-dark', 'bg-light');
    consoleSelectQuery.classList.remove('text-light', 'bg-dark', 'border-secondary'); consoleSelectQuery.classList.add('text-dark', 'bg-light');
    consoleButtonQuery.classList.remove('btn-outline-secondary'); consoleButtonQuery.classList.add('btn-primary'); 

    consoleInputSpan.classList.remove('bg-dark', 'text-secondary', 'border-secondary');
    consoleInputKey.classList.remove('bg-dark', 'text-secondary', 'border-secondary');

    let consoleSelectNodeHTML = '<option selected>node...</option>';
    nodesAddr.forEach((node, index) => {
        
        consoleSelectNodeHTML += `
        <option value=${index}>${node}</option>`

    })
    consoleSelectNode.innerHTML = consoleSelectNodeHTML;

    consoleButtonQuery.addEventListener('click', () => {

        storeDiv.classList.remove('border-danger', 'border-warning', 'border-success'); consoleDiv.classList.add('border-primary');
        storeButtonSave.classList.remove('d-none');
        storeDivSave.classList.replace('d-block', 'd-none');
        storeOutput.classList.replace('d-block', 'd-none');
        storeResponse.innerHTML = '';
        storeRequest.innerHTML = '';
        storeSelect.innerHTML = '';

        let obj = new Array;
        let tHTML = '';
        let dataHTML = '';

        function createErrorTable(errorObj) {

            dataHTML = `
                <table class="table table-sm table-striped bg-warning" id="legend-table-system">
                    <tbody class="bg-gray">
                        <tr>
                            <td colspan="1" class="text-secondary">error</td>
                            <td colspan="1" class="text-secondary">text</td>
                            <td colspan="2" class="">${errorObj.err.txt}</td>
                        </tr>
                        <tr>
                            <td colspan="1" class="text-secondary">error</td>
                            <td colspan="1" class="text-secondary">code</td>
                            <td colspan="2" class="">${errorObj.err.cd}</td>
                        </tr>
                    </tbody>
                </table>`

            consoleData.innerHTML = dataHTML;
        };
    
        switch(consoleSelectQuery.value) {

            case 'device-system':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/0`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            

                            obj[0] = JSON.parse(decryptedText);

                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="bg-gray">
                                            <tr>
                                                <td colspan="2" class="text-secondary">contiki version</td>
                                                <td colspan="2" class="">${obj[0].sys.cV}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">routing protocol</td>
                                                <td colspan="2" class="">${obj[0].sys.rt}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">network technology</td>
                                                <td colspan="2" class="">${obj[0].sys.net}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">IEEE 802.15.4 PAN ID</td>
                                                <td colspan="2" class="">${obj[0].sys.pId}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">mac technology</td>
                                                <td colspan="2" class="">${obj[0].sys.mac.t}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">IEEE 802.15.4 default channel</td>
                                                <td colspan="2" class="">${obj[0].sys.mac.dCh}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">node ID</td>
                                                <td colspan="2" class="">${obj[0].sys.nId}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">tentative link-local IPv6 address</td>
                                                <td colspan="2" class="">${obj[0].sys.tIad}</td>
                                            </tr>   
                                        </tbody>
                                    </table>`

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            }

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend('<pre>' + JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2) + '</pre>', undefined);

                            consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    }) 
                
                break;
            
            case 'device-sensor':
                    
                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/1`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            

                            obj[0] = JSON.parse(decryptedText);

                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>1</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>1</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="bg-gray">
                                            <tr>
                                                <td colspan="1" class="text-secondary">simulated temperature sensor</td>
                                                <td colspan="1" class="text-secondary"> = 15 + rand( ) % 30</td>
                                                <td colspan="2" class="">${obj[0].dev.tp}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">simulated humidity sensor</td>
                                                <td colspan="1" class="text-secondary"> = 80 + rand( ) % 17</td>
                                                <td colspan="2" class="">${obj[0].dev.hd}</td>
                                            </tr>
                                        </tbody>
                                    </table>`;

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>1</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend('<pre>' + JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2) + '</pre>', undefined);

                            consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                            storeButtonSave.addEventListener('click', () => {
                                
                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                            });
                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>1</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    }) 
                
                break;

            case 'device-energy':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/2`)

                .then((response) => response.text())
                    .then((text) => {
                        
                        console.log(text);
                        let decodedText = atob(text);

                        console.log(decodedText);
                        console.log(consoleInputKey.value);

                        let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
        
                        console.log(decryptedText);
                        

                        obj[0] = JSON.parse(decryptedText);

                        if(checksum(decryptedText)) {

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>2</b></td>
                                    <td class="text-success">INTACT</td>
                                    <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                </tr>`;

                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                            consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                            consoleOutputQuery.innerText = 'OK';

                            consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                        } else {

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>2</b></td>
                                    <td class="text-warning">CORRUPTED</td>
                                    <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                </tr>`;

                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                            consoleOutputQuery.innerText = 'CORRUPTED';

                            consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                        };
                        
                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleH2.classList.replace('d-none', 'd-block');

                        if(obj[0].pckt.vld) {

                            dataHTML = `
                                <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                    <tbody class="bg-gray">
                                        <tr>
                                            <td colspan="2" class="text-secondary">energest module active</td>
                                            <td colspan="2" class="">${obj[0].nrg.en}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">cpu active</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.cp}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">cpu in low power mode</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.lp}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">cpu in deep low power mode</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.dL}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">total tracking</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.tT}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">radio listening</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.rL}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">radio transmiting</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.rT}</td>
                                        </tr>
                                        <tr>
                                            <td colspan="1" class="text-secondary">radio off</td>
                                            <td colspan="1" class="text-secondary">(energest time source, seconds)</td>
                                            <td colspan="2" class="">${obj[0].nrg.rO}</td>
                                        </tr>
                                    </tbody>
                                </table>`;

                            consoleData.innerHTML = dataHTML;

                            storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                            storeButtonSave.addEventListener('click', () => {
                                
                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                            });

                        } else {

                            createErrorTable(obj[0]);

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                    <td class="text-warning">ERROR</td>
                                    <td class="text-warning">${obj[0].id.sT}</td>
                                </tr>`;
                            
                            storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                            storeButtonSave.addEventListener('click', () => {
                                
                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                            });
                        };

                        legendDiv.classList.replace('d-none', 'd-show');
                        constructLegend('<pre>' + JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2) + '</pre>', undefined);

                        consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    })

                .catch((error) => {

                    tHTML += `
                        <tr>
                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>2</b></td>
                            <td class="text-warning">INVALID</td>
                            <td class="text-danger">${error}</td>
                        </tr>`;

                    consoleTableQuery.classList.replace('d-none', 'd-block');
                    consoleTableQueryTbody.innerHTML = tHTML;

                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                    consoleOutputQuery.innerText = 'FAIL';

                    consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                    console.log(error);
                }) 
                
                break;

            case 'network-internet':
                
                obj = [];
                tHTML = '';
                dataHTML = '';

                window.setTimeout(() => {

                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/3`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>3</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>3</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="bg-gray">
                                            <tr>
                                                <td colspan="4" class="text-light bg-secondary">IP</td>
                                            </tr>
                                            <!-- <tr>
                                                <td colspan="2" class="text-secondary">network statistics collection active</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.uS}</td>
                                            </tr> -->
        .                                   <tr>
                                                <td colspan="2" class="text-secondary">received packets at the IP layer</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.rx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">sent packets at the IP layer</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.tx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">forwarded packets at the IP layer</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.fw}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">dropped packets at the IP layer</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.dr}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">packets dropped due to wrong IP version or header length</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.vE}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">packets dropped due to wrong IP length</td>
                                                <td colspan="1" class="text-secondary">high byte</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.hE}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">packets dropped due to wrong IP length</td>
                                                <td colspan="1" class="text-secondary">low byte</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.lE}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">packets dropped because they were IP fragments</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.fE}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">packets dropped due to IP checksum errors</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.cE}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">packets dropped because they were neither ICMP, UDP nor TCP</td>
                                                <td colspan="2" class="">${ obj[0].ipSt.ip.pE}</td>
                                            </tr>
                                        </tbody>
                                    </table>`

                                consoleData.innerHTML = dataHTML;

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>3</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>
                                <div class="container">
                                    <div class="row">
                                        <div class="col border">
                                            <pre> 
                                                ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                            </pre>
                                        </div>`, undefined);

                            consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                            window.setTimeout(() => {

                                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/4`)
            
                                .then((response) => response.text())
                                    .then((text) => {
                                        
                                        console.log(text);
                                        let decodedText = atob(text);
            
                                        console.log(decodedText);
                                        console.log(consoleInputKey.value);
            
                                        let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                        
                                        console.log(decryptedText);
                                        
                                        obj[1] = JSON.parse(decryptedText);
                                        
                                        if(checksum(decryptedText)) {
            
                                            tHTML += `
                                                <tr>
                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>4</b></td>
                                                    <td class="text-success">INTACT</td>
                                                    <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                </tr>`;
            
                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                            consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                            consoleOutputQuery.innerText = 'OK';
            
                                            consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
            
                                        } else {
            
                                            tHTML += `
                                                <tr>
                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>4</b></td>
                                                    <td class="text-warning">CORRUPTED</td>
                                                    <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                </tr>`
            
                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                            consoleOutputQuery.innerText = 'CORRUPTED';
            
                                            consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                        };
                                        
                                        consoleTableQuery.classList.replace('d-none', 'd-block');
                                        consoleTableQueryTbody.innerHTML = tHTML;
            
                                        consoleH2.classList.replace('d-none', 'd-block');
            
                                        if(obj[1].pckt.vld) {
            
                                            dataHTML = `
                                                <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                    <tbody class="bg-gray">
                                                        <tr>
                                                            <td colspan="4" class="text-light bg-secondary">IP</td>
                                                        </tr>
                                                        <!-- <tr>
                                                            <td colspan="2" class="text-secondary">network statistics collection active</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.uS}</td>
                                                        </tr> -->
                    .                                   <tr>
                                                            <td colspan="2" class="text-secondary">received packets at the IP layer</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.rx}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">sent packets at the IP layer</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.tx}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">forwarded packets at the IP layer</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.fw}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">dropped packets at the IP layer</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.dr}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">packets dropped due to wrong IP version or header length</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.vE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="1" class="text-secondary">packets dropped due to wrong IP length</td>
                                                            <td colspan="1" class="text-secondary">high byte</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.hE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="1" class="text-secondary">packets dropped due to wrong IP length</td>
                                                            <td colspan="1" class="text-secondary">low byte</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.lE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">packets dropped because they were IP fragments</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.fE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">packets dropped due to IP checksum errors</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.cE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">packets dropped because they were neither ICMP, UDP nor TCP</td>
                                                            <td colspan="2" class="">${ obj[0].ipSt.ip.pE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="4" class="text-light bg-secondary">ICMP</td>
                                                        </tr>
                                                        <!-- <tr>
                                                            <td colspan="2" class="text-secondary">network statistics collection active</td>
                                                            <td colspan="2" class="">${obj[1].icSt.uS}</td>
                                                        </tr> -->
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">received ICMP packets</td>
                                                            <td colspan="2" class="">${obj[1].icSt.ic.rx}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">sent ICMP packets</td>
                                                            <td colspan="2" class="">${obj[1].icSt.ic.tx}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">dropped ICMP packets</td>
                                                            <td colspan="2" class="">${obj[1].icSt.ic.dr}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">ICMP packets with a wrong type</td>
                                                            <td colspan="2" class="">${obj[1].icSt.ic.tE}</td>
                                                        </tr>
                                                        <tr>
                                                            <td colspan="2" class="text-secondary">ICMP packets with a bad checksum</td>
                                                            <td colspan="2" class="">${obj[1].icSt.ic.cE}</td>
                                                        </tr>
                                                    </tbody>
                                                </table>`
            
                                            consoleData.innerHTML = dataHTML;
            
                                            storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                            storeButtonSave.addEventListener('click', () => {
                                            
                                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                            });
            
                                        } else {
            
                                            createErrorTable(obj[1]);
            
                                            tHTML += `
                                                <tr>
                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>4</b></td>
                                                    <td class="text-warning">ERROR</td>
                                                    <td class="text-warning">${obj[1].id.sT}</td>
                                                </tr>`;
                                            
                                            storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                            storeButtonSave.addEventListener('click', () => {
                                            
                                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                            });
                                        };
            
                                        legendDiv.classList.replace('d-none', 'd-show');
                                        constructLegend(`
                                            <br>
                                            <div class="container">
                                                <div class="row">
                                                    <div class="col border">
                                                        <pre> 
                                                            ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                        </pre>
                                                    </div>
                                                    <div class="col border">
                                                        <pre>  
                                                            ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                        </pre>
                                                    </div>
                                                </div>
                                            </div>`, undefined);
            
                                        consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                                    })
            
                                .catch((error) => {
            
                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>4</b></td>
                                            <td class="text-warning">INVALID</td>
                                            <td class="text-danger">${error}</td>
                                        </tr>`;
            
                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                    consoleTableQueryTbody.innerHTML = tHTML;
            
                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                    consoleOutputQuery.innerText = 'FAIL';
            
                                    consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
            
                                    console.log(error);
                                });
            
                            },1000);
                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>3</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    })

                },1000);

                break;

            case 'network-transport':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/5`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>5</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>5</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="bg-gray">
                                            <!-- <tr>
                                                <td colspan="2" class="text-secondary">network statistics collection active</td>
                                                <td colspan="2" class="">${obj[0].tSt.uS}</td>
                                            </tr> -->
                                            <tr>
                                                <td colspan="2" class="text-light bg-secondary">TCP</td>
                                                <td colspan="2" class="text-light bg-secondary">${obj[0].tSt.tcp.use}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">received</td>
                                                <td colspan="1" class="text-secondary">TCP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.rx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">sent</td>
                                                <td colspan="1" class="text-secondary">TCP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.tx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">dropped</td>
                                                <td colspan="1" class="text-secondary">TCP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.dr}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">TCP segments</td>
                                                <td colspan="1" class="text-secondary">with a bad checksum</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.cE}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">TCP segments</td>
                                                <td colspan="1" class="text-secondary">with a bad ACK number</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.aA}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">received TCP RST (reset) segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.rst}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">retransmitted</td>
                                                <td colspan="1" class="text-secondary">TCP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.rM}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">dropped SYNs because too few connections were available</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.sD}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-secondary">SYNs for closed ports, triggering a RST</td>
                                                <td colspan="2" class="">${obj[0].tSt.tcp.sR}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" class="text-light bg-secondary">UDP</td>
                                                <td colspan="2" class="text-light bg-secondary">${obj[0].tSt.udp.use}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">dropped</td>
                                                <td colspan="1" class="text-secondary">UDP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.udp.dr}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">received</td>
                                                <td colspan="1" class="text-secondary">UDP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.udp.rx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">sent</td>
                                                <td colspan="1" class="text-secondary">UDP segments</td>
                                                <td colspan="2" class="">${obj[0].tSt.udp.tx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">UDP segments</td>
                                                <td colspan="1" class="text-secondary">with a bad checksum</td>
                                                <td colspan="2" class="">${obj[0].tSt.udp.cE}</td>
                                            </tr>
                                        </tbody>
                                    </table>`

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>  
                                <pre> 
                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                </pre>`, undefined);

                            consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>5</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    })
                
                break;

            case 'network-link':

                obj = [];
                tHTML = '';
                dataHTML = '';
                
                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/6`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>6</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>6</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="bg-gray">
                                            <!-- <tr>
                                                <td colspan="2" class="text-secondary">network statistics collection active</td>
                                                <td colspan="2" class="">${obj[0].dSt.uS}</td>
                                            </tr> -->
                                            <tr>
                                                <td colspan="1" class="text-secondary">dropped</td>
                                                <td colspan="1" class="text-secondary">ND6 packets</td>
                                                <td colspan="2" class="">${obj[0].dSt.nd6.dr}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">received</td>
                                                <td colspan="1" class="text-secondary">ND6 packets</td>
                                                <td colspan="2" class="">${obj[0].dSt.nd6.rx}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" class="text-secondary">sent</td>
                                                <td colspan="1" class="text-secondary">ND6 packets</td>
                                                <td colspan="2" class="">${obj[0].dSt.nd6.tx}</td>
                                            </tr>
                                        </tbody>
                                    </table>`;

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>6</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>  
                                    <pre> 
                                        ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                    </pre>`, undefined);

                            consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>6</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);

                    })

                break;

            case 'shell-macaddr':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/0`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-primary');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="">
                                            <tr>
                                                <td colspan="1" class="text-center text-light bg-secondary">command</td>
                                                <td colspan="1" class="text-center">mac-addr</td>
                                            </tr>
                                            <tr>
                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">Node MAC address: ${obj[0].id.adr}</td>
                                            </tr>
                                        </tbody>
                                    </table>`;

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>  
                                <pre> 
                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                </pre>`, undefined);

                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    })
                
                break;

            case 'shell-ipaddr':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/7`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>7</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>7</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="">
                                            <tr>
                                                <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                <td colspan="1" class="text-center">ipaddr</td>
                                            </tr>
                                            <tr>
                                                    <td colspan="2" style="background-color: rgb(41, 4, 30);" class="text-light border-top-0 border-bottom-0">Node IPv6 addresses:</td>
                                            </tr>`;
                                    
                                obj[0].addr.ad.forEach((address, index) => {

                                    if(address != null) {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${address}</td>
                                            </tr>`
                                    };
                                });

                                dataHTML += `
                                        </tbody>
                                    </table>`;
                                        
                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>0</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>  
                                <pre> 
                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                </pre>`, undefined);

                            consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>7</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    })
                
                break;

            case 'shell-ipnbr':

                obj = [];
                tHTML = '';
                dataHTML = '';

                window.setTimeout(() => {

                        fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/8`)

                            .then((response) => response.text())
                                .then((text) => {
                                    
                                    console.log(text);
                                    let decodedText = atob(text);

                                    console.log(decodedText);
                                    console.log(consoleInputKey.value);

                                    let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                    
                                    console.log(decryptedText);
                                    
                                    obj[0] = JSON.parse(decryptedText);
                                    
                                    if(checksum(decryptedText)) {

                                        tHTML += `
                                            <tr>
                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>8</b></td>
                                                <td class="text-success">INTACT</td>
                                                <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                            </tr>`;

                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                        consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                        consoleOutputQuery.innerText = 'OK';

                                        consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                                    } else {

                                        tHTML += `
                                            <tr>
                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>8</b></td>
                                                <td class="text-warning">CORRUPTED</td>
                                                <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                            </tr>`;

                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                        consoleOutputQuery.innerText = 'CORRUPTED';

                                        consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                    };
                                    
                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                    consoleTableQueryTbody.innerHTML = tHTML;

                                    consoleH2.classList.replace('d-none', 'd-block');

                                    if(obj[0].pckt.vld) {

                                        dataHTML = `
                                            <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                <tbody class="">
                                                    <tr>
                                                        <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                        <td colspan="1" class="text-center">ip_nbr</td>
                                                    </tr>
                                                    <tr>
                                                            <td colspan="2" style="background-color: rgb(41, 4, 30);" class="text-light border-bottom-0">Node IPv6 neighbors:</td>
                                                    </tr>`;
                                        
                                        for(let nbr = 0; nbr < obj[0].nsIP.ns.length; nbr++) {

                                            if(obj[0].nsIP.ns[nbr] != null) {

                                                dataHTML += `
                                                    <tr>
                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[0].nsIP.ns[nbr].ipAddr}</td>
                                                    </tr>`
                                            };
                                        };
                                        
                                        dataHTML += `
                                                </tbody>
                                            </table>`;
                                                
                                        consoleData.innerHTML = dataHTML;

                                    } else {

                                        createErrorTable(obj[0]);
        
                                        tHTML += `
                                            <tr>
                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>8</b></td>
                                                <td class="text-warning">ERROR</td>
                                                <td class="text-warning">${obj[0].id.sT}</td>
                                            </tr>`;
                                    };

                                    legendDiv.classList.replace('d-none', 'd-show');
                                    constructLegend(`
                                        <br>  
                                        <pre> 
                                            ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                        </pre>`, undefined);

                                    consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                    window.setTimeout(() => {

                                        fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/9`)
                    
                                            .then((response) => response.text())
                                                .then((text) => {
                                                    
                                                    console.log(text);
                                                    let decodedText = atob(text);
                    
                                                    console.log(decodedText);
                                                    console.log(consoleInputKey.value);
                    
                                                    let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                    
                                                    console.log(decryptedText);
                                                    
                                                    obj[1] = JSON.parse(decryptedText);
                                                    
                                                    if(checksum(decryptedText)) {
                    
                                                        tHTML += `
                                                            <tr>
                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>9</b></td>
                                                                <td class="text-success">INTACT</td>
                                                                <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                                            </tr>`;
                    
                                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                        consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                        consoleOutputQuery.innerText = 'OK';
                    
                                                        consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                    
                                                    } else {
                    
                                                        tHTML += `
                                                            <tr>
                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>9</b></td>
                                                                <td class="text-warning">CORRUPTED</td>
                                                                <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                                            </tr>`;
                    
                                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                        consoleOutputQuery.innerText = 'CORRUPTED';
                    
                                                        consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                    };
                                                    
                                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                                    consoleTableQueryTbody.innerHTML = tHTML;
                    
                                                    consoleH2.classList.replace('d-none', 'd-block');
                    
                                                    if(obj[1].pckt.vld) {
                    
                                                        dataHTML = `
                                                            <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                <tbody class="">
                                                                    <tr>
                                                                        <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                        <td colspan="1" class="text-center">ip_nbr</td>
                                                                    </tr>
                                                                    <tr>
                                                                            <td colspan="2" style="background-color: rgb(41, 4, 30);" class="text-light border-bottom-0">Node IPv6 neighbors:</td>
                                                                    </tr>`;
                                                        
                                                        for(let nbr = 0; nbr < obj[1].nsLL.ns.length; nbr++) {
                    
                                                            if(obj[1].nsLL.ns[nbr] != null) {
                    
                                                                dataHTML += `
                                                                    <tr>
                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[0].nsIP.ns[nbr].ipAddr} <-> ${obj[1].nsLL.ns[nbr].llAddr}</td>
                                                                    </tr>`
                                                            }
                                                        };
                    
                                                        dataHTML += `
                                                                </tbody>
                                                            </table>`;
                                                                
                                                        consoleData.innerHTML = dataHTML;
                    
                                                    } else {
                    
                                                        createErrorTable(obj[1]);
                        
                                                        tHTML += `
                                                            <tr>
                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>9</b></td>
                                                                <td class="text-warning">ERROR</td>
                                                                <td class="text-warning">${obj[1].id.sT}</td>
                                                            </tr>`;
                                                    };
                    
                                                    legendDiv.classList.replace('d-none', 'd-show');
                                                    constructLegend(`
                                                        <br>
                                                        <div class="container">
                                                            <div class="row">
                                                                <div class="col border">
                                                                    <pre> 
                                                                        ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                    </pre>
                                                                </div>
                                                                <div class="col border">
                                                                    <pre>  
                                                                        ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                                    </pre>
                                                                </div>
                                                            </div>
                                                        </div>`, undefined);
                    
                                                    consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                    window.setTimeout(() => {

                                                        fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/10`)
                                    
                                                            .then((response) => response.text())
                                                                .then((text) => {
                                                                    
                                                                    console.log(text);
                                                                    let decodedText = atob(text);
                                    
                                                                    console.log(decodedText);
                                                                    console.log(consoleInputKey.value);
                                    
                                                                    let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                    
                                                                    console.log(decryptedText);
                                                                    
                                                                    obj[2] = JSON.parse(decryptedText);
                                                                    
                                                                    if(checksum(decryptedText)) {
                                    
                                                                        tHTML += `
                                                                            <tr>
                                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>10</b></td>
                                                                                <td class="text-success">INTACT</td>
                                                                                <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                                                            </tr>`;
                                    
                                                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                        consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                        consoleOutputQuery.innerText = 'OK';
                                    
                                                                        consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                    
                                                                    } else {
                                    
                                                                        tHTML += `
                                                                            <tr>
                                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>10</b></td>
                                                                                <td class="text-warning">CORRUPTED</td>
                                                                                <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                                                            </tr>`;
                                    
                                                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                        consoleOutputQuery.innerText = 'CORRUPTED';
                                    
                                                                        consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                    };
                                                                    
                                                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                    consoleTableQueryTbody.innerHTML = tHTML;
                                    
                                                                    consoleH2.classList.replace('d-none', 'd-block');
                                    
                                                                    if(obj[2].pckt.vld) {
                                    
                                                                        dataHTML = `
                                                                            <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                                <tbody class="">
                                                                                    <tr>
                                                                                        <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                        <td colspan="1" class="text-center">ip_nbr</td>
                                                                                    </tr>
                                                                                    <tr>
                                                                                            <td colspan="2" style="background-color: rgb(41, 4, 30);" class="text-light border-bottom-0">Node IPv6 neighbors:</td>
                                                                                    </tr>`;
                                                                        
                                                                        for(let nbr = 0; nbr < obj[2].nsSt.ns.length; nbr++) {
                                    
                                                                            if(obj[2].nsSt.ns[nbr] != null) {
                                    
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[0].nsIP.ns[nbr].ipAddr} <-> ${obj[1].nsLL.ns[nbr].llAddr}, router ${obj[2].nsSt.ns[nbr].router}, state: ${obj[2].nsSt.ns[nbr].state}</td>
                                                                                    </tr>`
                                                                            };
                                                                        };
                                    
                                                                        dataHTML += `
                                                                                </tbody>
                                                                            </table>`;
                                                                                
                                                                        consoleData.innerHTML = dataHTML;
                                    
                                                                        storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                                                        storeButtonSave.addEventListener('click', () => {
                                                                    
                                                                            cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                        });
                                    
                                                                    } else {
                                    
                                                                        createErrorTable(obj[2]);
                                        
                                                                        tHTML += `
                                                                            <tr>
                                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>10</b></td>
                                                                                <td class="text-warning">ERROR</td>
                                                                                <td class="text-warning">${obj[2].id.sT}</td>
                                                                            </tr>`;
                                    
                                                                        storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                                                        storeButtonSave.addEventListener('click', () => {
                                                                    
                                                                            cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                        });
                                                                    };
                                    
                                                                    legendDiv.classList.replace('d-none', 'd-show');
                                                                    constructLegend(`
                                                                        <br>
                                                                        <div class="container">
                                                                            <div class="row">
                                                                                <div class="col border">
                                                                                    <pre> 
                                                                                        ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                    </pre>
                                                                                </div>
                                                                                <div class="col border">
                                                                                    <pre>  
                                                                                        ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                                                    </pre>
                                                                                </div>
                                                                                <div class="col border">
                                                                                    <pre>  
                                                                                        ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)}  
                                                                                    </pre>
                                                                                </div>
                                                                            </div>
                                                                        </div>`, undefined);
                                    
                                                                    consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                                                                })
                                    
                                                            .catch((error) => {
                                    
                                                                tHTML += `
                                                                    <tr>
                                                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>10</b></td>
                                                                        <td class="text-warning">INVALID</td>
                                                                        <td class="text-danger">${error}</td>
                                                                    </tr>`;
                                    
                                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                consoleTableQueryTbody.innerHTML = tHTML;
                                    
                                                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                                consoleOutputQuery.innerText = 'FAIL';
                                    
                                                                consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                    
                                                                console.log(error);
                                                            });
                                    
                                                    }, 1000);
                    
                                                })
                    
                                            .catch((error) => {
                    
                                                tHTML += `
                                                    <tr>
                                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>9</b></td>
                                                        <td class="text-warning">INVALID</td>
                                                        <td class="text-danger">${error}</td>
                                                    </tr>`;
                    
                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                consoleTableQueryTbody.innerHTML = tHTML;
                    
                                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                consoleOutputQuery.innerText = 'FAIL';
                    
                                                consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                    
                                                console.log(error);
                    
                                            });
                    
                                    }, 1000);
                                })

                        .catch((error) => {

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>8</b></td>
                                    <td class="text-warning">INVALID</td>
                                    <td class="text-danger">${error}</td>
                                </tr>`;

                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                            consoleOutputQuery.innerText = 'FAIL';

                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                            console.log(error);
                        });

                }, 1000);
                
                break;

            case 'shell-tschstatus':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/11`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>11</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-primary');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>11</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="">
                                            <tr>
                                                <td colspan="1" class="text-center text-light bg-secondary">command</td>
                                                <td colspan="1" class="text-center">tsch-status</td>
                                            </tr>`;
                                
                                if (obj[0].tsch.tsch == true) {

                                    if (obj[0].tsch.coo == true) {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="2" style="background-color: rgb(41, 4, 30);" class="text-light border-top-0 border-bottom-0">TSCH status:</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Is coordinator:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">1</td>
                                            </tr>`;

                                    } else {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Is coordinator:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">0</td>
                                            </tr>`;
                                    };

                                    if (obj[0].tsch.ass == true) {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Is associated:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">1</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- PAN ID:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">${obj[0].tsch.panid}</td>
                                            </tr>`;

                                        if(obj[0].tsch.panSecured == true) {

                                            dataHTML += `
                                                <tr>
                                                    <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Is PAN secured:</td>
                                                    <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">1</td>
                                                </tr>`;

                                        } else {

                                            dataHTML += `
                                                <tr>
                                                    <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Is PAN secured:</td>
                                                    <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">0</td>
                                                </tr>`;
                                        };

                                        dataHTML += `
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Join priority:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">${obj[0].tsch.joinp}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Time source:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">${obj[0].tsch.tsrc}</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Last synchronized:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">${obj[0].tsch.lsyn} seconds ago</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Drift w.r.t. coordinator:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">${obj[0].tsch.drift} ppm</td>
                                            </tr>
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Network uptime:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">${obj[0].tsch.netup} seconds</td>
                                            </tr>`;


                                    } else {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Is associated:</td>
                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">0</td>
                                            </tr>`;
                                    };

                                } else {

                                    dataHTML += `
                                        <tr>
                                            <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">Command not found. Type 'help' for a list of commands</td>
                                        </tr>`;
                                };

                                
                                dataHTML += `
                                    </tbody>
                                        </table>`;

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>11</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>  
                                <pre> 
                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                </pre>`, undefined);

                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>11</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    })
                
                break;

                case 'shell-tschschedule':

                obj = [];
                tHTML = '';
                dataHTML = '';

                fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/12`)

                    .then((response) => response.text())
                        .then((text) => {
                            
                            console.log(text);
                            let decodedText = atob(text);

                            console.log(decodedText);
                            console.log(consoleInputKey.value);

                            let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
            
                            console.log(decryptedText);
                            
                            obj[0] = JSON.parse(decryptedText);
                            
                            if(checksum(decryptedText)) {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>12</b></td>
                                        <td class="text-success">INTACT</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                consoleOutputQuery.innerText = 'OK';

                                consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-primary');

                            } else {

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>12</b></td>
                                        <td class="text-warning">CORRUPTED</td>
                                        <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                    </tr>`;

                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                consoleOutputQuery.innerText = 'CORRUPTED';

                                consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                            };
                            
                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleH2.classList.replace('d-none', 'd-block');

                            if(obj[0].pckt.vld) {

                                dataHTML = `
                                    <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                        <tbody class="">
                                            <tr>
                                                <td colspan="1" class="text-center text-light bg-secondary">command</td>
                                                <td colspan="1" class="text-center">tsch-status</td>
                                            </tr>`;
                                
                                if (obj[0].tschSch.tsch == true) {

                                    if (obj[0].tschSch.lock == true) {


                                    } else {

                                        if(obj[0].tschSch.sch == false) {

                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">TSCH schedule: no slotframe</td>
                                                </tr>`;
                                        } else {

                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">TSCH schedule:</td>
                                                </tr>`;

                                            obj[0].tschSch.slts.forEach((slot, slotindex) => {

                                                dataHTML += `
                                                    <tr>
                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Slotframe: handle ${slot.hdl}, size ${slot.sz}, links:</td>
                                                    </tr>`;

                                                slot.lnks.forEach((link, linkindex) => {

                                                    dataHTML += `
                                                        <tr>
                                                            <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">---- Options ${link.opt}, type ${link.tp}, timeslot ${link.tslt}, channel offset ${chOf}, address ${link.ad}</td>
                                                        </tr>`;
                                                })
                                            });
                                        };
                                    };

                                } else {

                                    dataHTML += `
                                        <tr>
                                            <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">Command not found. Type 'help' for a list of commands</td>
                                        </tr>`;
                                };

                                
                                dataHTML += `
                                    </tbody>
                                        </table>`;

                                consoleData.innerHTML = dataHTML;

                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });

                            } else {

                                createErrorTable(obj[0]);

                                tHTML += `
                                    <tr>
                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>12</b></td>
                                        <td class="text-warning">ERROR</td>
                                        <td class="text-warning">${obj[0].id.sT}</td>
                                    </tr>`;
                                
                                storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                storeButtonSave.addEventListener('click', () => {
                                
                                    cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                });
                            };

                            legendDiv.classList.replace('d-none', 'd-show');
                            constructLegend(`
                                <br>  
                                <pre> 
                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                </pre>`, undefined);

                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                        })

                    .catch((error) => {

                        tHTML += `
                            <tr>
                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>12</b></td>
                                <td class="text-warning">INVALID</td>
                                <td class="text-danger">${error}</td>
                            </tr>`;

                        consoleTableQuery.classList.replace('d-none', 'd-block');
                        consoleTableQueryTbody.innerHTML = tHTML;

                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                        consoleOutputQuery.innerText = 'FAIL';

                        consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                        console.log(error);
                    })
                
                break;
            
            case 'shell-routes':

                obj = [];
                tHTML = '';
                dataHTML = '';

                window.setTimeout(() => {

                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/13`)

                        .then((response) => response.text())
                            .then((text) => {
                                
                                console.log(text);
                                let decodedText = atob(text);

                                console.log(decodedText);
                                console.log(consoleInputKey.value);

                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                
                                console.log(decryptedText);
                                
                                obj[0] = JSON.parse(decryptedText);
                                
                                if(checksum(decryptedText)) {

                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>13</b></td>
                                            <td class="text-success">INTACT</td>
                                            <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                        </tr>`;

                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                    consoleOutputQuery.innerText = 'OK';

                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                                } else {

                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>13</b></td>
                                            <td class="text-warning">CORRUPTED</td>
                                            <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                        </tr>`;

                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                    consoleOutputQuery.innerText = 'CORRUPTED';

                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');

                                }
                                
                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                consoleTableQueryTbody.innerHTML = tHTML;

                                consoleH2.classList.replace('d-none', 'd-block');

                                if(obj[0].pckt.vld) {

                                    dataHTML = `
                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                            <tbody class="">
                                                <tr>
                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                    <td colspan="1" class="text-center">ip_nbr</td>
                                                </tr>
                                                <tr>
                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0">Default route:</td>
                                                </tr>`;
                                            
                                    if(obj[0].rt.lt == "infinite") {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt})</td>
                                            </tr>`;

                                    } else {

                                        dataHTML += `
                                            <tr>
                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt} seconds)</td>
                                            </tr>`;
                                    };
                                    
                                    dataHTML += `
                                            </tbody>
                                        </table>`;
                                            
                                    consoleData.innerHTML = dataHTML;

                                } else {

                                    createErrorTable(obj[0]);
    
                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>13</b></td>
                                            <td class="text-warning">ERROR</td>
                                            <td class="text-warning">${obj[0].id.sT}</td>
                                        </tr>`;
                                };

                                legendDiv.classList.replace('d-none', 'd-show');
                                constructLegend(`
                                    <br>
                                    <div class="container">
                                        <div class="row">
                                            <div class="col border">
                                                <pre> 
                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                </pre>
                                            </div>
                                        </div>
                                    </div>`, undefined);

                                    consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                    window.setTimeout(() => {

                                        fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/14`)
                    
                                            .then((response) => response.text())
                                                .then((text) => {
                                                    
                                                    console.log(text);
                                                    let decodedText = atob(text);
                    
                                                    console.log(decodedText);
                                                    console.log(consoleInputKey.value);
                    
                                                    let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                    
                                                    console.log(decryptedText);
                                                    
                                                    obj[1] = JSON.parse(decryptedText);
                                                    
                                                    if(checksum(decryptedText)) {
                    
                                                        tHTML += `
                                                            <tr>
                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>14</b></td>
                                                                <td class="text-success">INTACT</td>
                                                                <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                            </tr>`;
                    
                                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                        consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                        consoleOutputQuery.innerText = 'OK';
                    
                                                        consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                    
                                                    } else {
                    
                                                        tHTML += `
                                                            <tr>
                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>14</b></td>
                                                                <td class="text-warning">CORRUPTED</td>
                                                                <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                            </tr>`;
                    
                                                        consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                        consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                        consoleOutputQuery.innerText = 'CORRUPTED';
                    
                                                        consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                    };
                                                    
                                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                                    consoleTableQueryTbody.innerHTML = tHTML;
                    
                                                    consoleH2.classList.replace('d-none', 'd-block');
                    
                                                    if(obj[1].pckt.vld) {
                    
                                                        dataHTML = `
                                                            <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                <tbody class="">
                                                                    <tr>
                                                                        <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                        <td colspan="1" class="text-center">ip_nbr</td>
                                                                    </tr>
                                                                    <tr>
                                                                            <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0">Default route:</td>
                                                                    </tr>`;
                                                                
                                                        if(obj[0].rt.lt == "infinite") {
                    
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt})</td>
                                                                </tr>`;
                    
                                                        } else {
                    
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt} seconds)</td>
                                                                </tr>`;
                                                        };
                    
                                                        let atLeast1routingLink = false;
                    
                                                        for(let source = 0; source < obj[1].rtLS.ls.length; source++) {
                    
                                                            if(obj[1].rtLS.ls[source] != null) {
                    
                                                                atLeast1routingLink = true;
                                                            };
                                                        };
                    
                                                        if(atLeast1routingLink) {
                    
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">Routing links (${obj[1].rtLS.totLs} in total):</td>
                                                                </tr>`;
                    
                                                            for(source = 0; source < obj[1].rtLS.ls.length; source++) {
                    
                                                                if(obj[1].rtLS.ls[source] != null) {
                    
                                                                    dataHTML += `
                                                                        <tr>
                                                                            <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[1].rtLS.ls[source].from} ${obj[1].rtLS.ls[source].dodagRoot ? '(DODAG root)' : ''}</td>
                                                                        </tr>`;
                                                                };
                                                            };
                    
                                                            } else {
                    
                                                                dataHTML += `
                                                                    <tr>
                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">No routing links</td>
                                                                    </tr>`;
                                                            };
                    
                                                        dataHTML += `
                                                                </tbody>
                                                            </table>`;
                                                                
                                                        consoleData.innerHTML = dataHTML;
                    
                                                    } else {
                    
                                                        createErrorTable(obj[1]);
                        
                                                        tHTML += `
                                                            <tr>
                                                                <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>14</b></td>
                                                                <td class="text-warning">ERROR</td>
                                                                <td class="text-warning">${obj[1].id.sT}</td>
                                                            </tr>`;
                                                    };
                    
                                                    legendDiv.classList.replace('d-none', 'd-show');
                                                    constructLegend(`
                                                        <br>
                                                        <div class="container">
                                                            <div class="row">
                                                                <div class="col border">
                                                                    <pre> 
                                                                        ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                    </pre>
                                                                </div>
                                                                <div class="col border">
                                                                    <pre>  
                                                                        ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                                    </pre>
                                                                </div>
                                                            </div>
                                                        </div>`, undefined);
                    
                                                        consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                        window.setTimeout(() => {

                                                            fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/15`)
                                        
                                                                .then((response) => response.text())
                                                                    .then((text) => {
                                                                        
                                                                        console.log(text);
                                                                        let decodedText = atob(text);
                                        
                                                                        console.log(decodedText);
                                                                        console.log(consoleInputKey.value);
                                        
                                                                        let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                        
                                                                        console.log(decryptedText);
                                                                        
                                                                        obj[2] = JSON.parse(decryptedText);
                                                                        
                                                                        if(checksum(decryptedText)) {
                                        
                                                                            tHTML += `
                                                                                <tr>
                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>15</b></td>
                                                                                    <td class="text-success">INTACT</td>
                                                                                    <td class="">systemTime: <b>${obj[2].id.sT}</b>s</td>
                                                                                </tr>`;
                                        
                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                            consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                            consoleOutputQuery.innerText = 'OK';
                                        
                                                                            consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                        
                                                                        } else {
                                        
                                                                            tHTML += `
                                                                                <tr>
                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>15</b></td>
                                                                                    <td class="text-warning">CORRUPTED</td>
                                                                                    <td class="">systemTime: <b>${obj[2].id.sT}</b>s</td>
                                                                                </tr>`;
                                        
                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                            consoleOutputQuery.innerText = 'CORRUPTED';
                                        
                                                                            consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                        };
                                                                        
                                                                        consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                        consoleTableQueryTbody.innerHTML = tHTML;
                                        
                                                                        consoleH2.classList.replace('d-none', 'd-block');
                                        
                                                                        if(obj[2].pckt.vld) {
                                        
                                                                            dataHTML = `
                                                                                <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                                    <tbody class="">
                                                                                        <tr>
                                                                                            <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                            <td colspan="1" class="text-center">ip_nbr</td>
                                                                                        </tr>
                                                                                        <tr>
                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0">Default route:</td>
                                                                                        </tr>`;
                                                                                    
                                                                            if(obj[0].rt.lt == "infinite") {
                                        
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt})</td>
                                                                                    </tr>`;
                                        
                                                                            } else {
                                        
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt} seconds)</td>
                                                                                    </tr>`;
                                                                            };
                                        
                                                                            let atLeast1routingLink = false;
                                        
                                                                            for(let destination = 0; destination < obj[2].rtLD.ls.length; destination++) {
                                        
                                                                                if(obj[2].rtLD.ls[destination] != null) {
                                        
                                                                                    atLeast1routingLink = true;
                                                                                };
                                                                            };
                                        
                                                                            if(atLeast1routingLink) {
                                        
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">Routing links (${obj[1].rtLS.totLs} in total):</td>
                                                                                    </tr>`;
                                        
                                                                                for(destination = 0; destination < obj[1].rtLS.ls.length; destination++) {
                                        
                                                                                    if(obj[2].rtLS.ls[destination] != null) {
                                        
                                                                                        dataHTML += `
                                                                                            <tr>
                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[1].rtLS.ls[destination].from} ${obj[1].rtLS.ls[destination].dodagRoot ? '(DODAG root)' : ''} to ${obj[2].rtLD.ls[destination].to} (lifetime: ${obj[2].rtLD.ls[destination].lf})</td>
                                                                                            </tr>`
                                                                                    };
                                                                                };
                                        
                                                                            } else {
                                        
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">No routing links</td>
                                                                                    </tr>`
                                                                            };
                                        
                                                                            dataHTML += `
                                                                                    </tbody>
                                                                                </table>`;
                                                                                    
                                                                            consoleData.innerHTML = dataHTML;
                                        
                                                                        } else {
                                        
                                                                            createErrorTable(obj[2]);
                                            
                                                                            tHTML += `
                                                                                <tr>
                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>15</b></td>
                                                                                    <td class="text-warning">ERROR</td>
                                                                                    <td class="text-warning">${obj[2].id.sT}</td>
                                                                                </tr>`;
                                                                        };
                                        
                                                                        legendDiv.classList.replace('d-none', 'd-show');
                                                                        constructLegend(`
                                                                            <br>
                                                                            <div class="container">
                                                                                <div class="row">
                                                                                    <div class="col border">
                                                                                        <pre> 
                                                                                            ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                        </pre>
                                                                                    </div>
                                                                                    <div class="col border">
                                                                                        <pre>  
                                                                                            ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                                                        </pre>
                                                                                    </div>
                                                                                    <div class="col border">
                                                                                        <pre>  
                                                                                            ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)}  
                                                                                        </pre>
                                                                                    </div>
                                                                                </div>
                                                                            </div>`, undefined);
                                        
                                                                        consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                                        window.setTimeout(() => {

                                                                            fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/16`)
                                                        
                                                                                .then((response) => response.text())
                                                                                    .then((text) => {
                                                                                        
                                                                                        console.log(text);
                                                                                        let decodedText = atob(text);
                                                        
                                                                                        console.log(decodedText);
                                                                                        console.log(consoleInputKey.value);
                                                        
                                                                                        let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                                        
                                                                                        console.log(decryptedText);
                                                                                        
                                                                                        obj[3] = JSON.parse(decryptedText);
                                                                                        
                                                                                        if(checksum(decryptedText)) {
                                                        
                                                                                            tHTML += `
                                                                                                <tr>
                                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>16</b></td>
                                                                                                    <td class="text-success">INTACT</td>
                                                                                                    <td class="">systemTime: <b>${obj[3].id.sT}</b>s</td>
                                                                                                </tr>`;
                                                        
                                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                            consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                                            consoleOutputQuery.innerText = 'OK';
                                                        
                                                                                            consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                                        
                                                                                        } else {
                                                        
                                                                                            tHTML += `
                                                                                                <tr>
                                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>16</b></td>
                                                                                                    <td class="text-warning">CORRUPTED</td>
                                                                                                    <td class="">systemTime: <b>${obj[3].id.sT}</b>s</td>
                                                                                                </tr>`;
                                                        
                                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                                            consoleOutputQuery.innerText = 'CORRUPTED';
                                                        
                                                                                            consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                                        };
                                                                                        
                                                                                        consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                                        consoleTableQueryTbody.innerHTML = tHTML;
                                                        
                                                                                        consoleH2.classList.replace('d-none', 'd-block');
                                                        
                                                                                        if(obj[3].pckt.vld) {
                                                        
                                                                                            dataHTML = `
                                                                                                <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                                                    <tbody class="">
                                                                                                        <tr>
                                                                                                            <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                                            <td colspan="1" class="text-center">ip_nbr</td>
                                                                                                        </tr>
                                                                                                        </tr>
                                                                                                        <tr>
                                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0">Default route:</td>
                                                                                                        </tr>`;
                                                                                                    
                                                                                            if(obj[0].rt.lt == "infinite") {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt})</td>
                                                                                                    </tr>`;
                                                        
                                                                                            } else {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt} seconds)</td>
                                                                                                    </tr>`;
                                                                                            };
                                                        
                                                                                            let atLeast1routingLink = false;
                                                        
                                                                                            for(let destination = 0; destination < obj[2].rtLD.ls.length; destination++) {
                                                        
                                                                                                if(obj[2].rtLD.ls[destination] != null) {
                                                        
                                                                                                    atLeast1routingLink = true;
                                                                                                }
                                                                                            };
                                                        
                                                                                            if(atLeast1routingLink) {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">Routing links (${obj[1].rtLS.totLs} in total):</td>
                                                                                                    </tr>`;
                                                        
                                                                                                for(destination = 0; destination < obj[1].rtLS.ls.length; destination++) {
                                                        
                                                                                                    if(obj[2].rtLS.ls[destination] != null) {
                                                        
                                                                                                        dataHTML += `
                                                                                                            <tr>
                                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[1].rtLS.ls[destination].from} ${obj[1].rtLS.ls[destination].dodagRoot ? '(DODAG root)' : ''} to ${obj[2].rtLD.ls[destination].to} (lifetime: ${obj[2].rtLD.ls[destination].lf})</td>
                                                                                                            </tr>`
                                                                                                    };
                                                                                                };
                                                        
                                                                                            } else {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">No routing links</td>
                                                                                                    </tr>`
                                                                                            };
                                                        
                                                                                            let atLeast1routingEntry = false;
                                                        
                                                                                            for(let route = 0; route < obj[3].rtERt.es.length; route++) {
                                                        
                                                                                                if(obj[3].rtERt.es[route] != null) {
                                                        
                                                                                                    atLeast1routingEntry = true;
                                                                                                };
                                                                                            };
                                                        
                                                                                            if(atLeast1routingEntry) {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">Routing entries (${obj[3].rtERt.totEs} in total):</td>
                                                                                                    </tr>`;
                                                        
                                                                                                for(route = 0; route < obj[3].rtERt.es.length; route++) {
                                                        
                                                                                                    if(obj[3].rtERt.es[route] != null) {
                                                        
                                                                                                        dataHTML += `
                                                                                                            <tr>
                                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[3].rtERt.es[route].rt}</td>
                                                                                                            </tr>`
                                                                                                    };
                                                                                                };
                                                        
                                                                                            } else {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">No routing entries</td>
                                                                                                    </tr>`
                                                                                            };
                                                        
                                                                                            dataHTML += `
                                                                                                    </tbody>
                                                                                                </table>`;
                                                                                                    
                                                                                            consoleData.innerHTML = dataHTML;
                                                        
                                                                                        } else {
                                                        
                                                                                            createErrorTable(obj[3]);
                                                            
                                                                                            tHTML += `
                                                                                                <tr>
                                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>16</b></td>
                                                                                                    <td class="text-warning">ERROR</td>
                                                                                                    <td class="text-warning">${obj[3].id.sT}</td>
                                                                                                </tr>`;
                                                                                        };
                                                        
                                                                                        legendDiv.classList.replace('d-none', 'd-show');
                                                                                        constructLegend(`
                                                                                            <br>
                                                                                            <div class="container">
                                                                                                <div class="row">
                                                                                                    <div class="col border">
                                                                                                        <pre> 
                                                                                                            ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                                        </pre>
                                                                                                    </div>
                                                                                                    <div class="col border">
                                                                                                        <pre>  
                                                                                                            ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                                                                        </pre>
                                                                                                    </div>
                                                                                                    <div class="col border">
                                                                                                        <pre>  
                                                                                                            ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)}  
                                                                                                        </pre>
                                                                                                    </div>
                                                                                                    <div class="col border">
                                                                                                        <pre>  
                                                                                                            ${JSON.stringify(elaborate(obj[3], checksum(decryptedText)), null, 2)}  
                                                                                                        </pre>
                                                                                                    </div>
                                                                                                </div>
                                                                                            </div>`, undefined);
                                                        
                                                                                        consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                                                        window.setTimeout(() => {

                                                                                            fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/17`)
                                                                        
                                                                                                .then((response) => response.text())
                                                                                                    .then((text) => {
                                                                                                        
                                                                                                        console.log(text);
                                                                                                        let decodedText = atob(text);
                                                                        
                                                                                                        console.log(decodedText);
                                                                                                        console.log(consoleInputKey.value);
                                                                        
                                                                                                        let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                                                        
                                                                                                        console.log(decryptedText);
                                                                                                        
                                                                                                        obj[4] = JSON.parse(decryptedText);
                                                                                                        
                                                                                                        if(checksum(decryptedText)) {
                                                                        
                                                                                                            tHTML += `
                                                                                                                <tr>
                                                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>17</b></td>
                                                                                                                    <td class="text-success">INTACT</td>
                                                                                                                    <td class="">systemTime: <b>${obj[4].id.sT}</b>s</td>
                                                                                                                </tr>`;
                                                                        
                                                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                                            consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                                                            consoleOutputQuery.innerText = 'OK';
                                                                        
                                                                                                            consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                                                        
                                                                                                        } else {
                                                                        
                                                                                                            tHTML += `
                                                                                                                <tr>
                                                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>17</b></td>
                                                                                                                    <td class="text-warning">CORRUPTED</td>
                                                                                                                    <td class="">systemTime: <b>${obj[4].id.sT}</b>s</td>
                                                                                                                </tr>`;
                                                                        
                                                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                                                            consoleOutputQuery.innerText = 'CORRUPTED';
                                                                        
                                                                                                            consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                                                        };
                                                                                                        
                                                                                                        consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                                                        consoleTableQueryTbody.innerHTML = tHTML;
                                                                        
                                                                                                        consoleH2.classList.replace('d-none', 'd-block');
                                                                        
                                                                                                        if(obj[4].pckt.vld) {
                                                                        
                                                                                                            dataHTML = `
                                                                                                                <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                                                                    <tbody class="">
                                                                                                                        <tr>
                                                                                                                            <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                                                            <td colspan="1" class="text-center">ip_nbr</td>
                                                                                                                        </tr>
                                                                                                                        </tr>
                                                                                                                        <tr>
                                                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0">Default route:</td>
                                                                                                                        </tr>`;
                                                                                                                    
                                                                                                            if(obj[0].rt.lt == "infinite") {
                                                                        
                                                                                                                dataHTML += `
                                                                                                                    <tr>
                                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt})</td>
                                                                                                                    </tr>`;
                                                                        
                                                                                                            } else {
                                                                        
                                                                                                                dataHTML += `
                                                                                                                    <tr>
                                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">-- ${obj[0].rt.df} (lifetime: ${obj[0].rt.lt} seconds)</td>
                                                                                                                    </tr>`;
                                                                                                            };
                                                                        
                                                                                                            let atLeast1routingLink = false;
                                                                        
                                                                                                            for(let destination = 0; destination < obj[2].rtLD.ls.length; destination++) {
                                                                        
                                                                                                                if(obj[2].rtLD.ls[destination] != null) {
                                                                        
                                                                                                                    atLeast1routingLink = true;
                                                                                                                };
                                                                                                            };
                                                                        
                                                                                                            if(atLeast1routingLink) {
                                                                        
                                                                                                                dataHTML += `
                                                                                                                    <tr>
                                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">Routing links (${obj[1].rtLS.totLs} in total):</td>
                                                                                                                    </tr>`;
                                                                        
                                                                                                                for(destination = 0; destination < obj[1].rtLS.ls.length; destination++) {
                                                                        
                                                                                                                    if(obj[2].rtLS.ls[destination] != null) {
                                                                        
                                                                                                                        dataHTML += `
                                                                                                                            <tr>
                                                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[1].rtLS.ls[destination].from} ${obj[1].rtLS.ls[destination].dodagRoot ? '(DODAG root)' : ''} to ${obj[2].rtLD.ls[destination].to} (lifetime: ${obj[2].rtLD.ls[destination].lf})</td>
                                                                                                                            </tr>`
                                                                                                                    };
                                                                                                                };
                                                                        
                                                                                                            } else {
                                                                        
                                                                                                                dataHTML += `
                                                                                                                    <tr>
                                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">No routing links</td>
                                                                                                                    </tr>`
                                                                                                            };
                                                                        
                                                                                                            let atLeast1routingEntry = false;
                                                                        
                                                                                                            for(let via = 0; via < obj[4].rtEVia.es.length; via++) {
                                                                        
                                                                                                                if(obj[4].rtEVia.es[via] != null) {
                                                                        
                                                                                                                    atLeast1routingEntry = true;
                                                                                                                };
                                                                                                            };
                                                                        
                                                                                                            if(atLeast1routingEntry) {
                                                                        
                                                                                                                dataHTML += `
                                                                                                                    <tr>
                                                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">Routing entries (${obj[4].rtEVia.totEs} in total):</td>
                                                                                                                    </tr>`;
                                                                        
                                                                                                                for(via = 0; via < obj[4].rtERt.es.length; via++) {
                                                                        
                                                                                                                    if(obj[4].rtEVia.es[via] != null) {
                                                                        
                                                                                                                        dataHTML += `
                                                                                                                            <tr>
                                                                                                                                <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- ${obj[3].rtERt.es[via].rt} via ${obj[4].rtEVia.es[via].via} (lifetime: ${obj[4].rtEVia.es[via].lf})} </td>
                                                                                                                            </tr>`               
                                                                                                                    };
                                                                                                                };
                                                                        
                                                                                                            } else {
                                                                        
                                                                                                                dataHTML += `
                                                                                                                        <tr>
                                                                                                                            <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">No routing entries</td>
                                                                                                                        </tr>`
                                                                                                            };
                                                                        
                                                                                                            dataHTML += `
                                                                                                                    </tbody>
                                                                                                                </table>`;
                                                                                                                    
                                                                                                            consoleData.innerHTML = dataHTML;
                                                                        
                                                                                                            storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                                                                                            storeButtonSave.addEventListener('click', () => {
                                                                                                        
                                                                                                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                                                            });
                                                                        
                                                                                                        } else {
                                                                        
                                                                                                            createErrorTable(obj[4]);
                                                                            
                                                                                                            tHTML += `
                                                                                                                <tr>
                                                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>17</b></td>
                                                                                                                    <td class="text-warning">ERROR</td>
                                                                                                                    <td class="text-warning">${obj[4].id.sT}</td>
                                                                                                                </tr>`;
                                                                        
                                                                                                            storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                                                                                            storeButtonSave.addEventListener('click', () => {
                                                                                                        
                                                                                                                cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                                                            });
                                                                                                        };
                                                                        
                                                                                                        legendDiv.classList.replace('d-none', 'd-show');
                                                                                                        constructLegend(`
                                                                                                            <br>
                                                                                                            <div class="container">
                                                                                                                <div class="row">
                                                                                                                    <div class="col border">
                                                                                                                        <pre> 
                                                                                                                            ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                                                        </pre>
                                                                                                                    </div>
                                                                                                                    <div class="col border">
                                                                                                                        <pre>  
                                                                                                                            ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)}  
                                                                                                                        </pre>
                                                                                                                    </div>
                                                                                                                    <div class="col border">
                                                                                                                        <pre>  
                                                                                                                            ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)}  
                                                                                                                        </pre>
                                                                                                                    </div>
                                                                                                                    <div class="col border">
                                                                                                                        <pre>  
                                                                                                                            ${JSON.stringify(elaborate(obj[3], checksum(decryptedText)), null, 2)}  
                                                                                                                        </pre>
                                                                                                                    </div>
                                                                                                                    <div class="col border">
                                                                                                                        <pre>  
                                                                                                                            ${JSON.stringify(elaborate(obj[4], checksum(decryptedText)), null, 2)}
                                                                                                                        </pre>
                                                                                                                    </div>
                                                                                                                </div>
                                                                                                            </div>`, undefined);
                                                                        
                                                                                                        consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                                                                                                    })
                                                                        
                                                                                                .catch((error) => {
                                                                        
                                                                                                    tHTML += `
                                                                                                        <tr>
                                                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>17</b></td>
                                                                                                            <td class="text-warning">INVALID</td>
                                                                                                            <td class="text-danger">${error}</td>
                                                                                                        </tr>`;
                                                                        
                                                                                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                                                    consoleTableQueryTbody.innerHTML = tHTML;
                                                                        
                                                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                                                                    consoleOutputQuery.innerText = 'FAIL';
                                                                        
                                                                                                    consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                                                        
                                                                                                    console.log(error);
                                                                                                });
                                                                        
                                                                                        }, 1000);
                                                                                    })
                                                        
                                                                                .catch((error) => {
                                                        
                                                                                    tHTML += `
                                                                                        <tr>
                                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>16</b></td>
                                                                                            <td class="text-warning">INVALID</td>
                                                                                            <td class="text-danger">${error}</td>
                                                                                        </tr>`;
                                                        
                                                                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                                    consoleTableQueryTbody.innerHTML = tHTML;
                                                        
                                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                                                    consoleOutputQuery.innerText = 'FAIL';
                                                        
                                                                                    consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                                        
                                                                                    console.log(error);
                                                                                });
                                                        
                                                                        }, 1000);
                                                                    })
                                        
                                                                .catch((error) => {
                                        
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>15</b></td>
                                                                            <td class="text-warning">INVALID</td>
                                                                            <td class="text-danger">${error}</td>
                                                                        </tr>`;
                                        
                                                                    consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                    consoleTableQueryTbody.innerHTML = tHTML;
                                        
                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                                    consoleOutputQuery.innerText = 'FAIL';
                                        
                                                                    consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                        
                                                                    console.log(error);
                                                                });
                                        
                                                        }, 1000);
                                                })
                    
                                            .catch((error) => {
                    
                                                tHTML += `
                                                    <tr>
                                                        <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>14</b></td>
                                                        <td class="text-warning">INVALID</td>
                                                        <td class="text-danger">${error}</td>
                                                    </tr>`;
                    
                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                consoleTableQueryTbody.innerHTML = tHTML;
                    
                                                consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                consoleOutputQuery.innerText = 'FAIL';
                    
                                                consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                    
                                                console.log(error);
                                            });
                    
                                    }, 1000);
                            })

                        .catch((error) => {

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>13</b></td>
                                    <td class="text-warning">INVALID</td>
                                    <td class="text-danger">${error}</td>
                                </tr>`;

                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                            consoleOutputQuery.innerText = 'FAIL';

                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                            console.log(error);
                        });

                }, 1000);
                
                break;

            case 'shell-rplstatus':

                obj = [];
                tHTML = '';
                dataHTML = '';

                window.setTimeout(() => {

                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/18`)

                        .then((response) => response.text())
                            .then((text) => {
                                
                                console.log(text);
                                let decodedText = atob(text);

                                console.log(decodedText);
                                console.log(consoleInputKey.value);

                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                
                                console.log(decryptedText);
                                
                                obj[0] = JSON.parse(decryptedText);
                                
                                if(checksum(decryptedText)) {

                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>18</b></td>
                                            <td class="text-success">INTACT</td>
                                            <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                        </tr>`;

                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                    consoleOutputQuery.innerText = 'OK';

                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                                } else {

                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>18</b></td>
                                            <td class="text-warning">CORRUPTED</td>
                                            <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                        </tr>`;

                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                    consoleOutputQuery.innerText = 'CORRUPTED';

                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                };
                                
                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                consoleTableQueryTbody.innerHTML = tHTML;

                                consoleH2.classList.replace('d-none', 'd-block');

                                if(obj[0].pckt.vld) {

                                    dataHTML = `
                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                            <tbody class="">
                                                <tr>
                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                    <td colspan="1" class="text-center">rpl-status</td>
                                                </tr>`;

                                    if(obj[0].rSt.rL == true) {

                                        if(obj[0].rSt.iId == 'none') {

                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Instance: none</td>
                                                </tr>`;

                                        } else {

                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Instance: ${obj[0].rSt.iId}</td>
                                                </tr>`;
                                            
                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- MOP: ${obj[0].rSt.mop}</td>
                                                </tr>`;

                                            
                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- OF: ${obj[0].rSt.of}</td>
                                                </tr>`;
                                            
                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Hop rank incerement: ${obj[0].rSt.hRkI}</td>
                                                </tr>`;
                                            
                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Default lifetime: ${obj[0].rSt.dLt} seconds</td>
                                                </tr>`;
                                            
                                            dataHTML += `
                                                <tr>
                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DTSN out: ${obj[0].rSt.dtsnO}</td>
                                                </tr>`;
                                        };
                                    };
                                            
                                    dataHTML += `
                                            </tbody>
                                        </table>`;
                                            
                                    consoleData.innerHTML = dataHTML;

                                } else {

                                    createErrorTable(obj[0]);
    
                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>18</b></td>
                                            <td class="text-warning">ERROR</td>
                                            <td class="text-warning">${obj[0].id.sT}</td>
                                        </tr>`;
                                };

                                legendDiv.classList.replace('d-none', 'd-show');
                                constructLegend(`
                                    <br>
                                    <div class="container">
                                        <div class="row">
                                            <div class="col border">
                                                <pre> 
                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                </pre>
                                            </div>
                                        </div>
                                    </div>`, undefined);

                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                window.setTimeout(() => {

                                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/19`)
                
                                        .then((response) => response.text())
                                            .then((text) => {
                                                
                                                console.log(text);
                                                let decodedText = atob(text);
                
                                                console.log(decodedText);
                                                console.log(consoleInputKey.value);
                
                                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                
                                                console.log(decryptedText);
                                                
                                                obj[1] = JSON.parse(decryptedText);
                                                
                                                if(checksum(decryptedText)) {
                
                                                    tHTML += `
                                                        <tr>
                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>19</b></td>
                                                            <td class="text-success">INTACT</td>
                                                            <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                        </tr>`;
                
                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                    consoleOutputQuery.innerText = 'OK';
                
                                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                
                                                } else {
                
                                                    tHTML += `
                                                        <tr>
                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>19</b></td>
                                                            <td class="text-warning">CORRUPTED</td>
                                                            <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                        </tr>`;
                
                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                    consoleOutputQuery.innerText = 'CORRUPTED';
                
                                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                };
                                                
                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                consoleTableQueryTbody.innerHTML = tHTML;
                
                                                consoleH2.classList.replace('d-none', 'd-block');
                
                                                if(obj[1].pckt.vld) {
                
                                                    dataHTML = `
                                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                            <tbody class="">
                                                                <tr>
                                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                    <td colspan="1" class="text-center">rpl-status</td>
                                                                </tr>`;
                
                                                    if(obj[1].rStDag.rL == true) {
                
                                                        if(obj[1].rStDag.iId == 'none') {
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Instance: none</td>
                                                                </tr>`;
                
                                                        } else {
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DAG ${obj[1].rStDag.dT}</td>
                                                                </tr>`;
                                                            
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DAG: ${obj[1].rStDag.dId}, version ${obj[1].rStDag.dVer}</td>
                                                                </tr>`;
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Prefix: ${obj[1].rStDag.dPf}/${obj[1].rStDag.dPfL}</td>
                                                                </tr>`;
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Instance: ${obj[0].rSt.iId}</td>
                                                                </tr>`;
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- MOP: ${obj[0].rSt.mop}</td>
                                                                </tr>`;
                
                                                            
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- OF: ${obj[0].rSt.of}</td>
                                                                </tr>`;
                                                            
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Hop rank incerement: ${obj[0].rSt.hRkI}</td>
                                                                </tr>`;
                                                            
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Default lifetime: ${obj[0].rSt.dLt} seconds</td>
                                                                </tr>`;
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- State: ${obj[1].rStDag.st}</td>
                                                                </tr>`;
                
                                                            if(obj[1].rStDag.pP != 'none') {
                
                                                                dataHTML += `
                                                                    <tr>
                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Prefered parent: ${obj[1].rStDag.pP} (last DTSN: ${obj[1].rStDag.lD})</td>
                                                                    </tr>`;
                
                                                            } else {
                
                                                                dataHTML += `
                                                                    <tr>
                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Prefered parent: none</td>
                                                                    </tr>`;
                                                            }
                                                            
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Rank: ${obj[1].rStDag.rk}</td>
                                                                </tr>`;
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Lowest rank: ${obj[1].rStDag.lRk} (${obj[1].rStDag.mRkI})</td>
                                                                </tr>`;
                                                            
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DTSN out: ${obj[0].rSt.dtsnO}</td>
                                                                </tr>`;
                
                                                            dataHTML += `
                                                                <tr>
                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DAO sequence: last sent ${obj[1].rStDag.dao.lS}, last acked ${obj[1].rStDag.dao.lA}</td>
                                                                </tr>`;
                                                        };
                                                    };
                
                                                    dataHTML += `
                                                            </tbody>
                                                        </table>`;
                                                            
                                                    consoleData.innerHTML = dataHTML;
                
                                                } else {
                
                                                    createErrorTable(obj[1]);
                    
                                                    tHTML += `
                                                        <tr>
                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>19</b></td>
                                                            <td class="text-warning">ERROR</td>
                                                            <td class="text-warning">${obj[1].id.sT}</td>
                                                        </tr>`;
                                                };
                
                                                legendDiv.classList.replace('d-none', 'd-show');
                                                constructLegend(`
                                                    <br>
                                                    <div class="container">
                                                        <div class="row">
                                                            <div class="col border">
                                                                <pre> 
                                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                </pre>
                                                            </div>
                                                            <div class="col border">
                                                                <pre> 
                                                                    ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)} 
                                                                </pre>
                                                            </div>
                                                        </div>
                                                    </div>`, undefined);
                
                                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                window.setTimeout(() => {

                                                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/20`)
                                
                                                        .then((response) => response.text())
                                                            .then((text) => {
                                                                
                                                                console.log(text);
                                                                let decodedText = atob(text);
                                
                                                                console.log(decodedText);
                                                                console.log(consoleInputKey.value);
                                
                                                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                
                                                                console.log(decryptedText);
                                                                
                                                                obj[2] = JSON.parse(decryptedText);
                                                                
                                                                if(checksum(decryptedText)) {
                                
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>20</b></td>
                                                                            <td class="text-success">INTACT</td>
                                                                            <td class="">systemTime: <b>${obj[2].id.sT}</b>s</td>
                                                                        </tr>`;
                                
                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                    consoleOutputQuery.innerText = 'OK';
                                
                                                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                
                                                                } else {
                                
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>20</b></td>
                                                                            <td class="text-warning">CORRUPTED</td>
                                                                            <td class="">systemTime: <b>${obj[2].id.sT}</b>s</td>
                                                                        </tr>`;
                                
                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                    consoleOutputQuery.innerText = 'CORRUPTED';
                                
                                                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                };
                                                                
                                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                consoleTableQueryTbody.innerHTML = tHTML;
                                
                                                                consoleH2.classList.replace('d-none', 'd-block');
                                
                                                                if(obj[2].pckt.vld) {
                                
                                                                    dataHTML = `
                                                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                            <tbody class="">
                                                                                <tr>
                                                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                    <td colspan="1" class="text-center">rpl-status</td>
                                                                                </tr>`;
                                
                                                                    if(obj[2].rStTt.rL == true) {
                                
                                                                        if(obj[2].rStTt.iId == 'none') {
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Instance: none</td>
                                                                                </tr>`;
                                
                                                                        } else {
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DAG ${obj[1].rStDag.dT}</td>
                                                                                </tr>`;
                                                                            
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DAG: ${obj[1].rStDag.dId}, version ${obj[1].rStDag.dVer}</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Prefix: ${obj[1].rStDag.dPf}/${obj[1].rStDag.dPfL}</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Instance: ${obj[0].rSt.iId}</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- MOP: ${obj[0].rSt.mop}</td>
                                                                                </tr>`;
                                
                                                                            
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- OF: ${obj[0].rSt.of}</td>
                                                                                </tr>`;
                                                                            
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Hop rank incerement: ${obj[0].rSt.hRkI}</td>
                                                                                </tr>`;
                                                                            
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Default lifetime: ${obj[0].rSt.dLt} seconds</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- State: ${obj[1].rStDag.st}</td>
                                                                                </tr>`;
                                
                                                                            if(obj[1].rStDag.pP != 'none') {
                                
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Prefered parent: ${obj[1].rStDag.pP} (last DTSN: ${obj[1].rStDag.lD})</td>
                                                                                    </tr>`;
                                
                                                                            } else {
                                
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Prefered parent: none</td>
                                                                                    </tr>`;
                                                                            }
                                                                            
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Rank: ${obj[1].rStDag.rk}</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Lowest rank: ${obj[1].rStDag.lRk} (${obj[1].rStDag.mRkI})</td>
                                                                                </tr>`;
                                                                            
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DTSN out: ${obj[0].rSt.dtsnO}</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- DAO sequence: last sent ${obj[1].rStDag.dao.lS}, last acked ${obj[1].rStDag.dao.lA}</td>
                                                                                </tr>`;
                                
                                                                            dataHTML += `
                                                                                <tr>
                                                                                    <td colspan="2" style="background-color: rgb(0, 0, 0);" class="text-light border-top-0 border-bottom-0">-- Trickle timer: current ${obj[2].rStTt.cur}, min ${obj[2].rStTt.min}, max ${obj[2].rStTt.max}, redundancy ${obj[2].rStTt.red} </td>
                                                                                </tr>`;
                                                                        };
                                                                    };
                                
                                                                    dataHTML += `
                                                                            </tbody>
                                                                        </table>`;
                                                                            
                                                                    consoleData.innerHTML = dataHTML;
                                
                                                                    storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                                                    storeButtonSave.addEventListener('click', () => {
                                                                
                                                                        cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                    });
                                
                                                                } else {
                                
                                                                    createErrorTable(obj[2]);
                                    
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>20</b></td>
                                                                            <td class="text-warning">ERROR</td>
                                                                            <td class="text-warning">${obj[2].id.sT}</td>
                                                                        </tr>`;
                                
                                                                    storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                                                    storeButtonSave.addEventListener('click', () => {
                                                                
                                                                        cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                    });
                                                                };
                                
                                                                legendDiv.classList.replace('d-none', 'd-show');
                                                                constructLegend(`
                                                                    <br>
                                                                    <div class="container">
                                                                        <div class="row">
                                                                            <div class="col border">
                                                                                <pre> 
                                                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                </pre>
                                                                            </div>
                                                                            <div class="col border">
                                                                                <pre> 
                                                                                    ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)} 
                                                                                </pre>
                                                                            </div>
                                                                            <div class="col border">
                                                                                <pre> 
                                                                                    ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)} 
                                                                                </pre>
                                                                            </div>
                                                                        </div>
                                                                    </div>`, undefined);
                                
                                                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                                                            })
                                
                                                        .catch((error) => {
                                
                                                            tHTML += `
                                                                <tr>
                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>20</b></td>
                                                                    <td class="text-warning">INVALID</td>
                                                                    <td class="text-danger">${error}</td>
                                                                </tr>`;
                                
                                                            consoleTableQuery.classList.replace('d-none', 'd-block');
                                                            consoleTableQueryTbody.innerHTML = tHTML;
                                
                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                            consoleOutputQuery.innerText = 'FAIL';
                                
                                                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                
                                                            console.log(error);
                                                        });
                                                
                                                }, 1000);
                                            })
                
                                        .catch((error) => {
                
                                            tHTML += `
                                                <tr>
                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>19</b></td>
                                                    <td class="text-warning">INVALID</td>
                                                    <td class="text-danger">${error}</td>
                                                </tr>`;
                
                                            consoleTableQuery.classList.replace('d-none', 'd-block');
                                            consoleTableQueryTbody.innerHTML = tHTML;
                
                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                            consoleOutputQuery.innerText = 'FAIL';
                
                                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                
                                            console.log(error);
                                        });
                
                                }, 1000);
                            })

                        .catch((error) => {

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>18</b></td>
                                    <td class="text-warning">INVALID</td>
                                    <td class="text-danger">${error}</td>
                                </tr>`;

                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                            consoleOutputQuery.innerText = 'FAIL';

                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                            console.log(error);
                        });

                }, 1000);

                break;

            case 'shell-rplnbr':

                obj = [];
                tHTML = '';
                dataHTML = '';

                window.setTimeout(() => {

                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/21`)

                        .then((response) => response.text())
                            .then((text) => {
                                
                                console.log(text);
                                let decodedText = atob(text);

                                console.log(decodedText);
                                console.log(consoleInputKey.value);

                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                
                                console.log(decryptedText);
                                
                                obj[0] = JSON.parse(decryptedText);
                                
                                if(checksum(decryptedText)) {

                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>21</b></td>
                                            <td class="text-success">INTACT</td>
                                            <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                        </tr>`;

                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                    consoleOutputQuery.innerText = 'OK';

                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');

                                } else {

                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>21</b></td>
                                            <td class="text-warning">CORRUPTED</td>
                                            <td class="">systemTime: <b>${obj[0].id.sT}</b>s</td>
                                        </tr>`;

                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                    consoleOutputQuery.innerText = 'CORRUPTED';

                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');

                                }
                                
                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                consoleTableQueryTbody.innerHTML = tHTML;

                                consoleH2.classList.replace('d-none', 'd-block');

                                if(obj[0].pckt.vld) {

                                    dataHTML = `
                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                            <tbody class="">
                                                <tr>
                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                    <td colspan="11" class="text-center">rpl-nbr</td>
                                                </tr`;

                                    if(obj[0].rN.rL == true) {

                                        if(obj[0].rN.iId != 'none') {
                                            
                                            if(obj[0].rN.c == 0) {

                                                dataHTML += `
                                                    <tr>
                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors: none</td>
                                                    </tr>`;
                                            
                                            } else {
        
                                                dataHTML += `
                                                    <tr>
                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors:</td>
                                                    </tr>`;
        
                                                for (let nbr = 0; nbr < obj[0].rN.c; nbr++) {
        
                                                    if(obj[0].rN.ns[nbr] != null) {

                                                        dataHTML += `
                                                            <tr>
                                                                <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">${obj[0].rN.ns[nbr].ad}</td>
                                                            </tr>`;
                                                    };
                                                };
                                            };
                                        };
                                    };

                                    dataHTML += `
                                            </tbody>
                                        </table>`;
                                            
                                    consoleData.innerHTML = dataHTML;

                                } else {

                                    createErrorTable(obj[0]);
    
                                    tHTML += `
                                        <tr>
                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>21</b></td>
                                            <td class="text-warning">ERROR</td>
                                            <td class="text-warning">${obj[0].id.sT}</td>
                                        </tr>`;
                                };

                                legendDiv.classList.replace('d-none', 'd-show');
                                constructLegend(`
                                <br>
                                <div class="container">
                                    <div class="row">
                                        <div class="col border">
                                            <pre> 
                                                ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                            </pre>
                                        </div>
                                    </div>
                                </div>`, undefined);

                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                window.setTimeout(() => {

                                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/22`)
                
                                        .then((response) => response.text())
                                            .then((text) => {
                                                
                                                console.log(text);
                                                let decodedText = atob(text);
                
                                                console.log(decodedText);
                                                console.log(consoleInputKey.value);
                
                                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                
                                                console.log(decryptedText);
                                                
                                                obj[1] = JSON.parse(decryptedText);
                                                
                                                if(checksum(decryptedText)) {
                
                                                    tHTML += `
                                                        <tr>
                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>22</b></td>
                                                            <td class="text-success">INTACT</td>
                                                            <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                        </tr>`;
                
                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                    consoleOutputQuery.innerText = 'OK';
                
                                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                
                                                } else {
                
                                                    tHTML += `
                                                        <tr>
                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>22</b></td>
                                                            <td class="text-warning">CORRUPTED</td>
                                                            <td class="">systemTime: <b>${obj[1].id.sT}</b>s</td>
                                                        </tr>`;
                
                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                    consoleOutputQuery.innerText = 'CORRUPTED';
                
                                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                
                                                }
                                                
                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                consoleTableQueryTbody.innerHTML = tHTML;
                
                                                consoleH2.classList.replace('d-none', 'd-block');
                
                                                if(obj[1].pckt.vld) {
                
                                                    dataHTML = `
                                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                            <tbody class="">
                                                                <tr>
                                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                    <td colspan="11" class="text-center">rpl-nbr</td>
                                                                </tr`;
                
                                                    if(obj[1].rNR.rL == true) {
                
                                                        if(obj[1].rNR.iId != 'none') {
                                                            
                                                            if(obj[1].rNR.c == 0) {
                
                                                                dataHTML += `
                                                                    <tr>
                                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors: none</td>
                                                                    </tr>`;
                                                            
                                                            } else {
                        
                                                                dataHTML += `
                                                                    <tr>
                                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors:</td>
                                                                    </tr>`;
                        
                                                                for (let nbr = 0; nbr < obj[1].rNR.c; nbr++) {
                        
                                                                    if(obj[1].rNR.ns[nbr] != null) {
                
                                                                        dataHTML += `
                                                                            <tr>
                                                                                <td colspan="8" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-right-0">${obj[0].rN.ns[nbr].ad}</td>
                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].rk},</td>
                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].lM}</td>
                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">=></td>
                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0">${obj[1].rNR.ns[nbr].rkN}</td>
                                                                            </tr>`;
                                                                    };
                                                                };
                                                            };
                                                        };
                                                    };
                
                                                    dataHTML += `
                                                            </tbody>
                                                        </table>`;
                                                            
                                                    consoleData.innerHTML = dataHTML;
                
                                                } else {
                
                                                    createErrorTable(obj[1]);
                    
                                                    tHTML += `
                                                        <tr>
                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>22</b></td>
                                                            <td class="text-warning">ERROR</td>
                                                            <td class="text-warning">${obj[1].id.sT}</td>
                                                        </tr>`;
                                                };
                
                                                legendDiv.classList.replace('d-none', 'd-show');
                                                constructLegend(`
                                                    <br>
                                                    <div class="container">
                                                        <div class="row">
                                                            <div class="col border">
                                                                <pre> 
                                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                </pre>
                                                            </div>
                                                            <div class="col border">
                                                                <pre> 
                                                                    ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)} 
                                                                </pre>
                                                            </div>
                                                        </div>
                                                    </div>`, undefined);
                
                                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                window.setTimeout(() => {

                                                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/23`)
                                
                                                        .then((response) => response.text())
                                                            .then((text) => {
                                                                
                                                                console.log(text);
                                                                let decodedText = atob(text);
                                
                                                                console.log(decodedText);
                                                                console.log(consoleInputKey.value);
                                
                                                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                
                                                                console.log(decryptedText);
                                                                
                                                                obj[2] = JSON.parse(decryptedText);
                                                                
                                                                if(checksum(decryptedText)) {
                                
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>23</b></td>
                                                                            <td class="text-success">INTACT</td>
                                                                            <td class="">systemTime: <b>${obj[2].id.sT}</b>s</td>
                                                                        </tr>`;
                                
                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                    consoleOutputQuery.innerText = 'OK';
                                
                                                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                
                                                                } else {
                                
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>23</b></td>
                                                                            <td class="text-warning">CORRUPTED</td>
                                                                            <td class="">systemTime: <b>${obj[2].id.sT}</b>s</td>
                                                                        </tr>`;
                                
                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                    consoleOutputQuery.innerText = 'CORRUPTED';
                                
                                                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                };
                                                                
                                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                consoleTableQueryTbody.innerHTML = tHTML;
                                
                                                                consoleH2.classList.replace('d-none', 'd-block');
                                
                                                                if(obj[2].pckt.vld) {
                                
                                                                    dataHTML = `
                                                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                            <tbody class="">
                                                                                <tr>
                                                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                    <td colspan="11" class="text-center">rpl-nbr</td>
                                                                                </tr>`;
                                
                                                                    if(obj[2].rNV.rL == true) {
                                
                                                                        if(obj[2].rNV.iId != 'none') {
                                                                            
                                                                            if(obj[2].rNV.c == 0) {
                                
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors: none</td>
                                                                                    </tr>`;
                                                                            
                                                                            } else {
                                        
                                                                                dataHTML += `
                                                                                    <tr>
                                                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors:</td>
                                                                                    </tr>`;
                                        
                                                                                for (let nbr = 0; nbr < obj[2].rNV.c; nbr++) {
                                        
                                                                                    if(obj[2].rNV.ns[nbr] != null) {
                                
                                                                                        dataHTML += `
                                                                                            <tr>
                                                                                                <td colspan="5" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-right-0">${obj[0].rN.ns[nbr].ad}</td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].rk},</td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].lM}</td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">=></td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].rkN}</td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">--</td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[2].rNV.ns[nbr].fr}</td>
                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">`;
                                
                                                                                        if(obj[2].rNV.ns[nbr].r == true) {
                                
                                                                                            dataHTML += `r `;
                                
                                                                                        } else {
                                
                                                                                            dataHTML += `- `;
                                                                                        };
                                
                                                                                        if(obj[2].rNV.ns[nbr].b == true) {
                                
                                                                                            dataHTML += `b `;
                                
                                                                                        } else {
                                
                                                                                            dataHTML += `- `;
                                                                                        };
                                
                                                                                        if(obj[2].rNV.ns[nbr].a == true) {
                                
                                                                                            dataHTML += `a `;
                                
                                                                                        } else {
                                
                                                                                            dataHTML += `- `;
                                                                                        };
                                
                                                                                        if(obj[2].rNV.ns[nbr].f == true) {
                                
                                                                                            dataHTML += `f `;
                                
                                                                                        } else {
                                
                                                                                            dataHTML += `- `;
                                                                                        };
                                
                                                                                        if(obj[2].rNV.ns[nbr].p == true) {
                                
                                                                                            dataHTML += `p `;
                                
                                                                                        } else {
                                
                                                                                            dataHTML += `- `;
                                                                                        };
                                
                                                                                        dataHTML += `
                                                                                                </td>
                                                                                            </tr>`;
                                                                                    };
                                                                                };
                                                                            };
                                                                        };
                                                                    };
                                
                                                                    dataHTML += `
                                                                            </tbody>
                                                                        </table>`;
                                                                            
                                                                    consoleData.innerHTML = dataHTML;
                                
                                                                } else {
                                
                                                                    createErrorTable(obj[2]);
                                    
                                                                    tHTML += `
                                                                        <tr>
                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>23</b></td>
                                                                            <td class="text-warning">ERROR</td>
                                                                            <td class="text-warning">${obj[2].id.sT}</td>
                                                                        </tr>`;
                                                                };
                                
                                                                legendDiv.classList.replace('d-none', 'd-show');
                                                                constructLegend(`
                                                                    <br>
                                                                    <div class="container">
                                                                        <div class="row">
                                                                            <div class="col border">
                                                                                <pre> 
                                                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                </pre>
                                                                            </div>
                                                                            <div class="col border">
                                                                                <pre> 
                                                                                    ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)} 
                                                                                </pre>
                                                                            </div>
                                                                            <div class="col border">
                                                                                <pre> 
                                                                                    ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)} 
                                                                                </pre>
                                                                            </div>
                                                                        </div>
                                                                    </div>`, undefined);
                                
                                                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                                                                window.setTimeout(() => {

                                                                    fetch(`http://[${nodesAddr[consoleSelectNode.value]}]/24`)
                                                
                                                                        .then((response) => response.text())
                                                                            .then((text) => {
                                                                                
                                                                                console.log(text);
                                                                                let decodedText = atob(text);
                                                
                                                                                console.log(decodedText);
                                                                                console.log(consoleInputKey.value);
                                                
                                                                                let decryptedText = oarCrypt(decodedText, consoleInputKey.value);
                                                                
                                                                                console.log(decryptedText);
                                                                                
                                                                                obj[3] = JSON.parse(decryptedText);
                                                                                
                                                                                if(checksum(decryptedText)) {
                                                
                                                                                    tHTML += `
                                                                                        <tr>
                                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>24</b></td>
                                                                                            <td class="text-success">INTACT</td>
                                                                                            <td class="">systemTime: <b>${obj[3].id.sT}</b>s</td>
                                                                                        </tr>`;
                                                
                                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                    consoleOutputQuery.classList.remove('bg-danger', 'bg-warning'); consoleOutputQuery.classList.add('bg-success');
                                                                                    consoleOutputQuery.innerText = 'OK';
                                                
                                                                                    consoleDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-success');
                                                
                                                                                } else {
                                                
                                                                                    tHTML += `
                                                                                        <tr>
                                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>24</b></td>
                                                                                            <td class="text-warning">CORRUPTED</td>
                                                                                            <td class="">systemTime: <b>${obj[3].id.sT}</b>s</td>
                                                                                        </tr>`;
                                                
                                                                                    consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                                    consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-warning');
                                                                                    consoleOutputQuery.innerText = 'CORRUPTED';
                                                
                                                                                    consoleDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-warning');
                                                                                };
                                                                                
                                                                                consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                                consoleTableQueryTbody.innerHTML = tHTML;
                                                
                                                                                consoleH2.classList.replace('d-none', 'd-block');
                                                
                                                                                if(obj[3].pckt.vld) {
                                                
                                                                                    dataHTML = `
                                                                                        <table class="table table-sm table-striped table-bordered bg-light" id="legend-table-system">
                                                                                            <tbody class="">
                                                                                                <tr>
                                                                                                    <td colspan="1" class="text-center text-light bg-secondary">command:</td>
                                                                                                    <td colspan="11" class="text-center">rpl-nbr</td>
                                                                                                </tr>`;
                                                
                                                                                    if(obj[3].rNP.rL == true) {
                                                
                                                                                        if(obj[3].rNP.iId != 'none') {
                                                                                            
                                                                                            if(obj[3].rNP.c == 0) {
                                                
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors: none</td>
                                                                                                    </tr>`;
                                                                                            
                                                                                            } else {
                                                        
                                                                                                dataHTML += `
                                                                                                    <tr>
                                                                                                        <td colspan="12" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0">RPL neighbors:</td>
                                                                                                    </tr>`;
                                                        
                                                                                                for (let nbr = 0; nbr < obj[3].rNP.c; nbr++) {
                                                        
                                                                                                    if(obj[3].rNP.ns[nbr] != null) {
                                                
                                                                                                        dataHTML += `
                                                                                                            <tr>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-right-0">${obj[0].rN.ns[nbr].ad}</td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].rk},</td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].lM}</td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">=></td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[1].rNR.ns[nbr].rkN}</td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">--</td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">${obj[2].rNV.ns[nbr].fr}</td>
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">`;
                                                
                                                                                                        if(obj[2].rNV.ns[nbr].r == true) {
                                                
                                                                                                            dataHTML += `r `;
                                                
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `- `;
                                                                                                        };
                                                
                                                                                                        if(obj[2].rNV.ns[nbr].b == true) {
                                                
                                                                                                            dataHTML += `b `;
                                                
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `- `;
                                                                                                        };
                                                
                                                                                                        if(obj[2].rNV.ns[nbr].a == true) {
                                                
                                                                                                            dataHTML += `a `;
                                                
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `- `;
                                                                                                        };
                                                
                                                                                                        if(obj[2].rNV.ns[nbr].f == true) {
                                                
                                                                                                            dataHTML += `f `;
                                                
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `- `;
                                                                                                        };
                                                
                                                                                                        if(obj[2].rNV.ns[nbr].p == true) {
                                                
                                                                                                            dataHTML += `p `;
                                                
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `- `;
                                                                                                        };
                                                
                                                                                                        dataHTML += `
                                                                                                                </td>`;
                                                
                                                                                                        dataHTML += `<td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">(</td>`;
                                                
                                                                                                        if(obj[3].rNP.ns[nbr].lTx > 0) {
                                                
                                                                                                            dataHTML += `
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">last tx ${obj[3].rNP.ns[nbr].lTx} min ago</td>`;
                                                                                                        
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">no tx</td>`;
                                                                                                        }
                                                
                                                                                                        if(obj[3].rNP.ns[nbr].bS > 0) {
                                                
                                                                                                            dataHTML += `
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">, better since ${obj[3].rNP.ns[nbr].bS} min</td>`;
                                                                                                        
                                                                                                        } else {
                                                
                                                                                                            dataHTML += `
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0"></td>`;
                                                                                                        }
                                                
                                                                                                        dataHTML += `
                                                                                                                <td colspan="1" style="background-color: rgb(0, 0, 0);" class="text-light border-bottom-0 border-top-0 border-left-0 border-right-0">)</td>`;
                                                                                                        
                                                                                                        dataHTML += `
                                                                                                            </tr>`;
                                                                                                    };
                                                                                                };
                                                                                            };
                                                                                        };
                                                                                    };
                                                
                                                                                    dataHTML += `
                                                                                            </tbody>
                                                                                        </table>`;
                                                                                            
                                                                                    consoleData.innerHTML = dataHTML;
                                                
                                                                                    storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-warning'); storeButtonSave.classList.add('btn-outline-primary');
                                                                                    storeButtonSave.addEventListener('click', () => {
                                                                                
                                                                                        cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                                    });
                                                
                                                                                } else {
                                                
                                                                                    createErrorTable(obj[3]);
                                                    
                                                                                    tHTML += `
                                                                                        <tr>
                                                                                            <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>24</b></td>
                                                                                            <td class="text-warning">ERROR</td>
                                                                                            <td class="text-warning">${obj[3].id.sT}</td>
                                                                                        </tr>`;
                                                
                                                                                    storeButtonSave.classList.remove('d-none', 'btn-muted', 'btn-primary'); storeButtonSave.classList.add('btn-outline-warning');
                                                                                    storeButtonSave.addEventListener('click', () => {
                                                                            
                                                                                        cargoSave(nodesAddr[consoleSelectNode.value], obj);
                                                                                    });
                                                                                };
                                                
                                                                                legendDiv.classList.replace('d-none', 'd-show');
                                                                                constructLegend(`
                                                                                    <br>
                                                                                    <div class="container">
                                                                                        <div class="row">
                                                                                            <div class="col border">
                                                                                                <pre> 
                                                                                                    ${JSON.stringify(elaborate(obj[0], checksum(decryptedText)), null, 2)} 
                                                                                                </pre>
                                                                                            </div>
                                                                                            <div class="col border">
                                                                                                <pre> 
                                                                                                    ${JSON.stringify(elaborate(obj[1], checksum(decryptedText)), null, 2)} 
                                                                                                </pre>
                                                                                            </div>
                                                                                            <div class="col border">
                                                                                                <pre> 
                                                                                                    ${JSON.stringify(elaborate(obj[2], checksum(decryptedText)), null, 2)} 
                                                                                                </pre>
                                                                                            </div>
                                                                                            <div class="col border">
                                                                                                <pre> 
                                                                                                    ${JSON.stringify(elaborate(obj[3], checksum(decryptedText)), null, 2)} 
                                                                                                </pre>
                                                                                            </div>
                                                                                        </div>
                                                                                    </div>`, undefined);
                                                
                                                                                consoleButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                                                                            })
                                                
                                                                        .catch((error) => {
                                                
                                                                            tHTML += `
                                                                                <tr>
                                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>24</b></td>
                                                                                    <td class="text-warning">INVALID</td>
                                                                                    <td class="text-danger">${error}</td>
                                                                                </tr>`;
                                                
                                                                            consoleTableQuery.classList.replace('d-none', 'd-block');
                                                                            consoleTableQueryTbody.innerHTML = tHTML;
                                                
                                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                                            consoleOutputQuery.innerText = 'FAIL';
                                                
                                                                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                                
                                                                            console.log(error);
                                                                        });
                                                
                                                                }, 1000);
                                                            })
                                
                                                        .catch((error) => {
                                
                                                            tHTML += `
                                                                <tr>
                                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>23</b></td>
                                                                    <td class="text-warning">INVALID</td>
                                                                    <td class="text-danger">${error}</td>
                                                                </tr>`;
                                
                                                            consoleTableQuery.classList.replace('d-none', 'd-block');
                                                            consoleTableQueryTbody.innerHTML = tHTML;
                                
                                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                                            consoleOutputQuery.innerText = 'FAIL';
                                
                                                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                                
                                                            console.log(error);
                                                        });
                                
                                                }, 1000);
                                            })
                
                                        .catch((error) => {
                
                                            tHTML += `
                                                <tr>
                                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>22</b></td>
                                                    <td class="text-warning">INVALID</td>
                                                    <td class="text-danger">${error}</td>
                                                </tr>`;
                
                                            consoleTableQuery.classList.replace('d-none', 'd-block');
                                            consoleTableQueryTbody.innerHTML = tHTML;
                
                                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                                            consoleOutputQuery.innerText = 'FAIL';
                
                                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');
                
                                            console.log(error);
                                        });
                
                                }, 1000);
                            })

                        .catch((error) => {

                            tHTML += `
                                <tr>
                                    <td>http://[${nodesAddr[consoleSelectNode.value]}]/<b>21</b></td>
                                    <td class="text-warning">INVALID</td>
                                    <td class="text-danger">${error}</td>
                                </tr>`;

                            consoleTableQuery.classList.replace('d-none', 'd-block');
                            consoleTableQueryTbody.innerHTML = tHTML;

                            consoleOutputQuery.classList.replace('d-none', 'd-block');
                            consoleOutputQuery.classList.remove('bg-warning', 'bg-success'); consoleOutputQuery.classList.add('bg-danger');
                            consoleOutputQuery.innerText = 'FAIL';

                            consoleDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); consoleDiv.classList.add('border-danger');

                            console.log(error);
                        });

                }, 1000);

                break;
        };
        
        console.log(consoleSelectNode.value);
        console.log(consoleSelectQuery.value);
    })
};

function activateStore(nodesAddr) {

    storeDiv.classList.replace('border-secondary', 'border-info');
    storeH1.classList.replace('text-secondary', 'text-light');

    
};


databaseButton.addEventListener('click', () => {

    databaseButton.classList.add('d-none');
    databaseInputGroup.classList.remove('d-none');

    runDatabase();
});


function runDatabase() {

    databaseButtonGet.addEventListener('click', () => {

        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/${databaseSelect.value}`)
    
            .then(res => res.json())
            .then(data => {
                    
                console.log(data);
                
                databaseOutput.classList.replace('d-none', 'd-block');
                databaseOutput.classList.remove('bg-danger', 'bg-warning'); databaseOutput.classList.add('bg-success');
                databaseOutput.innerText = 'OK';
    
                databaseDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); databaseDiv.classList.add('border-success');
                
                databaseH2Response.classList.replace('d-none', 'd-block');
                databaseResponse.innerHTML = `<pre class="text-light">${JSON.stringify(data, null, 2)}</pre>`;
    
                databaseButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                
                controlRun();
    
                databaseButtonDrop.classList.replace('d-none', 'd-block');
                databaseButtonDrop.addEventListener('click', () => {
    
                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/${databaseSelect.value}`, {
                        method: 'DELETE'
                    })
                        .then(res => res.json())
                        .then(data => {
                            
                            console.log(data);
                            
                            if(data.status == 'error') {
    
                                databaseOutput.classList.remove('bg-warning', 'bg-success'); databaseOutput.classList.add('bg-danger');
                                databaseOutput.innerText = 'already null';
    
                                databaseDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary', 'border-info'); databaseDiv.classList.add('border-danger');
    
                            } else {
                                
                                databaseOutput.classList.remove('bg-danger', 'bg-success'); databaseOutput.classList.add('bg-warning');
                                databaseOutput.innerText = 'dropped';
    
                                databaseDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); databaseDiv.classList.add('border-warning');
    
                            }
                            
                            databaseResponse.innerHTML = '';
            
                            databaseButtonDrop.classList.replace('d-block', 'd-none');
    
                        })
                        
                        // .catch(err => {
    
                        //     console.log(err);
    
                        //     databaseOutput.classList.remove('bg-warning', 'bg-success'); databaseOutput.classList.add('bg-danger');
                        //     databaseOutput.innerText = err;
    
                        //     databaseDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary'); databaseDiv.classList.add('border-danger');
                        // })
                });
            })
            .catch(err => {
    
                console.log(err);
    
                databaseOutput.classList.replace('d-none', 'd-block');
                databaseOutput.classList.remove('bg-danger', 'bg-success'); databaseOutput.classList.add('bg-danger');
                databaseOutput.innerText = err;
    
                databaseDiv.classList.remove('border-warning', 'border-success', 'border-primary', 'border-secondary', 'border-info'); databaseDiv.classList.add('border-danger');
            })
    });
};




































































// {"pckt":{"vld":true,"err":null},"rcrd":2,"ndx":0,"id":{"sT":7886,"adr":"0012.4b00.0f82.da03","cd":"BLUE"},"sys":{"cV":"Contiki-NG-release/v4.2-335-ga95cf54ef-dirty","rt":"RPL Lite","net":"sicslowpan","pId":"0xabcd","mac":{"t":"CSMA","tDhS":null,"dCh":26},"nId":55811,"tIad":"fe80::212:4b00:f82:da03"},"hash":392888623}

function crud() {

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    controlCrudButtonPost.addEventListener('click', () => {

        fetch(`http://${controlCrudInputAddressPost.value}:${controlCrudInputPortPost.value}/api/cargo/`,{
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: controlCrudInputBodyPost.value
        })
        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.status == 'ok') {
                
                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputCreate.classList.replace('d-none', 'd-block');
                controlCrudOutputCreate.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputCreate.classList.add('bg-success')
                controlCrudOutputCreate.innerText = 'ok'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            } else {
                
                controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');

                controlCrudOutputCreate.classList.replace('d-none', 'd-block');
                controlCrudOutputCreate.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputCreate.classList.add('bg-warning')
                controlCrudOutputCreate.innerText = 'error'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputCreate.classList.replace('d-none', 'd-block');
            controlCrudOutputCreate.classList.remove('bg-warning', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputCreate.classList.add('bg-danger')
            controlCrudOutputCreate.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // READ /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    controlCrudButtonGetPath.addEventListener('click', () => {

        console.log(`http://${controlCrudInputAddressGetPath.value}:${controlCrudInputPortGetPath.value}/api/${controlCrudInputPath.value}`);

        fetch(`http://${controlCrudInputAddressGetPath.value}:${controlCrudInputPortGetPath.value}/api/${controlCrudInputPath.value}`)

        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.goto != null) {

                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputRead.classList.replace('d-none', 'd-block');
                controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-info')
                controlCrudOutputRead.innerText = 'goto'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-info">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            
            } else {

                if(data.status == 'ok') {
                
                    controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                    
                    controlCrudOutputRead.classList.replace('d-none', 'd-block');
                    controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-success')
                    controlCrudOutputRead.innerText = 'ok'

                    controlCrudDivResponse.classList.replace('d-none', 'd-block');
                    controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                    controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                    controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
    
                } else {
                    
                    controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');
    
                    controlCrudOutputRead.classList.replace('d-none', 'd-block');
                    controlCrudOutputRead.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-warning')
                    controlCrudOutputRead.innerText = 'error'

                    controlCrudDivResponse.classList.replace('d-none', 'd-block');
                    controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                    controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                    controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                };
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputRead.classList.replace('d-none', 'd-block');
            controlCrudOutputRead.classList.remove('bg-warning', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-danger')
            controlCrudOutputRead.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });

    // ----------------------------------------------------------------------------------------------------------------------------------------------

    controlCrudButtonGetOne.addEventListener('click', () => {

        console.log(`http://${controlCrudInputAddressGetOne.value}:${controlCrudInputPortGetOne.value}/api/cargo/${controlCrudSelectGetOne.value}/${controlCrudInputIdGetOne.value}`);

        fetch(`http://${controlCrudInputAddressGetOne.value}:${controlCrudInputPortGetOne.value}/api/cargo/${controlCrudSelectGetOne.value}/${controlCrudInputIdGetOne.value}`)

        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.goto != null) {

                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputRead.classList.replace('d-none', 'd-block');
                controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-info')
                controlCrudOutputRead.innerText = 'goto'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-info">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            
            } else {

                if(data.status == 'ok') {
                
                    controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                    
                    controlCrudOutputRead.classList.replace('d-none', 'd-block');
                    controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-success')
                    controlCrudOutputRead.innerText = 'ok'

                    controlCrudDivResponse.classList.replace('d-none', 'd-block');
                    controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                    controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                    controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
    
                } else {
                    
                    controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');
    
                    controlCrudOutputRead.classList.replace('d-none', 'd-block');
                    controlCrudOutputRead.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-warning')
                    controlCrudOutputRead.innerText = 'error'

                    controlCrudDivResponse.classList.replace('d-none', 'd-block');
                    controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                    controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                    controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                };
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputRead.classList.replace('d-none', 'd-block');
            controlCrudOutputRead.classList.remove('bg-warning', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-danger')
            controlCrudOutputRead.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });

    // ----------------------------------------------------------------------------------------------------------------------------------------------

    controlCrudButtonGetAll.addEventListener('click', () => {

        console.log(`http://${controlCrudInputAddressGetAll.value}:${controlCrudInputPortGetAll.value}/api/cargo/${controlCrudSelectGetAll.value}/`);

        fetch(`http://${controlCrudInputAddressGetAll.value}:${controlCrudInputPortGetAll.value}/api/cargo/${controlCrudSelectGetAll.value}/`)

        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.goto != null) {

                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputRead.classList.replace('d-none', 'd-block');
                controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-info')
                controlCrudOutputRead.innerText = 'goto'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-info">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            
            } else {

                if(data.status == 'ok') {

                    if(data.data.length == 0) {

                        controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-success', 'border-info'); controlDiv.classList.add('border-secondary');
                        
                        controlCrudOutputRead.classList.replace('d-none', 'd-block');
                        controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-success'); controlCrudOutputRead.classList.add('bg-secondary')
                        controlCrudOutputRead.innerText = 'empty'

                        controlCrudDivResponse.classList.replace('d-none', 'd-block');
                        controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                        controlCrudDivResponseContent.innerHTML = `<pre class="text-secondary">${JSON.stringify(data, null, 2)}</pre>`;

                        controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

                    } else {

                        controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                        
                        controlCrudOutputRead.classList.replace('d-none', 'd-block');
                        controlCrudOutputRead.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-success')
                        controlCrudOutputRead.innerText = 'ok'

                        controlCrudDivResponse.classList.replace('d-none', 'd-block');
                        controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                        controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                        controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                    };
                
                    
    
                } else {
                    
                    controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');
    
                    controlCrudOutputRead.classList.replace('d-none', 'd-block');
                    controlCrudOutputRead.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputRead.classList.add('bg-warning')
                    controlCrudOutputRead.innerText = 'error'

                    controlCrudDivResponse.classList.replace('d-none', 'd-block');
                    controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                    controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                    controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
                };
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputRead.classList.replace('d-none', 'd-block');
            controlCrudOutputRead.classList.remove('bg-warning', 'bg-success', 'bg-info'); controlCrudOutputRead.classList.add('bg-danger')
            controlCrudOutputRead.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // UPDATE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    controlCrudButtonPatch.addEventListener('click', () => {

        fetch(`http://${controlCrudInputAddressPatch.value}:${controlCrudInputPortPatch.value}/api/cargo/${controlCrudInputIdPatch.value}`,{
            method: 'PATCH',
            headers: {
                'Content-Type': 'application/json'
            },
            body: controlCrudInputBodyPatch.value
        })
        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.status == 'ok') {
                
                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputUpdate.classList.replace('d-none', 'd-block');
                controlCrudOutputUpdate.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputUpdate.classList.add('bg-success')
                controlCrudOutputUpdate.innerText = 'ok'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            } else {
                
                controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');

                controlCrudOutputUpdate.classList.replace('d-none', 'd-block');
                controlCrudOutputUpdate.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputUpdate.classList.add('bg-warning')
                controlCrudOutputUpdate.innerText = 'error'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputUpdate.classList.replace('d-none', 'd-block');
            controlCrudOutputUpdate.classList.remove('bg-warning', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputUpdate.classList.add('bg-danger')
            controlCrudOutputUpdate.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });

    // ----------------------------------------------------------------------------------------------------------------------------------------------

    controlCrudButtonPut.addEventListener('click', () => {

        fetch(`http://${controlCrudInputAddressPut.value}:${controlCrudInputPortPut.value}/api/cargo/${controlCrudInputIdPut.value}`,{
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: controlCrudInputBodyPut.value
        })
        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.status == 'ok') {
                
                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputUpdate.classList.replace('d-none', 'd-block');
                controlCrudOutputUpdate.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputUpdate.classList.add('bg-success')
                controlCrudOutputUpdate.innerText = 'ok'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            } else {
                
                controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');

                controlCrudOutputUpdate.classList.replace('d-none', 'd-block');
                controlCrudOutputUpdate.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputUpdate.classList.add('bg-warning')
                controlCrudOutputUpdate.innerText = 'error'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputUpdate.classList.replace('d-none', 'd-block');
            controlCrudOutputUpdate.classList.remove('bg-warning', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputUpdate.classList.add('bg-danger')
            controlCrudOutputUpdate.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // DELETE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    controlCrudButtonDeleteOne.addEventListener('click', () => {

        console.log(`http://${controlCrudInputAddressDeleteOne.value}:${controlCrudInputPortDeleteOne.value}/api/cargo/${controlCrudSelectDeleteOne.value}/${controlCrudInputIdDeleteOne.value}`);

        fetch(`http://${controlCrudInputAddressDeleteOne.value}:${controlCrudInputPortDeleteOne.value}/api/cargo/${controlCrudSelectDeleteOne.value}/${controlCrudInputIdDeleteOne.value}`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json'
            }
        })

        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.status == 'ok') {
            
                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputDelete.classList.replace('d-none', 'd-block');
                controlCrudOutputDelete.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputDelete.classList.add('bg-success')
                controlCrudOutputDelete.innerText = 'ok'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            } else {
                
                controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');

                controlCrudOutputDelete.classList.replace('d-none', 'd-block');
                controlCrudOutputDelete.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputDelete.classList.add('bg-warning')
                controlCrudOutputDelete.innerText = 'error'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputDelete.classList.replace('d-none', 'd-block');
            controlCrudOutputDelete.classList.remove('bg-warning', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputDelete.classList.add('bg-danger')
            controlCrudOutputDelete.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });

    // ----------------------------------------------------------------------------------------------------------------------------------------------

    controlCrudButtonDeleteAll.addEventListener('click', () => {

        console.log(`http://${controlCrudInputAddressDeleteAll.value}:${controlCrudInputPortDeleteAll.value}/api/cargo/${controlCrudSelectDeleteAll.value}/`);

        fetch(`http://${controlCrudInputAddressDeleteAll.value}:${controlCrudInputPortDeleteAll.value}/api/cargo/${controlCrudSelectDeleteAll.value}/`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json'
            }
        })

        .then(res => res.json())
        .then(data => {
            
            console.log(data);

            if(data.status == 'ok') {

                controlDiv.classList.remove('border-danger', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-success');
                
                controlCrudOutputDelete.classList.replace('d-none', 'd-block');
                controlCrudOutputDelete.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); controlCrudOutputDelete.classList.add('bg-success')
                controlCrudOutputDelete.innerText = 'ok'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-success">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');

            } else {
                
                controlDiv.classList.remove('border-danger', 'border-success', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-warning');

                controlCrudOutputDelete.classList.replace('d-none', 'd-block');
                controlCrudOutputDelete.classList.remove('bg-danger', 'bg-success', 'bg-info', 'bg-secondary'); controlCrudOutputDelete.classList.add('bg-warning')
                controlCrudOutputDelete.innerText = 'already null'

                controlCrudDivResponse.classList.replace('d-none', 'd-block');
                controlCrudDivResponseContent.classList.replace('text-center', 'text-left');
                controlCrudDivResponseContent.innerHTML = `<pre class="text-warning">${JSON.stringify(data, null, 2)}</pre>`;

                controlButtonContinue.classList.replace('btn-outline-secondary', 'btn-outline-primary');
            };
        })

        .catch(err => {

            console.log(err);

            controlDiv.classList.remove('border-success', 'border-warning', 'border-primary', 'border-secondary', 'border-info'); controlDiv.classList.add('border-danger');

            controlCrudOutputRead.classList.replace('d-none', 'd-block');
            controlCrudOutputRead.classList.remove('bg-warning', 'bg-success', 'bg-info'); controlCrudOutputRead.classList.add('bg-danger')
            controlCrudOutputRead.innerText = err;
            
            controlCrudDivResponse.classList.replace('d-none', 'd-block');
            controlCrudDivResponseContent.classList.remove('text-left'); controlCrudDivResponseContent.classList.add('text-center')
            controlCrudDivResponseContent.innerHTML = `<pre class="text-danger">${err}</pre>`;
        })
    });
};


function activateCrud() {

    controlCrudDivInput.classList.replace('d-none', 'd-block');

    crud();
};

function controlRun() {

    controlDiv.classList.replace('border-secondary', 'border-info');
    controlH1.classList.replace('text-secondary', 'text-light');
    controlCrudButton.classList.replace('btn-muted', 'btn-outline-primary');

    controlCrudButton.addEventListener('click', () => {

        controlCrudButton.classList.add('d-none');
        activateCrud();
    });
};


































































// function cargoFetch(address, port, path, array, index, tbody, callback) {

//     fetch(`http://${address}:${port}/api${path}`)

//         .then(res => res.json())
//         .then(data => {

//             console.log(`${path} DUMPED`);
//             array[index] = data.data;

//             tbody.innerHTML += `
//                 <tr>
//                     <td text-right>${path}</td>
//                     <td class="text-success">OK</td>
//                     <td class="">${array[index].length} docs</td>
//                 </tr>`;
//         })

//         .catch(err => {

//             console.log(err);

//             tbody.innerHTML += `
//                 <tr>
//                     <td>${path}</td>
//                     <td class="text-danger">FAIL</td>
//                     <td class="">err</td>
//                 </tr>`;

//                 demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
//                 demoOutputDump.innerText = err;
//         })

//         callback;
// };

demoDiv.classList.remove('d-none');

function findRecords(objarray, nodesarray) {

    demoButtonProcessRecords.classList.replace('btn-muted', 'btn-outline-primary');

    demoButtonProcessRecords.addEventListener('click', () => {

        let datearray = [];
        let indexarray = [];
        let recordsarray = [];

        
        nodesarray.addrs.forEach((addr, addrindex) => {

            objarray.forEach((collarray, collindex) => {

                collarray.forEach((doc, docindex) => {

                    if(doc.mote.linkLayerAddress == addr) {
                        datearray.push(doc.update);
                    }
                })

                indexarray[collindex] = datearray;

                console.log('addrindex: ' +addrindex);
                console.log('collindex: ' +collindex);
                console.log(indexarray[collindex]);

                datearray = [];
            })

            recordsarray[addrindex] = indexarray;
            indexarray = [];
        });

        // objarray.forEach((docarray, colindex) => {
        //     docarray.forEach((doc, docindex) => {

        //         nodesarray.addrs.forEach((addr, addrindex) => {
        //             if(doc.mote.linkLayerAddress == addr) {
        //                 datearray[addrindex].push(doc.update);
        //             }
        //         })
        //     })



        //     recordsarray[collindex] = 'address[date[]]'
        // })

        console.log(recordsarray);

        let rechtml = ''

       rechtml = `
        <thead>
            <tr>
                <th scope="col" class="text-center">#</th>`;

        nodesarray.addrs.forEach((addr, addrindex) => {

            rechtml += `
            <th scope="col" class="text-center">${addr}</th>`;
        })

        rechtml += `
            </tr>
        </thead>
        <tbody>`;

        let paths = [
            "system",
            "device",
            "energy",
            "stats/network/ip",
            "stats/network/icmp",
            "stats/transport",
            "stats/discovery",
            "cmd/ip/addr",
            "cmd/ip/nbr/ipaddr",
            "cmd/ip/nbr/lladdr",
            "cmd/ip/nbr/info",
            "cmd/tsch/status",
            "cmd/tsch/schedule",
            "cmd/routes/default",
            "cmd/routes/links/sources",
            "cmd/routes/links/destinations",
            "cmd/routes/entries/routes",
            "cmd/routes/entries/vias",
            "cmd/rpl/status/id",
            "cmd/rpl/status/dag",
            "cmd/rpl/status/time",
            "cmd/rpl/nbr/addr",
            "cmd/rpl/nbr/ranks",
            "cmd/rpl/nbr/values",
            "cmd/rpl/nbr/parens",
            "errors"
        ];

        objarray.forEach((coll, collindex) => {

            rechtml += `
            <tr>
                <th  scope="row" class="text-left align-middle">${paths[collindex]}</th>`;

            nodesarray.addrs.forEach((addr, addrindex) => {

                rechtml += `<td class="text-center justify-content-center align-middle">`;

                rechtml += `
                    <table class="align-middle m-auto p-auto ">    
                        <tbody>`;

                recordsarray[addrindex][collindex].forEach((date, dateindex) => {

                    rechtml += `
                    <tr class="align-middle"><td class="text-center"> ${date}</td></tr>`;
                })

                rechtml += `
                    </tbody>
                </table>`;

                rechtml += `${recordsarray[addrindex][collindex].length}`
                
                rechtml += `</td>`;
            })
            
            rechtml += `
            </tr>`;
        })

        rechtml += `
        </tbody>`;

        console.log(rechtml);

        // console.log(recordsarray[0][0]);

        demoTableProcessRecords.innerHTML = rechtml;
        demoTableProcessRecords.classList.remove('d-none');

        console.log(demoTableProcessRecords);
    })
}






function findDistictNodes(objarray) {

    let nodesarray = {
        addrs: [],
        codes: []
    };

    console.log(objarray);

    objarray.forEach((object, index) => {
        object.forEach((document, index) => {
            nodesarray.addrs.push(document.mote.linkLayerAddress)
            nodesarray.codes.push(document.mote.moteCode)
        })
    })

    console.log('all nodes addresses: ' + nodesarray);

    nodesarray.addrs = [...new Set(nodesarray.addrs)]; 
    nodesarray.codes = [...new Set(nodesarray.codes)]; 

    console.log('unique nodes addrs: ' + nodesarray.addrs);
    console.log('unique nodes codes: ' + nodesarray.codes);
    console.log('count of unique nodes addrs: ' + nodesarray.addrs.length);
    console.log('count of unique nodes codes: ' + nodesarray.codes.length);

    if(nodesarray.addrs.length === nodesarray.codes.length) {
        
        demoButtonProcessDistinctNodes.classList.remove('btn-outline-danger', 'btn-outline-warning', 'btn-outline-secondary');
        demoButtonProcessDistinctNodes.classList.add('btn-outline-success');

        // demoOutputDump.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-secondary'); 
        // demoOutputDump.classList.add('bg-success');
        // demoOutputDump.innerText = 'OK';

        demoTableProcessDistinctNodes.innerHTML = `
        <thead>
            <tr>
                <th class="text-center">addr</th>
                <th class="text-center">code</th>
            </tr>
        </thead>
        <tbody>`;

        nodesarray.addrs.forEach((addr, index) => {
            
            demoTableProcessDistinctNodes.innerHTML += `
            <tr>
                <td colspan="1" class="text-center">${nodesarray.addrs[index]}</td>
                <td colspan="1" class="text-center">${nodesarray.codes[index]}</td>
            </tr>`;
        })

        demoTableProcessDistinctNodes.innerHTML += `
        </tbody>`;

        demoTableProcessDistinctNodes.classList.remove('d-none');

        findRecords(objarray, nodesarray);

    } else {

        demoButtonProcessDistinctNodes.classList.remove('btn-outline-warning', 'btn-outline-primary', 'btn-outline-secondart');
        demoButtonProcessDistinctNodes.classList.add('btn-outline-danger');

        demoOutputDump.classList.remove('bg-success', 'bg-warning', 'bg-info', 'bg-secondary'); 
        demoOutputDump.classList.add('bg-danger');
        demoOutputDump.innerText = 'inconsistency detected (between distinct nodes: addrs.length =! codes.lenght';

    };

    

    // console.log(demoTableProcessDistinctNodes);
};



function demoProcess(objarray) {

    // demoDivProcessBridge.classList.remove('d-none');

    // demoDivProcessBridge.classList.add('d-none');
    demoDivProcessContent.classList.remove('d-none');

    demoDiv.classList.replace('border-success', 'border-primary');
    // demoOutputDump.classList.replace('d-block', 'd-none');

    demoButtonProcessDistinctNodes.addEventListener('click', () => {

        findDistictNodes(objarray);
    })
};






































































function endFetch(array) {
    
    let sum = 0;

    array.forEach((collection, index) => {

        sum += collection.length;
    })
    
    demoOutputDump.classList.remove('bg-danger', 'bg-warning', 'bg-info', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-success');
    demoOutputDump.innerText = `${array.length} Collections (${sum} Documents) dumped`;

    demoDiv.classList.remove('border-danger', 'border-warning', 'border-success', 'border-primary', 'border-secondary', 'border-info'); demoDiv.classList.add('border-success');
};


function demoRun() {

    demoDiv.classList.replace('border-secondary', 'border-info');
    demoH1.classList.replace('text-secondary', 'text-light');
    demoButtonDump.classList.replace('btn-muted', 'btn-outline-primary');

    let datarray = new Array();

    demoButtonDump.addEventListener('click', () => {
        
        demoButtonDump.classList.add('d-none');
        
        demoOutputDump.classList.replace('d-none', 'd-block');
        demoOutputDump.classList.remove('bg-danger', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-info');
        demoOutputDump.innerText = 'dumping database...'

        demoTableDump.classList.replace('d-none', 'd-block');
        demoTableDumpTbody.innerHTML = '';

        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/system', datarray, 0, demoTableDumpTbody, 
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/device', datarray, 1, demoTableDumpTbody, 
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/energy', datarray, 2, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/stats/network/ip', datarray, 3, demoTableDumpTbody, 
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/stats/network/icmp', datarray, 4, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/stats/transport', datarray, 5, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/stats/discovery', datarray, 6, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/ipaddr', datarray, 7, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/ipnbr/ipaddr', datarray, 8, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/ipnbr/lladdr', datarray, 9, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/ipnbr/info', datarray, 10, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/routes/default', datarray, 11, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/routes/links/sources', datarray, 12, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/routes/links/destinations', datarray, 13, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/routes/entries/routes', datarray, 14, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/routes/entries/vias', datarray, 15, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplstatus/id', datarray, 16, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplstatus/dag', datarray, 17, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplstatus/time', datarray, 18, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplnbr/addr', datarray, 19, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplnbr/ranks', datarray, 20, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplnbr/values', datarray, 21, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/cmd/rplnbr/parens', datarray, 22, demoTableDumpTbody,
        // cargoFetch(databaseInputAddress.value, databaseInputPort.value, '/cargo/errors', datarray, 23, demoTableDumpTbody, endFetch(datarray)))))))))))))))))))))))));

        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/system`)

        .then(res => res.json())
        .then(data => {

            datarray[0] = data.data;

            demoTableDumpTbody.innerHTML += `
                <tr>
                    <td>/cargo/system</td>
                    <td class="text-dark bg-success text-center">OK</td>
                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                    <td class="text-left text-light">${datarray[0].length}</td>
                </tr>`;

            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/device`)

            .then(res => res.json())
            .then(data => {

                datarray[1] = data.data;

                demoTableDumpTbody.innerHTML += `
                    <tr>
                        <td>/cargo/device</td>
                        <td class="text-dark bg-success text-center">OK</td>
                        <td class="text-right"><span class="text-secondary"> docs: </span></td>
                        <td class="text-left text-light">${datarray[1].length}</td>
                    </tr>`;

                fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/energy`)

                .then(res => res.json())
                .then(data => {

                    datarray[2] = data.data;

                    demoTableDumpTbody.innerHTML += `
                        <tr>
                            <td>/cargo/energy</td>
                            <td class="text-dark bg-success text-center">OK</td>
                            <td class="text-right"><span class="text-secondary"> docs: </span></td>
                            <td class="text-left text-light">${datarray[2].length}</td>
                        </tr>`;

                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/stats/network/ip`)

                    .then(res => res.json())
                    .then(data => {

                        datarray[3] = data.data;

                        demoTableDumpTbody.innerHTML += `
                            <tr>
                                <td>/cargo/stats/network/ip</td>
                                <td class="text-dark bg-success text-center">OK</td>
                                <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                <td class="text-left text-light">${datarray[3].length}</td>
                            </tr>`;

                        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/stats/network/icmp`)

                        .then(res => res.json())
                        .then(data => {
    
                            datarray[4] = data.data;
    
                            demoTableDumpTbody.innerHTML += `
                                <tr>
                                    <td>/cargo/stats/network/icmp</td>
                                    <td class="text-dark bg-success text-center">OK</td>
                                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                    <td class="text-left text-light">${datarray[4].length}</td>
                                </tr>`;

                            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/stats/transport`)

                            .then(res => res.json())
                            .then(data => {
        
                                datarray[5] = data.data;
        
                                demoTableDumpTbody.innerHTML += `
                                    <tr>
                                        <td>/cargo/stats/transport</td>
                                        <td class="text-dark bg-success text-center">OK</td>
                                        <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                        <td class="text-left text-light">${datarray[5].length}</td>
                                    </tr>`;
    
                                fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/stats/discovery`)

                                .then(res => res.json())
                                .then(data => {
            
                                    datarray[6] = data.data;
            
                                    demoTableDumpTbody.innerHTML += `
                                        <tr>
                                            <td>/cargo/stats/discovery</td>
                                            <td class="text-dark bg-success text-center">OK</td>
                                            <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                            <td class="text-left text-light">${datarray[6].length}</td>
                                        </tr>`;
        
                                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/ip/addr`)

                                    .then(res => res.json())
                                    .then(data => {
                
                                        datarray[7] = data.data;
                
                                        demoTableDumpTbody.innerHTML += `
                                            <tr>
                                                <td>/cargo/cmd/ip/addr</td>
                                                <td class="text-dark bg-success text-center">OK</td>
                                                <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                <td class="text-left text-light">${datarray[7].length}</td>
                                            </tr>`;
            
                                        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/ip/nbr/ipaddr`)

                                        .then(res => res.json())
                                        .then(data => {
                    
                                            datarray[8] = data.data;
                    
                                            demoTableDumpTbody.innerHTML += `
                                                <tr>
                                                    <td>/cargo/cmd/ip/nbr/ipaddrr</td>
                                                    <td class="text-dark bg-success text-center">OK</td>
                                                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                    <td class="text-left text-light">${datarray[8].length}</td>
                                                </tr>`;
                
                                            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/ip/nbr/lladdr`)

                                            .then(res => res.json())
                                            .then(data => {
                        
                                                datarray[9] = data.data;
                        
                                                demoTableDumpTbody.innerHTML += `
                                                    <tr>
                                                        <td>/cargo/cmd/ip/nbr/lladdr</td>
                                                        <td class="text-dark bg-success text-center">OK</td>
                                                        <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                        <td class="text-left text-light">${datarray[9].length}</td>
                                                    </tr>`;
                    
                                                fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/ip/nbr/info`)

                                                .then(res => res.json())
                                                .then(data => {
                            
                                                    datarray[10] = data.data;
                            
                                                    demoTableDumpTbody.innerHTML += `
                                                        <tr>
                                                            <td>/cargo/cmd/ip/nbr/info</td>
                                                            <td class="text-dark bg-success text-center">OK</td>
                                                            <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                            <td class="text-left text-light">${datarray[10].length}</td>
                                                        </tr>`;
                        
                                                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/tsch/status`)

                                                    .then(res => res.json())
                                                    .then(data => {
                                
                                                        datarray[11] = data.data;
                                
                                                        demoTableDumpTbody.innerHTML += `
                                                            <tr>
                                                                <td>/cargo/cmd/tsch/status</td>
                                                                <td class="text-dark bg-success text-center">OK</td>
                                                                <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                <td class="text-left text-light">${datarray[11].length}</td>
                                                            </tr>`;

                                                        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/tsch/schedule`)

                                                        .then(res => res.json())
                                                        .then(data => {
                                    
                                                            datarray[12] = data.data;
                                    
                                                            demoTableDumpTbody.innerHTML += `
                                                                <tr>
                                                                    <td>/cargo/cmd/tsch/schedule</td>
                                                                    <td class="text-dark bg-success text-center">OK</td>
                                                                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                    <td class="text-left text-light">${datarray[12].length}</td>
                                                                </tr>`;
                                                        
                                                            // ================================================================================================================================
                                                            
                                                            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/routes/default`)

                                                            .then(res => res.json())
                                                            .then(data => {
                                        
                                                                datarray[13] = data.data;
                                        
                                                                demoTableDumpTbody.innerHTML += `
                                                                    <tr>
                                                                        <td>/cargo/cmd/routes/default</td>
                                                                        <td class="text-dark bg-success text-center">OK</td>
                                                                        <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                        <td class="text-left text-light">${datarray[13].length}</td>
                                                                    </tr>`;
                                    
                                                                fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/routes/links/sources`)

                                                                .then(res => res.json())
                                                                .then(data => {
                                            
                                                                    datarray[14] = data.data;
                                            
                                                                    demoTableDumpTbody.innerHTML += `
                                                                        <tr>
                                                                            <td>/cargo/cmd/routes/links/sources</td>
                                                                            <td class="text-dark bg-success text-center">OK</td>
                                                                            <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                            <td class="text-left text-light">${datarray[14].length}</td>
                                                                        </tr>`;
                                        
                                                                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/routes/links/destinations`)

                                                                    .then(res => res.json())
                                                                    .then(data => {
                                                
                                                                        datarray[15] = data.data;
                                                
                                                                        demoTableDumpTbody.innerHTML += `
                                                                            <tr>
                                                                                <td>/cargo/cmd/routes/links/destinations</td>
                                                                                <td class="text-dark bg-success text-center">OK</td>
                                                                                <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                <td class="text-left text-light">${datarray[15].length}</td>
                                                                            </tr>`;
                                            
                                                                        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/routes/entries/routes`)

                                                                        .then(res => res.json())
                                                                        .then(data => {
                                                    
                                                                            datarray[16] = data.data;
                                                    
                                                                            demoTableDumpTbody.innerHTML += `
                                                                                <tr>
                                                                                    <td>/cargo/cmd/routes/entries/routes</td>
                                                                                    <td class="text-dark bg-success text-center">OK</td>
                                                                                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                    <td class="text-left text-light">${datarray[16].length}</td>
                                                                                </tr>`;
                                                
                                                                            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/routes/entries/vias`)

                                                                            .then(res => res.json())
                                                                            .then(data => {
                                                        
                                                                                datarray[17] = data.data;
                                                        
                                                                                demoTableDumpTbody.innerHTML += `
                                                                                    <tr>
                                                                                        <td>/cargo/cmd/routes/entries/vias</td>
                                                                                        <td class="text-dark bg-success text-center">OK</td>
                                                                                        <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                        <td class="text-left text-light">${datarray[17].length}</td>
                                                                                    </tr>`;
                                                                                
                                                                                fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/status/id`)

                                                                                .then(res => res.json())
                                                                                .then(data => {
                                                            
                                                                                    datarray[18] = data.data;
                                                            
                                                                                    demoTableDumpTbody.innerHTML += `
                                                                                        <tr>
                                                                                            <td>/cargo/cmd/rpl/status/id</td>
                                                                                            <td class="text-dark bg-success text-center">OK</td>
                                                                                            <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                            <td class="text-left text-light">${datarray[18].length}</td>
                                                                                        </tr>`;
                                                        
                                                                                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/status/dag`)

                                                                                    .then(res => res.json())
                                                                                    .then(data => {
                                                                
                                                                                        datarray[19] = data.data;
                                                                
                                                                                        demoTableDumpTbody.innerHTML += `
                                                                                            <tr>
                                                                                                <td>/cargo/cmd/rpl/status/dag</td>
                                                                                                <td class="text-dark bg-success text-center">OK</td>
                                                                                                <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                                <td class="text-left text-light">${datarray[19].length}</td>
                                                                                            </tr>`;
                                                            
                                                                                        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/status/time`)

                                                                                        .then(res => res.json())
                                                                                        .then(data => {
                                                                    
                                                                                            datarray[20] = data.data;
                                                                    
                                                                                            demoTableDumpTbody.innerHTML += `
                                                                                                <tr>
                                                                                                    <td>/cargo/cmd/rpl/status/time</td>
                                                                                                    <td class="text-dark bg-success text-center">OK</td>
                                                                                                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                                    <td class="text-left text-light">${datarray[20].length}</td>
                                                                                                </tr>`;
                                                                
                                                                                            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/nbr/addr`)

                                                                                            .then(res => res.json())
                                                                                            .then(data => {
                                                                        
                                                                                                datarray[21] = data.data;
                                                                        
                                                                                                demoTableDumpTbody.innerHTML += `
                                                                                                    <tr>
                                                                                                        <td>/cargo/cmd/rpl/nbr/addr</td>
                                                                                                        <td class="text-dark bg-success text-center">OK</td>
                                                                                                        <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                                        <td class="text-left text-light">${datarray[21].length}</td>
                                                                                                    </tr>`;
                                                                    
                                                                                                fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/nbr/ranks`)

                                                                                                .then(res => res.json())
                                                                                                .then(data => {
                                                                            
                                                                                                    datarray[22] = data.data;
                                                                            
                                                                                                    demoTableDumpTbody.innerHTML += `
                                                                                                        <tr>
                                                                                                            <td>/cargo/cmd/rpl/nbr/ranks</td>
                                                                                                            <td class="text-dark bg-success text-center">OK</td>
                                                                                                            <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                                            <td class="text-left text-light">${datarray[22].length}</td>
                                                                                                        </tr>`;
                                                                        
                                                                                                    fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/nbr/values`)

                                                                                                    .then(res => res.json())
                                                                                                    .then(data => {
                                                                                
                                                                                                        datarray[23] = data.data;
                                                                                
                                                                                                        demoTableDumpTbody.innerHTML += `
                                                                                                            <tr>
                                                                                                                <td>/cargo/cmd/rpl/nbr/values</td>
                                                                                                                <td class="text-dark bg-success text-center">OK</td>
                                                                                                                <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                                                <td class="text-left text-light">${datarray[23].length}</td>
                                                                                                            </tr>`;
                                                                            
                                                                                                        fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/cmd/rpl/nbr/parens`)

                                                                                                        .then(res => res.json())
                                                                                                        .then(data => {
                                                                                    
                                                                                                            datarray[24] = data.data;
                                                                                    
                                                                                                            demoTableDumpTbody.innerHTML += `
                                                                                                                <tr>
                                                                                                                    <td>/cargo/cmd/rpl/nbr/parens</td>
                                                                                                                    <td class="text-dark bg-success text-center">OK</td>
                                                                                                                    <td class="text-right"><span class="text-secondary"> docs: </span></td>
                                                                                                                    <td class="text-left text-light">${datarray[24].length}</td>
                                                                                                                </tr>`;
                                                                                
                                                                                                            fetch(`http://${databaseInputAddress.value}:${databaseInputPort.value}/api/cargo/errors`)

                                                                                                            .then(res => res.json())
                                                                                                            .then(data => {
                                                                                        
                                                                                                                datarray[25] = data.data;
                                                                                        
                                                                                                                demoTableDumpTbody.innerHTML += `
                                                                                                                    <tr>
                                                                                                                        <td>/cargo/errors</td>
                                                                                                                        <td class="text-dark bg-success text-center">OK</td>
                                                                                                                        <td class="text-right text-warning"><span class="text-secondary"> docs: </span></td>
                                                                                                                        <td class="text-left text-warning">${datarray[25].length}</td>
                                                                                                                    </tr>`;
                                                                                    
                                                                                                                endFetch(datarray);
                                                                                                                demoProcess(datarray);
                                                                                                            })

                                                                                                            .catch(err => {

                                                                                                                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                                                demoOutputDump.innerText = 'STOPPED';

                                                                                                                demoTableDump.classList.replace('col-6', 'col-12');
                                                                                                    
                                                                                                                demoTableDumpTbody.innerHTML += `
                                                                                                                            <tr>
                                                                                                                                <td>/cargo/errors</td>
                                                                                                                                <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                                                <td class="text-danger text-center">${err}</td>
                                                                                                                            </tr>`;
                                                                                                            })
                                                                                                        })

                                                                                                        .catch(err => {

                                                                                                            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                                            demoOutputDump.innerText = 'STOPPED';

                                                                                                            demoTableDump.classList.replace('col-6', 'col-12');
                                                                                                
                                                                                                            demoTableDumpTbody.innerHTML += `
                                                                                                                        <tr>
                                                                                                                            <td>/cargo/cmd/rpl/nbr/parens</td>
                                                                                                                            <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                                            <td class="text-danger text-center">${err}</td>
                                                                                                                        </tr>`;
                                                                                                        })
                                                                                                    })

                                                                                                    .catch(err => {

                                                                                                        demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                                        demoOutputDump.innerText = 'STOPPED';

                                                                                                        demoTableDump.classList.replace('col-6', 'col-12');
                                                                                            
                                                                                                        demoTableDumpTbody.innerHTML += `
                                                                                                                    <tr>
                                                                                                                        <td>/cargo/cmd/rpl/nbr/values</td>
                                                                                                                        <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                                        <td class="text-danger text-center">${err}</td>
                                                                                                                    </tr>`;
                                                                                                    })
                                                                                                })

                                                                                                .catch(err => {

                                                                                                    demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                                    demoOutputDump.innerText = 'STOPPED';

                                                                                                    demoTableDump.classList.replace('col-6', 'col-12');
                                                                                        
                                                                                                    demoTableDumpTbody.innerHTML += `
                                                                                                                <tr>
                                                                                                                    <td>/cargo/cmd/rpl/nbr/ranks</td>
                                                                                                                    <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                                    <td class="text-danger text-center">${err}</td>
                                                                                                                </tr>`;
                                                                                                })
                                                                                            })

                                                                                            .catch(err => {

                                                                                                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                                demoOutputDump.innerText = 'STOPPED';

                                                                                                demoTableDump.classList.replace('col-6', 'col-12');
                                                                                    
                                                                                                demoTableDumpTbody.innerHTML += `
                                                                                                            <tr>
                                                                                                                <td>/cargo/cmd/rpl/nbr/addr</td>
                                                                                                                <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                                <td class="text-danger text-center">${err}</td>
                                                                                                            </tr>`;
                                                                                            })
                                                                                        })

                                                                                        .catch(err => {

                                                                                            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                            demoOutputDump.innerText = 'STOPPED';
                                                                                            
                                                                                            demoTableDump.classList.replace('col-6', 'col-12');

                                                                                            demoTableDumpTbody.innerHTML += `
                                                                                                        <tr>
                                                                                                            <td>/cargo/cmd/rpl/status/time</td>
                                                                                                            <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                            <td class="text-danger">${err}</td>
                                                                                                        </tr>`;
                                                                                        })
                                                                                    })

                                                                                    .catch(err => {

                                                                                        demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                        demoOutputDump.innerText = 'STOPPED';

                                                                                        demoTableDump.classList.replace('col-6', 'col-12');
                                                                            
                                                                                        demoTableDumpTbody.innerHTML += `
                                                                                                    <tr>
                                                                                                        <td>/cargo/cmd/rpl/status/dag</td>
                                                                                                        <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                        <td class="text-danger text-center">${err}</td>
                                                                                                    </tr>`;
                                                                                    })
                                                                                })

                                                                                .catch(err => {

                                                                                    demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                    demoOutputDump.innerText = 'STOPPED';

                                                                                    demoTableDump.classList.replace('col-6', 'col-12');
                                                                        
                                                                                    demoTableDumpTbody.innerHTML += `
                                                                                                <tr>
                                                                                                    <td>/cargo/cmd/rpl/status/id</td>
                                                                                                    <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                    <td class="text-danger text-center">${err}</td>
                                                                                                </tr>`;
                                                                                })
                                                                            })

                                                                            .catch(err => {

                                                                                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                                demoOutputDump.innerText = 'STOPPED';

                                                                                demoTableDump.classList.replace('col-6', 'col-12');
                                                                    
                                                                                demoTableDumpTbody.innerHTML += `
                                                                                            <tr>
                                                                                                <td>/cargo/cmd/routes/entries/vias</td>
                                                                                                <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                                <td class="text-danger text-center">${err}</td>
                                                                                            </tr>`;
                                                                            })
                                                                        })

                                                                        .catch(err => {

                                                                            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                            demoOutputDump.innerText = 'STOPPED';

                                                                            demoTableDump.classList.replace('col-6', 'col-12');
                                                                
                                                                            demoTableDumpTbody.innerHTML += `
                                                                                        <tr>
                                                                                            <td>/cargo/cmd/routes/entries/routes</td>
                                                                                            <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                            <td class="text-danger text-center">${err}</td>
                                                                                        </tr>`;
                                                                        })
                                                                    })

                                                                    .catch(err => {

                                                                        demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                        demoOutputDump.innerText = 'STOPPED';

                                                                        demoTableDump.classList.replace('col-6', 'col-12');
                                                            
                                                                        demoTableDumpTbody.innerHTML += `
                                                                                    <tr>
                                                                                        <td>/cargo/cmd/routes/links/destinations</td>
                                                                                        <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                        <td class="text-danger text-center">${err}</td>
                                                                                    </tr>`;
                                                                    })
                                                                })

                                                                .catch(err => {

                                                                    demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                    demoOutputDump.innerText = 'STOPPED';

                                                                    demoTableDump.classList.replace('col-6', 'col-12');
                                                        
                                                                    demoTableDumpTbody.innerHTML += `
                                                                                <tr>
                                                                                    <td>/cargo/cmd/routes/links/sources</td>
                                                                                    <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                    <td class="text-danger text-center">${err}</td>
                                                                                </tr>`;
                                                                })
                                                            })

                                                            .catch(err => {

                                                                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                                demoOutputDump.innerText = 'STOPPED';

                                                                demoTableDump.classList.replace('col-6', 'col-12');
                                                    
                                                                demoTableDumpTbody.innerHTML += `
                                                                            <tr>
                                                                                <td>/cargo/cmd/routes/default</td>
                                                                                <td class="text-dark bg-danger text-center">FAIL</td>
                                                                                <td class="text-danger text-center">${err}</td>
                                                                            </tr>`;
                                                            })

                                                            // ============================================================================================================
                                                        })

                                                        .catch(err => {

                                                            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                            demoOutputDump.innerText = 'STOPPED';

                                                            demoTableDump.classList.replace('col-6', 'col-12');
                                                
                                                            demoTableDumpTbody.innerHTML += `
                                                                        <tr>
                                                                            <td>/cargo/cmd/tsch/schedule</td>
                                                                            <td class="text-dark bg-danger text-center">FAIL</td>
                                                                            <td class="text-danger text-center">${err}</td>
                                                                        </tr>`;
                                                        })

                                                    })

                                                    .catch(err => {

                                                        demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                        demoOutputDump.innerText = 'STOPPED';

                                                        demoTableDump.classList.replace('col-6', 'col-12');
                                            
                                                        demoTableDumpTbody.innerHTML += `
                                                                    <tr>
                                                                        <td>/cargo/cmd/tsch/status</td>
                                                                        <td class="text-dark bg-danger text-center">FAIL</td>
                                                                        <td class="text-danger text-center">${err}</td>
                                                                    </tr>`;
                                                    })
                                                })
                                                
                                                .catch(err => {

                                                    demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                    demoOutputDump.innerText = 'STOPPED';

                                                    demoTableDump.classList.replace('col-6', 'col-12');
                                        
                                                    demoTableDumpTbody.innerHTML += `
                                                                <tr>
                                                                    <td>/cargo/cmd/ip/nbr/info</td>
                                                                    <td class="text-dark bg-danger text-center">FAIL</td>
                                                                    <td class="text-danger text-center">${err}</td>
                                                                </tr>`;
                                                })
                                            })
                                            
                                            .catch(err => {

                                                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                                demoOutputDump.innerText = 'STOPPED';

                                                demoTableDump.classList.replace('col-6', 'col-12');
                                    
                                                demoTableDumpTbody.innerHTML += `
                                                            <tr>
                                                                <td>/cargo/cmd/ip/nbr/lladdr'</td>
                                                                <td class="text-dark bg-danger text-center">FAIL</td>
                                                                <td class="text-danger text-center">${err}</td>
                                                            </tr>`;
                                            })
                                        })
                                        
                                        .catch(err => {

                                            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                            demoOutputDump.innerText = 'STOPPED';
                                            
                                            demoTableDump.classList.replace('col-6', 'col-12');
                                
                                            demoTableDumpTbody.innerHTML += `
                                                        <tr>
                                                            <td>/cargo/cmd/ip/nbr/ipaddr</td>
                                                            <td class="text-dark bg-danger text-center">FAIL</td>
                                                            <td class="text-danger text-center">${err}</td>
                                                        </tr>`;
                                        })
                                    })
                                    
                                    .catch(err => {

                                        demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                        demoOutputDump.innerText = 'STOPPED';

                                        demoTableDump.classList.replace('col-6', 'col-12');
                            
                                        demoTableDumpTbody.innerHTML += `
                                                    <tr>
                                                        <td>/cargo/cmd/ip/addr</td>
                                                        <td class="text-dark bg-danger text-center">FAIL</td>
                                                        <td class="text-danger text-center">${err}</td>
                                                    </tr>`;
                                    })
                                })
                                
                                .catch(err => {

                                    demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                    demoOutputDump.innerText = 'STOPPED';

                                    demoTableDump.classList.replace('col-6', 'col-12');
                        
                                    demoTableDumpTbody.innerHTML += `
                                                <tr>
                                                    <td>/cargo/stats/discovery</td>
                                                    <td class="text-dark bg-danger text-center">FAIL</td>
                                                    <td class="text-danger text-center">${err}</td>
                                                </tr>`;
                                })
                            })

                            .catch(err => {

                                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                                demoOutputDump.innerText = 'STOPPED';

                                demoTableDump.classList.replace('col-6', 'col-12');
                    
                                demoTableDumpTbody.innerHTML += `
                                            <tr>
                                                <td>/cargo/stats/transport</td>
                                                <td class="text-dark bg-danger text-center">FAIL</td>
                                                <td class="text-danger text-center">${err}</td>
                                            </tr>`;
                            })
                        })

                        .catch(err => {

                            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                            demoOutputDump.innerText = 'STOPPED';

                            demoTableDump.classList.replace('col-6', 'col-12');
                
                            demoTableDumpTbody.innerHTML += `
                                        <tr>
                                            <td>/cargo/stats/network/icmp</td>
                                            <td class="text-dark bg-danger text-center">FAIL</td>
                                            <td class="text-danger text-center">${err}</td>
                                        </tr>`;
                        })
                    })

                    .catch(err => {

                        demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                        demoOutputDump.innerText = 'STOPPED';

                        demoTableDump.classList.replace('col-6', 'col-12');
            
                        demoTableDumpTbody.innerHTML += `
                                    <tr>
                                        <td>/cargo/stats/network/ip</td>
                                        <td class="text-dark bg-danger text-center">FAIL</td>
                                        <td class="text-danger text-center">${err}</td>
                                    </tr>`;
                    })
                })

                .catch(err => {

                    demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                    demoOutputDump.innerText = 'STOPPED';

                    demoTableDump.classList.replace('col-6', 'col-12');
        
                    demoTableDumpTbody.innerHTML += `
                                <tr>
                                    <td>/cargo/energy</td>
                                    <td class="text-dark bg-danger text-center">FAIL</td>
                                    <td class="text-danger text-center">${err}</td>
                                </tr>`;
                })
            })

            .catch(err => {

                demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
                demoOutputDump.innerText = 'STOPPED';

                demoTableDump.classList.replace('col-6', 'col-12');
    
                demoTableDumpTbody.innerHTML += `
                            <tr>
                                <td>/cargo/device</td>
                                <td class="text-dark bg-danger text-center">FAIL</td>
                                <td class="text-danger text-center">${err}</td>
                            </tr>`;
            })
        })
            
        .catch(err => {

            demoOutputDump.classList.remove('bg-info', 'bg-warning', 'bg-success', 'bg-primary', 'bg-secondary'); demoOutputDump.classList.add('bg-danger');
            demoOutputDump.innerText = 'STOPPED';

            demoTableDump.classList.replace('col-6', 'col-12');

            demoTableDumpTbody.innerHTML += `
                        <tr>
                            <td>/cargo/system</td>
                            <td class="text-dark bg-danger text-center">FAIL</td>
                            <td class="text-danger text-center">${err}</td>
                        </tr>`;
        })
    })
};

demoRun();


