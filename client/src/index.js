var m = require("mithril");
const login = require("./views/login");
var register = require("./views/register");

const {
    mountRoutes
} = require("./mounter");

if (window.localStorage['jwt'] != undefined)
    mountRoutes();
else
     m.route(document.body, "/login", {
            "/login": {
                render: function() {
                    return m(login);
                }
            },
            "/register": {
                render: function() {
                    return m(register);
                }
            },
        });