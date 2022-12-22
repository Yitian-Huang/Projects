/**
 * 
 */
 
 

 function f1(){
	var x1http = new XMLHttpRequest();
	x1http.onload = function() {
		document.getElementById("home").style.display = "none";
		document.getElementById("title").style.display = "block";
		var obj=JSON.parse(this.responseText);
 		document.getElementById("tick").innerHTML = obj.ticker;
 		document.getElementById("inf").innerHTML = obj.name+"<br>"+obj.exchange;
 		document.getElementById("minf").innerHTML = "<strong>IPO Date: </strong>"+obj.ipo
 													+"<br><strong>Market Cap ($M):</strong> "+obj.marketCapitalization
 													+"<br><strong>Share Outstanding: </strong>"+obj.shareOutstanding
 													+"<br><strong>Website: </strong>"+obj.weburl
 													+"<br><strong>Phone: </strong>"+obj.phone;
 		
 	};
	x1http.open("GET", "https://finnhub.io/api/v1/stock/profile2?symbol="+(document.getElementById("ticker").value)
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg", true);
 	x1http.send();
 
	var x2http=new XMLHttpRequest();
 	x2http.onload = function(){
	var p =JSON.parse(this.responseText);
	document.getElementById("pr").innerHTML = "Summary<br><hr>High Price: "+p.h+"<br>Low Price: "
												+ p.l+"<br>Open Price: "+p.o+"<br>Close Price: "+p.pc+"<hr>";
	
	};
	x2http.open("GET", "https://finnhub.io/api/v1/quote?symbol="+(document.getElementById("ticker").value) 
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg", true);
	x2http.send();
};

function f2(){
	document.getElementById("home").style.display = "block";
	document.getElementById("title").style.display = "none";
	
};

function f3(){
	var x1http = new XMLHttpRequest();
	x1http.onload = function() {
		document.getElementById("home").style.display = "none";
		document.getElementById("title").style.display = "block";
		var obj=JSON.parse(this.responseText);
 		document.getElementById("tick").innerHTML = obj.ticker;
 		document.getElementById("inf").innerHTML =obj.name+"<br>"+obj.exchange
 		document.getElementById("minf").innerHTML = "<strong>IPO Date: </strong>"+obj.ipo
 													+"<br><strong>Market Cap ($M):</strong> "+obj.marketCapitalization
 													+"<br><strong>Share Outstanding: </strong>"+obj.shareOutstanding
 													+"<br><strong>Website: </strong>"+obj.weburl
 													+"<br><strong>Phone: </strong>"+obj.phone;
 

 		
 	};
	x1http.open("GET", "https://finnhub.io/api/v1/stock/profile2?symbol="+(document.getElementById("ticker").value)
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg", true);
 	x1http.send();
 	
 	var x2http=new XMLHttpRequest();
 	x2http.onload = function(){
	var p =JSON.parse(this.responseText);
	var cha = p.d;
	var d = new Date();
	if(cha<0){
		document.getElementById("time").style.color = "red";
		document.getElementById("lp").style.color = "red";
		document.getElementById("op").style.color = "red";
		document.getElementById("lp").innerHTML = p.l;
		document.getElementById("op").innerHTML ="<i class=\"fa fa-caret-down\" aria-hidden=\"true\"></i>"
												+p.d+"("+p.dp+"%)";
	
	}
	else{
		document.getElementById("lp").innerHTML = p.l;
		document.getElementById("op").innerHTML ="<i class=\"fa fa-caret-up\" aria-hidden=\"true\"></i>"
												+p.d+"("+p.dp+"%)";

	}
	
	document.getElementById("time").innerHTML = d;
	hour = d.getHours();
	if(hour<6||hour>13){
		document.getElementById("market").innerHTML = "Market is closed";
	}else{
		document.getElementById("market").innerHTML = "Market is open";
	}
	document.getElementById("pr").innerHTML = "Summary<br><hr><div style=\"text-align:left; width:10%; margin:auto\"><strong>High Price: "
												+p.h.toFixed(2)+"<br>Low Price: "
												+p.l.toFixed(2)+"<br>Open Price: "
												+p.o.toFixed(2)+"<br>Close Price: "
												+p.pc.toFixed(2)+"</strong></div><hr>";
	
	};
	x2http.open("GET", "https://finnhub.io/api/v1/quote?symbol="+(document.getElementById("ticker").value) 
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg", true);
	x2http.send();

	
}

function buy(){
	var amount = document.getElementById("quantity").value;
	if(amount<=0){
		alert("FAILED: Purchase not possible");
	}
	else{
		var x1http = new XMLHttpRequest();
		var prc = amount*document.getElementById("lp").innerHTML;
		x1http.onload = function() {
			var obj=JSON.parse(this.responseText);
			if(obj.result==="true"){
				alert("Bought "+amount+" shares of "+document.getElementById("tick").innerHTML+" for "+prc.toFixed(2));
			}
			else{
				alert("FAILED: Purchase not possible");
			}
			
			document.getElementById("quantity").value='';
	 		
	 	};
		x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/buy?username="
				+localStorage.getItem("username")+
				"&amount="+amount+
				"&prc="+prc+
				"&ticker="+document.getElementById("tick").innerHTML,true)
	 	x1http.send();
	}
}


const getname = async(ti) =>{
	const res = await fetch("https://finnhub.io/api/v1/stock/profile2?symbol="+ti
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg");
	const data = await res.json();
	return data;
}

const getquote = async(ti) =>{
	const res = await fetch("https://finnhub.io/api/v1/quote?symbol="+ti
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg");
	const data = await res.json();
	return data;
}


async function getAll(){
	var x1http = new XMLHttpRequest();
	var obj;
	x1http.onload = function(){
		obj=JSON.parse(this.responseText);
		document.getElementById("ba").innerHTML= "Cash Balance:$"+obj.toFixed(2);
	}
	x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/amount?username="+localStorage.getItem("username"),true);
	x1http.send();
	
	
	var x2http = new XMLHttpRequest();
	x2http.onload = async function(){
		var arr=JSON.parse(this.responseText);
		var loc = document.getElementById("all");

		for(let i = 0; i < arr.length; i++){
			var x = await getname(arr[i].ticker);
			var y = await getquote(arr[i].ticker);
			var avg=(arr[i].cost/arr[i].quantity).toFixed(2);
			var nme=arr[i].ticker;
			loc.innerHTML+="<div style=\" border: 3px solid #EFEFEF; height:22px; background-color:#EFEFEF\"><span style=\"font-size:18px\">"+nme+"-"+x.name+"</span></div>";
			var ctt="";
			ctt+=
			"<div style=\" border: 3px solid #EFEFEF;height:120px\">"
			+"<div style= \"width:20%; margin-left:150px;float:left;padding-top:30px\">"
			+"<span>Quantity:<br>Avg. Cost/Share<br>Total Cost:</span><br>"+"</div>"
			+"<div style= \"width:10%; margin-left:10px;float:left;padding-top:30px\">"
			+"<span>"+arr[i].quantity+"<br>"+avg+"<br>"+(arr[i].cost).toFixed(2)+"</span><br>"+"</div>"
			+"<div style= \"width:20%; margin-left:10px;float:left;padding-top:30px\">"
			+"<span>Change:<br>Current Price:<br>Market Value:</span><br>"+"</div>"
			+"<div style= \"width:20%; margin-left:10px;float:left;padding-top:30px\">";
			if(y.d<0){
				ctt+="<span style=\"color:red\">"
				+"<i class=\"fa fa-caret-down\" aria-hidden=\"true\"></i>"
				+y.d+"</span><span><br>"+y.c+"<br>"
				+(y.c*arr[i].quantity).toFixed(2)+"</span><br>"+"</div>"+"</div>";
			}
			else{
				ctt+="<span style=\"color:green\">"
				+"<i class=\"fa fa-caret-up\" aria-hidden=\"true\"></i>"
				+y.d+"</span><span><br>"+y.c+"<br>"
				+(y.c*arr[i].quantity).toFixed(2)+"</span><br>"+"</div>"+"</div>";
				
			}
			localStorage.setItem(nme,y.c);
			ctt+="<div style=\"  border: 3px solid #EFEFEF; height:80px; background-color:#EFEFEF\">"
			+"<form style=\"text-align:center\" action=\"javascript:void(0);\" onsubmit=\"sub('"+nme+"')\">"
			+"<label for=\"quant-"+nme+"\">Quantity:</label>"
			+"<input type=\"number\" id=\"quant-"+nme+"\" style=width:30px><br>"
			+"<input type=\"radio\" id=\"buy-"+nme+"\" name=\""+nme+"\" required>"
			+"<label for=\"buy-"+nme+"\">Buy</label>"
			+"<input type=\"radio\" id=\"sell-"+nme+"\" name=\""+nme+"\">"
			+"<label for=\"sell-"+nme+"\">Sell</label><br>"
			+"<input type=\"submit\" value=\"Submit\" class=\"s\">"+"</form>"
			+"</div><br>";

			
			loc.innerHTML+=ctt;
			obj+=y.c*arr[i].quantity;
		}
		document.getElementById("va").innerHTML= "Total Account Value:$"+obj.toFixed(2);
		
		
	}
	x2http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/all?username="+localStorage.getItem("username"),true);
	x2http.send();
}

function sub(ticker){
	if(document.getElementById("quant-"+ticker).value===""){
		alert("FAILED: Transaction not possible.");
	}
	else if(document.getElementById("quant-"+ticker).value<=0){
		alert("FAILED: Transaction not possible.");
	}
	else{
		var x1http = new XMLHttpRequest();
		var amount = document.getElementById("quant-"+ticker).value;
		if(document.getElementById("sell-"+ticker).checked){
			amount*=-1;
		}
		var prc = amount*localStorage.getItem(ticker);
		var x1http = new XMLHttpRequest();
		x1http.onload = function() {
			var obj=JSON.parse(this.responseText);
			if(obj.result==="true"){
				if(amount<0){
					alert("Sold "+amount*-1+" shares of "+ticker);
				}
				else{
					alert("Bought "+amount+" shares of "+ticker);
				}
				location.href='portfolio.html';
				
			}
			else{
				alert("FAILED: Purchase not possible");
			}
			
	 		
	 	};
		x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/buy?username="
				+localStorage.getItem("username")+
				"&amount="+amount+
				"&prc="+prc+
				"&ticker="+ticker,true)
	 	x1http.send();
		
	}
	
	
	
}


	
