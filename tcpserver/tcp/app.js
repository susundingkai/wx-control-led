'use strict';
var net = require('net');
var ws = require('nodejs-websocket');
var server = net.createServer();
//聚合所有客户端
var sockets = [];
var client = new net.Socket();
var c
//接受新的客户端连接
server.on('connection', function (socket) {
    socket.setEncoding("utf8");
    console.log('got a new connection');
    sockets.push(socket);
    //从连接中读取数据
    socket.on('data', function (data) {
        console.log('got data:', data);
	if(data='arduino'){
	client=socket
}
        //广播数据
        //每当一个已连接的用户输入数据，就将这些数据广播给其他所有已连接的用户
               // socket.write(c);

        //删除被关闭的连接
        socket.on('close', function () {
	    client=0
            console.log('connection closed');
            var index = sockets.indexOf(socket);
            sockets.splice(index, 1);
        });
    });
});

server.on('error', function (err) {
    console.log('Server error:', err.message);
});

server.on('close', function () {
    console.log('Server closed');
});

server.listen(4000);



console.log("开始建立连接...")
var servers = ws.createServer(function (conn) {
    conn.on("text", function (str) {
        var a = []
        a = str.split('@')
        if (a[0] == 'wx') {
            console.log("手机客户端已上线")
            servers.connections.forEach(function (conn) {
                conn.sendText("手机客户端已上线")
            })
        }
        else if(a[0]='data'){
	if(client)
	client.write(a[1])
	 }
    })
    conn.on("close", function (code, reason) {
        console.log("关闭连接")
    })
    conn.on("error", function (code, reason) {
        console.log("异常关闭")
    })
}).listen(8001)
console.log("WebSocket建立完毕")
