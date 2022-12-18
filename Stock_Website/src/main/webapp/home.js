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
	document.getElementById("pr").innerHTML = "Summary<br><hr><strong>High Price: "+p.h+"<br>Low Price: "
												+ p.l+"<br>Open Price: "+p.o+"<br>Close Price: "+p.pc+"</strong><hr>";
	
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
				alert("Bought "+amount+" shares of "+document.getElementById("tick").innerHTML+" for "+prc);
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


const test = async() =>{
	const res = await fetch("https://finnhub.io/api/v1/quote?symbol="+"TSLA"
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg");
	const data = await res.json();
	return data;
}


async function getAll(){
	var x1http = new XMLHttpRequest();
	x1http.onload = function(){
		var obj=JSON.parse(this.responseText);
		document.getElementById("ba").innerHTML= "Cash Balance:$"+obj;
	}
	x1http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/amount?username="+localStorage.getItem("username"),true);
	x1http.send();
	
	
	var x2http = new XMLHttpRequest();
	var x3http = new XMLHttpRequest();
	var x4http = new XMLHttpRequest();
	x2http.onload = async function(){
		var arr=JSON.parse(this.responseText);
		var loc = document.getElementById("all");

		for(let i = 0; i < arr.length; i++){
			x3http.onload = function(){
				pc=JSON.parse(this.responseText);
			}
			x3http.open("GET", "https://finnhub.io/api/v1/quote?symbol="+(arr[i].ticker) 
			+"&token=cddn78qad3iag7bhsvp0cddn78qad3iag7bhsvpg", true);
			x3http.send();
			var x = await test();
			alert(x.c);

			loc.innerHTML+="<div style=\" border: 3px solid #EFEFEF; height:22px; background-color:#EFEFEF\">";
			loc.innerHTML+="<span style=\"font-size:18px\">"+arr[i].ticker+"</span>"+"</div>";
		}
	
	}
	x2http.open("GET", "http://localhost:9090/yitianhu_CSCI201_Assignment4/all?username="+localStorage.getItem("username"),true);
	x2http.send();
}

