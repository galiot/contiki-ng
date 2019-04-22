
// https://github.com/tabalinas/jsgrid/issues/795
// uniquejava commented on 27 Aug 2017

jsGrid.Grid.prototype._sortData = function () {
    var self = this,
      sortFactor = this._sortFactor(),
      sortField = this._sortField;
  
    if (sortField) {
      this.data.sort(function (item1, item2) {
  
        var value1 = self._getItemFieldValue(item1, sortField);
        var value2 = self._getItemFieldValue(item2, sortField);
        return sortFactor * sortField.sortingFunc(value1, value2);
      });
    }
  };


$("#jsGrid_system").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/system",
                data: filter,
                dataType: "json"
            }).then(function (result) {

                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},

        { width: "auto", type: "text",      align: "center", name: "system.contikiVersion"},
        { width: "auto", type: "text",      align: "center", name: "system.networkStackRouting"},
        { width: "auto", type: "text",      align: "center", name: "system.networkStackNetwork"},
        { width: "auto", type: "text",      align: "center", name: "system.ieee802154PANID"},

        { width: "auto", type: "text",      align: "center", name: "system.networkStackMac.name"},
        { width: "auto", type: "number",    align: "center", name: "system.networkStackMac.tschDefaultHoppingSequence"},
        { width: "auto", type: "number",    align: "center", name: "system.networkStackMac.defaultChannel"},

        { width: "auto", type: "number",    align: "center", name: "system.nodeId"},
        { width: "auto", type: "text",      align: "center", name: "system.tentaticeLinkLocalIPv6address"},


        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_device").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/device",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},

        { width: "auto", type: "number",    align: "center", name: "device.temperatureSensor"},
        { width: "auto", type: "number",    align: "center", name: "device.humiditySensor"},

        { width: "auto", type: "number",    align: "center", name: "system.nodeId"},
        { width: "auto", type: "text",      align: "center", name: "system.tentaticeLinkLocalIPv6address"},

        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_energest").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/energest",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},

        { width: "auto", type: "text",      align: "center", name: "energest.energest"},
        { width: "auto", type: "number",    align: "center", name: "energest.cpu"},
        { width: "auto", type: "number",    align: "center", name: "energest.lpm"},
        { width: "auto", type: "number",    align: "center", name: "energest.deepLpm"},
        { width: "auto", type: "number",    align: "center", name: "energest.totalTime"},
        { width: "auto", type: "number",    align: "center", name: "energest.radioListening"},
        { width: "auto", type: "number",    align: "center", name: "energest.radioTransmiting"},
        { width: "auto", type: "number",    align: "center", name: "energest.radioOff"},
        
        { width: "auto", type: "number",    align: "center", name: "system.nodeId"},
        { width: "auto", type: "text",      align: "center", name: "system.tentaticeLinkLocalIPv6address"},

        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_stats_network_ip").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/stats/network/ip",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},
        
        { width: "auto", type: "number",    align: "center", name: "stats_network_ip.uipStatistics"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipRecv"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipSent"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipForwarded"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipDrop"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipVhlerr"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipHblenerr"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipLblenerr"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipFragerr"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipChkerr"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_ip.ip.ipProtoerr"},

        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_stats_network_icmp").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/stats/network/icmp",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},
        
        { width: "auto", type: "number",    align: "center", name: "stats_network_icmp.uipStatistics"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_icmp.ic.icmpRecv"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_icmp.ic.icmpSent"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_icmp.ic.icmpDrop"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_icmp.ic.icmpTypeerr"},
        { width: "auto", type: "text",      align: "center", name: "stats_network_icmp.ic.icmpChkerr"},

        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_stats_transport").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/stats/transport",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},
        
        { width: "auto", type: "text",      align: "center", name: "stats_transport.uipStatistics"},

        { width: "auto", type: "text",      align: "center", name: "stats_transport.tcp.tcp"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpRecv"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpSent"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpDrop"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpChkerr"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpAckerr"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpRst"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpRexmit"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpSyndrop"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpSynrst"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.tcp.tcpAckerr"},

        { width: "auto", type: "text",      align: "center", name: "stats_transport.udp.udp"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.udp.udpRecv"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.udp.udpSent"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.udp.udpDrop"},
        { width: "auto", type: "number",    align: "center", name: "stats_transport.udp.udpChkerr"},

        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_stats_discovery").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/stats/discovery",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},
        
        { width: "auto", type: "text",      align: "center", name: "stats_discovery.uipStatistics"},

        { width: "auto", type: "text",      align: "center", name: "stats_discovery.nd6.nd6drop"},
        { width: "auto", type: "number",    align: "center", name: "stats_discovery.nd6.nd6recv"},
        { width: "auto", type: "number",    align: "center", name: "stats_discovery.nd6.nd6sent"},
        
        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});

$("#jsGrid_cmd_ipAddr").jsGrid({

    height: "auto",
    width: "500%",

    filtering: false,
    editing: false,
    sorting: true,
    paging: true,
    autoload: true,

    pageSize: 15,
    pageButtonCount: 5,

    controller: {

        loadData: function (filter) {

            console.log(filter);
            return $.ajax({

                type: "GET",
                url: "http://localhost:8080/api/cargo/read/cmd/ipAddr",
                data: filter,
                dataType: "json"
            }).then(function (result) {
                
                return result.data;
            });
        }
    },

    fields: [

        { width: "auto", type: "text",      align: "center", name: "packet.valid"},
        { width: "auto", type: "text",      align: "center", name: "packet.error"},
        { width: "auto", type: "number",    align: "center", name: "record"},
        { width: "auto", type: "number",    align: "center", name: "index"},
        { width: "auto", type: "number",    align: "center", name: "mote.systemTime"},
        { width: "auto", type: "text",      align: "center", name: "mote.linkLayerAddress"},
        { width: "auto", type: "text",      align: "center", name: "mote.moteCode"},
        
        { width: "auto", type: "text",      align: "center", name: "cmd_ipAddr.ipv6"},

        { width: "auto", type: "select",    align: "center", name: "cmd_ipAddr.nodeIPv6addresses", items: [
            {Name: "nodeIPv6address", id: 0},
            {Name: "nodeIPv6address", id: 1},
            {Name: "nodeIPv6address", id: 2}
        ], valueField: "id", textField: "Name"},
        
        { width: "auto", type: "number",    align: "center", name: "checksum.hash"},
        { width: "auto", type: "string",    align: "center", name: "checksum.check"},
        { width: "auto", type: "date",      align: "center", name: "update"}
    ],

    autoload: true,
});