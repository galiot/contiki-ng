$("#jsGrid").jsGrid({
    width: "100%",
    height: "auto",

    autoload:   true,
    paging:     true,
    // pageSize:   5,
    // pageButtonCount: 5,
    // pageIndex:  1,

    controller: {
        loadData: function (filter) {
            console.log(filter);
            return $.ajax({
                type: "GET",
                url: "http://localhost:8080/api/system",
                data: filter,
                dataType: "json"
            }).then(function(result) {
                return result.data;
            });
        }
    },
    fields: [
        // {name: "record", width: 100}
        // {name: "name", width: 50},
        // {name: "full_name", width: 100},
        // {name: "owner.id", width: 100}
        {name: "mote.systemTime", width: 100}
    ]
});