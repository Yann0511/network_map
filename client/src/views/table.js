var m = require('mithril');
const sidebar = require('../components/sidebar');
const navbar = require('../components/navbar');
const footer = require('../components/footer');


module.exports = {
    view: function(vnode){
        return [
          m("p", {"hello world"})
            // m("div", {"id":"wrapper"},
            //   m(sidebar),

            //   m("div", {"class":"d-flex flex-column","id":"content-wrapper"}, 
            //     m("div", {"id":"content"},
            //         m(navbar),

            //         m("div", {"class":"container-fluid"}, 
            //         m("div", {"class":"card shadow mb-4"},
            //           [
            //             m("div", {"class":"card-header py-3"}, 
            //               m("h6", {"class":"m-0 font-weight-bold text-primary"}, 
            //                 "DataTables"
            //               )
            //             ),
            //             m("div", {"class":"card-body"}, 
            //               m("div", {"class":"table-responsive"}, 
            //                 m("table", {"class":"table table-bordered","id":"dataTable","width":"100%","cellspacing":"0"},
            //                   [
            //                     m("thead", 
            //                       m("tr",
            //                         [
            //                           m("th", 
            //                             "Adresse ip"
            //                           ),
            //                           m("th", 
            //                             "Systeme d'exploitation"
            //                           ),
            //                           m("th", 
            //                             "Ports ouvert"
            //                           ),
            //                           m("th", 
            //                             "Paquet envoyé"
            //                           ),
            //                           m("th", 
            //                             "Paquet reçu"
            //                           ),
            //                           m("th", 
            //                             "Associés"
            //                           )
            //                         ]
            //                       )
            //                     ),
            //                     m("tfoot", 
            //                       m("tr",
            //                         [
            //                           m("th", 
            //                             "Adresse ip"
            //                           ),
            //                           m("th", 
            //                             "Systeme d'exploitation"
            //                           ),
            //                           m("th", 
            //                             "Ports ouvert"
            //                           ),
            //                           m("th", 
            //                             "Paquet envoyé"
            //                           ),
            //                           m("th", 
            //                             "Paquet reçu"
            //                           ),
            //                           m("th", 
            //                             "Associés"
            //                           )
            //                         ]
            //                       )
            //                     ),
            //                     m("tbody",
            //                       [
            //                         m("tr",
            //                           [
            //                             m("td", 
            //                               "192.168.8.177"
            //                             ),
            //                             m("td", 
            //                               "Windows 12"
            //                             ),
            //                             m("td", 
            //                               "21, 5000, 8000"
            //                             ),
            //                             m("td", 
            //                               "61"
            //                             ),
            //                             m("td", 
            //                               "60"
            //                             ),
            //                             m("td", 
            //                               "192.168.8.176, 192.168.8.178, 192.168.8.117"
            //                             )
            //                           ]
            //                         ),
                                    
            //                       ]
            //                     )
            //                   ]
            //                 )
            //               )
            //             )
            //           ]
            //         ),

            //         m(footer)
            //         )
            //     )
            //   )
            // ),

            // m("a", {"class":"scroll-to-top rounded","href":"#page-top"}, 
            //   m("i", {"class":"fas fa-angle-up"})
            // )

        ]
    }
}