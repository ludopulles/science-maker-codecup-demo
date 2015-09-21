var WID=7,HEI=6;
var aicmds=["./player1","./player2","./player3","./TNTiv3a -d 8","./TNTiv3a -d 10","./TNTiv3a -d 11","./TNTiv3a -d 12","./TNTiv3a2 -d 8","./TNTiv3a2 -d 10","./TNTiv3a2 -d 11","./TNTiv3a2 -d 12","./voer14_doc","./mc"];
var colheight,BD;

var aigoesfirst;

var socket=io();
socket.on("alert",function(msg){alert(msg);});
socket.on("jseval",function(msg){eval(msg);});
socket.on("ailine",function(line){
	aigetmove_cbs.shift()(line);
});
socket.on("aistatus",function(msg){
	document.getElementById("aistatus").innerHTML=msg;
});

function init(){
	var table=document.getElementById("boardtable");
	var x,y;
	var tbody,tr,td;
	var div;

	for(x=0;x<WID;x++){
		table.appendChild(document.createElement("colgroup"));
	}
	tbody=document.createElement("tbody");
	for(y=0;y<HEI;y++){
		tr=document.createElement("tr");
		for(x=0;x<WID;x++){
			td=document.createElement("td");
			td.classList.add("cell");
			tr.appendChild(td);
			(function(x,y){
				td.addEventListener("mouseover",function(ev){
					if(colheight[x]<HEI){
						table.children[x].classList.add("colhover");
					}
				});
				td.addEventListener("mouseout",function(ev){
					table.children[x].classList.remove("colhover");
				});
				td.addEventListener("click",function(ev){
					if(usergetmove_cb==null){
						alert("usergetmove_cb = null...?");
						throw new Error("usergetmove_cb = null in td click");
					}
					if(colheight[x]<HEI){
						usergetmove_cb(x);
					}
				});
			})(x,y);
		}
		tbody.appendChild(tr);
	}
	table.appendChild(tbody);


	colheight=iota(WID,0,0);
	BD=iota(WID*HEI,0,0);

	var select=document.getElementById("aicmdselect");
	aicmds.forEach(function(cmd,i){
		var option=document.createElement("option");
		option.value=cmd;
		if(i==7)option.setAttribute("selected","");
		option.innerHTML=cmd.replace(/^.*\//,"");
		select.appendChild(option);
	});


	setInterval(function(){
		socket.emit("aistatus");
	},4000);
}

function iota(len,start,incr){ //defaults start=0 incr=1
	var a=new Array(len);
	var i;
	for(i=0;i<len;i++)a[i]=start+i*incr;
	return a;
}

function stonesetcolour(x,y,c){
	var e=document.getElementById("boardtable").lastElementChild.children[HEI-1-y].children[x];
	if(!e.firstElementChild)throw new Error("stone color while no ston;e barf");
	e.firstElementChild.classList[c?"add":"remove"]("colour")
}

function setstone(x,y,p){ //pass p=0 to clear
	BD[WID*y+x]=p;
	var e=document.getElementById("boardtable").lastElementChild.children[HEI-1-y].children[x];
	if(e.firstElementChild)e.removeChild(e.firstElementChild);
	if(p!=1&&p!=2)return;
	var span=document.createElement("span");
	if(p==1)span.classList.add("X");
	else if(p==2)span.classList.add("O");
	span.setAttribute("style","top:-150px;opacity:0");
	setTimeout(function(){span.setAttribute("style","");},0);
	e.appendChild(span);
}

function addstone(col,p){
	if(colheight[col]>=HEI)throw new Error("addstone() on full column");
	setstone(col,colheight[col],p);
	colheight[col]++;
}

function removestone(col){
	if(colheight[col]<=0)throw new Error("removestone() on empty column");
	colheight[col]--;
	setstone(col,colheight[col],0);
}

function newgamevsai(){
	var i;
	aiVsAi=false;
	for(i=0;i<WID;i++){
		while(colheight[i])removestone(i);
	}
	var cmd=document.getElementById("aicmdselect").value;
	socket.emit("aistart",cmd);
	socket.emit("aistatus");
	if(document.getElementById("aistarts").checked){
		aigoesfirst=true;
		socket.emit("aiwriteln","Start");
		aigetmove(aigotmove);
	} else {
		aigoesfirst=false;
		usergetmove(usergotmove);
	}
}

function newaivsai(){
	aiVsAi=true;
	var i;
	for(i=0;i<WID;i++){
		while(colheight[i])removestone(i);
	}
	var cmd=document.getElementById("aicmdselect").value;
	socket.emit("aistart2",cmd,cmd);
	socket.emit("aistatus");
	socket.emit("aiwriteln","Start");
	aigetmove(aigotmove);
	document.getElementById("ainextmove").style.display="inline";
}

function aistop(){
	socket.emit("aistop");
	socket.emit("aistatus");
	var boardscreen=document.getElementById("boardscreen");
	boardscreen.removeAttribute("style");
}
var lastMove;
var turn=0;
var aiVsAi=false;
function aigotmove(col,reqtime){
	lastMove=col;
	turn=!turn;
	setTimeout(function(){
		if(aiVsAi){
			addstone(col,turn?1:2);
			//TODO enable button
		}
		else addstone(col,aigoesfirst?1:2);
		setTimeout(function(){
			if(!docheckwin())usergetmove(usergotmove);
		},350);
	},500-Math.min(500,new Date().getTime()-reqtime.getTime()));
}

function doNextMove(){
	usergotmove(lastMove);
}

function usergotmove(col){
	if(!aiVsAi)addstone(col,aigoesfirst?2:1);
	socket.emit("aiwriteln",(col+1).toString());
	setTimeout(function(){
		if(!docheckwin())aigetmove(aigotmove);
	},350);
}

var aigetmove_cbs=[];
function aigetmove(cb){
	var now=new Date();
	aigetmove_cbs.push(function(res){cb(res-1,now);});
	socket.emit("aigetline");
}

var usergetmove_cb=null;
function usergetmove(cb){
	var boardscreen=document.getElementById("boardscreen");
	boardscreen.style.display="none";
	usergetmove_cb=function(){
		boardscreen.removeAttribute("style");
		cb.apply(null,arguments);
	};
}

function docheckwin(){
	var win=checkwin();
	if(win[0]){
		var alertstring;
		if(win[0]==(aigoesfirst?1:2)){
			alertstring="The AI has won... Better next time!";
		} else if(win[0]==(aigoesfirst?2:1)){
			alertstring="You have conquered the AI! Good job!";
		} else {
			alertstring="? win = "+JSON.stringify(win)+", aigoesfirst = "+aigoesfirst;
		}
		setTimeout(function(){alert(alertstring);},1);
		win[1].forEach(function(tup){
			stonesetcolour(tup[0],tup[1],true);
		});
		socket.emit("aistop");
		socket.emit("aistatus");
	}
	return !!win[0];
}

function checkwin(){
	var x,y,r1,r2;
	var v;
	for(y=0;y<HEI;y++){ //horizontal
		r1=r2=0;
		for(x=0;x<WID;x++){
			if(BD[WID*y+x]==1){r1++;r2=0;}
			else if(BD[WID*y+x]==2){r1=0;r2++;}
			else r1=r2=0;
			if(r1==4)return [1,[[x-3,y],[x-2,y],[x-1,y],[x,y]]];
			if(r2==4)return [2,[[x-3,y],[x-2,y],[x-1,y],[x,y]]];
		}
	}
	for(x=0;x<WID;x++){ //vertical
		r1=r2=0;
		for(y=0;y<HEI;y++){
			if(BD[WID*y+x]==1){r1++;r2=0;}
			else if(BD[WID*y+x]==2){r1=0;r2++;}
			else r1=r2=0;
			if(r1==4)return [1,[[x,y-3],[x,y-2],[x,y-1],[x,y]]];
			if(r2==4)return [2,[[x,y-3],[x,y-2],[x,y-1],[x,y]]];
		}
	}
	for(y=0;y<HEI-3;y++){
		for(x=0;x<WID-3;x++){
			v=BD[WID*y+x]; //diagonal \.
			if(v!=0&&BD[WID*(y+1)+x+1]==v&&BD[WID*(y+2)+x+2]==v&&BD[WID*(y+3)+x+3]==v){
				return [v,[[x,y],[x+1,y+1],[x+2,y+2],[x+3,y+3]]];
			}
			v=BD[WID*y+x+3]; //diagonal /
			if(v!=0&&BD[WID*(y+1)+x+2]==v&&BD[WID*(y+2)+x+1]==v&&BD[WID*(y+3)+x]==v){
				return [v,[[x+3,y],[x+2,y+1],[x+1,y+2],[x,y+3]]];
			}
		}
	}
	return [0,[]];
}
