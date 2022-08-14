var m = require('mithril');

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
                    "Tous les clients"
                ),

                m("table", {"class":"table"},
                [
                    m("thead", 
                    m("tr",
                        [
                        m("th", {"scope":"col"}, 
                            "Nom d'utilisateur"
                        ),
                        m("th", {"scope":"col"}, 
                            "Groupe 1"
                        ),
                        m("th", {"scope":"col"}, 
                            "Groupe 2"
                        ),
                        m("th", {"scope":"col"}, 
                            "Groupe 3"
                        ),
                        m("th", {"scope":"col"}, 
                            "Punition"
                        )
                        ]
                    )
                    ),
                    m("tbody",
                    [
                        m("tr",
                        [
                            m("th", {"scope":"row"}, 
                            "John Doe"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "0"
                            )
                        ]
                        ),
                        m("tr",
                        [
                            m("th", {"scope":"row"}, 
                            "John Doe"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "0"
                            )
                        ]
                        ),
                        m("tr",
                        [
                            m("th", {"scope":"row"}, 
                            "John Doe"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "HH:MM:SS"
                            ),
                            m("td", 
                            "0"
                            )
                        ]
                        )
                    ]
                    )
                ]
                )
            ])
        ]
    }
}