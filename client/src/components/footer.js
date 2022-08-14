var m = require('mithril');

module.exports = {
    view: function(vnode){
        return [
            m("footer", {"class":"sticky-footer bg-white"}, 
            m("div", {"class":"container my-auto"}, 
              m("div", {"class":"copyright text-center my-auto"}, 
                m("span",
                  [
                    "Copyright ",
                    m.trust("&copy;"),
                    " Your Website 2020"
                  ]
                )
              )
            )
          )
        ]
    }
}