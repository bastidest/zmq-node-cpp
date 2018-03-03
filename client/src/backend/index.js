/* eslint-disable no-console */
const zmq = require('zeromq');

let socket = zmq.socket('dealer');

// connect to the router

socket.connect('tcp://localhost:3333');

console.log('request: start');
socket.send('start');

setInterval(() => {
  console.log('request: cmd_1');
  socket.send('cmd_1');
}, 10000);

socket.on('message', function(msg){
  console.log('response: %s', msg.toString());
});