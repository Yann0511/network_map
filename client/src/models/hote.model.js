var m = require("mithril")
const server = require("../config/server")

const hote = {
    error: "",
    displayErrror() {
        return this.error != ""
    },

    filtreHotes(value) {
       m.request({
        method: "POST",
        url: server.url + "/filtre",
        body: {filtre: value}
       }).then((result) => {
            hote.list = result
            console.log(hote.list);
       }, (error) => {
        hote.error = error.response.message
       })
       return hote.list
    },

    getHotes() {
        m.request({
            method: "GET",
            url: server.url + "/tables",
            
        }).then((result) => {
            hote.list = result
            console.log(hote.list);
        }, (error) => {
            hote.error = error.response.message
        })
        return hote.list
    },
    list: []
}
module.exports = hote;