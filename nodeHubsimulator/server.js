'use strict';
var express = require("express");
var cors = require("cors");
var bodyParser = require("body-parser");
var unirest = require('unirest');

var app = express();

var switchstate = [
    {
        "state": 0     
    }
];


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.post('/', function (req, res) {
    console.log(`${req.method} request for '${req.url}' - ${JSON.stringify(req.body)}`);
    switchstate = req.body.state;
   
    console.log(switchstate);
});

app.use(express.static("./public"));
app.use(cors());

app.get("/switch-api", function (req, res) {
    switchstate = [
        {
            "state": req.query.name
        }
    ];
    if (req.query.name.toString() == 'off') {
        unirest.post('http://192.168.1.60:9070/off??')
            .end(function (response) {
                console.log(response.body.state);
            });
        console.log("posted off");
    }else {
        unirest.post('http://192.168.1.60:9070/on??')
            .end(function (response) {
                console.log(response.body.state);
            });
        console.log("posted on");
    }
       console.log(switchstate);
       res.json(switchstate);
});


app.listen(3000);

console.log("Express app running on port 3000");

module.exports = app;