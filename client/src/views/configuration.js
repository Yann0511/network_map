var m = require('mithril');
const sidebar_configuration = require('../components/sidebar/sidebar_configuration');
const tabs_configuration = require('../components/tabs/tabs_configuration');

const group_mng = {
    view(vnode){
        return [
            m("table", {"class":"table"},
                [
                    m("thead", 
                    m("tr",
                        [
                        m("th", {"scope":"col"}, 
                            "Catégorie"
                        ),
                        m("th", {"scope":"col"}, 
                            "Nom du groupe"
                        ),
                        m("th", {"scope":"col"}, 
                            "Punitions (minutes)"
                        ),
                        m("th", {"scope":"col"}, 
                            "Actions"
                        )
                        ]
                    )
                    ),
                    m("tbody",
                    [
                        m("tr",
                        [
                            m("th", {"scope":"row"}, 
                            "PS"
                            ),
                            m("td", 
                            "Alpha"
                            ),
                            m("td", 
                            "1000"
                            ),
                            m("td",
                            [
                                m("button", {"class":"btn btn-danger mx-1","type":"button"}, 
                                "X"
                                ),
                                m("button", {"class":"btn btn-danger mx-1","type":"button"}, 
                                "X"
                                ),
                                m("button", {"class":"btn btn-danger mx-1","type":"button"}, 
                                "X"
                                )
                            ]
                            )
                        ]
                        ),
                        m("tr",
                        [
                            m("th", {"scope":"row"}, 
                            "XBOX"
                            ),
                            m("td", 
                            "Bêta"
                            ),
                            m("td", 
                            "1000"
                            ),
                            m("td", 
                            m("button", {"class":"btn btn-danger mx-1","type":"button"}, 
                                "X"
                            )
                            )
                        ]
                        ),
                        m("tr",
                        [
                            m("th", {"scope":"row"}, 
                            "PS"
                            ),
                            m("td", 
                            "Lambda"
                            ),
                            m("td", 
                            "1000"
                            ),
                            m("td", 
                            m("button", {"class":"btn btn-danger mx-1","type":"button"}, 
                                "X"
                            )
                            )
                        ]
                        )
                    ]
                    )
                ]
            )
        ]
    }
}

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
                    "Configuration"
                ),
                m(tabs_configuration),
                m("p", {
                    "class": ""
                }, "Punitions et actions"),
                m(group_mng)
            ])
        ]
    }
}