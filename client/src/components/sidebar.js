var m = require('mithril');

module.exports = {
    view: function(vnode){
        return [
            m("ul", {"class":"navbar-nav bg-gradient-primary sidebar sidebar-dark accordion","id":"accordionSidebar"},
            [
                m("a", {"class":"sidebar-brand d-flex align-items-center justify-content-center","href":"index.html"},
            [
        m("div", {"class":"sidebar-brand-icon rotate-n-15"}, 
          m("i", {"class":"fas fa-laugh-wink"})
        ),
        m("div", {"class":"sidebar-brand-text mx-3"}, 
          "Network "
        )
      ]
    ),
    m("hr", {"class":"sidebar-divider my-0"}),
    m("li", {"class":"nav-item"}, 
      m("a", {"class":"nav-link","href":"index.html"},
        [
          m("i", {"class":"fas fa-fw fa-tachometer-alt"}),
          m("span", 
            "Statistiques"
          )
        ]
      )
    ),
    m("li", {"class":"nav-item active"}, 
      m("a", {"class":"nav-link","href":"tables.html"},
        [
          m("i", {"class":"fas fa-fw fa-table"}),
          m("span", 
            "Tables"
          )
        ]
      )
    ),
    m("hr", {"class":"sidebar-divider d-none d-md-block"}),
    m("div", {"class":"text-center d-none d-md-inline"}, 
      m("button", {"class":"rounded-circle border-0","id":"sidebarToggle"})
    )
  ]
)
        ]
    }
}