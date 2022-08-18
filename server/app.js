const express=require("express"); 

var bodyParser = require('body-parser')

const app = express(); 

var jsonParser = bodyParser.json()

const cors = require('cors');

/*app.use(cors({
    origin: '*'
}));*/

app.use(cors({
        methods: ['GET','POST','DELETE','UPDATE','PUT','PATCH']
}));
    
const redis = require('redis');
const client = redis.createClient(
        {
                socket:{
                        host: '172.16.160.240',
                        port:6379
                },
                password: ''
        }
);

client.on('error', err => {
    console.log('Error ' + err);
});

app.get('/tables', cors(), async (req, res) => {

        await client.connect();

        var hotes = [];
        const keys = await client.json.OBJKEYS('hotes');

        for(const key of keys)
        {
                var chaine = '["'+key+ '"]';
                var contenu = await client.json.get('hotes',{
                        path: chaine
                })

                if(contenu.Port != undefined)
                        contenu.Port = contenu.Port.toString().replace(/,/g, ", ");
                
                if(contenu.Assoc != undefined)
                        contenu.Assoc = contenu.Assoc.toString().replace(/,/g, ", ");

                hotes.push({
                        "ip": key,
                        "contenu": contenu
                        
                }
                )
        
        }

        client.quit();

        console.log("get hotes");

        return res.status(200).send(hotes);

});

app.post('/filtre', cors(), jsonParser, async (req, res) => {

        await client.connect();

        var hotes = [];
        const keys = await client.json.OBJKEYS('hotes');

        for(const key of keys)
        {
                var chaine = '["'+key+ '"]';
                var contenu = await client.json.get('hotes',{
                        path: chaine
                })

               if(
                        key.toLocaleLowerCase().includes(req.body.filtre.toLocaleLowerCase()) ||
                        (contenu.OS != undefined && contenu.OS.toLocaleLowerCase().includes(req.body.filtre.toLocaleLowerCase())) ||
                        (contenu.PE != undefined && contenu.PE == req.body.filtre) ||
                        (contenu.PR != undefined && contenu.PR == req.body.filtre)
                )
                {
                        if(contenu.Port != undefined)
                                contenu.Port = contenu.Port.toString().replace(/,/g, ", ");
                
                        if(contenu.Assoc != undefined)
                                contenu.Assoc = contenu.Assoc.toString().replace(/,/g, ", ");

                        hotes.push({
                                "ip": key,
                                "contenu": contenu
                                
                        })
                }

                else
                {
                        //let ports = await client.hGet(key,'port');

                        /*Je dois m'assurer que element.ports est un array */
                        if(contenu.Port != undefined)                
                        {
                                for(const element of contenu.Port) {
                                       if(element == req.body.filtre)
                                        {
                                                if(contenu.Port != undefined)
                                                        contenu.Port = contenu.Port.toString().replace(/,/g, ", ");
                
                                                if(contenu.Assoc != undefined)
                                                        contenu.Assoc = contenu.Assoc.toString().replace(/,/g, ", ");

                                                hotes.push({
                                                        "ip": key,
                                                        "contenu": contenu
                                                
                                                })
                                        }
                                  
                                }
                        }
                }
        }

        client.quit();

        return res.status(200).send(hotes);
})

app.get('/statistiques', cors(), async (req, res) => {

        await client.connect();

        var hotes = [];
        const keys = await client.json.OBJKEYS('hotes');

        for(const key of keys)
        {
                var chaine = '["'+key+ '"]';
                var contenu = await client.json.get('hotes',{
                        path: chaine
                })

                // if(contenu.Port != undefined)
                //         contenu.Port = contenu.Port.toString().replace(/,/g, ", ");
                
                // if(contenu.Assoc != undefined)
                //         contenu.Assoc = contenu.Assoc.toString().replace(/,/g, ", ");

                hotes.push({
                        "ip": key,
                        "contenu": contenu
                        
                }
                )
        
        }

        var nombreHote = hotes.length;
        var paquet = 0;
        var linux = 0;
        var windows = 0;
        var mac = 0;
        var ports = [];

        hotes.forEach(element => {
                if(element.contenu.PE != undefined)
                        paquet += element.contenu.PE;

                if(element.contenu.OS!= undefined && element.contenu.OS.toLocaleLowerCase().includes('linux')) linux++;

                else if(element.contenu.OS!= undefined && element.contenu.OS.toLocaleLowerCase().includes('windows')) windows++;

                else if(element.contenu.OS!= undefined && element.contenu.OS.toLocaleLowerCase().includes('mac')) mac++;

                /*Je dois m'assurer que element.contenu.ports est un array */
                
                /*for(const port of element.contenu.Port)
                {
                        if(ports["Port "+port] == undefined) ports[port.toString()] = 1;

                        else ports[port.toString()]++;
                }*/
        });

        /*ports.forEach(element => {
             element = (element/nombreHote) * 100;
        });*/

        var statistiques = {
                "nombreHote": nombreHote,
                "paquet": paquet,
                'linux': linux,
                "windows": windows,
                "mac": mac,
                "ports": ports
        };

        client.quit();
        
        return res.status(200).send(statistiques);

});

app.listen(3000, function(){
        console.log("SERVER STARTED ON localhost:3000");     
})
