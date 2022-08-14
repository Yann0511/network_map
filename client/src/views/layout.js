var m = require('mithril');
const menu_dashboard = require('../components/menus/menu_dashboard');
const navbar = require('../components/navbar');

module.exports = {
    view: function(vnode) {
        return [
            m("div", {"class":"container-fluid"},
                [
                    m(navbar),
                    m("hr"),
                    m.route.get() == '/dashboard' ? m(menu_dashboard) : null,
                    m("div", {
                        "class": "row"
                    }, [
                        m("div", {"class":"col-3"}, 
                            vnode.children[0]
                        ),
                        m("div", {"class":"col-9"}, 
                            vnode.children[1]
                        )
                    ])
                ]
            )
        ]
    }
}