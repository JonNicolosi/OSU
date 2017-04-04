var express = require('express');
var path = require('path');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//Including a public directory to serve css files per: http://stackoverflow.com/questions/13395742/can-not-get-css-file
app.use(express.static(path.join(__dirname, 'public')));

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);


function processParams(req) {
  console.log(req.query);
  console.log(req.body);

  var context = {};
  context.queryParams = [];
  context.bodyParams = [];
  context.queryCount = 0;
  context.bodyCount = 0;
  
  for( var param in req.query) {
    context.queryCount++;
    context.queryParams.push({'name': param, 'value': req.query[param] });
  }

  for( var param in req.body) {
    context.bodyCount++;
    context.bodyParams.push({'name': param, 'value': req.body[param] });
  }

  context.methodType = req.method;
  return context;
}


app.get('/', function(req, res) {
  res.render('request', processParams(req));
});

app.post('/', function(req, res) {
  res.render('request', processParams(req));
});

app.use(function(req, res) {
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next) {
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function() {
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});