const express=require("express"); 

const app= express();        //binds the express module to 'app'

app.listen(3000, function(){
        console.log("SERVER STARTED ON localhost:3000");     
})
