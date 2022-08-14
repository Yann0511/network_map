var m = require('mithril');
const postes = require('../components/postes');
const tabs_dashboard_group = require('../components/tabs/tabs_dashboard_group');


module.exports = {
    view: function(vnode){
        return [
            m("div", {
                "class": "container-fluid"
            }, 
            [
                m("h6", {
                    "class": ""
                },
                    "Mon tableau de bord"
                ),
                m(tabs_dashboard_group),
                m(postes)
            ])
        ]
    }
}