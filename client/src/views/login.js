var m = require("mithril");
const jwt = require('../config/jwt');
const {
    mountRoutes
} = require("../mounter");
const User = require('../models/users');


const credential = {
    check: 0,
    error: "",
    errorDisplay() {
        return credential.error != "" ? "" : "none"
    },
    canSubmit() {
        return credential.email != "" && credential.password != ""
    },
    _username: "",
    get username() {
        return this._username;
    },
    set username(value) {
        this._username = value;
    },
    _password: "",
    get password() {
        return this._password;
    },
    set password(value) {
        this._password = value;
    },
    login(e) {
        e.preventDefault();
        for(var user of User){
            if((user.username == credential.username) && (user.password == credential.password)){
                jwt.token = credential.username + "-" + credential.password;
                mountRoutes(),
                credential.check++;
            }
        }
        if(credential.check == 0){
            credential.error = "Erreur de login"
        }
    }
}

module.exports = {
    view: function(vnode){
        return [
          m("div", {
            "class": "justify-content-center mt-5"
          }, [
            m("div", {
              "class": "row"
            }, [
              m("div", {
                "class": "col-4"
              }),
              m("div", {
                "class": "col-4"
              },[
                m("p", {"class": "text-center mb-3"}, "Connexion"),
                m("div", {
                  "class": "card"
                },[
                  m("div", {
                    "class": ""
                  }, [
                    m("a", {"class":"navbar-brand","href":"#"}, 
                      m("img", {"src":"/docs/5.2/assets/brand/bootstrap-logo.svg","alt":"","width":"30","height":"24"})
                    ),
                    m("h6", {
                      "class": "text-center"
                    }, "SWITCHSAB")
                  ]),
                  m("div", {
                    "class": "card-body"
                  }, [
                    m("div", {
                      "class": "login_form mx-auto"
                    }, [
                        m("form",
                        [
                          m("div", {"class":"mb-3"},
                            [
                              m("label", {"class":"form-label"}, 
                                "Nom d'utilisateur"
                              ),
                              m("input", {
                                "class":"form-control",
                                "type":"text",
                                "placeholder": "John Doe",
                                oninput: function(e) {
                                  credential.username = e.target.value
                                },
                                value: credential.username
                              }),
                            ]
                          ),
                          m("div", {"class":"mb-3"},
                            [
                              m("label", {"class":"form-label"}, 
                                "Mot de passe"
                              ),
                              m("input", {
                                "class":"form-control",
                                "type":"password",
                                "placeholder": "Entrez votre mot de passe",
                                oninput: function(e) {
                                  credential.password = e.target.value
                                },
                                value: credential.password
                              })
                            ]
                          ),
                          m(".alert.alert-danger[role='alert']", {
                            "style": {
                                "display": credential.errorDisplay()
                            }
                          }, credential.error),
                          m("button", {
                            "class":"btn btn-primary btn_login mb-3",
                            "type":"submit",
                            disabled: !credential.canSubmit(),
                            onclick: credential.login
                          }, 
                            "Se connecter"
                          ),
                          m("div", {"class":"text-center"},
                            [
                              " Pas de compte ? ",
                              m(m.route.Link, {
                                class:"",
                                href:"/register"
                                }, 
                                "Créer un compte"
                              )
                            ]
                          )
                        ]
                      )
                    ])
                  ])
                ])
              ]),
              m("div", {
                "class": "col-4"
              })
            ])
          ])
        ]
    }
}