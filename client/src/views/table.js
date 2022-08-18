var m = require('mithril');
const hote = require('../models/hote.model');
const sidebar = require('../components/sidebar');
const navbar = require('../components/navbar');
const footer = require('../components/footer');


module.exports = {
    oninit() {
      console.log("Fetching hote ....");
      hote.getHotes()
  
    },
    view: function(vnode){
        return [
            m("div", {"id":"wrapper"},
              m(sidebar),

              m("div", {"class":"d-flex flex-column","id":"content-wrapper"}, 
                m("div", {"id":"content"},
                    m(navbar),

                    m("div", {"class":"container-fluid"}, 
                    m("div", {"class":"card shadow mb-4"},
                      [
                        m("div", {"class":"card-header py-3"}, 
                          m("h6", {"class":"m-0 font-weight-bold text-primary"}, 
                            "DataTables"
                          )
                        ),
                        m("div", {"class":"card-body"}, 
                          m("div", {"class":"table-responsive"}, 
                            m("table", {"class":"table table-bordered","width":"100%","cellspacing":"0"},
                              [
                                m("thead", 
                                  m("tr",
                                    [
                                      m("th", 
                                        "Adresse ip"
                                      ),
                                      m("th", 
                                        "Systeme d'exploitation"
                                      ),
                                      m("th", 
                                        "Ports ouvert"
                                      ),
                                      m("th", 
                                        "Paquet envoyé"
                                      ),
                                      m("th", 
                                        "Paquet reçu"
                                      ),
                                      m("th", 
                                        "Associés"
                                      )
                                    ]
                                  )
                                ),
                                m("tfoot", 
                                  m("tr",
                                    [
                                      m("th", 
                                        "Adresse ip"
                                      ),
                                      m("th", 
                                        "Systeme d'exploitation"
                                      ),
                                      m("th", 
                                        "Ports ouvert"
                                      ),
                                      m("th", 
                                        "Paquet envoyé"
                                      ),
                                      m("th", 
                                        "Paquet reçu"
                                      ),
                                      m("th", 
                                        "Associés"
                                      )
                                    ]
                                  )
                                ),
                                m("tbody", hote.list.map(function (h) {
                                  return m("tr",
                                      
                                        m("td", 
                                          h['ip']
                                        ),
                                        m("td", 
                                          h['os']
                                        ),
                                        m("td", 
                                          h['ports']
                                        ),
                                        m("td", 
                                          h['pe']
                                        ),
                                        m("td", 
                                          h['pr']
                                        ),
                                        m("td", 
                                          h['assoc']
                                        )
                                      
                                    )
                                })
                                  
                                )
                              ]
                            )
                          )
                        )
                      ]
                    ),

                    m(footer)
                    )
                )
              )
            ),

            m("a", {"class":"scroll-to-top rounded","href":"#page-top"}, 
              m("i", {"class":"fas fa-angle-up"})
            )

        ]
    }
}