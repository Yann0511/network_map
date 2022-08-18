var m = require("mithril")
const server = require("../config/server")

const statistique = {
    error: "",
    displayErrror() {
        return this.error != ""
    },

    getStatistiques() {
        m.request({
            method: "GET",
            url: server.url + "/statistiques",
            
        }).then((result) => {
            statistique.objet = result
            console.log(statistique.objet);
        }, (error) => {
            statistique.error = error.response.message
        })
        return statistique.objet
    },
    objet: {
        "nombreHote": 0,
        "paquet": 0,
        'linux': 0,
        "windows": 0,
        "mac": 0,
        "ports": []
    }
}
module.exports = statistique;