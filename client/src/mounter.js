var m = require("mithril");
var layout = require("./views/layout");
const sidebar_dashboard = require("./components/sidebar/sidebar_dashboard");
const dashboard = require("./views/dashboard");
const sidebar_client_mng = require("./components/sidebar/sidebar_client_mng");
const client_mng = require("./views/client_mng");
const sidebar_configuration = require("./components/sidebar/sidebar_configuration");
const configuration = require("./views/configuration");


function mountRoutes() {
    document.body.className = "";
        m.route(document.body, "/dashboard", {
            "/dashboard": {
                render: function() {
                    return m(layout, m(sidebar_dashboard), m(dashboard));
                }
            },
            "/gestion_client": {
                render: function(){
                    return m(layout, m(sidebar_client_mng), m(client_mng))
                }
            },
            "/configuration": {
                render: function(){
                    return m(layout, m(sidebar_configuration), m(configuration))
                }
            }
        });
}
exports.mountRoutes = mountRoutes;