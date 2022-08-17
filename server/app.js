const express=require("express"); 

const app = express();      

const redis = require('redis');
const client = redis.createClient(
        {
                socket:{
                        host: '127.0.0.1',
                        port:6379
                },
                password: '05110yann'
        }
);

client.on('error', err => {
    console.log('Error ' + err);
});

app.get('/tables', async (req, res) => {

        await client.connect();

        var hotes = [];
        const keys = await client.keys('*.*');

        for(const key of keys)
        {
                hotes.push(
                        {
                                "ip" : key,
                                "os" :  await client.hGet(key,'os'),
                                "pe" :  await client.hGet(key,'pe'),
                                "pr" :  await client.hGet(key,'pr'),
                                "ports" : await client.hGet(key,'ports'),
                                "assoc" :  await client.hGet(key,'assoc'),
                                
                        }
                )
        }

        return res.status(200).send(hotes);

});

app.get('/statistiques', async (req, res) => {

        await client.connect();

        var hotes = [];
        const keys = await client.keys('*.*');

        for(const key of keys)
        {
                hotes.push(
                        {
                                "ip" : key,
                                "os" :  await client.hGet(key,'os'),
                                "pe" :  await client.hGet(key,'pe'),
                                "pr" :  await client.hGet(key,'pr'),
                                "ports" : await client.hGet(key,'port'),
                                "assoc" :  await client.hGet(key,'assoc'),
                                
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
                paquet += element.pr;

                if(element.os.toLocaleLowerCase().includes('linux')) linux++;

                else if(element.os.toLocaleLowerCase().includes('windows')) windows++;

                else if(element.os.toLocaleLowerCase().includes('mac')) mac++;

                /*Je dois m'assurer que element.ports est un array */
                
                for(const port of element.ports)
                {
                        console.log(element.ports[1]);
                        if(ports["Port "+port] == undefined) ports[port.toString()] = 1;

                        else ports[port.toString()]++;
                }
        });

        ports.forEach(element => {
             element = (element/nombreHote) * 100;
        });

        var statistiques = {
                "nombreHote": nombreHote,
                "paquet": paquet,
                'linux': linux,
                "windows": windows,
                "mac": mac,
                "ports": ports
        };

        return res.status(200).send(statistiques);

});

app.listen(3000, function(){
        console.log("SERVER STARTED ON localhost:3000");     
})
