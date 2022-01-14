// Server for communicating with a client
// Referencing https://cs.lmu.edu/~ray/notes/jsnetexamples/

// The Net module provides a way of creating TCP servers and TCP clients.
// Referencing https://nodejs.org/api/net.html
const net = require('net');

// socket: Automatically set as a listener for the 'connection' event.
// For each client that connects, set up a listener.
const server = net.createServer((socket) => {
    console.log('Client Connected: from', socket.remoteAddress, 'port', socket.remotePort);

    // When data is received on the connection, write back to the socket with new information
    socket.on('data', (buffer) => {
        console.log('Request from', socket.remoteAddress, 'port', socket.remotePort);
        socket.write(`${buffer.toString('utf-8').toUpperCase()}\n`);
    });
    // When the client disconnects, print notice.
    socket.on('end', () => {
        console.log('Client Disconnected: Closed', socket.remoteAddress, 'port', socket.remotePort);
    });
});

// Set this property to reject connections when the server's connection count gets high.
server.maxConnections = 20;
// Async function to start a server listening for connections
// Note that this call will fail if another server is already using the same port to listen
server.listen(59898);