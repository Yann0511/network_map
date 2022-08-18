var m = require('mithril');
const statistique = require('../models/statistique.model');
const sidebar = require('../components/sidebar');
const navbar = require('../components/navbar');
const footer = require('../components/footer');


module.exports = {
  oninit() {
    console.log("Fetching statistique ....");
    statistique.getStatistiques()
  
  },
    view: function(vnode){
        return [
            m("div", {"id":"wrapper"},
              m(sidebar),

              m("div", {"class":"d-flex flex-column","id":"content-wrapper"}, 
                m("div", {"id":"content"},
                    m(navbar),

                    m("div", {"class":"container-fluid"},
                    [
                      m("div", {"class":"d-sm-flex align-items-center justify-content-between mb-4"}, 
                        m("h1", {"class":"h3 mb-0 text-gray-800"}, 
                          "Statistiques"
                        )
                      ),
                      m("div", {"class":"row"},
                        [
                          m("div", {"class":"col-xl-3 col-md-6 mb-4"}, 
                            m("div", {"class":"card border-left-primary shadow h-100 py-2"}, 
                              m("div", {"class":"card-body"}, 
                                m("div", {"class":"row no-gutters align-items-center"},
                                  [
                                    m("div", {"class":"col mr-2"},
                                      [
                                        m("div", {"class":"text-xs font-weight-bold text-primary text-uppercase mb-1"}, 
                                          " Nombre d'hotes"
                                        ),
                                        m("div", {"class":"h5 mb-0 font-weight-bold text-gray-800"}, 
                                          statistique.objet['nombreHote']
                                        )
                                      ]
                                    ),
                                    m("div", {"class":"col-auto"}, 
                                      m("i", {"class":"fas fa-calendar fa-2x text-gray-300"})
                                    )
                                  ]
                                )
                              )
                            )
                          ),
                          m("div", {"class":"col-xl-3 col-md-6 mb-4"}, 
                            m("div", {"class":"card border-left-primary shadow h-100 py-2"}, 
                              m("div", {"class":"card-body"}, 
                                m("div", {"class":"row no-gutters align-items-center"},
                                  [
                                    m("div", {"class":"col mr-2"},
                                      [
                                        m("div", {"class":"text-xs font-weight-bold text-primary text-uppercase mb-1"}, 
                                          " Paquets"
                                        ),
                                        m("div", {"class":"h5 mb-0 font-weight-bold text-gray-800"}, 
                                          statistique.objet['paquet']
                                        )
                                      ]
                                    ),
                                    m("div", {"class":"col-auto"}, 
                                      m("i", {"class":"fas fa-calendar fa-2x text-gray-300"})
                                    )
                                  ]
                                )
                              )
                            )
                          ),
                        ]
                      ),
                      m("div", {"class":"row"},
                        [
                          m("div", {"class":"col-xl-8 col-lg-7"}, 
                            m("div", {"class":"card shadow mb-4"},
                              [
                                m("div", {"class":"card-header py-3"}, 
                                  m("h6", {"class":"m-0 font-weight-bold text-primary"}, 
                                    "Ports"
                                  )
                                ),
                                m("div", {"class":"card-body"},
                                  [
                                    m("h4", {"class":"small font-weight-bold"},
                                      [
                                        "Port 8000 ",
                                        m("span", {"class":"float-right"}, 
                                          "20%"
                                        )
                                      ]
                                    ),
                                    m("div", {"class":"progress mb-4"}, 
                                      m("div", {"class":"progress-bar bg-danger","role":"progressbar","aria-valuenow":"20","aria-valuemin":"0","aria-valuemax":"100","style":{"width":"20%"}})
                                    ),
                                    m("h4", {"class":"small font-weight-bold"},
                                      [
                                        "Port 8001 ",
                                        m("span", {"class":"float-right"}, 
                                          "40%"
                                        )
                                      ]
                                    ),
                                    m("div", {"class":"progress mb-4"}, 
                                      m("div", {"class":"progress-bar bg-warning","role":"progressbar","aria-valuenow":"40","aria-valuemin":"0","aria-valuemax":"100","style":{"width":"40%"}})
                                    ),
                                    m("h4", {"class":"small font-weight-bold"},
                                      [
                                        "Port 21 ",
                                        m("span", {"class":"float-right"}, 
                                          "60%"
                                        )
                                      ]
                                    ),
                                    m("div", {"class":"progress mb-4"}, 
                                      m("div", {"class":"progress-bar","role":"progressbar","aria-valuenow":"60","aria-valuemin":"0","aria-valuemax":"100","style":{"width":"60%"}})
                                    ),
                                    m("h4", {"class":"small font-weight-bold"},
                                      [
                                        "Port 5000 ",
                                        m("span", {"class":"float-right"}, 
                                          "80%"
                                        )
                                      ]
                                    ),
                                    m("div", {"class":"progress mb-4"}, 
                                      m("div", {"class":"progress-bar bg-info","role":"progressbar","aria-valuenow":"80","aria-valuemin":"0","aria-valuemax":"100","style":{"width":"80%"}})
                                    )
                                  ]
                                )
                              ]
                            )
                          ),
                          m("div", {"class":"col-xl-4 col-lg-5"}, 
                            m("div", {"class":"card shadow mb-4"},
                              [
                                m("div", {"class":"card-header py-3 d-flex flex-row align-items-center justify-content-between"},
                                  [
                                    m("h6", {"class":"m-0 font-weight-bold text-primary"}, 
                                      "Système d'exploitation"
                                    ),
                                    m("div", {"class":"dropdown no-arrow"}, 
                                      m("a", {"class":"dropdown-toggle","href":"#","role":"button","id":"dropdownMenuLink","data-toggle":"dropdown","aria-haspopup":"true","aria-expanded":"false"}, 
                                        m("i", {"class":"fas fa-ellipsis-v fa-sm fa-fw text-gray-400"})
                                      )
                                    )
                                  ]
                                ),
                                m("div", {"class":"card-body"},
                                  [
                                    m("div", {"class":"chart-pie pt-4 pb-2"}, 
                                      m("canvas", {"id":"myPieChart"})
                                    ),
                                    m("div", {"class":"mt-4 text-center small"},
                                      [
                                        m("span", {"class":"mr-2"},
                                          [
                                            m("i", {"class":"fas fa-circle text-primary"}),
                                            " Windows "
                                          ]
                                        ),
                                        m("span", {"class":"mr-2"},
                                          [
                                            m("i", {"class":"fas fa-circle text-success"}),
                                            " Linux "
                                          ]
                                        ),
                                        m("span", {"class":"mr-2"},
                                          [
                                            m("i", {"class":"fas fa-circle text-info"}),
                                            " Mac "
                                          ]
                                        )
                                      ]
                                    )
                                  ]
                                )
                              ]
                            )
                          )
                        ]
                      )
                    ]
                  ),
                  m(footer)
                )
              )
            ),

            m("a", {"class":"scroll-to-top rounded","href":"#page-top"}, 
              m("i", {"class":"fas fa-angle-up"})
            )
        ]
    }
}