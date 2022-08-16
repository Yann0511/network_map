var express = require('express');
const router = express.Router();

const redis = require('redis');
const client = redis.createClient();

client.on('error', err => {
    console.log('Error ' + err);
});

router.get('/tables', async (req, res) => {

    //console.log(req.user);
    const hotes = await client.hmGet('*')  
})

