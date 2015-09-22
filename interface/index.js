#!/usr/bin/env node
var app=require("express")(),
    http=require("http").Server(app),
    io=require("socket.io")(http),
    child_process=require("child_process"),
    shlex=require("shell-quote").parse;


var HTTPPORT=8012;


var conn=null,ai=new AI(),ai2=new AI();

function AI(){
	var proc=null;
	var cmd=null;
	var buf=null;
	var lines=[];
	var lineslisteners=[];

	this.reset=function(){
		console.log("AI_STOP\n");
		if(proc)proc.kill("SIGTERM");
		proc=null;
		cmd=null;
		buf=null;
		lines=[];
		lineslisteners=[];
	}

	this.start=function(command){
		this.reset();
		cmd=command;
		var lexed=shlex(cmd);
		console.log("starting");
		proc=child_process.spawn(lexed[0],lexed.slice(1),{stdio:["pipe","pipe","inherit"]});
		console.log("AI_START");
		var self=this;
		proc.on("error",function(err){
			if(err){
				if(conn)conn.emit("alert",err.message);
				console.log(err);
				self.reset();
				return;
			}
		});
		proc.stdout.on("data",function(data){
			console.log("AI_OUT: "+String(data).replace(/\n$/,""));
			var idx;
			buf+=data;
			idx=buf.indexOf("\n");
			while(idx!=-1){
				lines.push(buf.slice(0,idx));
				buf=buf.slice(idx+1);
				idx=buf.indexOf("\n");
			}
			while(lines.length&&lineslisteners.length){
				lineslisteners.shift()(lines.shift());
			}
		});
		buf="";
	}

	this.writeln=function(text){
		console.log("AI_IN: "+text);
		proc.stdin.write(text+"\n");
	}

	this.getline=function(){
		var line;
		if(lines.length){
			line=lines.shift();
			conn.emit("ailine",line);
			console.log(" sent: "+line);
		} else lineslisteners.push(function(line){
			conn.emit("ailine",line);
			console.log(" sent: "+line);
		});
	}

	this.status=function(){
		if(proc==null)conn.emit("aistatus","Not running");
		else conn.emit("aistatus","Running: "+cmd);
	}
}

app.get('/style.css', function(req, res) {
	res.sendFile(__dirname + "/style.css");
});
app.get('/client.js', function(req, res) {
	res.sendFile(__dirname + "/client.js");
});

app.get("/",function(req,res){
	res.sendFile(__dirname+"/index.html");
});
var aiVsAi=false;
var turn=0;
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
		ai.reset();
		if(aiVsAi)ai2.reset();
	});
	conn.on("aistart2",function(cmd,cmd2){
		ai.start(cmd);
		ai2.start(cmd2);
		aiVsAi=true;
		turn=0;
	});
	conn.on("aistart",function(cmd){
		if(aiVsAi)ai.reset();
		ai.start(cmd);
		aiVsAi=false;
	});
	conn.on("aistop",function(){
		ai.reset();
		if(aiVsAi)ai2.reset();
	});
	conn.on("aiwriteln",function(text){
		if(!aiVsAi)ai.writeln(text);
		else{
			if(turn==0)ai.writeln(text);
			else ai2.writeln(text);
		}
	});
	conn.on("aigetline",function(){
		if(aiVsAi){
			if(turn==0)ai.getline();
			else ai2.getline();
			turn=!turn;
		}else{
			ai.getline();
		}
	});
	conn.on("aistatus",function(){
		ai.status();
	});
});


http.listen(HTTPPORT,function(){
	console.log("Listening on http://localhost:"+HTTPPORT);
});
