var m = require("mithril");
const statistique = require("./views/statistique");
const table = require("./views/table");


function mountRoutes() {
    document.body.className = "";
        m.route(document.body, "/tables", {
            "/tables": {
                render: function() {
                    return m(table);
                }
            },

            "/statistiques": {
                render: function() {
                    return m(statistique);
                }
            },
        });
}
exports.mountRoutes = mountRoutes;