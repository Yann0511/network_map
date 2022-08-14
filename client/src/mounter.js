var m = require("mithril");
const table = require("./views/table");


function mountRoutes() {
    document.body.className = "";
        m.route(document.body, "/tables", {
            "/tables": {
                render: function() {
                    return m(table);
                }
            },
        });
}
exports.mountRoutes = mountRoutes;