#!/usr/bin/env node
var app=require("express")(),
    http=require("http").Server(app),
    io=require("socket.io")(http),
    child_process=require("child_process"),
    shlex=require("shell-quote").parse;


var HTTPPORT=8012;


var conn=null,proc=null,aicmd=null,aibuf=null,ailines=[],ailineslisteners=[];


function resetai(){
	console.log("AI_STOP\n");
	if(proc)proc.kill("SIGTERM");
	proc=null;
	aicmd=null;
	aibuf=null;
	ailines=[];
	ailineslisteners=[];
}

app.get("/",function(req,res){
	res.sendFile(__dirname+"/index.html");
});

io.on("connection",function(_conn){
	if(conn!=null){
		_conn.emit("alert","Another connection already active!");
		_conn.emit("jseval","window.close();");
		_conn.disconnect(true);
		return;
	}
	console.log("(connect)");
	conn=_conn;
	conn.on("disconnect",function(){
		console.log("(disconnect)");
		conn.disconnect(); //just to be sure
		conn=null;
		resetai();
	});
	conn.on("aistart",function(cmd){
		resetai();
		aicmd=cmd;
		var lexed=shlex(cmd);
		proc=child_process.spawn(lexed[0],lexed.slice(1),{stdio:["pipe","pipe","inherit"]});
		console.log("AI_START");
		proc.on("error",function(err){
			if(err){
				if(conn)conn.emit("alert",err.message);
				console.log(err);
				resetai();
				return;
			}
		});
		proc.stdout.on("data",function(data){
			console.log("AI_OUT: "+String(data).replace(/\n$/,""));
			var idx;
			aibuf+=data;
			idx=aibuf.indexOf("\n");
			while(idx!=-1){
				ailines.push(aibuf.slice(0,idx));
				aibuf=aibuf.slice(idx+1);
				idx=aibuf.indexOf("\n");
			}
			while(ailines.length&&ailineslisteners.length){
				ailineslisteners.shift()(ailines.shift());
			}
		});
		aibuf="";
	});
	conn.on("aistop",function(){
		resetai();
	});
	conn.on("aiwriteln",function(text){
		console.log("AI_IN: "+text);
		proc.stdin.write(text+"\n");
	});
	conn.on("aigetline",function(){
		var line;
		if(ailines.length){
			line=ailines.shift();
			conn.emit("ailine",line);
			console.log(" sent: "+line);
		} else ailineslisteners.push(function(line){
			conn.emit("ailine",line);
			console.log(" sent: "+line);
		});
	});
	conn.on("aistatus",function(){
		if(proc==null)conn.emit("aistatus","Not running");
		else conn.emit("aistatus","Running: "+aicmd);
	});
});


http.listen(HTTPPORT,function(){
	console.log("Listening on http://localhost:"+HTTPPORT);
});
