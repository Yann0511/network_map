var m = require('mithril');

module.exports = {
    view: function(vnode){
        return [
            m("nav", {"class":"navbar navbar-expand navbar-light bg-white topbar mb-4 static-top shadow"},
            [
              m("form", {"class":"form-inline"}, 
                m("button", {"class":"btn btn-link d-md-none rounded-circle mr-3","id":"sidebarToggleTop"}, 
                  m("i", {"class":"fa fa-bars"})
                )
              ),
              m("form", {"class":"d-none d-sm-inline-block form-inline mr-auto ml-md-3 my-2 my-md-0 mw-100 navbar-search"}, 
                m("div", {"class":"input-group"},
                  [
                    m("input", {"class":"form-control bg-light border-0 small","type":"text","placeholder":"Search for...","aria-label":"Search","aria-describedby":"basic-addon2"}),
                    m("div", {"class":"input-group-append"}, 
                      m("button", {"class":"btn btn-primary","type":"button"}, 
                        m("i", {"class":"fas fa-search fa-sm"})
                      )
                    )
                  ]
                )
              )
            ]
          )
        ]
    }
}