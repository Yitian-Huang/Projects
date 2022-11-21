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
 													+"<br><strong>Website: </strong>"+obj.weburl;
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



